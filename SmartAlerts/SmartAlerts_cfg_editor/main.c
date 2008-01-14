#include "..\..\inc\swilib.h"
#include "conf_loader.h"
#include "image.h"
#include "..\lgp.h"
#include "code.h"

#define fon 1
#define st_off 2
#define st_on 3
#define wd_off 4
#define wd_on 5
#define logo 6


#ifdef NEWSGOLD
#define num_alarms 5

#ifdef S68
#define DEFAULT_DISK "0"
#else
#define DEFAULT_DISK "4"
#endif

#else
#define DEFAULT_DISK "0"
#define num_alarms 6
#endif

#define menus 9
#define sevens 8
#define dats 24


TTime time;

unsigned int files[5];
unsigned int smss[5];
unsigned int calls[5];
unsigned int amenus[11];

unsigned int status[6];
unsigned int hour[6];
unsigned int min[7];
unsigned int weekdays[6][7];
unsigned int day[7][24];
unsigned int miss[6];

unsigned int bmenus[4];
unsigned int backup[7];
unsigned int other[9];
unsigned int name2[9];
unsigned int max;
unsigned int mode=0;
unsigned int X;
unsigned int Y;
unsigned int show_icon;

GBSTMR mytmr;
unsigned int input;

unsigned int file;
unsigned int sms;
unsigned int call;

unsigned int amenu=0;
unsigned int mmenu=0;
unsigned int bmenu=0;
unsigned int num=0;
unsigned int onum=0;
unsigned int num_alarm=0;
unsigned int menu=0;
unsigned int dat=0;
unsigned int seven=0;
unsigned int edit_level=1;
unsigned int ch[12];
unsigned int set=1;
int lng;
char cfgfile[]=DEFAULT_DISK":\\zbin\\img\\SmartAlerts\\SmartAlerts.cfg";
char fonpng[]=DEFAULT_DISK":\\zbin\\img\\SmartAlerts\\fon.png";
char bcfgfile[]=DEFAULT_DISK":\\Zbin\\etc\\alarm_melody.bcfg";
char bcfgfile1[]=DEFAULT_DISK":\\Zbin\\etc\\SmartAlerts.bcfg";
char ring[]=DEFAULT_DISK":\\Zbin\\img\\SmartAlerts\\alarm_ring.elf";

int scr_w;
int scr_h;
int font_size;
int a;
int tmp;

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


void draw_pic(int num,int x, int y)
{
  switch(num)
  {
  case fon:
    {
      DrawImg(0, 0, (int)fonpng);
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
    char *data=malloc(280);
    fread(handle,data,280,&err);
      
show_icon=data[2];
X=data[3];
Y=data[4];
//5
for(int i=0;i<5;i++)
{
  status[i]=data[i+5];
  hour[i]=data[i+10];
  min[i]=data[i+15];
  files[i]=data[i+20];
  calls[i]=data[i+25];
  smss[i]=data[i+30];
}
//35
for(int i=0;i<35;i++)
{
weekdays[i/7][i%7]=data[i+35];
}
//70
for(int i=0;i<168;i++)
{
day[i/24][i%24]=data[i+70];
}
//238
min[6]=data[238];

name2[0]=data[239];
name2[1]=data[240];
name2[2]=data[241];
name2[3]=data[242];
name2[4]=data[243];
name2[5]=data[244];
name2[6]=data[245];
name2[7]=data[246];

other[8]=data[247];

other[0]=data[248];
other[1]=data[249];
other[2]=data[250];
other[3]=data[251];

other[4]=data[252];
other[5]=data[253];
other[6]=data[254];
other[7]=data[255];

bmenus[0]=data[256];
bmenus[1]=data[257];
bmenus[2]=data[258];
bmenus[3]=data[259];

miss[0]=data[260];
miss[1]=data[261];
miss[2]=data[262];
miss[3]=data[263];
miss[4]=data[264];
miss[5]=data[265];

amenus[0]=data[266];
amenus[1]=data[267];
amenus[2]=data[268];
amenus[3]=data[269];
amenus[4]=data[270];
amenus[5]=data[271];
amenus[6]=data[272];
amenus[7]=data[273];
amenus[8]=data[274];
amenus[9]=data[275];
amenus[10]=data[276];



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
    char *data=malloc(280);

data[2]=show_icon;
data[3]=X;
data[4]=Y;
//5
for(int i=0;i<5;i++)
{
  data[i+5]=status[i];
  data[i+10]=hour[i];
  data[i+15]=min[i];
  data[i+20]=files[i];
  data[i+25]=calls[i];
  data[i+30]=smss[i];
}
//35
for(int i=0;i<35;i++)
{
data[i+35]=weekdays[i/7][i%7];
}
//70
for(int i=0;i<168;i++)
{
data[i+70]=day[i/24][i%24];
}
//238
data[238]=min[6];

data[239]=name2[0];
data[240]=name2[1];
data[241]=name2[2];
data[242]=name2[3];
data[243]=name2[4];
data[244]=name2[5];
data[245]=name2[6];
data[246]=name2[7];

data[247]=other[8];

data[248]=other[0];
data[249]=other[1];
data[250]=other[2];
data[251]=other[3];
data[252]=other[4];
data[253]=other[5];
data[254]=other[6];
data[255]=other[7];

data[256]=bmenus[0];
data[257]=bmenus[1];
data[258]=bmenus[2];
data[259]=bmenus[3];

data[260]=miss[0];
data[261]=miss[1];
data[262]=miss[2];
data[263]=miss[3];
data[264]=miss[4];
data[265]=miss[5];

data[266]=amenus[0];
data[267]=amenus[1];
data[268]=amenus[2];
data[269]=amenus[3];
data[270]=amenus[4];
data[271]=amenus[5];
data[272]=amenus[6];
data[273]=amenus[7];
data[274]=amenus[8];
data[275]=amenus[9];
data[276]=amenus[10];

    fwrite(handle,data,280,&err);
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
            if(ch[4])
      min[6]=backup[2];   
           if(ch[5])
      bmenus[bmenu]=backup[2];   
           if(ch[6])
      miss[mmenu]=backup[2];
            if(ch[7])
      files[file]=backup[2];
           if(ch[8])
      calls[call]=backup[2];      
           if(ch[9])
      smss[sms]=backup[2];
          if(ch[10])
      amenus[amenu]=backup[2];
          if(ch[11])
      other[onum]=backup[2];
      
    case 3: 
      if(ch[3])
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
      case 1:
        mode=2;
        break;
      case 2:
        mode=3;
        break;
      case 3:
        mode=4;
        break;
      case 4:
        mode=5;
        break;
      case 5:
        mode=6;
        break;
      case 6:
        mode=7;
        break;
      case 7:
        mode=8;
        break;
      case 8:
        mode=9;
        break;      
             
      default:
      break;
  }
}

void menux()
{
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
      draw_pic(fon,0,0);
      
      if(mode==15)
      ascii2ws(ws,wd2[seven],0);
      else
      ascii2ws(ws,alerts_name[mode],0);
      DrwStr(ws,5,3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
      a=scr_w-font_size*2;
      tmp=scr_h/11.6;
      GetDateTime(0,&time);
      wsprintf(ws,"%02d:%02d",time.hour,time.min);
      DrwStr(ws,a-font_size,4,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      ascii2ws(ws, change,0);
      DrwStr(ws,18,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
     if(mode==0)
      ascii2ws(ws,save,0);
     else
      ascii2ws(ws,back,0);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}


void OnRedraw()
{
  switch(mode)
  {
  case 0:
    {
      //draw_pic(logo,2,2);     
      menux();
      for (int i=0;i<menus;i++)
      {
        ascii2ws(ws,alerts_name[i+1],0);
        if (menu==i) DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        if(i<menus-1)
        {
        if (name2[i]) draw_pic(wd_on,a,6+tmp*(i+1));
          else draw_pic(wd_off,a,6+tmp*(i+1));
        }
      }

    } break;

    
  case 1:
    {
      //draw_pic(logo,2,2);
      menux();
      char *stat=malloc(16);
      for (int i=0;i<num_alarms;i++)
      {
        if (status[i]) strcpy(stat,on2);
          else strcpy(stat,off2);
        wsprintf(ws, "%d: %d:%02d %t",i+1,hour[i],min[i],stat);
        if (num_alarm==i) DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      mfree(stat);
    } break;

 case 2:
    {
      //draw_pic(logo,2,2);
      menux();
      wsprintf(ws,"%02d",amenus[3]);
      if(amenu==3)
      DrwStr(ws,a-font_size*1.5,6+tmp*4,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
      else
      DrwStr(ws,a-font_size*1.5,6+tmp*4,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws, "-");
      DrwStr(ws,a-font_size*0.5,6+tmp*4,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

      for (int i=0;i<10;i++)
      { 
       ascii2ws(ws,an[i],0); 
       if(amenu==i&&i<3)
       DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3)); 
       else if(i<9)
       DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

       if (i<3) 
       {
       if (amenus[i])  draw_pic(wd_on,a,6+tmp*(i+1));
          else draw_pic(wd_off,a,6+tmp*(i+1));
       }

       if(i>3)
       {
        wsprintf(ws, "%02d",amenus[i]);
        if(amenu==i)
        DrwStr(ws,a,6+tmp*i,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,a,6+tmp*i,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       }
      } 

    }break; 

   case 3:
    {
      //draw_pic(logo,2,2);
      menux();
      
      for (int i=0;i<8;i++)
      {
        ascii2ws(ws,wd2[i],0);
        if (seven==i) DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      if (other[8])  draw_pic(wd_on,scr_w-font_size*2,6+tmp*8);
          else draw_pic(wd_off,scr_w-font_size*2,6+tmp*8);
 
    } break; 
  
  case 4:
    {
      //draw_pic(logo,2,2);
      menux();
      for (int i=0;i<6;i++)
      {
        ascii2ws(ws,mn[i],0);
        if (mmenu==i&&i<2) 
        DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        if(i<2)
        {
        if (miss[i]) draw_pic(wd_on,a,6+tmp*(i+1));
          else draw_pic(wd_off,a,6+tmp*(i+1));
        }
        else
        {
        wsprintf(ws, "%02d",miss[i]);
        if(mmenu==i)
        DrwStr(ws,a,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,a,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        }
      }
      }break; 
  
  case 5:
    {
      //draw_pic(logo,2,2);
  
      menux();
      
      for (int i=0;i<4;i++)
      { 
       ascii2ws(ws,bn[i],0); 
       if(bmenu==i&&i==0)  
       DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3)); 
       else
       DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
       if (bmenus[0]) 
        draw_pic(wd_on,a,6+tmp);
          else draw_pic(wd_off,a,6+tmp);
       if(i>0)
       {
        wsprintf(ws, "%02d",bmenus[i]);
        if(bmenu==i)
        DrwStr(ws,a,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,a,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       }
      } 
    }break; 
    
    case 6:
    {
      //draw_pic(logo,2,2);
      menux();
      int c=font_size*1.5;

       ascii2ws(ws,rn,0); 
      
       if(file==0)  
       DrwStr(ws,5,6+tmp,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3)); 
       else
       DrwStr(ws,5,6+tmp,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
       if (files[0]) 
        draw_pic(wd_on,a,6+tmp);
          else draw_pic(wd_off,a,6+tmp);

      for(int i=1;i<5;i++)  
      {  
      wsprintf(ws, "%02d",files[i]);
      
      if (file==i)
        DrwStr(ws,5+(i-1)*c,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,5+(i-1)*c,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      
      wsprintf(ws, "-");
      DrwStr(ws,5+font_size,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws, ":");
      DrwStr(ws,5+font_size*4,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
    }break; 
    
    case 7:
    {
      //draw_pic(logo,2,2);
      
      menux();
      int c=font_size*1.5;

       ascii2ws(ws,rn,0); 
      
       if(call==0)  
       DrwStr(ws,5,6+tmp,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3)); 
       else
       DrwStr(ws,5,6+tmp,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
       if (calls[0]) 
        draw_pic(wd_on,a,6+tmp);
          else draw_pic(wd_off,a,6+tmp);

      for(int i=1;i<5;i++)  
      {  
      wsprintf(ws, "%02d",calls[i]);
      
      if (call==i)
        DrwStr(ws,5+(i-1)*c,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,5+(i-1)*c,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      
      wsprintf(ws, "-");
      DrwStr(ws,5+font_size,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws, ":");
      DrwStr(ws,5+font_size*4,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
    }break; 
    
    case 8:
    {
      //draw_pic(logo,2,2);
      menux();
      int c=font_size*1.5;

       ascii2ws(ws,rn,0); 
      
       if(sms==0)  
       DrwStr(ws,5,6+tmp,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3)); 
       else
       DrwStr(ws,5,6+tmp,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
       if (smss[0]) 
        draw_pic(wd_on,a,6+tmp);
          else draw_pic(wd_off,a,6+tmp);

      for(int i=1;i<5;i++)  
      {  
      wsprintf(ws, "%02d",smss[i]);
      
      if (sms==i)
        DrwStr(ws,5+(i-1)*c,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,5+(i-1)*c,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      
      wsprintf(ws, "-");
      DrwStr(ws,5+font_size,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      wsprintf(ws, ":");
      DrwStr(ws,5+font_size*4,6+tmp*2,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
    }break; 
    
    
  case 9:
    {
      //draw_pic(logo,2,2);
      menux();
      for (int i=0;i<8;i++)
      {
        ascii2ws(ws,othern[i],0);
        if (onum==i&&i<4) 
        DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,5,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        if(i<4)
        {
        if (other[i]) draw_pic(wd_on,a,6+tmp*(i+1));
          else draw_pic(wd_off,a,6+tmp*(i+1));
        }
        else
        {
        wsprintf(ws, "%02d",other[i]);
        if(onum==i)
        DrwStr(ws,a,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,a,6+tmp*(i+1),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        }
      }

    } break; 
    
    
  case 12:
    {
      DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
      draw_pic(fon,0,0);
      draw_pic(logo,2,2);

      GetDateTime(0,&time);
      wsprintf(ws,"%02d:%02d",time.hour,time.min);
      DrwStr(ws,a-font_size,4,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      ascii2ws(ws,Alarm_name[num_alarm],0);
      DrwStr(ws,30,3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

      if(status[num_alarm]==1) draw_pic(st_on,scr_w/2-25,HeaderH());
        else draw_pic(st_off,scr_w/2-25,HeaderH());

      if ((edit_level==1)||(edit_level==3))
        {
          ascii2ws(ws,change,0);
          DrwStr(ws,18,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        }
      
      ascii2ws(ws, ok,0);
      DrwStr(ws,scr_w/1.5,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      int x=scr_w/2-font_size*0.5;
      if (status[num_alarm]) ascii2ws(ws, on,0);
          else 
          {
            ascii2ws(ws, off,0);
            x-=3;
          }

      if (edit_level==1) DrwStr(ws,x,HeaderH()+57,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,x,HeaderH()+57,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

      x=scr_w/2-GetSymbolWidth((backup[1]/10)+'0',FONT_SMALL)-GetSymbolWidth((backup[1]%10)+'0',FONT_SMALL);      
        int b=HeaderH()+60+font_size;
      wsprintf(ws, "%02d",hour[num_alarm]);
      if ((edit_level==2)&&(set==1))
        DrwStr(ws,x,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,x,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        
      x=scr_w/2;
      wsprintf(ws, ":");
      DrwStr(ws,x,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      
      x+=GetSymbolWidth(':',FONT_SMALL);
      wsprintf(ws, "%02d",min[num_alarm]);
      if ((edit_level==2)&&(set==2))
        DrwStr(ws,x,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,x,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

      x=scr_w/7.3;
      b=scr_h-SoftkeyH()-font_size-24;
      for (int i=0;i<7;i++)
      {
        ascii2ws(ws, wd[i],0);
        if ((edit_level==3)&&(set==i)) DrwStr(ws,4+x*i,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,4+x*i,b,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
      }
      b+=(font_size+3);
      for (int i=0;i<7;i++)
      {
        if (weekdays[num_alarm][i]) draw_pic(wd_on,5+x*i,b);
          else draw_pic(wd_off,5+x*i,b);
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
      
      if (show_icon) ascii2ws(ws, on,0);
        else ascii2ws(ws, off,0);
      DrwStr(ws,8,scr_h-font_size-3,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
    } break;  
    
    
  case 15:
    {
     // draw_pic(logo,2,2);
      menux();
      
      ascii2ws(ws,minx,0);
      DrwStr(ws,5,HeaderH(),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

      wsprintf(ws, "%02d",min[6]);
      if (edit_level==1) 
        DrwStr(ws,a,HeaderH(),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
          else DrwStr(ws,a,HeaderH(),scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
        
      int x=scr_w/4;     
      int b=HeaderH()+font_size+4;
      int c=(ScreenH()-HeaderH()-SoftkeyH()-font_size)/6;
      
      for(int i=0;i<dats;i++)  
      {
      wsprintf(ws, "%02d-%01d",i,day[seven][i]);
      int j=i/4;
      if ((edit_level==2)&&(dat==i))
        DrwStr(ws,4+(i-4*j)*x,b+j*c,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(3));
        else DrwStr(ws,4+(i-4*j)*x,b+j*c,scr_w,scr_h,FONT_SMALL,1,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
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

void open_bcfg(char *x)
{
  WSHDR *_elf=AllocWS(256);
  wsprintf(_elf,"%s",x);
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
            case ENTER_BUTTON: menuselect(); OnRedraw(); break;
            case LEFT_SOFT: 
              if (name2[num]==1) name2[num]=0; else name2[num]=1;
            OnRedraw();break;
            case RIGHT_SOFT:
              {
                save_settings();
                GBS_SendMessage(MMI_CEPID, MSG_RECONFIGURE_REQ,0,"smartalerts");
                return(1);
              }
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
                if (menu>0) menu--;
                  else menu=(menus-1);
                if (num>0) num--;
                  else num=(menus-1);
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
                if (menu<(menus-1)) menu++;
                  else menu=0;
                if (num<(menus-1)) num++;
                  else num=0;
                  break;
              }
            
            case GREEN_BUTTON: open_bcfg(bcfgfile1); break;
            case '0':open_bcfg(ring);  break;
           /*  
            case '1': break;
            case '2': break;
            case '3': break;
            case '4': break;
            case '5': break;
    
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
            case GREEN_BUTTON: open_bcfg(bcfgfile); break;
            case '1': num_alarm=0; break;
            case '2': num_alarm=1; break;
            case '3': num_alarm=2; break;
            case '4': num_alarm=3; break;
            case '5': num_alarm=4; break;
            //case '6': num_alarm=5; break;
            case '#': mode=13; OnRedraw(); break;
            case '0':open_bcfg(ring);  break;
            //case '*': saveeeblock(); break;
            //case '*': ShowMSG(1,(int)"Alarm cfg editor\n(c)Geka"); break;
            }
          }
      } break;
      
    case 2:
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
            case LEFT_SOFT: 
            if(amenu<3)
            {
                if (amenus[amenu]==1) amenus[amenu]=0; else amenus[amenu]=1;}
                OnRedraw(); break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: open_bcfg(bcfgfile1); break;
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (amenu>0) amenu--;
                else amenu=10-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (amenu<(10-1)) amenu++;
                else amenu=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(amenu>2)
          {
               set=2;  
               if ((backup[set]<3&&(amenu==3||amenu==4))||(backup[set]<6&&amenu==5)||(backup[set]<10&&amenu==6)||(backup[set]<6&&amenu==7)||(backup[set]<10&&amenu==8)||(backup[set]<1&&amenu==9))
               backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                }
               ch[10]=1;
               input=1;
               edit();
               }
          }
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
            case LEFT_SOFT:  
                if(seven==7)
                {
                if (other[8]==1) other[8]=0; else other[8]=1;
		}
              else
              mode=15; OnRedraw(); break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            //case GREEN_BUTTON: open_bcfg(bcfgfile1); break;
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
      
     case 4:
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
            case LEFT_SOFT: 
                if(mmenu<2)
                {
                if (miss[mmenu]==1) miss[mmenu]=0; else miss[mmenu]=1;
			    }
                OnRedraw(); break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: open_bcfg(bcfgfile1); break;

            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (mmenu>0) mmenu--;
                else mmenu=6-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (mmenu<(6-1)) mmenu++;
                else mmenu=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(mmenu>1)
          {
               set=2;  
               if ((backup[set]<3&&(mmenu==2||mmenu==3))||(backup[set]<10&&mmenu==4)||(backup[set]<2&&mmenu==5)) backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                }
               ch[6]=1;
               input=1;
               edit();
               }
            }
            }
          }
      } break;    
      
      
     case 5:
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
            case LEFT_SOFT: 
                if(bmenu==0)
                {
                if (bmenus[0]==1) bmenus[0]=0; else bmenus[0]=1;
			    }
                OnRedraw(); break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: open_bcfg(bcfgfile1); break;

            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (bmenu>0) bmenu--;
                else bmenu=4-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (bmenu<(4-1)) bmenu++;
                else bmenu=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(bmenu!=0)
          {
               set=2;  
               if ((backup[set]<2&&bmenu==3)||(backup[set]<10&&bmenu==1)||(backup[set]<10&&bmenu==2)) backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                }
               ch[5]=1;
               input=1;
               edit();
               }
            }
            }
          }
      } break;   
      
     case 6:
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
            case LEFT_SOFT: 
                if(file==0)
                {
                if (files[0]==1) files[0]=0; else files[0]=1;
			    }
                OnRedraw(); break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: open_bcfg(bcfgfile1); break;

            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (file>0) file--;
                else file=5-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (file<(5-1)) file++;
                else file=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(file!=0)
          {
               set=2;  
               if ((backup[set]<2&&file==1)||(backup[set]<4&&file==2)||(backup[set]<3&&file==3)||(backup[set]<6&&file==4)) backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                }
               ch[7]=1;
               input=1;
               edit();
               }
            }
            }
          }
      } break;   
      
     case 7:
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
            case LEFT_SOFT: 
                if(call==0)
                {
                if (calls[0]==1) calls[0]=0; else calls[0]=1;
			    }
                OnRedraw(); break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: open_bcfg(bcfgfile1); break;

            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (call>0) call--;
                else call=5-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (call<(5-1)) call++;
                else call=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(call!=0)
          {
               set=2;  
               if ((backup[set]<2&&call==1)||(backup[set]<4&&call==2)||(backup[set]<3&&call==3)||(backup[set]<6&&call==4)) backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                }
               ch[8]=1;
               input=1;
               edit();
               }
            }
            }
          }
      } break;  
      
     case 8:
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
            case LEFT_SOFT: 
                if(sms==0)
                {
                if (smss[0]==1) smss[0]=0; else smss[0]=1;
			    }
                OnRedraw(); break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: open_bcfg(bcfgfile1); break;

            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (sms>0) sms--;
                else sms=5-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (sms<(5-1)) sms++;
                else sms=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(sms!=0)
          {
               set=2;  
               if ((backup[set]<2&&sms==1)||(backup[set]<4&&sms==2)||(backup[set]<3&&sms==3)||(backup[set]<6&&sms==4)) 
                 backup[set]=backup[set]*10+keycode-'0';
                else
                {
                  backup[set]=keycode-'0';
                }
               ch[9]=1;
               input=1;
               edit();
               }
            }
            }
          }
      } break;  
      
    case 9:
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
            case LEFT_SOFT: 
            if(onum<4)
            {
                if (other[onum]==1) other[onum]=0; else other[onum]=1;}
                OnRedraw(); break;
            case RIGHT_SOFT: mode=0; OnRedraw(); break;
            case GREEN_BUTTON: open_bcfg(bcfgfile1); break;
            case UP_BUTTON:
            case LEFT_BUTTON:
              {
              if (onum>0) onum--;
                else onum=8-1;      
                break;
              }
            case RIGHT_BUTTON:
            case DOWN_BUTTON:
              {
              if (onum<(8-1)) onum++;
                else onum=0;     
                  break;
              }
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          {
          if(onum>3)
          {
               set=2;  
               if (backup[set]<2&&(onum==4||onum==5)||(backup[set]<10&&onum==6)||(backup[set]<10&&onum==7)) 
               backup[set]=backup[set]*10+keycode-'0';
                else
                  backup[set]=keycode-'0';
               ch[11]=1;
               input=1;
               edit();
               }
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
                }
               ch[4]=1;
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
  free_font_lib();
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"SA cfg editor");
  FreeWS(ws);
}

int main(void)
{
  init_font_lib();
  InitConfig();
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
