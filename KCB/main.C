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
extern const int line2;
extern const int number2;
extern const int wc;
extern const int showr;
extern const char b1[140];
extern const char b2[140];
extern const char b3[140];
extern const char b4[140];
extern const char b5[140];
extern const char b6[140];
extern const char b7[140];





//extern const char c[30];

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

char c[30]="\xE4\xB8\x80\xE4\xBA\x8C\xE4\xB8\x89\xE5\x9B\x9B\xE4\xBA\x94\xE5\x85\xAD\xE6\x97\xA5";

int num=0;
int nx=1;
int week;
unsigned int MAINCSM_ID = 0;


void onRedraw(MAIN_GUI *data)
{

  //WSHDR *ws = AllocWS(256);
  //WSHDR *ws1 = AllocWS(20);
  int aa;
  week=wc+5;
  int w;
  //const char *pa1;
  WSHDR *kc = AllocWS(20);
  WSHDR *bt = AllocWS(sizeof(btz));
  WSHDR* ws = AllocWS(20);
  
  if(showr)
  {
    w=16;
    aa=1;
  }
  else
  {
  if(week==5)
  {
    w=22;
    aa=4;
  }
  if(week==6)
  {
    w=18;
   aa=2;
  }
  if(week==7)
  {
    w=16;
    aa=1;
  }
  }
  int h=16;
  

  copy_unicode_2ws(bt, btz);
  DrawRectangle(0,0,ScreenW(),ScreenH(),0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  DrawString(bt,1,1,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

  
  const char *pc;
  pc=&c[0];
  
  TDate d;
  TTime t;
  GetDateTime(&d, &t);
  wsprintf(ws, "%d%d:%d%d", t.hour / 10, t.hour % 10, t.min / 10, t.min % 10);
  DrawString(ws,ScreenW()-GetFontYSIZE(FONT_SMALL_ITALIC_BOLD)*3, 2, ScreenW(), 1+GetFontYSIZE(FONT_SMALL_ITALIC_BOLD),
              8,
              2,
              GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)
             );
  if((GetWeek(&d)+7-nx)%7<week)
  DrawRoundedFrame(w*((GetWeek(&d)+7-nx)%7+1)-aa,h-1,w*((GetWeek(&d)+7-nx)%7+1)+w-aa,h-1+GetFontYSIZE(FONT_SMALL_ITALIC_BOLD)+3,2,2,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(2)); 
 

char classr[8];
int c,k;
int cc=0;
const char *s;
char *r;
  switch((GetWeek(&d)+nx)%7)
  {
  case 1:
  s=b1;
  break;
  case 2:
  s=b2;
  break;
  case 3:
  s=b3;
  break;
  case 4:
  s=b4;
  break;
  case 5:
  s=b5;
  break;
  case 6:
  s=b6;
  break;
  case 0:
  s=b7;
  break;
  default:
      break;
  }


  while((c=*s))
  {
    s++;
    switch(c)
    {
    case '\r':
    case '\n':
      break;
      
    case ' ': 
      r=classr;
      k=0;
      cc++;
      while(*s!=' ' && *s && k<(sizeof(classr)-1))  
      {
        *r++=*s++;
        k++;
      }
      *r=0;
      if(num==0)
      {
      if(cc<=10)
      {
      utf8_2ws(kc,classr,8);
      DrawString(kc,w*6,h+14*cc+2,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));     
      }
      }
      if(num==10)
      {
      if(cc>10&&cc<20)
      {
      utf8_2ws(kc,classr,8);
      DrawString(kc,w*6,h+14*(cc-10)+2,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));     
      }
      }
      break;
      
     default:
      break;
    }
  }

 int i,j;
 for(i=0;i<=week;i++)
{
 for(j=0;j<=10;j++)
{
  int x,y,z,z2;
  if(line2)
  ((j%2)==0?(x=j):(x=j+1));
  else
  x=j;
  if(number2)
  {
  ((j%2)==0?(y=j/2):(y=j/2+1));
  ((j%2)==0?(z=j-1):(z=j));
  z2=num/2;
  }
  else
  {
  y=j;
  z=j;
  z2=num;
  }
  if(showr&&(week==5))
  {
  DrawLine(w*(7+1)-aa,h+14,w*(7+1)-aa,h+14*11,0,GetPaletteAdrByColorIndex(0));
  DrawLine(w*(week+1)-aa,h+14*(x+1),w*(week+3)-aa,h+14*(x+1),0,GetPaletteAdrByColorIndex(0));
  utf8_2ws(kc,pc+((GetWeek(&d)+nx-1)%7)*3,3);
  DrawString(kc,w*(week+2)-aa,h,w*(week+3)-aa,ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  DrawLine(w*(i+1)-aa,h+14,w*(i+1)-aa,h+14*11,0,GetPaletteAdrByColorIndex(0));
  DrawLine(w-aa,h+14*(x+1),w*(week+1)-aa,h+14*(x+1),0,GetPaletteAdrByColorIndex(0));
  if(j==0&&i>0)
  {
  utf8_2ws(kc,pc+((GetWeek(&d)+i+nx-4)%7)*3,3);
  DrawString(kc,w*i,h,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  if(i==0&&j>0)
  {
  wsprintf(kc,"%d",y+z2);
  DrawString(kc,0,h+3+14*z,GetFontYSIZE(FONT_SMALL_ITALIC_BOLD),ScreenH(),8,4,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  if(j>0&&i>0)
  { 
  switch((GetWeek(&d)+i+nx-3)%7)
  {
  case 1:
  s=a1;
  break;
  case 2:
  s=a2;
  break;
  case 3:
  s=a3;
  break;
  case 4:
  s=a4;
  break;
  case 5:
  s=a5;
  break;
  case 6:
  s=a6;
  break;
  case 0:
  s=a7;
  break;
  default:
      break;
  }       
   utf8_2ws(kc,s+(j-1+num)*3,3);  
   DrawString(kc,w*i,h+14*j,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
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
      case DOWN_BUTTON: if(num<10) num=num+10; REDRAW(); break;
    case RIGHT_BUTTON:if(week!=7){nx++;if(nx>7) nx=1;} REDRAW(); break;
    case LEFT_BUTTON:if(week!=7) {nx--;if(nx<1) nx=7;}REDRAW(); break;
      case RIGHT_SOFT: CloseCSM(MAINCSM_ID); break;
    }
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON: if(num!=0)num=num-10; REDRAW(); break;
      case DOWN_BUTTON:if(num<10) num=num+10; REDRAW(); break;
      case RIGHT_BUTTON:if(num<10) num=num+10; REDRAW(); break;
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
