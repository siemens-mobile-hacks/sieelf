#include <swilib.h>
#include <cfg_items.h>
#include <sieapi.h>
#include <playsound.h>
#include "scrtool.h"
#include "conf_loader.h"
//-------------
//����
const char ANST[13]="\xE8\xAE\xBE\xE7\xBD\xAE\xE5\x8F\x82\xE6\x95\xB0";
//�ػ�
const char ANTO[18]="\xE5\x85\xB3\xE6\x9C\xBA\x2D\xE7\x8E\xAB\xE7\x91\xB0\x32\x2E\x30\x39";
//����
const char ANRT[13]="\xE9\x87\x8D\xE5\x90\xAF\xE7\xB3\xBB\xE7\xBB\x9F";
//����
const char ANLK[13]="\xE9\x94\x81\xE5\xAE\x9A\xE9\x94\xAE\xE7\x9B\x98";
//------------
const int  minus11=-11;
const char ipc_name[]=SCRTOOL_NAME;
const IPC_REQ my_ipc={ipc_name, ipc_name, NULL};
TSCR    IDS[MAX_IDS];
TAPP    APP[MAX_APP];
TRect   txt,ico;
TNongLi NongLi;
GBSTMR  barTimer;
GBSTMR  txtTimer;
int MAINCSM_ID = 0;//��¼ͼ�ν���״̬
int DirsActive = 0;//�Ƿ񼤻�Ŀ¼�˵�
int SUCCED_HOOK= 0;//��¼HOOK״̬
int MenuActive = 0;//�Ƿ񼤻����˵�
int TextActive = 0;//�Ƿ񼤻���Ļ��Ϣ
int DAEMON_ID  = 0;//��¼�ڴ�����״̬
int auto_close = 0;//��¼�Զ��˳��˵�
int RingHandle = 0;//��¼��������״̬
int PowerState = 0;//��¼�Զ��ػ�״̬
int Count,Seled,RIN_VPW;
//�������ݻ���
char *BirBuf;
//���ò˵�
char path[128];

HEADER_DESC MENU_HDR={0,0,0,0,NULL,(int)path,LGP_NULL};

//�ر��еĲ˵�
void CloseMenu(void);
//�˵���������
int  MENU_ONKEY(void *gui, GUI_MSG *msg);
//�˵�HOOK��������
void MENU_HOOK(void *gui, int cmd)
{
  TFile *FileList=MenuGetUserPointer(gui);
  if (cmd==3)
  { 
    FreeFile(FileList);
  }  
}
//�˵��ػ��б�
void MENU_DRAW(void *gui, int cur_item, void *user_pointer)
{
  WSHDR *ws;
  TFile *FileList=user_pointer;
  for (int n=0; n!=cur_item; n++) FileList=FileList->next;
  void *item=AllocMenuItem(gui);
  if (FileList)
  {
    int len=strlen(FileList->filename);
    ws=AllocMenuWS(gui,len+4);
    if(FileList->type){
       str_2ws(ws,FileList->filename,len);
       wsInsertChar(ws,0x0002,1);
       wsInsertChar(ws,0xE008,1);
    }else{str_2ws(ws,FileList->filename,len);}
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    wsprintf(ws,"%t","Error!");
  }  
  SetMenuItemText(gui, item, ws, cur_item);  
}
//�˵�������ʼ��
int MENU_SOFTKEYS[]={0,1,2};
//�˵��������
SOFTKEY_DESC MENU_PRESS[]=
{
#ifdef ELKA
  {0x0018,0x0000,8104},//�� 8104
  {0x0001,0x0000,7240},//�ر�7240
  {0x003D,0x0000,(int)"+"}
#else
  {0x0018,0x0000,(int)"Open"},//�� 8104
  {0x0001,0x0000,(int)"Close"},//�ر�7240
  {0x003D,0x0000,(int)"+"}
#endif
};

SOFTKEYSTAB MENU_TAB=
{
  MENU_PRESS,0
};
//����˵��ṹ
MENU_DESC MENU_STRUCT=
{
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
//���尴ť��Ӧ�¼�
int MENU_ONKEY(void *gui, GUI_MSG *msg)
{
  TFile *sbtop=MenuGetUserPointer(gui);
  if (msg->keys==0x3D || msg->keys==0x18)
  {
    int i=GetCurMenuItem(gui);
    for (int n=0; n!=i; n++) sbtop=sbtop->next;
    if (sbtop)
    {      
      CloseMenu();
      RunAPP(sbtop->fullname);
      return (1);
    }
  }
  if((msg->keys==0x01 || msg->keys==RED_BUTTON)&&(MAINCSM_ID)) CloseMenu();  
  return (0);
}
//���������ļ�
TFile *FindBCFGFile()
{
  uint err;
  DIR_ENTRY de;
  int  len;
  TFile *filelist=0;
  char str[128];
  strcpy(str,path);
  if (isdir(path,&err))strcat(str,"*");
  if (FindFirstFile(&de,str,&err)){
    do{
      if (!(de.file_attr&FA_DIRECTORY)){
        TFile *sb=malloc(sizeof(TFile));
        //�����ļ�Ŀ¼
        len=strlen(de.folder_name)+strlen(de.file_name)+2+1;
        sb->fullname=malloc(len);        
        strcpy(sb->fullname,de.folder_name);
        strcat(sb->fullname,"\\");
        strcat(sb->fullname,de.file_name);
        //�����ļ�����
        sb->filename=malloc(strlen(de.file_name)+1);        
        strcpy(sb->filename,de.file_name);
        //������չ��
        if(!SHOW_EXT)sb->filename[getstrpos(sb->filename,'.')]=0;
        sb->type=0;
        sb->next=0;
        if (filelist){
          TFile *sbr, *sbt;
          sbr=(TFile *)&filelist;
          sbt=filelist;
          while(strcmp_nocase(sbt->filename,sb->filename)<0){
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
//�������˵�
int BrowserFileMenu()
{ 
if(DirsActive){   
  TFile *sbtop=FindBCFGFile();
  patch_header(&MENU_HDR);
  return CreateMenu(0,0,&MENU_STRUCT,&MENU_HDR,0,FileCount(sbtop),sbtop,0);
 }else return 0;
}
//�������ò˵�
//��ʼ��������ʾ����
void InitData(void);
//�ҹ�ϵͳʱ��ˢ�²���
void TimerProc(void)
{
  InitData();  
  GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&my_ipc);  
}

#pragma inline  
int wsprintf_bytes(WSHDR *ws, uint bytes)
{
  if (bytes<=1024)
    return (wsprintf(ws,BYTES_FMT,bytes,BYTES_SG));
  else{
    bytes>>=10;
    return (wsprintf(ws,BYTES_FMT,bytes,KBYTES_SG));
  }  
}
//��ʾ������ɫ��λ����ʾ��
void FillScreen(TSCR *Info,int x_start,int y_start, int fontSize,const char *Pen,const char *Brush)
{  
  Info->rc.x=x_start;  
  Info->rc.x2=x_start+get_string_width(Info->ws,fontSize)+6;
  Info->rc.y=y_start;
  Info->rc.y2=y_start+GetFontYSIZE(fontSize);
  Info->Size=fontSize;
  memcpy(Info->Pen,Pen,4);
  memcpy(Info->Brush,Brush,4);
}
//�����Զ�����ղ���
int FindBirName(const char *date,WSHDR *ws)
{   
  char *s=strstr(BirBuf,date);
  if(s){  
      int c,i=0;
      char ss[LEN];
      s+=strlen(date);       
      while((c=*s++)!=NULL){if (i<(sizeof(ss)-1)) ss[i++]=c;}
    ss[i]=0;
    utf8_2ws(ws,ss,strlen(ss));
  }
  int state = wstrlen(ws);
  return(state);
}
//�����Զ������Ӳ���
void ExcuteRing(const char *time,int Week)
{   
  char *s=strstr(BirBuf,time);
  if((s)&&(!RingHandle)){  
    int c,i=0;
    char w[LEN];
    s+=strlen(time);       
    while((c=*s++)!=NULL){if (i<(sizeof(w)-1)) w[i++]=c; }
    w[i]=0;   
    if(strlen(w)>=7){
      if(w[Week]>='1'){
       RingHandle=PlayMusic(RIN_FILE, RIN_VOLUME,RIN_NUM);
       if((VIB_ENA)&&(!IsCalling())){
          RIN_VPW=RIN_VIB;
          SetVibration(RIN_VIB);
       }
      }
    }
  }
}
//�Զ��ػ�
int AutoPowerOff(const char *time)
{
  char *s=strstr(AUTOSD_TIME,time);
  if(s) return(1); else return(0);
}
//��������ʾ���ݽ��в�ʼ��
void InitData(void)
{ //��ʼ��ʾ��������
  IDS[ 0].Show=TEMP_ENA;
  IDS[ 1].Show=VOLT_ENA;
  IDS[ 2].Show=RAM_ENA;
  IDS[ 3].Show=TEXT_ENA;
  IDS[ 4].Show=NET_ENA;
  IDS[ 5].Show=CAP_ENA;
  IDS[ 6].Show=CPU_ENA;
  IDS[ 7].Show=GPRS_ENA;
  IDS[ 8].Show=WEEK_ENA;
  IDS[ 9].Show=DATE_ENA;
  IDS[10].Show=TIME_ENA;
  IDS[11].Show=CHSYEAR_ENA;
  IDS[12].Show=CHSDATE_ENA; 
  IDS[13].Show=NBIR_ENA;
  IDS[14].Show=OBIR_ENA;
  //��ʼ��ʾ��������  
  int c;
  char cWeek[16],cData[16];
  const char cWeekName[4][7][12]={
    {"MONDAY","TUESDAY","WEDNESDAY","THUSDAY","FRIDAY","SATURDAY","SUNDAY"},
    {"MON","TUES","WED","THU","FRI","SAT","SUN"},
    {"Monday","Tuesday","Wednesday","Thusday","Friday","Saturday","Sunday"},
    {"Mon","Tues","Wed","Thu","Fri","Sat","Sun"}};
  const word XINGQI[]  = {0x661F, 0x671F, 0}; //����
  const word UniNum[]  = {0x4E00,0x4E8C,0x4E09,0x56DB,0x4E94,0x516D,0x65E5,0};//һ������������
  const word UniDate[] = {0x5E74,0x6708,0x65E5,0};//������
  const word UniTime[] = {0x70B9,0x5206,0x79D2,0x4E0A,0x4E0B,0x5348,0};//�����������  
  char cDataFmt[8][16] = {"%02d/%02d/%02d", "%02d-%02d-%02d", "%02d.%02d.%02d", "%02d %02d %02d", "%02d/%02d", "%02d-%02d", "%02d.%02d", "%02d %02d"};  
  //��ʾ�¶���Ϣ  
  if(IDS[0].Show){
    c=GetAkku(1,3)-0xAAA+15;
    wsprintf(IDS[0].ws,TEMP_FMT,c/10,c%10);
    FillScreen(&IDS[0],TEMP_X,TEMP_Y,FontType(TEMP_FONT),TEMP_COLORS,TEMP_FCOLOR);
  }
  //��ʾ��ѹ��Ϣ  
  if(IDS[1].Show){
    c=GetAkku(0,9);
    wsprintf(IDS[1].ws,VOLT_FMT,c/1000,(c%1000)/10);
    FillScreen(&IDS[1],VOLT_X,VOLT_Y,FontType(VOLT_FONT),VOLT_COLORS,VOLT_FCOLOR);
  }
  //��ʾʣ����Ϣ  
  if(IDS[2].Show){    
    c=GetFreeRamAvail();
    wsprintf_bytes(IDS[2].ws,c);
    FillScreen(&IDS[2],RAM_X,RAM_Y,FontType(RAM_FONT),RAM_COLORS,RAM_FCOLOR);  
  }
  //��ʾ������Ϣ  
  if(IDS[3].Show){
    utf8_2ws(IDS[3].ws,TEXT_FMT,strlen(TEXT_FMT));
    FillScreen(&IDS[3],TEXT_X,TEXT_Y,FontType(TEXT_FONT),TEXT_COLORS,TEXT_FCOLOR);
  } 
  //��ʾ������Ϣ  
  if(IDS[4].Show){
    RAMNET *net_data=RamNet();
    c=(net_data->ch_number>=255)?'=':'-';
    wsprintf(IDS[4].ws,NET_FMT,c,net_data->power);
    FillScreen(&IDS[4],NET_X,NET_Y,FontType(NET_FONT),NET_COLORS,NET_FCOLOR);
  }
  //��ʾCAP��Ϣ  
  if(IDS[5].Show){
    c=*RamCap();
    wsprintf(IDS[5].ws,CAP_FMT,c);
    FillScreen(&IDS[5],ACCU_X,ACCU_Y,FontType(ACCU_FONT),ACCU_COLORS,ACCU_FCOLOR);
  }
  //��ʾCPUʹ����  
  if(IDS[6].Show){
    c=GetCPULoad();
    if(c==100) c=99;
    wsprintf(IDS[6].ws,CPU_FMT,c);
    FillScreen(&IDS[6],CPU_X,CPU_Y,FontType(CPU_FONT),CPU_COLORS,CPU_FCOLOR);
  }
  //��ʾGPRS����  
  if(IDS[7].Show){
    //RefreshGPRSTraffic();
    c=*GetGPRSTrafficPointer();
    wsprintf_bytes(IDS[7].ws,c);
    FillScreen(&IDS[7],GPRS_X,GPRS_Y,FontType(GPRS_FONT),GPRS_COLORS,GPRS_FCOLOR);
  }
  //����ʱ����Ϣ
  TTime time; TDate date; GetDateTime(&date,&time);
  word UniToday[3];
  //��ʾ��ǰ����  
  if(IDS[8].Show){
    c = GetWeek(&date);
    if(WEEK_FMT <4)
    {
      for(int iloop = 0;iloop < 16;iloop++){
        cWeek[iloop] = cWeekName[WEEK_FMT][c][iloop];        
      }
      wsprintf(IDS[8].ws,cWeek,c);
    } else {
      CutWSTR(IDS[8].ws,0);
      UniToday[0] = UniNum[c];
      if(WEEK_FMT==4)
         BSTRAdd(IDS[8].ws->wsbody, XINGQI, 2);
      BSTRAdd(IDS[8].ws->wsbody,UniToday, 1);      
    }
    FillScreen(&IDS[8],WEEK_X,WEEK_Y,FontType(WEEK_FONT),WEEK_COLORS,WEEK_FCOLOR);
  }
  //��ʾ��ǰ����  
  if(IDS[9].Show){
    for(int iloop = 0;iloop < 16;iloop++){ cData[iloop] = cDataFmt[DATE_FMT][iloop]; }
    if(DATE_FMT < 4)
      wsprintf(IDS[9].ws,cData,date.year,date.month,date.day);
    else if(DATE_FMT <8)
      wsprintf(IDS[9].ws,cData,date.month,date.day);
    else {
      CutWSTR(IDS[9].ws,0);
      if(DATE_FMT == 8) {
        wsprintf(IDS[9].ws,"%04d",date.year);
        UniToday[0] = UniDate[0];
        BSTRAdd(IDS[9].ws->wsbody,UniToday, 1);
      }      
      UniToday[0] = date.month/10 + 0x30;
      UniToday[1] = date.month%10 + 0x30;
      BSTRAdd(IDS[9].ws->wsbody,UniToday, 2);
      UniToday[0] = UniDate[1];
      BSTRAdd(IDS[9].ws->wsbody,UniToday, 1);      
      UniToday[0] = date.day/10 + 0x30;
      UniToday[1] = date.day%10 + 0x30;
      BSTRAdd(IDS[9].ws->wsbody,UniToday, 2);
      UniToday[0] = UniDate[2];
      BSTRAdd(IDS[9].ws->wsbody,UniToday, 1);      
    }
    FillScreen(&IDS[9],DATE_X,DATE_Y,FontType(DATE_FONT),DATE_COLORS,DATE_FCOLOR);
  }
  //��ʾ��ǰʱ��  
  if(IDS[10].Show){
    switch(TIME_FMT) {
    case 0: wsprintf(IDS[10].ws,"%02d:%02d",time.hour,time.min); break;
      
    case 1:
      if(time.hour <= 12) {
        wsprintf(IDS[10].ws,"AM %02d:%02d",time.hour,time.min);
      } else {
        time.hour = time.hour - 12;
        wsprintf(IDS[10].ws,"PM %02d:%02d",time.hour,time.min);
      } break;
      
    case 2:
      if(time.hour > 12) time.hour = time.hour - 12;
      wsprintf(IDS[10].ws,"%02d:%02d",time.hour,time.min);
      break;
      
    case 3: wsprintf(IDS[10].ws,"%02d:%02d:%02d",time.hour,time.min,time.sec); break;
      
    case 4:
      if(time.hour <= 12){
        wsprintf(IDS[10].ws,"AM %02d:%02d:%02d",time.hour,time.min,time.sec);
      } else {
        time.hour = time.hour - 12;
        wsprintf(IDS[10].ws,"PM %02d:%02d:%02d",time.hour,time.min,time.sec);
      } break;
    case 5:
      wsprintf(IDS[10].ws,"%02d",time.hour);
      UniToday[0] = UniTime[0];
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 1);      
      UniToday[0] = time.min/10 + 0x30;
      UniToday[1] = time.min%10 + 0x30;
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 2);
      UniToday[0] = UniTime[1];
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 1);
      break;
    case 6:
      wsprintf(IDS[10].ws,"%02d",time.hour);
      UniToday[0] = UniTime[0];
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 1);      
      UniToday[0] = time.min/10 + 0x30;
      UniToday[1] = time.min%10 + 0x30;
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 2);
      UniToday[0] = UniTime[1];
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 1);      
      UniToday[0] = time.sec/10 + 0x30;
      UniToday[1] = time.sec%10 + 0x30;
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 2);
      UniToday[0] = UniTime[2];
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 1);
      break;
    default: break;      
    }   
    FillScreen(&IDS[10],TIME_X,TIME_Y,FontType(TIME_FONT),TIME_COLORS,TIME_FCOLOR);
  }
  //��ʾũ�����  
  if(IDS[11].Show){
    CutWSTR(IDS[11].ws,0);
    GetDayOf(date,&NongLi);
    memcpy(IDS[11].ws->wsbody,NongLi.year->wsbody,16);
    FillScreen(&IDS[11],CHSYEAR_X,CHSYEAR_Y,FontType(CHSYEAR_FONT),CHSYEAR_COLORS,CHSYEAR_FCOLOR);
  }
  //��ʾũ������  
  if(IDS[12].Show){
    CutWSTR(IDS[12].ws,0);
    GetDayOf(date,&NongLi);
    memcpy(IDS[12].ws->wsbody,NongLi.mday->wsbody,16);
    FillScreen(&IDS[12],CHSDATE_X,CHSDATE_Y,FontType(CHSDATE_FONT),CHSDATE_COLORS,CHSDATE_FCOLOR);
  }
  //��ʾ�������� 
  if(IDS[13].Show){
    char nDay[8];       
    CutWSTR(IDS[13].ws,0);
    sprintf(nDay,"N%02d.%02d:",date.month,date.day);
    IDS[13].Show = FindBirName(nDay,IDS[13].ws);
    FillScreen(&IDS[13],NBIR_X,NBIR_Y,FontType(NBIR_FONT),NBIR_COLORS,NBIR_FCOLOR);
  }
  //��ʾũ������  
  if(IDS[14].Show){      
    char oDay[8];   
    TDate o=GetOldDay(date);
    CutWSTR(IDS[14].ws,0);
    sprintf(oDay,"P%02d.%02d:",o.month,o.day);
    IDS[14].Show = FindBirName(oDay,IDS[14].ws);
    FillScreen(&IDS[14],OBIR_X,OBIR_Y,FontType(OBIR_FONT),OBIR_COLORS,OBIR_FCOLOR);
  }
  //����
  if((RIN_ENA)&&(!RingHandle)){
    char cTime[12];
    sprintf(cTime,"R%02d:%02d:%02d.",time.hour,time.min,time.sec);
    ExcuteRing(cTime,GetWeek(&date));
  }
  //�Զ��ػ�
  if((AUTOSD_ENA)&&(!PowerState)){
    char aTime[9];
    sprintf(aTime,"%02d:%02d:%02d",time.hour,time.min,time.sec);
    PowerState=AutoPowerOff(aTime);
  }
}
//�˵�����
void APP_TRAF(const char *name, int inx, int type,char *pic,char *file)
{
  APP[inx].Type = type;
  APP[inx].Pic  = pic;
  APP[inx].File = file;
  utf8_2ws(APP[inx].ws,name,strlen(name));  
  if((file)&&(strlen(file)))Count+=1;
}
//��ʼ������ִ����Ϣ
void CreateAppInfo(int inx)
{ 
  switch(inx){  
  case  0: APP_TRAF(ANTO,inx,   -1,(char*)AITO,         ""); break;//�ػ�
  case  1: APP_TRAF(ANRT,inx,   -2,(char*)AIRT,         ""); break;//����
  case  2: APP_TRAF(ANLK,inx,   -3,(char*)AILK,         ""); break;//����
  case  3: APP_TRAF(ANST,inx,   -4,(char*)AIST,         ""); break;//���� 
  case  4: APP_TRAF(AN04,inx, AT04,(char*)AI04,(char*)AF04); break;//����
  case  5: APP_TRAF(AN05,inx, AT05,(char*)AI05,(char*)AF05); break;
  case  6: APP_TRAF(AN06,inx, AT06,(char*)AI06,(char*)AF06); break;
  case  7: APP_TRAF(AN07,inx, AT07,(char*)AI07,(char*)AF07); break;
  case  8: APP_TRAF(AN08,inx, AT08,(char*)AI08,(char*)AF08); break;
  case  9: APP_TRAF(AN09,inx, AT09,(char*)AI09,(char*)AF09); break;
  case 10: APP_TRAF(AN10,inx, AT10,(char*)AI10,(char*)AF10); break;
  case 11: APP_TRAF(AN11,inx, AT11,(char*)AI11,(char*)AF11); break;
  case 12: APP_TRAF(AN12,inx, AT12,(char*)AI12,(char*)AF12); break;
  case 13: APP_TRAF(AN13,inx, AT13,(char*)AI13,(char*)AF13); break;
  }  
}

int size=32;
//��ʼ�����˵�ͼ��λ�ú��ı���Ϣ
void InitMenu(int active)
{   //ȫ������
   Seled=0;
   Count=4;   
   for(int i=0;i<MAX_APP;i++) CreateAppInfo(i); 
   int TextH = GetFontYSIZE(APPTEXT_FONT)+4;
   if (TextH < SoftkeyH()) TextH = SoftkeyH();
    //�ı�����    
    txt.l = 0;
    txt.r = ScreenW()-1;
    txt.t = ScreenH()-OFFSET-1-TextH;    
    txt.b = ScreenH()-OFFSET-1;
    //ͼ��λ��
    ico.l = 0;
    ico.t = txt.t-size-1;
    ico.r = size;
    ico.b = txt.t-1; 
   MenuActive=active;
}
//����Ļ�ϻ����˵�ͼ��λ�ú��ı���Ϣ
void DrawPanel(void)
{/*   
 #ifdef ELKA
  void *canvasmenu = BuildCanvas();{
 #else
  void *idata = GetDataOfItemByID(GetTopGUI(), 2);
  if (idata){
  void *canvasmenu = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
 #endif     
  void *canvasmenu = BuildCanvas();
  DrawCanvas(canvasmenu,txt.l,txt.t,txt.r,txt.b, 1); 
  DrawRoundedFrame( txt.l, txt.t, txt.r, txt.b, 0, 0, 0, cfgPanBorderCol, cfgPanBGCol ); 
  GBS_StartTimerProc(&barTimer,10,DrawPanel); 
  int y = 0; 
  int i = 0;
  int state=0;
  int n = (txt.r-txt.l)/size;
  int m = size + (txt.r-txt.l-size*n)/(n-1);
  int ts=(txt.b-txt.t-GetFontYSIZE(APPTEXT_FONT))/2;  
  //��ҳ��ʾ����
  if ( i < 0 ) i = 0; 
  if (i>=Count) i=Count - 1;
  while ( i < Count ){  
    const char *s=APP[i].Pic;
    if (!((s)&&(strlen(s)))) s=AINO;
    TRect tmp;
    if(i<(MAX_APP+1)/2){
     tmp.l = y+ico.l;
     tmp.t = ico.t;
     tmp.r = y+ico.r;
     tmp.b = ico.b;
     state = 1;
    }else{
     if(state){y=0;state=0;}
     tmp.l = y+ico.l;
     tmp.t = ico.t-size;
     tmp.r = y+ico.r;
     tmp.b = ico.b-size;
    }
    DrawCanvas(canvasmenu, tmp.l, tmp.t, tmp.r, tmp.b, 1); 
    if (i == Seled){                    
       DrawRoundedFrame(tmp.l+1, tmp.t+1, tmp.r-1, tmp.b-1, 2, 2, 0, cfgBookBorderCol, cfgBookBGCol );        
       DrawString(APP[i].ws, txt.l+2, txt.t+ts, txt.r-2, txt.b-ts, FontType(APPTEXT_FONT), TEXT_ALIGNLEFT,APPTEXT_COLORS, cfgPanBGCol);    
    }
    int picw = (size-GetImgWidth((int)s))/2;  if(picw<0)picw=0;
    int pich = (size-GetImgHeight((int)s))/2; if(pich<0)pich=0; 
    DrawImg(tmp.l+picw,tmp.t+pich,(int)s);
    y += m;
    i++;    
  }*/
  void *canvasmenu=BuildCanvas();
  DrawRoundedFrame( txt.l, txt.t, txt.r, txt.b, 0, 0, 0, cfgPanBorderCol, cfgPanBGCol ); 
  GBS_StartTimerProc(&barTimer,10,DrawPanel);   
  if ( Count == 0 ) return; 
  int y = 0; 
  int z = 0;
  int i = 0;  
  int n = ScreenW()/size;
  int OFFSET = size + (ScreenW()-n*size)/(n-1);
  int ts=(txt.b-txt.t-GetFontYSIZE(APPTEXT_FONT))/2;  
  if(Count>((ScreenW())/(OFFSET))) i = Seled - ((ScreenW())/(OFFSET))+1; else i=0;
  if ( i < 0 ) i = 0;
  while ( i < Count )
  {
    const char *s=APP[i].Pic;
    if (!((s)&&(strlen(s)))) s=AINO;
    int picw = (size-GetImgWidth((int)s))/2;  if(picw<0)picw=0;
    int pich = (size-GetImgHeight((int)s))/2; if(pich<0)pich=0; 
    TRect tmp;
    tmp.l = y+ico.l;
    tmp.t = ico.t;
    tmp.r = y+ico.r;
    tmp.b = ico.b;
    DrawCanvas(canvasmenu, tmp.l, tmp.t, tmp.r, tmp.b, 1);
    if ( i == Seled )
    {
       DrawRoundedFrame(tmp.l+1, tmp.t+1, tmp.r-1, tmp.b-1, 2, 2, 0, cfgBookBorderCol, cfgBookBGCol );        
       DrawString(APP[i].ws, txt.l+2, txt.t+ts, txt.r-2, txt.b-ts, FontType(APPTEXT_FONT), TEXT_ALIGNLEFT,APPTEXT_COLORS, cfgPanBGCol); 
       //DrawImg(tmp.l+picw,tmp.t+pich,(int)s);
    }
    DrawImg(tmp.l+picw,tmp.t+pich,(int)s);
    i++;
    y += OFFSET;
    z++;
    if ( z > ((ScreenW())/(OFFSET))-1 ) break;
  }
 //�Զ��رղ˵�
  if((++auto_close>=AUTO_CLOSE*TMR_SECOND/10)&&(MenuActive)&&(MAINCSM_ID)) CloseMenu();
}
//�ػ���Ӧ�¼�
void OnRedraw(GUI *data)
{
  if(SUCCED_HOOK&&MENU_ENA&&(MenuActive)) DrawPanel();
}
//������Ӧ�¼�
void onCreate(GUI *data, void *(*malloc_adr)(int))
{
  data->state=1;
}
//�ر���Ӧ�¼�
void onClose(GUI *data, void (*mfree_adr)(void *))
{
  data->state=0;
}
//�۽���Ӧ�¼�
void onFocus(GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->state=2;
}
//ȡ���۽���Ӧ�¼�
void onUnfocus(GUI *data, void (*mfree_adr)(void *))
{
  if (data->state!=2) return;
  data->state=1;  
}
//���幦��ִ�в�������
void DoIt(int inx);
//���尴����������
int OnKey(GUI *data, GUI_MSG *msg)
{ 
  if(SUCCED_HOOK||MENU_ENA){
    DirectRedrawGUI();
    if ((msg->gbsmsg->msg==KEY_DOWN)){
    //�رղ˵�
     if(msg->gbsmsg->submess==EXIT_BTN){ CloseMenu(); return(1);}
    //ѡ������
   // if(IsUnlocked()){
    // int tmp=Seled;
     //int line=(MAX_APP+1)/2;
     auto_close=0;  
     switch(msg->gbsmsg->submess){     
      //��ѡ��
      case  DOWN_BUTTON://if((Seled-=line)<0) Seled=tmp+line; break;  
      //��ѡ��
      case RIGHT_BUTTON:if(++Seled >= Count) Seled=0;break; 
      //��ѡ��
      case    UP_BUTTON://if((Seled+=line)>=Count) Seled=tmp-line;break;         
      //��ѡ��
      case  LEFT_BUTTON:if(--Seled<0) Seled=Count-1; break;   
        
      //ִ�жԾ͵Ĺ���
      case ENTER_BUTTON: DoIt(Seled); break;
     }     
     //return(1);
    //}
   }
  }
  return(0);
}
//�ͷ���Ӧ�¼�
void onDestroy(GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,	//�ػ�
  (void *)onCreate,	//����
  (void *)onClose,	//�ر�
  (void *)onFocus,	//�۽�
  (void *)onUnfocus,	//ȡ���۽�
  (void *)OnKey,	//��������
  0,
  (void *)onDestroy,	//�ͷ�
  (void *)method8,      //����δ֪
  (void *)method9,      //����δ֪
  0
};

const RECT Canvas={0, 0, 0, 0};

void maincsm_onguicreate(CSM_RAM *data)
{
  GUI *main_gui=malloc(sizeof(GUI));
  DAEMON_GUI *csm=(DAEMON_GUI*)data;
  zeromem(main_gui,sizeof(GUI));
  main_gui->canvas=(void *)(&Canvas);
  //main_gui->flag30=2;
  main_gui->methods=(void *)gui_methods;
  main_gui->item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->menu_id=CreateGUI(main_gui);  
  csm->file_id=BrowserFileMenu();
}

#ifndef DAEMON
static void ELF_KILLER(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
#endif
void maincsm_onguiclose(CSM_RAM *csm)
{  
#ifndef DAEMON
  SUBPROC((void *)ELF_KILLER);
#endif  
}

int maincsm_onguimessage(CSM_RAM *data, GBS_MSG *msg)
{
  DAEMON_GUI *csm=(DAEMON_GUI*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->menu_id))
  {
    csm->csm.state=-3;
  }  
  return(1);
}

unsigned short maincsm_name_body[LEN];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name_gui;
}DAEMONCSM =
{
  {
    maincsm_onguimessage,
    maincsm_onguicreate,
#ifdef NEWSGOLD
0,
0,
0,
0,
#endif
maincsm_onguiclose,
sizeof(DAEMON_CSM),
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

void CloseMenu(void)
{
  if(IsTimerProc(&barTimer)){GBS_DelTimer(&barTimer);}
  if(MAINCSM_ID){CloseCSM(MAINCSM_ID); MAINCSM_ID=0;}
  MenuActive=0;
  DirsActive=0;
  auto_close=0;
  RefreshGUI();
}
void RunDIR(char *dir)
{
  LockSched();  
  MenuActive=0;
  DirsActive=1;
  strcpy(path,dir);
  GBS_SendMessage(MMI_CEPID,KEY_UP);  
  char dummy[sizeof(DAEMON_CSM)];
  MAINCSM_ID=CreateCSM(&DAEMONCSM.maincsm,dummy,2);
  RefreshGUI();
  UnlockSched();
}
void TaskMenu(int mode)
{
  LockSched();
  DirsActive=0;
  char dummy[sizeof(DAEMON_CSM)];
  InitMenu(mode);
  MAINCSM_ID=CreateCSM(&DAEMONCSM.maincsm,dummy,2);
  UnlockSched();
}

void DoIt(int inx) 
{ 
  CloseMenu();
  switch(APP[inx].Type){
   case -4: OpenBCFGFile(); break;
   case -3: KbdLock();break;
   case -2: RebootPhone();break;
   case -1: SwitchPhoneOff(); break;
   case  0: RunAPP(APP[inx].File); break;
   case  1: RunCUT(APP[inx].File); break;
   case  2: RunADR(APP[inx].File); break;
   case  3: RunDIR(APP[inx].File); break;
  }     
}

#ifdef DAEMON
//�����ҹ�
int daemon_keyhook(int key, int m)
{
  extern const int MODE_KBD;
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&(m==MODE_KBD+0x193))
  { 
    if(IsUnlocked()&&(key==CALL_BTN)){ TaskMenu(1); return(0);}
    if((RingHandle)&&(RIN_ENA)&&(key==RIN_BTN)){
        if(VIB_ENA)SetVibration(0);
        PlayMelody_StopPlayback(RingHandle);
        RingHandle=0;
        return(0);
    }
   }
  return 0;
}

static void daemon_killer(void)
{
  extern void *ELF_BEGIN;
  if(MAINCSM_ID) CloseCSM(MAINCSM_ID);
  if(SUCCED_HOOK) RemoveKeybMsgHook((void *)daemon_keyhook);  
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int daemon_onmessage(CSM_RAM* data,GBS_MSG* msg)
{  
  // ��������
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {      
      ShowMSG(1,(int)"ScrTool updated!");
      InitConfig();
      //���¼��ؽ����ļ�����
      if(FreeFileBuf(BirBuf)) BirBuf=LoadFileBuf(BIR_FILE);  
    }
  } 
  //�Զ����ֻ���������
  if ((MENU_ENA)&&(!SUCCED_HOOK))
  {      
      AddKeybMsgHook((void *)daemon_keyhook);
      SUCCED_HOOK = 1;
  }
  else if((!MENU_ENA)&&(SUCCED_HOOK))
  {
     if(MAINCSM_ID) CloseCSM(MAINCSM_ID); 
     RemoveKeybMsgHook((void *)daemon_keyhook);  
     SUCCED_HOOK = 0;
  }
  //�Զ��幦����ʾ
  if (INFO_ENA){
   #define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
   if (msg->msg==MSG_IPC){
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0)){
      if (strcmp_nocase(ipc->name_to,ipc_name)==0){
        switch (msg->submess){
        case UPDATE_STAT:
          #ifdef NEWSGOLD
          if (!getCpuUsedTime_if_ena()){StartCpuUsageCount();}
          #endif
          GBS_StartTimerProc(&txtTimer, REFRESH*TMR_SECOND/10, TimerProc);
          TextActive = 1;
        }
      }
    }
   }  
   CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
   if (icsm){
    if (IsGuiOnTop(idlegui_id(icsm))){
      GUI *igui=GetTopGUI();
      if (igui){
        InitData();
        #ifdef ELKA
        { void *canvastext = BuildCanvas();
        #else
          void *idata = GetDataOfItemByID(igui, 2);
        if (idata){
          void *canvastext = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
        #endif
          for (int inx=0; inx<(sizeof(IDS)/sizeof(TSCR)); inx++){
            if (IDS[inx].Show){
              DrawCanvas(canvastext, IDS[inx].rc.x,IDS[inx].rc.y,IDS[inx].rc.x2,IDS[inx].rc.y2, 1);
              DrawString(IDS[inx].ws,IDS[inx].rc.x,IDS[inx].rc.y,IDS[inx].rc.x2,IDS[inx].rc.y2,IDS[inx].Size,
                         TEXT_OUTLINE,IDS[inx].Pen,IDS[inx].Brush);
            }          
          }
        }
      }
    }
    }
   }else{if((TextActive)&&(IsTimerProc(&txtTimer))){GBS_DelTimer(&txtTimer);TextActive=0;}}
   //�˵�
   DAEMON_GUI *csm=(DAEMON_GUI*)data;
   if ((int)msg->data0==csm->file_id){
      if (csm->menu_id==0)
         csm->csm.state=-3;
      csm->file_id=0;
    }   
   //��������
   if((msg->msg==MSG_PLAYFILE_REPORT)&&(RIN_ENA)){
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if (pmsg->handler==RingHandle){
      if (pmsg->cmd==M_SAE_PLAYBACK_ERROR || pmsg->cmd==M_SAE_PLAYBACK_DONE){
       RingHandle=0;
       SetVibration(0);
      }else if((VIB_ENA)&&(!IsCalling())){
        if(--RIN_VPW>0){
          SetVibration(RIN_VPW);
        }else{
          RIN_VPW=RIN_VIB;
          SetVibration(RIN_VIB);
        }
      }
    }else RingHandle=0;    
   }
   //�Զ��ػ�
   if((AUTOSD_ENA)&&(PowerState)&&(DAEMON_ID)){
     CloseCSM(DAEMON_ID);
     SwitchPhoneOff(); 
   }
  return(1);
}  

static void daemon_oncreate(CSM_RAM *data)
{  
  for (int i=0;i<MAX_IDS; i++) IDS[i].ws=AllocWS(50);
  for (int i=0;i<MAX_APP; i++) APP[i].ws=AllocWS(50);
  BirBuf=LoadFileBuf(BIR_FILE);
  NongLi.year=AllocWS(50);
  NongLi.mday=AllocWS(50);
  if(INFO_ENA) GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&my_ipc);
}

static void daemon_onclose(CSM_RAM *csm)
{
  if((TextActive)&&(IsTimerProc(&txtTimer)))GBS_DelTimer(&txtTimer);
  for (int i=0;i!=MAX_IDS; i++) FreeWS(IDS[i].ws);
  for (int i=0;i!=MAX_APP; i++) FreeWS(APP[i].ws);
  FreeFileBuf(BirBuf);
  FreeWS(NongLi.year);
  FreeWS(NongLi.mday);
  SUBPROC((void *)daemon_killer);  
}

static unsigned short daemon_name_body[LEN];

static const struct
{
  CSM_DESC maincsm;
  WSHDR daemon_name;
}CSM_DAEMON =
{
  {
  daemon_onmessage,
  daemon_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  daemon_onclose,
  sizeof(DAEMON_GUI),
  1,
  &minus11
  },
  {
    daemon_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void)
{   
  const char *AVER=strrchr(ANTO,'-')+1;
  utf8_2ws((WSHDR *)(&CSM_DAEMON.daemon_name),AVER,strlen(AVER));
}
#endif

int main()
{
  LockSched();
  InitConfig();
  UpdateCSMname();
#ifdef DAEMON
  CSM_RAM *save_cmpc;
  char dummy[sizeof(DAEMON_GUI)];  
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  DAEMON_ID=CreateCSM(&CSM_DAEMON.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  if(MENU_ENA){      
      AddKeybMsgHook((void *)daemon_keyhook);   
      SUCCED_HOOK = 1;
  }
#else 
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
#endif    
  UnlockSched();
  return 0;
}
