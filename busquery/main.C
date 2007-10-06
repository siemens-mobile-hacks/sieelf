#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

extern const char name[128];
#define MAX_STR 512

const int minus11=-11;
char *buf=0;
int fsize=0;
WSHDR* ws;


SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};


int num=0;
int nx=0;
int mode=0;

unsigned int MAINCSM_ID = 0;


typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;


void ErrorMsg(const char *msg)
{
  LockSched();
  ShowMSG(1,(int)msg);
  UnlockSched();
}

void copy_unicode_2ws(WSHDR* ws, unsigned short* unicode)
{
	int i = 0;
	for (; unicode[i]!=0 && i<=4; i++ )
	{
		ws->wsbody[i+1] = unicode[i];
	}
	ws->wsbody[0] = i;                  // set ws length
}

void Loaddata()
{ 
  int f;
  unsigned int err;
  char fname[128];
  
  if (buf != 0)
   mfree(buf);
  snprintf(fname,128,"%sdata.txt",name);
  if ((f=fopen(fname, A_ReadOnly+A_BIN, 0, &err))==-1)
  {
         ErrorMsg("Can't open .dict file!");
         return;
  }
  fsize=lseek(f,0,S_END,&err,&err);
  lseek(f,0,S_SET,&err,&err);
  if (fsize<=0)
  {
    ErrorMsg("Zero lenght of data file!");
    fclose(f,&err);
  } 
  else if ((buf=malloc(fsize))==0)
  {
      ErrorMsg("Can't malloc!");
  }  
  else if (fread(f,buf,fsize,&err)!=fsize)
  {
      ErrorMsg("Can't read .dict file!");
      fclose(f, &err);
      mfree(buf);
      buf=0;
  }
  fclose(f,&err);
}


void onRedraw(MAIN_GUI *data)
{
  const char *s;
  DrawRectangle(0,0,ScreenW(),ScreenH(),0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  if(mode==0)
  DrawRectangle(0,14+16*(nx),130,14+16*(nx+1),0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));

  s=buf;
  int c,k;
  int cc=0;
  char *r;
  char cr[MAX_STR]; 
  //strchr(s,c)
  
  while((c=*s))
  {
    s++;
    switch(c)
    {
    case '\n': 
      r=cr;
      k=0;
      cc++;
      if(mode==0)
      {
      while(*s!='*'&& *s && k<(sizeof(cr)-1))  
      {
        *r++=*s++;
        k++;
      }
      *r=0;
      if(cc>=(num*10+1)&&cc<(num+1)*10+1)
      {
      wsprintf(ws, "%d",((num+1)*10+1)/10);
      DrawString(ws,1,1,130,ScreenH(),8,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));  
      utf8_2ws(ws,cr,MAX_STR);
      DrawString(ws,1,16+16*((cc-1)%10),132,ScreenH(),8,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));  
      }
      }
      if(mode==1)
      {
      while(*s!='\r'&&*s!='\n' && *s && k<(sizeof(cr)-1))  
      {
        *r++=*s++;
        k++;
      }
      *r=0;
      if(cc==num*10+nx+1)
      {
      utf8_2ws(ws,cr,MAX_STR);
      DrawString(ws,0,1,130,ScreenH(),8,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));  
      }
      }
      break;

     default:
      break;
    }
  }
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

void create_num(int numx)
{
  num=numx*10;
  REDRAW();
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{ 
  if (msg->gbsmsg->msg==KEY_UP)
  {
    switch(msg->gbsmsg->submess)
    {
      case '0': create_num(0); break;
      case '1': create_num(1); break;
      case '2': create_num(2); break;
      case '3': create_num(3); break;
      case '4': create_num(4); break;
      case '5': create_num(5); break;
      case '6': create_num(6); break;
      case '7': create_num(7); break;
      case '8': create_num(8); break;
      case '9': create_num(9); break;
      case '*': num=0; REDRAW(); break;
      case '#': ShowMSG(1,(int)"busquery 0.05 (c)zhanxxx(zxzyzw@163.com)");REDRAW(); break;
      case UP_BUTTON: if(nx>0) nx--; REDRAW(); break;
      case DOWN_BUTTON: nx++;if(nx>9){num++; nx=0;} REDRAW(); break;
      case RIGHT_BUTTON:num++;REDRAW(); break;
      case LEFT_BUTTON:if(num>0) num--; REDRAW(); break;
      case RIGHT_SOFT: CloseCSM(MAINCSM_ID); break;
      case ENTER_BUTTON:if(mode==0) mode=1;else mode=0;REDRAW();break;

    }
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON: if(nx>0) nx--; REDRAW(); break;
      case DOWN_BUTTON: nx++;if(nx>9){num++; nx=0;} REDRAW(); break;
      case RIGHT_BUTTON:num++;REDRAW(); break;
      case LEFT_BUTTON:if(num>0) num--; REDRAW(); break;
    }
  }
  return(0);
}

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(data, mfree_adr);
}


int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)onRedraw,	//Redraw
	(void *)onCreate,	//Create
	(void *)onClose,	//Close
	(void *)onFocus,	//Focus
	(void *)onUnfocus,	//Unfocus
	(void *)OnKey,		//OnKey
	0,
	(void *)method7,	//Destroy
	(void *)method8,
	(void *)method9,
	0
};


int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}


#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
	rc->x=x;
	rc->y=y;
	rc->x2=x2;
	rc->y2=y2;
}


const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  ws=AllocWS(MAX_STR);
  Loaddata();
  
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
	MAIN_CSM *csm=(MAIN_CSM*)data;
	zeromem(main_gui,sizeof(MAIN_GUI));
	
	patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
	csm->csm.state=0;
	csm->csm.unk1=0;
	
	csm->gui_id=CreateGUI(main_gui);
}

void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ws);
  if (buf != 0)
    mfree(buf);
}


unsigned short maincsm_name_body[140];

const struct
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

void UpdateCSMname(void) 
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "busquery");
}


int main()
{
  LockSched();
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  InitConfig(); 
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
