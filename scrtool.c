#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "scrtool.h"

//���п��
#pragma inline
void RunCUT(char *s)
{
 uint* addr = (uint*)GetFunctionPointer(s);
 if (addr){
   typedef void (*voidfunc)(); 
  #ifdef NEWSGOLD          
         voidfunc pp=(voidfunc)*(addr+4);
  #else 
         voidfunc pp=(voidfunc)addr; 
  #endif 
         SUBPROC((void*)pp);
 }
}

//���г���
#pragma inline
void RunAPP(char *s)
{
  if ((s)&&(strlen(s))){
      WSHDR *ws;
      ws=AllocWS(150);
      str_2ws(ws,s,128);
      ExecuteFile(ws,0,0);
      FreeWS(ws);
  }
}

//���е�ַ����
#pragma inline
void RunADR(char *s)
{  
  typedef void (*voidfunc)(); 
  uint addr=strtoul(s, 0, 16 );
  voidfunc pp=(voidfunc)addr;
  SUBPROC((void*)pp); 
}

int extstrcmp(char *a,char *b)
{
  int state=0,max=strlen(a);
  if(strlen(a)>strlen(b)) max = strlen(b);
  for(int i=0;i<max;i++){
    if(a[i]!=b[i]){state=0; break;}else{state=1;}
  } 
  return(state);
}
#pragma inline
void BSTRAdd(word *pDst, const word * pSrc, int Count)
{
  uint nSize = *pDst, i=1;
  while(*pSrc != '\0' && i<=Count) *(pDst+ nSize + i++) = *pSrc++;
  *pDst = nSize+i-1;
}

//����ũ������
#pragma inline
void GetDayOf(TDate pSt,TNongLi *NongLiData)
{ 
/*�������*/
//const char *cTianGan[] = {"��","��","��","��","��","��","��","��","��","��"};
const word cTianGan[] = {0x7532,0x4E59,0x4E19,0x4E01,0x620A,0x5DF1,0x5E9A,0x8F9B,0x58EC,0x7678,0};  
/*��֧����*/
//const char *cDiZhi[] = {"��","��","��","î","��","��","��","δ","��","��","��","��"};
const word cDiZhi[] = {0x5B50,0x4E11,0x5BC5,0x536F,0x8FB0,0x5DF3,0x5348,0x672A,0x7533,0x9149,0x620C,0x4EA5,0};
/*��������*/
//const char *cShuXiang[] = {"��","ţ","��","��","��","��","��","��","��","��","��","��"};
const word cShuXiang[] = {0x9F20,0x725B,0x864E,0x5154,0x9F99,0x86C7,0x9A6C,0x7F8A,0x7334,0x9E21,0x72D7,0x732A,0};
/*ũ��������*/
/*const char *cDayName[] = {"*","��һ","����","����","����","����","����","����","����","����","��ʮ",
                                "ʮһ","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","��ʮ",
                                "إһ","إ��","إ��","إ��","إ��","إ��","إ��","إ��","إ��","��ʮ"};*/
const word cDayName[][2] = {{0x002A},
{0x521D,0x4E00},{0x521D,0x4E8C},{0x521D,0x4E09},
{0x521D,0x56DB},{0x521D,0x4E94},{0x521D,0x516D},{0x521D,0x4E03},
{0x521D,0x516B},{0x521D,0x4E5D},{0x521D,0x5341},{0x5341,0x4E00},
{0x5341,0x4E8C},{0x5341,0x4E09},{0x5341,0x56DB},{0x5341,0x4E94},
{0x5341,0x516D},{0x5341,0x4E03},{0x5341,0x516B},{0x5341,0x4E5D},
{0x4E8C,0x5341},{0x5EFF,0x4E00},{0x5EFF,0x4E8C},{0x5EFF,0x4E09},
{0x5EFF,0x56DB},{0x5EFF,0x4E94},{0x5EFF,0x516D},{0x5EFF,0x4E03},
{0x5EFF,0x516B},{0x5EFF,0x4E5D},{0x4E09,0x5341},{0,0}};
/*ũ���·���*/
/*const char *cMonName[] = {"*","��","��","��","��","��","��","��","��","��","ʮ","��","��"};*/
const word cMonName[] = {0x002A,0x6B63,0x4E8C,0x4E09,0x56DB,0x4E94,0x516D,0x4E03,0x516B,0x4E5D,0x5341,0x7545,0x814A,0};
/*��������:��,��,��*/
const word cOtherName[] = {0x5E74,0x6708,0x95F0,0};
/*����ÿ��ǰ�������*/
const int wMonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
/*ũ������*/
const int wNongliData[100] = {2635  ,333387,1701,1748,267701,694,2391,133423,1175,396438
                             ,3402  ,3749  ,331177,1453,694,201326,2350,465197,3221,3402
                             ,400202,2901  ,1386,267611,605,2349,137515,2709,464533,1738
                             ,2901  ,330421,1242,2651,199255,1323,529706,3733,1706,398762
                             ,2741  ,1206  ,267438,2647,1318,204070,3477,461653,1386,2413
                             ,330077,1197  ,2637,268877,3365,531109,2900,2922,398042,2395
                             ,1179  ,267415,2635,661067,1701,1748,398772,2742,2391,330031
                             ,1175  ,1611  ,200010,3749,527717,1452,2742,332397,2350,3222
                             ,268949,3402  ,3493,133973,1386,464219,605,2349,334123,2709
                             ,2890  ,267946,2773,592565,1210,2651,395863,1323,2707,265877};
static int wCurYear,wCurMonth,wCurDay;
static int nTheDate,nIsEnd,m,k,n,i,nBit;
word UniToday[5];
/*---ȡ��ǰ�����ꡢ�¡���---*/
wCurYear = pSt.year;
wCurMonth = pSt.month;
wCurDay = pSt.day;
/*---���㵽��ʼʱ��1921��2��8�յ�������1921-2-8(���³�һ)---*/
nTheDate = (wCurYear - 1921) * 365 + (wCurYear - 1921) / 4 + wCurDay + wMonthAdd[wCurMonth - 1] - 38;
if((!(wCurYear % 4)) && (wCurMonth > 2))
  nTheDate = nTheDate + 1;

/*--����ũ����ɡ���֧���¡���---*/
nIsEnd = 0;
m = 0;
while(nIsEnd != 1)
{
  if(wNongliData[m] < 4095)
   k = 11;
  else
   k = 12;
  n = k;
  while(n>=0)
  {
   //��ȡwNongliData(m)�ĵ�n��������λ��ֵ
   nBit = wNongliData[m];
   for(i=1;i<n+1;i++)
    nBit = nBit/2;

   nBit = nBit % 2;

   if (nTheDate <= (29 + nBit))
   {
    nIsEnd = 1;
    break;
   }

   nTheDate = nTheDate - 29 - nBit;
   n = n - 1;
  }
  if(nIsEnd)
   break;
  m = m + 1;
}
wCurYear = 1921 + m;
wCurMonth = k - n + 1;
wCurDay = nTheDate;
if (k == 12)
{
  if (wCurMonth == wNongliData[m] / 65536 + 1)
   wCurMonth = 1 - wCurMonth;
  else if (wCurMonth > wNongliData[m] / 65536 + 1)
   wCurMonth = wCurMonth - 1;
}

/*--����ũ����ɡ���֧������ ==> wNongli--*/
CutWSTR(NongLiData->year,0);
UniToday[0] = cTianGan[((wCurYear - 4) % 60) % 10];   //���
UniToday[1] = cDiZhi[((wCurYear - 4) % 60) % 12];     //��֧
UniToday[2] = cShuXiang[((wCurYear - 4) % 60) % 12];  //����
UniToday[3] = cOtherName[0];                          //��
BSTRAdd(NongLiData->year->wsbody,UniToday,4);
/*--����ũ���� --*/
CutWSTR(NongLiData->monthday,0);
if (wCurMonth < 1)                            //����
{
    UniToday[0] = cOtherName[2];                //��
    UniToday[1] = cMonName[-1 * wCurMonth];
    BSTRAdd(NongLiData->monthday->wsbody,UniToday,2);
}
else
{
    UniToday[0] = cMonName[wCurMonth];
    BSTRAdd(NongLiData->monthday->wsbody,UniToday,1);
}
  UniToday[0] = cOtherName[1];                //��
  BSTRAdd(NongLiData->monthday->wsbody,UniToday,1);
/*--����ũ���� --*/  
  UniToday[0] = cDayName[wCurDay][0];  
  UniToday[1] = cDayName[wCurDay][1]; 
  BSTRAdd(NongLiData->monthday->wsbody,UniToday,2);  
}  

#pragma inline
int get_string_width(WSHDR *ws, int font)
{
  int width=0;
  word *body=ws->wsbody;
  int l=body[0];
  while(l){
    width+=GetSymbolWidth(body[l],font);
    l--;
  }
  return (width);
}
#pragma inline
void FillIDS(TSCR *Info,int x_start,int y_start, int font,const char *color,const char *colorframe)
{  
  Info->rc.x=x_start;
  Info->rc.y=y_start;
  Info->rc.x2=x_start+get_string_width(Info->ws,font);
  Info->rc.y2=y_start+GetFontYSIZE(font);
  Info->font=font;
  memcpy(Info->pen,color,4);
  memcpy(Info->frame,colorframe,4);
}
#pragma inline  
int wsprintf_bytes(WSHDR *ws, uint bytes)
{
  if (bytes<=1024)
    return (wsprintf(ws,BYTES_FMT,bytes,BYTES_SG));
  else{
    bytes>>=10;
    return (wsprintf(ws,BYTES_FMT,bytes,KBYTES_SG));
  }  
}
