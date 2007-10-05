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


void getfname(char *recname,int x)
{
  switch(x)
  {
  case 1:
  snprintf(recname,128,"%s1.txt",fname);
  break;
  case 2:
  snprintf(recname,128,"%s2.txt",fname);
  break;
  case 3:
  snprintf(recname,128,"%s3.txt",fname);
  break;
  case 4:
  snprintf(recname,128,"%s4.txt",fname);
  break;
  case 5:
  snprintf(recname,128,"%s5.txt",fname);
  break;
  case 6:
  snprintf(recname,128,"%s6.txt",fname);
  break;
  case 0:
  snprintf(recname,128,"%s7.txt",fname);
  break;
  default:
      break;
  }
}


void drawname(const char *s,int l,int a,int b,int d,int h,int h2)
{
  WSHDR* ws = AllocWS(55);
  int c,k;
  int cc=0;
  char *r;
  char cr[55];
#ifdef ELKA
  int n=8;
  int ab=h+2;
#else
  int n=10; 
  int ab=2;
#endif
  
  
  while((c=*s))
  {
    s++;
    switch(c)
    {
    case '\r':
    case '\n':
      break;
      
    case ' ': 
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
     if(line2)
     {
       if(num==0&&cc<=(n/2))
        DrawString(ws,a,h+h2*(cc*2-1)+ab,b,ScreenH(),8,d,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));     
      if(num==n&&cc>(n/2)&&cc<n)
        DrawString(ws,a,h+h2*(cc*2-n-1)+ab,b,ScreenH(),8,d,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));     
     }
     else
     {
      if(num==0&&cc<=n)
        DrawString(ws,a,h+h2*cc+ab,b,ScreenH(),8,d,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));     
      if(num==n&&cc>n&&cc<(n*2))
        DrawString(ws,a,h+h2*(cc-n)+ab,b,ScreenH(),8,d,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));     
     }
      break;
      
     default:
      break;
    }
  }
  cc=0;
  FreeWS(ws);
}

int m2d(int m,int y)
{
  int b;
  switch(m)
  {
  case 1:b=0;break;
  case 2:b=31; break;   
  case 3:b=59; break; 
  case 4:b=90; break; 
  case 5:b=120; break;
  case 6:b=151; break;
  case 7:b=181; break; 
  case 8:b=212; break;
  case 9:b=243; break; 
  case 10:b=273; break;
  case 11:b=304; break;
  case 12:b=334; break;
  default:
      break;
  }
  if(y%4==0&&b>2)
    b=b+1;
  return(b);
}



void onRedraw(MAIN_GUI *data)
{
  WSHDR* ws = AllocWS(20);
  WSHDR* ws1 = AllocWS(20);
  const char *pc;
  pc=c;
  const char *s;
  int lx,ly,lz;
  int x,y,z,z2;
  int week;
  char recname[128];
#ifdef ELKA
  int aa=2;
  int h=30;
  int h2=26;
  int w=29;
  int ab=26;
  int ac=8;
  int ad=h2;
#else
  int h=16; 
  int h2=14;
  int aa=1;
  int w=16;
  int ab=0;
  int ac=10;
  int ad=0;
#endif

  //底色
  DrawRectangle(0,0,ScreenW(),ScreenH(),0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  
  //时间日期星期
  TDate d;
  TTime t;
  GetDateTime(&d, &t);
  
  week=((d.year-year)*365+m2d(d.month,d.year)-m2d(month,year)+d.day-day)/7+1;
  
  utf8_2ws(ws1,pc+GetWeek(&d)*3,3);
  wsprintf(ws, "%d%d-%d-%d W%d %w %d%d:%d%d",(d.year%100)/10,(d.year%1000),d.month,d.day,week,ws1,t.hour/10, t.hour % 10, t.min/10, t.min%10);
  DrawString(ws,3,3+ab, ScreenW()-3,3+ab+GetFontYSIZE(FONT_SMALL_ITALIC_BOLD),
              8,
              2,
              GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)
             );
  
  //if((GetWeek(&d)+7-nx)%7<week)
  //DrawRoundedFrame(w*((GetWeek(&d)+7-nx)%7+1)-aa,h-1,w*((GetWeek(&d)+7-nx)%7+1)+w-aa,h-1+GetFontYSIZE(FONT_SMALL_ITALIC_BOLD)+3,2,2,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(2)); 
 

  //
  if(line2)
  {
  lx=6;
  ly=24;
  lz=54;
  }
  else
  {
  lx=3;
  ly=12;
  lz=27;
  }

  
  if(daylist==0)
  {
//1
  getfname(recname,(GetWeek(&d)+nx-2)%7);
  s=Opendata(recname);
  drawname(s,lx,w*1,w*2,32,h,h2);

//2
  getfname(recname,(GetWeek(&d)+nx-1)%7);
  s=Opendata(recname);
  drawname(s,lx,w*2,w*3,32,h,h2);

//3
  getfname(recname,(GetWeek(&d)+nx)%7);
  s=Opendata(recname);
  drawname(s,ly,w*3-aa-2,w*6+aa,2,h,h2);
  
//4
  getfname(recname,(GetWeek(&d)+nx+1)%7);
  s=Opendata(recname);
  drawname(s,lx,w*6,w*7,32,h,h2);
  
 //5 
  getfname(recname,(GetWeek(&d)+nx+2)%7);
  s=Opendata(recname);
  drawname(s,lx,w*7,w*8,32,h,h2);
  }
  else
  {
  getfname(recname,(GetWeek(&d)+nx)%7);
  s=Opendata(recname);
  drawname(s,lz,w*1-aa-2,w*8+aa,2,h,h2);
  }
  
 int i,j;
 for(i=0;i<=5;i++)
{
 for(j=0;j<=ac;j++)
{
  
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
  
  if(line2)
  ((j%2)==0?(x=j):(x=j+1));
  else
  x=j;


  //画框
  DrawLine(w-aa,h+ad-aa,w*(7+1)-aa,h+ad-aa,0,GetPaletteAdrByColorIndex(0));
  DrawLine(w-aa,h+h2*(x+1)+ad,w*(7+1)-aa,h+h2*(x+1)+ad,0,GetPaletteAdrByColorIndex(0));
  if(daylist==0)
  {
  if(i<3)
  DrawLine(w*(i+1)-aa,h-aa+ad,w*(i+1)-aa,h+h2*(ac+1)+ad,0,GetPaletteAdrByColorIndex(0));
  if(i>=3)
  DrawLine(w*(i+3)-aa,h-aa+ad,w*(i+3)-aa,h+h2*(ac+1)+ad,0,GetPaletteAdrByColorIndex(0)); 
  }
  else
  {
  DrawLine(w-aa,h-aa+ad,w-aa,h+h2*(ac+1)+ad,0,GetPaletteAdrByColorIndex(0)); 
  DrawLine(w*8-aa,h-aa+ad,w*8-aa,h+h2*(ac+1)+ad,0,GetPaletteAdrByColorIndex(0)); 
  }
  //星期
  if(j==0&&i>0)
  {
  utf8_2ws(ws,pc+((GetWeek(&d)+i+nx-4)%7)*3,3);
  if(i==3)
  DrawString(ws,w*(i+1),h+ad,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  if(daylist==0)
  {
  if(i<3)
  DrawString(ws,w*i,h+ad,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  if(i>3)
  DrawString(ws,w*(i+2),h+ad,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));  
  }
  }

  //数字
  if(i==0&&j>0)
  {
  wsprintf(ws,"%d",y+z2);
  DrawString(ws,0,h+3+h2*z+ad,GetFontYSIZE(FONT_SMALL_ITALIC_BOLD)+aa,ScreenH(),8,4,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
}
}
    FreeWS(ws);
    FreeWS(ws1);
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
      case ENTER_BUTTON:
        if(daylist==0)
        daylist=1;
        else
        daylist=0;REDRAW()
         ;break;
      //ShowMSG(1,(int)"kcb 0.96 (c)zhanxxx(zxzyzw@163.com)")
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
