#include "..\inc\swilib.h"
#include "addr.h"

#define	COUNT_ALL 0
#define	COUNT_CHM 1
#define	COUNT_CHU 2
#define	COUNT_XLT 3
#define	COUNT_OTH 4
#define	TYPE_ALL  5
#define	BUF_LEN   (TYPE_ALL*sizeof(int))

void countadd(int *buf, int type)
{
	buf[COUNT_ALL]++;
	buf[type]++;
}

void is_mobile(char *num, int *buf)
{
	int c;
	c=(*(num+1))%0x10;
	if(*num==0x31)
	{
		if(c>3) //134...
			countadd(buf, COUNT_CHM);
		else
			countadd(buf, COUNT_CHU);
	}
	else
	{
		if(*num==0x51)
		{
			switch(c)
			{
			case 0: //150
			case 8: //158
			case 9: //159
				countadd(buf, COUNT_CHM);
				break;
			case 6: //156
			case 3: //153
			case 1: //151
				countadd(buf, COUNT_CHU);
				break;
			default:
				countadd(buf, COUNT_OTH);
			}
		}
		else
			countadd(buf, COUNT_OTH);
	}
}

void check_num(void)
{
	int buf[TYPE_ALL];
	unsigned int err;
	int f;
	char dat_path[]="2:\\SMSCount.dat";
	int i;
	for(i=0;i<TYPE_ALL;i++)
		buf[i]=0;
	if((f=fopen(dat_path, A_ReadWrite+A_BIN, P_READ+P_WRITE, &err))!=-1)
	{
		fread(f, buf, BUF_LEN, &err);
		lseek(f, 0, S_SET, &err, &err);
	}
	else if((f=fopen(dat_path, A_ReadWrite+A_Create+A_Truncate, P_READ+P_WRITE, &err))==-1)
		return;
		
	char *p=(char *)RamSMSNum;
	if(*p>=0x0A)
	{
		int c;
		p++;
		if(*p==0x91) //+
		{
			p++;
			if(*p==0x68) //86
			{
				p++;
				goto CheckMobile;
			}
			else
			{
				countadd(buf, COUNT_OTH);
				goto END;
			}
		}
		p++; //81
		c=(*p)%0x10; //用于判断小灵通区号前必带一个0
		if((*p==0x01&&*(p+1)==0x06)||c==0x0) //1060...的小灵通
		{
			countadd(buf, COUNT_XLT);
			goto END;
		}
		CheckMobile:
		is_mobile(p, buf);
	}
	else
		countadd(buf, COUNT_OTH);
END:
	fwrite(f, buf, BUF_LEN, &err);
	fclose(f,&err);
}

