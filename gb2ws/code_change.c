#include "..\inc\swilib.h"


/*#ifdef NEWSGOLD
#define CODEMAP_ADDR 0xA1568200  //-0xA157A24F
#else
#define CODEMAP_ADDR 0xA0FA0200
#endif*/

#define BASE_ADDR 0x{ÐÂ°æcodemap}°¡ÄãÃÃ

__thumb void ws2ascii(WSHDR *ws, char *s, int maxlen)
{
  unsigned short *codemap=(unsigned short *)(BASE_ADDR+0xCC6C);
  int i,j=0;
  unsigned short temp;
  while(ws[i]!=0 && maxlen-->0)
  {
    temp=ws[i];
    if(temp < 256) s[j++] = (unsigned char)temp;
    else if(temp >= 0x4E00 && temp <= 0x9FA5)
    {
      s[j++] = (unsigned char)(codemap[temp-0x4E00]>>8);
      s[j++] = (unsigned char)((codemap[temp-0x4E00]<<8)>>8);
    }
    else 
      s[j++] = '?';
    i++;
  }
  s[j] = 0;
}

__thumb void ascii2ws(WSHDR *ws, const char *s, int maxlen)
{
  int i,j=0;
  while(s[i]!='\0' && maxlen-->0)
  {
    if(s[i] >= 0x81 && s[i+1] >= 0x40)//Chinese
    {
      int tmp = (s[i] - 0x81)*0xC0+(s[i+1]-0x40);
      ws[j++] = *((WSHDR *)(BASE_ADDR) + tmp);
      i += 2;
    }
    else//not Chinese
    {
	ws[j++] = s[i++];
    }
  }
  ws[j] = 0;
}