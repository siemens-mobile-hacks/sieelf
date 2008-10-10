#include "../inc/swilib.h"
#include "string_works.h"


typedef struct
{
  unsigned short u;
  unsigned short a;
} TUNICODE2ANSI;

const TUNICODE2ANSI u2a[]=
{
  0x2014,'¡ª',
  0x2018,'¡®',
  0x201C,'¡°',
  0x201D,'¡±',
  0x2103,'¡æ',
  0x3001,'¡¢',
  0x3002,'¡£',
  0xFF01,'£¡',
  0xFF08,'£¨',
  0xFF09,'£©',
  0xFF0C,'£¬',
  0xFF1A,'£º',
  0xFF1B,'£»',
  0xFF1F,'£¿',
  0xFF5E,'¡«',
  0xFFE5,'£¤',
  0,0
};

int unicode2ansi(int c) //
{
  int i;
  const TUNICODE2ANSI *p=u2a;
  if(c>=0x400 && c<0x1000)
  {
    int d;
    c-=0x400;
    c+=0xA791;
    d=c>>8;
    c=(c<<24)>>16;
    return (c|d);
  }
  else
  {
    while((i=p->u))
    {
      if(c==i)
	return p->a;
      p++;
    }
    return 0x2020;
  }
}
int char16to8(int c) //unicode2win1251
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

#ifdef LANG_CN
#ifdef NEWSGOLD
#define CODEMAP_ADDR 0xA1568200  //-0xA157A24F
#else
#define CODEMAP_ADDR 0xA0FA0200
#endif

void ws2ascii(WSHDR *ws, char *s, int maxlen)
{
  unsigned short *codemap=(unsigned short *)(CODEMAP_ADDR+32004);
  int i,j=0;
  unsigned short temp;
  for(i=1; i<=ws->wsbody[0]; i++)
  {
    temp=ws->wsbody[i];
    if(temp < 256)
      s[j++] = (unsigned char)temp;
    else if(temp >= 0x4E00 && temp <= 0x9FA5)
    {
      s[j++] = (unsigned char)(codemap[temp-0x4E00]>>8);
      s[j++] = (unsigned char)((codemap[temp-0x4E00]<<8)>>8);
    }
    else if(temp>=0x400)
    {
      temp=unicode2ansi(temp);
      s[j++]=temp>>8;
      s[j++]=(temp<<8)>>8;
    }
    else
    {
      s[j++]=' ';
    }
    if(maxlen != 0 && j >= maxlen)
      break;
  }
  s[j] = 0;
}

#endif
void ws_2ascii(WSHDR *ws, char *str, int maxlen)
{
#ifdef LANG_CN
  ws2ascii(ws, str, maxlen);
#else
  unsigned short *p=ws->wsbody+1;
  int i=0;
  while((i<maxlen)&&(i<ws->wsbody[0]))
  {
    str[i]=char16to8(p[i]);
    i++;
  }
  str[i]=0;
#endif
}

#define wslen(ARG) (ARG->wsbody[0])

int wstrcmp_nocase(WSHDR *ws1, WSHDR *ws2)
{
  int l1=wslen(ws1);
  int l2=wslen(ws2);
  int pos=1;
  int cs, ds;
  while((pos<=l1)&&(pos<=l2))
  {
    cs=ws1->wsbody[pos];
    ds=ws2->wsbody[pos];
    if(cs<0x1000 && ds<0x1000)
    {
    	cs=char16to8(cs);
    	ds=char16to8(ds);
    	if(cs&0x40) cs&=0xDF;
    	if(ds&0x40) ds&=0xDF;
    }
    cs-=ds;
    if (cs) return cs;
    pos++;
  }
  return(l1-l2);
}

int wstrncmp_nocase(WSHDR *ws1, WSHDR *ws2, int n)
{
  int l1=wslen(ws1);
  int l2=wslen(ws2);
  int pos=1;
  int cs, ds;
  n++;
  while((pos<=l1)&&(pos<=l2)&&(pos<=n))
  {
    cs=ws1->wsbody[pos];
    ds=ws2->wsbody[pos];
    if(cs<0x1000 && ds<0x1000)
    {
    	cs=char16to8(cs);
    	ds=char16to8(ds);
    	if(cs&0x40) cs&=0xDF;
    	if(ds&0x40) ds&=0xDF;
    }
    cs-=ds;
    if (cs) return cs;
    pos++;
  }
  return 0;
}
