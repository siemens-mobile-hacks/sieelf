#include "..\..\inc\swilib.h"
#include "..\..\inc\cfg_items.h"
#include "conf_loader.h"
#include "SmartAlerts.h"
#include "extern.h"

#define TMR_SECOND 216

#ifdef NEWSGOLD
#ifdef S68
#define DEFAULT_DISK "0"
#else
#define DEFAULT_DISK "4"
#endif
#else
#define DEFAULT_DISK "0"
#endif


GBSTMR *xtmr;

unsigned int files[5];
unsigned int smss[5];
unsigned int calls[5];
unsigned int anemus[11];
unsigned int miss[6];
unsigned int bnemus[4];

unsigned int hour[5];
unsigned int min[7];
unsigned int status[5];
unsigned int weekdays[5][7];
unsigned int day[7][24];
unsigned int other[9];
unsigned int name2[9];
int show_icon=0;
int status_icon=0;
int X;
int Y;
int imgw;
int imgh;


TDate date; 
TTime time; 
TDate week;
GBSTMR mytmr;
GBSTMR tmr_vibra;

WSHDR* ws;

int count;
int fb=0;
volatile int _count;


char icon[]=DEFAULT_DISK":\\Zbin\\img\\SmartAlerts\\icon.png";
char cfgfile[]=DEFAULT_DISK":\\Zbin\\img\\SmartAlerts\\SmartAlerts.cfg";
char sound[]=DEFAULT_DISK ":\\ZBin\\img\\SmartAlerts\\alerts\\";

void getimgwh()
{
  imgw=GetImgWidth((int)icon);
  imgh=GetImgHeight((int)icon);
}


void update_status()
{
  if (status[0] || status[1] || status[2] || status[3] || status[4])
  {
    status_icon=1;
  }
   else status_icon=0;
}

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

min[6]=data[230];

name2[0]=data[231];
name2[1]=data[232];
name2[2]=data[233];
name2[3]=data[234];
name2[4]=data[235];
name2[5]=data[236];
name2[6]=data[237];
name2[7]=data[238];
name2[8]=data[239];

other[0]=data[240];
other[1]=data[241];
other[2]=data[242];
other[3]=data[243];

other[4]=data[244];
other[5]=data[245];
other[6]=data[246];
other[7]=data[247];

bnemus[0]=data[248];
bnemus[1]=data[249];
bnemus[2]=data[250];
bnemus[3]=data[251];

miss[0]=data[252];
miss[1]=data[253];
miss[2]=data[254];
miss[3]=data[255];
miss[4]=data[256];
miss[5]=data[257];


files[0]=data[258];
files[1]=data[259];
files[2]=data[260];
files[3]=data[261];
files[4]=data[262];

calls[0]=data[263];
calls[1]=data[264];
calls[2]=data[265];
calls[3]=data[266];
calls[4]=data[267];

smss[0]=data[268];
smss[1]=data[269];
smss[2]=data[270];
smss[3]=data[271];
smss[4]=data[272];

anemus[0]=data[273];
anemus[1]=data[274];
anemus[2]=data[275];
anemus[3]=data[276];
anemus[4]=data[277];
anemus[5]=data[278];
anemus[6]=data[279];
anemus[7]=data[280];
anemus[8]=data[281];
anemus[9]=data[282];
anemus[10]=data[283];

other[8]=data[284];

    mfree(data);
    fclose(handle,&err);
  }
  getimgwh();
  update_status();
}

void start_ring()
{
  char elf[]=DEFAULT_DISK":\\Zbin\\img\\SmartAlerts\\alarm_ring.elf";
  WSHDR *ws;
  ws=AllocWS(64);
  str_2ws(ws,elf,strlen(elf)+1);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}


int runFile(char *file) 
{
  if(file)
  {
    if (strlen(file))
    {
      WSHDR *ws;
      ws=AllocWS(64);
      str_2ws(ws, file, 64);
      ExecuteFile(ws, 0, 0);
      FreeWS(ws);
      return 1;
    }
  }
  return 0;
}

void Play(const char *fpath, const char *fname)
{
  WSHDR* sndPath=AllocWS(64);
  WSHDR* sndFName=AllocWS(64);

  wsprintf(sndPath, fpath);
  wsprintf(sndFName, fname);
  
    if(fpath==0)
    {
    FSTATS fstats;
    unsigned int err; 
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      char s[64];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,64);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,64);
    }
    }

    PLAYFILE_OPT _sfo1;
    zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
    _sfo1.repeat_num=1;
    _sfo1.time_between_play=0;
    _sfo1.play_first=0;
    _sfo1.volume=other[4];
#ifdef NEWSGOLD
    _sfo1.unk6=1;
    _sfo1.unk7=1;
    _sfo1.unk9=2;
    PlayFile(0x10, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
    _sfo1.unk4=0x80000000;
    _sfo1.unk5=1;
    PlayFile(0xC, sndPath, sndFName, 0, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
    _sfo1.unk5=1;
    PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif 
    
  FreeWS(sndPath);
  FreeWS(sndFName);
}



void start_(void)
{
  if(name2[8])
  {
  void stop_(void);
  if(!name2[4]||!bnemus[0]||(*RamCap()<bnemus[1]))
  {
  	if (other[1])
		SetIllumination(0, 1, other[7]+1, 0);
	if (other[2])
		SetIllumination(1, 1, other[7]+1, 0);   
#ifndef NEWSGOLD
	if (other[3])
		SetIllumination(2, 1, other[7]+1, 0);
#else
	if (other[3])
		SetIllumination(4, 1, other[7]+1, 0);
#endif
  
  if (other[0]) SetVibration(other[6]);
  }
  GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,stop_);
  }
}

void stop_(void)
{
  if(name2[8])
  {
  	if (other[1])
		SetIllumination(0, 1, 0, 0);
	if (other[2])
		SetIllumination(1, 1, 0, 0);   
#ifndef NEWSGOLD
	if (other[3])
		SetIllumination(2, 1, 0, 0);
#else
	if (other[3])
		SetIllumination(4, 1, 0, 0);
#endif
  
  if (other[0]) SetVibration(0);

  if (--_count)
  {
    GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,start_);
  }
  }
}

void alarm(int n)
{
  if (status[n])
  {
    TDate date;
    GetDateTime(&date, 0);
    char wd = GetWeek(&date);
    if (weekdays[n][wd])
      {
        GetDateTime(&date,&time);
        if (time.hour==hour[n])
          {
            if (time.min==min[n])
              {
                start_ring();
              }
          }
      }
  }
}


void Check()
{
GetDateTime(&date,&time);
 if (!IsCalling())
 {
   
  if(name2[0])
  {
   for (int i=0;i<5;i++)
  {
    alarm(i);
  }
  }

   
   
   if(name2[1])
   {
     if ((time.hour>=anemus[3])&&(time.hour<=anemus[4]))
        {              
         if(time.min==anemus[5]&&!(name2[7]&&time.hour==smss[3]&&time.min==smss[4]))
	 { 
               if(anemus[1]&&((GetProfile()+1)!=anemus[9]))
               {
                   char w[5];
                   sprintf(w, "%d.%s",time.hour,mstyle);
                   Play(sound,w);
               }
               else if(anemus[0]&&((GetProfile()+1)!=anemus[9]))
               {
                   Play(0,vname);
               }
               else
               {
		   PlaySound(1,0,0,anemus[6],0);
               }
                   _count=other[5];
                   start_();
	  }
          else if(time.min==anemus[7]&&anemus[2])
	  { 
               PlaySound(1,0,0,anemus[8],0);
                  _count=other[5];
                  start_();
           }
        }
   }
        if(name2[5])
        {
          if(!files[0]||(date.month==files[1]&&date.day==files[2]))
          {
          if(time.hour==files[3]&&time.min==files[4])
           {
           runFile((char*)name1);
           }
          }
        }
        
        if(name2[6])
        {
          if(!calls[0]||(date.month==calls[1]&&date.day==calls[2]))
          {
	  if(time.hour==calls[3]&&time.min==calls[4])
           {
            if(strlen(callnum)>5)
            MakeVoiceCall(callnum,0x10,0x2FFF);
           }
          }
        }
        
        if(name2[7])
        {
         if(!smss[0]||(date.month==smss[1]&&date.day==smss[2]))
          {
	  if(time.hour==smss[3]&&time.min==smss[4])
          {
                utf8_2ws(ws,content,210);
                if(strlen(smsnum)>5)
                SendSMS(ws,smsnum,MMI_CEPID,MSG_SMS_RX-1, 6);
          }
          }
        }  
     
        if (name2[4])
        {
           if (*RamCap()==100&&fb!=bnemus[3])
           {
           PlaySound(1,0,0,bnemus[2],0);
           fb++;
           }
           else if(*RamCap()!=100)
                fb=0;
        }
        
        if(name2[3])
        {
          if ((time.hour>=miss[2])&&(time.hour<=miss[3]))
          {
          if(time.min%miss[5]==0)
          {
          #ifdef NEWSGOLD          
	    if (GetMissedEventCount(0) > 0)
          #else
            if (GetMissedCallsCount()||HasNewSMS()) 
          #endif
          {
            if(!miss[0])
            {
             if(miss[1])
              Play(0,mname); 
             else
             PlaySound(1,0,0,miss[4],0);
            }
             _count=other[5];
             start_();
          }
          }
          }
        }

     
 }
 if(name2[2])
 {
  if(time.min==min[6])
  {
   int a1,a2;
   if(GetWeek(&date)<5&&other[8])
   a1=0;
   else
   a1=GetWeek(&date);
   
   a2=time.hour;
   if(day[a1][a2]<9&&day[a1][a2]!=0)
     SetProfile(day[a1][a2]-1);
  }
 }

GBS_StartTimerProc(&mytmr,216*60,Check);
}



void start()
{ 
GBS_StartTimerProc(&mytmr,216*60,Check); 
} 

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

int IDLECSM_ID=-1;

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
      
    }

    if (strcmp_nocase("smartalerts",(char *)msg->data0)==0)
    {
      load_settings();
    }

  }

  if (msg->msg == MSG_IPC)
  {
    IPC_REQ *ipc=(IPC_REQ*)((msg)->data0);
    if (ipc)
    {
      if (strcmp_nocase("smartalerts",(char *)ipc->name_to)==0)
      {
         int time2 =msg->submess;
        GBS_StartTimerProc(&xtmr,216*60*time2,start_ring);
      }
    }
  }

  
  CSM_RAM *icsm;
  if ((icsm=FindCSMbyID(CSM_root()->idle_id)))
  {
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    if (IsGuiOnTop(idlegui_id))
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
#ifdef ELKA
        {
          void *canvasdata = BuildCanvas();
#else
          void *idata = GetDataOfItemByID(igui, 2);
          if (idata)
          {
            void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
          if((IsUnlocked())&&(show_icon)&&(status_icon))
          {
            DrawCanvas(canvasdata, X, Y, X + imgh, Y + imgh, 1);
            DrawImg(X, Y, (int)icon);
          }
        }
      }
    }
  }
  
  return(1);
}  

static void maincsm_oncreate(CSM_RAM *data)
{
  start();
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  GBS_DelTimer(&tmr_vibra);
  GBS_DelTimer(xtmr);
  FreeWS(ws);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr()); 
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM_d =
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM_d.maincsm_name),"smartalerts");
}

int main()
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig(); 
  load_settings();
  UpdateCSMname();
  ws=AllocWS(210);
  LockSched(); 
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM_d.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();

  return 0;
}
