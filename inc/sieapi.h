#ifndef _SIEAPI_H_
#define _SIEAPI_H_ 
 #ifndef _SYSTEM_BUILD
  #pragma system_include
 #endif
 #include <ysizet.h>
 #include <math.h>
_C_STD_BEGIN
 //�������Ĭ���̷�
#ifdef NEWSGOLD
  #ifdef ELKA
   #define DEFAULT_DISK "4"
  #else
   #define DEFAULT_DISK "0"
  #endif //newsgold
#else
  #define DEFAULT_DISK "0"
#endif //newsgold
 //������������ 
#define byte    short int
#define ubyte   unsigned short int
#define uword   unsigned short
#define uint    unsigned int
#define ulong   unsigned long
#define uchar   unsigned char
#define TVoid   typedef void
#define TStruct typedef struct 
#define LunarMaxYear 2050
#define LunarMinYear 1901
 //����������������0-16!
 #define FontSyEN "Large","Large bold","Large italic","Large italic bold","Medium","Medium bold","Medium italic","Medium italic bold","Small","Small bold","Small italic","Small italic bold","Numeric small","Numeric small bold","Numeric xsmall","Numeric large","Numeric medium"
 #define FontSyCN "�������","��żӴ�","���б��","��Ŵ�б","�к�����","�кżӴ�","�к���б","�кŴ�б","С������","С�żӴ�","С��б��","С�Ŵ�б","С������","С������","��С����","�������","�к�����"
 //#define IS_FOLDER 1 //�����ļ��в���
 //#define IS_FILE 0  //�����ļ�����
 
 //����ũ�����ͽṹ
 TStruct{
  WSHDR *year;//���
  WSHDR *mday;//�·�
 }TNongLi;
 //������������
 TStruct{
  int t;//top
  int l;//left
  int r;//Right;
  int b;//Bottom;
 }TRect;
 //������������
 TStruct{
  char Pen[4];//������ɫ
  char Brush[4];//�߿���ɫ
  byte Size;//�����С
 }TFont;
 //�����ļ��ṹ
 TStruct{
  void *next;
  char *file;
  char *path;
  int   type;//1Ϊ�ļ���,0Ϊ�ļ�
 }TFile;
 //�����ļ��ṹ
 TStruct{
  void *next;
  char *name;
  uint  cmd;//Ϊִ�й��ܴ���
 }TMenu;
 //����ʱ��ṹ
 TStruct{
  ulong year;
  uchar month;
  uchar day; 
  uchar hour;
  uchar min;
  uchar sec;
  ulong millisec;
 }TDateTime;
 //���庯�������ṹ
_C_LIB_DECL
 __INTRINSIC ulong strtoul(const char *nptr,char **endptr,int base); 
 __INTRINSIC int  strlpos(char *str,char c); 
 //��ȡ���ֻ���Ӧ�����ı��ĳ���
 __INTRINSIC int  get_string_width(WSHDR *ws, int font); 
 //�ִ��ȽϺ���
 __INTRINSIC int  toupper(int c);
 __INTRINSIC int  ExtStrcmp(char *a,char *b);
 __INTRINSIC int  strcmp_nocase(const char *s1,const char *s2); 
 //��Ļ���Ʒ�Χ����
 __INTRINSIC void patch_rect(RECT*rc,int x,int y, int x2, int y2);//�趨����
 __INTRINSIC void patch_header(const HEADER_DESC* head);//�趨ͷ����
 __INTRINSIC void patch_input(const INPUTDIA_DESC* inp);//�趨��������
 __INTRINSIC void patch_dialog(INPUTDIA_DESC* dialog, int x,int y,int x2, int y2);//�趨�Ի�������
 //�򿪳����Ӧ��Ĭ�������ļ�(*.BCFG)
 __INTRINSIC void OpenBCFGFile(void);
 //�ض��廭������
 __INTRINSIC void DrawCanvasExt(void *canvas, RECT rc,int mode);
 __INTRINSIC void DrawCanvasRect(void *canvas, TRect rc,int mode);
 __INTRINSIC void DrawStringExt(WSHDR *ws,RECT rc,TFont Font,int text_attribute);
 __INTRINSIC void DrawStringRect(WSHDR *ws,TRect rc,TFont Font,int text_attribute);
 //�ͷų����ڴ�
 __INTRINSIC void kill_data(void *p, void (*func_p)(void *));
 //�ִ�ת������
 __INTRINSIC void str2ws_unicode(WSHDR* ws, char* str, int len);
 __INTRINSIC void ws2str_unicode(char* str, WSHDR* ws, int *len);
 __INTRINSIC char* unicodeSwitch(char *str, int len, int *rlen, int *llen); 
 __INTRINSIC char* utf82unicode(char *str, int len, int *rlen, int *llen); 
 __INTRINSIC char* unicode2utf8(char *str, int *len); 
 //UNICODE�������ӵ�WS������
 __INTRINSIC void BSTRAdd(uword *pDst, const uword * pSrc, int Count);
 //��ȡũ�����ں���
 __INTRINSIC void GetDayOf(TDate pSt,TNongLi *NongLiData);//��ȡũ���ִ�
 __INTRINSIC TDate GetOldDay(TDate pSt);//��ȡũ������
 //��ȡ�ļ�����չ��
 __INTRINSIC void CutFileExt(char *filename,char *ext);
 //�����ļ�����
 __INTRINSIC void RunCUT(char *s);//ִ�п��
 __INTRINSIC void RunAPP(char *s);//���ļ�
 __INTRINSIC void RunADR(char *s);//ִ�е�ַ 
 //UTF8�ļ��������ͷ�
 __INTRINSIC char *LoadFileBuf(const char *FileName);
 __INTRINSIC int  FreeFileBuf(char *Buffer);
 //��ȡ�ֻ��ڲ���Ӧ������
 __INTRINSIC uint FontType(int index);
 //���������ļ�,֧���ֻ��ڲ����������ļ�
 __INTRINSIC int PlayMusic(const char *fname, uint VOLUME, uint RepeatNum);
 //��̬�˵���������
 __INTRINSIC TMenu *BuildMenu(char *Title[]);
 __INTRINSIC void DrawMenu(void *gui, int cur_item, void *user_pointer);
 __INTRINSIC void FreeMenu(TMenu *Menu);
 __INTRINSIC int  MenuCount(TMenu *Menu);
 //�ļ��˵���غ���
 __INTRINSIC int  FileCount(TFile *File);
 __INTRINSIC void FreeFile(TFile *File);
 //ý�幦���Ƿ�ʹ����-------------
 __INTRINSIC int IsMediaActive(void);
 //ʮ������ת��Ϊʮ����-----------
 __INTRINSIC ulong HexToInt(char *HEX);
 //����ת��
 __INTRINSIC void  Ascii2WS(uword *data,WSHDR *ws, const char *s, int maxlen);
 __INTRINSIC void  WS2Ascii(uword *data, WSHDR *ws, char *s, int maxlen);
 __INTRINSIC void  FreeFontLib(uword *data);//�ͷ��ֿ��ڴ�
 __INTRINSIC uword *LoadFontLib(void);//�����ֿ��ڴ�
 //��ʮ�Ľ���
 __INTRINSIC void  LunarHolDay(WSHDR* ws,int LunarId);//���ض�Ӧ�Ķ�ʮ�Ľ����ִ�
 __INTRINSIC int   LunarHolId(TDate date);//���ض�Ӧ�Ķ�ʮ�Ľ���ID(1..24)
 __INTRINSIC uchar LunarYearId(ulong year);// ����ĳ�����Ƿ�����
 __INTRINSIC uword BetweenDaySum(TDate start,TDate end);//����������֮�������
 __INTRINSIC uword GetDayFromYearBegin(ulong AYear,uchar AMonth,uchar ADay);// ȡĳ���ڵ����������
_END_C_LIB_DECL
_C_STD_END
//����ִ�д���
#pragma inline//��ȡc��str�ִ���λ��
int  getstrpos(char *str,char c)
{
  int cur = 0;
  for (int inx=1;inx<=strlen(str);inx++)
  {
    if(str[inx]==c){cur=inx;break;}
  }
  return cur;
}

#pragma inline//��ȡ���ļ�����
void CutFileExt(char *filename,char *ext)
{
  if(strlen(filename)>strlen(ext))filename[strlen(filename)-strlen(ext)]=0;
}
#pragma inline//���п��
void RunCUT(char *s)
{
 if ((s)&&(strlen(s))){
 uint* addr = (uint*)GetFunctionPointer(s);
 if (addr){
   TVoid (*voidfunc)(); 
  #ifdef NEWSGOLD          
         voidfunc pp=(voidfunc)*(addr+4);
  #else 
         voidfunc pp=(voidfunc)addr; 
  #endif 
         SUBPROC((void*)pp);
 }
 }
}
#pragma inline//����ELF����
void RunAPP(char *s)
{
  if ((s)&&(strlen(s))){
      WSHDR *ws=AllocWS(128);
      str_2ws(ws,s,strlen(s));
      ExecuteFile(ws, 0,0);
      FreeWS(ws);
  }
}
#pragma inline//���е�ַ����
void RunADR(char *s)
{  
  if ((s)&&(strlen(s))){
      TVoid (*voidfunc)(); 
      uint addr=strtoul(s, 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp); 
  }
}
#pragma inline//�ִ��ȽϺ���
int ExtStrcmp(char *a,char *b)
{
  int state=0,max=strlen(a);
  if(strlen(a)>strlen(b)) max = strlen(b);
  for(int i=0;i<max;i++){
    if(a[i]!=b[i]){state=0; break;}else{state=1;}
  } 
  return(state);
}
#pragma inline//���ݺϲ�
void BSTRAdd(uword *pDst, const uword * pSrc, int Count)
{
  uint nSize = *pDst, i=1;
  while(*pSrc != '\0' && i<=Count) *(pDst+ nSize + i++) = *pSrc++;
  *pDst = nSize+i-1;
}

#pragma inline//��ǰ����ת��Ϊũ������
TDate GetOldDay(TDate pSt)
{/*����ÿ��ǰ�������*/
const uword wMonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
/*ũ������*/
const ulong wNongliData[100] = {
0x00A4B,0x5164B,0x006A5,0x006D4,0x415B5,0x002B6,0x00957,0x2092F,0x00497,0x60C96,
0x00D4A,0x00EA5,0x50DA9,0x005AD,0x002B6,0x3126E,0x0092E,0x7192D,0x00C95,0x00D4A,
0x61B4A,0x00B55,0x0056A,0x4155B,0x0025D,0x0092D,0x2192B,0x00A95,0x71695,0x006CA,
0x00B55,0x50AB5,0x004DA,0x00A5B,0x30A57,0x0052B,0x8152A,0x00E95,0x006AA,0x615AA,
0x00AB5,0x004B6,0x414AE,0x00A57,0x00526,0x31D26,0x00D95,0x70B55,0x0056A,0x0096D,
0x5095D,0x004AD,0x00A4D,0x41A4D,0x00D25,0x81AA5,0x00B54,0x00B6A,0x612DA,0x0095B,
0x0049B,0x41497,0x00A4B,0xA164B,0x006A5,0x006D4,0x615B4,0x00AB6,0x00957,0x5092F,
0x00497,0x0064B,0x30D4A,0x00EA5,0x80D65,0x005AC,0x00AB6,0x5126D,0x0092E,0x00C96,
0x41A95,0x00D4A,0x00DA5,0x20B55,0x0056A,0x7155B,0x0025D,0x0092D,0x5192B,0x00A95,
0x00B4A,0x416AA,0x00AD5,0x90AB5,0x004BA,0x00A5B,0x60A57,0x0052B,0x00A93,0x40E95};
static int wCurYear,wCurMonth,wCurDay;
static int nTheDate,nIsEnd,m,k,n,i,nBit;
TDate OldDay;
/*---ȡ��ǰ�����ꡢ�¡���---*/
wCurYear  = pSt.year;
wCurMonth = pSt.month;
wCurDay   = pSt.day;
/*---���㵽��ʼʱ��1921��2��8�յ�������1921-2-8(���³�һ)---*/
nTheDate = (wCurYear - 1921) * 365 + (wCurYear - 1921) / 4 + wCurDay + wMonthAdd[wCurMonth - 1] - 38;
if((!(wCurYear % 4)) && (wCurMonth > 2))
  nTheDate = nTheDate + 1;

/*--����ũ����ɡ���֧���¡���---*/
nIsEnd = 0;
m      = 0;
while(nIsEnd != 1)
{
  if(wNongliData[m] < 4095)  k = 11; else k = 12;
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
wCurYear  = 1921 + m;
wCurMonth = k - n + 1;
wCurDay   = nTheDate;
if (k == 12)
{
  if (wCurMonth == wNongliData[m] / 65536 + 1)
      wCurMonth = 1 - wCurMonth;
  else if (wCurMonth > wNongliData[m] / 65536 + 1)
      wCurMonth = wCurMonth - 1;
}
OldDay.year =wCurYear;
OldDay.month=wCurMonth;
OldDay.day  =wCurDay;
return(OldDay);
}

#pragma inline//��ȡũ��������Ϣ
void GetDayOf(TDate pSt,TNongLi *NongLiData)
{ 
/*�������*/
//const char *cTianGan[] = {"��","��","��","��","��","��","��","��","��","��"};
const uword cTianGan[] = {0x7532,0x4E59,0x4E19,0x4E01,0x620A,0x5DF1,0x5E9A,0x8F9B,0x58EC,0x7678,0};  
/*��֧����*/
//const char *cDiZhi[] = {"��","��","��","î","��","��","��","δ","��","��","��","��"};
const uword cDiZhi[] = {0x5B50,0x4E11,0x5BC5,0x536F,0x8FB0,0x5DF3,0x5348,0x672A,0x7533,0x9149,0x620C,0x4EA5,0};
/*��������*/
//const char *cShuXiang[] = {"��","ţ","��","��","��","��","��","��","��","��","��","��"};
const uword cShuXiang[] = {0x9F20,0x725B,0x864E,0x5154,0x9F99,0x86C7,0x9A6C,0x7F8A,0x7334,0x9E21,0x72D7,0x732A,0};
/*ũ��������*/
/*const char *cDayName[] = {"*","��һ","����","����","����","����","����","����","����","����","��ʮ",
                                "ʮһ","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","��ʮ",
                                "إһ","إ��","إ��","إ��","إ��","إ��","إ��","إ��","إ��","��ʮ"};*/
const uword cDayName[][2] = {{0x002A},
                            {0x521D,0x4E00},{0x521D,0x4E8C},{0x521D,0x4E09},{0x521D,0x56DB},
                            {0x521D,0x4E94},{0x521D,0x516D},{0x521D,0x4E03},{0x521D,0x516B},
                            {0x521D,0x4E5D},{0x521D,0x5341},{0x5341,0x4E00},{0x5341,0x4E8C},
                            {0x5341,0x4E09},{0x5341,0x56DB},{0x5341,0x4E94},{0x5341,0x516D},
                            {0x5341,0x4E03},{0x5341,0x516B},{0x5341,0x4E5D},{0x4E8C,0x5341},
                            {0x5EFF,0x4E00},{0x5EFF,0x4E8C},{0x5EFF,0x4E09},{0x5EFF,0x56DB},
                            {0x5EFF,0x4E94},{0x5EFF,0x516D},{0x5EFF,0x4E03},{0x5EFF,0x516B},
                            {0x5EFF,0x4E5D},{0x4E09,0x5341},{0,0}};
/*ũ���·���*/
/*const char *cMonName[] = {"*","��","��","��","��","��","��","��","��","��","ʮ","��","��"};*/
const uword cMonName[] = {0x002A,0x6B63,0x4E8C,0x4E09,0x56DB,0x4E94,0x516D,0x4E03,0x516B,0x4E5D,0x5341,0x51AC,0x814A,0};
/*��������:��,��,��*/
const uword cOtherName[] = {0x5E74,0x6708,0x95F0,0};
TDate old = GetOldDay(pSt);
/*--����ũ����ɡ���֧������ ==> wNongli--*/
uword UniToday[5];
CutWSTR(NongLiData->year,0);
UniToday[0] = cTianGan[ ((old.year - 4) % 60) % 10];  //���
UniToday[1] = cDiZhi[   ((old.year - 4) % 60) % 12];  //��֧
UniToday[2] = cShuXiang[((old.year - 4) % 60) % 12];  //����
UniToday[3] = cOtherName[0];                          //��
BSTRAdd(NongLiData->year->wsbody,UniToday,4);
/*--����ũ���� --*/
CutWSTR(NongLiData->mday,0);
if (old.month < 1)  //����
{
    UniToday[0] = cOtherName[2]; //��
    UniToday[1] = cMonName[-1 * old.month];
    BSTRAdd(NongLiData->mday->wsbody,UniToday,2);
}
else
{
    UniToday[0] = cMonName[old.month];
    BSTRAdd(NongLiData->mday->wsbody,UniToday,1);
}
  UniToday[0] = cOtherName[1]; //��
  BSTRAdd(NongLiData->mday->wsbody,UniToday,1);
/*--����ũ���� --*/  
  UniToday[0] = cDayName[old.day][0];  
  UniToday[1] = cDayName[old.day][1]; 
  BSTRAdd(NongLiData->mday->wsbody,UniToday,2);  
}  

#pragma inline
int get_string_width(WSHDR *ws, int font)
{  
  uword *body=ws->wsbody;
  int len=body[0],width;
  if(len>0)width=1;else width=0;
  while(len>0){
    width+=GetSymbolWidth(body[len],font);
    len--;
  }
  return (width);
}

#pragma inline=forced
int toupper(int c){ if ((c>='a')&&(c<='z')) c+='A'-'a';  return(c);}

#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i,c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}
#pragma inline
void str2ws_unicode(WSHDR* ws, char* str, int len)
 {
  int i = 0;
  char *p = str;
  while ((p - str) < len - 1) {
    ws->wsbody[++i] = (*(p + 1) << 8) + *p;
    p += 2;
  }
  ws->wsbody[0] = i;
}
#pragma inline
void ws2str_unicode(char* str, WSHDR* ws, int *len) 
{	//ע�ⷶΧ
  for (int i = 0; i < ws->wsbody[0]; i++) {
  	*(str + (i << 1)) = ws->wsbody[i + 1] & 0xFF;
  	*(str + (i << 1) + 1) = ws->wsbody[i + 1] >> 8;
	}
	*len = ws->wsbody[0] << 1;
}
#pragma inline
char* unicodeSwitch(char *str, int len, int *rlen, int *llen) 
{
  if (!str) return NULL;
  int i = 0, l = len >> 1 << 1;
  char *p = malloc(l);
  while (i < l) {
    *(p + i) = *(str + i + 1);
    *(p + i + 1) = *(str + i);
    i += 2;
  }
  *rlen = *llen = l;
  return p;
}
#pragma inline
char* utf82unicode(char *str, int len, int *rlen, int *llen) 
{
  if (!str) return NULL;
  
/*
  char *ms = malloc (50);
  sprintf(ms, "%d, %d", j, l);
  ShowMSG(1, (int) ms);
  mfree(ms);*/
  
  int i = 0, j = 0, l = len, bl = len << 1;
  char* s = malloc(bl);
  char c;
  *rlen = *llen = 0;
  bl -= 3;
  for (i = 0; i < l; i++) {
    c = str[i];
    if ((c >> 7) == 0x0) {  //���ֽڱ���
      s[j++] = c;
      s[j++] = 0x0;
      (*llen)++;
    }
    else if ((c >> 5) == 0x6 && i < l - 1) { //˫�ֽڱ���
      s[++j] = ((c & 0x1f) >> 2);
      s[j - 1] = c << 6;
      c = str[++i];
      s[j - 1] = s[j - 1] | (c & 0x3f);
      j++;
      (*llen) += 2;
    }
    else if ((c >> 4) == 0xe && i < l - 2) { //���ֽڱ���
      s[++j] = c << 4;
      c = str[++i];
      s[j] = s[j] | ((c >> 2) & 0xf);
      s[j - 1] = c << 6;
      c = str[++i];
      s[j - 1] = s[j - 1] | (c & 0x3f);
      j++;
      (*llen) += 3;
      
    }
    else
    	break;
    (*rlen) += 2;
  }

  if (*rlen < (l << 1)) {
   	char *r = malloc(*rlen);
   	memcpy(r, s, *rlen);
   	mfree(s);
   	s = r;
  }
  return s; 
}
#pragma inline
char* unicode2utf8(char *str, int *len) 
{
if (!str) return NULL;

  int i = 0, j = 0;
  char* s = malloc((*len) << 1);
  
  int c;
  for (i = 0; i < (*len) - 1; i += 2) {
    c = (str[i + 1] << 8) | str[i];
    if (c < 0x80) {  //���ֽڱ���
      s[j++] = (char) c;
    }
    else if (c > 0x7f && c < 0x800) { //˫�ֽڱ���
    	s[j++] = (c >> 6) | 0xc0;
    	s[j++] = c & 0x3f | 0x80;
    }
    else if (c > 0x7ff && c < 0x10000) { //���ֽڱ���
      s[j++] = (c >> 12) | 0xe0;
      s[j++] = (c >> 6) & 0x3f | 0x80;
      s[j++] = c & 0x3f | 0x80;
    }
  }
  *len = j;
  return s; 
}

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x =x;
  rc->y =y;
  rc->x2=x2;
  rc->y2=y2;
}

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}

#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}

#pragma inline
void patch_dialog(INPUTDIA_DESC* dialog, int x,int y,int x2, int y2)
{
  dialog->rc.x  = x;
  dialog->rc.y  = y;
  dialog->rc.x2 = x2;
  dialog->rc.y2 = y2;
}
#pragma inline
void OpenBCFGFile(void)
{   
  extern const char *successed_config_filename;
  if ((successed_config_filename)&&(strlen(successed_config_filename))){
   WSHDR *ws = AllocWS(150);
   str_2ws(ws, successed_config_filename, 128);
   ExecuteFile(ws, 0, 0);
   FreeWS(ws);
   GeneralFuncF1(1);
  }
}
#pragma inline
void DrawCanvasExt(void *canvas, RECT rc,int mode){ DrawCanvas(canvas, rc.x, rc.y, rc.x2, rc.y2, mode); }
#pragma inline
void DrawCanvasRect(void *canvas, TRect rc,int mode){ DrawCanvas(canvas, rc.l, rc.t, rc.r, rc.b, mode); }
#pragma inline
void DrawStringExt(WSHDR *ws,RECT rc,TFont Font,int text_attribute)
{ DrawString(ws, rc.x, rc.y, rc.x2, rc.y2, Font.Size,text_attribute,Font.Pen, Font.Brush); }
#pragma inline
void DrawStringRect(WSHDR *ws,TRect rc,TFont Font,int text_attribute)
{ DrawString(ws, rc.l, rc.t, rc.r, rc.b, Font.Size,text_attribute,Font.Pen, Font.Brush); }
#pragma inline//�����ļ�������
char *LoadFileBuf(const char *FileName)
{
  int f;
  char *buf=0;  
  uint err,fsize;  
  if ((f=fopen(FileName,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
  {
   fsize  =lseek(f,0,S_END,&err,&err);
   if (fsize<=0){
     fclose(f,&err);     
   }else{       
    lseek(f,0,S_SET,&err,&err);
    buf=malloc(fsize+1);
    fread(f,buf,fsize,&err);    
    fclose(f,&err); 
    buf[fsize]=0;   
   }
  }
  return(buf);
}
#pragma inline//�ͷ��ļ�������
int FreeFileBuf(char *Buffer)
{
  if(Buffer){
    mfree(Buffer);
    return(1);
  }else return(0);
}
#pragma inline//��ȡ��������
uint FontType(int index)
{
 switch(index){
 #ifdef NEWSGOLD
  #ifdef ELKA
     case  0:return(0);//#define FONT_LARGE 0
     case  1:return(1);//#define FONT_LARGE_BOLD 1
     case  2:return(2);//#define FONT_LARGE_ITALIC 2
     case  3:return(3);//#define FONT_LARGE_ITALIC_BOLD 3
     case  4:return(4);//#define FONT_MEDIUM 4
     case  5:return(5);//#define FONT_MEDIUM_BOLD 5
     case  6:return(6);//#define FONT_MEDIUM_ITALIC 6
     case  7:return(7);//#define FONT_MEDIUM_ITALIC_BOLD 7
     case  8:return(8);//#define FONT_SMALL 8
     case  9:return(9);//#define FONT_SMALL_BOLD 9
     case 10:return(10);//#define FONT_SMALL_ITALIC 10
     case 11:return(11);//#define FONT_SMALL_ITALIC_BOLD 11
     case 12:return(8);//#define FONT_NUMERIC_SMALL 8
     case 13:return(9);//#define FONT_NUMERIC_SMALL_BOLD 9
     case 14:return(8);//#define FONT_NUMERIC_XSMALL 8
     case 15:return(0);//#define FONT_NUMERIC_LARGE 0
  default   :return(4);//#define FONT_NUMERIC_MEDIUM 4
  #else //#ifdef ELKA
     case  0:return(0);//#define FONT_LARGE 0
     case  1:return(1);//#define FONT_LARGE_BOLD 1
     case  2:return(0);//#define FONT_LARGE_ITALIC 0
     case  3:return(1);//#define FONT_LARGE_ITALIC_BOLD 1
     case  4:return(2);//#define FONT_MEDIUM 2
     case  5:return(3);//#define FONT_MEDIUM_BOLD 3
     case  6:return(2);//#define FONT_MEDIUM_ITALIC 2
     case  7:return(3);//#define FONT_MEDIUM_ITALIC_BOLD 3
     case  8:return(7);//#define FONT_SMALL 7
     case  9:return(8);//#define FONT_SMALL_BOLD 8
     case 10:return(7);//#define FONT_SMALL_ITALIC 7
     case 11:return(8);//#define FONT_SMALL_ITALIC_BOLD 8
     case 12:return(4);//#define FONT_NUMERIC_SMALL 4
     case 13:return(5);//#define FONT_NUMERIC_SMALL_BOLD 5
     case 14:return(6);//#define FONT_NUMERIC_XSMALL 6
     case 15:return(9);//#define FONT_NUMERIC_LARGE 9
  default   :return(10);//#define FONT_NUMERIC_MEDIUM 10
  #endif //#ifdef NEWSGOLD
 #else //#ifdef NEWSGOLD
     case  0:return(0);//#define FONT_LARGE 0
     case  1:return(1);//#define FONT_LARGE_BOLD 1
     case  2:return(0);//#define FONT_LARGE_ITALIC 0
     case  3:return(1);//#define FONT_LARGE_ITALIC_BOLD 1
     case  4:return(2);//#define FONT_MEDIUM 2
     case  5:return(3);//#define FONT_MEDIUM_BOLD 3
     case  6:return(2);//#define FONT_MEDIUM_ITALIC 2
     case  7:return(3);//#define FONT_MEDIUM_ITALIC_BOLD 3
     case  8:return(7);//#define FONT_SMALL 7
     case  9:return(8);//#define FONT_SMALL_BOLD 8
     case 10:return(7);//#define FONT_SMALL_ITALIC 7
     case 11:return(8);//#define FONT_SMALL_ITALIC_BOLD 8
     case 12:return(4);//#define FONT_NUMERIC_SMALL 4
     case 13:return(5);//#define FONT_NUMERIC_SMALL_BOLD 5
     case 14:return(6);//#define FONT_NUMERIC_XSMALL 6
     case 15:return(9);//#define FONT_NUMERIC_LARGE 9
  default   :return(10);//#define FONT_NUMERIC_MEDIUM 10
 #endif //#ifdef NEWSGOLD
 }
}
#pragma inline//���������ļ�
int PlayMusic(const char *fname, uint VOLUME, uint RepeatNum)
{
  int Handle=0;
  if(!IsCalling()){
    FSTATS fstats;
    uint err;
    if (GetFileStats(fname,&fstats,&err)!=-1){
      PLAYFILE_OPT INFO;
      WSHDR* sndPath =AllocWS(128);
      WSHDR* sndName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);
      
      zeromem(&INFO,sizeof(PLAYFILE_OPT));
      INFO.repeat_num=RepeatNum;
      INFO.time_between_play=0;
      INFO.play_first=0;
      INFO.volume=VOLUME;
     #ifdef NEWSGOLD
      INFO.unk6=1;
      INFO.unk7=1;
      INFO.unk9=2;
      Handle=PlayFile(0x10, sndPath, sndName, MMI_CEPID, MSG_PLAYFILE_REPORT, &INFO);
     #else
      #ifdef X75
      INFO.unk4=0x80000000;
      INFO.unk5=1;
      Handle=PlayFile(0xC, sndPath, sndName, 0, MMI_CEPID, MSG_PLAYFILE_REPORT, &INFO);
      #else
      INFO.unk5=1;
      Handle=PlayFile(0xC, sndPath, sndName, MMI_CEPID, MSG_PLAYFILE_REPORT, &INFO);
      #endif
     #endif
      FreeWS(sndPath);
      FreeWS(sndName);
      return(Handle);
    }
  }
  return(Handle);
}
#pragma inline//�����ִ�����
uint CountTitle(char *Title[])
{
 int max=0;
 for (int i=0; Title[i]!=NULL; i++)
    max++;
 return(max-1); 
}
#pragma inline//�����˵�����
TMenu *BuildMenu(char *Title[])
{
  TMenu *Menu=0;
  for (int i=0; Title[i]!=NULL; i++)
  {
        TMenu *sbl=malloc(sizeof(TMenu));
        sbl->name=malloc(strlen(Title[i])+1);        
        strcpy(sbl->name,Title[i]);
        sbl->cmd=i;
        sbl->next=0;
        if (Menu)
        {
          TMenu *sbr, *sbt;
          sbr=(TMenu *)&Menu;
          sbt=Menu;
          while(strcmp_nocase(sbt->name,sbl->name)<0)
          {
            sbr=sbt;
            sbt=sbt->next;
            if (!sbt) break;
          }
          sbl->next=sbt;
          sbr->next=sbl;
        } else{Menu=sbl;}
  }
  return(Menu);
}
#pragma inline//�����˵��б�
void DrawMenu(void *gui, int cur_item, void *user_pointer)
{
  WSHDR *ws;
  TMenu *Menu=user_pointer;
  void *item=AllocMenuItem(gui);
  for (int n=0; n!=cur_item; n++) 
  {
    Menu=Menu->next;
  }  
  if (Menu)
  {
    int len=strlen(Menu->name);
    ws=AllocMenuWS(gui,len+4);
    //str_2ws(ws,Menu->name,len);
    utf8_2ws(ws,Menu->name,len);
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    wsprintf(ws,"%t","Error!");
  }    
  SetMenuItemText(gui, item, ws, cur_item);       
}
#pragma inline//�ͷŲ˵���Դ
void FreeMenu(TMenu *Menu)
{
  while(Menu){
      TMenu *sb=Menu;
      Menu=Menu->next;
      mfree(sb->name);
      mfree(sb);
  } 
  mfree(Menu);
}
#pragma inline//��ȡ�˵�����
int MenuCount(TMenu *Menu)
{
  int i=0;
  TMenu *sb=(TMenu*)&Menu;
  while((sb=sb->next)) i++;
  return (i);
}
#pragma inline//��ȡ�ļ�����
int FileCount(TFile *File)
{
  int i=0;
  TFile *sb=(TFile*)&File;
  while((sb=sb->next)) i++;
  return (i);
}
#pragma inline//�ͷ��ļ���Դ
void FreeFile(TFile *File)
{
  while(File){
      TFile *sb=File;
      File=File->next;
      mfree(sb->path);
      mfree(sb->file);
      mfree(sb);
  } 
  mfree(File);
}
#pragma inline//��ȡ����״̬
int IsMediaActive(void)
{
  char s[40];
  sprintf(s,RamMediaIsPlaying());
#ifdef NEWSGOLD
  if (s[0]==1) return 1;
#else
  if (s[0]==2) return 1;// SGOLD s[0]!=2    
#endif 
  return 0;
}
#pragma inline
ulong HexToInt(char *HEX) 
{ 
 ulong result=0; 
 for(int i=0 ; i<strlen(HEX) ; i++) 
 { 
  if(*(HEX+i)>='A'&&*(HEX+i)<='F') 
  { 
   result*=16; 
   result+=*(HEX+i)-'A'+10; 
  } 
  if(*(HEX+i)>='0'&&*(HEX+i)<='9') 
  { 
  result*=16; 
  result+=*(HEX+i)-'0'; 
  } 
 }
 return(result); 
}
#pragma inline
uword *LoadFontLib(void)
{
  int f;
  char cnfont[]=DEFAULT_DISK ":\\ZBin\\ETC\\cnfont.dat";
  uint ul;
  uword *data = 0;
  f=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  if(f == -1){
    cnfont[0] = '0';
    f=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  }
  if(f == -1){
    cnfont[0] = '2';
    f=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  }
  if(f != -1){
    data=(uword *)malloc(73808);
    if (fread(f,(void*)data,73808,&ul)!=73808){
      mfree((void*)data);
      data = 0;
    }
    fclose(f,&ul);
  }
  return(data);
}
#pragma inline
void FreeFontLib(uword *data)
{
  if (data){
    mfree(data);
    data = 0;
  }
}
#pragma inline
void WS2Ascii(uword *data, WSHDR *ws, char *s, int maxlen)
{
  int len=ws->wsbody[0];
  if(maxlen != 0 && len > maxlen)
    len = maxlen;
  if(data == 0){
    ws_2str(ws, s, len);
    return;
  }
  int i,j=0;
  uword temp;
  for(i=1; i<=len; i++){
    temp=ws->wsbody[i];
    if(temp < 256)
      s[j++] = (uchar)temp;
    else if(temp >= 0x4E00 && temp <= 0x9FA5){
      s[j++] = (uchar)(data[temp-0x4E00+32004]>>8);
      s[j++] = (uchar)((data[temp-0x4E00+32004]<<8)>>8);
    }else s[j++] = '?';
  }
  s[j] = 0;
}
#pragma inline
void Ascii2WS(uword *data,WSHDR *ws, const char *s, int maxlen)
{
  if(data == 0){
    wsprintf(ws, "%t", s);
    return;
  }
  char *p=(char *)s;
  unsigned char uc,uc2;
  CutWSTR(ws,0);
  while((uc=*s++) && (maxlen == 0 || s-p<maxlen)){
    if(uc <= 128)
      wsAppendChar(ws,uc);
    else{
      uc2=*s++;
      if(uc2 < 128)
        wsAppendChar(ws, uc2);
      else{
        wsAppendChar(ws, data[(uc-129)*127+(uc2-128)]);
      }
    }
  }
}
#pragma inline// ����ĳ�����Ƿ�����
uchar LunarYearId(ulong year)
{  
  return (year%4==0)&&((year%100!=0)||(year%400==0));
}
#pragma inline
uword MonthMaxDay(int year,int month)
{
  uword result;
  switch(month){ 
  case  4: 
  case  6: 
  case  9: 
  case 11:result= 30; break;
  case  2:result= 28+LunarYearId(year);break;
  default:result= 31;
 }
 return result;
}
#pragma inline// ȡĳ���ڵ������������������ 1582 �� 10 �µ��������
uword GetDayFromYearBegin(ulong AYear,uchar AMonth,uchar ADay)
{
  uword Result=0;
  for(int i= 1;i<= AMonth - 1;i++){
    Result+=MonthMaxDay(AYear, i);
  }
  Result+=ADay;
  return Result;
}
#pragma inline
uword BetweenDaySum(TDate start,TDate end)
{
uword sum=0;
TDate e = end;
TDate s = start;
if (s.month>12||e.month>12||s.month<1||e.month<1){return(sum);}
if (s.day<1||e.day<1||s.day>MonthMaxDay(s.year,s.month)||e.day>MonthMaxDay(e.year,e.month)){return(sum);}
if ((s.year>e.year)||(s.year==e.year&&s.month>e.month)||(s.year==e.year&&s.month==e.month&&s.day>e.day)){
  s.year^=e.year^=s.year^=e.year;
  s.month^=e.month^=s.month^=e.month;
  s.day^=e.day^=s.day^=e.day;
  /*
   k=s.year; s.year=e.year; e.year=k;
   k=s.month; s.month=e.month; e.month=k;
   k=s.day; s.day=e.day; e.day=k;*/
}
sum=e.day;
for(;!(s.year==e.year&&s.month==e.month);s.month++){
  sum+=MonthMaxDay(s.year,s.month);
  if(s.month==12){
     s.year++;
     s.month=0;
  }
}
sum=sum-s.day;
return(sum);
}
#pragma inline
int LunarHolId(TDate date)
{ 
  if((date.year>LunarMaxYear)||(date.year<LunarMinYear))return 0;
  ubyte HolDay[1800]={
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1901
    0x96, 0xA4, 0x96, 0x96, 0x97, 0x87, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1902
    0x96, 0xA5, 0x87, 0x96, 0x87, 0x87, 0x79, 0x69, 0x69, 0x69, 0x78, 0x78,   //1903
    0x86, 0xA5, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x78, 0x87,   //1904
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1905
    0x96, 0xA4, 0x96, 0x96, 0x97, 0x97, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1906
    0x96, 0xA5, 0x87, 0x96, 0x87, 0x87, 0x79, 0x69, 0x69, 0x69, 0x78, 0x78,   //1907
    0x86, 0xA5, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1908
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1909
    0x96, 0xA4, 0x96, 0x96, 0x97, 0x97, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1910
    0x96, 0xA5, 0x87, 0x96, 0x87, 0x87, 0x79, 0x69, 0x69, 0x69, 0x78, 0x78,   //1911
    0x86, 0xA5, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1912
    0x95, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1913
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1914
    0x96, 0xA5, 0x97, 0x96, 0x97, 0x87, 0x79, 0x79, 0x69, 0x69, 0x78, 0x78,   //1915
    0x96, 0xA5, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //1916
    0x95, 0xB4, 0x96, 0xA6, 0x96, 0x97, 0x78, 0x79, 0x78, 0x69, 0x78, 0x87,   //1917
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x79, 0x79, 0x79, 0x69, 0x78, 0x77,   //1918
    0x96, 0xA5, 0x97, 0x96, 0x97, 0x87, 0x79, 0x79, 0x69, 0x69, 0x78, 0x78,   //1919
    0x96, 0xA5, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //1920
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x78, 0x79, 0x78, 0x69, 0x78, 0x87,   //1921
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x79, 0x79, 0x79, 0x69, 0x78, 0x77,   //1922
    0x96, 0xA4, 0x96, 0x96, 0x97, 0x87, 0x79, 0x79, 0x69, 0x69, 0x78, 0x78,   //1923
    0x96, 0xA5, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //1924
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x78, 0x79, 0x78, 0x69, 0x78, 0x87,   //1925
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1926
    0x96, 0xA4, 0x96, 0x96, 0x97, 0x87, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1927
    0x96, 0xA5, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1928
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //1929
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1930
    0x96, 0xA4, 0x96, 0x96, 0x97, 0x87, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1931
    0x96, 0xA5, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1932
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1933
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1934
    0x96, 0xA4, 0x96, 0x96, 0x97, 0x97, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1935
    0x96, 0xA5, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1936
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1937
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1938
    0x96, 0xA4, 0x96, 0x96, 0x97, 0x97, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1939
    0x96, 0xA5, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1940
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1941
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1942
    0x96, 0xA4, 0x96, 0x96, 0x97, 0x97, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1943
    0x96, 0xA5, 0x96, 0xA5, 0xA6, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1944
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //1945
    0x95, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x78, 0x69, 0x78, 0x77,   //1946
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1947
    0x96, 0xA5, 0xA6, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //1948
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x79, 0x78, 0x79, 0x77, 0x87,   //1949
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x78, 0x79, 0x78, 0x69, 0x78, 0x77,   //1950
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x79, 0x79, 0x79, 0x69, 0x78, 0x78,   //1951
    0x96, 0xA5, 0xA6, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //1952
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //1953
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x78, 0x79, 0x78, 0x68, 0x78, 0x87,   //1954
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1955
    0x96, 0xA5, 0xA5, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //1956
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //1957
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1958
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1959
    0x96, 0xA4, 0xA5, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //1960
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1961
    0x96, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1962
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1963
    0x96, 0xA4, 0xA5, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //1964
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1965
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1966
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1967
    0x96, 0xA4, 0xA5, 0xA5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //1968
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1969
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1970
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x79, 0x69, 0x78, 0x77,   //1971
    0x96, 0xA4, 0xA5, 0xA5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //1972
    0xA5, 0xB5, 0x96, 0xA5, 0xA6, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1973
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1974
    0x96, 0xB4, 0x96, 0xA6, 0x97, 0x97, 0x78, 0x79, 0x78, 0x69, 0x78, 0x77,   //1975
    0x96, 0xA4, 0xA5, 0xB5, 0xA6, 0xA6, 0x88, 0x89, 0x88, 0x78, 0x87, 0x87,   //1976
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //1977
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x78, 0x87,   //1978
    0x96, 0xB4, 0x96, 0xA6, 0x96, 0x97, 0x78, 0x79, 0x78, 0x69, 0x78, 0x77,   //1979
    0x96, 0xA4, 0xA5, 0xB5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //1980
    0xA5, 0xB4, 0x96, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x77, 0x87,   //1981
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //1982
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x78, 0x79, 0x78, 0x69, 0x78, 0x77,   //1983
    0x96, 0xB4, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x87,   //1984
    0xA5, 0xB4, 0xA6, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //1985
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //1986
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x79, 0x78, 0x69, 0x78, 0x87,   //1987
    0x96, 0xB4, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x86,   //1988
    0xA5, 0xB4, 0xA5, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //1989
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //1990
    0x95, 0xB4, 0x96, 0xA5, 0x86, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1991
    0x96, 0xB4, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x86,   //1992
    0xA5, 0xB3, 0xA5, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //1993
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1994
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x76, 0x78, 0x69, 0x78, 0x87,   //1995
    0x96, 0xB4, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x86,   //1996
    0xA5, 0xB3, 0xA5, 0xA5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //1997
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //1998
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //1999
    0x96, 0xB4, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x86,   //2000
    0xA5, 0xB3, 0xA5, 0xA5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //2001
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //2002
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //2003
    0x96, 0xB4, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x86,   //2004
    0xA5, 0xB3, 0xA5, 0xA5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //2005
    0xA5, 0xB4, 0x96, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //2006
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x69, 0x78, 0x87,   //2007
    0x96, 0xB4, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x87, 0x78, 0x87, 0x86,   //2008
    0xA5, 0xB3, 0xA5, 0xB5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //2009
    0xA5, 0xB4, 0x96, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //2010
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x78, 0x87,   //2011
    0x96, 0xB4, 0xA5, 0xB5, 0xA5, 0xA6, 0x87, 0x88, 0x87, 0x78, 0x87, 0x86,   //2012
    0xA5, 0xB3, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x87,   //2013
    0xA5, 0xB4, 0x96, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //2014
    0x95, 0xB4, 0x96, 0xA5, 0x96, 0x97, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //2015
    0x95, 0xB4, 0xA5, 0xB4, 0xA5, 0xA6, 0x87, 0x88, 0x87, 0x78, 0x87, 0x86,   //2016
    0xA5, 0xC3, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x87,   //2017
    0xA5, 0xB4, 0xA6, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //2018
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //2019
    0x95, 0xB4, 0xA5, 0xB4, 0xA5, 0xA6, 0x97, 0x87, 0x87, 0x78, 0x87, 0x86,   //2020
    0xA5, 0xC3, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x86,   //2021
    0xA5, 0xB4, 0xA5, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //2022
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x79, 0x77, 0x87,   //2023
    0x95, 0xB4, 0xA5, 0xB4, 0xA5, 0xA6, 0x97, 0x87, 0x87, 0x78, 0x87, 0x96,   //2024
    0xA5, 0xC3, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x86,   //2025
    0xA5, 0xB3, 0xA5, 0xA5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //2026
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //2027
    0x95, 0xB4, 0xA5, 0xB4, 0xA5, 0xA6, 0x97, 0x87, 0x87, 0x78, 0x87, 0x96,   //2028
    0xA5, 0xC3, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x86,   //2029
    0xA5, 0xB3, 0xA5, 0xA5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //2030
    0xA5, 0xB4, 0x96, 0xA5, 0x96, 0x96, 0x88, 0x78, 0x78, 0x78, 0x87, 0x87,   //2031
    0x95, 0xB4, 0xA5, 0xB4, 0xA5, 0xA6, 0x97, 0x87, 0x87, 0x78, 0x87, 0x96,   //2032
    0xA5, 0xC3, 0xA5, 0xB5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x86,   //2033
    0xA5, 0xB3, 0xA5, 0xA5, 0xA6, 0xA6, 0x88, 0x78, 0x88, 0x78, 0x87, 0x87,   //2034
    0xA5, 0xB4, 0x96, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //2035
    0x95, 0xB4, 0xA5, 0xB4, 0xA5, 0xA6, 0x97, 0x87, 0x87, 0x78, 0x87, 0x96,   //2036
    0xA5, 0xC3, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x86,   //2037
    0xA5, 0xB3, 0xA5, 0xA5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //2038
    0xA5, 0xB4, 0x96, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //2039
    0x95, 0xB4, 0xA5, 0xB4, 0xA5, 0xA6, 0x97, 0x87, 0x87, 0x78, 0x87, 0x96,   //2040
    0xA5, 0xC3, 0xA5, 0xB5, 0xA5, 0xA6, 0x87, 0x88, 0x87, 0x78, 0x87, 0x86,   //2041
    0xA5, 0xB3, 0xA5, 0xB5, 0xA6, 0xA6, 0x88, 0x88, 0x88, 0x78, 0x87, 0x87,   //2042
    0xA5, 0xB4, 0x96, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //2043
    0x95, 0xB4, 0xA5, 0xB4, 0xA5, 0xA6, 0x97, 0x87, 0x87, 0x88, 0x87, 0x96,   //2044
    0xA5, 0xC3, 0xA5, 0xB4, 0xA5, 0xA6, 0x87, 0x88, 0x87, 0x78, 0x87, 0x86,   //2045
    0xA5, 0xB3, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x88, 0x78, 0x87, 0x87,   //2046
    0xA5, 0xB4, 0x96, 0xA5, 0xA6, 0x96, 0x88, 0x88, 0x78, 0x78, 0x87, 0x87,   //2047
    0x95, 0xB4, 0xA5, 0xB4, 0xA5, 0xA5, 0x97, 0x87, 0x87, 0x88, 0x86, 0x96,   //2048
    0xA4, 0xC3, 0xA5, 0xA5, 0xA5, 0xA6, 0x97, 0x87, 0x87, 0x78, 0x87, 0x86,   //2049
    0xA5, 0xC3, 0xA5, 0xB5, 0xA6, 0xA6, 0x87, 0x88, 0x78, 0x78, 0x87, 0x87};  //2050
 int day;
 int Flag=HolDay[(date.year-1901)*12+date.month-1]; 
 if (date.day<15)
     day=15-((Flag >> 4) & 0x0F);
 else
     day=(Flag & 0x0F)+15;
 if (date.day==day){
   if (date.day>15)
       return (date.month-1)*2+2;
   else
       return (date.month-1)*2+1;
 }else return 0;
}

#pragma inline
void LunarHolDay(WSHDR* ws,int LunarId)
{
 /*const uword cDay[][2] = {{"*"},
  {"С��"},{"��"},{"����"},{"��ˮ"}, {"����"},{"����"},{"����"},{"����"},
  {"����"},{"С��"},{"â��"},{"����"}, {"С��"},{"����"},{"����"},{"����"},
  {"��¶"},{"���"},{"��¶"},{"˪��"}, {"����"},{"Сѩ"},{"��ѩ"},{"����"}}*/
 uword UNI[4];
 UNI[0] = 0x519C;
 UNI[1] = 0x5386;
 const uword cDay[][2] = {
 {0x002A},
 {0x5C0F,0x5BD2},{0x5927,0x5BD2},{0x7ACB,0x6625},{0x96E8,0x6C34},
 {0x60CA,0x86F0},{0x6625,0x5206},{0x6E05,0x660E},{0x8C37,0x96E8},
 {0x7ACB,0x590F},{0x5C0F,0x6EE1},{0x8292,0x79CD},{0x590F,0x81F3},
 {0x5C0F,0x6691},{0x5927,0x6691},{0x7ACB,0x79CB},{0x5904,0x6691},
 {0x767D,0x9732},{0x79CB,0x5206},{0x5BD2,0x9732},{0x971C,0x964D},
 {0x7ACB,0x51AC},{0x5C0F,0x96EA},{0x5927,0x96EA},{0x51AC,0x81F3},
 {0,0}};  
 UNI[2] = cDay[LunarId][0];  
 UNI[3] = cDay[LunarId][1]; 
 BSTRAdd(ws->wsbody,UNI,4);
}

#endif/*SIEAPI_H_*/

//�����������ñ�
#if defined(_STD_USING)
 using _CSTD strtoul;
 using _CSTD kill_data;
 using _CSTD RunCUT;
 using _CSTD RunAPP;
 using _CSTD RunADR;
 using _CSTD ExtStrcmp;
 using _CSTD BSTRAdd;
 using _CSTD GetDayOf;
 using _CSTD get_string_width;
 using _CSTD toupper;
 using _CSTD strcmp_nocase;
 using _CSTD str2ws_unicode;
 using _CSTD ws2str_unicode;
 using _CSTD unicodeSwitch;
 using _CSTD utf82unicode;
 using _CSTD unicode2utf8;
 using _CSTD patch_rect;
 using _CSTD patch_header;
 using _CSTD patch_input;
 using _CSTD patch_dialog;
 using _CSTD OpenBCFGFile;
 using _CSTD DrawCanvasExt;
 using _CSTD DrawCanvasRect;
 using _CSTD DrawStringExt;
 using _CSTD DrawStringRect;
 using _CSTD CutFileExt;
 using _CSTD getstrpos;
 using _CSTD GetOldDay;
 using _CSTD LoadFileBuf;
 using _CSTD FreeFileBuf;
 using _CSTD FontType;
 using _CSTD PlayMusic;
 using _CSTD BuildMenu;
 using _CSTD DrawMenu;
 using _CSTD FreeMenu;
 using _CSTD MenuCount;
 using _CSTD FileCount;
 using _CSTD FreeFile;
 using _CSTD IsMediaActive;
 using _CSTD HexToInt;
 using _CSTD Ascii2WS;
 using _CSTD WS2Ascii;
 using _CSTD FreeFontLib;
 using _CSTD LoadFontLib;
 using _CSTD LunarHolDay;
 using _CSTD LunarHolID;
 using _CSTD LunarYearId;
 using _CSTD BetweenDaySum;
 using _CSTD GetDayFromYearBegin;
#endif /* �����������ñ� */
 

