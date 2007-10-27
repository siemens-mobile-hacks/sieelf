#ifndef _SIEAPI_H_
#define _SIEAPI_H_ 
 #ifndef _SYSTEM_BUILD
  #pragma system_include
 #endif
 #include <ysizet.h>
_C_STD_BEGIN
 //������������
 #define word  unsigned short
 #define uint  unsigned int
 #define ulong unsigned long
 #define uchar unsigned char
 #define TVoid typedef void
 #define TStruct typedef struct
 #define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
 //����ũ�����ͽṹ
 TStruct{
  WSHDR *year;
  WSHDR *monthday;
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
  word Size;//�����С
 }TFont;
 //���庯�������ṹ
_C_LIB_DECL
 __INTRINSIC ulong strtoul(const char *nptr,char **endptr,int base); 
 __INTRINSIC int  ExtStrcmp(char *a,char *b);
 __INTRINSIC int  get_string_width(WSHDR *ws, int font);
 __INTRINSIC int  toupper(int c);
 __INTRINSIC int  strcmp_nocase(const char *s1,const char *s2); 
 __INTRINSIC char* unicodeSwitch(char *str, int len, int *rlen, int *llen); 
 __INTRINSIC char* utf82unicode(char *str, int len, int *rlen, int *llen); 
 __INTRINSIC char* unicode2utf8(char *str, int *len); 
 __INTRINSIC void patch_rect(RECT*rc,int x,int y, int x2, int y2);
 __INTRINSIC void patch_header(const HEADER_DESC* head);
 __INTRINSIC void patch_input(const INPUTDIA_DESC* inp);
 __INTRINSIC void patch_dialog(INPUTDIA_DESC* dialog, int x,int y,int x2, int y2);
 __INTRINSIC void OpenBCFGFile(const char *filename);
 __INTRINSIC void DrawCanvasExt(void *canvas, RECT rc,int mode);
 __INTRINSIC void DrawCanvasRect(void *canvas, TRect rc,int mode);
 __INTRINSIC void DrawStringExt(WSHDR *ws,RECT rc,TFont Font,int text_attribute);
 __INTRINSIC void DrawStringRect(WSHDR *ws,TRect rc,TFont Font,int text_attribute);
 __INTRINSIC void kill_data(void *p, void (*func_p)(void *));
 __INTRINSIC void str2ws_unicode(WSHDR* ws, char* str, int len);
 __INTRINSIC void ws2str_unicode(char* str, WSHDR* ws, int *len);  
 __INTRINSIC void BSTRAdd(word *pDst, const word * pSrc, int Count);
 __INTRINSIC void GetDayOf(TDate pSt,TNongLi *NongLiData);
 __INTRINSIC void RunCUT(char *s);
 __INTRINSIC void RunAPP(char *s);
 __INTRINSIC void RunADR(char *s);
_END_C_LIB_DECL
_C_STD_END
//����ִ�д���
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
      WSHDR *ws=AllocWS(150);
      str_2ws(ws,s,128);
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
void BSTRAdd(word *pDst, const word * pSrc, int Count)
{
  uint nSize = *pDst, i=1;
  while(*pSrc != '\0' && i<=Count) *(pDst+ nSize + i++) = *pSrc++;
  *pDst = nSize+i-1;
}
#pragma inline//����ũ������
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
  int len=body[0];
  while(0<len){
    width+=GetSymbolWidth(body[len],font);
    len--;
  }
  return (width);
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';  return(c);
}

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
  char *p;
  p = str;
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
  rc->x=x;
  rc->y=y;
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
  dialog->rc.x = x;
  dialog->rc.y = y;
  dialog->rc.x2 = x2;
  dialog->rc.y2 = y2;
}
#pragma inline
void OpenBCFGFile(const char *filename)
{   
  if ((filename)&&(strlen(filename))){
  WSHDR *ws = AllocWS(150);
  str_2ws(ws, filename, 128);
  ExecuteFile(ws, 0, 0);
  FreeWS(ws);
  GeneralFuncF1(1);
  }
}
#pragma inline
void DrawCanvasExt(void *canvas, RECT rc,int mode)
{ DrawCanvas(canvas, rc.x, rc.y, rc.x2, rc.y2, mode); }
#pragma inline
void DrawCanvasRect(void *canvas, TRect rc,int mode)
{ DrawCanvas(canvas, rc.l, rc.t, rc.r, rc.b, mode); }
#pragma inline
void DrawStringExt(WSHDR *ws,RECT rc,TFont Font,int text_attribute)
{ DrawString(ws, rc.x, rc.y, rc.x2, rc.y2, Font.Size,text_attribute,Font.Pen, Font.Brush); }
#pragma inline
void DrawStringRect(WSHDR *ws,TRect rc,TFont Font,int text_attribute)
{ DrawString(ws, rc.l, rc.t, rc.r, rc.b, Font.Size,text_attribute,Font.Pen, Font.Brush); }
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
#endif /* �����������ñ� */
 

