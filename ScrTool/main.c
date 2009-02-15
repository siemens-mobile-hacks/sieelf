#include <swilib.h>
#include <cfg_items.h>
#include <sieapi.h>
#include <playsound.h>
#include "scrtool.h"
#include "conf_loader.h"
//注释这里编译成完全后台运行版本
static char ANST[]="软件配置";//配置
static char ANTO[]="关机-玫瑰v2.27";//关机
static char ANRT[]="重启手机";//重启
static char ANLK[]="锁住键盘";//锁键
static char TASK[]="任务菜单";//任务菜单
static char ALRM[]="酷酷闹钟";//闹钟界面
static const IPC_REQ SCR_IPC={SCR_NAME, SCR_NAME, NULL};
static const int MINUSLL=-11;
static int   TASK_ID   = 0;//记录图形界面
static int   RING_ID   = 0;//记录闹钟响铃
static char  TASK_STATE;//记录运行界面类型,1为菜单,2为快捷菜单,3为闹钟界面
static ubyte AUTO_EXIT = 0;//记录自动退出菜单状态
static ubyte SUCC_HOOK = 0;//记录HOOK状态
static int   mCount,mSelet,aCur;
//定义数据缓存区
static char *Gala;
//配置菜单
static char  PATHS[64],TITLE[32];
static TSCR  SCR[MAX_SCR];
static TAPP  APP[MAX_APP];
static TLunar NLi;
static GBSTMR tskTimer,scrTimer;
static short OLScr;//屏幕亮灯原值
static TTime t; 
static TDate d;
static short week=0;
static short SWYD=0;

CSM_DESC  icsmd;
//CSM_DESC* ocsmd;
int  (*OICSMOnMessage)(CSM_RAM*,GBS_MSG*);
void (*OICSMOnClose)(CSM_RAM*);
//菜单标题信息
HEADER_DESC MENU_HDR={0,0,0,0,NULL,(int)TITLE,LGP_NULL};
//关闭有的菜单
static void CloseTask(void){
  if(IsTimerProc(&tskTimer)){GBS_DelTimer(&tskTimer);}  
  if(TASK_STATE==SCR_ALARM){
   if(RING_ID)PlayMelody_StopPlayback(RING_ID);      
   SetIllumination(0,1,OLScr,0);     
   SetVibration(0);
   RING_ID=0;
  }  
  if(TASK_ID)CloseCSM(TASK_ID); 
  AUTO_EXIT=0;    
  TASK_ID=0; 
  DoIDLE();
}
//菜单按键操作
static int  MENU_ONKEY(void *gui, GUI_MSG *msg);
//菜单HOOK操作命令
static void MENU_HOOK(void *gui, int cmd){
  TFile *FileList=MenuGetUserPointer(gui);
  if(cmd==3){ 
    FreeFile(FileList);
  }  
}
//菜单重画列表
static void MENU_DRAW(void *gui, int cur_item, void *user_pointer){
  WSHDR *ws;
  TFile *FileList=user_pointer;
  for(int n=0; n!=cur_item; n++) FileList=FileList->next;
  void *item=AllocMenuItem(gui);
  if(FileList){
    int len=strlen(FileList->file);
    ws=AllocMenuWS(gui,len+4);
    if(FileList->type){
       str_2ws(ws,FileList->file,len);
       wsInsertChar(ws,0x0002,1);
       wsInsertChar(ws,0xE008,1);
    }else{str_2ws(ws,FileList->file,len);}
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    wsprintf(ws,"%t","错误!!!");
  }  
  SetMenuItemText(gui, item, ws, cur_item); 
}
//菜单按键初始化
static int MENU_SOFTKEYS[]={0,1,2};
//菜单软键名称
SOFTKEY_DESC MENU_PRESS[]={
  {0x0018,0x0000,(int)"打开"},
  {0x0001,0x0000,(int)"退出"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB MENU_TAB={MENU_PRESS,0};
//定义菜单结构
MENU_DESC MENU_STRUCT={
  8,
  MENU_ONKEY,
  MENU_HOOK,
  NULL,
  MENU_SOFTKEYS,
  &MENU_TAB,
  0x10,
  MENU_DRAW,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};
//定义按钮响应事件
static int MENU_ONKEY(void *gui, GUI_MSG *msg){
  TFile *sbtop=MenuGetUserPointer(gui);
  if(msg->keys==0x3D || msg->keys==0x18){
    int i=GetCurMenuItem(gui);
    SetMenuItemIcon(gui,i,0);
    for(int n=0; n!=i; n++) sbtop=sbtop->next;
    if(sbtop){      
      CloseTask();
      RunAPP(sbtop->path);
      return(1);
    }
  }
  if((msg->keys==0x01 || msg->keys==RED_BUTTON)&&(TASK_ID)) CloseTask();  
  return(0);
}
//搜索配置文件
static TFile *FindBCFGFile(){
  uint err;
  DIR_ENTRY de;
  int  len;
  TFile *filelist=0;
  char str[128];
  strcpy(str,PATHS);
  if(isdir(PATHS,&err))strcat(str,"*");
  if(FindFirstFile(&de,str,&err)){
    do{
      if(!(de.file_attr&FA_DIRECTORY)){
        TFile *sb=malloc(sizeof(TFile));
        //设置文件目录
        len=strlen(de.folder_name)+strlen(de.file_name)+2+1;
        sb->path=malloc(len);        
        strcpy(sb->path,de.folder_name);
        strcat(sb->path,"\\");
        strcat(sb->path,de.file_name);
        //设置文件名称
        sb->file=malloc(strlen(de.file_name)+1);        
        strcpy(sb->file,de.file_name);
        //隐藏扩展名
        if(!SHOW_EXT)sb->file[getstrpos(sb->file,'.')]=0;
        sb->type=0;
        sb->next=0;
        if(filelist){
          TFile *sbr, *sbt;
          sbr=(TFile *)&filelist;
          sbt=filelist;
          while(strcmp_nocase(sbt->file,sb->file)<0){
            sbr=sbt;
            sbt=sbt->next;
            if(!sbt) break;
          }
          sb->next=sbt;
          sbr->next=sb;
        } else{filelist=sb;}
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return filelist;
}
//创建主菜单
static int BrowserFileMenu(){ 
  TFile *sbtop=FindBCFGFile();
  patch_header(&MENU_HDR);
  return CreateMenu(0,0,&MENU_STRUCT,&MENU_HDR,0,FileCount(sbtop),sbtop,0);
}
//结束配置菜单
//初始化生日显示数据
static void SetIDS(TSCR *INFO,int ENA,uint TYPE,int FONT,const char *PEN,const char *BUH){
  INFO->Show  = ENA;
  INFO->Size  = FontType(FONT);
  INFO->Style = TYPE;    
  memcpy(INFO->PEN,PEN,4);
  memcpy(INFO->BUH,BUH,4);
}
static void InitShow(void){
 SetIDS(&SCR[ 0],TEMP_ENA,TEMP_XT,TEMP_FT,TEMP_CS,TEMP_CB);
 SetIDS(&SCR[ 1],VOLT_ENA,VOLT_XT,VOLT_FT,VOLT_CS,VOLT_CB);
 SetIDS(&SCR[ 2],RAMT_ENA,RAMT_XT,RAMT_FT,RAMT_CS,RAMT_CB);
 SetIDS(&SCR[ 3],TEXT_ENA,TEXT_XT,TEXT_FT,TEXT_CS,TEXT_CB);
 SetIDS(&SCR[ 4],NETI_ENA,NETI_XT,NETI_FT,NETI_CS,NETI_CB);
 SetIDS(&SCR[ 5],CPUI_ENA,CPUI_XT,CPUI_FT,CPUI_CS,CPUI_CB);
 SetIDS(&SCR[ 6],GPRS_ENA,GPRS_XT,GPRS_FT,GPRS_CS,GPRS_CB);
 SetIDS(&SCR[ 7],WEEK_ENA,WEEK_XT,WEEK_FT,WEEK_CS,WEEK_CB);
 SetIDS(&SCR[ 8],DATE_ENA,DATE_XT,DATE_FT,DATE_CS,DATE_CB);
 SetIDS(&SCR[ 9],TIME_ENA,TIME_XT,TIME_FT,TIME_CS,TIME_CB);
 SetIDS(&SCR[10],CHSD_ENA,CHSD_XT,CHSD_FT,CHSD_CS,CHSD_CB);
 SetIDS(&SCR[11],NBIR_ENA,NBIR_XT,NBIR_FT,NBIR_CS,NBIR_CB);
 SetIDS(&SCR[12],OBIR_ENA,OBIR_XT,OBIR_FT,OBIR_CS,OBIR_CB);
}
#pragma inline  
static int wsprintf_bytes(WSHDR *ws, uint bytes){
  if(bytes<=1024)
    return(wsprintf(ws,"%uB",bytes));
  else{
    bytes>>=10;
    return(wsprintf(ws,"%uKB",bytes));
  }  
}
//显示内容配色和位置显示等
static void FillScreen(TSCR *INFO,uint x,uint y){  
  int wstyle =PixlsWidth(INFO->WS,INFO->Size);
  switch(INFO->Style){
    case 1:INFO->L=0;break;
    case 2:INFO->L=(ScreenW()-wstyle-1)/2;break;
    case 3:INFO->L=ScreenW()-wstyle-1;break;
   default:INFO->L=x;break;
  }  
  INFO->T=y;
  INFO->R=INFO->L+wstyle;  
  INFO->B=INFO->T+GetFontYSIZE(INFO->Size);
}


//菜单功能
static void APP_TRAF(char *Name, int i, int Type,char *Pic,char *File){
  APP[i].Type = Type;
  APP[i].Pic  = Pic;
  APP[i].File = File;
  APP[i].Name = Name;
  if((File)&&(strlen(File)))mCount+=1;
}
//对所有显示数据进行补始化
static void InitScreen(void){  
  if(SCR[0].Show){//显示温度信息 
    int c=GetAkku(1,3)-0xAAA+15;
    wsprintf(SCR[0].WS,"%d.%d癈",c/10,c%10);
    FillScreen(&SCR[0],TEMP_X,TEMP_Y);
  }   
  if(SCR[1].Show){//显示电压信息    
    if(VOLT_TY==0){
      int c=GetAkku(0,9);
      wsprintf(SCR[1].WS,"%d.%02dV",c/1000,(c%1000)/10);
    }elif(VOLT_TY==1){
      wsprintf(SCR[1].WS,"%3d%%",*RamCap());
    }
    FillScreen(&SCR[1],VOLT_X,VOLT_Y);
  }
  if(SCR[2].Show){//显示剩余信息  
    wsprintf_bytes(SCR[2].WS,GetFreeRamAvail());
    FillScreen(&SCR[2],RAMT_X,RAMT_Y);  
  } 
  if(SCR[3].Show){//显示定义信息
    wsprintf(SCR[3].WS,PFMT_STR,TEXT_CP);
    FillScreen(&SCR[3],TEXT_X,TEXT_Y);
  }         
  if(SCR[4].Show){//显示网络信息
    RAMNET *net_data=RamNet();
    int c=(net_data->ch_number>=255)?'=':'-';
    wsprintf(SCR[4].WS,"%c%ddB",c,net_data->power);
    FillScreen(&SCR[4],NETI_X,NETI_Y);
  }       
  if(SCR[5].Show){//显示CPU使用率
    wsprintf(SCR[5].WS,"%3d%%",GetCPULoad());
    FillScreen(&SCR[5],CPUI_X,CPUI_Y);
  }       
  if(SCR[6].Show){//显示GPRS流量
    //RefreshGPRSTraffic();
   // int c=*GetGPRSTrafficPointer();
    wsprintf_bytes(SCR[6].WS,*GetGPRSTrafficPointer());
    FillScreen(&SCR[6],GPRS_X,GPRS_Y);
  }
  //定义时间信息
  uword UniToday[8];  
  if(SCR[7].Show){//显示当前星期    
    if(WEEK_FMT <4){
      char cWeek[16];
      for(ubyte i=0;i<16;i++){cWeek[i]=cWeekName[WEEK_FMT][week][i];}
      wsprintf(SCR[7].WS,cWeek,week);
    }else if(WEEK_FMT==4){
      wsprintf(SCR[7].WS,_percent_e,WeekHD,WeekID[week]);
    }else{
      wsprintf(SCR[7].WS,PFMT_STR,WeekID[week]); 
    }
    FillScreen(&SCR[7],WEEK_X,WEEK_Y);
  }
  if(SCR[8].Show){//显示当前日期
    char cData[16]; 
    for(ubyte i=0;i<16;i++){cData[i]=cDataFmt[DATE_FMT][i]; }
    if(DATE_FMT < 4)
      wsprintf(SCR[8].WS,cData,d.year,d.month,d.day);
    else if(DATE_FMT <8)
      wsprintf(SCR[8].WS,cData,d.month,d.day);
    else {
      short inx=-1;
      CutWSTR(SCR[8].WS,0);
      if(DATE_FMT == 8) {
        wsprintf(SCR[8].WS,"%04d",d.year);
        UniToday[++inx] = UniDate[0];
      }
      UniToday[++inx] = d.month/10 + 0x30;
      UniToday[++inx] = d.month%10 + 0x30;
      UniToday[++inx] = UniDate[1];
      UniToday[++inx] = d.day/10 + 0x30;
      UniToday[++inx] = d.day%10 + 0x30;
      UniToday[++inx] = UniDate[2];
      BSTRAdd(SCR[8].WS->wsbody,UniToday, ++inx);     
    }
    FillScreen(&SCR[8],DATE_X,DATE_Y);
  }  
  if(SCR[9].Show){//显示当前时间
    switch(TIME_FMT) {
    case 0: wsprintf(SCR[9].WS,"%02d:%02d",t.hour,t.min); 
      break;      
    case 1:
      if(t.hour <= 12) {
        wsprintf(SCR[9].WS,"AM %02d:%02d",t.hour,t.min);
      } else {
        t.hour = t.hour - 12;
        wsprintf(SCR[9].WS,"PM %02d:%02d",t.hour,t.min);
      } 
      break;      
    case 2:
      if(t.hour > 12) t.hour = t.hour - 12;
      wsprintf(SCR[9].WS,"%02d:%02d",t.hour,t.min);
      break;      
    case 3: 
      wsprintf(SCR[9].WS,"%02d:%02d:%02d",t.hour,t.min,t.sec); 
      break;      
    case 4:
      if(t.hour <= 12){
        wsprintf(SCR[9].WS,"AM %02d:%02d:%02d",t.hour,t.min,t.sec);
      } else {
        t.hour = t.hour - 12;
        wsprintf(SCR[9].WS,"PM %02d:%02d:%02d",t.hour,t.min,t.sec);
      }
      break;
    case 5:
      wsprintf(SCR[9].WS,"%02d",t.hour);
      UniToday[0] = UniTime[0];  
      UniToday[1] = t.min/10 + 0x30;
      UniToday[2] = t.min%10 + 0x30;
      UniToday[3] = UniTime[1];
      BSTRAdd(SCR[9].WS->wsbody,UniToday, 4);
      break;
    case 6:
      wsprintf(SCR[9].WS,"%02d",t.hour);
      UniToday[0] = UniTime[0];   
      UniToday[1] = t.min/10 + 0x30;
      UniToday[2] = t.min%10 + 0x30;
      UniToday[3] = UniTime[1];   
      UniToday[4] = t.sec/10 + 0x30;
      UniToday[5] = t.sec%10 + 0x30;
      UniToday[6] = UniTime[2];
      BSTRAdd(SCR[9].WS->wsbody,UniToday, 7);
      break;
    default: break;      
    }   
    FillScreen(&SCR[9],TIME_X,TIME_Y);
  }  
  if(SCR[10].Show){//显示农历信息
    CutWSTR(SCR[10].WS,0);
    GetDayOf(d,&NLi);
    if((SWYD>=0)&&(SWYD<3)){//显示农历日期 
      memcpy(SCR[10].WS->wsbody,NLi.year->wsbody,16);
    }elif((SWYD>=3)&&(SWYD<6)){//显示农历年份     
      memcpy(SCR[10].WS->wsbody,NLi.mday->wsbody,16); 
    }else{//显示农历节气
      uword lunar;
      if(lunar=LunarHolId(d))
         LunarHolDay(SCR[10].WS,lunar);
      else
         SWYD=9;
    }
    if(SWYD++>=9)SWYD=0;
    FillScreen(&SCR[10],CHSD_X,CHSD_Y);
  }
  if(SCR[11].Show){//显示公历节日
    char nDay[8],nRes[LEN];  
    sprintf(nDay,"N%02d.%02d:",d.month,d.day);
    MidStr(Gala,nDay,nRes);
    wsprintf(SCR[11].WS,PFMT_STR,nRes);
    FillScreen(&SCR[11],NBIR_X,NBIR_Y);
  }
  if(SCR[12].Show){//显示农历节日      
    char oDay[8],oRes[LEN];   
    TDate o=GetOldDay(d);
    sprintf(oDay,"P%02d.%02d:",o.month,o.day);
    MidStr(Gala,oDay,oRes);
    wsprintf(SCR[12].WS,PFMT_STR,oRes);
    FillScreen(&SCR[12],OBIR_X,OBIR_Y);
  }
}

//在屏幕上画主菜单图标位置和文本信息
static void DrawGUI(void){ 
  GBS_StartTimerProc(&tskTimer,10,DrawGUI); 
  int fSize,TextH=0;
  WSHDR *MWS=AllocWS(50);
  void *TskCanvas=BuildCanvas();
  if((SUCC_HOOK)&&(TASK_ENA)&&(TASK_STATE==SCR_TASKS))
  {//开始菜单代码--------文本区域--------
   fSize = FontType(ATEXT_FT);
   if(DEST_ENA){
    TextH = GetFontYSIZE(fSize)+4;//文本高度
    if(TextH < SoftkeyH()) TextH = SoftkeyH(); 
   }
   short top=ScreenH()-TextH-OFFSET-1;//文本顶部位置 
   TRect tRC={0,top,ScreenW()-1,ScreenH()-OFFSET-1};//生成文本绘制区域   
   TRect iRC={0,top-PicSize-1,PicSize-1,top-1};//生成图标绘制区域
   TRect fRc=iRC; 
   int y=0,z=0,i=0,n=ScreenW()/PicSize;  
   int ts=(tRC.b-tRC.t-GetFontYSIZE(fSize))/2;//计算文本垂直偏移  
   n = PicSize +(ScreenW()-n*PicSize)/(n-1);//计算图标显示数
   if(mCount>((ScreenW())/(n))){ i=mSelet-((ScreenW())/(n))+1; if(i<0)i=0;} else i=0;
   //--------绘制图标和文本--
   if(DEST_ENA)DrawRectangle(tRC.l, tRC.t, tRC.r, tRC.b,0, cfgPBDCol, cfgPBGCol);
   while(i<mCount){
    const char *s=APP[i].Pic;
    if(!((s)&&(strlen(s)))) s=AINO;    
    TRect tmp=iRC; tmp.l+=y; tmp.r+=y;  
    DrawCanvas(TskCanvas, tmp.l,tmp.t,tmp.r,tmp.b, 1);
    int picw =(PicSize-GetImgWidth((int)s))/2;  if(picw<0)picw=0;
    int pich =(PicSize-GetImgHeight((int)s))/2; if(pich<0)pich=0; 
    DrawImg(tmp.l+picw,tmp.t+pich,(uint)s);  
    if(i==mSelet){
      if(DEST_ENA){
        wsprintf(MWS,PFMT_STR,APP[i].Name);
        DrawString(MWS,tRC.l+3,tRC.t+ts,tRC.r-3,tRC.b-ts,fSize,1,ATEXT_CS,TRAN_CBK); 
      }
      fRc = tmp;
    }
    y+=n;
    i++;
    if(++z>((ScreenW())/(n))-1) break;
   }  
   DrawRectangle(fRc.l,fRc.t,fRc.r,fRc.b,0,cfgBBDCol,TRAN_CBK);
   //自动关闭菜单
   if((++AUTO_EXIT>=AUTO_CLOSE*TMR_SECOND/5)&&(TASK_ID)) CloseTask();
   //结束菜单
  }
  else if((ALRM_ENA)&&(TASK_STATE==SCR_ALARM))
  {//闹钟界面 
   TRect Alarm={0,YDISP,ScreenW()-1,ScreenH()-1};
   DrawCanvas(TskCanvas, Alarm.l,Alarm.t,Alarm.r,Alarm.b, 1);
   char PIC[64];
   sprintf(PIC,ALRM_PIC,aCur);
   wsprintf(MWS,PFMT_STR,ALRM); 
   fSize=FontType(ALRM_FT);
   TextH=GetFontYSIZE(fSize)+4;
   int wso=(Alarm.r-Alarm.l-PixlsWidth(MWS,fSize))/2;
   int pio=(Alarm.r-Alarm.l-GetImgWidth((int)PIC))/2;
   int pih=GetImgHeight((int)PIC);     
   TRect Altxt={Alarm.l,Alarm.t,Alarm.r,Alarm.t+TextH}; 
   TRect Alpic={Alarm.l+pio,Altxt.b,Alarm.l-pio,Alarm.b+pih};
   DrawRectangle(Alarm.l, Alarm.t, Alarm.r, Alarm.b,0, ALRM_CBK, ALRM_CBK);  
  //标题     
   DrawString(MWS, Altxt.l+wso, Altxt.t+2, Altxt.r-wso, Altxt.b-2,fSize,1,ALRM_CTX, TRAN_CBK); 
  //图标
   DrawImg(Alpic.l,Alpic.t,(uint)PIC);
  //定义
   wsprintf(MWS,PFMT_STR,WeekGB[week]);
   wso=(Alarm.r-Alarm.l-PixlsWidth(MWS,fSize))/2;
   TRect Alwek={Alarm.l+wso,Altxt.b+pih,Alarm.r-wso,Altxt.b+pih+TextH}; 
   DrawString(MWS, Alwek.l, Alwek.t+2,Alwek.r,Alwek.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
  //时间
   wsprintf(MWS,"%02d:%02d:%02d",t.hour,t.min,t.sec); 
   wso=(Alarm.r-Alarm.l-PixlsWidth(MWS,fSize))/2;
   TRect Altim={Alarm.l+wso,Alwek.b,Alarm.r-wso,Alwek.b+TextH}; 
   DrawString(MWS, Altim.l, Altim.t+2,Altim.r,Altim.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
  //显示日期
   wsprintf(MWS,"%04d%t%02d%t%02d%t",d.year,"年",d.month,"月",d.day,"日");
   wso=(Alarm.r-Alarm.l-PixlsWidth(MWS,fSize))/2;
   TRect Aldat={Alarm.l+wso,Altim.b,Alarm.r-wso,Altim.b+TextH}; 
   DrawString(MWS, Aldat.l, Aldat.t+2,Aldat.r,Aldat.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
   //循环图片
   if(aCur%2){
     SetIllumination(0,1,100,0);
     if(ALRV_ENA)SetVibration(ALRM_VIB);
   }else{
     if(ALIU_ENA)
        SetIllumination(0,1,5,0);
     else
        SetIllumination(0,1,100,0);
     if(ALRV_ENA)SetVibration(0);
   }
   if(aCur>=ALRM_COT)aCur=0;
   aCur++;
  }//结束闹钟代码
  FreeWS(MWS);
}
//重画响应事件
static void TaskRedraw(GUI *gui){
     DrawGUI();
}
//创建响应事件
static void TaskCreate(GUI *gui, void *(*malloc_adr)(int)){
  if(TASK_STATE==SCR_TASKS){//任务菜单
    mSelet=0;  
  }elif(TASK_STATE==SCR_ALARM){//任务闹钟    
    OLScr=GetIlluminationDataTable()[3];
    aCur=1; 
  }  
  gui->state=1;
}
//关闭响应事件
static void TaskClose(GUI *gui, void(*mfree_adr)(void *)){
  gui->state=0;
}
//聚焦响应事件
static void TaskFocus(GUI *gui, void *(*malloc_adr)(int), void(*mfree_adr)(void *)){
  gui->state=2;
}
//取消聚焦响应事件
static void TaskUnfus(GUI *gui, void(*mfree_adr)(void *)){
  if(gui->state!=2) return;
  gui->state=1; 
  CloseTask();
}
//定义功能执行操作函数
static void DoIt(int inx);
//主体按键操作功能
static int TaskKeypress(GUI *gui, GUI_MSG *msg){ 
  if(SUCC_HOOK||TASK_ENA){
    DirectRedrawGUI();
    if((msg->gbsmsg->msg==KEY_DOWN)){    
    AUTO_EXIT=0;       
    if(msg->gbsmsg->submess==KeyButton(CALL_BTN)){//关闭菜单 
      CloseTask(); 
      return(1);
    }    
    switch(msg->gbsmsg->submess){//选定操作          
      case  DOWN_BUTTON://下选定右选定      
      case RIGHT_BUTTON:if(++mSelet >=mCount)mSelet=0;break;       
      case    UP_BUTTON://上选定右选定         
      case  LEFT_BUTTON:if(--mSelet<0)mSelet=mCount-1;break;           
      //执行对就的功能
      case ENTER_BUTTON:if(TASK_STATE==SCR_TASKS)DoIt(mSelet); break;
    }  
   }
  }
  return(0);
}
static int TaskMethod8(void){return(0);}
static int TaskMethod9(void){return(0);}
static const void * const TaskMethods[11]={
 (void *)TaskRedraw,	//重画
 (void *)TaskCreate,	//创建
 (void *)TaskClose,	//关闭
 (void *)TaskFocus,	//聚焦
 (void *)TaskUnfus,	//取消聚焦
 (void *)TaskKeypress,	//按键操作
  0,
 (void *)kill_data,
 (void *)TaskMethod8,      //功能未知
 (void *)TaskMethod9,      //功能未知
  0
};

const RECT Canvas={0, 0, 0, 0};

static void TaskOnCreate(CSM_RAM *data){   
  GUI *TaskGui=malloc(sizeof(GUI));
  TASK_GUI *TaskCsm=(TASK_GUI*)data;
  zeromem(TaskGui,sizeof(GUI));
  TaskGui->canvas=(void *)(&Canvas);
  //TaskGui->flag30=2;
  TaskGui->methods=(void *)TaskMethods;
  TaskGui->item_ll.data_mfree=(void(*)(void *))mfree_adr();
  TaskCsm->CSM.state=0;
  TaskCsm->CSM.unk1 =0;
  if(TASK_STATE==SCR_MENUS)
     TaskCsm->TaskID=BrowserFileMenu();
  else
     TaskCsm->TaskID=CreateGUI(TaskGui); 
}

static void TaskKiller(void){
#ifndef DAEMON
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void(*)(void *))mfree_adr());
#endif
}
static void TaskOnClose(CSM_RAM *csm){  
  SUBPROC((void *)TaskKiller); 
}

static int TaskOnMessage(CSM_RAM *data, GBS_MSG *msg){
  TASK_GUI *TaskCsm=(TASK_GUI*)data;
  if((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==TaskCsm->TaskID)){
    TaskCsm->CSM.state=-3;
  }  
  return(1);
}

static uword TaskBody[LEN];

static const struct{
  CSM_DESC CSM;
  WSHDR NAME;
}TASK_CSM={{
  TaskOnMessage,
  TaskOnCreate,
#ifdef NEWSGOLD
  0,0,0,0,
#endif
  TaskOnClose,
  sizeof(TASK_GUI),
  1,
  &MINUSLL},{
  TaskBody,
  NAMECSM_MAGIC1,
  NAMECSM_MAGIC2,
  0x0,
  139}
};
//创建GUI界面
static void BuildGUI(short MODE,char *NAME){  
  LockSched();
  TASK_STATE=MODE;
  static char DUMMY[sizeof(TASK_GUI)];
  wsprintf((WSHDR *)(&TASK_CSM.NAME),PFMT_STR,NAME);
  TASK_ID=CreateCSM(&TASK_CSM.CSM,DUMMY,0);  
  UnlockSched();
}
//执行指定目录
static void RunDIR(char *dir,char *name){  
  strcpy(PATHS,dir);  
  strcpy(TITLE,name);
  BuildGUI(SCR_MENUS,name);
}
//执行菜单功能
static void DoIt(int i){ 
  CloseTask();
  switch(APP[i].Type){
   case -4: OpenBCFGFile(); break;
   case -3: KbdLock();break;
   case -2: RebootPhone();break;
   case -1: SwitchPhoneOff(); break;
   case  0: RunAPP(APP[i].File); break;
   case  1: RunCUT(APP[i].File); break;
   case  2: RunADR(APP[i].File); break;
   case  3: RunDIR(APP[i].File,APP[i].Name); break;
  }     
}
//按键挂钩,内存运行
static int DaemonKeyHook(int key, int m){  
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&(m==MODE_KBD+0x193)){ 
    if(IsUnlocked()&&(key==KeyButton(CALL_BTN))){
       BuildGUI(SCR_TASKS,TASK); 
       return(0);
    }    
  }
  return 0;
}
static void InitMenu(void){
 mCount=4;    
 for(int inx=0;inx<MAX_APP;inx++){ 
  switch(inx){  
  case  0: APP_TRAF((char*)ANTO,inx,   -1,(char*)AITO,         ""); break;//关机
  case  1: APP_TRAF((char*)ANRT,inx,   -2,(char*)AIRT,         ""); break;//重启
  case  2: APP_TRAF((char*)ANLK,inx,   -3,(char*)AILK,         ""); break;//锁键
  case  3: APP_TRAF((char*)ANST,inx,   -4,(char*)AIST,         ""); break;//设置 
  case  4: APP_TRAF((char*)AN04,inx, AT04,(char*)AI04,(char*)AF04); break;//配置
  case  5: APP_TRAF((char*)AN05,inx, AT05,(char*)AI05,(char*)AF05); break;
  case  6: APP_TRAF((char*)AN06,inx, AT06,(char*)AI06,(char*)AF06); break;
  case  7: APP_TRAF((char*)AN07,inx, AT07,(char*)AI07,(char*)AF07); break;
  case  8: APP_TRAF((char*)AN08,inx, AT08,(char*)AI08,(char*)AF08); break;
  case  9: APP_TRAF((char*)AN09,inx, AT09,(char*)AI09,(char*)AF09); break;
  case 10: APP_TRAF((char*)AN10,inx, AT10,(char*)AI10,(char*)AF10); break;
  case 11: APP_TRAF((char*)AN11,inx, AT11,(char*)AI11,(char*)AF11); break;
  case 12: APP_TRAF((char*)AN12,inx, AT12,(char*)AI12,(char*)AF12); break;
  case 13: APP_TRAF((char*)AN13,inx, AT13,(char*)AI13,(char*)AF13); break;
  }   
 }
}
//搜索自定义闹钟操作
static int ExcuteRing(const char *sub,int Week){ 
  char TEMP[LEN];
  if(MidStr(Gala,sub,TEMP)){
    if(strlen(TEMP)>=7){
     if(TEMP[Week]=='1'){
      KbdUnlock();
      BuildGUI(SCR_ALARM,ALRM);
      return(PlayMusic(ALRM_FILE, ALRM_VOL,ALRM_NUM));
     }
    }
  }
  return(0);
}
//挂勾系统时间刷新操作
static void TimerProc(void){
  InitScreen();//自定义功能显示  
  GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&SCR_IPC);  
}
static int DaemonOnMessage(CSM_RAM* data,GBS_MSG* msg){  
  //获取系统时间和日期,星期
  GetDateTime(&d,&t);
  week = GetWeek(&d);  
  // 更新配置
  if(msg->msg == MSG_RECONFIGURE_REQ){
    extern const char *successed_config_filename;
    if(strcmp_nocase(successed_config_filename,(char *)msg->data0)==0){                
      InitConfig();
      //重新加载节日文件数据
      if(FreeFileBuf(Gala)) Gala=LoadFileBuf(BIRS_FILE); 
      InitMenu();
      InitShow();
      ShowMSG(1,(int)"参数已更新!");  
    }
  }   
  //调用旧的消息事件
  int Result=OICSMOnMessage(data,msg);
  //自动关机 
   if((SHUT_ENA)&&(SHUT_TIME.hour==t.hour)&&(SHUT_TIME.min==t.min)&&(t.sec<3)){
     SwitchPhoneOff();//自动关机后,会不能释放内存
     return(Result);
   }
  //自动重启
   if((ROOT_ENA)&&(ROOT_TIME.hour==t.hour)&&(ROOT_TIME.min==t.min)&&(t.sec<3)){
     RebootPhone();
     return(Result);
   }
  //自定义手机启动管理
  if((TASK_ENA)&&(!SUCC_HOOK)){      
      AddKeybMsgHook((void *)DaemonKeyHook);
      SUCC_HOOK = 1;
  }elif((!TASK_ENA)&&(SUCC_HOOK)){
     if(TASK_ID) CloseCSM(TASK_ID); 
     RemoveKeybMsgHook((void *)DaemonKeyHook);  
     SUCC_HOOK = 0;
  }
  if(msg->msg==MSG_IPC){
    IPC_REQ *IPC;
    if(IPC=(IPC_REQ*)msg->data0){
      if(strcmp_nocase(IPC->name_to,SCR_NAME)==0){
        switch(msg->submess){
        case UPDATE_STAT:
          #ifdef NEWSGOLD
          if(!getCpuUsedTime_if_ena()){StartCpuUsageCount();}
          #endif
          GBS_StartTimerProc(&scrTimer, REFRESH*TMR_SECOND/10, TimerProc);
        }
      }
    }
  }     
  //屏显功能  
  static short ScrShow=0;
  switch(INFO_ENA){
   case 0: ScrShow = !IsUnlocked();  break;
   case 1: ScrShow =  IsUnlocked();  break;
   case 2: ScrShow = 1;  break;
   default:ScrShow = 0;  break;
  }      
  CSM_RAM *icsm;
  if(icsm=FindCSMbyID(CSM_root()->idle_id)){
    if(IsGuiOnTop(idlegui_id(icsm))&&ScrShow){
      GUI *igui=GetTopGUI();
      if(igui){      
       //InitScreen();//自定义功能显示
       #ifdef ELKA
        {void *ScrCanvas = BuildCanvas();
       #else
        void *idata  = GetDataOfItemByID(igui,2);
        if(idata)
        {void *ScrCanvas =((void **)idata)[DISPLACE_OF_IDLECANVAS/4];         
       #endif       
        for(int i=0; i<(sizeof(SCR)/sizeof(TSCR)); i++){
        if(SCR[i].Show){
          DrawCanvas(ScrCanvas,SCR[i].L,SCR[i].T,SCR[i].R,SCR[i].B,1);
          DrawString(SCR[i].WS,SCR[i].L,SCR[i].T,SCR[i].R,SCR[i].B,SCR[i].Size,32,SCR[i].PEN,SCR[i].BUH);
         }          
        }
       }  
      }
    }
  }
  //获取日期信息    
  if((ALRM_ENA)&&(!RING_ID)&&(!IsCalling())&&(t.sec<3)){//闹钟
    char cTime[12];
    sprintf(cTime,"R%02d:%02d.",t.hour,t.min);
    RING_ID=ExcuteRing(cTime,week);
  }    
  if((msg->msg==MSG_PLAYFILE_REPORT)&&(ALRM_ENA)&&(RING_ID)){//停止铃声
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if(pmsg->handler==RING_ID){
      if(pmsg->cmd==M_SAE_PLAYBACK_ERROR || pmsg->cmd==M_SAE_PLAYBACK_DONE){ 
       KbdLock();
       CloseTask();
      }
    }  
  }  
  return(Result);
}  

static void DaemonInit(void){
  for(int i=0;i<MAX_SCR; i++) SCR[i].WS=AllocWS(50);
  Gala=LoadFileBuf(BIRS_FILE);
  NLi.year=AllocWS(50);
  NLi.mday=AllocWS(50);
  InitMenu();
  InitShow();
  GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&SCR_IPC);
}

static void Destructor(void){  
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
static void DaemonOnClose(CSM_RAM *data){ 
  if(SUCC_HOOK) RemoveKeybMsgHook((void *)DaemonKeyHook);
  if(IsTimerProc(&scrTimer))GBS_DelTimer(&scrTimer);
  for(int i=0;i!=MAX_SCR; i++) FreeWS(SCR[i].WS);
  FreeFileBuf(Gala);
  FreeWS(NLi.year);
  FreeWS(NLi.mday);
  SUBPROC((void *)Destructor);  
}

int main(){
  InitConfig();  
  LockSched();    
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  OICSMOnClose   = icsmd.onClose;
  OICSMOnMessage = icsmd.onMessage;
  icsmd.onClose  = DaemonOnClose;
  icsmd.onMessage= DaemonOnMessage;
  icsm->constr   = &icsmd;
  DaemonInit();
  if(TASK_ENA){      
     AddKeybMsgHook((void *)DaemonKeyHook);   
     SUCC_HOOK = 1;
  }
  UnlockSched();
  return 0;
}
