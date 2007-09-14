#include "../inc/swilib.h"
#include "view.h"
#include "parse_oms.h"
#include "main.h"
#include "rect_patcher.h"
#include "local_ipc.h"
#include "display_utils.h"
#include "string_works.h"
#include "destructors.h"
#include "siemens_unicode.h"
#include "inet.h"
#include "urlstack.h"

static void UpdateCSMname(void);
static int ParseInputFilename(const char *fn);

volatile int TERMINATED=0;
volatile int STOPPED=0;

int ENABLE_REDRAW=0;

extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

const char ipc_my_name[32]=IPC_BALLETMINI_NAME;
IPC_REQ gipc;

int view_url_mode; //MODE_FILE, MODE_URL
char *view_url;
static char *goto_url;

static const char percent_t[]="%t";

WSHDR *ws_console;

typedef struct
{
  CSM_RAM csm;
  int view_id;
}MAIN_CSM;


char URLCACHE_PATH[256];
char OMSCACHE_PATH[256];
char AUTHDATA_FILE[256];

static void StartGetFile(int dummy, char *fncache)
{
  IPC_REQ *sipc;
  if (view_url_mode==MODE_FILE)
  {
    unsigned int err;
    char buf[1024];
    int i;
    int f=fopen(view_url,A_ReadOnly+A_BIN,P_READ,&err);
    if (f!=-1)
    {
      int fc=-1;
      if (fncache)
      {
	fc=fopen(fncache,A_ReadWrite+A_Create+A_Truncate+A_BIN,P_READ+P_WRITE,&err);
      }
      else
      {
	UpPageStack(); 
      }
      while((i=fread(f,buf,sizeof(buf),&err))>0)
      {
	if (fc!=-1)
	{
	  fwrite(fc,buf,i,&err);
	}
	LockSched();
	if ((!TERMINATED)&&(!STOPPED))
	{
	  sipc=malloc(sizeof(IPC_REQ));
	  sipc->name_to=ipc_my_name;
	  sipc->name_from=ipc_my_name;
	  sipc->data=malloc(i+4);
	  *((int *)(sipc->data))=i;
	  memcpy(((char *)(sipc->data))+4,buf,i);
	  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_DATA_ARRIVED,sipc);
	}
	UnlockSched();
	if (TERMINATED||STOPPED) break;
      }
      if (fc!=-1) fclose(fc,&err);
      fclose(f,&err);
    }
    else
    {
      LockSched();
      ShowMSG(1,(int)"Can't open file!");
      UnlockSched();
    }
    mfree(fncache);
    STOPPED=1;
    SmartREDRAW();
  }
  if (view_url_mode==MODE_URL)
  {
    StartINET(view_url,fncache);
  }
}

//===============================================================================================
typedef struct
{
  GUI gui;
  VIEWDATA *vd;
  int cached;
  WSHDR *ws1;
  WSHDR *ws2;
}VIEW_GUI;

static void method0(VIEW_GUI *data)
{
  int scr_w=ScreenW()-1;
  int scr_h=ScreenH()-1;
  
  VIEWDATA *vd=data->vd;
  
  if (data->gui.state==2)
  {
    DrawRectangle(0,YDISP,scr_w,scr_h,0,
		  GetPaletteAdrByColorIndex(0),
		  GetPaletteAdrByColorIndex(0));
    RenderPage(vd,1);
/*    {
      WSHDR *ws=vd->ws;
      int dc=0;
      ws->wsbody[++dc]=0xE012;
      ws->wsbody[++dc]=0xE006;
      ws->wsbody[++dc]=0x0000;
      ws->wsbody[++dc]=0x0064;
      ws->wsbody[++dc]=0xE007;
      ws->wsbody[++dc]=0xFFFF;
      ws->wsbody[++dc]=0xFF64;
//      ws->wsbody[++dc]=0xE005;
      ws->wsbody[++dc]=0xE001;
      ws->wsbody[++dc]=0x440;
      ws->wsbody[++dc]=0x440;
      ws->wsbody[++dc]=0x440;
      ws->wsbody[++dc]=0x440;
      ws->wsbody[++dc]=0xE002;
      ws->wsbody[++dc]=0xE001;
//      ws->wsbody[++dc]='A';
      ws->wsbody[0]=dc;
	DrawString(ws,0,0,scr_w,20,
		   FONT_SMALL,TEXT_NOFORMAT
		       ,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
    }*/
    DrawString(ws_console,0,0,scr_w,20,
		 FONT_SMALL,TEXT_NOFORMAT
		   ,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
    extern int connect_state;
    if (!STOPPED)
    {
      int w1, h1;
      if (connect_state)
      {
        switch(connect_state)
        {
        case 1:
          wsprintf(data->ws1,percent_t,"����������...");
          break;
        case 2:
          wsprintf(data->ws1,percent_t,"���������...");
          break;
        case 3:
          wsprintf(data->ws1,percent_t,"��������...");
          break;
        }
      }
      wsprintf(data->ws2,percent_t,"����");
      
      h1=scr_h-GetFontYSIZE(FONT_MEDIUM_BOLD)-2;
      w1=scr_w-Get_WS_width(data->ws2,FONT_MEDIUM_BOLD)-2;
      DrawRectangle(0,h1,w1,scr_h,0,
                    GetPaletteAdrByColorIndex(1),
                    GetPaletteAdrByColorIndex(0));
      DrawRectangle(w1+1,h1,scr_w,scr_h,0,
                    GetPaletteAdrByColorIndex(1),
                    GetPaletteAdrByColorIndex(0));
      if ((view_url_mode==MODE_FILE && vd->oms_size<vd->page_sz) ||
          (view_url_mode==MODE_URL && connect_state==3 && vd->oms_size<vd->page_sz))
      {
        DrawRectangle(1,h1+1,vd->oms_size*(w1-1)/vd->page_sz,scr_h-1,0,
                      GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
        wsprintf(data->ws1,"%uB/%uB",vd->oms_size,vd->page_sz);
      }
      DrawString(data->ws1,0,h1+2,w1,scr_h,FONT_MEDIUM_BOLD,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));   
      DrawString(data->ws2,w1+1,h1+2,scr_w,scr_h,FONT_MEDIUM_BOLD,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));      
              
      DrawString(ws_console,0,0,scr_w,20,
		 FONT_SMALL,TEXT_NOFORMAT
		   ,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));

    }
  }
}

static void method1(VIEW_GUI *data,void *(*malloc_adr)(int))
{
  VIEWDATA *vd=malloc(sizeof(VIEWDATA));
  zeromem(vd,sizeof(VIEWDATA));
  vd->ws=AllocWS(32767);
  vd->pos_cur_ref=0xFFFFFFFF; //��� ������ �� ������� ������
  *((unsigned short *)(&vd->current_tag_d))=0xFFFF;
  data->vd=vd;
  data->ws1=AllocWS(128);
  data->ws2=AllocWS(128);
  data->gui.state=1;
  STOPPED=0;
  if ((vd->cached=data->cached))
  {
    SUBPROC((void *)StartGetFile,0,NULL);
  }
  else
  {
    SUBPROC((void *)StartGetFile,1,PushPageToStack());
  }
}

void FreeViewUrl(void)
{
  freegstr(&view_url);
}

static void method2(VIEW_GUI *data,void (*mfree_adr)(void *))
{
  STOPPED=1;
  SUBPROC((void*)StopINET);
  FreeViewData(data->vd);
  data->vd=NULL;
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
  FreeViewUrl();
}

static void method3(VIEW_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
  PNGTOP_DESC *pltop=PNG_TOP();
  pltop->dyn_pltop=&data->vd->dynpng_list->dp;
  ENABLE_REDRAW=1;
  DisableIDLETMR();
  data->gui.state=2;
}

static void method4(VIEW_GUI *data,void (*mfree_adr)(void *))
{
  PNGTOP_DESC *pltop=PNG_TOP();
  pltop->dyn_pltop=NULL;
  ENABLE_REDRAW=0;
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

static void RunOtherCopyByURL(const char *url)
{
  char fname[256];
  TDate d;
  TTime t;
  int f;
  unsigned int err;
  WSHDR *ws;
  GetDateTime(&d,&t);
  sprintf(fname,"%s%d%d%d%d%d%d.url",URLCACHE_PATH,d.year,d.month,d.day,t.hour,t.min,t.sec);
  f=fopen(fname,A_Create+A_Truncate+A_BIN+A_ReadWrite,P_READ+P_WRITE,&err);
  if (f!=-1)
  {
    fwrite(f,url,strlen(url),&err);
    fclose(f,&err);
    ws=AllocWS(256);
    str_2ws(ws,fname,255);
    ExecuteFile(ws,NULL,NULL);
    FreeWS(ws);
    unlink(fname,&err);
  }
}

static int method5(VIEW_GUI *data,GUI_MSG *msg)
{
  VIEWDATA *vd=data->vd;
  REFCACHE *rf;
  int m=msg->gbsmsg->msg;
//  REFCACHE *p;
//  REFCACHE *q;
  if ((m==KEY_DOWN)||(m==LONG_PRESS))
  {
    switch(msg->gbsmsg->submess)
    {
    case ENTER_BUTTON:
      rf=FindReference(vd,vd->pos_cur_ref);
      if (rf)
      {
	switch(rf->tag)
	{
	case 'L':
	  if (rf->id)
	  {
	    strcpy(goto_url=malloc(strlen(rf->id)+1),rf->id);
	    return 0xFF;
	  }
	  break;
	case 'r':
	  ChangeRadioButtonState(vd,rf);
	  break;
	case 'c':
	  ChangeCheckBoxState(vd,rf);
	  break;
	default:
	  ShowMSG(1,(int)"This Reftype under construction!");
	  break;
	}
      }
      else
      {
	ShowMSG(1,(int)"RF empty!");
      }
      break;
    case UP_BUTTON:
//      if (!RenderPage(vd,1)) break;
      //Check reference move
      if (vd->pos_prev_ref!=0xFFFFFFFF)
      {
	vd->pos_cur_ref=vd->pos_prev_ref;
      }
      else
      {
	LineUp(vd);
      }
      break;
    case DOWN_BUTTON:
      if (vd->pos_next_ref!=0xFFFFFFFF)
      {
	vd->pos_cur_ref=vd->pos_next_ref;
      }
      else
      {
	if (vd->pos_last_ref!=0xFFFFFFFF)
	{
	  vd->pos_cur_ref=vd->pos_last_ref;
	}
	if (!RenderPage(vd,0)) break;
	LineDown(vd);
      }
      break;
    case LEFT_BUTTON:
      m=6;
      do
      {
	if (!LineUp(vd)) break;
      }
      while(--m);
      RenderPage(vd,0);
      if (vd->pos_first_ref!=0xFFFFFFFF)
      {
	vd->pos_cur_ref=vd->pos_first_ref;
      }
      break;
    case RIGHT_BUTTON:
      m=6;
      do
      {
	if (!RenderPage(vd,0)) break;
	if (!LineDown(vd)) break;
      }
      while(--m);
      if (vd->pos_last_ref!=0xFFFFFFFF)
      {
	vd->pos_cur_ref=vd->pos_last_ref;
      }
      break;
    case LEFT_SOFT:
      STOPPED=1;
      CreateInputUrl();
      break;
    case RIGHT_SOFT:
      if (STOPPED)
      {
	mfree(PopPageFromStack());
	return 0xFE;
      }
      else
      {
	if (view_url_mode==MODE_URL)
	{
	  SUBPROC((void*)StopINET);
	}
	else
	{
	  STOPPED=1;
	}
	break;
      }
    case GREEN_BUTTON:
/*      {
	//Dump rawtext
	unsigned int ul;
	int f;
	if ((f=fopen("4:\\dumptext.raw",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
	{
	  fwrite(f,vd->rawtext,vd->rawtext_size*2,&ul);
	  fclose(f,&ul);
	}
//	RenderPage(vd,2); //With dump
      }*/
      rf=FindReference(vd,vd->pos_cur_ref);
      if (rf)
      {
	if (rf->tag=='L')
	{
//	  ShowMSG(0x10,(int)(rf->id));
	  if (rf->id)
	  {
	    if (strlen(rf->id)>2)
	    {
	      RunOtherCopyByURL(rf->id+2);
	    }
	  }
	}
      }
      break;
    }
  }
  DirectRedrawGUI();
  return(0);
}

static int method8(void){return(0);}

static int method9(void){return(0);}

static const void * const gui_methods[11]={
  (void *)method0,  //Redraw
  (void *)method1,  //Create
  (void *)method2,  //Close
  (void *)method3,  //Focus
  (void *)method4,  //Unfocus
  (void *)method5,  //OnKey
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)method8,
  (void *)method9,
  0
};

static int CreateViewGUI(int cached)
{
  static const RECT Canvas={0,0,0,0};
  VIEW_GUI *view_gui=malloc(sizeof(VIEW_GUI));
  zeromem(view_gui,sizeof(VIEW_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  view_gui->gui.canvas=(void *)(&Canvas);
//  view_gui->gui.flag30=2;
  view_gui->gui.methods=(void *)gui_methods;
  view_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  view_gui->cached=cached;
  return CreateGUI(view_gui);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ws_console=AllocWS(1024);
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->view_id=CreateViewGUI(0);
}

static void KillAll(void)
{
  FreePageStack();
  FreeWS(ws_console);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  KillAll();
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  TERMINATED=1;
  mfree(goto_url);
  SUBPROC((void *)Killer);
}

static void GotoLink(void)
{
  LockSched();
  if (!TERMINATED)
  {
    IPC_REQ *sipc;
    sipc=malloc(sizeof(IPC_REQ));
    sipc->name_to=ipc_my_name;
    sipc->name_from=ipc_my_name;
    sipc->data=NULL;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_GOTO_URL,sipc);
  }
  UnlockSched();
}

static void GotoFile(void)
{
  LockSched();
  if (!TERMINATED)
  {
    IPC_REQ *sipc;
    sipc=malloc(sizeof(IPC_REQ));
    sipc->name_to=ipc_my_name;
    sipc->name_from=ipc_my_name;
    sipc->data=NULL;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_GOTO_FILE,sipc);
  }
  UnlockSched();
}


static int char16to8(int c)
{
  if (c<0x400) return (c);
  c-=0x400;
  if (c<16)
  {
    if (c==1) c=0;
    else if (c==4) c=2;
    else if (c==6) c=10;
    else return (c);
  }
  else if (c>79)
  {
    if (c==0x51) c=16;
    else if (c==0x54) c=18;
    else if (c==0x56) c=11;
    else if (c==0x57) c=23;
    else return (c);
  }
  else c+=8;
  c+=168;
  return (c);
}


static const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"�������"},
  {0x0001,0x0000,(int)"������"},
  {0x003D,0x0000,(int)"+"}
};



static const SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};


static const HEADER_DESC input_url_hdr={0,0,0,0,NULL,(int)"�����",LGP_NULL};

static void input_url_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"�������"};
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

static void input_url_locret(void){}

static int input_url_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  WSHDR *ws;
  char *s;
  if (msg->keys==0xFFF)
  {
    ExtractEditControl(data,1,&ec);
    ws = ec.pWS;
    s = goto_url = (char *)malloc(ws->wsbody[0]+3);
    *s++='0';
    *s++='/';
    for (int i=0; i<ws->wsbody[0]; i++) *s++=char16to8(ws->wsbody[i+1]);
    *s = 0;
    SUBPROC((void*)GotoLink);
    return 1;
  }
  return (0);
}

static const INPUTDIA_DESC input_url_desc =
{
  1,
  input_url_onkey,
  input_url_ghook,
  (void *)input_url_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - ��������� �� ������� ����
  //  0x00000002 - ��������� �� ������
  //  0x00000004 - �������� ���������
  //  0x00000008 - UnderLine
  //  0x00000020 - �� ���������� �����
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - �� ��������� ������
  //  0x40000000 - �������� ������� ����-������
  0x40000000
};

static const char wintranslation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0x5F,0xFD,0x83,0xB3,0x15,0xF0,0x63,0xF2,0x3C,0xBF,0x2D,0x52,0xF4,
  0xF8,0x2B,'I' ,'i' ,0xA3,0xE7,0x14,0xFA,0xF1,0xFC,0xF3,0x3E,0x5F,0x5F,0x5F,0xF5,
  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
  0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
  0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
  0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF
};

static const char koi8translation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0xF1,0xF3,0x5F,'i' ,0xF5,0xF0,0x63,0xF2,0x3C,0xBF,0xA3,0x52,0xF4,
  0xF8,0x2B,0x5F,0xF0,0xF2,0xE7,'I' ,0xF4,0xF1,0xFC,0xF3,0x3E,0x5F,0x83,0x5F,0xF5,

  0xEE,0xA0,0xA1,0xE6,0xA4,0xA5,0xE4,0xA3,0xE5,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,
  0xAF,0xEF,0xE0,0xE1,0xE2,0xE3,0xA6,0xA2,0xEC,0xEB,0xA7,0xE8,0xED,0xE9,0xE7,0xEA,
  0x9E,0x80,0x81,0x96,0x84,0x85,0x94,0x83,0x95,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,
  0x8F,0x9F,0x90,0x91,0x92,0x93,0x86,0x82,0x9C,0x9B,0x87,0x98,0x9D,0x99,0x97,0x9A
};

static const unsigned short dos2unicode[128]=
{
  0x0410,0x0411,0x0412,0x0413,0x0414,0x0415,0x0416,0x0417,
  0x0418,0x0419,0x041A,0x041B,0x041C,0x041D,0x041E,0x041F,
  0x0420,0x0421,0x0422,0x0423,0x0424,0x0425,0x0426,0x0427,
  0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,
  0x0430,0x0431,0x0432,0x0433,0x0434,0x0435,0x0436,0x0437,
  0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043E,0x043F,
  0x002D,0x002D,0x002D,0x00A6,0x002B,0x00A6,0x00A6,0x00AC,
  0x00AC,0x00A6,0x00A6,0x00AC,0x002D,0x002D,0x002D,0x00AC,
  0x004C,0x002B,0x0054,0x002B,0x002D,0x002B,0x00A6,0x00A6,
  0x004C,0x0433,0x00A6,0x0054,0x00A6,0x003D,0x002B,0x00A6,
  0x00A6,0x0054,0x0054,0x004C,0x004C,0x002D,0x0433,0x002B,
  0x002B,0x002D,0x002D,0x002D,0x002D,0x00A6,0x00A6,0x002D,
  0x0440,0x0441,0x0442,0x0443,0x0444,0x0445,0x0446,0x0447,
  0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F,
  0x0401,0x0451,0x0404,0x0454,0x0407,0x0457,0x040E,0x045E,
  0x00B0,0x2022,0x00B7,0x0076,0x2116,0x00A4,0x00A6,0x00A0
};



static unsigned int char8to16(int c, int type)
{
  if (c>=128)
  {
    switch(type)
    {
    case 1:
      //Win->Dos
      c=wintranslation[c-128];
      break;
    case 2:
      //Koi8->Dos
      c=koi8translation[c-128];
      break;
    case 3:
      break;
      //Dos
    }
    if (c<128) return(c);
    return(dos2unicode[c-128]);
  }
  return(c);
}

static void ascii2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c,1));
  }
}

static void CreateInputUrl()
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  
  
  eq=AllocEQueue(ma,mfree_adr());    // Extension
  WSHDR *ews=AllocWS(1024);

  ascii2ws(ews,view_url);  

  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);   //2

  FreeWS(ews);
  patch_header(&input_url_hdr);
  patch_input(&input_url_desc);
  CreateInputTextDialog(&input_url_desc,&input_url_hdr,eq,1,0);

}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  int csm_result=1;
  //IPC
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
	switch (msg->submess)
	{
	case IPC_DATA_ARRIVED:
	  //���� ������� ���� ����������� ���������, ������ ��������� �����
	  if (ipc->name_from==ipc_my_name)
	  {
	    VIEW_GUI *p=FindGUIbyId(csm->view_id,NULL);
	    VIEWDATA *vd;
	    int len=*((int*)(ipc->data));
	    char *buf=((char*)(ipc->data))+4;
	    if (p)
	    {
	      vd=p->vd;
	      if (vd)
	      {
		OMS_DataArrived(vd,buf,len);
		if (IsGuiOnTop(csm->view_id)) DirectRedrawGUI();
	      }
	    }
	    mfree(ipc->data);
	    mfree(ipc);
            csm_result=0;  //���������� ��������� 
	  }
	  break;
	case IPC_GOTO_URL:
	  if (ipc->name_from==ipc_my_name)
	  {
	    mfree(ipc);
	    FreeViewUrl();
	    view_url=goto_url;
	    view_url_mode=MODE_URL;
	    goto_url=NULL;
	    UpdateCSMname();
	    csm->view_id=CreateViewGUI(0);
            csm_result=0;  //���������� ��������� 
	  }
	  break;
	case IPC_GOTO_FILE:
	  if (ipc->name_from==ipc_my_name)
	  {
	    mfree(ipc);
	    if (ParseInputFilename(goto_url))
	    {
	      UpdateCSMname();
	      csm->view_id=CreateViewGUI(1);
	    }
	    mfree(goto_url);
	    goto_url=NULL;
            csm_result=0;   //���������� ��������� 
	  }
	  break;
	}
      }
    }
  }
  ParseSocketMsg(msg);
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->view_id)
    {
      switch((int)msg->data1)
      {
      case 0xFE:
	//������� ���� �� ����� �����
	if ((goto_url=PopPageFromStack()))
	{
	  SUBPROC((void*)GotoFile);
	  break;
	}
	goto L_CLOSE;
      case 0xFF:
	if (goto_url)
	{
	  //���� ���� �����
	  SUBPROC((void*)GotoLink);
	  break;
	}
	else
	  goto L_CLOSE;
      default:
      L_CLOSE:
	csm->csm.state=-3;
	break;
      }
    }
  }
  return(csm_result);
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  switch(view_url_mode)
  {
  case MODE_FILE:
    str_2ws(ws,view_url,255);
    break;
  case MODE_URL:
    wsprintf(ws,"%s",view_url+2);
    break;
  }
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"BM: %w",ws);
  FreeWS(ws);
}

static int ParseInputFilename(const char *fn)
{
  char *s=strrchr(fn,'.');
  FreeViewUrl();
  if (s)
  {
    s++;
    if (!strcmp_nocase(s,"oms"))
    {
      view_url=globalstr(fn);
      view_url_mode=MODE_FILE;
    }
    else
      if (!strcmp_nocase(s,"url"))
      {
	int f;
	unsigned int err;
	int fsize;
	char *buf;
	FSTATS stat;
	if (GetFileStats(fn,&stat,&err)==-1) return 0;
	if ((fsize=stat.size)<=0) return 0;
	if ((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 0;
	buf=malloc(fsize+3);
	buf[0]='0';
	buf[1]='/';
	buf[fread(f,buf+2,fsize,&err)+2]=0;
	fclose(f,&err);
	s=buf;
	while(*s>32) s++;
	*s++=0;
	view_url=realloc(buf,s-buf);
	view_url_mode=MODE_URL;
      }
      else return 0;
    return 1;
  }
  return 0;
}

char AUTH_PREFIX[64];
char AUTH_CODE[128];

int LoadAuthCode(void)
{
  int f;
  unsigned int err;
  int fsize;
  char *buf;
  char *s;
  int c;
  FSTATS stat;
  if (GetFileStats(AUTHDATA_FILE,&stat,&err)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if ((f=fopen(AUTHDATA_FILE,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 0;
  buf=malloc(fsize+1);
  buf[fread(f,buf,fsize,&err)]=0;
  fclose(f,&err);
  s=buf;
  f=0;
  err=0;
  while((c=*s++)>=32)
  {
    if (c=='.') break;
    if (f<63) AUTH_PREFIX[f++]=c;
  }
  if (c)
  {
    while((c=*s)<32)
    {
      if (!c) goto LEND;
      s++;
    }
    f=0;
    while((c=*s++)>32)
    {
      if (c=='.') break;
      if (f<127) AUTH_CODE[f++]=c;
    }
    err=1;
  }
LEND:
  mfree(buf);
  return err;
}

int main(const char *exename, const char *filename)
{
  char dummy[sizeof(MAIN_CSM)];
  char *path=strrchr(exename,'\\');
  int l;
  if (!path) return 0; //����� �����-��
  path++;
  l=path-exename;
  memcpy(URLCACHE_PATH,exename,l);
  strcat(URLCACHE_PATH,"UrlCache\\");
  memcpy(OMSCACHE_PATH,exename,l);
  strcat(OMSCACHE_PATH,"OmsCache\\");
  memcpy(AUTHDATA_FILE,exename,l);
  strcat(AUTHDATA_FILE,"AuthCode");
  if (!LoadAuthCode())
  {
    LockSched();
    ShowMSG(1,(int)"BM: Can't load AuthCode!");
    UnlockSched();
    SUBPROC((void *)Killer);
    return 0;
  }
  if (ParseInputFilename(filename))
  {
    UpdateCSMname();
    LockSched();
    CreateCSM(&MAINCSM.maincsm,dummy,0);
    UnlockSched();
  }
  else
  {
    LockSched();
    ShowMSG(1,(int)"BM: Nothing to do!");
    UnlockSched();
    SUBPROC((void *)Killer);
  }
  return 0;
}
