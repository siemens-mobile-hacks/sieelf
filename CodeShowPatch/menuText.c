/*********************************************
区号秀号码选择菜单部分(新), 1.8以后版本使用
作者：		BingK(binghelingxi)
最后修改:	2008.08.07
简述：
    改用多行菜单.
***********************************************/

#include "type_.h"
extern WSTRING *AllocMenuWS(void *gui, int len);
extern void AppendInfoW(WSTRING *pWS, WSTRING * pNo);
extern void SetMLMenuItemText(void *data,void *item,WSTRING *ws1,WSTRING *ws2,int n);
void setMenuText(void *gui, void *item, WSTRING *text,int item_n)
{
	unsigned short *p=text->pstr+1;
	int wslen=text->pstr[0];
	int i=0;
	int is_num=1;
	WSTRING *ws2=AllocMenuWS(gui, 24);
	if(*p=='+')
	{
		p+=3;
		wslen-=3;
	}
	for(;i<wslen;i++) //检查是否是号码
	{
		if(p[i]>'9'||p[i]<'0')
		{
			is_num=0;
			break;
		}
	}
	if(is_num)
	{
		#define N 4 //空格数
		unsigned short *p2;
		AppendInfoW(ws2, text);
		//前面加N个空格
		wslen=ws2->pstr[0];
		p=ws2->pstr+1;
		p2=p+wslen-1;
		for(i=0;i<wslen;i++) //后移
		{
			*(p2-i+N)=*(p2-i);
		}
		for(i=0;i<N;i++) //加空格
		{
			p[i]=' ';
		}
		ws2->pstr[0]=wslen+N;
	}
	SetMLMenuItemText(gui, item, text, ws2, item_n);
}

