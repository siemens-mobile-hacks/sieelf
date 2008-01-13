#include "..\inc\swilib.h"


int get_initday(void)
{
  unsigned int err;
  int f;
  char bcfgpath[]="0:\\ZBin\\etc\\SMSCount.bcfg";
  if((f=fopen(bcfgpath,A_ReadOnly+A_BIN,P_READ,&err))==-1)
  {
  	bcfgpath[0]='4';
  	if((f=fopen(bcfgpath,A_ReadOnly+A_BIN,P_READ,&err))==-1)
  		return 1;
  }
  //char *initday=malloc(8);
  int initday;
  lseek(f,44,0,&err,&err);
  fread(f,&initday,1,&err);
  fclose(f,&err);
  //mfree(initday);
  //return initday[0];
  return initday;
}

int get_month_day(int type)
{
  TTime tt;
  TDate td;
  GetDateTime(&td,&tt);
  if(type==1) return (int)td.day;
  if(type==2) return (int)td.month;
  return 0;
}

int check_initday(void)
{
	int initday=get_initday();
  if(initday==0) return 0;
  if(initday==get_month_day(1)) return 1;
  return 2;
}

#pragma swi_number=0x0A4
__swi	__arm	WSHDR * AllocWS_2 (int len);

#pragma swi_number=0x0A5
__swi	__arm	void  FreeWS_2 (WSHDR *wshdr);

#pragma swi_number=0x0A0
__swi	__arm	int wsprintf_2 (WSHDR *,const char *format,...);

void start_elf()
{
	char fpath[]="0:\\ZBin\\utilities\\SMSCountReader.elf";
	FSTATS fstats;
	unsigned int err;
	if (GetFileStats(fpath,&fstats,&err)==-1)
	{
		fpath[0]='4';
		if (GetFileStats(fpath,&fstats,&err)==-1)
	  {
	  	MsgBoxError(1, (int)"Can't find SMSCountReader.elf");
	  	return;
	  }
	}
	WSHDR *ws=AllocWS_2(128);
	wsprintf_2(ws,"%s",fpath);
	ExecuteFile(ws,0,0);
	FreeWS_2(ws);
}

#pragma diag_suppress=Pe177
__root static const int HookShow @ "HookShow" = (int)start_elf;
#pragma diag_default=Pe177
