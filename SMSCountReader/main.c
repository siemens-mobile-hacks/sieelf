#include "..\inc\swilib.h"

/*****************************************************************************
00000000h: 0B 00 00 00 4E 00 00 00 42 00 00 00 00 00 00 00 ; ....N...B.......
00000010h: 0C 00 00 00                                     ; ....
*****************************************************************************/

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;

extern void kill_data(void *p, void (*func_p)(void *));

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
int screenw;
int screenh;
char* data_buf;

#pragma inline
int get_string_width(WSHDR *ws, int font)
{
  int width=0;
  unsigned short *body=ws->wsbody;
  int len=body[0];
  while(len)
  {
    width+=GetSymbolWidth(body[len],font);
    len--;
  }
  return (width);
}

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
	rc->x=x;
	rc->y=y;
	rc->x2=x2;
	rc->y2=y2;
}

void exit(void)
{
	CloseCSM(MAINCSM_ID);
}

int get_initday(void)
{
  unsigned int err;
  int f;
  char bcfgpath[]="0:\\ZBin\\etc\\SMSCount.bcfg";
  if((f=fopen(bcfgpath,A_ReadOnly+A_BIN,P_READ,&err))==-1)
  {
  	bcfgpath[0]='4';
  	if((f=fopen(bcfgpath,A_ReadOnly+A_BIN,P_READ,&err))==-1)
  	{
  		MsgBoxError(1, (int)"Can't find SMSCount.bcfg!\nDefault initday: 1");
  		return 1;
  	}
  }
  char *initday=malloc(8);
  lseek(f,44,0,&err,&err);
  fread(f,initday,4,&err);
  fclose(f,&err);
  mfree(initday);
  return initday[0];
}


void load_dat(void)
{
	unsigned int err;
	int f;
	if((f=fopen("2:\\SMSCount.dat",A_ReadOnly+A_BIN,P_READ,&err))==-1)
  {
  	if((f=fopen("2:\\SMSCount\\SMSCount.dat",A_ReadOnly+A_BIN,P_READ,&err))==-1)
    {
    	ShowMSG(1, (int)"Can't find SMSCount.dat");
    	exit();
    }
  }
  fread(f,data_buf,20,&err);
  fclose(f,&err);
}

void soft_key(void)
{
	char utf8_exit[]="\xE9\x80\x80\xE5\x87\xBA";//退出
  WSHDR *wsr = AllocWS(16);
  utf8_2ws(wsr,utf8_exit,strlen(utf8_exit));
  DrawString(wsr,screenw-get_string_width(wsr,FONT_MEDIUM)-4,screenh-GetFontYSIZE(FONT_MEDIUM)-2,screenw,screenh,FONT_MEDIUM,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  FreeWS(wsr);
}

void onRedraw(MAIN_GUI *data)
{
	int init_day=get_initday();
	int font_h=GetFontYSIZE(FONT_SMALL);
	DrawRectangle(0,YDISP,screenw,screenh,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
	soft_key();
	char *utf8_str=malloc(128);
	WSHDR *ws = AllocWS(128);
	wsprintf(ws, "SMSCount v3.6\nSMSCountReader v1.0\n");
	DrawString(ws,0,YDISP,screenw,screenh,FONT_SMALL,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
	//全部，移动，联通，其它
	sprintf(utf8_str,"\xE5\x85\xA8\xE9\x83\xA8: %d\n\xE7\xA7\xBB\xE5\x8A\xA8: %d\n\xE8\x81\x94\xE9\x80\x9A: %d\n\xE5\x85\xB6\xE4\xBB\x96: %d", data_buf[4], data_buf[8], data_buf[0xC], data_buf[0x10]);
	utf8_2ws(ws,utf8_str,strlen(utf8_str));
	DrawString(ws,0,YDISP+3*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
	//清零日期
  if(init_day==0)
  {
    sprintf(utf8_str,"\xE6\xB8\x85\xE9\x9B\xB6\xE6\x97\xA5\xE6\x9C\x9F: \xE4\xB8\x8D\xE6\xB8\x85\xE9\x9B\xB6");
  }
  else sprintf(utf8_str,"\xE6\xB8\x85\xE9\x9B\xB6\xE6\x97\xA5\xE6\x9C\x9F: %d",init_day);
	utf8_2ws(ws,utf8_str,strlen(utf8_str));
	DrawString(ws,0,YDISP+7*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 	
	//显示当前日期
	TTime tt;
  TDate td;
  GetDateTime(&td,&tt);
  sprintf(utf8_str,"\xE5\xBD\x93\xE5\x89\x8D\xE6\x97\xA5\xE6\x9C\x9F: %04d.%i.%i",td.year,td.month,td.day);
  utf8_2ws(ws,utf8_str,strlen(utf8_str));
  DrawString(ws,0,YDISP+8*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  
	mfree(utf8_str);
	FreeWS(ws);
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
	if(msg->gbsmsg->msg==KEY_UP)
	{
		if(msg->gbsmsg->submess==RIGHT_SOFT)
			exit();
			
	}
	return(0);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)onRedraw,	//Redraw
	(void *)onCreate,	//Create
	(void *)onClose,	//Close
	(void *)onFocus,	//Focus
	(void *)onUnfocus,	//Unfocus
	(void *)OnKey,		//OnKey
	0,
	(void *)kill_data,	//Destroy
	(void *)method8,
	(void *)method9,
	0
};

const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  screenw=ScreenW();
  screenh=ScreenH();
  data_buf=malloc(32);
  load_dat();
	MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM *csm=(MAIN_CSM *)data;
	zeromem(main_gui,sizeof(MAIN_GUI));	
	patch_rect((RECT*)&Canvas,0,0,screenw-1,screenh-1);
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();	
	
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  
  MAINGUI_ID=csm->gui_id;
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

void Killer(void)
{
  extern void *ELF_BEGIN;
  mfree(data_buf);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

const int minus11=-11;
unsigned short maincsm_name_body[140];

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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "SMSCountReader");
}

int main(char *initday)
{
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
