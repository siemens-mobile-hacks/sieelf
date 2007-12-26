#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include "SmartAlerts.h"
#include "extern.h"

#define TMR_SECOND 216

TDate date; 
TTime time; 
GBSTMR mytmr;
GBSTMR tmr_vibra;

WSHDR* ws;

int count;
int fb=0;
volatile int _count;

void start_(void)
{
  void stop_(void);
  	if (dis)
		SetIllumination(0, 1, light, 0);
	if (key)
		SetIllumination(1, 1, light, 0);   
#ifndef NEWSGOLD
	if (dyn)
		SetIllumination(2, 1, light, 0);
#else
	if (lighter)
		SetIllumination(4, 1, light, 0);
#endif
  
  if (vib) SetVibration(vibra_pow);
  GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,stop_);
}

void stop_(void)
{
  	if (dis)
		SetIllumination(0, 1, 0, 0);
	if (key)
		SetIllumination(1, 1, 0, 0);   
#ifndef NEWSGOLD
	if (dyn)
		SetIllumination(2, 1, 0, 0);
#else
	if (lighter)
		SetIllumination(4, 1, 0, 0);
#endif
  
  if (vib) SetVibration(0);
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
         if(time.min==minute&&!(sdate&&time.hour==smstime.hour&&time.min==smstime.min))
	 { 
               if(voice&&((GetProfile()+1)!=filter))
               {
                   char w[5];
                   sprintf(w, "%d.%s",time.hour,mstyle);
                   Play(sound,w);
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
          if(!rdate||(date.month==rundate.month&&date.day==rundate.day))
          {
          if(time.hour==runtime.hour&&time.min==runtime.min)
           {
           runFile((char*)name1);
           }
          }
        }
        
        if(call)
        {
          if(!cdate||(date.month==calldate.month&&date.day==calldate.day))
          {
	  if(time.hour==calltime.hour&&time.min==calldate.day)
           {
            if(strlen(callnum)>5)
            MakeVoiceCall(callnum,0x10,0x2FFF);
           }
          }
        }
        
        if(sms)
        {
         if(!sdate||(date.month==smsdate.month&&date.day==smsdate.day))
          {
	  if(time.hour==smstime.hour&&time.min==smstime.min)
          {
                utf8_2ws(ws,content,210);
                if(strlen(smsnum)>5)
                SendSMS(ws,smsnum,MMI_CEPID,MSG_SMS_RX-1, 6);
          }
          }
        }  
     
        if (ch_bat)
        {
           if (*RamCap()==100&&fb!=fcount)
           {
           PlaySound(1,0,0,melody3,0);
           fb++;
           }
           else if(*RamCap()!=100)
                fb=0;
        }
        
        if(miss)
        {
          if (!(time.hour<min)&&!(time.hour>max))
          {
          if(time.min%mminute==0)
          {
          #ifdef NEWSGOLD          
	    if (GetMissedEventCount(events) > 0)
          #else
            if (GetMissedCallsCount()||HasNewSMS()) 
          #endif
          {
            if(!mvib)
            {
             if(voice2)
              Play(0,mname); 
             else
             PlaySound(1,0,0,melodym,0);
            }
             _count=count2;
             start_();
          }
          }
          }
        }

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
      if(merge)
      pc=&day1[0];
      else
      pc=&day2[0];
  break;
  case 3:
      if(merge)
      pc=&day1[0];
      else
      pc=&day3[0];
  break;
  case 4:
      if(merge)
      pc=&day1[0];
      else
      pc=&day4[0];
  break;
  case 5:
      if(merge)
      pc=&day1[0];
      else
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
  
  ws=AllocWS(210);
  start();
  return 0;
}
