#include "../inc/swilib.h"
#include "string_works.h"

static unsigned int _rshort(char *p)
{
  unsigned int r=*p++;
  r<<=8;
  r|=*p;
  return r;
}

int strcmp_nocase(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=*s++;
    if (cs&0x40) cs&=0xDF;
    ds=*d++;
    if (ds&0x40) ds&=0xDF;
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}

int omstrcmp(VIEWDATA *vd, unsigned int ps, unsigned int pd)
{
  int ls;
  char *s;
  int ld;
  char *d;
//  int l;
//  int r;
  if (ps>=vd->oms_size) return 1;
  if (pd>=vd->oms_size) return 1;
  ls=_rshort(s=vd->oms+ps);
  ld=_rshort(d=vd->oms+pd);
  if (ls!=ld) return 1;
  return memcmp(s+2,d+2,ls);
}

char *globalstr(const char *s)
{
  int l=strlen(s)+1;
  char *d=malloc(l);
  memcpy(d,s,l);
  return d;
}

void freegstr(char **ps)
{
  mfree(*ps);
  *ps=NULL;
}

char *replacegstr(char **ps, const char *s, int len)
{
  freegstr(ps);
  char *d=malloc(len+1);
  memcpy(d,s,len);
  d[len]=0;
  return *ps=d;
}

int char16to8(int c)
{
  if (c<0x400) return (c);
  c-=0x400;
  if (c<16)
  {
    if (c==1) c=0;
    else if (c==4) c=2;
    else if (c==6) c=10;
    else return (c);
  }
  else if (c>79)
  {
    if (c==0x51) c=16;
    else if (c==0x54) c=18;
    else if (c==0x56) c=11;
    else if (c==0x57) c=23;
    else return (c);
  }
  else c+=8;
  c+=168;
  return (c);
}

int char8to16(int c)
{
  if (c<168) return (c);
  c-=168;
  if (!c)  c=1;
  else if (c<24) 
  {
    if (c==2) c=4;
    else if (c==10) c=6;
    else if (c==11) c=0x56;
    else if (c==16) c=0x51;
    else if (c==18) c=0x54;
    else if (c==23) c=0x57;
    else return (c);
  }
  else if (c>87) return (c);
  else c-=8;
  c+=0x400;
  return (c); 
}

void ascii2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
}

char *extract_omstr(VIEWDATA *vd, unsigned int pos)
{
  int n;
  char *s;
  char *d;
  if (pos>=vd->oms_size) return NULL;
  n=_rshort(s=vd->oms+pos);
  d=malloc(n+1);
  memcpy(d,s+2,n);
  d[n]=0;
  return d;
}
