#include "..\..\inc\swilib.h"
#include "image.h"
#include "..\lgp.h"

#define fon 1
#define st_off 2
#define st_on 3
#define wd_off 4
#define wd_on 5
#define logo 6

//#define NO_PNG

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#define num_alarms 5
#else
#define DEFAULT_DISK "0"
#define num_alarms 6
#endif

#define menus 9
#define sevens 7
#define dats 24

TTime time;

unsigned int status[6];
unsigned int hour[6];
unsigned int min[7];
unsigned int weekdays[6][7];
unsigned int day[7][24];
unsigned int backup[4];
unsigned int max;
unsigned int mode=0;
unsigned int X;
unsigned int Y;
unsigned int show_icon;

GBSTMR mytmr;
unsigned int input;

unsigned int num_alarm=0;
unsigned int menu=0;
unsigned int dat=0;
unsigned int seven=0;
unsigned int edit_level=1;
unsigned int ch[4];
unsigned int set=1;
int lng;
char cfgfile[]=DEFAULT_DISK":\\zbin\\img\\SmartAlerts\\SmartAlerts.cfg";
char fongpf[]=DEFAULT_DISK":\\zbin\\img\\SmartAlerts\\fon.gpf";
char fonpng[]=DEFAULT_DISK":\\zbin\\img\\SmartAlerts\\fon.png";
char bcfgfile[]=DEFAULT_DISK":\\Zbin\\etc\\alarm_melody.bcfg";

int scr_w;
int scr_h;
int font_size;

const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
char colors[4][4]={{0xFF,0,0,0x64},{0,0xFF,0,0x64},{0,0,0xFF,0x64},{0xC6,0xAA,0xAF,0x32}};
const char Pointer[5]={0x27,0x27,0xFF,0x27,0x27};
const IMGHDR imgPointer = {5,5,0x1,(char *)Pointer};
GBSTMR mytmr;

WSHDR *ws;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

typedef struct
{
  char signature[16];
  unsigned short picnum;
  unsigned short unk1;
  char w; 
  char h; 
  char Compr_Bits;  
}PICHDR;

void DrwStr(WSHDR *ws, int x, int y,int w,int h, int font,int flag,char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,w,h);
  SetPropTo_Obj1(&drwobj,&rc,0,ws,font,flag);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

DrwImg(IMGHDR *img, int x, int y)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
  DrawObject(&drwobj);
}

void DrawBackground()
{
  volatile int hFile;
  PICHDR Pic_Header;
  unsigned int io_error = 0;
  hFile = fopen(fongpf, A_ReadOnly + A_BIN, P_READ, &io_error);
  if(!io_error)
  {
    fread(hFile, &Pic_Header, sizeof(Pic_Header), &io_error);
    unsigned int buf_size = lseek(hFile, 0, S_END, &io_error, &io_error) - sizeof(PICHDR);
    lseek(hFile, sizeof(PICHDR), S_SET, &io_error, &io_error); 
    char *pic_buffer = malloc((buf_size+3)&(~3));
    fread(hFile, pic_buffer, buf_size, &io_error);    
    fclose(hFile, &io_error);
    IMGHDR img;
    img.w = Pic_Header.w;
    img.h = Pic_Header.h;
    img.bpnum = Pic_Header.Compr_Bits;
    img.bitmap = pic_buffer;
    DrwImg(&img, 0, 0);
    mfree(pic_buffer);
  }
  else
  {
    DrawImg(0, 0, (int)fonpng);
  }
}

void draw_pic(int num,int x, int y)
{
  switch(num)
  {
  case fon:
    {
      DrawBackground();
    } break;
  case st_off:
    {
      IMGHDR img;
      img.w = 52;
      img.h = 52;
      img.bpnum = 0x88;
      img.bitmap = _st_off;
      DrwImg(&img,x,y);
    } break;
  case st_on:
    {
      IMGHDR img;
      img.w = 52;
      img.h = 52;
      img.bpnum = 0x88;
      img.bitmap = _st_on;
      DrwImg(&img,x,y);
    } break;
  case wd_off:
    {
      IMGHDR img;
      img.w = 14;
      img.h = 14;
      img.bpnum = 0x85;
      img.bitmap = _wd_off;
      DrwImg(&img,x,y);
    } break;
  case wd_on:
    {
      IMGHDR img;
      img.w = 14;
      img.h = 14;
      img.bpnum = 0x85;
      img.bitmap = _wd_on;
      DrwImg(&img,x,y);
    } break;
  case logo:
    {
      IMGHDR img;
      img.w = 26;
      img.h = 14;
      img.bpnum = 0x85;
      img.bitmap = _logo;
      DrwImg(&img,x,y);
    } break;
  }
}

#ifndef NEWSGOLD

#define MAX_HEX   (100+10)
#define MAX_BIN   (4 * MAX_HEX)

int hex2bin(char *bin, int hex_len, char *hex)
{
    int i;
    int bi;
    int num;
    int start = 1;

    bi = 0;
    i = 0;
    while (hex[i] == '0') i++;
    for ( ; i < hex_len; i++) {
        if      (hex[i] >= '0' && hex[i] <= '9') num = hex[i]-'0';
        else if (hex[i] >= 'A' && hex[i] <= 'F') num = hex[i]-'A'+10;
        else if (hex[i] >= 'a' && hex[i] <= 'f') num = hex[i]-'a'+10;
        else continue;
        if (start) {
            if ((num >> 3) & 1) start = 0;

            if (!start) bin[bi++] = (num >> 2) & 1;
            else if ((num >> 2) & 1) start = 0;

            if (!start) bin[bi++] = (num >> 1) & 1;
            else if ((num >> 1) & 1) start = 0;

            if (!start) bin[bi++] = num & 1;
            start = 0;
        } else {
            bin[bi++] = (num >> 3) & 1;
            bin[bi++] = (num >> 2) & 1;
            bin[bi++] = (num >> 1) & 1;
            bin[bi++] =  num       & 1;
        }
    }
    return bi;
}

int bin2hex(char *hex, int bin_len, char *bin)
{
    int  i, j;
    int  num;
    int  ti, hi;
    char tmp[MAX_BIN];

    ti = 0;
    num = (bin_len+1) % 4;
    if (num > 0) {
        num = 4 - num;
        while (num-- > 0) tmp[ti++] = 0;
    }
    tmp[ti++] = 1;
    while (bin_len-- > 0) tmp[ti++] = *bin++;

    hi = 0;
    for (i = 0; i < ti; i += 4) {
        num = 0;
        for (j = 0; j < 4; j++) num = (num << 1) | tmp[i+j];
        if (num < 10) num += '0';
        else          num += 'A' - 10;
        hex[hi++] = num;
    }
    return hi;
}

int digit2int (char d)
{
  switch (d)
    {
    case 'F':
    case 'E':
    case 'D':
    case 'C':
    case 'B':
    case 'A':
      return d - 'A' + 10;
    case 'f':
    case 'e':
    case 'd':
    case 'c':
    case 'b':
    case 'a':
      return d - 'a' + 10;
    case '9':
    case '8':
    case '7':
    case '6':
    case '5':
    case '4':
    case '3':
    case '2':
    case '1':
    case '0':
      return d - '0';
    }
  return -1;
}

int hex2int (char *s)
{
  int res;
  int tmp;
  if (strlen (s) < 1)
    return -1;
  if (strlen (s) > 2)
    return -1;
  res = digit2int (s[0]);
  if (res < 0)
    return -1;
  tmp = res;
  if (strlen (s) > 1)
    {
      res = digit2int (s[1]);
      if (res < 0)
	return -1;
      tmp = tmp * 16 + res;
    }
  return tmp;
}

void geteeblock()
{
  char *Block5166=malloc(8);
  EEFullReadBlock(5166, Block5166, 0, 5,0,0);
  
  char *hex=malloc(8);
  char *bin=malloc(8);
  sprintf(hex, "%x", Block5166[3]);  
  hex2bin(bin, 3, hex);
  
  if (Block5166[4]==0xF1)
    status[5]=1;
  else status[5]=0;
  hour[5]=Block5166[0];
  min[5]=Block5166[1];
  
  weekdays[5][0]=bin[6];
  weekdays[5][1]=bin[5];
  weekdays[5][2]=bin[4];
  weekdays[5][3]=bin[3];
  weekdays[5][4]=bin[2];
  weekdays[5][5]=bin[1];
  weekdays[5][6]=bin[0];
  
  mfree(Block5166);
  mfree(bin);
  mfree(hex);
}

void saveeeblock()
{
  char *Block5166=malloc(8);
  Block5166[0]=hour[5];
  Block5166[1]=min[5];
  Block5166[2]=0;
  
  char *hex=malloc(3);
  char *bin=malloc(8);
  bin[0]=weekdays[5][6];
  bin[1]=weekdays[5][5];
  bin[2]=weekdays[5][4];
  bin[3]=weekdays[5][3];
  bin[4]=weekdays[5][2];
  bin[5]=weekdays[5][1];
  bin[6]=weekdays[5][0];
  bin[7]=1;
 
  
  bin2hex(hex, 7, bin);
  hex[2]=0;
  Block5166[3]=hex2int(hex);
  
  if (status[5]==1)
    Block5166[4]=0xF1;
  else Block5166[4]=0xF0;
  Block5166[5]=0xFF;
  
  EEFullWriteBlock(5166, Block5166, 0, 5,0,0);
  mfree(Block5166);
  mfree(bin);
  mfree(hex);
}

#else

void geteeblock()
{
  /*
  unsigned int err;
  int fp=fopen("2:\\Default\\PD\\alarmclock.pd", A_ReadOnly, P_READ,&err);
  if(fp!=-1)
  {
    char *buf=malloc(128);
    fread(fp, buf, 128, &err);
    fclose(fp,&err);
    
    buf=strstr(buf,"days_in_use=");
    buf+=strlen("days_in_use=");
    for (int i=0; i<7; i++)
    {
      weekdays[5][i]=buf[i]-'0';
    }
    buf=strstr(buf,"alarm_time=");
    buf+=strlen("alarm_time=");
    //????????????????
    buf=strstr(buf,"alarm_active=");
    buf+=strlen("alarm_active=");
    status[5]=buf[0]-'0';
    mfree(buf);
  }
  else
  {
    status[5]=0;
    hour[5]=0;
    min[5]=0;
    weekdays[5][0]=0;
    weekdays[5][1]=0;
    weekdays[5][2]=0;
    weekdays[5][3]=0;
    weekdays[5][4]=0;
    weekdays[5][5]=0;
    weekdays[5][6]=0;
  }
  */
}

void saveeeblock()
{
  
}

#endif

void load_settings(void)
{
  unsigned int err;
  int handle=fopen(cfgfile, A_ReadOnly, P_READ,&err);
  if(handle!=-1)
  {
    char *data=malloc(300);
    fread(handle,data,300,&err);
      
status[0]=data[2];
hour[0]=data[3];
min[0]=data[4];
weekdays[0][0]=data[5];
weekdays[0][1]=data[6];
weekdays[0][2]=data[7];
weekdays[0][3]=data[8];
weekdays[0][4]=data[9];
weekdays[0][5]=data[10];
weekdays[0][6]=data[11];
status[1]=data[12];
hour[1]=data[13];
min[1]=data[14];
weekdays[1][0]=data[15];
weekdays[1][1]=data[16];
weekdays[1][2]=data[17];
weekdays[1][3]=data[18];
weekdays[1][4]=data[19];
weekdays[1][5]=data[20];
weekdays[1][6]=data[21];
status[2]=data[22];
hour[2]=data[23];
min[2]=data[24];
weekdays[2][0]=data[25];
weekdays[2][1]=data[26];
weekdays[2][2]=data[27];
weekdays[2][3]=data[28];
weekdays[2][4]=data[29];
weekdays[2][5]=data[30];
weekdays[2][6]=data[31];
status[3]=data[32];
hour[3]=data[33];
min[3]=data[34];
weekdays[3][0]=data[35];
weekdays[3][1]=data[36];
weekdays[3][2]=data[37];
weekdays[3][3]=data[38];
weekdays[3][4]=data[39];
weekdays[3][5]=data[40];
weekdays[3][6]=data[41];
status[4]=data[42];
hour[4]=data[43];
min[4]=data[44];
weekdays[4][0]=data[45];
weekdays[4][1]=data[46];
weekdays[4][2]=data[47];
weekdays[4][3]=data[48];
weekdays[4][4]=data[49];
weekdays[4][5]=data[50];
weekdays[4][6]=data[51];

show_icon=data[53];
X=data[54];
Y=data[55];

min[6]=data[230];
day[0][0]=data[56];
day[0][1]=data[57];
day[0][2]=data[58];
day[0][3]=data[59];
day[0][4]=data[60];
day[0][5]=data[61];
day[0][6]=data[62];
day[0][7]=data[63];
day[0][8]=data[64];
day[0][9]=data[65];
day[0][10]=data[66];
day[0][11]=data[67];
day[0][12]=data[68];
day[0][13]=data[69];
day[0][14]=data[70];
day[0][15]=data[71];
day[0][16]=data[72];
day[0][17]=data[73];
day[0][18]=data[74];
day[0][19]=data[75];
day[0][20]=data[76];
day[0][21]=data[77];
day[0][22]=data[78];
day[0][23]=data[79];
day[1][0]=data[80];
day[1][1]=data[81];
day[1][2]=data[82];
day[1][3]=data[83];
day[1][4]=data[84];
day[1][5]=data[85];
day[1][6]=data[86];
day[1][7]=data[87];
day[1][8]=data[88];
day[1][9]=data[89];
day[1][10]=data[90];
day[1][11]=data[91];
day[1][12]=data[92];
day[1][13]=data[93];
day[1][14]=data[94];
day[1][15]=data[95];
day[1][16]=data[96];
day[1][17]=data[97];
day[1][18]=data[98];
day[1][19]=data[99];
day[1][20]=data[100];
day[1][21]=data[101];
day[1][22]=data[102];
day[1][23]=data[103];
day[2][0]=data[104];
day[2][1]=data[105];
day[2][2]=data[106];
day[2][3]=data[107];
day[2][4]=data[108];
day[2][5]=data[109];
day[2][6]=data[110];
day[2][7]=data[111];
day[2][8]=data[112];
day[2][9]=data[119];
day[2][10]=data[114];
day[2][11]=data[115];
day[2][12]=data[116];
day[2][13]=data[117];
day[2][14]=data[118];
day[2][15]=data[119];
day[2][16]=data[120];
day[2][17]=data[121];
day[2][18]=data[122];
day[2][19]=data[123];
day[2][20]=data[124];
day[2][21]=data[125];
day[2][22]=data[126];
day[2][23]=data[127];
day[3][0]=data[128];
day[3][1]=data[129];
day[3][2]=data[130];
day[3][3]=data[131];
day[3][4]=data[132];
day[3][5]=data[133];
day[3][6]=data[134];
day[3][7]=data[135];
day[3][8]=data[136];
day[3][9]=data[137];
day[3][10]=data[138];
day[3][11]=data[139];
day[3][12]=data[140];
day[3][13]=data[141];
day[3][14]=data[142];
day[3][15]=data[143];
day[3][16]=data[144];
day[3][17]=data[145];
day[3][18]=data[146];
day[3][19]=data[147];
day[3][20]=data[148];
day[3][21]=data[149];
day[3][22]=data[150];
day[3][23]=data[151];
day[4][0]=data[152];
day[4][1]=data[153];
day[4][2]=data[154];
day[4][3]=data[155];
day[4][4]=data[156];
day[4][5]=data[157];
day[4][6]=data[158];
day[4][7]=data[159];
day[4][8]=data[160];
day[4][9]=data[161];
day[4][10]=data[162];
day[4][11]=data[163];
day[4][12]=data[164];
day[4][13]=data[165];
day[4][14]=data[166];
day[4][15]=data[167];
day[4][16]=data[168];
day[4][17]=data[169];
day[4][18]=data[170];
day[4][19]=data[171];
day[4][20]=data[172];
day[4][21]=data[173];
day[4][22]=data[174];
day[4][23]=data[175];
day[5][0]=data[176];
day[5][1]=data[177];
day[5][2]=data[178];
day[5][3]=data[179];
day[5][4]=data[180];
day[5][5]=data[181];
day[5][6]=data[182];
day[5][7]=data[183];
day[5][8]=data[184];
day[5][9]=data[185];
day[5][10]=data[186];
day[5][11]=data[187];
day[5][12]=data[188];
day[5][13]=data[189];
day[5][14]=data[190];
day[5][15]=data[191];
day[5][16]=data[192];
day[5][17]=data[193];
day[5][18]=data[194];
day[5][19]=data[195];
day[5][20]=data[196];
day[5][21]=data[197];
day[5][22]=data[198];
day[5][23]=data[199];
day[6][0]=data[200];
day[6][1]=data[201];
day[6][2]=data[202];
day[6][3]=data[203];
day[6][4]=data[204];
day[6][5]=data[205];
day[6][6]=data[206];
day[6][7]=data[207];
day[6][8]=data[208];
day[6][9]=data[209];
day[6][10]=data[210];
day[6][11]=data[211];
day[6][12]=data[212];
day[6][13]=data[213];
day[6][14]=data[214];
day[6][15]=data[215];
day[6][16]=data[216];
day[6][17]=data[217];
day[6][18]=data[218];
day[6][19]=data[219];
day[6][20]=data[220];
day[6][21]=data[221];
day[6][22]=data[222];
day[6][23]=data[229];

    mfree(data);
  }
  fclose(handle,&err);
  geteeblock();
}

void save_settings(void)
{
  unsigned int err; 
  int handle=fopen(cfgfile,A_WriteOnly+A_Create,P_WRITE,&err);
  if(handle!=-1)
  {
    char *data=malloc(300);
 
    
data[2]=status[0];
data[3]=hour[0];
data[4]=min[0];
data[5]=weekdays[0][0];
data[6]=weekdays[0][1];
data[7]=weekdays[0][2];
data[8]=weekdays[0][3];
data[9]=weekdays[0][4];
data[10]=weekdays[0][5];
data[11]=weekdays[0][6];
data[12]=status[1];
data[13]=hour[1];
data[14]=min[1];
data[15]=weekdays[1][0];
data[16]=weekdays[1][1];
data[17]=weekdays[1][2];
data[18]=weekdays[1][3];
data[19]=weekdays[1][4];
data[20]=weekdays[1][5];
data[21]=weekdays[1][6];
data[22]=status[2];
data[23]=hour[2];
data[24]=min[2];
data[25]=weekdays[2][0];
data[26]=weekdays[2][1];
data[27]=weekdays[2][2];
data[28]=weekdays[2][3];
data[29]=weekdays[2][4];
data[30]=weekdays[2][5];
data[31]=weekdays[2][6];
data[32]=status[3];
data[33]=hour[3];
data[34]=min[3];
data[35]=weekdays[3][0];
data[36]=weekdays[3][1];
data[37]=weekdays[3][2];
data[38]=weekdays[3][3];
data[39]=weekdays[3][4];
data[40]=weekdays[3][5];
data[41]=weekdays[3][6];
data[42]=status[4];
data[43]=hour[4];
data[44]=min[4];
data[45]=weekdays[4][0];
data[46]=weekdays[4][1];
data[47]=weekdays[4][2];
data[48]=weekdays[4][3];
data[49]=weekdays[4][4];
data[50]=weekdays[4][5];
data[51]=weekdays[4][6];

data[53]=show_icon;
data[54]=X;
data[55]=Y;


data[56]=day[0][0];
data[57]=day[0][1];
data[58]=day[0][2];
data[59]=day[0][3];
data[60]=day[0][4];
data[61]=day[0][5];
data[62]=day[0][6];
data[63]=day[0][7];
data[64]=day[0][8];
data[65]=day[0][9];
data[66]=day[0][10];
data[67]=day[0][11];
data[68]=day[0][12];
data[69]=day[0][13];
data[70]=day[0][14];
data[71]=day[0][15];
data[72]=day[0][16];
data[73]=day[0][17];
data[74]=day[0][18];
data[75]=day[0][19];
data[76]=day[0][20];
data[77]=day[0][21];
data[78]=day[0][22];
data[79]=day[0][23];
data[80]=day[1][0];
data[81]=day[1][1];
data[82]=day[1][2];
data[83]=day[1][3];
data[84]=day[1][4];
data[85]=day[1][5];
data[86]=day[1][6];
data[87]=day[1][7];
data[88]=day[1][8];
data[89]=day[1][9];
data[90]=day[1][10];
data[91]=day[1][11];
data[92]=day[1][12];
data[93]=day[1][13];
data[94]=day[1][14];
data[95]=day[1][15];
data[96]=day[1][16];
data[97]=day[1][17];
data[98]=day[1][18];
data[99]=day[1][19];
data[100]=day[1][20];
data[101]=day[1][21];
data[102]=day[1][22];
data[103]=day[1][23];
data[104]=day[2][0];
data[105]=day[2][1];
data[106]=day[2][2];
data[107]=day[2][3];
data[108]=day[2][4];
data[109]=day[2][5];
data[110]=day[2][6];
data[111]=day[2][7];
data[112]=day[2][8];
data[119]=day[2][9];
data[114]=day[2][10];
data[115]=day[2][11];
data[116]=day[2][12];
data[117]=day[2][13];
data[118]=day[2][14];
data[119]=day[2][15];
data[120]=day[2][16];
data[121]=day[2][17];
data[122]=day[2][18];
data[123]=day[2][19];
data[124]=day[2][20];
data[125]=day[2][21];
data[126]=day[2][22];
data[127]=day[2][23];
data[128]=day[3][0];
data[129]=day[3][1];
data[130]=day[3][2];
data[131]=day[3][3];
data[132]=day[3][4];
data[133]=day[3][5];
data[134]=day[3][6];
data[135]=day[3][7];
data[136]=day[3][8];
data[137]=day[3][9];
data[138]=day[3][10];
data[139]=day[3][11];
data[140]=day[3][12];
data[141]=day[3][13];
data[142]=day[3][14];
data[143]=day[3][15];
data[144]=day[3][16];
data[145]=day[3][17];
data[146]=day[3][18];
data[147]=day[3][19];
data[148]=day[3][20];
data[149]=day[3][21];
data[150]=day[3][22];
data[151]=day[3][23];
data[152]=day[4][0];
data[153]=day[4][1];
data[154]=day[4][2];
data[155]=day[4][3];
data[156]=day[4][4];
data[157]=day[4][5];
data[158]=day[4][6];
data[159]=day[4][7];
data[160]=day[4][8];
data[161]=day[4][9];
data[162]=day[4][10];
data[163]=day[4][11];
data[164]=day[4][12];
data[165]=day[4][13];
data[166]=day[4][14];
data[167]=day[4][15];
data[168]=day[4][16];
data[169]=day[4][17];
data[170]=day[4][18];
data[171]=day[4][19];
data[172]=day[4][20];
data[173]=day[4][21];
data[174]=day[4][22];
data[175]=day[4][23];
data[176]=day[5][0];
data[177]=day[5][1];
data[178]=day[5][2];
data[179]=day[5][3];
data[180]=day[5][4];
data[181]=day[5][5];
data[182]=day[5][6];
data[183]=day[5][7];
data[184]=day[5][8];
data[185]=day[5][9];
data[186]=day[5][10];
data[187]=day[5][11];
data[188]=day[5][12];
data[189]=day[5][13];
data[190]=day[5][14];
data[191]=day[5][15];
data[192]=day[5][16];
data[193]=day[5][17];
data[194]=day[5][18];
data[195]=day[5][19];
data[196]=day[5][20];
data[197]=day[5][21];
data[198]=day[5][22];
data[199]=day[5][23];
data[200]=day[6][0];
data[201]=day[6][1];
data[202]=day[6][2];
data[203]=day[6][3];
data[204]=day[6][4];
data[205]=day[6][5];
data[206]=day[6][6];
data[207]=day[6][7];
data[208]=day[6][8];
data[209]=day[6][9];
data[210]=day[6][10];
data[211]=day[6][11];
data[212]=day[6][12];
data[213]=day[6][13];
data[214]=day[6][14];
data[215]=day[6][15];
data[216]=day[6][16];
data[217]=day[6][17];
data[218]=day[6][18];
data[219]=day[6][19];
data[220]=day[6][20];
data[221]=day[6][21];
data[222]=day[6][22];
data[229]=day[6][23];

data[230]=min[6];

    fwrite(handle,data,300,&err);
    mfree(data);
  }
  fclose(handle,&err);
  saveeeblock();
}

void edit()
{
  if (input)
  {
    switch(set)
    {
    case 1: if(ch[1])
        hour[num_alarm]=backup[1];
    case 2: if(ch[2])
      min[num_alarm]=backup[2];
            if(ch[1])
      min[6]=backup[2];   
    case 3: if(ch[3])
      day[seven][dat]=backup[3];
    }
    }
}

void status_on_off()
{
  if (status[num_alarm]==1) status[num_alarm]=0; else status[num_alarm]=1;
}

void weekday_on_off()
{
  if (weekdays[num_alarm][set]==1) weekdays[num_alarm][set]=0; else weekdays[num_alarm][set]=1;
}


void menuselect()
{
  switch(menu)
  {
      case 0:
        mode=1;
        break;
      case 2:
        mode=3;
        break;      
             
      default:
      break;
  }
}


void OnRedraw()
{
  switch(mode)
  {
  case 0:
    {
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
      draw_pic(fon,0,0);
      //draw_pic(logo,2,2);
      
      wsprintf(ws, "%t",name);
      DrwStr(ws,15,3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws, "%t",select);
      DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws, "%t",save);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      

      int tmp=scr_h/10.3;
      for (int i=0;i<menus;i++)
      {
        wsprintf(ws, "%t",alerts_name[i]);
        if (menu==i) DrwStr(ws,5,1+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,5,1+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
    } break;

    
  case 1:
    {
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
      draw_pic(fon,0,0);
      draw_pic(logo,2,2);
      
      wsprintf(ws, "%t",alerts_name[0]);
      DrwStr(ws,30,3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws, "%t",change);
      DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws, "%t",back);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      char *stat=malloc(16);
      int tmp=scr_h/7.3;
      for (int i=0;i<num_alarms;i++)
      {
        if (status[i]) strcpy(stat,on);
          else strcpy(stat,off);
        wsprintf(ws, "%t %d: %d:%02d %t",alerts_name[0],i+1,hour[i],min[i],stat);
        if (num_alarm==i) DrwStr(ws,5,1+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,5,1+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      mfree(stat);
    } break;

   case 3:
    {
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
      draw_pic(fon,0,0);
      //draw_pic(logo,2,2);
      
      wsprintf(ws, "%t",alerts_name[2]);
      DrwStr(ws,30,3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws, "%t",change);
      DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws, "%t",back);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      

      int tmp=scr_h/8.7;
      for (int i=0;i<7;i++)
      {
        wsprintf(ws, "%t",wd[i]);
        if (seven==i) DrwStr(ws,5,1+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,5,1+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
    } break; 
    
  case 12:
    {
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
      draw_pic(fon,0,0);
      draw_pic(logo,2,2);
      
      wsprintf(ws, "%t %d",alerts_name[0],num_alarm+1);
      DrwStr(ws,30,3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      //////////////////////////////////  SL65  ////////////////////////////////
#ifdef SL65
      if(status[num_alarm]==1) draw_pic(st_on,5,HeaderH());
        else draw_pic(st_off,5,HeaderH());
#else
      //////////////////////////////////////////////////////////////////////////
      if(status[num_alarm]==1) draw_pic(st_on,scr_w/2-25,HeaderH());
        else draw_pic(st_off,scr_w/2-25,HeaderH());
#endif
      if ((edit_level==1)||(edit_level==3))
        {
          wsprintf(ws,"%t",change);
          DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        }
      
      wsprintf(ws, "%t",ok);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      int a=scr_w/2-GetSymbolWidth('n',FONT_SMALL)*2;
      if (status[num_alarm]) wsprintf(ws, "%t",on);
          else 
          {
            wsprintf(ws, "%t",off);
            a-=3;
          }
      //////////////////////////////////  SL65  ////////////////////////////////
#ifdef SL65
      if (edit_level==1) DrwStr(ws,67,HeaderH()+18,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,67,HeaderH()+18,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
#else
      //////////////////////////////////////////////////////////////////////////
      if (edit_level==1) DrwStr(ws,a,HeaderH()+57,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,a,HeaderH()+57,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
#endif
      
      //////////////////////////////////  SL65  ////////////////////////////////
#ifdef SL65
      a=67;
        int b=HeaderH()+21+font_size;
      wsprintf(ws, "%02d",hour[num_alarm]);
      if ((edit_level==2)&&(set==1))
        DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        
      a+=(GetSymbolWidth((backup[1]/10)+'0',FONT_SMALL)+GetSymbolWidth((backup[1]%10)+'0',FONT_SMALL));
      wsprintf(ws, ":");
      DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      a+=GetSymbolWidth(':',FONT_SMALL);
      wsprintf(ws, "%02d",min[num_alarm]);
      if ((edit_level==2)&&(set==2))
        DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));      
#else
      //////////////////////////////////////////////////////////////////////////
      a=scr_w/2-GetSymbolWidth((backup[1]/10)+'0',FONT_SMALL)-GetSymbolWidth((backup[1]%10)+'0',FONT_SMALL);      
        int b=HeaderH()+60+font_size;
      wsprintf(ws, "%02d",hour[num_alarm]);
      if ((edit_level==2)&&(set==1))
        DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        
      a=scr_w/2;
      wsprintf(ws, ":");
      DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      a+=GetSymbolWidth(':',FONT_SMALL);
      wsprintf(ws, "%02d",min[num_alarm]);
      if ((edit_level==2)&&(set==2))
        DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,a,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
#endif
      a=scr_w/7.3;
      b=scr_h-SoftkeyH()-font_size-24;
      for (int i=0;i<7;i++)
      {
        wsprintf(ws, "%t",wd[i]);
        if ((edit_level==3)&&(set==i)) DrwStr(ws,4+a*i,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,4+a*i,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      b+=(font_size+3);
      for (int i=0;i<7;i++)
      {
        if (weekdays[num_alarm][i]) draw_pic(wd_on,5+a*i,b);
          else draw_pic(wd_off,5+a*i,b);
      }
    } break;
    
    
  case 13:
    {
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,
                   GetPaletteAdrByColorIndex(0),
                   GetPaletteAdrByColorIndex(0));
      for (int y_0=0; y_0< scr_h;y_0+=10)
        {
          DrawLine(0,y_0,scr_w,y_0,1,colors[3]);
        }
      for (int x_0=0; x_0<scr_w;x_0+=10)
        {
          DrawLine(x_0,0,x_0,scr_h,1,colors[3]);
        }
      DrwImg((IMGHDR *)&imgPointer,X-2,Y-2);
      
      wsprintf(ws, "%03d,%03d", X, Y);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
      
      if (show_icon) wsprintf(ws, "%t",on);
        else wsprintf(ws, "%t",off);
      DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
    }
    
    
  case 15:
    {
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
      draw_pic(fon,0,0);
     // draw_pic(logo,2,2);
      
      wsprintf(ws, "%t %d",alerts_name[2],seven+1);
      DrwStr(ws,30,3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

      wsprintf(ws,"%t",change);
      DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

      wsprintf(ws, "%t",ok);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
     int a=scr_w/4;
     
     GetDateTime(0,&time);
     
     wsprintf(ws,"%d:%d_Min=%02d",time.hour,time.min,min[6]);

      if (edit_level==1) DrwStr(ws,a,HeaderH(),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,a,HeaderH(),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        
            
      int b=HeaderH()+font_size+4;
      
      for(int i=0;i<dats;i++)  
      {  
      wsprintf(ws, "%02d-%01d",i,day[seven][i]);
      
      if(i<4)
      {
      if ((edit_level==2)&&(dat==i))
        DrwStr(ws,4+i*ScreenW()/4,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,4+i*ScreenW()/4,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      else if(i<8)
      {
      if ((edit_level==2)&&(dat==i))
        DrwStr(ws,4+(i-4)*ScreenW()/4,b+(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,4+(i-4)*ScreenW()/4,b+(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      else if(i<12)
      {
      if ((edit_level==2)&&(dat==i))
        DrwStr(ws,4+(i-8)*ScreenW()/4,b+2*(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,4+(i-8)*ScreenW()/4,b+2*(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      else if(i<16)
      {
      if ((edit_level==2)&&(dat==i))
        DrwStr(ws,4+(i-12)*ScreenW()/4,b+3*(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,4+(i-12)*ScreenW()/4,b+3*(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      else if(i<20)
      {
      if ((edit_level==2)&&(dat==i))
        DrwStr(ws,4+(i-16)*ScreenW()/4,b+4*(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,4+(i-16)*ScreenW()/4,b+4*(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      else 
      {
      if ((edit_level==2)&&(dat==i))
        DrwStr(ws,4+(i-20)*ScreenW()/4,b+5*(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,4+(i-20)*ScreenW()/4,b+5*(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      }
      
      
    } break;  
    
  }
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  ws = AllocWS(128);
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(ws);
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  //DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

void open_bcfg()
{
  WSHDR *_elf=AllocWS(256);
  wsprintf(_elf,"%s",bcfgfile);
  ExecuteFile(_elf,0,0);
  FreeWS(_elf);
}

int onkey(unsigned char keycode, int pressed)
{
  switch(mode)
  {
    case 0:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
            case LEFT_SOFT:  menuselect(); OnRedraw(); break;
            case RIGHT_SOFT:
              {
                save_settings();
                GBS_SendMessage(MMI_CEPID, MSG_RECONFIGURE_REQ,0,"alarm");
                return(1);
              }
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
                if (menu>0) menu--;
                  else menu=(menus-1);
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
                if (menu<(menus-1)) menu++;
                  else menu=0;
                  break;
              }
            /*  
            case GREEN_BUTTON: open_bcfg(); break;
            case '1': num_alarm=0; break;
            case '2': num_alarm=1; break;
            case '3': num_alarm=2; break;
            case '4': num_alarm=3; break;
            case '5': num_alarm=4; break;
            //case '6': num_alarm=5; break;
            case '#': mode=3; break;
            //case '*': saveeeblock(); break;
            //case '*': ShowMSG(1,(int)"Alarm cfg editor\n(c)Geka"); break;
              */
            }
          }
      } break;
    case 1:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
            case LEFT_SOFT:  mode=12; OnRedraw(); break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
                if (num_alarm>0) num_alarm--;
                  else num_alarm=(num_alarms-1);
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
                if (num_alarm<(num_alarms-1)) num_alarm++;
                  else num_alarm=0;
                  break;
              }
            case GREEN_BUTTON: open_bcfg(); break;
            case '1': num_alarm=0; break;
            case '2': num_alarm=1; break;
            case '3': num_alarm=2; break;
            case '4': num_alarm=3; break;
            case '5': num_alarm=4; break;
            //case '6': num_alarm=5; break;
            case '#': mode=13; break;
            //case '*': saveeeblock(); break;
            //case '*': ShowMSG(1,(int)"Alarm cfg editor\n(c)Geka"); break;
            }
          }
      } break;
      
   case 3:
      {
        switch(pressed)
          {
          case KEY_UP: break;
          case LONG_PRESS:
          case KEY_DOWN:
            switch(keycode)
            {
            case RED_BUTTON: return(1);
            case ENTER_BUTTON:
            case LEFT_SOFT:  mode=15; OnRedraw(); break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
                if (seven>0) seven--;
                  else seven=(sevens-1);
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
                if (seven<(sevens-1)) seven++;
                  else seven=0;
                  break;
              }
            }
          }
      } break;   
      
  case 12:
    {
      switch(pressed)
      {
      case KEY_UP: break;
      case LONG_PRESS:
      case KEY_DOWN:
        switch(keycode)
        {
        case RED_BUTTON:  mode=1; break;
        case RIGHT_SOFT:  mode=1; OnRedraw(); break;
        case LEFT_SOFT:
          {
            if (edit_level==1) status_on_off();
            if (edit_level==3)
            {
              weekday_on_off();
              if (set<6) set++;
               else set=0;
            }
            break;
          }
          case UP_BUTTON:
            {
              if (edit_level>1) edit_level--;
                else edit_level=3;
              if (edit_level==3)
                set=0;
              else set=1;
              input=1;
              edit();
              break;
            }
        case DOWN_BUTTON:
          {
            if (edit_level<3) edit_level++;
              else edit_level=1;
              if (edit_level==3)
                set=0;
              else set=1;
            input=1;
            edit();
            break;
          }
        case LEFT_BUTTON:
          {
            if(edit_level==1) status_on_off();
            if(edit_level==2)
            {
              if (set>0) set--;
                else set=2;
              lng=0;
            }
            if(edit_level==3)
            {
              if (set>0) set--;
                else set=6;
            }
            break;
          }
        case RIGHT_BUTTON:
          {
            if(edit_level==1) status_on_off();
            if(edit_level==2)
            {
              if (set<2) set++;
                else set=1;
              lng=0;
            }
            if(edit_level==3)
            {
              if (set<6) set++;
                else set=0;
            }
            break;
          }
        case ENTER_BUTTON:
          {
            if(edit_level==3)
            {
              weekday_on_off();
              if (set<6) set++;
                else set=0;
            }
            break;
          }
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
            if(edit_level==2)
            {
              ++lng;
              if (set==1) max=3;
                else max=6;
              if (backup[set]<max) backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                  lng=1;
                }
                ch[set]=1;
                input=1;
                edit();
                if (lng==2) {if(set==1) {set=2; lng=0;} else {edit_level=1; lng=1;}}
            }
            if(edit_level==3)
            {
              int key=keycode-'0';
              if (key<8&&key>0) set=key;
            }
            break;
          }
        }
      }
    } break;
  case 13:
    {
      switch(pressed)
      {
      case KEY_UP: break;
      case LONG_PRESS:
        switch(keycode)
          {
          case LEFT_BUTTON: case '4': if (X>0) X-=5; else X=scr_w; break;
          case RIGHT_BUTTON: case '6': if (X<132) X+=5; else X=0; break;
          case UP_BUTTON: case '2': if (Y>0) Y-=5; else Y=scr_h; break;
          case DOWN_BUTTON: case '8': if (Y<176) Y+=5; else Y=0; break;
          }
      case KEY_DOWN:
        switch(keycode)
        {
        case RED_BUTTON:  mode=1; break;
        case LEFT_SOFT: if (show_icon==1) show_icon=0; else show_icon=1; break;
        case LEFT_BUTTON: case '4': if (X!=0) X--; else X=scr_w; break;
        case RIGHT_BUTTON: case '6': if (X!=132) X++; else X=0; break;
        case UP_BUTTON: case '2': if (Y!=0) Y--; else Y=scr_h; break;
        case DOWN_BUTTON: case '8': if (Y!=176) Y++; else Y=0; break;
        default: mode=1; break;
        }
      }
    } break;
    
    
  case 15:
    {
      switch(pressed)
      {
      case KEY_UP: break;
      case LONG_PRESS:
      case KEY_DOWN:
        switch(keycode)
        {
        case RED_BUTTON:  mode=3; break;
        case RIGHT_SOFT:  mode=3; OnRedraw(); break;
        case LEFT_SOFT:
          {
            if (edit_level==1)
            {edit_level=2;dat=0;}
            else
              edit_level=1;
            break;
          }
          case UP_BUTTON:
            {
              if (edit_level==2&&dat>3) 
                dat=dat-4;
              else
                dat=dat+20;
              break;
            }
        case DOWN_BUTTON:
          {
            if (edit_level==2&&dat<20) 
                dat=dat+4;
            else
                dat=dat-20;
            break;
          }
        case LEFT_BUTTON:
          {
            if(edit_level==2)
            {
              if (dat>0) dat--;
                else dat=23;
            }
            break;
          }
        case RIGHT_BUTTON:
          {
            if(edit_level==2)
            {
              if (dat<23) dat++;
                else dat=0;
            }
            break;
          }
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
            if(edit_level==1)
            {
               set=2;
                
               if (backup[set]<6) backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                  lng=1;
                }

               ch[1]=1;
               input=1;
               edit();
            }
            
            
            if(edit_level==2)
            {
                backup[3]=keycode-'0';
                set=3;
                ch[set]=1;
                input=1;
                edit();
                dat++;
            }
            break;
          }
        }
      }
    } break;
  }
  DirectRedrawGUI();
  return(0);
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  return onkey(msg->gbsmsg->submess, msg->gbsmsg->msg);
}

  extern void kill_data(void *p, void (*func_p)(void *));
#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
}
#endif

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,
  #else
  (void *)kill_data,
  #endif
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,129,129};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Alarm cfg editor");
  FreeWS(ws);
}

int main(void)
{
  font_size=GetFontYSIZE(FONT_SMALL);
  load_settings();
  scr_w=ScreenW()-1;
  scr_h=ScreenH()-1;
  LockSched();
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
