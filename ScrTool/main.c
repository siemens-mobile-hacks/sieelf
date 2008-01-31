#include <swilib.h>
#include <cfg_items.h>
#include <sieapi.h>
#include <playsound.h>
#include "scrtool.h"
#include "conf_loader.h"
//注释这里编译成完全后台运行版本
static char ANST[]="软件配置";//配置
static char ANTO[]="关机-玫瑰v2.13";//关机
static char ANRT[]="重启手机";//重启
static char ANLK[]="锁住键盘";//锁键
static char TASK[]="任务菜单";//任务菜单
static char ALRM[]="极酷闹钟";//闹钟界面
const char _percent_t[]="%t";
const  IPC_REQ my_ipc={SCRTOOL_NAME, SCRTOOL_NAME, NULL};
const  int  minus11=-11;
static int  TASK_ID   = 0;//记录图形界面
static int  RING_ID   = 0;//记录闹钟响铃
static int  DMON_ID   = 0;//记录内存运行
static char TASK_STATE;//记录运行界面类型,1为菜单,2为快捷菜单,3为闹钟界面
static ubyte AUTO_EXIT = 0;//记录自动退出菜单状态
static ubyte AUTO_SHUT = 0;//记录自动关机状态
static ubyte SUCC_HOOK = 0;//记录HOOK状态
static int TaskCount,TaskSeled,Alrmvpw,Alrminx;
//定义数据缓存
static char *FestaData;
static void *TaskCanvas;
static WSHDR *AlrmWS;
//配置菜单
static char  PATHS[64];
static char  TITLE[32];
static TSCR  IDS[MAX_IDS];
static TAPP  APP[MAX_APP];
static TLunar NongLi;
static GBSTMR barTimer,csmTimer;
static short OLScr;//屏幕亮灯原值
HEADER_DESC MENU_HDR={0,0,0,0,NULL,(int)TITLE,LGP_NULL};
static void BuildGUI(short mode,char *name);
//关闭有的菜单
static void CloseTask(void){
  if(IsTimerProc(&barTimer)){GBS_DelTimer(&barTimer);}  
  if(TASK_STATE==SCR_ALARM){
   if(RING_ID)PlayMelody_StopPlayback(RING_ID);      
   SetIllumination(0,1,OLScr,0);     
   SetVibration(0);
   RING_ID=0;
  }  
  if(TASK_ID)CloseCSM(TASK_ID); 
  TaskCanvas=NULL;
  AUTO_EXIT=0;  
  TASK_ID=0; 
  DoIDLE();
}
//菜单按键操作
static int  MENU_ONKEY(void *gui, GUI_MSG *msg);
//菜单HOOK操作命令
static void MENU_HOOK(void *gui, int cmd){
  TFile *FileList=MenuGetUserPointer(gui);
  if (cmd==3){ 
    FreeFile(FileList);
  }  
}
//菜单重画列表
static void MENU_DRAW(void *gui, int cur_item, void *user_pointer){
  WSHDR *ws;
  TFile *FileList=user_pointer;
  for (int n=0; n!=cur_item; n++) FileList=FileList->next;
  void *item=AllocMenuItem(gui);
  if (FileList){
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
  if (msg->keys==0x3D || msg->keys==0x18){
    int i=GetCurMenuItem(gui);
    SetMenuItemIcon(gui,i,0);
    for (int n=0; n!=i; n++) sbtop=sbtop->next;
    if (sbtop){      
      CloseTask();
      RunAPP(sbtop->path);
      return (1);
    }
  }
  if((msg->keys==0x01 || msg->keys==RED_BUTTON)&&(TASK_ID)) CloseTask();  
  return (0);
}
//搜索配置文件
static TFile *FindBCFGFile(){
  uint err;
  DIR_ENTRY de;
  int  len;
  TFile *filelist=0;
  char str[128];
  strcpy(str,PATHS);
  if (isdir(PATHS,&err))strcat(str,"*");
  if (FindFirstFile(&de,str,&err)){
    do{
      if (!(de.file_attr&FA_DIRECTORY)){
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
        if (filelist){
          TFile *sbr, *sbt;
          sbr=(TFile *)&filelist;
          sbt=filelist;
          while(strcmp_nocase(sbt->file,sb->file)<0){
            sbr=sbt;
            sbt=sbt->next;
            if (!sbt) break;
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
static void InitData(void);
//挂勾系统时间刷新操作
static void TimerProc(void)
{
  InitData();  
  GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&my_ipc);  
}
#pragma inline  
static int wsprintf_bytes(WSHDR *ws, uint bytes)
{
  if (bytes<=1024)
    return (wsprintf(ws,BYTES_FMT,bytes,BYTES_SG));
  else{
    bytes>>=10;
    return (wsprintf(ws,BYTES_FMT,bytes,KBYTES_SG));
  }  
}
//显示内容配色和位置显示等
static void FillScreen(TSCR *SCR,int style,int x,int y, int Size,const char *Pen,const char *Brush)
{  
  int width =PixlsWidth(SCR->ws,Size);  
  int center=(ScreenW()-width-1)/2;
  int right =ScreenW()-width-1;
  switch(style){
    case 1:SCR->l=0;       SCR->r=width;break;
    case 2:SCR->l=center;  SCR->r=center+width;break;
    case 3:SCR->l=right;   SCR->r=right+width;break;
   default:SCR->l=x;       SCR->r=x+width;break;
  }
  SCR->t=y;
  SCR->b=y+GetFontYSIZE(Size);
  SCR->Size=Size;
  memcpy(SCR->Pen,Pen,4);
  memcpy(SCR->Brush,Brush,4);
}
//搜索自定义节日操作
static int FindBirName(WSHDR *ws,const char *sub){  
  char TEMP[LEN];
  SearchSub(FestaData,sub,TEMP);
  utf8_2ws(ws,TEMP,strlen(TEMP));
  return(wstrlen(ws));
}
//搜索自定义闹钟操作
static void ExcuteRing(const char *sub,int Week){ 
  char TEMP[LEN];
  SearchSub(FestaData,sub,TEMP);
  if(strlen(TEMP)>=7){
    if(TEMP[Week]=='1'){
      BuildGUI(SCR_ALARM,ALRM);
      RING_ID=PlayMusic(ALRM_FILE, ALRM_VOLUME,ALRM_NUM);
      if(VIB_ENA){
          Alrmvpw=ALRM_VIB;
          SetVibration(ALRM_VIB);
      }
   }
  }
}
//菜单功能
static void APP_TRAF(char *name, int inx, int type,char *pic,char *file)
{
  APP[inx].Type = type;
  APP[inx].Pic  = pic;
  APP[inx].File = file;
  APP[inx].Name = name;
  if(type>=0)
     utf8_2ws(APP[inx].ws,name,strlen(name));  
  else
     gb2ws(APP[inx].ws,name,strlen(name));
  if((file)&&(strlen(file)))TaskCount+=1;
}
//初始化程序执行信息
static void CreateAppInfo(int inx)
{ 
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
//对所有显示数据进行补始化
static void InitData(void)
{
  IDS[0].Show=TEMP_ENA;
  if(IDS[0].Show){//显示温度信息 
    int c=GetAkku(1,3)-0xAAA+15;
    wsprintf(IDS[0].ws,TEMP_FMT,c/10,c%10);
    FillScreen(&IDS[0],TEMP_XT,TEMP_X,TEMP_Y,FontType(TEMP_FONT),TEMP_CS,TEMP_CB);
  }          
  IDS[1].Show=VOLT_ENA;
  if(IDS[1].Show){//显示电压信息
    int c=GetAkku(0,9);
    wsprintf(IDS[1].ws,VOLT_FMT,c/1000,(c%1000)/10);
    FillScreen(&IDS[1],VOLT_XT,VOLT_X,VOLT_Y,FontType(VOLT_FONT),VOLT_CS,VOLT_CB);
  }
  IDS[2].Show=RAM_ENA;
  if(IDS[2].Show){//显示剩余信息    
    int c=GetFreeRamAvail();
    wsprintf_bytes(IDS[2].ws,c);
    FillScreen(&IDS[2],RAM_XT,RAM_X,RAM_Y,FontType(RAM_FONT),RAM_CS,RAM_CB);  
  }
  IDS[3].Show=TEXT_ENA;     
  if(IDS[3].Show){//显示定义信息
    utf8_2ws(IDS[3].ws,TEXT_FMT,strlen(TEXT_FMT));
    FillScreen(&IDS[3],TEXT_XT,TEXT_X,TEXT_Y,FontType(TEXT_FONT),TEXT_CS,TEXT_CB);
  }
  IDS[4].Show=NET_ENA;            
  if(IDS[4].Show){//显示网络信息
    RAMNET *net_data=RamNet();
    int c=(net_data->ch_number>=255)?'=':'-';
    wsprintf(IDS[4].ws,NET_FMT,c,net_data->power);
    FillScreen(&IDS[4],NET_XT,NET_X,NET_Y,FontType(NET_FONT),NET_CS,NET_CB);
  }
  IDS[5].Show=ACCU_ENA;      
  if(IDS[5].Show){//显示CAP信息
    int c=*RamCap();
    wsprintf(IDS[5].ws,ACCU_FMT,c);
    FillScreen(&IDS[5],ACCU_XT,ACCU_X,ACCU_Y,FontType(ACCU_FONT),ACCU_CS,ACCU_CB);
  }
  IDS[6].Show=CPU_ENA;       
  if(IDS[6].Show){//显示CPU使用率
    int c=GetCPULoad();
    if(c==100) c=99;
    wsprintf(IDS[6].ws,CPU_FMT,c);
    FillScreen(&IDS[6],CPU_XT,CPU_X,CPU_Y,FontType(CPU_FONT),CPU_CS,CPU_CB);
  } 
  IDS[7].Show=GPRS_ENA;        
  if(IDS[7].Show){//显示GPRS流量
    //RefreshGPRSTraffic();
    int c=*GetGPRSTrafficPointer();
    wsprintf_bytes(IDS[7].ws,c);
    FillScreen(&IDS[7],GPRS_XT,GPRS_X,GPRS_Y,FontType(GPRS_FONT),GPRS_CS,GPRS_CB);
  }
  //定义时间信息
  TTime time; TDate date; GetDateTime(&date,&time);
  uword UniToday[8];  
  int Week = GetWeek(&date);  
  IDS[8].Show=WEEK_ENA;
  if(IDS[8].Show){//显示当前星期    
    if(WEEK_FMT <4){
      char cWeek[16];
      for(ubyte i=0;i<16;i++){cWeek[i]=cWeekName[WEEK_FMT][Week][i];}
      wsprintf(IDS[8].ws,cWeek,Week);
    }else{
      CutWSTR(IDS[8].ws,0);
      UniToday[0] = UniNum[Week];
      if(WEEK_FMT==4)BSTRAdd(IDS[8].ws->wsbody, XINGQI, 2);
      BSTRAdd(IDS[8].ws->wsbody,UniToday, 1);      
    }
    FillScreen(&IDS[8],WEEK_XT,WEEK_X,WEEK_Y,FontType(WEEK_FONT),WEEK_CS,WEEK_CB);
  }
  IDS[9].Show=DATE_ENA;   
  if(IDS[9].Show){//显示当前日期
    char cData[16]; 
    for(ubyte i=0;i<16;i++){cData[i]=cDataFmt[DATE_FMT][i]; }
    if(DATE_FMT < 4)
      wsprintf(IDS[9].ws,cData,date.year,date.month,date.day);
    else if(DATE_FMT <8)
      wsprintf(IDS[9].ws,cData,date.month,date.day);
    else {
      CutWSTR(IDS[9].ws,0);
      short inx=-1;
      if(DATE_FMT == 8) {
        wsprintf(IDS[9].ws,"%04d",date.year);
        UniToday[++inx] = UniDate[0];
      }      
      UniToday[++inx] = date.month/10 + 0x30;
      UniToday[++inx] = date.month%10 + 0x30;
      UniToday[++inx] = UniDate[1];
      UniToday[++inx] = date.day/10 + 0x30;
      UniToday[++inx] = date.day%10 + 0x30;
      UniToday[++inx] = UniDate[2];
      BSTRAdd(IDS[9].ws->wsbody,UniToday, ++inx);      
    }
    FillScreen(&IDS[9],DATE_XT,DATE_X,DATE_Y,FontType(DATE_FONT),DATE_CS,DATE_CB);
  }  
  IDS[10].Show=TIME_ENA;
  if(IDS[10].Show){//显示当前时间
    switch(TIME_FMT) {
    case 0: wsprintf(IDS[10].ws,"%02d:%02d",time.hour,time.min); 
      break;      
    case 1:
      if(time.hour <= 12) {
        wsprintf(IDS[10].ws,"AM %02d:%02d",time.hour,time.min);
      } else {
        time.hour = time.hour - 12;
        wsprintf(IDS[10].ws,"PM %02d:%02d",time.hour,time.min);
      } 
      break;      
    case 2:
      if(time.hour > 12) time.hour = time.hour - 12;
      wsprintf(IDS[10].ws,"%02d:%02d",time.hour,time.min);
      break;      
    case 3: 
      wsprintf(IDS[10].ws,"%02d:%02d:%02d",time.hour,time.min,time.sec); 
      break;      
    case 4:
      if(time.hour <= 12){
        wsprintf(IDS[10].ws,"AM %02d:%02d:%02d",time.hour,time.min,time.sec);
      } else {
        time.hour = time.hour - 12;
        wsprintf(IDS[10].ws,"PM %02d:%02d:%02d",time.hour,time.min,time.sec);
      }
      break;
    case 5:
      wsprintf(IDS[10].ws,"%02d",time.hour);
      UniToday[0] = UniTime[0];  
      UniToday[1] = time.min/10 + 0x30;
      UniToday[2] = time.min%10 + 0x30;
      UniToday[3] = UniTime[1];
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 4);
      break;
    case 6:
      wsprintf(IDS[10].ws,"%02d",time.hour);
      UniToday[0] = UniTime[0];   
      UniToday[1] = time.min/10 + 0x30;
      UniToday[2] = time.min%10 + 0x30;
      UniToday[3] = UniTime[1];   
      UniToday[4] = time.sec/10 + 0x30;
      UniToday[5] = time.sec%10 + 0x30;
      UniToday[6] = UniTime[2];
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 7);
      break;
    default: break;      
    }   
    FillScreen(&IDS[10],TIME_XT,TIME_X,TIME_Y,FontType(TIME_FONT),TIME_CS,TIME_CB);
  }  
  IDS[11].Show=CYEAR_ENA;
  if(IDS[11].Show){//显示农历年份
    CutWSTR(IDS[11].ws,0);
    GetDayOf(date,&NongLi);
    memcpy(IDS[11].ws->wsbody,NongLi.year->wsbody,16);
    FillScreen(&IDS[11],CYEAR_XT,CYEAR_X,CYEAR_Y,FontType(CYEAR_FONT),CYEAR_CS,CYEAR_CB);
  } 
  IDS[12].Show=CDATE_ENA;
  if(IDS[12].Show){//显示农历日期
    CutWSTR(IDS[12].ws,0);
    uword lunar = LunarHolId(date);
    if(lunar)
      LunarHolDay(IDS[12].ws,lunar);
    else{
      GetDayOf(date,&NongLi);
      memcpy(IDS[12].ws->wsbody,NongLi.mday->wsbody,16);
    }
    FillScreen(&IDS[12],CDATE_XT,CDATE_X,CDATE_Y,FontType(CDATE_FONT),CDATE_CS,CDATE_CB);
  }  
  IDS[13].Show=NBIR_ENA; 
  if(IDS[13].Show){//显示公历节日
    char nDay[8];       
    CutWSTR(IDS[13].ws,0);
    sprintf(nDay,"N%02d.%02d:",date.month,date.day);
    IDS[13].Show = FindBirName(IDS[13].ws,nDay);
    FillScreen(&IDS[13],NBIR_XT,NBIR_X,NBIR_Y,FontType(NBIR_FONT),NBIR_CS,NBIR_CB);
  }   
  IDS[14].Show=OBIR_ENA;  
  if(IDS[14].Show){//显示农历节日      
    char oDay[8];   
    TDate o=GetOldDay(date);
    CutWSTR(IDS[14].ws,0);
    sprintf(oDay,"P%02d.%02d:",o.month,o.day);
    IDS[14].Show = FindBirName(IDS[14].ws,oDay);
    FillScreen(&IDS[14],OBIR_XT,OBIR_X,OBIR_Y,FontType(OBIR_FONT),OBIR_CS,OBIR_CB);
  }
  //闹钟
  if((ALRM_ENA)&&(!RING_ID)&&(!IsCalling())){
    char cTime[12];
    sprintf(cTime,"R%02d:%02d:%02d.",time.hour,time.min,time.sec);
    ExcuteRing(cTime,Week);
  }
  //自动关机
  AUTO_SHUT=(DMON_ID)&&(SHUT_ENA)&&(SHUT_TIME.hour==time.hour)&&(SHUT_TIME.min==time.min);
}

static int size=32;
//在屏幕上画主菜单图标位置和文本信息
static void DrawPanel(void)
{ 
  GBS_StartTimerProc(&barTimer,5,DrawPanel); 
  if(TaskCanvas!=NULL){
   //--------文本区域--------
   int TextH = GetFontYSIZE(ATEXT_FONT)+4;//文本高度
   if (TextH < SoftkeyH()) TextH = SoftkeyH();   
   short top=ScreenH()-TextH-OFFSET-1;//文本顶部位置 
   TRect tRC={0,top,ScreenW()-1,ScreenH()-OFFSET-1};//生成文本绘制区域
   TRect iRC={0,top-size-1,size,top-1};//生成图标绘制区域
   int y=0,z=0,i=0,n=ScreenW()/size;  
   int ts=(tRC.b-tRC.t-GetFontYSIZE(ATEXT_FONT))/2;//计算文本垂直偏移  
   n = size + (ScreenW()-n*size)/(n-1);//计算图标显示数
   if(TaskCount>((ScreenW())/(n))){ i=TaskSeled-((ScreenW())/(n))+1; if(i<0)i=0;} else i=0;
   //--------绘制图标和文本--
   if(DEST_ENA)DrawRectangle(tRC.l, tRC.t, tRC.r, tRC.b,0, cfgPBDCol, cfgPBGCol);
   while(i<TaskCount){
    const char *s=APP[i].Pic;
    if(!((s)&&(strlen(s)))) s=AINO;    
    TRect tmp=iRC; tmp.l+=y; tmp.r+=y;  
    DrawCanvas(TaskCanvas, tmp.l,tmp.t,tmp.r,tmp.b, 0);
    int picw = (size-GetImgWidth((int)s))/2;  if(picw<0)picw=0;
    int pich = (size-GetImgHeight((int)s))/2; if(pich<0)pich=0; 
    DrawImg(tmp.l+picw,tmp.t+pich,(int)s);  
    if(i==TaskSeled){
      if(DEST_ENA)DrawString(APP[i].ws, tRC.l+3, tRC.t+ts, tRC.r-3, tRC.b-ts, FontType(ATEXT_FONT), 1,ATEXT_CS, TRAN_CBK);
      DrawRectangle(tmp.l,tmp.t,tmp.r,tmp.b,0,cfgBBDCol,TRAN_CBK);
    }
    y+=n;
    i++;
    if(++z>((ScreenW())/(n))-1) break;
   }   
  }
  //自动关闭菜单
  if((++AUTO_EXIT>=AUTO_CLOSE*TMR_SECOND/5)&&(TASK_ID)) CloseTask();
}
//闹钟界面
static void DrawAlarm(void){  
  utf8_2ws(AlrmWS,ALRM,strlen(ALRM));  
  GBS_StartTimerProc(&barTimer,100,DrawAlarm);  
  char s[64];
  sprintf(s,ALRM_PIC,Alrminx);
  TRect Alarm={0,YDISP,ScreenW()-1,ScreenH()-1};
  int wsh=GetFontYSIZE(ALRM_FONT)+4;
  int wso=(Alarm.r-Alarm.l-PixlsWidth(AlrmWS,ALRM_FONT))/2;
  int pio=(Alarm.r-Alarm.l-GetImgWidth((int)s))/2;
  int pih=GetImgHeight((int)s);    
  TRect Altxt={Alarm.l,Alarm.t,Alarm.r,Alarm.t+wsh}; 
  TRect Alpic={Alarm.l+pio,Altxt.b,Alarm.l-pio,Alarm.b+pih};
  DrawRectangle(Alarm.l, Alarm.t, Alarm.r, Alarm.b,0, ALRM_CBK, ALRM_CBK);  
  //标题  
  DrawString(AlrmWS, Altxt.l+wso, Altxt.t+2, Altxt.r-wso, Altxt.b-2,FontType(ALRM_FONT), 1,ALRM_CTX, TRAN_CBK); 
  //图标
  DrawImg(Alpic.l,Alpic.t,(int)s);
  //定义
  TTime time; 
  TDate date;
  uword UniToday[8]; 
  GetDateTime(&date,&time);   //星期
  CutWSTR(AlrmWS,0);
  UniToday[0]=XINGQI[0];
  UniToday[1]=XINGQI[1];
  UniToday[2]=UniNum[GetWeek(&date)];  
  //BSTRAdd(AlrmWS->wsbody,XINGQI, 2);
  BSTRAdd(AlrmWS->wsbody,UniToday, 3); 
  wso=(Alarm.r-Alarm.l-PixlsWidth(AlrmWS,ALRM_FONT))/2;
  TRect Alwek={Alarm.l+wso,Altxt.b+pih,Alarm.r-wso,Altxt.b+pih+wsh}; 
  DrawString(AlrmWS, Alwek.l, Alwek.t+2,Alwek.r,Alwek.b-2,FontType(ALRM_FONT), 1,ALRM_CTX, TRAN_CBK);
  //时间
  wsprintf(AlrmWS,"%02d:%02d:%02d",time.hour,time.min,time.sec); 
  wso=(Alarm.r-Alarm.l-PixlsWidth(AlrmWS,ALRM_FONT))/2;
  TRect Altim={Alarm.l+wso,Alwek.b,Alarm.r-wso,Alwek.b+wsh}; 
  DrawString(AlrmWS, Altim.l, Altim.t+2,Altim.r,Altim.b-2,FontType(ALRM_FONT), 1,ALRM_CTX, TRAN_CBK);
  //显示日期
  CutWSTR(AlrmWS,0);
  wsprintf(AlrmWS,"%04d",date.year);
  UniToday[0] = UniDate[0];
  UniToday[1] = date.month/10 + 0x30;
  UniToday[2] = date.month%10 + 0x30;
  UniToday[3] = UniDate[1]; 
  UniToday[4] = date.day/10 + 0x30;
  UniToday[5] = date.day%10 + 0x30;
  UniToday[6] = UniDate[2];
  BSTRAdd(AlrmWS->wsbody,UniToday, 7);  
  wso=(Alarm.r-Alarm.l-PixlsWidth(AlrmWS,ALRM_FONT))/2;
  TRect Aldat={Alarm.l+wso,Altim.b,Alarm.r-wso,Altim.b+wsh}; 
  DrawString(AlrmWS, Aldat.l, Aldat.t+2,Aldat.r,Aldat.b-2,FontType(ALRM_FONT), 1,ALRM_CTX, TRAN_CBK);
  //循环图片
  if(Alrminx%2)
     SetIllumination(0,1,100,0);
  else
     SetIllumination(0,1,5,0);
  if(Alrminx>=ALRM_COT)Alrminx=0;
  Alrminx++;
}
//重画响应事件
static void TaskRedraw(GUI *gui){
  if(SUCC_HOOK&&TASK_ENA&&(TASK_STATE==SCR_TASKS))
     DrawPanel();
  else if((ALRM_ENA)&&(TASK_STATE==SCR_ALARM))
     DrawAlarm();
}
//创建响应事件
static void TaskCreate(GUI *gui, void *(*malloc_adr)(int)){
  if(TASK_STATE==SCR_TASKS){
    TaskCanvas=CreateCanvas();
    //全画区域
    TaskSeled=0; TaskCount=4;    
    for(int i=0;i<MAX_APP;i++) CreateAppInfo(i);  
  }
  if(TASK_STATE==SCR_ALARM){
    Alrminx=1;    
    TaskCanvas=CreateCanvas();
    OLScr=GetIlluminationDataTable()[3];
  }
  DisableIDLETMR();
  gui->state=1;
}
//关闭响应事件
static void TaskClose(GUI *gui, void (*mfree_adr)(void *)){
  RestartIDLETMR();
  gui->state=0;
}
//聚焦响应事件
static void TaskFocus(GUI *gui, void *(*malloc_adr)(int), void (*mfree_adr)(void *)){
  gui->state=2;
}
//取消聚焦响应事件
static void TaskUnfocus(GUI *gui, void (*mfree_adr)(void *)){
  if (gui->state!=2) return;
  gui->state=1;  
}
//定义功能执行操作函数
void DoIt(int inx);
//主体按键操作功能
static int TaskKeypress(GUI *gui, GUI_MSG *msg){ 
  if(SUCC_HOOK||TASK_ENA){
    DirectRedrawGUI();
    if ((msg->gbsmsg->msg==KEY_DOWN)){    
    AUTO_EXIT=0;
    uint KeyPress=msg->gbsmsg->submess;    
    //关闭菜单    
    if(KeyPress==EXIT_BTN){CloseTask(); return(1);}
    //选定操作
    switch(KeyPress){          
      case  DOWN_BUTTON://下选定右选定      
      case RIGHT_BUTTON:if(++TaskSeled >=TaskCount)TaskSeled=0;break;       
      case    UP_BUTTON://上选定右选定         
      case  LEFT_BUTTON:if(--TaskSeled<0)TaskSeled=TaskCount-1;break;           
      //执行对就的功能
      case ENTER_BUTTON:if(TASK_STATE==SCR_TASKS)DoIt(TaskSeled); break;
    }  
   }
  }
  return(0);
}
//释放响应事件
#ifdef NEWSGOLD
static void TaskDestroy(GUI *gui, void (*mfree_adr)(void *)){
  kill_data(gui,mfree_adr);
}
#endif
static int TaskMethod8(void){return(0);}
static int TaskMethod9(void){return(0);}
static const void * const task_methods[11]={
  (void *)TaskRedraw,	//重画
  (void *)TaskCreate,	//创建
  (void *)TaskClose,	//关闭
  (void *)TaskFocus,	//聚焦
  (void *)TaskUnfocus,	//取消聚焦
  (void *)TaskKeypress,	//按键操作
  0,
#ifdef NEWSGOLD
  (void *)TaskDestroy,	//释放
#else
  (void *)kill_data, 
#endif
  (void *)TaskMethod8,      //功能未知
  (void *)TaskMethod9,      //功能未知
  0
};

const RECT Canvas={0, 0, 0, 0};

static void task_oncreate(CSM_RAM *data){   
  GUI *task_gui=malloc(sizeof(GUI));
  TASK_GUI *csm=(TASK_GUI*)data;
  zeromem(task_gui,sizeof(GUI));
  task_gui->canvas=(void *)(&Canvas);
  //task_gui->flag30=2;
  task_gui->methods=(void *)task_methods;
  task_gui->item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1 =0;
  if(TASK_STATE==SCR_MENUS)
     csm->TaskID=BrowserFileMenu();
  else
     csm->TaskID=CreateGUI(task_gui); 
}

static void task_killer(void){
#ifndef DAEMON
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
#endif
}
static void task_onclose(CSM_RAM *csm){  
  SUBPROC((void *)task_killer); 
}

static int task_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  TASK_GUI *csm=(TASK_GUI*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->TaskID))
  {
    csm->csm.state=-3;
  }  
  return(1);
}

static uword task_body[LEN];

static const struct{
  CSM_DESC csm;
  WSHDR name;
}GUI_TASK={{
  task_onmessage,
  task_oncreate,
#ifdef NEWSGOLD
  0,0,0,0,
#endif
  task_onclose,
  sizeof(TASK_GUI),
  1,
  &minus11},{
  task_body,
  NAMECSM_MAGIC1,
  NAMECSM_MAGIC2,
  0x0,
  139}
};

static void BuildGUI(short mode,char *name){
  TASK_STATE=mode;
  LockSched();
  static char dummy[sizeof(TASK_GUI)];
  wsprintf((WSHDR *)(&GUI_TASK.name),_percent_t,name);
  TASK_ID=CreateCSM(&GUI_TASK.csm,dummy,2);  
  UnlockSched();
}
static void RunDIR(char *dir,char *NAME){  
  strcpy(PATHS,dir);
  strcpy(TITLE,NAME);
  BuildGUI(SCR_MENUS,NAME);
}
static void DoIt(int inx){ 
  CloseTask();
  switch(APP[inx].Type){
   case -4: OpenBCFGFile(); break;
   case -3: KbdLock();break;
   case -2: RebootPhone();break;
   case -1: SwitchPhoneOff(); break;
   case  0: RunAPP(APP[inx].File); break;
   case  1: RunCUT(APP[inx].File); break;
   case  2: RunADR(APP[inx].File); break;
   case  3: RunDIR(APP[inx].File,APP[inx].Name); break;
  }     
}
//按键挂钩,内存运行
static int daemon_keyhook(int key, int m){  
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&(m==MODE_KBD+0x193)){ 
    if(IsUnlocked()&&(key==CALL_BTN)){BuildGUI(SCR_TASKS,TASK); return(0);}    
  }
  return 0;
}
static int daemon_onmessage(CSM_RAM* data,GBS_MSG* msg){   
  // 更新配置
  if(msg->msg == MSG_RECONFIGURE_REQ){
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0){                
      InitConfig();
      //重新加载节日文件数据
      if(FreeFileBuf(FestaData)) FestaData=LoadFileBuf(BIRS_FILE); 
      ShowMSG(1,(int)"参数已更新!");  
    }
  } 
  //自定义手机启动管理
  if((TASK_ENA)&&(!SUCC_HOOK)){      
      AddKeybMsgHook((void *)daemon_keyhook);
      SUCC_HOOK = 1;
  }elif((!TASK_ENA)&&(SUCC_HOOK)){
     if(TASK_ID) CloseCSM(TASK_ID); 
     RemoveKeybMsgHook((void *)daemon_keyhook);  
     SUCC_HOOK = 0;
  }
  //自定义功能显示 
  InitData();
  if(INFO_ENA){ 
   if (msg->msg==MSG_IPC){
    IPC_REQ *ipc;
    if(ipc=(IPC_REQ*)msg->data0){
      if(strcmp_nocase(ipc->name_to,SCRTOOL_NAME)==0){
        switch (msg->submess){
        case UPDATE_STAT:
          #ifdef NEWSGOLD
          if (!getCpuUsedTime_if_ena()){StartCpuUsageCount();}
          #endif
          GBS_StartTimerProc(&csmTimer, REFRESH*TMR_SECOND/10, TimerProc);
        }
      }
    }
   }  
   void *canvas;   
   if(canvas=CreateCanvas()){       
     for (int inx=0; inx<(sizeof(IDS)/sizeof(TSCR)); inx++){
      if (IDS[inx].Show){
          DrawCanvas(canvas, IDS[inx].l,IDS[inx].t,IDS[inx].r,IDS[inx].b, 1);
          DrawString(IDS[inx].ws,IDS[inx].l,IDS[inx].t,IDS[inx].r,IDS[inx].b,IDS[inx].Size,32,IDS[inx].Pen,IDS[inx].Brush);
      }          
     }
   }  
  }elif(IsTimerProc(&csmTimer)){GBS_DelTimer(&csmTimer);}
  //播放铃声
  if((msg->msg==MSG_PLAYFILE_REPORT)&&(ALRM_ENA)){
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if (pmsg->handler==RING_ID){
      if (pmsg->cmd==M_SAE_PLAYBACK_ERROR || pmsg->cmd==M_SAE_PLAYBACK_DONE){       
       //SetVibration(0);
       CloseTask();
       //RING_ID=0;
      }elif((VIB_ENA)&&(!IsCalling())){
        if(--Alrmvpw>0){
          SetVibration(Alrmvpw);
        }else{
          Alrmvpw=ALRM_VIB;
          SetVibration(ALRM_VIB);
        }
      }
    }  
   }
   //自动关机
   if(AUTO_SHUT){
     CloseCSM(DMON_ID);
     SwitchPhoneOff();
   }
 return(1);
}  

static void daemon_oncreate(CSM_RAM *data){
  for (int i=0;i<MAX_IDS; i++) IDS[i].ws=AllocWS(50);
  for (int i=0;i<MAX_APP; i++) APP[i].ws=AllocWS(50);
  FestaData=LoadFileBuf(BIRS_FILE);
  NongLi.year=AllocWS(50);
  NongLi.mday=AllocWS(50);
  AlrmWS=AllocWS(50);
  if(INFO_ENA) GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&my_ipc);
}
static void daemon_killer(void){  
  extern void *ELF_BEGIN;  
  if(SUCC_HOOK) RemoveKeybMsgHook((void *)daemon_keyhook);  
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
static void daemon_onclose(CSM_RAM *csm){  
  if(IsTimerProc(&csmTimer))GBS_DelTimer(&csmTimer);
  for (int i=0;i!=MAX_IDS; i++) FreeWS(IDS[i].ws);
  for (int i=0;i!=MAX_APP; i++) FreeWS(APP[i].ws);
  FreeFileBuf(FestaData);
  FreeWS(NongLi.year);
  FreeWS(NongLi.mday);
  FreeWS(AlrmWS);
  SUBPROC((void *)daemon_killer);  
}
static uword daemon_body[LEN];
static const struct{
  CSM_DESC csm;
  WSHDR name;
}CSM_DAEMON={{
  daemon_onmessage,
  daemon_oncreate,
#ifdef NEWSGOLD
  0,0,0,0,
#endif
  daemon_onclose,
  sizeof(DAEMON_CSM),
  1,
  &minus11},{
  daemon_body,
  NAMECSM_MAGIC1,
  NAMECSM_MAGIC2,
  0x0,
  139}
};

static void UpdateCSMName(void){ 
  wsprintf((WSHDR *)(&CSM_DAEMON.name),_percent_t,(char *)(strrchr(ANTO,'-')+1));
}

int main()
{
  InitConfig();  
  LockSched();    
  UpdateCSMName();
  char dummy[sizeof(DAEMON_CSM)];    
  CSM_RAM *save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;  
  DMON_ID=CreateCSM(&CSM_DAEMON.csm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  if(TASK_ENA){      
     AddKeybMsgHook((void *)daemon_keyhook);   
     SUCC_HOOK = 1;
  }
  UnlockSched();
  return 0;
}
