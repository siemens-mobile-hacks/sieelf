
#include "..\inc\swilib.h"


#ifdef NEWSGOLD
#define CODEMAP_ADDR 0xA1568200;  //-0xA157A24F
#else
#define CODEMAP_ADDR 0xA0FE0200;
#endif

extern CutWSTRT(WSHDR *,int );

#pragma swi_number=0x0A0
__swi	__arm	int wsprintf_2 (WSHDR *,const char *format,...);

#pragma segment="BODY"

__thumb void ws2ascii(WSHDR *ws, char *s, int maxlen)
{
  unsigned short *codemap=(unsigned short *)CODEMAP_ADDR;
  int len=ws->wsbody[0];
  if(maxlen != 0 && len > maxlen)
    len = maxlen;
  if(codemap == 0)
  {
    ws_2str(ws, s, len);
    return;
  }
  int i,j=0;
  unsigned short temp;
  for(i=1; i<=len; i++)
  {
    temp=ws->wsbody[i];
    if(temp < 256)
      s[j++] = (unsigned char)temp;
    else if(temp >= 0x4E00 && temp <= 0x9FA5)
    {
      s[j++] = (unsigned char)(codemap[temp-0x4E00+32004]>>8);
      s[j++] = (unsigned char)((codemap[temp-0x4E00+32004]<<8)>>8);
    }
    else
      s[j++] = '?';
  }
  s[j] = 0;
}

__thumb void ascii2ws(WSHDR *ws, const char *s, int maxlen)
{
  unsigned short *codemap=(unsigned short *)CODEMAP_ADDR;
  if(codemap == 0)
  {
    wsprintf_2(ws, "%t", s);
    return;
  }
  char *p=(char *)s;
  unsigned char uc,uc2;
  //CutWSTR(ws,0);
  CutWSTRT(ws,0);
  while((uc=*s++) && (maxlen == 0 || s-p<=maxlen))
  {
    if(uc <= 128)
      wsAppendChar(ws,uc);
    else
    {
      uc2=*s++;
      if(uc2 < 128)
        wsAppendChar(ws, uc2);
      else
        wsAppendChar(ws, codemap[(uc-129)*127+(uc2-128)]);
    }
  }
}

#pragma diag_suppress=Pe177
__root static const int SWILIB_GB2WS @ "SWILIB_GB2WS" = (int)ascii2ws;
#pragma diag_default=Pe177

#pragma diag_suppress=Pe177
__root static const int SWILIB_WS2GB @ "SWILIB_WS2GB" = (int)ws2ascii;
#pragma diag_default=Pe177

