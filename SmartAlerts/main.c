#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"


#define TMR_SECOND 216

extern const int ch_bat;
extern const int twice;
extern const unsigned int melody;
extern const unsigned int melody2;
extern const unsigned int min;
extern const unsigned int max;
extern const unsigned int minute;
extern const unsigned int minute2;
//extern const unsigned int filter;
extern const unsigned int minute3;
extern const char day1[25];
extern const char day2[25];
extern const char day3[25];
extern const char day4[25];
extern const char day5[25];
extern const char day6[25];
extern const char day7[25];

TDate date; 
TTime time; 

GBSTMR mytmr;


void Check()
{

if (!IsCalling())
{
	GetDateTime(&date,&time);

	if(time.min==minute||(time.min==minute2&&twice))
	{ 
		if (time.hour>min)
		{
			if (time.hour<max)
			{  
			//if((GetProfile()+1)!=filter)
				PlaySound(1,0,0,melody,0);
			}
		}
	}
        

        if(ch_bat)
	{
          if (*RamCap()==100)
          {
          PlaySound(1,0,0,melody2,0);
          *RamCap()==99;
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
  InitConfig(); 
  start();
  LockSched();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM_d.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  return 0;
}
