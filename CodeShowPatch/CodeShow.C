/********************************************************************
   (C) Copyright free source ,by Bennie.Joe@Gmail.com  

	filename: 	CodeShow.c
	created:	2005-10-1
	author:		Bennie
	
	describe:	replaces provider name with custom format
	history:    2005-06-22 V2
*********************************************************************/


#define VERSION "2.0b"

#define BASEADDRESS			0xA1580000
#define CODESHOWDATAADDRESS	BASEADDRESS
#define IPCODETABLECOUNT	(BASEADDRESS+0x1E000)
#define REPEATSELECTTABLE	(BASEADDRESS+0x1F000)
#define LOCALNOINFOTABLE	(BASEADDRESS+0x1F100)
#define CODESHOWFLAG		0xFB
#define CODESHOWVERSION		2
#define MAXCITYNO			0x1FF


#define LOBYTE(w) ((byte)(w))
#define HIBYTE(w) ((byte)(((word)(w) >> 8) & 0xFF))

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int   dword;
typedef unsigned int   uint;

typedef struct WString{
	word* pstr;
	int unknown[3];
	int buflen;
}WSTRING; 

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


extern int strlen(const char*);
extern int memcmp(const void*, const void*, int size);
extern uint atou(const char*);
extern WSTRING*  WS_InitByZero(WSTRING*, word* buf, int count);
extern void GetCalleeNumber(int index, WSTRING *ws);
extern void UpdateWndItem(void* Countext, WSTRING* ws, int index); 
 
int GetProvAndCity(word *pBSTR, char *pNoStr);
void BSTRAdd(word *pDst, const word * pSrc, int Count );
word GetCode(byte *pBuf, dword Index);
word FindLocale(LOCALE *pLocale, int LocaleCount, int LocaleNo, int *nRepeatNum);
void AppendInfoW(WSTRING *pWS, WSTRING * pNo);

const word szUnknownUser[] 	= { 0x672A, 0x77E5, 0x53F7,0x7801, 0};
const word szErrorData[] 	= { 0x6570, 0x636E, 0x5E93, 0x9519, 0x8BEF, 0};
const word szLocalCode[] 	= { 0x672C, 0x5730, 0x53F7,0x7801, 0};
const word szSplit[] 		= { 0x2027, 0 };
const word szAddInfo[] 		= { 0x20, 0 };

/****************/
/* main program */
/****************/

void UpdateLocaleToItem(int Index, int NoIndex, void* Context)
{
	WSTRING ws1, ws2, *pws1, *pws2;
	word buf1[0x3E], buf2[0x3E];
	pws1 = WS_InitByZero(&ws1, buf1, 0x3D);
	pws2 = WS_InitByZero(&ws2, buf2, 0x3D);
	GetCalleeNumber(NoIndex, pws1);
	AppendInfoW(pws2, pws1);
	UpdateWndItem(Context, pws2, Index); 
}

//WString号码版本
void AppendInfoW(WSTRING *pWS, WSTRING * pNo)
{
	char szPNo[0x30];
	int i=0;
	for(; i<*pNo->pstr && i<0x2B; ++i)
	{
		szPNo[i] = pNo->pstr[i+1];
	}
	szPNo[i] = '\0';
	GetProvAndCity(pWS->pstr, szPNo);			
}

void memcpy(char *szDest, char *szSrc, int len)
{
  int i;
  for(i=0; i<len; i++)
    szDest[i] = szSrc[i];
  szDest[len] = 0;
}

word GetLocalNoInfo(char *szLocalNo, char *szLocalName)
{
	int i = 0;
	word len = 0;
	word no1, no2;
	int nLocalNo=atou(szLocalNo);
	int nLocalNum=*(int*)LOCALNOINFOTABLE;
	const char * pLocalInfo = (const char *)(LOCALNOINFOTABLE+20);
	for(; i< nLocalNum; ++i, pLocalInfo += 14)
	{
	    no1 = *(word *)(pLocalInfo);
	    no2 = *(word *)(pLocalInfo+2);
		if(no1 <= nLocalNo && nLocalNo <= no2)
		{
		    len = 5;
		    memcpy(szLocalName, (char *)(pLocalInfo+4), 10);
			break;
		}
	}
	return len;
}

//得到号码所对应的省市字串  
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

	pHead = (const CODESHOWHEAD *)CODESHOWDATAADDRESS;
	//校验数据库的有效性
	if(pHead->Flag != CODESHOWFLAG || pHead->Version != CODESHOWVERSION) {
		BSTRAdd(pBSTR, szErrorData, 4);	
		return 0;	
	}
	//得到省表和市表
	pProvince = (PROVINCE*)(CODESHOWDATAADDRESS+pHead->ProvinceTableOffset);
	pCity = (CITY*)(CODESHOWDATAADDRESS+pHead->CityTableOffset);
	//去掉国际码+86
	if(*pNoStr == '+')
		pNoStr += 3;

	//如果长度大于12，则包括IP前缀，下面滤去已知IP前缀
	CodeLen = strlen(pNoStr);
	if(CodeLen > 12)
	{
		int i = 0;
		const char * pIPCode = (const char *)(IPCODETABLECOUNT+4);
		for(; i< *(const int *)IPCODETABLECOUNT; ++i, pIPCode += 8)
		{
			if(!memcmp(pNoStr, pIPCode+1, *pIPCode)){
				pNoStr += *pIPCode;	
				if(!memcmp(pNoStr, "013", 3) || !memcmp(pNoStr, "015", 3))
					++pNoStr;
				break;
			}
		}
	}

	//得到长途电话区号表
	pLocale = (LOCALE*)(CODESHOWDATAADDRESS+pHead->LocaleTableOffset);
	//如果以0开头，则判断为是固定长途电话
	if(*pNoStr == '0')
	{
		++pNoStr;
		//判断是否是三位区号010和02x
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
		//得到区号，在区号表中查找对应的城市号
		CityNo = FindLocale(pLocale, pHead->LocaleCount, atou(pNoStr), &nRepeatNum); 
	}
	//如果是13x，则判定为移动电话
	else if(*pNoStr == '1' && (*(pNoStr+1) == '3' || *(pNoStr+1) == '5'))
	{
		char chTemp=*(pNoStr+1);
		bLocal = 2;
		pNoStr += 2;
		*(pNoStr+5) = '\0';
		//得到手机号码的前五位，在手机号码表中查找对应的城市号
		if(chTemp == '3')
		  CityNo = GetCode((byte *)(CODESHOWDATAADDRESS+pHead->CodeTableOffset), atou(pNoStr));
		else
		  CityNo = GetCode((byte *)(CODESHOWDATAADDRESS+0x20000), atou(pNoStr));
	}
	//如果不是长话和移动电话，判断为本地区号。或者不能在IP表中找到对应项。
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

	//如果城市号不在范围内	
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
		    bLocal = (memcmp(LocalCity.CityName, pCity[CityNo].CityName, 10) == 0);
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
			   bLocal = (memcmp(LocalCity.CityName, pCity[CityNo].CityName, 10) == 0);
		   }
		}
		if(bLocal == 1 && nLocalNum > 0 && nLocalNum < 200 && (memcmp(LocalProvince.ProvinceName, pProvince[pCity[CityNo].ProvinceNo].ProvinceName, 6) == 0))
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

//从手机号码表中查找对应的城市号
word GetCode(byte *pBuf, dword Index)
{
    word CodeL, CodeH;
    pBuf = pBuf + (Index + (Index>>3));					//每条记录9个bit,即Index*9/8
    Index &= 0x7;										//得到在字节内的偏移量
    CodeL = ((word)pBuf[0])>>Index ;					//低字节右移偏移量
    CodeH = ((pBuf[1]<<(15-Index)) & 0xFFFF)>>7;	    //高字节去掉高处无效位,并左移到合适的位置
    return (CodeH + CodeL);								//拼接高低字节,共9位
}

//从长话区号表中查找对应的城市号
word FindLocale(LOCALE *pLocale, int LocaleCount, int LocaleNo, int *nRepeatNum)
{
	//长话区号表是顺序存储的,下面是个简单的二分法查找.
	int j = 0;
    int i = 0, nStart = 0, nEnd = LocaleCount;

	//处理几个特殊的地区，这些地区有相同的区号，在二分法时结果不确定
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
	//二分法查找对应的城市号，区号表是升序存储的
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

//附加UNICODE字串到另一个字串上,结束标志是L'\0'或Count个字符
void BSTRAdd(word *pDst, const word * pSrc, int Count)
{
	uint nSize = *pDst, i=1;
	while(*pSrc != '\0' && i<=Count)
		*(pDst+ nSize + i++) = *pSrc++;
	*pDst = nSize+i-1;
}


