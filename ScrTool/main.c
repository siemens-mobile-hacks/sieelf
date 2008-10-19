#include <swilib.h>
#include <cfg_items.h>
#include <sieapi.h>
#include <playsound.h>
#include "scrtool.h"
#include "conf_loader.h"
//ע������������ȫ��̨���а汾
static char ANST[]="�������";//����
static char ANTO[]="�ػ�-õ��v2.20";//�ػ�
static char ANRT[]="�����ֻ�";//����
static char ANLK[]="��ס����";//����
static char TASK[]="����˵�";//����˵�
static char ALRM[]="�������";//���ӽ���
static const  IPC_REQ my_ipc={SCR_NAME, SCR_NAME, NULL};
static const int MINUSLL=-11;
static int  TASK_ID   = 0;//��¼ͼ�ν���
static int  RING_ID   = 0;//��¼��������
static int  DMON_ID   = 0;//��¼�ڴ�����
static char TASK_STATE;//��¼���н�������,1Ϊ�˵�,2Ϊ��ݲ˵�,3Ϊ���ӽ���
static ubyte AUTO_EXIT = 0;//��¼�Զ��˳��˵�״̬
static ubyte SUCC_HOOK = 0;//��¼HOOK״̬
static int TaskCount,TaskSeled,AlrmInx;
//�������ݻ���
static char *BirsData;
//���ò˵�
static char  PATHS[64];
static char  TITLE[32];
static TSCR  IDS[MAX_IDS];
static TAPP  APP[MAX_APP];
static TLunar NongLi;
static GBSTMR tskTimer,scrTimer;
static short OLScr;//��Ļ����ԭֵ
HEADER_DESC MENU_HDR={0,0,0,0,NULL,(int)TITLE,LGP_NULL};
//���幦��ִ�в�������
static void DoIt(int inx);
static void BuildGUI(short mode,char *name);
//�ر��еĲ˵�
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
//�˵���������
static int  MENU_ONKEY(void *gui, GUI_MSG *msg);
//�˵�HOOK��������
static void MENU_HOOK(void *gui, int cmd){
  TFile *FileList=MenuGetUserPointer(gui);
  if (cmd==3){ 
    FreeFile(FileList);
  }  
}
//�˵��ػ��б�
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
    wsprintf(ws,"%t","����!!!");
  }  
  SetMenuItemText(gui, item, ws, cur_item); 
}
//�˵�������ʼ��
static int MENU_SOFTKEYS[]={0,1,2};
//�˵��������
SOFTKEY_DESC MENU_PRESS[]={
  {0x0018,0x0000,(int)"��"},
  {0x0001,0x0000,(int)"�˳�"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB MENU_TAB={MENU_PRESS,0};
//����˵��ṹ
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
//���尴ť��Ӧ�¼�
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
//���������ļ�
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
        //�����ļ�Ŀ¼
        len=strlen(de.folder_name)+strlen(de.file_name)+2+1;
        sb->path=malloc(len);        
        strcpy(sb->path,de.folder_name);
        strcat(sb->path,"\\");
        strcat(sb->path,de.file_name);
        //�����ļ�����
        sb->file=malloc(strlen(de.file_name)+1);        
        strcpy(sb->file,de.file_name);
        //������չ��
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
//�������˵�
static int BrowserFileMenu(){ 
  TFile *sbtop=FindBCFGFile();
  patch_header(&MENU_HDR);
  return CreateMenu(0,0,&MENU_STRUCT,&MENU_HDR,0,FileCount(sbtop),sbtop,0);
}
//�������ò˵�
//��ʼ��������ʾ����
static void SetIDS(TSCR *SCR,int ENA,int TYPE,int FONT,const char *Pen,const char *Brush){
  SCR->Show = ENA;
  SCR->Font = FontType(FONT);
  SCR->Type = TYPE;    
  memcpy(SCR->Pen,Pen,4);
  memcpy(SCR->Brush,Brush,4);
}
static void InitShow(void){
 SetIDS(&IDS[0],TEMP_ENA,TEMP_XT,TEMP_FONT,TEMP_CS,TEMP_CB);
 SetIDS(&IDS[1],VOLT_ENA,VOLT_XT,VOLT_FONT,VOLT_CS,VOLT_CB);
 SetIDS(&IDS[2],RAM_ENA,RAM_XT,RAM_FONT, RAM_CS,RAM_CB);
 SetIDS(&IDS[3],TEXT_ENA,TEXT_XT,TEXT_FONT,TEXT_CS,TEXT_CB);
 SetIDS(&IDS[4],NET_ENA,NET_XT,NET_FONT,NET_CS,NET_CB);
 SetIDS(&IDS[5],ACCU_ENA,ACCU_XT,ACCU_FONT,ACCU_CS,ACCU_CB);
 SetIDS(&IDS[6],CPU_ENA,CPU_XT,CPU_FONT,CPU_CS,CPU_CB);
 SetIDS(&IDS[7],GPRS_ENA,GPRS_XT,GPRS_FONT,GPRS_CS,GPRS_CB);
 SetIDS(&IDS[8],WEEK_ENA,WEEK_XT,WEEK_FONT,WEEK_CS,WEEK_CB);
 SetIDS(&IDS[9],DATE_ENA,DATE_XT,DATE_FONT,DATE_CS,DATE_CB);
 SetIDS(&IDS[10],TIME_ENA,TIME_XT,TIME_FONT,TIME_CS,TIME_CB);
 SetIDS(&IDS[11],CYEAR_ENA,CYEAR_XT,CYEAR_FONT,CYEAR_CS,CYEAR_CB);
 SetIDS(&IDS[12],CDATE_ENA,CDATE_XT,CDATE_FONT,CDATE_CS,CDATE_CB);
 SetIDS(&IDS[13],NBIR_ENA,NBIR_XT ,NBIR_FONT,NBIR_CS,NBIR_CB);
 SetIDS(&IDS[14],OBIR_ENA,OBIR_XT ,OBIR_FONT,OBIR_CS,OBIR_CB);
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
//��ʾ������ɫ��λ����ʾ��
static void FillScreen(TSCR *SCR,int x,int y)
{  
  int width =PixlsWidth(SCR->ws,SCR->Font);
  int center=(ScreenW()-width-1)/2;
  int right =ScreenW()-width-1;
  switch(SCR->Type){
    case 1:SCR->l=0;       SCR->r=width;break;
    case 2:SCR->l=center;  SCR->r=center+width;break;
    case 3:SCR->l=right;   SCR->r=right+width;break;
   default:SCR->l=x;       SCR->r=x+width;break;
  }
  SCR->t=y;
  SCR->b=y+GetFontYSIZE(SCR->Font);
}

//�����Զ������Ӳ���
static int ExcuteRing(const char *sub,int Week){ 
  char TEMP[LEN];
  if(FindSub(BirsData,sub,TEMP,7)){
    if(strlen(TEMP)>=7){
     if(TEMP[Week]=='1'){
      BuildGUI(SCR_ALARM,ALRM);
      return(PlayMusic(ALRM_FILE, ALRM_VOLUME,ALRM_NUM));
     }
    }
  }
  return(0);
}
//�˵�����
static void APP_TRAF(char *Name, int i, int Type,char *Pic,char *File)
{
  APP[i].Type = Type;
  APP[i].Pic  = Pic;
  APP[i].File = File;
  APP[i].Name = Name;
  if((File)&&(strlen(File)))TaskCount+=1;
}
/*
static int GetSec(int sec)
{
  int result = sec;
  if(sec>=10&&sec<20)
     result = sec-10;
  elif(sec>=20&&sec<30)
     result = sec-20;
  elif(sec>=30&&sec<40)
     result = sec-30;
  elif(sec>=40&&sec<50)
     result = sec-40;
  elif(sec>=50&&sec<60)
     result = sec-50;
  return(result);
}
*/
//�����Զ�����ղ���

static int FindBirName(WSHDR *ws,const char *sub){  
  char *p = strstr(BirsData,sub);
  if(p){
    char *pa = strchr(p,0x0A);
    char TEMP[LEN];
    strncpy(TEMP,p+7,pa-p-7);
    wsprintf(ws,PFMT_STR,TEMP);
    return 1;
  }else{return 0;}
}
//��������ʾ���ݽ��в�ʼ��
static void InitScreen(void)
{  
  for(int i=0;i<MAX_IDS;i++){CutWSTR(IDS[i].ws,0);}
  if(IDS[0].Show){//��ʾ�¶���Ϣ 
    int c=GetAkku(1,3)-0xAAA+15;
    wsprintf(IDS[0].ws,TEMP_FMT,c/10,c%10);
    FillScreen(&IDS[0],TEMP_X,TEMP_Y);
  }   
  if(IDS[1].Show){//��ʾ��ѹ��Ϣ
    int c=GetAkku(0,9);
    if(VOLT_TY==0)
       wsprintf(IDS[1].ws,VOLT_FMT,c/1000,(c%1000)/10);
    elif(VOLT_TY==1){
      int ct=VOLT_TS-VOLT_TE;
      c=(c-VOLT_TE)*100;
      if(VOLT_TE>VOLT_TS)ct=VOLT_TE-VOLT_TS;
      if(ct>0)c=(c/ct);else c=0;
      if(c>100)c=100;elif(c<0)c=0;
      wsprintf(IDS[1].ws,"%d%%",c);
    }
    FillScreen(&IDS[1],VOLT_X,VOLT_Y);
  }
  if(IDS[2].Show){//��ʾʣ����Ϣ    
    int c=GetFreeRamAvail();
    wsprintf_bytes(IDS[2].ws,c);
    FillScreen(&IDS[2],RAM_X,RAM_Y);  
  } 
  if(IDS[3].Show){//��ʾ������Ϣ
    wsprintf(IDS[3].ws,PFMT_STR,TEXT_FMT);
    FillScreen(&IDS[3],TEXT_X,TEXT_Y);
  }         
  if(IDS[4].Show){//��ʾ������Ϣ
    RAMNET *net_data=RamNet();
    int c=(net_data->ch_number>=255)?'=':'-';
    wsprintf(IDS[4].ws,NET_FMT,c,net_data->power);
    FillScreen(&IDS[4],NET_X,NET_Y);
  }     
  if(IDS[5].Show){//��ʾCAP��Ϣ
    int c=*RamCap();
    wsprintf(IDS[5].ws,ACCU_FMT,c);
    FillScreen(&IDS[5],ACCU_X,ACCU_Y);
  }    
  if(IDS[6].Show){//��ʾCPUʹ����
    int c=GetCPULoad();
    if(c==100) c=99;
    wsprintf(IDS[6].ws,CPU_FMT,c);
    FillScreen(&IDS[6],CPU_X,CPU_Y);
  }       
  if(IDS[7].Show){//��ʾGPRS����
    //RefreshGPRSTraffic();
    int c=*GetGPRSTrafficPointer();
    wsprintf_bytes(IDS[7].ws,c);
    FillScreen(&IDS[7],GPRS_X,GPRS_Y);
  }
  //����ʱ����Ϣ
  TTime t; TDate d; GetDateTime(&d,&t);
  uword UniToday[8];  
  int Week = GetWeek(&d);  
  if(IDS[8].Show){//��ʾ��ǰ����    
    if(WEEK_FMT <4){
      char cWeek[16];
      for(ubyte i=0;i<16;i++){cWeek[i]=cWeekName[WEEK_FMT][Week][i];}
      wsprintf(IDS[8].ws,cWeek,Week);
    }else if (WEEK_FMT==4){
      wsprintf(IDS[8].ws,_percent_e,WeekHD,WeekID[Week]);
    }else{
      wsprintf(IDS[8].ws,PFMT_STR,WeekID[Week]); 
    }
    FillScreen(&IDS[8],WEEK_X,WEEK_Y);
  }
  if(IDS[9].Show){//��ʾ��ǰ����
    char cData[16]; 
    for(ubyte i=0;i<16;i++){cData[i]=cDataFmt[DATE_FMT][i]; }
    if(DATE_FMT < 4)
      wsprintf(IDS[9].ws,cData,d.year,d.month,d.day);
    else if(DATE_FMT <8)
      wsprintf(IDS[9].ws,cData,d.month,d.day);
    else {
      short inx=-1;
      if(DATE_FMT == 8) {
        wsprintf(IDS[9].ws,"%04d",d.year);
        UniToday[++inx] = UniDate[0];
      }
      UniToday[++inx] = d.month/10 + 0x30;
      UniToday[++inx] = d.month%10 + 0x30;
      UniToday[++inx] = UniDate[1];
      UniToday[++inx] = d.day/10 + 0x30;
      UniToday[++inx] = d.day%10 + 0x30;
      UniToday[++inx] = UniDate[2];
      BSTRAdd(IDS[9].ws->wsbody,UniToday, ++inx);     
    }
    FillScreen(&IDS[9],DATE_X,DATE_Y);
  }  
  if(IDS[10].Show){//��ʾ��ǰʱ��
    switch(TIME_FMT) {
    case 0: wsprintf(IDS[10].ws,"%02d:%02d",t.hour,t.min); 
      break;      
    case 1:
      if(t.hour <= 12) {
        wsprintf(IDS[10].ws,"AM %02d:%02d",t.hour,t.min);
      } else {
        t.hour = t.hour - 12;
        wsprintf(IDS[10].ws,"PM %02d:%02d",t.hour,t.min);
      } 
      break;      
    case 2:
      if(t.hour > 12) t.hour = t.hour - 12;
      wsprintf(IDS[10].ws,"%02d:%02d",t.hour,t.min);
      break;      
    case 3: 
      wsprintf(IDS[10].ws,"%02d:%02d:%02d",t.hour,t.min,t.sec); 
      break;      
    case 4:
      if(t.hour <= 12){
        wsprintf(IDS[10].ws,"AM %02d:%02d:%02d",t.hour,t.min,t.sec);
      } else {
        t.hour = t.hour - 12;
        wsprintf(IDS[10].ws,"PM %02d:%02d:%02d",t.hour,t.min,t.sec);
      }
      break;
    case 5:
      wsprintf(IDS[10].ws,"%02d",t.hour);
      UniToday[0] = UniTime[0];  
      UniToday[1] = t.min/10 + 0x30;
      UniToday[2] = t.min%10 + 0x30;
      UniToday[3] = UniTime[1];
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 4);
      break;
    case 6:
      wsprintf(IDS[10].ws,"%02d",t.hour);
      UniToday[0] = UniTime[0];   
      UniToday[1] = t.min/10 + 0x30;
      UniToday[2] = t.min%10 + 0x30;
      UniToday[3] = UniTime[1];   
      UniToday[4] = t.sec/10 + 0x30;
      UniToday[5] = t.sec%10 + 0x30;
      UniToday[6] = UniTime[2];
      BSTRAdd(IDS[10].ws->wsbody,UniToday, 7);
      break;
    default: break;      
    }   
    FillScreen(&IDS[10],TIME_X,TIME_Y);
  }  
  if(IDS[11].Show){//��ʾũ�����
    GetDayOf(d,&NongLi);
    memcpy(IDS[11].ws->wsbody,NongLi.year->wsbody,16);
    FillScreen(&IDS[11],CYEAR_X,CYEAR_Y);
  } 
  if(IDS[12].Show){//��ʾũ������
    uword lunar = LunarHolId(d);
    if(lunar)
      LunarHolDay(IDS[12].ws,lunar);
    else{
      GetDayOf(d,&NongLi);
      memcpy(IDS[12].ws->wsbody,NongLi.mday->wsbody,16);
    }
    FillScreen(&IDS[12],CDATE_X,CDATE_Y);
  }
  /*
  if(IDS[13].Show){//��ʾ���湫������
    char Result[8];
    TDate o=GetOldDay(d);  
    if(GetSec(t.sec)<5){
     sprintf(Result,"N%02d.%02d:",d.month,d.day); 
    }else{     
     sprintf(Result,"P%02d.%02d:",o.month,o.day);
    }
    if(FindBirName(IDS[13].ws,Result)){
     FillScreen(&IDS[13],NBIR_X,NBIR_Y);
   }
  }*/
  if(NBIR_ENA){//��ʾ��������
    char nDay[8];  
    sprintf(nDay,"N%02d.%02d:",d.month,d.day);
    IDS[13].Show=FindBirName(IDS[13].ws,nDay);
    FillScreen(&IDS[13],NBIR_X,NBIR_Y);
  }  
  if(OBIR_ENA){//��ʾũ������      
    char oDay[8];   
    TDate o=GetOldDay(d);
    sprintf(oDay,"P%02d.%02d:",o.month,o.day);
    IDS[14].Show = FindBirName(IDS[14].ws,oDay);
    FillScreen(&IDS[14],OBIR_X,OBIR_Y);
  }
}

//����Ļ�ϻ����˵�ͼ��λ�ú��ı���Ϣ
static void DrawPanel(void)
{ 
  GBS_StartTimerProc(&tskTimer,5,DrawPanel); 
  WSHDR *MenuWS=AllocWS(50);
  void *TaskCanvas=BuildCanvas();//CreateCanvas();
  if(TaskCanvas){
   //--------�ı�����--------
   int TextH = GetFontYSIZE(ATEXT_FONT)+4;//�ı��߶�
   if (TextH < SoftkeyH()) TextH = SoftkeyH(); 
   short top=ScreenH()-TextH-OFFSET-1;//�ı�����λ�� 
   TRect tRC={0,top,ScreenW()-1,ScreenH()-OFFSET-1};//�����ı���������
   TRect iRC={0,top-PicSize-1,PicSize-1,top-1};//����ͼ���������
   TRect fRc=iRC; 
   int y=0,z=0,i=0,n=ScreenW()/PicSize;  
   int ts=(tRC.b-tRC.t-GetFontYSIZE(ATEXT_FONT))/2;//�����ı���ֱƫ��  
   n = PicSize + (ScreenW()-n*PicSize)/(n-1);//����ͼ����ʾ��
   if(TaskCount>((ScreenW())/(n))){ i=TaskSeled-((ScreenW())/(n))+1; if(i<0)i=0;} else i=0;
   //--------����ͼ����ı�--
   if(DEST_ENA)DrawRectangle(tRC.l, tRC.t, tRC.r, tRC.b,0, cfgPBDCol, cfgPBGCol);
   while(i<TaskCount){
    const char *s=APP[i].Pic;
    if(!((s)&&(strlen(s)))) s=AINO;    
    TRect tmp=iRC; tmp.l+=y; tmp.r+=y;  
    DrawCanvas(TaskCanvas, tmp.l,tmp.t,tmp.r,tmp.b, 0);
    int picw = (PicSize-GetImgWidth((int)s))/2;  if(picw<0)picw=0;
    int pich = (PicSize-GetImgHeight((int)s))/2; if(pich<0)pich=0; 
    DrawImg(tmp.l+picw,tmp.t+pich,(int)s);  
    if(i==TaskSeled){
      if(DEST_ENA){
        wsprintf(MenuWS,PFMT_STR,APP[i].Name);
        DrawString(MenuWS,tRC.l+3,tRC.t+ts,tRC.r-3,tRC.b-ts,FontType(ATEXT_FONT),1,ATEXT_CS,TRAN_CBK);
      }
      fRc = tmp;
    }
    y+=n;
    i++;
    if(++z>((ScreenW())/(n))-1) break;
   }  
   DrawRectangle(fRc.l,fRc.t,fRc.r,fRc.b,0,cfgBBDCol,TRAN_CBK);
  }
  //�Զ��رղ˵�
  if((++AUTO_EXIT>=AUTO_CLOSE*TMR_SECOND/5)&&(TASK_ID)) CloseTask();
  FreeWS(MenuWS);
}
//���ӽ���
static void DrawAlarm(void){     
  GBS_StartTimerProc(&tskTimer,100,DrawAlarm); 
  WSHDR *AlrmWS=AllocWS(50);
  void *TaskCanvas=BuildCanvas();//CreateCanvas();
  if(TaskCanvas){   
   TRect Alarm={0,YDISP,ScreenW()-1,ScreenH()-1};
   DrawCanvas(TaskCanvas, Alarm.l,Alarm.t,Alarm.r,Alarm.b, 1);
   char PIC[64];
   sprintf(PIC,ALRM_PIC,AlrmInx);
   wsprintf(AlrmWS,PFMT_STR,ALRM);   
   int wsh=GetFontYSIZE(ALRM_FONT)+4;
   int wso=(Alarm.r-Alarm.l-PixlsWidth(AlrmWS,ALRM_FONT))/2;
   int pio=(Alarm.r-Alarm.l-GetImgWidth((int)PIC))/2;
   int pih=GetImgHeight((int)PIC);    
   TRect Altxt={Alarm.l,Alarm.t,Alarm.r,Alarm.t+wsh}; 
   TRect Alpic={Alarm.l+pio,Altxt.b,Alarm.l-pio,Alarm.b+pih};
   DrawRectangle(Alarm.l, Alarm.t, Alarm.r, Alarm.b,0, ALRM_CBK, ALRM_CBK);  
  //����     
   DrawString(AlrmWS, Altxt.l+wso, Altxt.t+2, Altxt.r-wso, Altxt.b-2,FontType(ALRM_FONT), 1,ALRM_CTX, TRAN_CBK); 
  //ͼ��
   DrawImg(Alpic.l,Alpic.t,(uint)PIC);
  //����
   TTime t; TDate d;
   GetDateTime(&d,&t);   //����
   wsprintf(AlrmWS,PFMT_STR,WeekGB[GetWeek(&d)]);
   wso=(Alarm.r-Alarm.l-PixlsWidth(AlrmWS,ALRM_FONT))/2;
   TRect Alwek={Alarm.l+wso,Altxt.b+pih,Alarm.r-wso,Altxt.b+pih+wsh}; 
   DrawString(AlrmWS, Alwek.l, Alwek.t+2,Alwek.r,Alwek.b-2,FontType(ALRM_FONT), 1,ALRM_CTX, TRAN_CBK);
  //ʱ��
   wsprintf(AlrmWS,"%02d:%02d:%02d",t.hour,t.min,t.sec); 
   wso=(Alarm.r-Alarm.l-PixlsWidth(AlrmWS,ALRM_FONT))/2;
   TRect Altim={Alarm.l+wso,Alwek.b,Alarm.r-wso,Alwek.b+wsh}; 
   DrawString(AlrmWS, Altim.l, Altim.t+2,Altim.r,Altim.b-2,FontType(ALRM_FONT), 1,ALRM_CTX, TRAN_CBK);
  //��ʾ����
   wsprintf(AlrmWS,"%04d%t%02d%t%02d%t",d.year,"��",d.month,"��",d.day,"��");
   wso=(Alarm.r-Alarm.l-PixlsWidth(AlrmWS,ALRM_FONT))/2;
   TRect Aldat={Alarm.l+wso,Altim.b,Alarm.r-wso,Altim.b+wsh}; 
   DrawString(AlrmWS, Aldat.l, Aldat.t+2,Aldat.r,Aldat.b-2,FontType(ALRM_FONT), 1,ALRM_CTX, TRAN_CBK);
   //ѭ��ͼƬ
   if(AlrmInx%2){
     SetIllumination(0,1,100,0);
     if(VIB_ENA)SetVibration(ALRM_VIB);
   }else{
     SetIllumination(0,1,5,0);
     if(VIB_ENA)SetVibration(0);
   }
   if(AlrmInx>=ALRM_COT)AlrmInx=0;
   AlrmInx++;
  }
  FreeWS(AlrmWS);
}
//�ػ���Ӧ�¼�
static void TaskRedraw(GUI *gui){
  if(SUCC_HOOK&&TASK_ENA&&(TASK_STATE==SCR_TASKS))
     DrawPanel();
  else if((ALRM_ENA)&&(TASK_STATE==SCR_ALARM))
     DrawAlarm();
}
//������Ӧ�¼�
static void TaskCreate(GUI *gui, void *(*malloc_adr)(int)){
  if(TASK_STATE==SCR_TASKS){
    //ȫ������
    TaskSeled=0;  
  }
  if(TASK_STATE==SCR_ALARM){    
    OLScr=GetIlluminationDataTable()[3];
    AlrmInx=1;    
  }  
  gui->state=1;
}
//�ر���Ӧ�¼�
static void TaskClose(GUI *gui, void (*mfree_adr)(void *)){
  gui->state=0;
}
//�۽���Ӧ�¼�
static void TaskFocus(GUI *gui, void *(*malloc_adr)(int), void (*mfree_adr)(void *)){
  gui->state=2;
}
//ȡ���۽���Ӧ�¼�
static void TaskUnfocus(GUI *gui, void (*mfree_adr)(void *)){
  if (gui->state!=2) return;
  gui->state=1; 
  CloseCSM(TASK_ID);
}
//���尴����������
static int TaskKeypress(GUI *gui, GUI_MSG *msg){ 
  if(SUCC_HOOK||TASK_ENA){
    DirectRedrawGUI();
    if ((msg->gbsmsg->msg==KEY_DOWN)){    
    AUTO_EXIT=0;
    uint KeyPress=msg->gbsmsg->submess;    
    //�رղ˵�    
    //if(KeyPress==KeyButton(EXIT_BTN)){CloseTask(); return(1);}
    if(KeyPress==KeyButton(CALL_BTN)){CloseTask(); return(1);}
    //ѡ������
    switch(KeyPress){          
      case  DOWN_BUTTON://��ѡ����ѡ��      
      case RIGHT_BUTTON:if(++TaskSeled >=TaskCount)TaskSeled=0;break;       
      case    UP_BUTTON://��ѡ����ѡ��         
      case  LEFT_BUTTON:if(--TaskSeled<0)TaskSeled=TaskCount-1;break;           
      //ִ�жԾ͵Ĺ���
      case ENTER_BUTTON:if(TASK_STATE==SCR_TASKS)DoIt(TaskSeled); break;
    }  
   }
  }
  return(0);
}
static int TaskMethod8(void){return(0);}
static int TaskMethod9(void){return(0);}
static const void * const TaskMethods[11]={
  (void *)TaskRedraw,	//�ػ�
  (void *)TaskCreate,	//����
  (void *)TaskClose,	//�ر�
  (void *)TaskFocus,	//�۽�
  (void *)TaskUnfocus,	//ȡ���۽�
  (void *)TaskKeypress,	//��������
  0,
  (void *)kill_data,
  (void *)TaskMethod8,      //����δ֪
  (void *)TaskMethod9,      //����δ֪
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
  TaskGui->item_ll.data_mfree=(void (*)(void *))mfree_adr();
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
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
#endif
}
static void TaskOnClose(CSM_RAM *csm){  
  SUBPROC((void *)TaskKiller); 
}

static int TaskOnMessage(CSM_RAM *data, GBS_MSG *msg)
{
  TASK_GUI *TaskCsm=(TASK_GUI*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==TaskCsm->TaskID))
  {
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

static void BuildGUI(short mode,char *name){  
  LockSched();
  TASK_STATE=mode;
  static char DUMMY[sizeof(TASK_GUI)];
  wsprintf((WSHDR *)(&TASK_CSM.NAME),PFMT_STR,name);
  TASK_ID=CreateCSM(&TASK_CSM.CSM,DUMMY,2);  
  UnlockSched();
}
static void RunDIR(char *dir,char *name){  
  strcpy(PATHS,dir);  
  strcpy(TITLE,name);
  BuildGUI(SCR_MENUS,name);
}
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
//�����ҹ�,�ڴ�����
static int DaemonKeyHook(int key, int m){  
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&(m==MODE_KBD+0x193)){ 
    if(IsUnlocked()&&(key==KeyButton(CALL_BTN))){BuildGUI(SCR_TASKS,TASK); return(0);}    
  }
  return 0;
}
static void InitMenu(void){
 TaskCount=4;    
 for(int inx=0;inx<MAX_APP;inx++){ 
  switch(inx){  
  case  0: APP_TRAF((char*)ANTO,inx,   -1,(char*)AITO,         ""); break;//�ػ�
  case  1: APP_TRAF((char*)ANRT,inx,   -2,(char*)AIRT,         ""); break;//����
  case  2: APP_TRAF((char*)ANLK,inx,   -3,(char*)AILK,         ""); break;//����
  case  3: APP_TRAF((char*)ANST,inx,   -4,(char*)AIST,         ""); break;//���� 
  case  4: APP_TRAF((char*)AN04,inx, AT04,(char*)AI04,(char*)AF04); break;//����
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
//�ҹ�ϵͳʱ��ˢ�²���
static void TimerProc(void)
{
  InitScreen();  
  GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&my_ipc);  
}
static int DaemonOnMessage(CSM_RAM* data,GBS_MSG* msg){   
  // ��������
  if(msg->msg == MSG_RECONFIGURE_REQ){
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0){                
      InitConfig();
      //���¼��ؽ����ļ�����
      if(FreeFileBuf(BirsData)) BirsData=LoadFileBuf(BIRS_FILE); 
      InitMenu();
      InitShow();
      ShowMSG(1,(int)"�����Ѹ���!");  
    }
  } 
  //�Զ����ֻ���������
  if((TASK_ENA)&&(!SUCC_HOOK)){      
      AddKeybMsgHook((void *)DaemonKeyHook);
      SUCC_HOOK = 1;
  }elif((!TASK_ENA)&&(SUCC_HOOK)){
     if(TASK_ID) CloseCSM(TASK_ID); 
     RemoveKeybMsgHook((void *)DaemonKeyHook);  
     SUCC_HOOK = 0;
  }
  if (msg->msg==MSG_IPC){
    IPC_REQ *IPC;
    if(IPC=(IPC_REQ*)msg->data0){
      if(strcmp_nocase(IPC->name_to,SCR_NAME)==0){
        switch (msg->submess){
        case UPDATE_STAT:
          #ifdef NEWSGOLD
          if (!getCpuUsedTime_if_ena()){StartCpuUsageCount();}
          #endif
          GBS_StartTimerProc(&scrTimer, REFRESH*TMR_SECOND/10, TimerProc);
        }
      }
    }
   }
  //���Թ���
  uword ScrShow;
  switch (INFO_ENA){
   case 0: ScrShow = !IsUnlocked();  break;
   case 1: ScrShow =  IsUnlocked();  break;
   case 2: ScrShow = 1;  break;
   default:ScrShow = 0;  break;
  }
  CSM_RAM *icsm;
  if (icsm=FindCSMbyID(CSM_root()->idle_id)){
    if (IsGuiOnTop(idlegui_id(icsm))&&ScrShow){
      GUI *igui=GetTopGUI();
      if(igui){      
       #ifdef ELKA
        {void *ScrCanvas = BuildCanvas();
       #else
        void *idata  = GetDataOfItemByID(igui,2);
        if(idata)
        {void *ScrCanvas = ((void **)idata)[DISPLACE_OF_IDLECANVAS/4];         
       #endif
        InitScreen();//�Զ��幦����ʾ
        //DrawCanvas(ScrCanvas, 0,YDISP,ScreenW()-1,ScreenH()-1, 1);
        for (int i=0; i<(sizeof(IDS)/sizeof(TSCR)); i++){
        if (IDS[i].Show){
          DrawCanvas(ScrCanvas, IDS[i].l,IDS[i].t,IDS[i].r,IDS[i].b, 1);
          DrawString(IDS[i].ws,IDS[i].l,IDS[i].t,IDS[i].r,IDS[i].b,IDS[i].Font,32,IDS[i].Pen,IDS[i].Brush);
         }          
        }
       }  
      }
    }
  }
  //��ȡ������Ϣ
  TTime t; TDate d; 
  GetDateTime(&d,&t);
  int Week = GetWeek(&d);  
  if((ALRM_ENA)&&(!RING_ID)&&(!IsCalling())&&(t.sec<=10)){//����
    char cTime[12];
    sprintf(cTime,"R%02d:%02d.",t.hour,t.min);
    RING_ID=ExcuteRing(cTime,Week);
  }    
  if((msg->msg==MSG_PLAYFILE_REPORT)&&(ALRM_ENA)&&(RING_ID)){//ֹͣ����
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if (pmsg->handler==RING_ID){
      if (pmsg->cmd==M_SAE_PLAYBACK_ERROR || pmsg->cmd==M_SAE_PLAYBACK_DONE){  
       CloseTask();
      }
    }  
   }
  //�Զ��ػ� 
   if((SHUT_ENA)&&(SHUT_TIME.hour==t.hour)&&(SHUT_TIME.min==t.min)){
     CloseCSM(DMON_ID);
     SwitchPhoneOff();
   }
  //�Զ�����
   if((ROOT_ENA)&&(ROOT_TIME.hour==t.hour)&&(ROOT_TIME.min==t.min)){
     CloseCSM(DMON_ID);
     RebootPhone();
   }
 return(1);
}  

static void DaemonOnCreate(CSM_RAM *data){
  for (int i=0;i<MAX_IDS; i++) IDS[i].ws=AllocWS(50);
  BirsData=LoadFileBuf(BIRS_FILE);
  NongLi.year=AllocWS(50);
  NongLi.mday=AllocWS(50);
  InitMenu();
  InitShow();
  if(INFO_ENA) GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&my_ipc);
}
static void DaemonKiller(void){  
  extern void *ELF_BEGIN;  
  if(SUCC_HOOK) RemoveKeybMsgHook((void *)DaemonKeyHook);  
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
static void DaemonOnClose(CSM_RAM *csm){  
  if(IsTimerProc(&scrTimer))GBS_DelTimer(&scrTimer);
  for (int i=0;i!=MAX_IDS; i++) FreeWS(IDS[i].ws);
  FreeFileBuf(BirsData);
  FreeWS(NongLi.year);
  FreeWS(NongLi.mday);
  SUBPROC((void *)DaemonKiller);  
}
static uword DaemonBody[LEN];
static const struct{
  CSM_DESC CSM;
  WSHDR NAME;
}MAIN_CSM={{
  DaemonOnMessage,
  DaemonOnCreate,
#ifdef NEWSGOLD
  0,0,0,0,
#endif
  DaemonOnClose,
  sizeof(DAEMON_CSM),
  1,
  &MINUSLL},{
  DaemonBody,
  NAMECSM_MAGIC1,
  NAMECSM_MAGIC2,
  0x0,
  139}
};

static void UpdateCSMName(void){ 
  wsprintf((WSHDR *)(&MAIN_CSM.NAME),PFMT_STR,(char *)(strrchr(ANTO,'-')+1));
}

int main()
{
  InitConfig();  
  LockSched();    
  UpdateCSMName();
  char DUMMY[sizeof(DAEMON_CSM)];    
  CSM_RAM *save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;  
  DMON_ID=CreateCSM(&MAIN_CSM.CSM,DUMMY,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  if(TASK_ENA){      
     AddKeybMsgHook((void *)DaemonKeyHook);   
     SUCC_HOOK = 1;
  }
  UnlockSched();
  return 0;
}
