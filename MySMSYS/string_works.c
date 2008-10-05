#include "../inc/swilib.h"
#include "string_works.h"


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
    else
    {
      switch(temp)
      {
	//CODEMAP不支持的部分字符，这里只写出少量几个常用的
      case 0x2014:
	s[j++]=0xA1; //'—'
	s[j++]=0xAA;
	break;
      case 0x2018:
	s[j++]=0xA1; //'‘'
	s[j++]=0xAE;
	break;
      case 0x201C:
	s[j++]=0xA1;//'“'
	s[j++]=0xB0;
	break;
      case 0x201D:
	s[j++]=0xA1;//'”'
	s[j++]=0xB1;//'”'
	break;
      case 0x2103:
	s[j++]=0xA1;//'℃'
	s[j++]=0xE6;//'℃'
	break;
      case 0x3001:
	s[j++]=0xA1;//'、'
	s[j++]=0xA2;//'、'
	break;
      case 0x3002:
	s[j++]=0xA1;//'。'
	s[j++]=0xA3;//'。'
	break;
      case 0xFF01:
	s[j++]='！'/0x100;
	s[j++]='！'%0x100;
	break;
      case 0xFF08:
	s[j++]='（'/0x100;
	s[j++]='（'%0x100;
	break;
      case 0xFF09:
	s[j++]='）'/0x100;
	s[j++]='）'%0x100;
	break;
      case 0xFF0C:
	s[j++]='，'/0x100;
	s[j++]='，'%0x100;
	break;
      case 0xFF1A:
	s[j++]='：'/0x100;
	s[j++]='：'%0x100;
	break;
      case 0xFF1B:
	s[j++]='；'/0x100;
	s[j++]='；'%0x100;
	break;
      case 0xFF1F:
	s[j++]='？'/0x100;
	s[j++]='？'%0x100;
	break;
      case 0xFF5E:
	s[j++]='～'/0x100;
	s[j++]='～'%0x100;
	break;
      case 0xFFE5:
	s[j++]='￥'/0x100;
	s[j++]='￥'%0x100;
	break;
      default :
	s[j++]=char16to8(temp);
      }
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

