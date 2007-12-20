#include "..\inc\swilib.h"
#include "SmartAlerts.h"

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
    
  FreeWS(sndPath);
  FreeWS(sndFName);
}


