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
if (ch_bat){
if (*RamCap()==100){
  PlaySound(1,0,0,melody2,0);
  *RamCap()==99;
}
}
GBS_StartTimerProc(&mytmr,262*60,Check);//262*60
}

int main(void)
{
  InitConfig();
  start();
  return 0;
}
