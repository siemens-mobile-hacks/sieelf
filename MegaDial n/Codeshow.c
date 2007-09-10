/********************************************************************
   (C) Copyright free source ,by Bennie.Joe@Gmail.com  

	filename: 	CodeShow.c
	created:	2005-10-1
	author:		Bennie
	
	describe:	replaces provider name with custom format
	history:    2005-06-22 V2
*********************************************************************/
#define VERSION "2.0b"
#include "..\inc\swilib.h"
#include "extern.h"
extern int cs_adr;
#define BASEADDRESS			cs_adr
#define CODESHOWDATAADDRESS	BASEADDRESS
#define IPCODETABLECOUNT	(BASEADDRESS+0x1E000)
#define REPEATSELECTTABLE	(BASEADDRESS+0x1F000)
#define LOCALNOINFOTABLE	(BASEADDRESS+0x1F100)
#define CODESHOWFLAG		0xFB
#define CODESHOWVERSION		2
#define MAXCITYNO			0x1FF

#define byte unsigned char
#define dword int
#define word unsigned short
#define uint unsigned int

#define LOBYTE(w) ((byte)(w))
#define HIBYTE(w) ((byte)(((word)(w) >> 8) & 0xFF))

typedef struct {
    byte Flag;
    byte ID;
    byte Version;
    byte Year;
    byte Month;
    byte Day;
    byte ProvinceNameLen;
    byte CityNameLen;
    dword CodeTableOffset;
    dword CodeCount;
    dword LocaleTableOffset;
    dword LocaleCount;
    dword ProvinceTableOffset;
    dword ProvinceCount;
    dword CityTableOffset;
    dword CityCount;
}CODESHOWHEAD;

#pragma pack(2)
typedef struct {
    word ProvinceName[3];
    word StartOffset;
    word EndOffset;
}PROVINCE;

typedef struct {
    word CityName[6];
    word LocaleNo     :10;
    word ProvinceNo   :6;
}CITY;
#pragma pack()

typedef struct {
    word LocaleNo;
    word CityNo;
}LOCALE;

extern const int cfg_cs_split;
 
int GetProvAndCity(word *pBSTR, char *pNoStr);
void BSTRAdd(word *pDst, const word * pSrc, int Count );
word GetCode(byte *pBuf, dword Index);
word FindLocale(LOCALE *pLocale, int LocaleCount, int LocaleNo, int *nRepeatNum);
void AppendInfoW(WSHDR *pWS, WSHDR * pNo);

const word szUnknownUser[] 	= { 0x672A, 0x77E5, 0x53F7,0x7801, 0};
const word szErrorData[] 	= { 0x6570, 0x636E, 0x5E93, 0x9519, 0x8BEF, 0};
const word szLocalCode[] 	= { 0x672C, 0x5730, 0x53F7,0x7801, 0};
word szSplit[] 		= { 0x2027, 0 };
const word szAddInfo[] 		= { 0x20, 0 };

/****************/
/* main program */
/****************/

word GetLocalNoInfo(char *szLocalNo, char *szLocalName)
{
	int i = 0;
	word len = 0;
	word no1, no2;
	int nLocalNo=strtoul(szLocalNo,&szLocalNo,10);
	int nLocalNum=*(int*)LOCALNOINFOTABLE;
	const char * pLocalInfo = (const char *)(LOCALNOINFOTABLE+20);
	for(; i< nLocalNum; ++i, pLocalInfo += 14)
	{
	    no1 = *(word *)(pLocalInfo);
	    no2 = *(word *)(pLocalInfo+2);
		if(no1 <= nLocalNo && nLocalNo <= no2)
		{
		    len = 5;
		    memcpy(szLocalName, (pLocalInfo+4), 10);
			break;
		}
	}
	return len;
}

//�õ���������Ӧ��ʡ���ִ�  
int GetProvAndCity(word *pBSTR, char *pNoStr)
{
	int bLocal=0;
    char szLocalNo[5];
	word CityNo = MAXCITYNO;
	char szLocalInfo[11];
	const PROVINCE * pProvince;
	const CITY* pCity;
	LOCALE *pLocale;
	const CODESHOWHEAD * pHead;
	int CodeLen;
	int nLocalNum=*(int*)LOCALNOINFOTABLE;
	const PROVINCE LocalProvince=*(PROVINCE*)(LOCALNOINFOTABLE+4);
	const CITY LocalCity=*(CITY*)(LOCALNOINFOTABLE+10);
	int nRepeatNum=1;

	szSplit[0] = cfg_cs_split;
	pHead = (const CODESHOWHEAD *)CODESHOWDATAADDRESS;
	//У�����ݿ����Ч��
	if(pHead->Flag != CODESHOWFLAG || pHead->Version != CODESHOWVERSION) {
		BSTRAdd(pBSTR, szErrorData, 4);	
		return 0;	
	}
	//�õ�ʡ����б�
	pProvince = (PROVINCE*)(CODESHOWDATAADDRESS+pHead->ProvinceTableOffset);
	pCity = (CITY*)(CODESHOWDATAADDRESS+pHead->CityTableOffset);
	//ȥ��������+86
	if(*pNoStr == '+')
		pNoStr += 3;

	//������ȴ���12�������IPǰ׺��������ȥ��֪IPǰ׺
	CodeLen = strlen(pNoStr);
	if(CodeLen > 12)
	{
		int i = 0;
		const char * pIPCode = (const char *)(IPCODETABLECOUNT+4);
		for(; i< *(const int *)IPCODETABLECOUNT; ++i, pIPCode += 8)
		{
			if(!memcmp(pNoStr, (void*)(pIPCode+1), *pIPCode)){
				pNoStr += *pIPCode;	
				if(!memcmp(pNoStr, "013", 3) || !memcmp(pNoStr, "015", 3))
					++pNoStr;
				break;
			}
		}
	}

	//�õ���;�绰���ű�
	pLocale = (LOCALE*)(CODESHOWDATAADDRESS+pHead->LocaleTableOffset);
	//�����0��ͷ�����ж�Ϊ�ǹ̶���;�绰
	if(*pNoStr == '0')
	{
		++pNoStr;
		//�ж��Ƿ�����λ����010��02x
		if(*pNoStr == '1' || *pNoStr == '2')
		{
			memcpy(szLocalNo, pNoStr+2, 4);
			*(pNoStr+2) = '\0';
		}
		else
		{
			memcpy(szLocalNo, pNoStr+3, 4);
			*(pNoStr+3) = '\0';	
		}
		//�õ����ţ������ű��в��Ҷ�Ӧ�ĳ��к�
		CityNo = FindLocale(pLocale, pHead->LocaleCount, strtoul(pNoStr,&pNoStr,10), &nRepeatNum); 
	}
	//�����13x�����ж�Ϊ�ƶ��绰
	else if(*pNoStr == '1' && (*(pNoStr+1) == '3' || *(pNoStr+1) == '5'))
	{
		char chTemp=*(pNoStr+1);
		bLocal = 2;
		pNoStr += 2;
		*(pNoStr+5) = '\0';
		//�õ��ֻ������ǰ��λ�����ֻ�������в��Ҷ�Ӧ�ĳ��к�
		if(chTemp == '3')
		  CityNo = GetCode((byte *)(CODESHOWDATAADDRESS+pHead->CodeTableOffset), strtoul(pNoStr,&pNoStr,10));
		else
		  CityNo = GetCode((byte *)(CODESHOWDATAADDRESS+0x20000), strtoul(pNoStr,&pNoStr,10));
	}
	//������ǳ������ƶ��绰���ж�Ϊ�������š����߲�����IP�����ҵ���Ӧ�
	else
	{
		BSTRAdd(pBSTR, szLocalCode, 4);	
		if(nLocalNum > 0 && nLocalNum < 200)
		{
		  memcpy(szLocalNo, pNoStr, 4);
		  if(GetLocalNoInfo(szLocalNo, szLocalInfo))
		  {
		    BSTRAdd(pBSTR, szAddInfo, 1);
			BSTRAdd(pBSTR, (word *)szLocalInfo, 5);
		  }
		}
		return 0;
	}

	//������кŲ��ڷ�Χ��	
	if(CityNo >= pHead->CityCount){
		BSTRAdd(pBSTR, szUnknownUser, 4);	
		return 0;
	}
	else{
		if(nRepeatNum == 1)
		{
		  BSTRAdd(pBSTR, pProvince[pCity[CityNo].ProvinceNo].ProvinceName, 3);
		  BSTRAdd(pBSTR, szSplit, 1);
		  BSTRAdd(pBSTR, pCity[CityNo].CityName, 5);
		  if(bLocal == 0)
		    bLocal = (memcmp((void*)LocalCity.CityName, (void*)pCity[CityNo].CityName, 10) == 0);
		}
		else
		{
		  int i;
		  BSTRAdd(pBSTR, pProvince[pCity[pLocale[CityNo].CityNo].ProvinceNo].ProvinceName, 3);
		  BSTRAdd(pBSTR, szSplit, 1);
		  for(i=0; i<nRepeatNum; i++)
		  {
		     if(nRepeatNum < 3)
			   BSTRAdd(pBSTR, szAddInfo, 1);
		     BSTRAdd(pBSTR, pCity[pLocale[i+CityNo].CityNo].CityName, 5);
			 if(bLocal == 0)
			   bLocal = (memcmp((void*)LocalCity.CityName, (void*)pCity[CityNo].CityName, 10) == 0);
		   }
		}
		if(bLocal == 1 && nLocalNum > 0 && nLocalNum < 200 && (memcmp((void*)LocalProvince.ProvinceName, (void*)pProvince[pCity[CityNo].ProvinceNo].ProvinceName, 6) == 0))
		{
		  if(GetLocalNoInfo(szLocalNo, szLocalInfo))
		  {
	        BSTRAdd(pBSTR, szAddInfo, 1);
		    BSTRAdd(pBSTR, (word *)szLocalInfo, 5);
		  }
		}
		return 1;
	}
}

//���ֻ�������в��Ҷ�Ӧ�ĳ��к�
word GetCode(byte *pBuf, dword Index)
{
    word CodeL, CodeH;
    pBuf = pBuf + (Index + (Index>>3));					//ÿ����¼9��bit,��Index*9/8
    Index &= 0x7;										//�õ����ֽ��ڵ�ƫ����
    CodeL = ((word)pBuf[0])>>Index ;					//���ֽ�����ƫ����
    CodeH = ((pBuf[1]<<(15-Index)) & 0xFFFF)>>7;	    //���ֽ�ȥ���ߴ���Чλ,�����Ƶ����ʵ�λ��
    return (CodeH + CodeL);								//ƴ�Ӹߵ��ֽ�,��9λ
}

//�ӳ������ű��в��Ҷ�Ӧ�ĳ��к�
word FindLocale(LOCALE *pLocale, int LocaleCount, int LocaleNo, int *nRepeatNum)
{
	//�������ű���˳��洢��,�����Ǹ��򵥵Ķ��ַ�����.
	int j = 0;
    int i = 0, nStart = 0, nEnd = LocaleCount;

	//����������ĵ�������Щ��������ͬ�����ţ��ڶ��ַ�ʱ�����ȷ��
	*nRepeatNum = 0;
/*	
	while(i < *(int*)REPEATSELECTTABLE)
	{
		if(	LocaleNo == *(word*)(REPEATSELECTTABLE+4+i*4))
		{
			return *(word*)(REPEATSELECTTABLE+6+i*4);
		}
		++i;
	}*/
	//���ַ����Ҷ�Ӧ�ĳ��кţ����ű�������洢��
	while(nStart <= nEnd)
    {
        i = (nEnd+nStart)/2;

        if(LocaleNo == pLocale[i].LocaleNo)
		{
			do
			{
			  if(LocaleNo != pLocale[i].LocaleNo)
			    break;
			  i--;
			}
			while(i > 0);
			i++;
			j = i;
			do
			{
			  if(LocaleNo != pLocale[j].LocaleNo)
			    break;
			  j++;
			  (*nRepeatNum)++;
			}
			while(j <= nEnd);
            break;
		}
        if(LocaleNo < pLocale[i].LocaleNo)
            nEnd   = i-1;
        else
            nStart = i+1;
    }
	if(*nRepeatNum > 1)
	  return	i;
	else
      return	(nStart > nEnd)? MAXCITYNO:pLocale[i].CityNo;
}

//����UNICODE�ִ�����һ���ִ���,������־��L'\0'��Count���ַ�
void BSTRAdd(word *pDst, const word * pSrc, int Count)
{
	uint nSize = *pDst, i=1;
	while(*pSrc != '\0' && i<=Count)
		*(pDst+ nSize + i++) = *pSrc++;
	*pDst = nSize+i-1;
}


