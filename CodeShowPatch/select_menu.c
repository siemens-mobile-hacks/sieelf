/***********************************************************************
���������ѡ��˵�����
���ߣ�BingK(binghelingxi)
������
    �����ɲ˵����ı�ʱ��һ��HOOK,�����еõ��ĺ���д�뵽UNUSERAM_NUM��.
    �ڴ���GUI֮ǰ����һ��HOOK,copy���е�methods���ֵ�UNUSERAM_METHOD,
��GUI�ṹ�е�methodsָ��UNUSERAM_METHOD,��copy methods�е�oldredraw����
��UNUSERAM_OLD_REDRAW,�����ڽ���newredrawʱ�ָ�,����newredraw,�滻oldredraw,
newredraw��,�ȴ�UNUSERAM_OLD_REDRAW�ж�ȡoldredraw,ִ��,Ȼ�������ʾ��
�ų���,���ϲ���ʹ�û��,ͨ����ȡ���λ��,��λ��UNUSERAM_NUM�еĺ���,��
������ת��,���ʹ��DrawString��ʾ����
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

//pos/8,���Ǻ���Ĵ��� 
void store_the_num_2_ram(int pos, char *num)
{
	char *ram=(char *)UNUSERAM_NUM;
	ram+=pos/8*16; //16�ֽ����ڴ洢����Ӧ�ù���
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
	while(*p) //�ж��Ƿ��Ǻ��룬�����ǵ����ʼ���ַ
	{
		if(*p<'0'||*p>'9')
		{
			is_num=0;
			break;
		}
		p++;
		i++; //i���ڼ���
	}
	if(i>0&&is_num)
	{
		GetProvAndCity(ws->pstr, num);
		DrawString(ws, 0, 140, 131, 157, FONT_MEDIUM, 34, color_white, color_black);
	}
	FreeWS(ws);
}

