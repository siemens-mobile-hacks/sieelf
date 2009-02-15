#include <swilib.h>
#include <cfg_items.h>
#include <sieapi.h>
#include <playsound.h>
#include "scrtool.h"
#include "conf_loader.h"
//ע������������ȫ��̨���а汾
static char ANST[]="�������";//����
static char ANTO[]="�ػ�-õ��v2.27";//�ػ�
static char ANRT[]="�����ֻ�";//����
static char ANLK[]="��ס����";//����
static char TASK[]="����˵�";//����˵�
static char ALRM[]="�������";//���ӽ���
static const IPC_REQ SCR_IPC={SCR_NAME, SCR_NAME, NULL};
static const int MINUSLL=-11;
static int   TASK_ID   = 0;//��¼ͼ�ν���
static int   RING_ID   = 0;//��¼��������
static char  TASK_STATE;//��¼���н�������,1Ϊ�˵�,2Ϊ��ݲ˵�,3Ϊ���ӽ���
static ubyte AUTO_EXIT = 0;//��¼�Զ��˳��˵�״̬
static ubyte SUCC_HOOK = 0;//��¼HOOK״̬
static int   mCount,mSelet,aCur;
//�������ݻ�����
static char *Gala;
//���ò˵�
static char  PATHS[64],TITLE[32];
static TSCR  SCR[MAX_SCR];
static TAPP  APP[MAX_APP];
static TLunar NLi;
static GBSTMR tskTimer,scrTimer;
static short OLScr;//��Ļ����ԭֵ
static TTime t; 
static TDate d;
static short week=0;
static short SWYD=0;

CSM_DESC  icsmd;
//CSM_DESC* ocsmd;
int  (*OICSMOnMessage)(CSM_RAM*,GBS_MSG*);
void (*OICSMOnClose)(CSM_RAM*);
//�˵�������Ϣ
HEADER_DESC MENU_HDR={0,0,0,0,NULL,(int)TITLE,LGP_NULL};
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
  if(cmd==3){ 
    FreeFile(FileList);
  }  
}
//�˵��ػ��б�
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
//���������ļ�
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
//�������˵�
static int BrowserFileMenu(){ 
  TFile *sbtop=FindBCFGFile();
  patch_header(&MENU_HDR);
  return CreateMenu(0,0,&MENU_STRUCT,&MENU_HDR,0,FileCount(sbtop),sbtop,0);
}
//�������ò˵�
//��ʼ��������ʾ����
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
//��ʾ������ɫ��λ����ʾ��
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


//�˵�����
static void APP_TRAF(char *Name, int i, int Type,char *Pic,char *File){
  APP[i].Type = Type;
  APP[i].Pic  = Pic;
  APP[i].File = File;
  APP[i].Name = Name;
  if((File)&&(strlen(File)))mCount+=1;
}
//��������ʾ���ݽ��в�ʼ��
static void InitScreen(void){  
  if(SCR[0].Show){//��ʾ�¶���Ϣ 
    int c=GetAkku(1,3)-0xAAA+15;
    wsprintf(SCR[0].WS,"%d.%d�C",c/10,c%10);
    FillScreen(&SCR[0],TEMP_X,TEMP_Y);
  }   
  if(SCR[1].Show){//��ʾ��ѹ��Ϣ    
    if(VOLT_TY==0){
      int c=GetAkku(0,9);
      wsprintf(SCR[1].WS,"%d.%02dV",c/1000,(c%1000)/10);
    }elif(VOLT_TY==1){
      wsprintf(SCR[1].WS,"%3d%%",*RamCap());
    }
    FillScreen(&SCR[1],VOLT_X,VOLT_Y);
  }
  if(SCR[2].Show){//��ʾʣ����Ϣ  
    wsprintf_bytes(SCR[2].WS,GetFreeRamAvail());
    FillScreen(&SCR[2],RAMT_X,RAMT_Y);  
  } 
  if(SCR[3].Show){//��ʾ������Ϣ
    wsprintf(SCR[3].WS,PFMT_STR,TEXT_CP);
    FillScreen(&SCR[3],TEXT_X,TEXT_Y);
  }         
  if(SCR[4].Show){//��ʾ������Ϣ
    RAMNET *net_data=RamNet();
    int c=(net_data->ch_number>=255)?'=':'-';
    wsprintf(SCR[4].WS,"%c%ddB",c,net_data->power);
    FillScreen(&SCR[4],NETI_X,NETI_Y);
  }       
  if(SCR[5].Show){//��ʾCPUʹ����
    wsprintf(SCR[5].WS,"%3d%%",GetCPULoad());
    FillScreen(&SCR[5],CPUI_X,CPUI_Y);
  }       
  if(SCR[6].Show){//��ʾGPRS����
    //RefreshGPRSTraffic();
   // int c=*GetGPRSTrafficPointer();
    wsprintf_bytes(SCR[6].WS,*GetGPRSTrafficPointer());
    FillScreen(&SCR[6],GPRS_X,GPRS_Y);
  }
  //����ʱ����Ϣ
  uword UniToday[8];  
  if(SCR[7].Show){//��ʾ��ǰ����    
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
  if(SCR[8].Show){//��ʾ��ǰ����
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
  if(SCR[9].Show){//��ʾ��ǰʱ��
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
  if(SCR[10].Show){//��ʾũ����Ϣ
    CutWSTR(SCR[10].WS,0);
    GetDayOf(d,&NLi);
    if((SWYD>=0)&&(SWYD<3)){//��ʾũ������ 
      memcpy(SCR[10].WS->wsbody,NLi.year->wsbody,16);
    }elif((SWYD>=3)&&(SWYD<6)){//��ʾũ�����     
      memcpy(SCR[10].WS->wsbody,NLi.mday->wsbody,16); 
    }else{//��ʾũ������
      uword lunar;
      if(lunar=LunarHolId(d))
         LunarHolDay(SCR[10].WS,lunar);
      else
         SWYD=9;
    }
    if(SWYD++>=9)SWYD=0;
    FillScreen(&SCR[10],CHSD_X,CHSD_Y);
  }
  if(SCR[11].Show){//��ʾ��������
    char nDay[8],nRes[LEN];  
    sprintf(nDay,"N%02d.%02d:",d.month,d.day);
    MidStr(Gala,nDay,nRes);
    wsprintf(SCR[11].WS,PFMT_STR,nRes);
    FillScreen(&SCR[11],NBIR_X,NBIR_Y);
  }
  if(SCR[12].Show){//��ʾũ������      
    char oDay[8],oRes[LEN];   
    TDate o=GetOldDay(d);
    sprintf(oDay,"P%02d.%02d:",o.month,o.day);
    MidStr(Gala,oDay,oRes);
    wsprintf(SCR[12].WS,PFMT_STR,oRes);
    FillScreen(&SCR[12],OBIR_X,OBIR_Y);
  }
}

//����Ļ�ϻ����˵�ͼ��λ�ú��ı���Ϣ
static void DrawGUI(void){ 
  GBS_StartTimerProc(&tskTimer,10,DrawGUI); 
  int fSize,TextH=0;
  WSHDR *MWS=AllocWS(50);
  void *TskCanvas=BuildCanvas();
  if((SUCC_HOOK)&&(TASK_ENA)&&(TASK_STATE==SCR_TASKS))
  {//��ʼ�˵�����--------�ı�����--------
   fSize = FontType(ATEXT_FT);
   if(DEST_ENA){
    TextH = GetFontYSIZE(fSize)+4;//�ı��߶�
    if(TextH < SoftkeyH()) TextH = SoftkeyH(); 
   }
   short top=ScreenH()-TextH-OFFSET-1;//�ı�����λ�� 
   TRect tRC={0,top,ScreenW()-1,ScreenH()-OFFSET-1};//�����ı���������   
   TRect iRC={0,top-PicSize-1,PicSize-1,top-1};//����ͼ���������
   TRect fRc=iRC; 
   int y=0,z=0,i=0,n=ScreenW()/PicSize;  
   int ts=(tRC.b-tRC.t-GetFontYSIZE(fSize))/2;//�����ı���ֱƫ��  
   n = PicSize +(ScreenW()-n*PicSize)/(n-1);//����ͼ����ʾ��
   if(mCount>((ScreenW())/(n))){ i=mSelet-((ScreenW())/(n))+1; if(i<0)i=0;} else i=0;
   //--------����ͼ����ı�--
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
   //�Զ��رղ˵�
   if((++AUTO_EXIT>=AUTO_CLOSE*TMR_SECOND/5)&&(TASK_ID)) CloseTask();
   //�����˵�
  }
  else if((ALRM_ENA)&&(TASK_STATE==SCR_ALARM))
  {//���ӽ��� 
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
  //����     
   DrawString(MWS, Altxt.l+wso, Altxt.t+2, Altxt.r-wso, Altxt.b-2,fSize,1,ALRM_CTX, TRAN_CBK); 
  //ͼ��
   DrawImg(Alpic.l,Alpic.t,(uint)PIC);
  //����
   wsprintf(MWS,PFMT_STR,WeekGB[week]);
   wso=(Alarm.r-Alarm.l-PixlsWidth(MWS,fSize))/2;
   TRect Alwek={Alarm.l+wso,Altxt.b+pih,Alarm.r-wso,Altxt.b+pih+TextH}; 
   DrawString(MWS, Alwek.l, Alwek.t+2,Alwek.r,Alwek.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
  //ʱ��
   wsprintf(MWS,"%02d:%02d:%02d",t.hour,t.min,t.sec); 
   wso=(Alarm.r-Alarm.l-PixlsWidth(MWS,fSize))/2;
   TRect Altim={Alarm.l+wso,Alwek.b,Alarm.r-wso,Alwek.b+TextH}; 
   DrawString(MWS, Altim.l, Altim.t+2,Altim.r,Altim.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
  //��ʾ����
   wsprintf(MWS,"%04d%t%02d%t%02d%t",d.year,"��",d.month,"��",d.day,"��");
   wso=(Alarm.r-Alarm.l-PixlsWidth(MWS,fSize))/2;
   TRect Aldat={Alarm.l+wso,Altim.b,Alarm.r-wso,Altim.b+TextH}; 
   DrawString(MWS, Aldat.l, Aldat.t+2,Aldat.r,Aldat.b-2,fSize,1,ALRM_CTX, TRAN_CBK);
   //ѭ��ͼƬ
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
  }//�������Ӵ���
  FreeWS(MWS);
}
//�ػ���Ӧ�¼�
static void TaskRedraw(GUI *gui){
     DrawGUI();
}
//������Ӧ�¼�
static void TaskCreate(GUI *gui, void *(*malloc_adr)(int)){
  if(TASK_STATE==SCR_TASKS){//����˵�
    mSelet=0;  
  }elif(TASK_STATE==SCR_ALARM){//��������    
    OLScr=GetIlluminationDataTable()[3];
    aCur=1; 
  }  
  gui->state=1;
}
//�ر���Ӧ�¼�
static void TaskClose(GUI *gui, void(*mfree_adr)(void *)){
  gui->state=0;
}
//�۽���Ӧ�¼�
static void TaskFocus(GUI *gui, void *(*malloc_adr)(int), void(*mfree_adr)(void *)){
  gui->state=2;
}
//ȡ���۽���Ӧ�¼�
static void TaskUnfus(GUI *gui, void(*mfree_adr)(void *)){
  if(gui->state!=2) return;
  gui->state=1; 
  CloseTask();
}
//���幦��ִ�в�������
static void DoIt(int inx);
//���尴����������
static int TaskKeypress(GUI *gui, GUI_MSG *msg){ 
  if(SUCC_HOOK||TASK_ENA){
    DirectRedrawGUI();
    if((msg->gbsmsg->msg==KEY_DOWN)){    
    AUTO_EXIT=0;       
    if(msg->gbsmsg->submess==KeyButton(CALL_BTN)){//�رղ˵� 
      CloseTask(); 
      return(1);
    }    
    switch(msg->gbsmsg->submess){//ѡ������          
      case  DOWN_BUTTON://��ѡ����ѡ��      
      case RIGHT_BUTTON:if(++mSelet >=mCount)mSelet=0;break;       
      case    UP_BUTTON://��ѡ����ѡ��         
      case  LEFT_BUTTON:if(--mSelet<0)mSelet=mCount-1;break;           
      //ִ�жԾ͵Ĺ���
      case ENTER_BUTTON:if(TASK_STATE==SCR_TASKS)DoIt(mSelet); break;
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
 (void *)TaskUnfus,	//ȡ���۽�
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
//����GUI����
static void BuildGUI(short MODE,char *NAME){  
  LockSched();
  TASK_STATE=MODE;
  static char DUMMY[sizeof(TASK_GUI)];
  wsprintf((WSHDR *)(&TASK_CSM.NAME),PFMT_STR,NAME);
  TASK_ID=CreateCSM(&TASK_CSM.CSM,DUMMY,0);  
  UnlockSched();
}
//ִ��ָ��Ŀ¼
static void RunDIR(char *dir,char *name){  
  strcpy(PATHS,dir);  
  strcpy(TITLE,name);
  BuildGUI(SCR_MENUS,name);
}
//ִ�в˵�����
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
//�����Զ������Ӳ���
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
//�ҹ�ϵͳʱ��ˢ�²���
static void TimerProc(void){
  InitScreen();//�Զ��幦����ʾ  
  GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&SCR_IPC);  
}
static int DaemonOnMessage(CSM_RAM* data,GBS_MSG* msg){  
  //��ȡϵͳʱ�������,����
  GetDateTime(&d,&t);
  week = GetWeek(&d);  
  // ��������
  if(msg->msg == MSG_RECONFIGURE_REQ){
    extern const char *successed_config_filename;
    if(strcmp_nocase(successed_config_filename,(char *)msg->data0)==0){                
      InitConfig();
      //���¼��ؽ����ļ�����
      if(FreeFileBuf(Gala)) Gala=LoadFileBuf(BIRS_FILE); 
      InitMenu();
      InitShow();
      ShowMSG(1,(int)"�����Ѹ���!");  
    }
  }   
  //���þɵ���Ϣ�¼�
  int Result=OICSMOnMessage(data,msg);
  //�Զ��ػ� 
   if((SHUT_ENA)&&(SHUT_TIME.hour==t.hour)&&(SHUT_TIME.min==t.min)&&(t.sec<3)){
     SwitchPhoneOff();//�Զ��ػ���,�᲻���ͷ��ڴ�
     return(Result);
   }
  //�Զ�����
   if((ROOT_ENA)&&(ROOT_TIME.hour==t.hour)&&(ROOT_TIME.min==t.min)&&(t.sec<3)){
     RebootPhone();
     return(Result);
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
  //���Թ���  
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
       //InitScreen();//�Զ��幦����ʾ
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
  //��ȡ������Ϣ    
  if((ALRM_ENA)&&(!RING_ID)&&(!IsCalling())&&(t.sec<3)){//����
    char cTime[12];
    sprintf(cTime,"R%02d:%02d.",t.hour,t.min);
    RING_ID=ExcuteRing(cTime,week);
  }    
  if((msg->msg==MSG_PLAYFILE_REPORT)&&(ALRM_ENA)&&(RING_ID)){//ֹͣ����
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
