#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "FesRemind.h"
#include "sieapi.h"

extern void kill_data(void *p, void (*func_p)(void *));

static char zhName[] = "节日提醒";
int FirstRun = 1,cnt = 0;
unsigned int fShow;

CSM_DESC icsmd;
TTime t_time;
TDate t_date;

typedef struct{
  int enabled;
  RECT rc;
  WSHDR *ws;
  char pen[4];
  unsigned short font;
  unsigned short type;
  WSHDR wsh;
  unsigned short wsbody[WS_MAXLEN+1]; 
  unsigned int draw_flag;
  char fr_cl[4];
} TInfo;

TInfo InfoData[7];

GBSTMR mytmr;
const IPC_REQ my_ipc={
  IPC_FESREMIND_NAME,
  IPC_FESREMIND_NAME,
  NULL
};


// ----------------------------------------------------------------------------
#pragma segment="ELFBEGIN"
void ElfKiller(void)
{
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}

//搜索自定义节日操作
static int FindBirName(WSHDR* ws,const char *source,const char *sub)
{
  char *p;
  p=strstr(source,sub);
  if (p) 
  {
    wsprintf(ws,_percent_t,p+7);
    return 1;
  }
  else{
    return 0;}
}

//搜索自定义事件操作
static int FindApp(const char *source,const char *sub,char stTime[6],char enTime[6],WSHDR* ws)
{
  char *end,*pstT,*penT;
  char *src1,src2[256];
  src1 = strstr(source,sub);
  if (src1) 
  {
    end = strchr(src1,0x0A);
    strncpy(src2,src1,end - src1);
    pstT = strstr(src2,"FM");
    if (pstT)
    {
      strncpy(stTime,pstT + 2,6);
      enTime[6] = '\0';
      penT = strstr(src2,"TO");
      if (penT)
      {
        strncpy(enTime,penT + 2,6);
        enTime[6] = '\0';
        wsprintf(ws,_percent_t,penT + 9);
        return 3;
      }
      else
      {
        wsprintf(ws,_percent_t,pstT + 9);
        return 2;
      }
    }
    else 
    {
      wsprintf(ws,_percent_t,src2 + 8);
      return 1;
    }
  }
  else
  {
    return 0;
  }
}
        

void InitInfoData(void);
void TimerProc(void)
{
  cnt++;
  if (FirstRun == 1) InitInfoData();
  else if (cnt == 35)
  {
    InitInfoData();
    cnt = 0;
  }
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

void FillInfoData(TInfo *Info,int x_start,int y_start, int font,const char *color,int draw_flag,const char *fr_cl)
{  
  Info->rc.x=x_start;
  Info->rc.y=y_start;
  Info->rc.x2=x_start+Get_WS_width(Info->ws,font)+1;
  Info->rc.y2=y_start+GetFontYSIZE(font);
  Info->font=font;
  memcpy(Info->pen,color,4);
  Info->draw_flag=draw_flag;
  memcpy(Info->fr_cl,fr_cl,4);
}
  

const char weekdays1[7][5]={"MON","TUE","WED","THU","FRI","SAT","SUN"};
const char weekdays2[7][8]={"星期一","星期二","星期三","星期四","星期五","星期六","星期日"};
const char jDay[24][6]={
                        "小寒","大寒","立春","雨水","惊蛰","春分",
                        "清明","谷雨","立夏","小满","芒种","夏至",
                        "小暑","大暑","立秋","处暑","白露","秋分",
                        "寒露","霜降","立冬","小雪","大雪","冬至"}; 

void InitInfoData(void)
{
  if (fShow)
  {
      GetDateTime(&t_date,&t_time);
      char *FestaData;
      char oDian[6] = "00h00m";
      FestaData=LoadFileBuf(BIRS_FILE);

      char stTime[6],enTime[6],toDay[8],nTime[6];
      int ena1,ena2;
      sprintf(toDay,"AP%02d.%02d",t_date.month,t_date.day);
      sprintf(nTime,"%02dh%02dm",t_time.hour,t_time.min); 
      int app = FindApp(FestaData,toDay,stTime,enTime,InfoData[6].ws);
      switch(app)
       {
       case 0:
         InfoData[6].enabled = 0;
         if (FirstRun == 1) goto lb1;
         else if (strcmp(nTime,oDian) == 0) goto lb1;
         break;
       case 1:
         InfoData[6].enabled = 1;
         if (FirstRun == 1) goto lb1;
         else if (strcmp(nTime,oDian) == 0) goto lb1;
         break;
       case 2:
         if (strcmp(nTime,stTime) >= 0) InfoData[6].enabled = 1;
         else InfoData[6].enabled = 0;
         if (FirstRun == 1) goto lb1;
         else 
           if ((strcmp(nTime,oDian) == 0) || (strcmp(nTime,stTime) == 0)) goto lb1;
         break;
       case 3:
         ena1 = strcmp(nTime,stTime);
         ena2 = strcmp(enTime,nTime);
         if ((ena1 >= 0) && (ena2 > 0)) InfoData[6].enabled = 1;
         else InfoData[6].enabled = 0;
         if (FirstRun == 1) goto lb1;
         else if ((strcmp(nTime,oDian) == 0) || (ena1 == 0) || (ena2 == 0)) goto lb1;
       }      
       goto lb2;
                
  lb1:
      if (TEXT_ENA)
         {
           InfoData[0].enabled=1;
           wsprintf(InfoData[0].ws,_percent_t,TEXT_FMT);
           FillInfoData(&InfoData[0],TEXT_X,TEXT_Y,FontType(TEXT_FONT),TEXT_CS,
                     TEXT_OUTLINE,TEXT_CB);
         }
       else
         {
           InfoData[0].enabled=0;
         }
 
       TDate pLdate;
       int f = GetLunarDate(&t_date, &pLdate);    
       if (CYEAR_ENA)
         {
           int d = GetLunarYearID(pLdate.year);
           int e = GetLunarAnimal(pLdate.year);   
    	   InfoData[1].enabled=1;
           wsprintf(InfoData[1].ws,"%t%t",d,e);
    	   FillInfoData(&InfoData[1],CYEAR_X,CYEAR_Y,FontType(CYEAR_FONT),CYEAR_CS,32,CYEAR_CB);
         }
       else
         {
    	   InfoData[1].enabled=0;
         }

       if (CDATE_ENA)
         {
    	    InfoData[2].enabled=1;
            if ((f == 0) || (f >= pLdate.month)) 
               wsprintf(InfoData[2].ws,"%t%t%t",cMName[pLdate.month],cOName[1],cDName[pLdate.day]);
            if (f == pLdate.month - 1)
               wsprintf(InfoData[2].ws,"%t%t%t%t",cOName[2],cMName[f],cOName[1],cDName[pLdate.day]);
            if ((f !=  0) && (f < pLdate.month - 1))
               wsprintf(InfoData[2].ws,"%t%t%t",cMName[pLdate.month - 1],cOName[1],cDName[pLdate.day]);
    	    FillInfoData(&InfoData[2],CDATE_X,CDATE_Y,FontType(CDATE_FONT),CDATE_CS,32,CDATE_CB);
         }
       else
         {
            InfoData[2].enabled=0;
         }

       if (BIR_ENA)
         {
            char oDay[7],nDay[7];
            sprintf(oDay,"L%02d.%02d:",pLdate.month,pLdate.day);
            InfoData[3].enabled = FindBirName(InfoData[3].ws,FestaData,oDay);
            if (InfoData[3].enabled)
                 FillInfoData(&InfoData[3],OBIR_X,OBIR_Y,FontType(OBIR_FONT),OBIR_CS,32,OBIR_CB);
     
            unsigned short lunar = LunarHolId(t_date);
            if (lunar)
              {
                 gb2ws(InfoData[4].ws, &jDay[lunar - 1][0], 6);
                 InfoData[4].enabled = 1;
              }
            else
              {
                 sprintf(nDay,"N%02d.%02d:",t_date.month,t_date.day);
                 InfoData[4].enabled = FindBirName(InfoData[4].ws,FestaData,nDay);
              }
            if (InfoData[4].enabled)
                 FillInfoData(&InfoData[4],NBIR_X,NBIR_Y,FontType(NBIR_FONT),NBIR_CS,32,NBIR_CB);

            if (InfoData[6].enabled)
                 FillInfoData(&InfoData[6],APP_X,APP_Y,FontType(APP_FONT),APP_CS,32,APP_CB);
         }
       else
         {
            InfoData[3].enabled = 0;
            InfoData[4].enabled = 0;            
         }
       if (WEEK_ENA)
         {
            InfoData[5].enabled=1;
            int c=GetWeek(&t_date);
            switch(WEEK_STYLE)
              {
    	         case 0:
    		    str_2ws(InfoData[5].ws, &weekdays1[c][0], 5);
    		    break;
    	         case 1:
    		    gb2ws(InfoData[5].ws, &weekdays2[c][0], 8);
               }
             FillInfoData(&InfoData[5],WEEK_X,WEEK_Y,FontType(WEEK_FONT),WEEK_COLORS,TEXT_OUTLINE,WEEK_FRINGING_COLORS);
         }
       else
         {
            InfoData[5].enabled=0;
         }
       
  lb2:FirstRun = 0;       
      FreeFileBuf(FestaData);

  }
}

// ----------------------------------------------------------------------------

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  void *icsm;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
      ShowMSG(1,(int)"'节日提醒'配置更新!");
      FirstRun = 1;
      InitInfoData();
    }
  }
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,IPC_FESREMIND_NAME)==0)
      {
        switch (msg->submess)
        {
        case IPC_UPDATE_STAT:
#ifdef NEWSGOLD
          if (!getCpuUsedTime_if_ena())
          {
            StartCpuUsageCount();
          }
#endif
          GBS_StartTimerProc(&mytmr, TMR_SECOND, TimerProc);
        }
      }
    }
  }
  switch (cfgShowIn)
  {
  case 0:
    fShow = !IsUnlocked();
    break;
  case 1:
    fShow = IsUnlocked();
    break;
  default:
    fShow = 1;
    break;
  }
  icsm=FindCSMbyID(CSM_root()->idle_id);
  if (icsm)
  {
    if (IsGuiOnTop(idlegui_id(icsm)) && fShow)
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
#ifdef ELKA
        {
          void *canvasdata = BuildCanvas();
#else
        void *idata = GetDataOfItemByID(igui, 2);
        if (idata)
        {
          void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
          for (int i=0; i<(sizeof(InfoData)/sizeof(TInfo)); i++)
          {
            if (InfoData[i].enabled)
            {
              DrawCanvas(canvasdata, InfoData[i].rc.x, InfoData[i].rc.y, InfoData[i].rc.x2, InfoData[i].rc.y2, 1);
              DrawString(InfoData[i].ws, InfoData[i].rc.x, InfoData[i].rc.y, InfoData[i].rc.x2, InfoData[i].rc.y2, 
                         InfoData[i].font,
                         InfoData[i].draw_flag,
                         InfoData[i].pen,
                         InfoData[i].fr_cl);
            }
          }
        }
      }
    }
  }
  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  for (int i=0;i<(sizeof(InfoData)/sizeof(TInfo)); i++)
  {
    InfoData[i].ws=CreateLocalWS(&InfoData[i].wsh,InfoData[i].wsbody,WS_MAXLEN+1);
  }  
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&mytmr);
  SUBPROC((void *)ElfKiller);
}

static unsigned short maincsm_name_body[140];
const int minus11=-11;

static const struct
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
  sizeof(CSM_RAM),
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),_percent_t,(zhName));
}
// ----------------------------------------------------------------------------

int main(void)
{
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  InitConfig();
  UpdateCSMname();
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  return (0);
}
