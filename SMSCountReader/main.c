#include "..\inc\swilib.h"

#define CP_MSG "SMSCountReader v1.6\n(C) 2008 BingK(binghelingxi)"

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
int is_editing=0;
int edit_line=1;
int screenw;
int screenh;
char dat_path[]="2:\\SMSCount.dat";
int f;

#define	COUNT_ALL 0
#define	COUNT_CHM 1
#define	COUNT_CHU 2
#define	COUNT_XLT 3
#define	COUNT_OTH 4
#define	TYPE_ALL  5
#define	BUF_LEN   (TYPE_ALL*sizeof(int))

int count[TYPE_ALL];

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
int load_dat(void)
{
	unsigned int err;
	if((f=fopen(dat_path, A_ReadWrite+A_BIN, P_READ+P_WRITE, &err))!=-1)
	{
		fread(f, count, BUF_LEN, &err);
		lseek(f, 0, S_SET, &err, &err);
	}
	else if((f=fopen(dat_path, A_ReadWrite+A_Create+A_Truncate, P_READ+P_WRITE, &err))==-1)
		return -1;
	return 1;
}

void save_dat(int type)
{
	unsigned int err;
	if(type==1)
	{
		int i;
		for(i=0; i<TYPE_ALL; i++)
			count[i]=0;
	}
	if(fwrite(f, count, BUF_LEN, &err)!=BUF_LEN)
		MsgBoxError(1,(int)"Save Error");
	is_editing=0;
}
void clearProc(int id)
{
  if(id==0)
  	save_dat(1);
}

void saveProc(int id)
{
  if(id==0)
    save_dat(0);
}

void exit(void)
{
	if(is_editing)
	{
		MsgBoxYesNo(1, (int)"Is Editing, Save First?", saveProc);
	}
	else
		CloseCSM(MAINCSM_ID);
}


void soft_key(void)
{
  char utf8_clear[]="\xE6\xB8\x85\xE7\xA9\xBA\xE8\xAE\xA1\xE6\x95\xB0";//清空计数
  char utf8_exit[]="\xE9\x80\x80\xE5\x87\xBA";//退出
  WSHDR *wsl=AllocWS(16);
  WSHDR *wsr=AllocWS(16);
  utf8_2ws(wsr,utf8_exit,strlen(utf8_exit));
  utf8_2ws(wsl,utf8_clear,strlen(utf8_clear));
  DrawString(wsr,screenw-get_string_width(wsr,FONT_MEDIUM)-4,screenh-GetFontYSIZE(FONT_MEDIUM)-2,screenw,screenh,FONT_MEDIUM,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  DrawString(wsl,2,screenh-GetFontYSIZE(FONT_MEDIUM)-2,screenw,screenh,FONT_MEDIUM,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  FreeWS(wsr);
  FreeWS(wsl);
}

void onRedraw(MAIN_GUI *data)
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  int color_index=0;
	//int init_day;
	//if(no_bcfg) init_day=1;
	//  else init_day=get_initday();
	int font_h=GetFontYSIZE(FONT_SMALL);
	DrawRectangle(0,0,screenw,screenh,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
	soft_key();
	char *utf8_str=malloc(128);
	WSHDR *ws = AllocWS(128);
	wsprintf(ws, "SMSCount v3.7.1\nSMSCountReader v1.6\n");
	DrawString(ws,0,0,screenw,screenh,FONT_SMALL,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
	//全部
	sprintf(utf8_str,"\xE5\x85\xA8\xE9\x83\xA8: %d", count[0]);
	utf8_2ws(ws,utf8_str,strlen(utf8_str));
	DrawString(ws,0,3*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
	//移动
	sprintf(utf8_str,"\xE7\xA7\xBB\xE5\x8A\xA8: %d", count[1]);
	utf8_2ws(ws,utf8_str,strlen(utf8_str));
	if(is_editing)
	{
	  if(edit_line==1)
	    color_index=2;
	  else color_index=0;
	}
	else color_index=0;
	DrawString(ws,0,4*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(color_index),GetPaletteAdrByColorIndex(23)); 
	//联通
	sprintf(utf8_str,"\xE8\x81\x94\xE9\x80\x9A: %d", count[2]);
	utf8_2ws(ws,utf8_str,strlen(utf8_str));
	if(is_editing)
	{
	  if(edit_line==2)
	    color_index=2;
	  else color_index=0;
	}
	else color_index=0;
	DrawString(ws,0,5*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(color_index),GetPaletteAdrByColorIndex(23)); 
	//小灵通
	sprintf(utf8_str,"\xE5\xB0\x8F\xE7\x81\xB5\xE9\x80\x9A: %d", count[3]);
	utf8_2ws(ws,utf8_str,strlen(utf8_str));
	if(is_editing)
	{
	  if(edit_line==3)
	    color_index=2;
	  else color_index=0;
	}
	else color_index=0;
	DrawString(ws,0,6*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(color_index),GetPaletteAdrByColorIndex(23)); 
	//其它
	sprintf(utf8_str,"\xE5\x85\xB6\xE4\xBB\x96: %d", count[4]);
	utf8_2ws(ws,utf8_str,strlen(utf8_str));
	if(is_editing)
	{
	  if(edit_line==4)
	    color_index=2;
	  else color_index=0;
	}
	else color_index=0;
	DrawString(ws,0,7*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(color_index),GetPaletteAdrByColorIndex(23)); 
	//清零日期
  //if(init_day==0)
  //{
  //  sprintf(utf8_str,"\xE6\xB8\x85\xE9\x9B\xB6\xE6\x97\xA5\xE6\x9C\x9F: \xE4\xB8\x8D\xE6\xB8\x85\xE9\x9B\xB6");
  //}
  //else sprintf(utf8_str,"\xE6\xB8\x85\xE9\x9B\xB6\xE6\x97\xA5\xE6\x9C\x9F: \xE6\xAF\x8F\xE6\x9C\x88%d\xE6\x97\xA5",init_day);
//	utf8_2ws(ws,utf8_str,strlen(utf8_str));
//	DrawString(ws,0,8*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 	
	//显示当前日期
	TTime tt;
	TDate td;
	GetDateTime(&td,&tt);
	sprintf(utf8_str,"\xE5\xBD\x93\xE5\x89\x8D\xE6\x97\xA5\xE6\x9C\x9F: %04d.%i.%i",td.year,td.month,td.day);
	utf8_2ws(ws,utf8_str,strlen(utf8_str));
	DrawString(ws,0,9*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
	//正在编辑 
	if(is_editing)
	{
		sprintf(utf8_str,"\xE7\xBC\x96\xE8\xBE\x91\xE4\xB8\xAD\xE3\x80\x82\xE3\x80\x82\xE3\x80\x82\n\xE8\xAF\xB7\xE6\x8C\x89\xE7\xBB\xBF\xE9\x94\xAE\xE4\xBF\x9D\xE5\xAD\x98");
		utf8_2ws(ws,utf8_str,strlen(utf8_str));
		DrawString(ws,0,10*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(7),GetPaletteAdrByColorIndex(23)); 
	}
	else //提示按中键编辑
  	{
  		sprintf(utf8_str,"\xE6\x8C\x89\xE4\xB8\xAD\xE9\x94\xAE\xE5\xBC\x80\xE5\xA7\x8B\xE4\xBF\xAE\xE6\x94\xB9\xE6\x95\xB0\xE6\x8D\xAE");
		utf8_2ws(ws,utf8_str,strlen(utf8_str));
		DrawString(ws,0,10*font_h,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(7),GetPaletteAdrByColorIndex(23)); 
	}
  
	mfree(utf8_str);
	FreeWS(ws);
}

void show_about(void)
{
	ShowMSG(1, (int)CP_MSG);
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
	if(msg->gbsmsg->msg==KEY_UP)
	{
	  int i=msg->gbsmsg->submess;
	  switch(i)
	  {
	    case RIGHT_SOFT: 
	      exit();
	      break;
	    case LEFT_SOFT:
	      MsgBoxYesNo(1, (int)"Clear ALL?", clearProc);
	      REDRAW();
	      break;
	    case ENTER_BUTTON:
	      is_editing=1;
	      REDRAW();
	      break;
	    case DOWN_BUTTON:
	    	if(is_editing)
	    	{
	      if(edit_line!=4) 
	        edit_line++;
	      else edit_line=1;
	      	}
	      REDRAW();
	      break;
	    case UP_BUTTON:
	    	if(is_editing)
	    	{
	      if(edit_line!=1)
	        edit_line--;
	      else edit_line=4;
		}
	      REDRAW();
	      break;
	    case LEFT_BUTTON:
	    	if(is_editing)
	    	{
	      if(count[edit_line])
	      {
	        count[0]--;
	        count[edit_line]--;
	      }
		}
	      REDRAW();
	      break;
	    case RIGHT_BUTTON:
	    	if(is_editing)
	    	{
	        count[0]++;
	        count[edit_line]++;
		}
	      REDRAW();
	      break;
	    case GREEN_BUTTON:
	      if(is_editing) MsgBoxYesNo(1, (int)"Save All Change?", saveProc);
	      REDRAW();
	      break;
	     case '*':
	     	show_about();
	     	break; 
	  }
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
  DisableIDLETMR();
  data->gui.state=2;
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
	screenw=ScreenW()-1;
	screenh=ScreenH()-1;
	int i;
	for(i=0; i<TYPE_ALL; i++)
		count[i]=0;
	if(load_dat()<0)
		ShowMSG(1, (int)"Load SMSCount.dat failed");
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
  unsigned int err;
  fclose(f, &err);
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
