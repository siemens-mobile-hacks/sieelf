#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"


#define TMR_SECOND 216

extern const int ch_bat;
extern const int setp;
extern const int twice;
extern const unsigned int melody;
extern const unsigned int melody2;
extern const unsigned int min;
extern const unsigned int max;
extern const unsigned int minute;
extern const unsigned int minute2;
extern const unsigned int filter;
extern const unsigned int minute3;
extern const char fname[128];

TDate date; 
TTime time; 

GBSTMR mytmr;

char recname[128];

void getfname(int x)
{
  switch(x)
  {
  case 1:
  snprintf(recname,128,"%s1.tmo",fname);
  break;
  case 2:
  snprintf(recname,128,"%s2.tmo",fname);
  break;
  case 3:
  snprintf(recname,128,"%s3.tmo",fname);
  break;
  case 4:
  snprintf(recname,128,"%s4.tmo",fname);
  break;
  case 5:
  snprintf(recname,128,"%s5.tmo",fname);
  break;
  case 6:
  snprintf(recname,128,"%s6.tmo",fname);
  break;
  case 0:
  snprintf(recname,128,"%s7.tmo",fname);
  break;
  default:
      break;
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


void copy_unicode_2ws(WSHDR* ws, unsigned short* unicode,int x)
{
	int i = 0;
	for (; unicode[i]!=0 && i<=x; i++ )
	{
		ws->wsbody[i+1] = unicode[i];
	}
	ws->wsbody[0] = i;                  // set ws length
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
      if((GetProfile()+1)!=filter)
          PlaySound(1,0,0,melody,0);
    }
  }
}

if(time.min==minute3&&setp)
{
  WSHDR* ws = AllocWS(30);
  unsigned short *s;
  getfname((GetWeek(&date)+1)%7);
  s=Opendata(recname);
  copy_unicode_2ws(ws,s,30);
  
  char c[30];
  const char *pc;
  ws_2str(ws,c,30);
  pc=&c[0];
  
  switch(*(pc+time.hour+2))
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
  
  FreeWS(ws);
}

void Cap();
}
GBS_StartTimerProc(&mytmr,262*60,Check);
}

void start()
{ 
GBS_StartTimerProc(&mytmr,262*60,Check); 
} 

void Cap()
{
if (ch_bat)
{
if (*RamCap()==100)
{
  PlaySound(1,0,0,melody2,0);
  *RamCap()==99;
}
}
GBS_StartTimerProc(&mytmr,262*60,Check);//262*60
}


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
