#include "..\..\inc\swilib.h"
#include "conf_loader.h"
#include "code.h"


unsigned short *codemap;

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

void init_font_lib(void)
{
  int f;
  char cnfont[]=DEFAULT_DISK":\\zbin\\utilities\\cnfont.dat";
  unsigned int ul;
  codemap = 0;
  f=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  if(f != -1)
  {
    codemap=(unsigned short *)malloc(73808);
    if (fread(f,(void*)codemap,73808,&ul)!=73808)
    {
      mfree((void*)codemap);
      codemap = 0;
    }
    fclose(f,&ul);
  }
}

void free_font_lib(void)
{
  if (codemap)
  {
    mfree(codemap);
    codemap = 0;
  }
}

void ascii2ws(WSHDR *ws, const char *s, int maxlen)
{
  if(codemap == 0)
  {
    wsprintf(ws, "%t", s);
    return;
  }
  char *p=(char *)s;
  unsigned char uc,uc2;
  CutWSTR(ws,0);
  while((uc=*s++) && (maxlen == 0 || s-p<maxlen))
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
