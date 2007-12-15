#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include "SmartAlerts.h"

#define TMR_SECOND 216

TDate date; 
TTime time; 
GBSTMR mytmr;
GBSTMR tmr_vibra;

WSHDR* ws;
unsigned short *s;

int count;
volatile int _count;

unsigned short* Opendata(char *recname)
{
  char *buf;
  int f;
  unsigned int fsize;  
  unsigned int err;
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
  return ((unsigned short*) buf);
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
  
  if (!IsCalling())
  {
    PLAYFILE_OPT _sfo1;
    zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
    _sfo1.repeat_num=1;
    _sfo1.time_between_play=0;
    _sfo1.play_first=0;
    _sfo1.volume=volume;
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
  }
  FreeWS(sndPath);
  FreeWS(sndFName);
}

void copy_unicode_2ws(WSHDR* ws, unsigned short* unicode,int x)
{
	int i = 0;
	for (; unicode[i]!=0 && i<=x; i++ )
	{
		ws->wsbody[i+1] = unicode[i];
	}
	ws->wsbody[0] = i;                  // set ws length
}

void start_(void)
{
  void stop_(void);
  SetVibration(vibra_pow);
  GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,stop_);
}

void stop_(void)
{
  SetVibration(0);
  if (--_count)
  {
    GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,start_);
  }
}

void Check()
{
GetDateTime(&date,&time);
 if (!IsCalling())
 {
     if (!(time.hour<min)&&!(time.hour>max))
        {              
         if(time.min==minute)
	 { 
               if(voice&&((GetProfile()+1)!=filter))
               {
                   char w[5];
                   sprintf(w, "%d.wav",time.hour);
                   Play(wav,w);
               }
               else
               {
		   PlaySound(1,0,0,melody,0);
               }
               if(!amelody)
               {
                   _count=count2;
                   start_();
               }
	  }
          else if(time.min==minute2&&twice)
	  { 
               PlaySound(1,0,0,melody2,0);
               if(!amelody)
               {
                  _count=count2;
                  start_();
               }
           }
        }

        if(runfile)
        {
          if(time.hour!=0&&time.min!=0)
           {
            void Runing(unsigned int x,unsigned int y);
            Runing(time.hour,time.min);
           }
        }
        
        if(call)
        {
	  if(time.hour==chour1&&time.min==cminute1)
           {
            if(strlen(num)>5)
            MakeVoiceCall(num,0x10,0x2FFF);
           }
        }
        
        if(sms)
        {
	  if(time.hour==shour1)
          {
            if(time.min==sminute1)
            {
            void Sms();
            }
          }
        }
     
        if (ch_bat)
        {
          void Cap();
        }
        
        if(miss)
        {
          if(time.min%mminute==0)
          {
          void Missed();
          }
        }

 }

  if(time.min==minute3)
  {
     void Profile(unsigned int x);
     Profile(time.hour);
  }

GBS_StartTimerProc(&mytmr,216*60,Check);
}

void Sms()
{
   s=Opendata((char*)tmo);
   copy_unicode_2ws(ws,s+1,140);
   if(strlen(snum)>5&&s)
   SendSMS(ws, snum, MMI_CEPID, MSG_SMS_RX-1, 6);
   
   GBS_StartTimerProc(&mytmr,216*60,Check);
}

void Cap()
{
  if (*RamCap()==100)
  {
  PlaySound(1,0,0,melody3,0);
  *RamCap()==99;
  }
  GBS_StartTimerProc(&mytmr,216*60,Check);
}

void Missed()
{
#ifdef NEWSGOLD          
	if (GetMissedEventCount(0) > 0)
#else
        if (GetMissedCallsCount()||HasNewSMS()) 
#endif
        {
          if(!mvib)
           PlaySound(1,0,0,melodym,0);
          
           _count=count2;
           start_();
        }
  GBS_StartTimerProc(&mytmr,216*60,Check);
}

void Runing(unsigned int x,unsigned int y)
{
	if(x==rhour1&&y==rminute1)
        {
          runFile((char*)name1);
        }
	if(x==rhour2&&y==rminute2)
        {
          runFile((char*)name2);
        }
	if(x==rhour3&&y==rminute3)
        {
          runFile((char*)name3);
        }
	if(x==rhour4&&y==rminute4)
        {
          runFile((char*)name4);
        } 
	if(x==rhour5&&y==rminute5)
        {
          runFile((char*)name5);
        }
    GBS_StartTimerProc(&mytmr,216*60,Check);
}

void Profile(unsigned int x)
{
  const char *pc;
  
  switch((GetWeek(&date)+1)%7)
  {
  case 1:
      pc=&day1[0];
  break;
  case 2:
      pc=&day2[0];
  break;
  case 3:
      pc=&day3[0];
  break;
  case 4:
      pc=&day4[0];
  break;
  case 5:
      pc=&day5[0];
  break;
  case 6:
      pc=&day6[0];
  break;
  case 0:
      pc=&day7[0];
  break;
  default:
      break;
  }
    
  switch(*(pc+x))
  {
  case '1':
  SetProfile(0);
  break;
  case '2':
  SetProfile(1);
  break;
  case '3':
  SetProfile(2);
  break;
  case '4':
  SetProfile(3);
  break;
  case '5':
  SetProfile(4);
  break;
  case '6':
  SetProfile(5);
  break;
  case '7':
  SetProfile(6);
  break;
  case '8':
  SetProfile(7);  
  break;
  case '0':
  break;
  
  default:
      break;
  }
  ShowMSG(1,(int)"Profile Changed!");
  
  GBS_StartTimerProc(&mytmr,216*60,Check);
}

void start()
{ 
GBS_StartTimerProc(&mytmr,216*60,Check); 
} 

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

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
  }
  return(1);
}  

static void maincsm_oncreate(CSM_RAM *data)
{
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  GBS_DelTimer(&tmr_vibra);
  FreeWS(ws);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr()); 
}

static void maincsm_onclose(CSM_RAM *csm)
{
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
  wsprintf((WSHDR *)(&MAINCSM_d.maincsm_name),"SmartAlerts");
}

int main()
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig(); 
  UpdateCSMname();
 
  LockSched(); 
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM_d.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  
  ws=AllocWS(140);
  start();
  return 0;
}
