#include "addr.h"

__thumb void Hex2Num(char *hex, char *num, int len) @ "CODE_X"
{
	int c;
	int i=0,j;
	char *p=hex;
	if(*p==0x91)
	{
		//num[i]='+';
		//i++;
		p++;
	}
	p++;
	for (j=0; j<len; j++)
	{
		c=p[j]%0x10;
		if(c>=0&&c<=9)
			num[i]=c+'0';
		else
			break;
		i++;
		c=p[j]/0x10;
		if(c>=0&&c<=9)
			num[i]=c+'0';
		else
			break;
		i++;
	}
	num[i]=0;
}

__thumb int GetNumFromIncomingPDU(char *num) @ "CODE_X"
{
	int c;
	char *p=(char *)ADDR_IncommingPDU;
	if ( *p++ != 0x11 )
		return 0;
	if ( *p++ != 0x11 )
		return 0;
	p++;
	c=*p++;
	p+=c+1;
	c=*p++;
	if(c)
	{
		if(c%2)
			c=c/2+2;
		else
			c=c/2+1;
		Hex2Num(p, num, c);
		return 1;
	}
	return 0;
}

