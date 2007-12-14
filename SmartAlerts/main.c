#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"


#define TMR_SECOND 216

extern const int ch_bat;
extern const unsigned int melody3;


extern const unsigned int melody;
extern const unsigned int min;
extern const unsigned int max;
extern const unsigned int minute;

extern const int voice;
extern const unsigned int volume;
extern const unsigned int filter;
extern const char wav[64];
extern const int amelody;

extern const int twice;
extern const unsigned int minute2;
extern const unsigned int melody2;

extern const unsigned int minute3;
extern const char day1[25];
extern const char day2[25];
extern const char day3[25];
extern const char day4[25];
extern const char day5[25];
extern const char day6[25];
extern const char day7[25];


extern const int runfile;
extern const char name1[64];
extern const unsigned int rhour1;
extern const unsigned int rminute1;
extern const char name2[64];
extern const unsigned int rhour2;
extern const unsigned int rminute2;
extern const char name3[64];
extern const unsigned int rhour3;
extern const unsigned int rminute3;
extern const char name4[64];
extern const unsigned int rhour4;
extern const unsigned int rminute4;
extern const char name5[64];
extern const unsigned int rhour5;
extern const unsigned int rminute5;

extern const int call;
extern const char num[30];
extern const unsigned int chour1;
extern const unsigned int cminute1;

extern const int sms;
extern const char snum[30];
extern const unsigned int shour1;
extern const unsigned int sminute1;
extern const char tmo[64];

extern const int miss;
extern const int mvib;
extern const unsigned int melodym;
extern const unsigned int mminute;

extern const unsigned int count2;
extern const unsigned int vibra_pow;

TDate date; 
TTime time; 

GBSTMR mytmr;

WSHDR* ws;

unsigned short *s;

int count;
GBSTMR tmr_vibra;

volatile int _count;

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
  if (file) 
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
  /*}*/
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



#ifdef NEWSGOLD
#pragma swi_number=0x9E
__swi __arm GetMissedEventCount(unsigned int Event);
#endif



void Check()
{

if (!IsCalling())
{
	GetDateTime(&date,&time);

	if(time.min==minute)
	{ 
		if (time.hour>min)
		{
			if (time.hour<max)
			{  
                          if(voice&&((GetProfile()+1)!=filter))
                          {
                            char s[5];
                            sprintf(s, "%d.wav",time.hour);
                            Play(wav, s);
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
		}
	}
        
        if(time.min==minute2&&twice)
	{ 
          	if (time.hour>min)
		{
			if (time.hour<max)
			{  
        		  PlaySound(1,0,0,melody2,0);
                          if(!amelody)
                          {
                          _count=count2;
                          start_();
                          }
                        }
                }
        }
        

        if(runfile)
        {
        if(!(time.hour==0&&time.min==0))
        {
	if(time.hour==rhour1&&time.min==rminute1)
        {
          runFile((char*)name1);
        }
	if(time.hour==rhour2&&time.min==rminute2)
        {
          runFile((char*)name2);
        }
	if(time.hour==rhour3&&time.min==rminute3)
        {
          runFile((char*)name3);
        }
	if(time.hour==rhour4&&time.min==rminute4)
        {
          runFile((char*)name4);
        } 
	if(time.hour==rhour5&&time.min==rminute5)
        {
          runFile((char*)name5);
        }
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
	if(time.hour==shour1&&time.min==sminute1)
        {
          s=Opendata((char*)tmo);
          copy_unicode_2ws(ws,s+1,210);
          if(strlen(snum)>5&&s>0)
          SendSMS(ws, snum, MMI_CEPID, MSG_SMS_RX-1, 6);
        }
        }
        
        
        void Cap();
}

if(time.min==minute3)
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
  
  switch(*(pc+time.hour))
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
}

GBS_StartTimerProc(&mytmr,216*60,Check);
}

void Cap()
{
if (ch_bat)
{
if (*RamCap()==100){
  PlaySound(1,0,0,melody3,0);
  *RamCap()==99;
}
}
GBS_StartTimerProc(&mytmr,216*60,Check);
}

void missed()
{
        if(miss)
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
        }

  GBS_StartTimerProc(&mytmr, 216*60*mminute, missed);  
}

void start()
{ 
missed();
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
  if(msg->msg == MSG_RECONFIGURE_REQ) // Perechityvanie configuration reported
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
  
  ws=AllocWS(210);
  start();
  return 0;
}
