#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"


extern const int line2;
extern const int number2;
extern const char fname[128];
extern const int year;
extern const int month;
extern const int day;


typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
	GUI gui;
} MAIN_GUI;


extern void kill_data(void *p, void (*func_p)(void *));

void copy_unicode_2ws(WSHDR* ws, unsigned short* unicode)
{
	int i = 0;
	for (; unicode[i]!=0 && i<=4; i++ )
	{
		ws->wsbody[i+1] = unicode[i];
	}
	ws->wsbody[0] = i;                  // set ws length
}

unsigned short w[8]={0x4E00,0x4E8C,0x4E09,0x56DB,0x4E94,0x516D,0x4E03, 0};

char c[30]="\xE4\xB8\x80\xE4\xBA\x8C\xE4\xB8\x89\xE5\x9B\x9B\xE4\xBA\x94\xE5\x85\xAD\xE6\x97\xA5";

int num=0;
int nx=1;
unsigned int daylist=0;

unsigned int MAINCSM_ID = 0;


char* Opendata(char *recname)
{
  char *buf;
  int f;
  unsigned int err;
  unsigned int fsize;  
  f=fopen(recname,A_ReadOnly+A_BIN,P_READ,&err);
  fsize=lseek(f,0,S_END,&err,&err);
  if (fsize<=0)
  {
    fclose(f,&err);
  }
  lseek(f,0,S_SET,&err,&err);
  buf=malloc(fsize+1);
  fread(f,buf,fsize,&err);
  buf[fsize]=0;
  fclose(f,&err);
  return (buf);
}


void drawname(const char *s)
{
  WSHDR* ws = AllocWS(55);
  int c,k;
  int cc=0;
  char *r;
  char cr[55];
  while((c=*s))
  {
    s++;
    switch(c)
    {
    case '\r':
    case '\n':
      break;
      
    case '\r':
    case '\n':
      r=cr;
      k=0;
      cc++;
      while(*s!=' ' && *s && k<(sizeof(cr)-1))  
      {
        *r++=*s++;
        k++;
      }
      *r=0;
     utf8_2ws(ws,cr,l);
     DrawString(ws,1,1,132,ScreenH(),8,d,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));     
     break;
      
     default:
      break;
    }
  }
  cc=0;
  FreeWS(ws);
}



void onRedraw(MAIN_GUI *data)
{
  const char *s;
  int lz;
  char recname[128];

  //µ×É«
  DrawRectangle(0,0,ScreenW(),ScreenH(),0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));

  snprintf(recname,128,"%sdata.dat",fname);
  s=Opendata(recname);
  drawname(s);
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
  /*
  int w=0,t;
  t=num;
  while(t)
  {
    ++w;
    t=t/10;
  };*/
  num=num*10+numx;
  REDRAW();
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
#ifdef ELKA
  int aa=8;
#else
  int aa=10;
#endif
  
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
      case '#': num=num; REDRAW(); break;
      case UP_BUTTON: if(num!=0) num=num-aa; REDRAW(); break;
      case DOWN_BUTTON: if(num<aa) num=num+aa; REDRAW(); break;
      case RIGHT_BUTTON:{nx++;if(nx>7) nx=1;} REDRAW(); break;
      case LEFT_BUTTON:{nx--;if(nx<1) nx=7;}REDRAW(); break;
      case RIGHT_SOFT: CloseCSM(MAINCSM_ID); break;
    }
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON: if(num!=0)num=num-10; REDRAW(); break;
      case DOWN_BUTTON:if(num<10) num=num+10; REDRAW(); break;
      case RIGHT_BUTTON:nx++;if(nx>7) nx=1; REDRAW(); break;
      case LEFT_BUTTON:nx--;if(nx<1) nx=7; REDRAW(); break;
    }
  }
  return(0);
}

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
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

}

const int minus11=-11;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "Kcb");
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
