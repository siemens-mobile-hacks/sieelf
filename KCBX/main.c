#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "..\inc\sieapi.h"
#include "conf_loader.h"

extern const char *cfn;
extern const TDate ymd;
extern const char cData[64];
extern const char FND_COLOR[];//今天颜色
extern const char FNC_COLOR[];//课程颜色
extern const char FNL_COLOR[];//线条颜色
extern const char FNM_COLOR[];//时间颜色
extern const char FNW_COLOR[];//周次颜色
extern const char FNT_COLOR[];//标题颜色
//背景
extern const char BGC_COLOR[];//选中
extern const char BGA_COLOR[];//全部
extern const char BGW_COLOR[];//周次
extern const char BGT_COLOR[];//标题
extern const char BGAM_COLOR[];//上午
extern const char BGPM_COLOR[];//下午
extern const char BGNT_COLOR[];//晚上

static short point_x=1, point_y=1; //移动查看选中项
static char *Data;

#define color(x) (x<24)?GetPaletteAdrByColorIndex(x):(char *)(&(x))
#define ColorIdx GetPaletteAdrByColorIndex(23)

typedef struct{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct{
  GUI gui;
} MAIN_GUI;


static const char ver[16] = "课程表v2.02";

unsigned short daylist=0;
unsigned int err;
TDate d;
TTime t;

unsigned int MAINCSM_ID = 0;
static short ac=10;

static void onRedraw(MAIN_GUI *data){
  WSHDR* ws = AllocWS(20);
  int week,i,j;
#ifdef ELKA
  static short aa=2;
  static short ad=24;
  static short y1=28;
  static short y2=24;
  static short ww=29;  
#else
  static short aa=1;
  static short ad=1;
  static short y1=18;
  static short y2=14;  
  static short ww=16;  
#endif
  short OHigh=y1+y2+ad;  
  short Right=ww*8+aa;
  short Left =aa+1;
  short YSize =GetFontYSIZE(FONT_SMALL);
  //时间日期星期
  GetDateTime(&d, &t);
  //计算周次
  week=((d.year-ymd.year)*365+SumDays(d.year,d.month)-SumDays(ymd.year,ymd.month)+d.day-ymd.day)/7+1;
  //底色
  DrawRectangle(0,YDISP,ScreenW()-1,ScreenH()-1,0,BGA_COLOR,BGA_COLOR);
  //课程表标题
  wsprintf(ws,PNT_ONE,ver);
  DrawString(ws,-1,YDISP+2, ScreenW()-1,3+YDISP+YSize,8,2,FNT_COLOR,ColorIdx);
  //画周次时间信息
  WSHDR* wsL = AllocWS(4);
  wsAppendChar(wsL,0xE405);  
  if(t.hour>12){
     t.hour-=12;
     wsprintf(ws, "%w:%dW %02d-%02d %02d:%02dP",wsL,week,d.month,d.day,t.hour,t.min);       
  }else{
     wsprintf(ws, "%w:%dW %02d-%02d %02d:%02dA",wsL,week,d.month,d.day,t.hour,t.min);
  }     
  
  DrawString(ws,-1,YDISP+YSize+6,ScreenW()-1,YDISP+YSize*2+6,FONT_SMALL_BOLD,2,FNT_COLOR,ColorIdx);
  FreeWS(wsL);
  //画背景框  1.时间；2.星期；3.上午；4.下午；5.晚上 width*2+aa
  DrawRectangle(Left,OHigh,   ww*2+aa,y1+ad+y2*11,0,BGT_COLOR, BGT_COLOR); // 1.时间
  DrawRectangle(Left,OHigh,   Right,y1+ad+y2*2 ,0,BGW_COLOR ,BGW_COLOR); // 2.星期
  DrawRectangle(Left,y1+y2*2+ad, Right,y1+ad+y2*6 ,0,BGAM_COLOR,BGAM_COLOR); // 3.上午
  DrawRectangle(Left,y1+y2*6+ad, Right,y1+ad+y2*ac,0,BGPM_COLOR,BGPM_COLOR); // 4.下午
  DrawRectangle(Left,y1+y2*ac+1, Right,y1+ad+y2*11,0,BGNT_COLOR,BGNT_COLOR); // 5.晚上
 //选中背景
  TRect rc={ww*2+2,y1+y2*(point_y+1)+1,ww*8+2,y1+y2*(point_y+2)};
  if(daylist==0){
    rc=SetRect(ww*(point_x+1)+2,y1+y2*(point_y+1)+1,ww*(point_x+2)+2,y1+y2*(point_y+2));  
  }
  DrawRectangle(rc.l,rc.t,rc.r,rc.b,0,BGC_COLOR,BGC_COLOR); 
  wsprintf(ws,PNT_ONE,"时间");
  DrawString(ws,10,OHigh+2,ww*8,ScreenH(),8,32,FNW_COLOR,ColorIdx);
  //课程表线及课程数据
  for(i=0;i<=7;i++){
   for(j=0;j<=ac;j++){
  //画线框
  //DrawLine(Left, y1+ad-aa,ww*(7+1)+1,y1+ad-aa,0,FNL_COLOR); //上
  DrawLine(Left, y1+ad+y2*(j+1),ww*(7+1)+1,y1+ad+y2*(j+1),0,FNL_COLOR); //下
  DrawLine(Left, y1+ad*2,Left,y1+y2*(ac+1)+ad,0,FNL_COLOR); //左
  DrawLine(Right,y1+ad*2,Right,y1+y2*(ac+1)+ad,0,FNL_COLOR); //右
  rc=SetRect(ww*(i+1)+aa,y1+y2+ad,ww*(i+1)+aa,y1+ad+y2*(ac+1)); 
  if(!daylist && i && i!=7)
   DrawLine(rc.l,rc.t,rc.r,rc.b,0,FNL_COLOR); //其它竖线，短
  else if(i==1)
   DrawLine(rc.l,rc.t,rc.r,rc.b,0,FNL_COLOR); //第二根竖线，重复，粗线
  //星期
  if(j==0 && i>0){  
   short center=32;
   if(daylist==0){
    wsprintf(ws,PNT_ONE,WeekID[i-1]);
    rc=SetRect(ww*(i+1)+5,OHigh+2,ww*8,ScreenH()); 
   }else if(daylist==1 && i==point_x){
    center = 2;
    wsprintf(ws,PNT_ONE,WeekGB[i-1]);
    rc=SetRect(ww*2+5,OHigh+3,ww*8,ScreenH());
   }
   DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,center,FNW_COLOR,ColorIdx);   
  }
  //课程数据
  if(j<9){
    char TEMP[6],Res[16];
    sprintf(TEMP,"%d.%d:",i,j+1);
    MidStr(Data,TEMP,Res);
    wsprintf(ws,PNT_ONE,Res);
    rc=SetRect(ww*(i+1)+5,OHigh+YSize+j*(YSize+2)+4,ww*8,OHigh+YSize*2+j*(YSize+2)+4); 
    if(i==0) rc.l=3; else if(daylist==1) rc.l = ww*2+5;     
    if(daylist==1 && i==point_x){      
      DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,2,FNC_COLOR,ColorIdx);    
    }else if(i==0){
      DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,32,FNM_COLOR,ColorIdx);       
    }else if(daylist==0 && i>0){
      strncpy(TEMP,Res,2);      
      TEMP[2]=0;
      wsprintf(ws,PNT_ONE,TEMP);      
      if(i==GetWeek(&d)+1){
         if(j+2==point_y)
           DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,32,FNC_COLOR,ColorIdx);   
         else
           DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,32,FND_COLOR,ColorIdx);
      }else{
        DrawString(ws,rc.l,rc.t,rc.r,rc.b,8,32,FNC_COLOR,ColorIdx);      
      }
    }
  }
 }
}
FreeWS(ws);
}
static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)){
  data->gui.state=1;
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)){
  data->gui.state=0;
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *)){
  data->gui.state=2;
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)){
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg){
  if (msg->gbsmsg->msg==KEY_DOWN){   
    switch(msg->gbsmsg->submess){
      case UP_BUTTON:    if(point_y>1)  point_y--; else point_y=ac; REDRAW(); break;
      case DOWN_BUTTON:  if(point_y<ac) point_y++; else point_y=1;  REDRAW(); break;
      case LEFT_BUTTON:  if(point_x>1)  point_x--; else point_x=6;  REDRAW(); break;
      case RIGHT_BUTTON: if(point_x<6)  point_x++; else point_x=1;  REDRAW(); break;
      case ENTER_BUTTON: if(daylist==0) daylist=1; else daylist=0;  REDRAW(); break;
      case LEFT_SOFT: REDRAW(); break;
      case GREEN_BUTTON:RunAPP((char *)cfn);break;
      case RED_BUTTON:
      case RIGHT_SOFT: CloseCSM(MAINCSM_ID); break;
    }
  }
  return(0);
}

static int method8(void){return(0);}
static int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)onRedraw,	//Redraw
	(void *)onCreate,	//Create
	(void *)onClose,	//Close
	(void *)onFocus,	//Focus
	(void *)onUnfocus,	//Unfocus
	(void *)OnKey,		//OnKey
	0,
	(void *)kill_data,	//Destroy
	(void *)method8,
	(void *)method9,
	0
};

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg){
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if(msg->msg == MSG_RECONFIGURE_REQ){    
    if(strcmp_nocase(cfn,(char *)msg->data0)==0){                
      InitConfig();
      //重新加载节日文件数据
      if(FreeFileBuf(Data)) Data=LoadFileBuf(cData); 
      ShowMSG(1,(int)ver);  
    }
  }   
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))  {
    csm->csm.state=-3;
  }
  return(1);
}

const RECT Canvas={0,0,0,0};

static void maincsm_oncreate(CSM_RAM *data){
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM *csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));	
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;	
  csm->gui_id=CreateGUI(main_gui);  
}

static void Killer(void){
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm){
  FreeFileBuf(Data);
  SUBPROC((void *)Killer);
}

const int minus11=-11;
unsigned short maincsm_name_body[140];

const struct{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM ={{
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
  },{
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void){
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),PNT_ONE,ver);
}

int main(){  
  InitConfig();
  Data=LoadFileBuf(cData);
  //根据每日时间改变默认选中课程
  GetDateTime(&d, &t);
  point_x=GetWeek(&d)+1; 

  if(t.hour<=7) point_y=1; //morning 1
  else{
    if(t.hour<=11) point_y=t.hour%7; //morning 1-4
    else{
      if(t.hour<=14) point_y=5; //afternoon 5
      else{
        if(t.hour<=17) point_y=t.hour%10; //afternoon 5-7
        else{
          if(t.hour>=22) { point_y=1; point_x=GetWeek(&d)+2; } //next morning 1
          else point_y=8; //night 8
      }
     }
    }
  }
  LockSched();  
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
