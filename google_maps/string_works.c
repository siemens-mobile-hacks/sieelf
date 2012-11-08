#include "../inc/swilib.h"
#include <math.h>
#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

char *MakeGlobalString(const char *first, int breakchar, const char *last)
{
  int l;
  char *p;
  p=malloc((l=strlen(first))+strlen(last)+2);
  strcpy(p,first);
  if (first[strlen(first)-1]!=breakchar) p[l++]=breakchar;
  strcpy(p+l,last);
  return p;
}

void ascii2ws(WSHDR *ws, const char *s)
{
  gb2ws(ws, s, strlen(s));
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

void utf82win(char*d,const char *s)
{
  for (; *s; s+=2)
  {
    unsigned char ub = *s, lb = *(s+1);
    if (ub == 208)
      if (lb != 0x81)
        {*d = lb + 48; d++;}
      else
        {*d = '¨'; d++;}

    if (ub == 209)
      if (lb != 0x91)
        {*d = lb + 112; d++;}
      else
        {*d = '¸'; d++;}

    if ((ub != 208) && (ub != 209) && (lb != 91) && (lb != 81))
    {
      *d = ub;
      d++;
      s--;
    }
  }
  *d = 0;
}

int get_dec(const char *str)
{
	int dec=0;
	int r=0;
	while(str[dec]!=0x2E&&dec<strlen(str))
	{
		if(str[dec]-0x30<0||str[dec]-0x30>9)r++;
		dec++;
	}
	return dec-r;
}

double str_to_double(const char *str)
{
	volatile int flag=0;
	int dec=get_dec(str);
        double r=0.0;
	for(int i=0;i<strlen(str);i++)
	{
          if(str[i]-0x30<0||str[i]-0x30>9)continue;
		if(str[i]==0x2E)
		{
			flag=1;
			dec=get_dec(str);
			continue;
		}
		if(flag)r+=(double)(str[i]-0x30)/pow((double)10,(double)(i-dec));
		else r+=((double)str[i]-0x30)*(double)pow((double)10,(double)(--dec));
	}
	return r;
}
char *valuetag(char *src,char *dst, int maxlen){
 if (!src) return 0;
 if (!*src) return src;
 int c=0;
 while (*src!='\n' && *src!='"' && *src!=0 && c < maxlen){
  *dst++=*src++;
  c++;
 }
 *dst=0;
 return src;
}

char * findtag(char *src, char *tag){
 char *s;
 if (s=strstr(src,tag))
  return s+strlen(tag);
 return s;
}
