/***********************************************************************
区号秀号码选择菜单部分
作者：BingK(binghelingxi)
简述：
    在生成菜单单文本时做一个HOOK,将其中得到的号码写入到UNUSERAM_NUM中.
    在创建GUI之前再做一个HOOK,copy其中的methods部分到UNUSERAM_METHOD,
将GUI结构中的methods指向UNUSERAM_METHOD,另copy methods中的oldredraw部分
到UNUSERAM_OLD_REDRAW,以用于建立newredraw时恢复,建立newredraw,替换oldredraw,
newredraw中,先从UNUSERAM_OLD_REDRAW中读取oldredraw,执行,然后进入显示区
号程序,以上部分使用汇编,通过读取光标位置,定位到UNUSERAM_NUM中的号码,进
行区号转换,最后使用DrawString显示出来
************************************************************************/

#include "type_.h"
#include "addr.h"

extern int GetProvAndCity(word *pBSTR, char *pNoStr);

extern WSTRING *AllocWS(int len);
extern void  FreeWS(WSTRING *wshdr);
extern void DrawString(WSTRING *WSHDR,int x1,int y1,int x2,int y2,int font,int text_attribute,const char *Pen,const char *Brush);
extern int GetCurMenuItem(void *gui);

void memcpy_n(char *s1, char *s2, int len)
{
	int i;
	for(i=0;i<len;i++)
		s1[i]=s2[i];
}

//pos/8,就是号码的次序 
void store_the_num_2_ram(int pos, char *num)
{
	char *ram=(char *)UNUSERAM_NUM;
	ram+=pos/8*16; //16字节用于存储号码应该够用
	char *p=num;
	memcpy_n(ram, p, 16);
}

#define FONT_MEDIUM 2

void new_redraw_(void *data)
{
	const char color_white[4]={0xFF, 0xFF, 0xFF, 0x64};
	const char color_black[4]={0x0, 0x0, 0x0, 0x64};
	WSTRING *ws=AllocWS(16);
	int menucur=GetCurMenuItem(data);
	char *num=(char *)UNUSERAM_NUM;
	num+=menucur*16;
	int i=0, is_num=1;
	char *p=num;
	while(*p) //判断是否是号码，可能是电子邮件地址
	{
		if(*p<'0'||*p>'9')
		{
			is_num=0;
			break;
		}
		p++;
		i++; //i用于计数
	}
	if(i>0&&is_num)
	{
		GetProvAndCity(ws->pstr, num);
		DrawString(ws, 0, 140, 131, 157, FONT_MEDIUM, 34, color_white, color_black);
	}
	FreeWS(ws);
}

