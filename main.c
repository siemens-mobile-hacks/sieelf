#include <swilib.h>
#include <cfg_items.h>
#include <sieapi.h>
#include "scrtool.h"
#include "conf_loader.h"

const int minus11=-11;
const char ipc_my_name[]=SCRTOOL_NAME;
TSCR IDS[MAX_IDS];
int Count,Seled;
TAPP APP[MAX_APP];
TRect pos,txt,ico;
TNongLi NongLi;
TBIR    BIR[MAX_BIR];
TBIRS   BIRS;
int MAINCSM_ID = 0;
int SUCCED_HOOK= 0;
int MenuActive = 0;
int auto_close = 0;
GBSTMR barTimer;
GBSTMR txtTimer;
const IPC_REQ my_ipc={ipc_my_name, ipc_my_name, NULL};

//��ʼ��������ʾ����
void InitBir(void)
{ 
  BIR[0].tp = BIRT01;
  utf8_2ws(BIR[0].dt,BIRD01,strlen(BIRD01));
  utf8_2ws(BIR[0].ws,BIRS01,strlen(BIRS01));
  BIR[1].tp = BIRT02;
  utf8_2ws(BIR[1].dt,BIRD02,strlen(BIRD02));
  utf8_2ws(BIR[1].ws,BIRS02,strlen(BIRS02));
  BIR[2].tp = BIRT03;
  utf8_2ws(BIR[2].dt,BIRD03,strlen(BIRD03));
  utf8_2ws(BIR[2].ws,BIRS03,strlen(BIRS03));
  BIR[3].tp = BIRT04;
  utf8_2ws(BIR[3].dt,BIRD04,strlen(BIRD04));
  utf8_2ws(BIR[3].ws,BIRS04,strlen(BIRS04));
  BIR[4].tp = BIRT05;
  utf8_2ws(BIR[4].dt,BIRD05,strlen(BIRD05));
  utf8_2ws(BIR[4].ws,BIRS05,strlen(BIRS05));
  BIR[5].tp = BIRT06;
  utf8_2ws(BIR[5].dt,BIRD06,strlen(BIRD06));
  utf8_2ws(BIR[5].ws,BIRS06,strlen(BIRS06));
  BIR[6].tp = BIRT07;
  utf8_2ws(BIR[6].dt,BIRD07,strlen(BIRD07));
  utf8_2ws(BIR[6].ws,BIRS07,strlen(BIRS07));
  BIR[7].tp = BIRT08;
  utf8_2ws(BIR[7].dt,BIRD08,strlen(BIRD08));
  utf8_2ws(BIR[7].ws,BIRS08,strlen(BIRS08));
}

void InitIDS(void);
void TimerProc(void)
{
  InitIDS();
  InitBir();
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

void FillIDS(TSCR *Info,int x_start,int y_start, int font,const char *color,const char *colorframe)
{  
  Info->rc.x=x_start;
  Info->rc.y=y_start;
  Info->rc.x2=x_start+get_string_width(Info->ws,font);
  Info->rc.y2=y_start+GetFontYSIZE(font);
  Info->font=font;
  memcpy(Info->pen,color,4);
  memcpy(Info->frame,colorframe,4);
}

void InitIDS(void)
{
  RAMNET *net_data;
  int c;
  char cWeek[16];
  char cData[16];
  const char cWeekName[4][7][16]={
    {"MONDAY","TUESDAY","WEDNESDAY","THUSDAY","FRIDAY","SATURDAY","SUNDAY"},
    {"MON","TUES","WED","THU","FRI","SAT","SUN"},
    {"Monday","Tuesday","Wednesday","Thusday","Friday","Saturday","Sunday"},
    {"Mon","Tues","Wed","Thu","Fri","Sat","Sun"}};
  const word XINGQI[] = {0x661F, 0x671F, 0}; //����
  const word UniNum[] = {0x4E00,0x4E8C,0x4E09,0x56DB,0x4E94,0x516D,0x65E5,0};//һ������������
  const word UniData[] = {0x5E74,0x6708,0x65E5,0};//������
  const word UniTime[] = {0x70B9,0x5206,0x79D2,0x4E0A,0x4E0B,0x5348,0};//�����������
  word UniToday[3];
  char cDataFmt[8][16] = {
    "%02d/%02d/%02d",
    "%02d-%02d-%02d",
    "%02d.%02d.%02d",
    "%02d %02d %02d",
    "%02d/%02d",
    "%02d-%02d",
    "%02d.%02d",
    "%02d %02d",};
  TTime tt;
  TDate d;
  if (TEMP_ENA){
    IDS[0].enabled=1;
    c=GetAkku(1,3)-0xAAA+15;
    wsprintf(IDS[0].ws,TEMP_FMT,c/10,c%10);
    FillIDS(&IDS[0],TEMP_X,TEMP_Y,TEMP_FONT,TEMP_COLORS,TEMP_FCOLOR);
  } else { IDS[0].enabled=0; }
  
  if (VOLT_ENA){
    IDS[1].enabled=1;
    c=GetAkku(0,9);
    wsprintf(IDS[1].ws,VOLT_FMT,c/1000,(c%1000)/10);
    FillIDS(&IDS[1],VOLT_X,VOLT_Y,VOLT_FONT,VOLT_COLORS,VOLT_FCOLOR);
  } else { IDS[1].enabled=0; }
  
  if (RAM_ENA){
    IDS[2].enabled=1;
    c=GetFreeRamAvail();
    wsprintf_bytes(IDS[2].ws,c);
    FillIDS(&IDS[2],RAM_X,RAM_Y,RAM_FONT,RAM_COLORS,RAM_FCOLOR);  
  } else { IDS[2].enabled=0; }
  
  if(WEEK_ENA){
    IDS[3].enabled=1;
    GetDateTime(&d,&tt);
    c = GetWeek(&d);
    if(WEEK_FMT <4)
    {
      for(int iloop = 0;iloop < 16;iloop++){
        cWeek[iloop] = cWeekName[WEEK_FMT][c][iloop];        
      }
      wsprintf(IDS[3].ws,cWeek,c);
    } else {
      CutWSTR(IDS[3].ws,0);
      UniToday[0] = UniNum[c];
      if(WEEK_FMT==4)
         BSTRAdd(IDS[3].ws->wsbody, XINGQI, 2);
      BSTRAdd(IDS[3].ws->wsbody,UniToday, 1);      
    }
    FillIDS(&IDS[3],WEEK_X,WEEK_Y,WEEK_FONT,WEEK_COLORS,WEEK_FCOLOR);
  } else { IDS[3].enabled=0; }
  
  if(DATE_ENA){
    IDS[4].enabled=1;
    GetDateTime(&d,&tt);  
    for(int iloop = 0;iloop < 16;iloop++){
      cData[iloop] = cDataFmt[DATE_FMT][iloop];        
    }
    if(DATE_FMT < 4)
      wsprintf(IDS[4].ws,cData,d.year,d.month,d.day);
    else if(DATE_FMT <8)
      wsprintf(IDS[4].ws,cData,d.month,d.day);
    else {
      CutWSTR(IDS[4].ws,0);
      if(DATE_FMT == 8) {
        wsprintf(IDS[4].ws,"%04d",d.year);
        UniToday[0] = UniData[0];
        BSTRAdd(IDS[4].ws->wsbody,UniToday, 1);
      }      
      UniToday[0] = d.month/10 + 0x30;
      UniToday[1] = d.month%10 + 0x30;
      BSTRAdd(IDS[4].ws->wsbody,UniToday, 2);
      UniToday[0] = UniData[1];
      BSTRAdd(IDS[4].ws->wsbody,UniToday, 1);
      
      UniToday[0] = d.day/10 + 0x30;
      UniToday[1] = d.day%10 + 0x30;
      BSTRAdd(IDS[4].ws->wsbody,UniToday, 2);
      UniToday[0] = UniData[2];
      BSTRAdd(IDS[4].ws->wsbody,UniToday, 1);      
    }
    FillIDS(&IDS[4],DATE_X,DATE_Y,DATE_FONT,DATE_COLORS,DATE_FCOLOR);
  } else { IDS[4].enabled=0; }
  
  if(TIME_ENA){
    IDS[5].enabled=1;
    GetDateTime(&d,&tt);
    switch(TIME_FMT) {
    case 0: wsprintf(IDS[5].ws,"%02d:%02d",tt.hour,tt.min); break;
      
    case 1:
      if(tt.hour <= 12) {
        wsprintf(IDS[5].ws,"AM %02d:%02d",tt.hour,tt.min);
      } else {
        tt.hour = tt.hour - 12;
        wsprintf(IDS[5].ws,"PM %02d:%02d",tt.hour,tt.min);
      } break;
      
    case 2:
      if(tt.hour > 12) tt.hour = tt.hour - 12;
      wsprintf(IDS[5].ws,"%02d:%02d",tt.hour,tt.min);
      break;
      
    case 3: wsprintf(IDS[5].ws,"%02d:%02d:%02d",tt.hour,tt.min,tt.sec); break;
      
    case 4:
      if(tt.hour <= 12){
        wsprintf(IDS[5].ws,"AM %02d:%02d:%02d",tt.hour,tt.min,tt.sec);
      } else {
        tt.hour = tt.hour - 12;
        wsprintf(IDS[5].ws,"PM %02d:%02d:%02d",tt.hour,tt.min,tt.sec);
      } break;
    case 5:
      wsprintf(IDS[5].ws,"%02d",tt.hour);
      UniToday[0] = UniTime[0];
      BSTRAdd(IDS[5].ws->wsbody,UniToday, 1);
      
      UniToday[0] = tt.min/10 + 0x30;
      UniToday[1] = tt.min%10 + 0x30;
      BSTRAdd(IDS[5].ws->wsbody,UniToday, 2);
      UniToday[0] = UniTime[1];
      BSTRAdd(IDS[5].ws->wsbody,UniToday, 1);
      break;
    case 6:
      wsprintf(IDS[5].ws,"%02d",tt.hour);
      UniToday[0] = UniTime[0];
      BSTRAdd(IDS[5].ws->wsbody,UniToday, 1);
      
      UniToday[0] = tt.min/10 + 0x30;
      UniToday[1] = tt.min%10 + 0x30;
      BSTRAdd(IDS[5].ws->wsbody,UniToday, 2);
      UniToday[0] = UniTime[1];
      BSTRAdd(IDS[5].ws->wsbody,UniToday, 1);
      
      UniToday[0] = tt.sec/10 + 0x30;
      UniToday[1] = tt.sec%10 + 0x30;
      BSTRAdd(IDS[5].ws->wsbody,UniToday, 2);
      UniToday[0] = UniTime[2];
      BSTRAdd(IDS[5].ws->wsbody,UniToday, 1);
      break;
    default:
      break;
      
    }   
    FillIDS(&IDS[5],TIME_X,TIME_Y,TIME_FONT,TIME_COLORS,TIME_FCOLOR);
  } else { IDS[5].enabled=0; }
  
  if (TEXT_ENA){
    IDS[6].enabled=1;
    utf8_2ws(IDS[6].ws,TEXT_FMT,strlen(TEXT_FMT));
    FillIDS(&IDS[6],TEXT_X,TEXT_Y,TEXT_FONT,TEXT_COLORS,TEXT_FCOLOR);
  } else { IDS[6].enabled=0; }    
  
  if (NongLiNian_ENA){
    IDS[7].enabled=1;
    CutWSTR(IDS[7].ws,0);
    GetDateTime(&d,&tt); 
    GetDayOf(d,&NongLi);
    memcpy(IDS[7].ws->wsbody,NongLi.year->wsbody,16);
    FillIDS(&IDS[7],NongLiNian_X,NongLiNian_Y,NongLiNian_FONT,NongLiNian_COLORS,NongLiNian_FCOLOR);
  } else { IDS[7].enabled=0; }    

  if (NongLiDATE_ENA){
    IDS[8].enabled=1;
    CutWSTR(IDS[8].ws,0);
    GetDateTime(&d,&tt); 
    GetDayOf(d,&NongLi);
    memcpy(IDS[8].ws->wsbody,NongLi.monthday->wsbody,16);
    FillIDS(&IDS[8],NongLiDATE_X,NongLiDATE_Y,NongLiDATE_FONT,NongLiDATE_COLORS,NongLiDATE_FCOLOR);
  } else { IDS[8].enabled=0; }   
  
  if(NET_ENA){
    IDS[9].enabled=1;
    net_data=RamNet();
    c=(net_data->ch_number>=255)?'=':'-';
    wsprintf(IDS[9].ws,NET_FMT,c,net_data->power);
    FillIDS(&IDS[9],NET_X,NET_Y,NET_FONT,NET_COLORS,NET_FCOLOR);
  } else { IDS[9].enabled=0; }
  
  if (CAP_ENA){
    IDS[10].enabled=1;
    c=*RamCap();
    wsprintf(IDS[10].ws,CAP_FMT,c);
    FillIDS(&IDS[10],ACCU_X,ACCU_Y,ACCU_FONT,ACCU_COLORS,ACCU_FCOLOR);
  } else { IDS[10].enabled=0; }
  
  if (CPU_ENA){
    IDS[11].enabled=1;
    c=GetCPULoad();
    if(c==100) c=99;
    wsprintf(IDS[11].ws,CPU_FMT,c);
    FillIDS(&IDS[11],CPU_X,CPU_Y,CPU_FONT,CPU_COLORS,CPU_FCOLOR);
  } else { IDS[11].enabled=0; }

  if (GPRS_ENA){
    IDS[12].enabled=1;
    //RefreshGPRSTraffic();
    c=*GetGPRSTrafficPointer();
    wsprintf_bytes(IDS[12].ws,c);
    FillIDS(&IDS[12],GPRS_X,GPRS_Y,GPRS_FONT,GPRS_COLORS,GPRS_FCOLOR);
  } else { IDS[12].enabled=0; }
  
  if(BIR_ENA){
    char dta[16],dtb[16];  
    CutWSTR(IDS[13].ws,0);
    GetDateTime(&d,&tt);      
    GetDayOf(d,&NongLi);
    wsprintf(BIRS.nd,"%02d.%02d",d.month,d.day); 
    memcpy(BIRS.od->wsbody,NongLi.monthday->wsbody,16);    
    int i=0;
    while(i<MAX_BIR){
      switch(BIR[i].tp){
       case 0:ws_2str(BIRS.nd,(char*)dta,16);break;
       case 1:ws_2str(BIRS.od,(char*)dta,16);break;
      }
      ws_2str(BIR[i].dt,(char*)dtb,16); 
      IDS[13].enabled=extstrcmp(dta,dtb);
      if(IDS[13].enabled){
        wstrcpy(IDS[13].ws,BIR[i].ws);
        break;
      }  
      i++;
    }     
    FillIDS(&IDS[13],BIR_X,BIR_Y,BIR_FONT,BIR_COLORS,BIR_FCOLOR);
  } else { IDS[13].enabled=0; }
}
//�˵�����
const char AN00[LEN]="\xE9\x85\x8D\xE7\xBD\xAE\x2D\xE6\xA1\x8C\xE9\x9D\xA2\xE5\xB7\xA5\xE5\x85\xB7\x76\x32\x2E\x30\x35";
const char AVER[LEN]="\xE6\xA1\x8C\xE9\x9D\xA2\xE5\xB7\xA5\xE5\x85\xB7\x76\x32\x2E\x30\x35";

void APP_TRAF(const char *Name, int inx, int type,char *pic,char *file)
{
  utf8_2ws(APP[inx].ws,Name,strlen(Name));
  APP[inx].type = type;
  APP[inx].pic  = pic;
  APP[inx].file = file;
  if ((file)&&(strlen(file)))Count+=1;
}

void CreateAppInfo(int inx)
{ 
  switch(inx)
  {  
  case  0: APP_TRAF(AN00,inx,   -1,(char*)AI00, ""); break; 
  case  1: APP_TRAF(AN01,inx, AT01,(char*)AI01,(char*)AF01); break;
  case  2: APP_TRAF(AN02,inx, AT02,(char*)AI02,(char*)AF02); break;
  case  3: APP_TRAF(AN03,inx, AT03,(char*)AI03,(char*)AF03); break;
  case  4: APP_TRAF(AN04,inx, AT04,(char*)AI04,(char*)AF04); break;
  case  5: APP_TRAF(AN05,inx, AT05,(char*)AI05,(char*)AF05); break;
  case  6: APP_TRAF(AN06,inx, AT06,(char*)AI06,(char*)AF06); break;
  case  7: APP_TRAF(AN07,inx, AT07,(char*)AI07,(char*)AF07); break;
  case  8: APP_TRAF(AN08,inx, AT08,(char*)AI08,(char*)AF08); break;
  case  9: APP_TRAF(AN09,inx, AT09,(char*)AI09,(char*)AF09); break;
  case 10: APP_TRAF(AN10,inx, AT10,(char*)AI10,(char*)AF10); break;
  case 11: APP_TRAF(AN11,inx, AT11,(char*)AI11,(char*)AF11); break;
  case 12: APP_TRAF(AN12,inx, AT12,(char*)AI12,(char*)AF12); break;
  }  
}

//�������ļ�
void OpenBCFGFile(void)
{ 
  extern const char *successed_config_filename;
  WSHDR *ws = AllocWS(150);
  str_2ws(ws, successed_config_filename, 128);
  ExecuteFile(ws, 0, 0);
  FreeWS(ws);
  GeneralFuncF1(1);
}

void CloseMenu(void)
{
  GBS_DelTimer(&barTimer);
  CloseCSM(MAINCSM_ID); //�ر�GUI����
  MAINCSM_ID=0;
  MenuActive=0;
  auto_close=0;
  RefreshGUI();
}

//���ܶ�λ
void DoIt(int inx) 
{ 
  CloseMenu();
  char *s = APP[inx].file;
  switch(APP[inx].type)
  {
   case -1: OpenBCFGFile(); break;
   case  0: RunAPP(s); break;
   case  1: RunCUT(s); break;
   case  2: RunADR(s); break;
  }
}

int size=32;

void InitMenu(int active)
{   //ȫ������
   Seled=SELECTED;
   Count=1;   
   for(int i=0;i<MAX_APP;i++) CreateAppInfo(i); 
   int TextH = GetFontYSIZE(APPTEXT_FONT)+4;
   if (TextH < SoftkeyH()) TextH = SoftkeyH();
   int BarsH = size + TextH;
   switch(BARPOS){
    case 0:{
    pos.l = 0;
    pos.r = ScreenW()-1;
    pos.t = OFFSET+YDISP;
    pos.b = OFFSET+BarsH+YDISP;    
    //�ı�����    
    txt.l = pos.l;
    txt.r = pos.r;
    txt.t = pos.t;    
    txt.b = pos.t+TextH;
    //ͼ��λ��
    ico.l = pos.l;
    ico.t = pos.t+TextH;
    ico.r = pos.l+size;
    ico.b = pos.b;  
    };break;
   case 1:{
    pos.l = 0;
    pos.r = ScreenW()-1;
    pos.t = ScreenH()-BarsH-OFFSET-1;
    pos.b = ScreenH()-OFFSET-1;    
    //�ı�����    
    txt.l = pos.l;
    txt.r = pos.r;
    txt.t = pos.b-TextH;    
    txt.b = pos.b;
    //ͼ��λ��
    ico.l = pos.l;
    ico.t = pos.t;
    ico.r = pos.l+size;
    ico.b = pos.t+size;  
   }; break;
  }  
  MenuActive=active;
}
void DrawPanel(void)
{  
 GBS_StartTimerProc(&barTimer,10,DrawPanel);
 #ifdef ELKA
  {void *canvasAPPS = BuildCanvas();
 #else
  void *idata = GetDataOfItemByID(GetTopGUI(), 2);
  if (idata){
  void *canvasAPPS = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
 #endif     
  DrawCanvas(canvasAPPS, pos.l, pos.t, pos.r, pos.b, 1);  
  DrawRoundedFrame( txt.l, txt.t, txt.r, txt.b, 0, 0, 0, cfgPanBorderCol, cfgPanBGCol ); 
  int y = 0; 
  int z = 0;  
  int i = 0;
  int n = (pos.r-pos.l)/size;
  int m = size + (pos.r-pos.l-size*n)/(n-1);
  int x = ((pos.r-pos.l)/m)-1;
  int ts=(txt.b-txt.t-GetFontYSIZE(APPTEXT_FONT))/2;  
  //��ҳ��ʾ����
  if(Count>((pos.r-pos.l)/(m))) i = Seled - ((pos.r-pos.l)/(m))+1; else i=0;  
  if ( i < 0 ) i = 0;  
  while ( i < Count ){  
    const char *s=APP[i].pic;
    if (!((s)&&(strlen(s)))) s=AINO;
   // DrawCanvas(canvasAPPS, y+ico.l, ico.t, y+ico.r, ico.b, 1); 
    if (i == Seled){                    
       DrawRoundedFrame(y+ico.l, ico.t, y+ico.r, ico.b, 2, 2, 0, cfgBookBorderCol, cfgBookBGCol ); 
       DrawString(APP[i].ws, txt.l+1, txt.t+ts, txt.r-1, txt.b-ts, APPTEXT_FONT, TEXT_OUTLINE,APPTEXT_COLORS, APPTEXT_FCOLOR);    
    }
    int picw = (size-GetImgWidth((int)s))/2; if(picw<0)picw=0;
    int pich = (size-GetImgHeight((int)s))/2; if(pich<0)pich=0;    
    DrawImg(y+ico.l+picw, ico.t+pich, (int)s);    
    y += m;
    i++;
    z++;
    if ( z > x ) break;
  }
  }  
 //�Զ��رղ˵�
 if((++auto_close>=AUTO_CLOSE*TMR_SECOND/10)&&(MenuActive)&&(MAINCSM_ID)) CloseMenu();
}

void OnRedraw(GUI *data)
{
  if(SUCCED_HOOK&&MENU_ENA&&MenuActive) DrawPanel();
}

void onCreate(GUI *data, void *(*malloc_adr)(int))
{
  data->state=1;
}

void onClose(GUI *data, void (*mfree_adr)(void *))
{
  data->state=0;
}

void onFocus(GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->state=2;
}

void onUnfocus(GUI *data, void (*mfree_adr)(void *))
{
  if (data->state!=2) return;
  data->state=1;  
}

int OnKey(GUI *data, GUI_MSG *msg)
{ 
  if(SUCCED_HOOK||MENU_ENA)
  {
  DirectRedrawGUI();

  if ((msg->gbsmsg->msg==KEY_DOWN))
  {
    if(msg->gbsmsg->submess==EXIT_BTN) CloseMenu();
    if(IsUnlocked()){
     switch(msg->gbsmsg->submess){     
      case RIGHT_BUTTON:  
      case UP_BUTTON:{auto_close=0; if (++Seled >= Count) Seled=0;} break;
      case LEFT_BUTTON: 
      case DOWN_BUTTON:{auto_close=0; if (--Seled<0) Seled=Count-1;} break;     
      case ENTER_BUTTON: DoIt(Seled); break;
     }
    }
   }
  }
  return(0);
}

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
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0, 0, 0, 0};

void maincsm_onguicreate(CSM_RAM *data)
{
  GUI *main_gui=malloc(sizeof(GUI));
  MAIN_CSM_GUI *csm=(MAIN_CSM_GUI*)data;
  zeromem(main_gui,sizeof(GUI));
  main_gui->canvas=(void *)(&Canvas);
  //main_gui->flag30=2;
  main_gui->methods=(void *)gui_methods;
  main_gui->item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

#ifndef DAEMON
static void ELF_KILLER(void)
{
  extern void *ELF_BEGIN;
  if(my_pic) deleteIMGHDR(my_pic);  
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
  MAIN_CSM_GUI *csm=(MAIN_CSM_GUI*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
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
}MAINCSM =
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
sizeof(MAIN_CSM_GUI),
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

#ifdef DAEMON
void ShowMenu()
{
  LockSched();
  char dummy[sizeof(MAIN_CSM_GUI)];
  InitMenu(1);
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,2);
  UnlockSched();
}

//�����ҹ�
int my_keyhook(int key, int m)
{
  extern const int MODE_KBD;
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&IsUnlocked()&&(m==MODE_KBD+0x193))
  {
    if (key==CALL_BTN) ShowMenu();
   }
  return 0;
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  #define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM *icsm;
  if(msg->msg == MSG_RECONFIGURE_REQ) // Perechityvanie configuration reported
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {      
      ShowMSG(1,(int)"ScrTool updated!");
      InitConfig();
      InitMenu(0);
      InitBir();
    }
  } 
  //�Զ����ֻ���������
  if ((MENU_ENA)&&(!SUCCED_HOOK))
  {      
      AddKeybMsgHook((void *)my_keyhook);
      SUCCED_HOOK = 1;
  }
  else if((!MENU_ENA)&&(SUCCED_HOOK))
  {
     if(MAINCSM_ID) CloseCSM(MAINCSM_ID); 
     RemoveKeybMsgHook((void *)my_keyhook);  
     SUCCED_HOOK = 0;
  }
  //�Զ��幦����ʾ
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
        switch (msg->submess)
        {
        case UPDATE_STAT:
          #ifdef NEWSGOLD
          if (!getCpuUsedTime_if_ena())
          {
            StartCpuUsageCount();
          }
          #endif
          GBS_StartTimerProc(&txtTimer, REFRESH*TMR_SECOND/10, TimerProc);
        }
      }
    }
  }
  icsm=FindCSMbyID(CSM_root()->idle_id);
  if (icsm)
  {
    if (IsGuiOnTop(idlegui_id(icsm))) //���� IdleGui �� ����?����?
    {
      GUI *igui=GetTopGUI();
      if (igui) //?�� ����������
      {
        InitIDS();
        #ifdef ELKA
        { void *canvastext = BuildCanvas();
        #else
          void *idata = GetDataOfItemByID(igui, 2);
        if (idata){
          void *canvastext = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
        #endif
          for (int inx=0; inx<(sizeof(IDS)/sizeof(TSCR)); inx++)
          {
            if (IDS[inx].enabled)
            {
          DrawCanvas(canvastext, IDS[inx].rc.x, IDS[inx].rc.y, IDS[inx].rc.x2, IDS[inx].rc.y2, 1);
          DrawString(IDS[inx].ws, IDS[inx].rc.x, IDS[inx].rc.y, IDS[inx].rc.x2+10, IDS[inx].rc.y2, IDS[inx].font,
          32,IDS[inx].pen, IDS[inx].frame);         
            }
          }
        }
      }
    }
  }
  return(1);
}  

static void Killer(void)
{
  extern void *ELF_BEGIN;
  if(MAINCSM_ID) CloseCSM(MAINCSM_ID);
  if(SUCCED_HOOK) RemoveKeybMsgHook((void *)my_keyhook);  
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_oncreate(CSM_RAM *data)
{
  for (int i=0;i<MAX_IDS; i++) IDS[i].ws=AllocWS(50);
  for (int i=0;i<MAX_APP; i++) APP[i].ws=AllocWS(50);
  for (int i=0;i<MAX_BIR; i++){BIR[i].ws=AllocWS(50);BIR[i].dt=AllocWS(50);}
  BIRS.nd=AllocWS(50);
  BIRS.od=AllocWS(50);
  NongLi.year=AllocWS(50);
  NongLi.monthday=AllocWS(50);
  GBS_SendMessage(MMI_CEPID,MSG_IPC,UPDATE_STAT,&my_ipc);
}

static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&txtTimer);
  for (int i=0;i!=MAX_IDS; i++) FreeWS(IDS[i].ws);
  for (int i=0;i!=MAX_APP; i++) FreeWS(APP[i].ws);
  for (int i=0;i!=MAX_BIR; i++){FreeWS(BIR[i].ws);FreeWS(BIR[i].dt);}
  FreeWS(NongLi.year);
  FreeWS(NongLi.monthday);
  FreeWS(BIRS.nd);
  FreeWS(BIRS.od);
  SUBPROC((void *)Killer);  
}

static unsigned short maincsm_name_body[LEN];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM_d =
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

static void UpdateCSMname(void)
{   
  utf8_2ws((WSHDR *)(&MAINCSM_d.maincsm_name),AVER,strlen(AVER));
  //wsprintf((WSHDR *)(&MAINCSM_d.maincsm_name),SCRTOOL_NAME);
}
#endif

int main()
{
  LockSched();
  InitConfig();  
#ifdef DAEMON
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  
  #ifdef NEWSGOLD
    save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
    CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
    CreateCSM(&MAINCSM_d.maincsm,dummy,0);
    CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
    if (MENU_ENA)
    {      
      AddKeybMsgHook((void *)my_keyhook);   
      SUCCED_HOOK = 1;
    }
  #else
      if ((!AddKeybMsgHook_end((void *)my_keyhook))&&(!SUCCED_HOOK)) 
      {
        ShowMSG(1, (int) "ScrTool failed!"); 
        SUBPROC((void *)Killer);
      }
      else
      {
        save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
        CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
        CreateCSM(&MAINCSM_d.maincsm,dummy,0);
        CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
      }
  #endif   
#else 
  char dummy[sizeof(MAIN_CSM_gui)];
  UpdateCSMname();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
#endif    
  UnlockSched();
  return 0;
}
