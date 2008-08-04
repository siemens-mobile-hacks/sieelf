#include "..\inc\swilib.h"

__thumb void Hex2Num(char *hex, char *num, int len)
{
	int c;
	int i=0,j;
	char *p=hex;
	if(*p==0x91)
	{
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

int GetNumFromIncomingPDU(char *num)
{
	int c;
	char *p=(char *)IncommingPDU(); //ֱ�ӵ��ú�����õ�ַ
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

#ifdef NEWSGOLD
#define MAX_RECORDS 5000
#define LEVEL1_RN	(41*41)
#define LEVEL2_RN	(41)
#else
#define MAX_RECORDS 1024
#define LEVEL1_RN	(0x20)
#endif

#define NUMBERS_MAX 5

#ifdef NEWSGOLD
#define LAST_NAME 0x23
#define FIRST_NAME 0x24
#define COMPANY_NAME 0x29
#define POST_NAME 0x6F
#define DISPLAY_NAME 0x60
#else
#define NICKNAME 0x12
#define LAST_NAME 0x23
#define FIRST_NAME 0x24
#define STREET 0x25
#define POSTCODE 0x26
#define CITY 0x27
#define COUNTRY 0x28
#define COMPANY_NAME 0x29
#define PHONE_OFFICE 0x2A
#define PHONE_FAX 0x2B
#define PHONE_MOBILE 0x2C
#define PHONE_NUMBER 0x2D
#define E_MAIL 0x2E
#define URL 0x2F
#define PICTURE 0x33
#define E_MAIL2 0x5D
#define PHONE_FAX2 0x5E
#define WALKY_TALKY_ID 0x6D
#endif

typedef struct
{
	WSHDR *name;
	char num[NUMBERS_MAX][32];
}CNTT;


int FindName(WSHDR *wsrc, char *num_needed)
{
const char *s_ab_main="0:\\System\\apo\\addr\\main"; 
#ifdef NEWSGOLD
const char *s_ab_entry="0:\\System\\apo\\addr\\data\\%02d\\%02d\\%02d";
#else
const char *s_ab_entry="0:\\System\\apo\\addr\\%02x\\%02x";
#endif

	int fin;
	unsigned int ul;
	char recname[128];

	AB_UNPRES ur;
	void *buffer;

#pragma pack(1)
	struct {
#ifdef NEWSGOLD
		long dummy1;
		short dummy2;
		char bitmap[MAX_RECORDS/8];
#else
		long dummy1;
		char bitmap[MAX_RECORDS/8];
#endif
	} ABmain;
#pragma pack()

	unsigned int rec=0;
	int fsz;
	CNTT contact;
	int isFound=0;
	contact.name=AllocWS(32);
	if ((buffer=malloc(65536)))
	{
		zeromem(&ABmain,sizeof(ABmain));
		if ((fin=fopen(s_ab_main, A_ReadOnly+A_BIN, P_READ, &ul))!=-1)
		{
#ifdef ELKA
			if (fread(fin,&ABmain,sizeof(ABmain),&ul)>=194)
#else
			if (fread(fin,&ABmain,sizeof(ABmain),&ul)==sizeof(ABmain))
#endif
			{
				fclose(fin,&ul);
				do
				{
#ifdef NEWSGOLD
					if (ABmain.bitmap[rec>>3]&(0x80>>(rec&7)))
#else
					if (ABmain.bitmap[rec>>3]&(1<<(rec&7)))
#endif
					{
#ifdef NEWSGOLD
						unsigned int rl1;
						unsigned int rl2;
						unsigned int rl3;
						rl1=rec/LEVEL1_RN;
						rl2=(rec%LEVEL1_RN)/LEVEL2_RN;
						rl3=rec%LEVEL2_RN;
						snprintf(recname, 128, s_ab_entry, rl1, rl2, rl3);
#else
						unsigned int rl1=rec/LEVEL1_RN;
						unsigned int r12=rec%LEVEL1_RN;
						snprintf(recname, 128, s_ab_entry, rl1, r12);
#endif
						if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
						{
							zeromem(&ur,sizeof(AB_UNPRES));
							fsz=lseek(fin,0,S_END,&ul,&ul);
							lseek(fin,0,S_SET,&ul,&ul);
							fread(fin,buffer,fsz,&ul);
							fclose(fin,&ul);
#ifdef NEWSGOLD
							UnpackABentry(&ur,((char *)buffer+8),fsz,0x28);
#else
							UnpackABentry(&ur,((char *)buffer+4),fsz-4,0x28);
#endif
							int i=0;
							while(i<ur.number_of_records)
							{
								AB_UNPRES_ITEM *r=ur.record_list+i;
								if (r->no_data!=1)
								{
									switch(GetTypeOfAB_UNPRES_ITEM(r->item_type))
									{
										case 0x05:
											if (r->item_type==LAST_NAME)
											{
												if (r->data)
												{
													wstrcpy(contact.name,(WSHDR *)(r->data));
												}
											}
											break;
										case 0x01:
										{
											PKT_NUM *p=(PKT_NUM*)r->data;
											unsigned int n=r->item_type;
											int j;
											unsigned int c;
#ifdef NEWSGOLD
											if (n!=106) n-=0x62;
											else n=4;
											if (n<5)
#else
											switch(r->item_type)
											{
												case PHONE_NUMBER:
													n=0;    break;
												case PHONE_OFFICE:
													n=1;    break;
												case PHONE_MOBILE:
													n=2;    break;
												case PHONE_FAX:
													n=3;    break;
												case PHONE_FAX2:
													n=4;    break;
												default:
													continue;
											}
#endif
											{
												if (p)
												{
													unsigned int c1;
													int m;
													int k=0;
													char *num0=contact.num[n];
													j=0;
													m=0;
													if (p->format==0x91)
														num0[k++]='+';
													while(j<p->data_size)
													{
														if (m&1) {c1=c>>4; j++;}
														else c1=(c=p->data[j])&0x0F;
														if (c1==0x0F) break;
														if (c1==0xA) c1='*';
														else if (c1==0xB) c1='#';
														else if (c1==0xC) c1='+';
														else if (c1==0xD) c1='?';
														else c1+='0';
														num0[k++]=c1;
														m++;
													}
													num0[k]=0;
													if(strstr(num0, num_needed))
														isFound=1;
												}
											}
											break;
										}
									}
								}
								i++;
							}
							FreeUnpackABentry(&ur,mfree_adr());
						}
						else
							break;
					}
					if(isFound)
					{
						break;
					}
					rec++;
				}
				while(rec<MAX_RECORDS);
			}
			else
			{
				fclose(fin,&ul);
			}
		}
		  mfree(buffer);
	}
	if(isFound)
		wstrcpy(wsrc, contact.name);
	FreeWS(contact.name);
	return (isFound);
}


void AddTheName(WSHDR *wsrc)
{
	char num[32];
	WSHDR *ws;
	char *new_msg;
	if(!GetNumFromIncomingPDU(num))return;
	if(strncmp(num,"1986",4)==0)//��Ϣ����
	{
           new_msg="״̬����!\n����:\n";
           strcpy(num,num+4);//ȥ��1986
	}
	else
	{
	   new_msg="����Ϣ!\n����:\n";
	}
	ws=AllocWS(32);
	if(!FindName(ws, num))//û���ҵ�
		str_2ws(ws, num, strlen(num));//������� 
	gb2ws(wsrc, new_msg, strlen(new_msg));//new_msgת����wsrc
	wstrcat(wsrc, ws);
	FreeWS(ws);
}

