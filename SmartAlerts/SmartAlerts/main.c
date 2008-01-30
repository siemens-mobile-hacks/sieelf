#include "..\..\inc\swilib.h"
#include "..\..\inc\cfg_items.h"
#include "conf_loader.h"
#include "SmartAlerts.h"


#define TMR_SECOND (1300/6)

#ifdef NEWSGOLD
#ifdef S68
#define DEFAULT_DISK "0"
#else
#define DEFAULT_DISK "4"
#endif
#else
#define DEFAULT_DISK "0"
#endif



unsigned int files[5];
unsigned int smss[5];
unsigned int calls[5];
unsigned int amenus[11];
unsigned int miss[6];
unsigned int bmenus[4];

unsigned int hour[5];
unsigned int min[7];
unsigned int status[5];
unsigned int weekdays[5][7];
unsigned int day[7][24];
unsigned int other[9];
unsigned int name2[8];
int show_icon=0;
int status_icon=0;
int X;
int Y;
int imgw;
int imgh;

TDate date; 
TTime time; 
TDate week;
GBSTMR mytmr;
GBSTMR tmr_vibra;
GBSTMR *xtmr;

WSHDR* ws;

int count;
int fb=0;
volatile int _count;

char icon[]=DEFAULT_DISK":\\Zbin\\img\\SmartAlerts\\icon.png";
char cfgfile[]=DEFAULT_DISK":\\Zbin\\img\\SmartAlerts\\SmartAlerts.cfg";
char sound[]=DEFAULT_DISK ":\\ZBin\\img\\SmartAlerts\\alerts\\";

void getimgwh()
{
  imgw=GetImgWidth((int)icon);
  imgh=GetImgHeight((int)icon);
}

void update_status()
{
  if (status[0] || status[1] || status[2] || status[3] || status[4])
  {
    status_icon=1;
  }
   else status_icon=0;
}

void load_settings(void)
{
  unsigned int err;
  int handle=fopen(cfgfile, A_ReadOnly, P_READ,&err);
  if(handle!=-1)
  {
    char *data=malloc(280);
    fread(handle,data,280,&err);

      
show_icon=data[2];
X=data[3];
Y=data[4];
//5
for(int i=0;i<5;i++)
{
  status[i]=data[i+5];
  hour[i]=data[i+10];
  min[i]=data[i+15];
  files[i]=data[i+20];
  calls[i]=data[i+25];
  smss[i]=data[i+30];
}
//35
for(int i=0;i<35;i++)
{
weekdays[i/7][i%7]=data[i+35];
}
//70
for(int i=0;i<168;i++)
{
day[i/24][i%24]=data[i+70];
}
//238
min[6]=data[238];

name2[0]=data[239];
name2[1]=data[240];
name2[2]=data[241];
name2[3]=data[242];
name2[4]=data[243];
name2[5]=data[244];
name2[6]=data[245];
name2[7]=data[246];

other[8]=data[247];

other[0]=data[248];
other[1]=data[249];
other[2]=data[250];
other[3]=data[251];

other[4]=data[252];
other[5]=data[253];
other[6]=data[254];
other[7]=data[255];

bmenus[0]=data[256];
bmenus[1]=data[257];
bmenus[2]=data[258];
bmenus[3]=data[259];

miss[0]=data[260];
miss[1]=data[261];
miss[2]=data[262];
miss[3]=data[263];
miss[4]=data[264];
miss[5]=data[265];

amenus[0]=data[266];
amenus[1]=data[267];
amenus[2]=data[268];
amenus[3]=data[269];
amenus[4]=data[270];
amenus[5]=data[271];
amenus[6]=data[272];
amenus[7]=data[273];
amenus[8]=data[274];
amenus[9]=data[275];
amenus[10]=data[276];

    mfree(data);
    fclose(handle,&err);
  }
  getimgwh();
  update_status();
}

void start_ring()
{
  char elf[]=DEFAULT_DISK":\\Zbin\\img\\SmartAlerts\\alarm_ring.elf";
  WSHDR *ws;
  ws=AllocWS(64);
  str_2ws(ws,elf,strlen(elf)+1);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}


int runFile(char *file) 
{
  if(file)
  {
    if (strlen(file))
    {
      WSHDR *ws;
      ws=AllocWS(64);
      str_2ws(ws, file, 64);
      ExecuteFile(ws, 0, 0);
      FreeWS(ws);
      return 1;
    }
  }
  return 0;
}

void Play(const char *fpath, const char *fname)
{
  WSHDR* sndPath=AllocWS(64);
  WSHDR* sndFName=AllocWS(64);

  wsprintf(sndPath, fpath);
  wsprintf(sndFName, fname);
  
    if(fpath==0)
    {
    FSTATS fstats;
    unsigned int err; 
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      char s[64];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,64);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,64);
    }
    }

    PLAYFILE_OPT _sfo1;
    zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
    _sfo1.repeat_num=1;
    _sfo1.time_between_play=0;
    _sfo1.play_first=0;
    _sfo1.volume=other[4];
#ifdef NEWSGOLD
    _sfo1.unk6=1;
    _sfo1.unk7=1;
    _sfo1.unk9=2;
    PlayFile(0x10, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
    _sfo1.unk4=0x80000000;
    _sfo1.unk5=1;
    PlayFile(0xC, sndPath, sndFName, 0, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
    _sfo1.unk5=1;
    PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif 
    
  FreeWS(sndPath);
  FreeWS(sndFName);
}



void start_(void)
{
  void stop_(void);
  if(!name2[4]||!bmenus[0]||(*RamCap()<bmenus[1]))
  {
  	if (other[1])
		SetIllumination(0, 1, other[7]+1, 0);
	if (other[2])
		SetIllumination(1, 1, other[7]+1, 0);   
#ifndef NEWSGOLD
	if (other[3])
		SetIllumination(2, 1, other[7]+1, 0);
#else
	if (other[3])
		SetIllumination(4, 1, other[7]+1, 0);
#endif
  
  if (other[0]) SetVibration(other[6]);
  }
  GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,stop_);
}

void stop_(void)
{
  	if (other[1])
		SetIllumination(0, 1, 0, 0);
	if (other[2])
		SetIllumination(1, 1, 0, 0);   
#ifndef NEWSGOLD
	if (other[3])
		SetIllumination(2, 1, 0, 0);
#else
	if (other[3])
		SetIllumination(4, 1, 0, 0);
#endif
  if (other[0]) SetVibration(0);
  if (--_count)
  {
    GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,start_);
  }
}

void alarm(int n)
{
  if (status[n])
  {
    TDate date;
    GetDateTime(&date, 0);
    char wd = GetWeek(&date);
    if (weekdays[n][wd])
      {
        GetDateTime(&date,&time);
        if (time.hour==hour[n])
          {
            if (time.min==min[n])
              {
                start_ring();
              }
          }
      }
  }
}


void Check()
{
GetDateTime(&date,&time);
 if (!IsCalling())
 {
   
  if(name2[0])
  {
   for (int i=0;i<5;i++)
  {
    alarm(i);
  }
  }

   if(name2[1])
   {
     if ((time.hour>=amenus[3])&&(time.hour<=amenus[4]))
        {              
         if(time.min==amenus[5]&&!(name2[7]&&time.hour==smss[3]&&time.min==smss[4]))
	 { 
               if(amenus[1]&&((GetProfile()+1)!=amenus[9]))
               {
                   char w[5];
                   sprintf(w, "%d.%s",time.hour,mstyle);
                   Play(sound,w);
               }
               else if(amenus[0]&&((GetProfile()+1)!=amenus[9]))
               {
                   Play(0,vname);
               }
               else
               {
		   PlaySound(1,0,0,amenus[6],0);
               }
                   _count=other[5];
                   start_();
	  }
          else if(time.min==amenus[7]&&amenus[2]&&!(name2[7]&&time.hour==smss[3]&&time.min==smss[4]))
	  { 
               PlaySound(1,0,0,amenus[8],0);
                  _count=other[5];
                  start_();
           }
        }
   }
  
        if(name2[5])
        {
          if(!files[0]||(date.month==files[1]&&date.day==files[2]))
          {
          if(time.hour==files[3]&&time.min==files[4])
           {
           runFile((char*)name1);
           }
          }
        }
        
        if(name2[6])
        {
          if(!calls[0]||(date.month==calls[1]&&date.day==calls[2]))
          {
	  if(time.hour==calls[3]&&time.min==calls[4])
           {
            if(strlen(callnum)>5)
            MakeVoiceCall(callnum,0x10,0x2FFF);
           }
          }
        }
        
        if(name2[7])
        {
         if(!smss[0]||(date.month==smss[1]&&date.day==smss[2]))
          {
	  if(time.hour==smss[3]&&time.min==smss[4])
          {
                utf8_2ws(ws,content,210);
                if(strlen(smsnum)>5)
                SendSMS(ws,smsnum,MMI_CEPID,MSG_SMS_RX-1, 6);
          }
          }
        }  
     
        if (name2[4])
        {
           if (*RamCap()==100&&fb!=bmenus[3])
           {
           PlaySound(1,0,0,bmenus[2],0);
           fb++;
           }
           else if(*RamCap()!=100)
                fb=0;
        }
        
        if(name2[3])
        {
          if ((time.hour>=miss[2])&&(time.hour<=miss[3]))
          {
          if(time.min%miss[5]==0)
          {
          #ifdef NEWSGOLD          
	    if (GetMissedEventCount(0) > 0)
          #else
            if (GetMissedCallsCount()||HasNewSMS()) 
          #endif
          {
            if(!miss[0])
            {
             if(miss[1])
              Play(0,mname); 
             else
             PlaySound(1,0,0,miss[4],0);
            }
             _count=other[5];
             start_();
          }
          }
          }
        }
 }
 if(name2[2])
 {
  if(time.min==min[6])
  {
   int a1,a2;
   if(GetWeek(&date)<5&&other[8])
   a1=0;
   else
   a1=GetWeek(&date);
   
   a2=time.hour;
   if(day[a1][a2]<9&&day[a1][a2]!=0)
     SetProfile(day[a1][a2]-1);
  }
 }

GBS_StartTimerProc(&mytmr,13000,Check);
}

void start()
{ 
GBS_StartTimerProc(&mytmr,13000,Check); 
} 

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

int IDLECSM_ID=-1;

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
    }

    if (strcmp_nocase("smartalerts",(char *)msg->data0)==0)
    {
      load_settings();
    }
  }

  if (msg->msg == MSG_IPC)
  {
    IPC_REQ *ipc=(IPC_REQ*)((msg)->data0);
    if (ipc)
    {
      if (strcmp_nocase("smartalerts",(char *)ipc->name_to)==0)
      {
         int time2 =msg->submess;
        GBS_StartTimerProc(&xtmr,13000*time2,start_ring);
      }
    }
  }
  
  CSM_RAM *icsm;
  if ((icsm=FindCSMbyID(CSM_root()->idle_id)))
  {
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    if (IsGuiOnTop(idlegui_id))
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
          if((IsUnlocked())&&(show_icon)&&(status_icon))
          {
            DrawCanvas(canvasdata, X, Y, X + imgh, Y + imgh, 1);
            DrawImg(X, Y, (int)icon);
          }
        }
      }
    }
  }
  
  return(1);
}  

static void maincsm_oncreate(CSM_RAM *data)
{
  start();
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr()); 
}

static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&mytmr);
  GBS_DelTimer(&tmr_vibra);
  //GBS_DelTimer(&xtmr);
  FreeWS(ws);
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

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
  wsprintf((WSHDR *)(&MAINCSM_d.maincsm_name),"smartalerts");
}

int main()
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig(); 
  load_settings();
  UpdateCSMname();
  ws=AllocWS(210);
  LockSched(); 
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM_d.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();

  return 0;
}
