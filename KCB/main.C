#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

//extern const char a[512];
extern const char a1[60];
extern const char a2[60];
extern const char a3[60];
extern const char a4[60];
extern const char a5[60];
extern const char a6[60];
extern const char a7[60];

extern const char c[30];

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

unsigned short btz[]={0x8BFE,0x7A0B,0x8868, 0};
unsigned short w[8]={0x4E00,0x4E8C,0x4E09,0x56DB,0x4E94,0x516D,0x4E03, 0};

int num=0;
unsigned int MAINCSM_ID = 0;

void onRedraw(MAIN_GUI *data)
{
  //WSHDR *ws = AllocWS(256);
  //WSHDR *ws1 = AllocWS(20);
  int w=16;
  int h=16;
  //WSHDR *kc1 = AllocWS(20);
  //WSHDR *kc2 = AllocWS(20);
  //WSHDR *kc3 = AllocWS(20);
  //WSHDR *kc4 = AllocWS(20);
  //WSHDR *kc5 = AllocWS(20);
  //WSHDR *kc6 = AllocWS(20);
  //WSHDR *kc7 = AllocWS(20);
  WSHDR *kc = AllocWS(20);
  //WSHDR *kc0 = AllocWS(20);
  WSHDR *bt = AllocWS(sizeof(btz));
  WSHDR* ws = AllocWS(20);
  copy_unicode_2ws(bt, btz);
  DrawRectangle(0,0,ScreenW(),ScreenH(),0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  DrawString(bt,1,1,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

  
  TDate d;
  TTime t;
  GetDateTime(&d, &t);
  wsprintf(ws, "%d%d:%d%d", t.hour / 10, t.hour % 10, t.min / 10, t.min % 10);
  DrawString(ws,ScreenW()-GetFontYSIZE(FONT_SMALL_ITALIC_BOLD)*3, 2, ScreenW(), 1+GetFontYSIZE(FONT_SMALL_ITALIC_BOLD),
              8,
              2,
              GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)
             );
   

  DrawRoundedFrame(w*(GetWeek(&d)+1)-1,h-1,w*(GetWeek(&d)+1)+GetFontYSIZE(FONT_SMALL_ITALIC_BOLD)+3,h-1+GetFontYSIZE(FONT_SMALL_ITALIC_BOLD)+3,2,2,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(2)); 
  

 int i,j;
 for(i=0;i<=7;i++)
{
 for(j=0;j<=10;j++)
{

  DrawLine(w*(i+1)-1,h+14,w*(i+1)-1,h+14*11,0,GetPaletteAdrByColorIndex(0));
  DrawLine(w-1,h+14*(j+1),w*8-1,h+14*(j+1),0,GetPaletteAdrByColorIndex(0));
  if(j==0)
  {
  //unsigned short *p;
  //p=&w[0];
  //copy_unicode_2ws(kc,p+i-1);
  const char *pc;
  pc=&c[0];
  utf8_2ws(kc,pc+i*3,3);
  DrawString(kc,w*(i+1),h,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  else if(i==0)
  {
  wsprintf(kc,"%d",j+num);
  DrawString(kc,0,h+3+14*j,GetFontYSIZE(FONT_SMALL_ITALIC_BOLD),ScreenH(),8,4,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  /*
  else if(j>0&&i>0)
  {
  const char *pa;
  pa=&a[0];
  utf8_2ws(kc,pa+(j-1)*3+(i-1)*27,3);
  DrawString(kc,15*i,16+15*j,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  */
  else if(j>0)
  { 
  
  if(i==1)
  {
  const char *pa1;
  pa1=&a1[0];
  utf8_2ws(kc,pa1+(j-1+num)*3,3);
  DrawString(kc,w*i,h+14*j,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  if(i==2)
  {
  const char *pa2;
  pa2=&a2[0];
  utf8_2ws(kc,pa2+(j-1+num)*3,3);
  DrawString(kc,w*i,h+14*j,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  if(i==3)
  {
  const char *pa3;
  pa3=&a3[0];
  utf8_2ws(kc,pa3+(j-1+num)*3,3);
  DrawString(kc,w*i,h+14*j,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  if(i==4)
  {
  const char *pa4;
  pa4=&a4[0];
  utf8_2ws(kc,pa4+(j-1+num)*3,3);
  DrawString(kc,w*i,h+14*j,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  if(i==5)
  {
  const char *pa5;
  pa5=&a5[0];
  utf8_2ws(kc,pa5+(j-1+num)*3,3);
  DrawString(kc,w*i,h+14*j,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  if(i==6)
  {
  const char *pa6;
  pa6=&a6[0];
  utf8_2ws(kc,pa6+(j-1+num)*3,3);
  DrawString(kc,w*i,h+14*j,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  if(i==7)
  {
  const char *pa7;
  pa7=&a7[0];
  utf8_2ws(kc,pa7+(j-1+num)*3,3);
  DrawString(kc,w*i,h+14*j,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  }

}
}
  
 //wsprintf(ws1, "LGPID: %d",num);
 //wsprintf(ws, "%t",num);
  
  //DrawString(ws1,5,70,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  //DrawString(ws,5,100,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  
    FreeWS(bt);
    FreeWS(ws);
    FreeWS(kc);
  //FreeWS(ws);
  //FreeWS(ws1);
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
      case UP_BUTTON: if(num!=0) num=num-10; REDRAW(); break;
      case DOWN_BUTTON: if(num<20) num=num+10; REDRAW(); break;
      case RIGHT_BUTTON:if(num<20) num=num+10; REDRAW(); break;
      case LEFT_BUTTON: if(num!=0) num=num-10; REDRAW(); break;
      case RIGHT_SOFT: CloseCSM(MAINCSM_ID); break;
    }
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON: if(num!=0)num=num-10; REDRAW(); break;
      case DOWN_BUTTON:if(num<20) num=num+10; REDRAW(); break;
      case RIGHT_BUTTON:if(num<20) num=num+10; REDRAW(); break;
      case LEFT_BUTTON:if(num!=0) num=num-10; REDRAW(); break;
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
