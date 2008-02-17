#ifndef _SIEAPI_H_
#define _SIEAPI_H_ 
 #ifndef _SYSTEM_BUILD
  #pragma system_include
 #endif
#include <ysizet.h>
#include <siecxt.h>
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
#define uword   unsigned short
#define uint    unsigned int
#define ulong   unsigned long
#define ubyte   unsigned char//0..255
#define TYPVOID typedef void
#define TSTRUCT typedef struct 
#define elif    else if
//�����ʮ������ʼ����(������Ϊ51��)
#define LHYear  2050//����������������
#define LLYear  2000//������������С���
#define LCData (LHYear-LLYear+1)*12//�������ݳ���
#define color(x) (x<24)?GetPaletteAdrByColorIndex(x):(char *)(&(x))
#define idlegui_id(icsm) (((int*)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
#define MIN(a,b) (a<b)?a:b
#define MAX(a,b) (a>b)?a:b
#define TRAN_CBK GetPaletteAdrByColorIndex(23)
#define CTYPE1 0
#define CTYPE2 1
//����������������0-16!
#define FontSyEN "Large","Large bold","Large italic","Large italic bold","Medium","Medium bold","Medium italic","Medium italic bold","Small","Small bold","Small italic","Small italic bold","Numeric small","Numeric small bold","Numeric xsmall","Numeric large","Numeric medium"
#define FontSyCN "�������","��żӴ�","���б��","��Ŵ�б","�к�����","�кżӴ�","�к���б","�кŴ�б","С������","С�żӴ�","С��б��","С�Ŵ�б","С������","С������","��С����","�������","�к�����"
 //#define IS_FOLDER 1 //�����ļ��в���
 //#define IS_FILE 0  //�����ļ�����
 
 //����ũ�����ͽṹ
 TSTRUCT{
  WSHDR *year;//���
  WSHDR *mday;//�·�
 }TLunar;
 TSTRUCT{
  char R;
  char G;
  char B;
  char A;
 }color;
 //������������
 TSTRUCT{
  short l;//left
  short t;//top  
  short r;//Right;
  short b;//Bottom;
 }TRect;
 //������������
 TSTRUCT{
  char Pen[4];//������ɫ
  char Brush[4];//�߿���ɫ
  ubyte Size;//�����С
 }TFont;
 //�����ļ��ṹ
 TSTRUCT{
  void *next;
  char *file;
  char *path;
  int   type;//1Ϊ�ļ���,0Ϊ�ļ�
 }TFile;
 //�����ļ��ṹ
 TSTRUCT{
  void *next;
  char *name;
  uint  cmd;//Ϊִ�й��ܴ���
 }TMenu;
 //����ʱ��ṹ
 TSTRUCT{
  ulong year;
  ubyte month;
  ubyte day; 
  ubyte hour;
  ubyte min;
  ubyte sec;
  ulong millisec;
 }TDateTime;
 //���庯�������ṹ
_C_LIB_DECL
 __INTRINSIC ulong strtoul(const char *nptr,char **endptr,int base); 
 __INTRINSIC long strtol(const char *nptr,char **endptr,int base);
 __INTRINSIC int  strlpos(char *str,char c); 
 //��ȡ���ֻ���Ӧ�����ı��ĳ���
 __INTRINSIC int  PixlsWidth(WSHDR *ws, int font); 
 //�ִ��ȽϺ���
 __INTRINSIC int  toupper(int c);
 __INTRINSIC int  ExtStrcmp(char *a,char *b);
 __INTRINSIC int  strcmp_nocase(const char *s1,const char *s2); 
 __INTRINSIC int  cmpstr_nocase(const char *s, const char *d);
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
 __INTRINSIC void GetDayOf(TDate pSt,TLunar *Lunar);//��ȡũ���ִ�
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
 __INTRINSIC ubyte LunarYearId(ulong year);// ����ĳ�����Ƿ�����
 __INTRINSIC uword BetweenDaySum(TDate start,TDate end);//����������֮�������
 __INTRINSIC uword GetDayFromYearBegin(ulong AYear,ubyte AMonth,ubyte ADay);// ȡĳ���ڵ����������
 __INTRINSIC ubyte FileExists(char *FileName,int *Handle);//�ж��ļ��Ƿ����!
 __INTRINSIC void *CreateCanvas();//��������ָ��
 __INTRINSIC void  SearchSub(const char *source,const char *sub,char *result);//��ȡ���ִ�
//PNGת����غ��� 
 __INTRINSIC IMGHDR_Draw(IMGHDR *Handle, int x, int y, char *pen, char *brush);
 __INTRINSIC IMGHDR_Delete(IMGHDR *Handle);
 __INTRINSIC void  IMGHDR_Free(IMGHDR *Handle);
 __INTRINSIC color IMGHDR_Color(IMGHDR *Handle, int x, int y);
 __INTRINSIC IMGHDR *IMGHDR_Alpha(IMGHDR *Handle, char a, int nw, int del);
 __INTRINSIC IMGHDR *IMGHDR_Sample(IMGHDR *Handle, int px, int py, int fast, int del);
 __INTRINSIC IMGHDR *IMGHDR_Handle(int x,int y,const char *pic_path,int pic_size);
_END_C_LIB_DECL
_C_STD_END
//����ִ�д���
#pragma inline//��ȡc��str�ִ���λ��
static int getstrpos(char *str,char c)
{
  int cur = 0;
  for (int inx=1;inx<=strlen(str);inx++)
  {
    if(str[inx]==c){cur=inx;break;}
  }
  return cur;
}

#pragma inline//��ȡ���ļ�����
static void CutFileExt(char *filename,char *ext)
{
  if(strlen(filename)>strlen(ext))filename[strlen(filename)-strlen(ext)]=0;
}
#pragma inline//���п��
static void RunCUT(char *s)
{
 if ((s)&&(strlen(s))){
 uint* addr = (uint*)GetFunctionPointer(s);
 if (addr){
   TYPVOID (*voidfunc)(); 
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
static void RunAPP(char *s)
{
  if ((s)&&(strlen(s))){
      WSHDR *ws=AllocWS(128);
      str_2ws(ws,s,strlen(s));
      ExecuteFile(ws, 0,0);
      FreeWS(ws);
  }
}
#pragma inline//���е�ַ����
static void RunADR(char *s)
{  
  if ((s)&&(strlen(s))){
      TYPVOID (*voidfunc)(); 
      uint addr=strtoul(s, 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp); 
  }
}
#pragma inline//�ִ��ȽϺ���
static int ExtStrcmp(char *a,char *b)
{
  int state=0,max=strlen(a);
  if(strlen(a)>strlen(b)) max = strlen(b);
  for(int i=0;i<max;i++){
    if(a[i]!=b[i]){state=0; break;}else{state=1;}
  } 
  return(state);
}
#pragma inline//���ݺϲ�
static void BSTRAdd(uword *pDst, const uword * pSrc, int Count)
{
  uint nSize = *pDst, i=1;
  while(*pSrc != '\0' && i<=Count) *(pDst+ nSize + i++) = *pSrc++;
  *pDst = nSize+i-1;
}
#pragma inline//��ǰ����ת��Ϊũ������
static TDate GetOldDay(TDate pSt)
{/*����ÿ��ǰ�������*/
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
while(nIsEnd != 1){
  if(wLunar[m] < 4095)  k = 11; else k = 12;
  n = k;
  while(n>=0){
   //��ȡwLunar(m)�ĵ�n��������λ��ֵ
   nBit = wLunar[m];
   for(i=1;i<n+1;i++) nBit = nBit/2;
   nBit = nBit % 2;
   if (nTheDate <= (29 + nBit)){
    nIsEnd = 1;
    break;
   }
   nTheDate = nTheDate - 29 - nBit;
   n = n - 1;
  }
  if(nIsEnd) break;
  m = m + 1;
}
wCurYear  = 1921 + m;
wCurMonth = k - n + 1;
wCurDay   = nTheDate;
if (k == 12){

  if (wCurMonth == wLunar[m] / 65536 + 1)
      wCurMonth = 1 - wCurMonth;
  else if (wCurMonth > wLunar[m] / 65536 + 1)
      wCurMonth = wCurMonth - 1;
}
OldDay.year =wCurYear;
OldDay.month=wCurMonth;
OldDay.day  =wCurDay;
return(OldDay);
}
#pragma inline//��ȡũ��������Ϣ
static void GetDayOf(TDate pSt,TLunar *Lunar)
{ 
TDate old = GetOldDay(pSt);
const char _year_t[]="%t%t%t%t";
const char _mday_o[]="%t%t%t%t";
const char _mday_t[]="%t%t%t";
/*--����ũ����ɡ���֧������ ==> Lunar--*/
short cTGInx=((old.year-4)%60)%10;
short cTDInx=((old.year-4)%60)%12;
wsprintf(Lunar->year,_year_t,cTGan[cTGInx],cDZhi[cTDInx],cSXin[cTDInx],cOName[0]);
/*--����ũ���� --*/
if (old.month < 1){  //����
    wsprintf(Lunar->mday,_mday_o,cOName[2],cMName[-1*old.month],cOName[1],cDName[old.day]);
}else{
    wsprintf(Lunar->mday,_mday_t,cMName[old.month],cOName[1],cDName[old.day]);
}
}  

#pragma inline
static int PixlsWidth(WSHDR *ws, int font)
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
static int toupper(int c){ if ((c>='a')&&(c<='z')) c+='A'-'a';  return(c);}

#pragma inline
static int strcmp_nocase(const char *s1,const char *s2)
{
  int i,c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}
#pragma inline
static int cmpstr_nocase(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=*s++;
    if (cs&0x40) cs&=0xDF;
    ds=*d++;
    if (ds&0x40) ds&=0xDF;
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}
#pragma inline
static void str2ws_unicode(WSHDR* ws, char* str, int len)
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
static void ws2str_unicode(char* str, WSHDR* ws, int *len) 
{	//ע�ⷶΧ
  for (int i = 0; i < ws->wsbody[0]; i++) {
  	*(str + (i << 1)) = ws->wsbody[i + 1] & 0xFF;
  	*(str + (i << 1) + 1) = ws->wsbody[i + 1] >> 8;
	}
	*len = ws->wsbody[0] << 1;
}
#pragma inline
static char* unicodeSwitch(char *str, int len, int *rlen, int *llen) 
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
static char* utf82unicode(char *str, int len, int *rlen, int *llen) 
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
static char* unicode2utf8(char *str, int *len) 
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
static void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x =x;
  rc->y =y;
  rc->x2=x2;
  rc->y2=y2;
}

#pragma inline
static void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}

#pragma inline
static void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}

#pragma inline
static void patch_dialog(INPUTDIA_DESC* dialog, int x,int y,int x2, int y2)
{
  dialog->rc.x  = x;
  dialog->rc.y  = y;
  dialog->rc.x2 = x2;
  dialog->rc.y2 = y2;
}
#pragma inline
static void OpenBCFGFile(void)
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
static void DrawCanvasExt(void *canvas, RECT rc,int mode)
{ DrawCanvas(canvas, rc.x, rc.y, rc.x2, rc.y2, mode); }
#pragma inline
static void DrawCanvasRect(void *canvas, TRect rc,int mode)
{ DrawCanvas(canvas, rc.l, rc.t, rc.r, rc.b, mode); }
#pragma inline
static void DrawStringExt(WSHDR *ws,RECT rc,TFont Font,int text_attribute)
{ DrawString(ws, rc.x, rc.y, rc.x2, rc.y2, Font.Size,text_attribute,Font.Pen, Font.Brush); }
#pragma inline
static void DrawStringRect(WSHDR *ws,TRect rc,TFont Font,int text_attribute)
{ DrawString(ws, rc.l, rc.t, rc.r, rc.b, Font.Size,text_attribute,Font.Pen, Font.Brush); }
#pragma inline//�����ļ�������
static char *LoadFileBuf(const char *FileName)
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
static int FreeFileBuf(char *Buffer)
{
  if(Buffer){
    mfree(Buffer);
    return(1);
  }else return(0);
}
#pragma inline//��ȡ��������
static uint FontType(int index)
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
static int PlayMusic(const char *fname, uint VOLUME, uint RepeatNum)
{
    int Handle=0;
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
   return(Handle);
}
#pragma inline//�����ִ�����
static uint CountTitle(char *Title[])
{
 int max=0;
 for (int i=0; Title[i]!=NULL; i++)
    max++;
 return(max-1); 
}
#pragma inline//�����˵�����
static TMenu *BuildMenu(char *Title[])
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
static void DrawMenu(void *gui, int cur_item, void *user_pointer)
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
static void FreeMenu(TMenu *Menu)
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
static int MenuCount(TMenu *Menu)
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
static void FreeFile(TFile *File)
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
static int IsMediaActive(void)
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
static ulong HexToInt(char *HEX) 
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
static ubyte FileExists(char *FileName,int *Handle)
{
  int ul;
  *Handle=fopen(FileName,A_ReadOnly+A_BIN,P_READ,&ul);
  if(*Handle==-1) return 0; else return 1;
}
#pragma inline
static uword *LoadFontLib(void)
{  
  int ul;
  uword *data = 0;
  char cnfont[]="4:\\ZBin\\ETC\\cnfont.dat"; 
  int handle=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  if(handle == -1){
    cnfont[0] = '0';
    handle=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  }
  if(handle == -1){
    cnfont[0] = '1';
    handle=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  }
  if(handle == -1){
    cnfont[0] = '2';
    handle=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  }
  if(handle != -1){
    data=(uword *)malloc(73808);
    if (fread(handle,(void*)data,73808,&ul)!=73808){
      mfree((void*)data);
      data = 0;
    }
    fclose(handle,&ul);
  }
  return(data);
}
#pragma inline
static void FreeFontLib(uword *data)
{
  if (data){
    mfree(data);
    data = 0;
  }
}
#pragma inline
static void WS2Ascii(uword *data, WSHDR *ws, char *s, int maxlen)
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
      s[j++] = (ubyte)temp;
    else if(temp >= 0x4E00 && temp <= 0x9FA5){
      s[j++] = (ubyte)(data[temp-0x4E00+32004]>>8);
      s[j++] = (ubyte)((data[temp-0x4E00+32004]<<8)>>8);
    }else s[j++] = '?';
  }
  s[j] = 0;
}
#pragma inline
static void Ascii2WS(uword *data,WSHDR *ws, const char *s, int maxlen)
{
  if(data == 0){
    wsprintf(ws, "%t", s);
    return;
  }
  char *p=(char *)s;
  ubyte uc,uc2;
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
static ubyte LunarYearId(ulong year)
{  
  return (year%4==0)&&((year%100!=0)||(year%400==0));
}
#pragma inline
static uword MonthMaxDay(int year,int month)
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
static uword GetDayFromYearBegin(ulong AYear,ubyte AMonth,ubyte ADay)
{
  uword Result=0;
  for(int i= 1;i<= AMonth - 1;i++){
    Result+=MonthMaxDay(AYear, i);
  }
  Result+=ADay;
  return Result;
}
#pragma inline
static uword BetweenDaySum(TDate start,TDate end)
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
#pragma inline//��ȡ��ʮ�Ľ�������IDֵ
static int LunarHolId(TDate date)
{ 
 if((date.year>LHYear)||(date.year<LLYear))return 0; 
 int Flag=HolDay[(date.year-LLYear)*12+date.month-1]; 
 int day=(Flag & 0x0F)+15;
 if (date.day<15) day=15-((Flag >> 4) & 0x0F);
 if (date.day==day){
   if (date.day>15)
       return (date.month-1)*2+2;
   else
       return (date.month-1)*2+1;
 }else return 0;
}
#pragma inline//��ȡ��ʮ�����ִ�����
static void LunarHolDay(WSHDR* ws,int LunarId)
{
 uword UNI[4];
 UNI[0] = 0x519C;
 UNI[1] = 0x5386; 
 UNI[2] = cDay[LunarId-1][0];  
 UNI[3] = cDay[LunarId-1][1]; 
 BSTRAdd(ws->wsbody,UNI,4);
}
#pragma inline//��ȡ����
static void *CreateCanvas()
{
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (icsm){
    if (IsGuiOnTop(idlegui_id(icsm))){
      GUI *igui=GetTopGUI();      
      #ifdef ELKA
       return(BuildCanvas());
      #else
       void *idata = GetDataOfItemByID(igui,2);
       if(idata){
         return(((void **)idata)[DISPLACE_OF_IDLECANVAS/4]);         
       }
      #endif
    }
  }
  return NULL;
}
#pragma inline//��ȡ�ִ�
static void SearchSub(const char *source,const char *sub,char *result)
{
  char *s=strstr(source,sub);
  if(s){  
      int c,i=0;
      char TEMP[256];
      s+=strlen(sub);       
      while((c=*s++)!=0x0A){if (i<(sizeof(TEMP)-1)) TEMP[i++]=c;}
      TEMP[i]=0;
      strcpy(result,TEMP);
      return;
  }
  result=NULL;
}
#pragma inline//��ʼIMGHDR
static color IMGHDR_Color(IMGHDR *Handle, int x, int y)
{
  color *bm=(color*)Handle->bitmap;
  if(x < Handle->w && x>=0 && y < Handle->h && y>=0) 
    return *(bm + x + y*Handle->w);
  else
    return (color){0,0,0,0};
}
#pragma inline//��ʼIMGHDR
static void IMGHDR_Free(IMGHDR *Handle)
{
  int x, y;
  for(y=0; y<Handle->h; y++)
    for(x=0; x<Handle->w; x++)
      setcolor(Handle, x, y, (color){0,0,0,0});
}
#pragma inline//����IMGHDR
IMGHDR *IMGHDR_Create(int w, int h, int type)
{
  IMGHDR *img=malloc(sizeof(IMGHDR));
  img->w=w; 
  img->h=h; 
  img->bpnum=type;
  img->bitmap=malloc(h*w*sizeof(color));
  IMGHDRFree(img);
  return img;
}
#pragma inline//�ͷ�IMGHDR
static IMGHDR_Delete(IMGHDR *Handle)
{
  mfree(Handle->bitmap);
  mfree(Handle);
}
#pragma inline//����IMGHDR
static IMGHDR *IMGHDR_Sample(IMGHDR *Handle, int px, int py, int fast, int del)
{
  if (px==100 && py==100) return Handle;

  long newx = (Handle->w*px)/100,
  newy = (Handle->h*py)/100;
  
  float xScale, yScale, fX, fY;
  xScale = (float)Handle->w  / (float)newx;
  yScale = (float)Handle->h / (float)newy;
  
  IMGHDR *TEMP=IMGHDR_Create(newx,newy,CTYPE1);
  if (fast) 
  {
    for(long y=0; y<newy; y++)
    {
      fY = y * yScale;
      for(long x=0; x<newx; x++)
      {
        fX = x * xScale;
        setcolor(TEMP,  x,  y, getcolor(Handle, (long)fX,(long)fY));
      }
    }
  }
  else 
  {
    long ifX, ifY, ifX1, ifY1, xmax, ymax;
    float ir1, ir2, ig1, ig2, ib1, ib2, ia1, ia2, dx, dy;
    char r,g,b,a;
    color rgb1, rgb2, rgb3, rgb4;
    xmax = Handle->w-1;
    ymax = Handle->h-1;
    for(long y=0; y<newy; y++)
    {
      fY   = y * yScale;
      ifY  = (int)fY;
      ifY1 = min(ymax, ifY+1);
      dy   = fY - ifY;
      for(long x=0; x<newx; x++)
      {
        fX   = x * xScale;
        ifX  = (int)fX;
        ifX1 = min(xmax, ifX+1);
        dx   = fX - ifX;
        rgb1= IMGHDR_Color(Handle, ifX,ifY);
        rgb2= IMGHDR_Color(Handle, ifX1,ifY);
        rgb3= IMGHDR_Color(Handle, ifX,ifY1);
        rgb4= IMGHDR_Color(Handle, ifX1,ifY1);
        
        ir1 = rgb1.R * (1 - dy) + rgb3.R * dy;
        ig1 = rgb1.G * (1 - dy) + rgb3.G * dy;
        ib1 = rgb1.B * (1 - dy) + rgb3.B * dy;
        ia1 = rgb1.A * (1 - dy) + rgb3.A * dy;
        ir2 = rgb2.R * (1 - dy) + rgb4.R * dy;
        ig2 = rgb2.G * (1 - dy) + rgb4.G * dy;
        ib2 = rgb2.B * (1 - dy) + rgb4.B * dy;
        ia2 = rgb2.A * (1 - dy) + rgb4.A * dy;
        
        r = (char)(ir1 * (1 - dx) + ir2 * dx);
        g = (char)(ig1 * (1 - dx) + ig2 * dx);
        b = (char)(ib1 * (1 - dx) + ib2 * dx);
        a = (char)(ia1 * (1 - dx) + ia2 * dx);
        
        setcolor(TEMP, x,y,RGBA(r,g,b,a));
      }
    }
  }
  if(del)IMGHDR_Delete(Handle);
  return TEMP;  
}
#pragma inline//ת��PNG��IMGHDR
static IMGHDR *IMGHDR_Handle(int x,int y,const char *pic_path,int pic_size)
{
  //unsigned int pic_op = 50;
  IMGHDR *handle=0;
  if(strlen(pic_path))
  {
    FSTATS fstats;
    unsigned int err;     
    if (GetFileStats(pic_path,&fstats,&err)!=-1)
    {
      #ifdef NEWSGOLD
      if(handle=CreateIMGHDRFromPngFile(pic_path, CTYPE2)){                                                    
         handle=IMGHDR_Sample(handle, pic_size, pic_size, 0, 1);
      }      
      #else
      #ifdef X75
      if(handle=CreateIMGHDRFromPngFile(pic_path, CTYPE2)){                                                    
         handle=IMGHDR_Sample(handle, pic_size, pic_size, 0, 1);  
      }
      #else
         handle=CreateIMGHDRFromPngFile(pic_path,CTYPE2);
      #endif
      #endif
    }
  }
  return handle;
}
#pragma inline//͸��IMGHDR
static IMGHDR *IMGHDR_Alpha(IMGHDR *Handle, char a, int nw, int del)
{
  int i;
  color *r=(color*)Handle->bitmap;
  for(i=0;i<Handle->h*Handle->w; i++, r++)
    if(r->A>a)
      r->A-=a;
    else
      r->A=0;
    return Handle;
}
#pragma inline//��ʾIMGHDR
static IMGHDR_Draw(IMGHDR *Handle, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,Handle->w,Handle->h);
  SetPropTo_Obj5(&drwobj,&rc,0,Handle);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}
#endif/*SIEAPI_H_*/

//�����������ñ�
#if defined(_STD_USING)
 using _CSTD strtoul;
 using _CSTD strtol;
 using _CSTD kill_data;
 using _CSTD RunCUT;
 using _CSTD RunAPP;
 using _CSTD RunADR;
 using _CSTD ExtStrcmp;
 using _CSTD BSTRAdd;
 using _CSTD GetDayOf;
 using _CSTD PixlsWidth;
 using _CSTD toupper;
 using _CSTD strcmp_nocase;
 using _CSTD cmpstr_nocase;
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
 using _CSTD FileExists;
 using _CSTD CreateCanvas;
 using _CSTD SearchSub;
 using _CSTD IMGHDR_Draw;
 using _CSTD IMGHDR_Delete;
 using _CSTD IMGHDR_Free;
 using _CSTD IMGHDR_Color;
 using _CSTD IMGHDR_Alpha;
 using _CSTD IMGHDR_Sample;
 using _CSTD IMGHDR_Handle;
#endif /* �����������ñ� */
 

