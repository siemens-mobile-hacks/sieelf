#include "..\inc\swilib.h"
#include "..\inc\playsound.h" 
#include "conf_loader.h"
#include "rect_patcher.h"
#include "filelist.h"
#include "play_list.h"
#include "lang.h"

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
extern const char *successed_config_filename;

//config
extern const RECT name_pos;
extern const unsigned int name_font;
extern const char name_col[4];
extern const char frame_col[4];
extern const char gui_main_bg_col[4];
extern const unsigned int gui_name_x;
extern const unsigned int gui_name_y;
extern const unsigned int gui_name_font;
extern const char gui_name_col[4];
extern const char gui_frame_col[4];
extern const unsigned int gui_sta_x;
extern const unsigned int gui_sta_y;
extern const unsigned int gui_sta_font;
extern const char gui_sta_col[4];
extern const char gui_sta_frame_col[4];
extern const unsigned int sk_font;
extern const char sk_col[4];
extern const unsigned int defau_vol;


unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
int screenw;
int screenh;
int playhandle=0;
int play_flag=0;//0:stop, 1:paly, 2:pause
char procfile[128];
char song_name[128];
unsigned int sndVolume=6;
//int is_new_file_selected=0;
WSHDR *ws_idle_name;


void exit(void)
{
  if(playhandle) PlayMelody_StopPlayback(playhandle);
	CloseCSM(MAINCSM_ID);
}


void Play(const char *fname)
{
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      PLAYFILE_OPT _sfo1;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);
      
      zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num=1;
      _sfo1.time_between_play=0;
      _sfo1.play_first=0;
      _sfo1.volume=sndVolume;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      playhandle=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      playhandle=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      playhandle=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
    else ShowMSG(1,(int)"FFF");//������
}



const int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_skm[]=
{
  {0x0018,0x0000,(int)LGP_SELECT},
  {0x0001,0x0000,(int)LGP_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};


SOFTKEYSTAB menu_sktm=
{
  menu_skm,0
};


#define ITEMS_N 4

MENUITEM_DESC menu_items[ITEMS_N]=
{
  {NULL,(int)LGP_OPEN,          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_OPTIONS,       LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_ABOUT,         LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_EXIT,          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

void control(int type);
void menu_open(GUI *data) 
{
  open_select_file_gui(1);
  GeneralFuncF1(1);

}

void menu_options(GUI *data)
{
  WSHDR *ws;
  ws=AllocWS(128);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
}

void menu_about(GUI *data) 
{
  ShowMSG(1, (int)COPYRIGHT);
  GeneralFuncF1(1);
}

void menu_exit(GUI *data)
{
  exit();
}


const MENUPROCS_DESC menu_hndls[ITEMS_N]=
{
  menu_open,
  menu_options,
  menu_about,
  menu_exit,
};


HEADER_DESC mm_menuhdr={0,0,0,0,NULL,(int)ELF_NAME,LGP_NULL};

const MENU_DESC mm_menu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_sktm,
  0,
  NULL,
  menu_items,   //Items
  menu_hndls,   //Procs
  ITEMS_N   //n
};

void create_main_menu(void)
{
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&mm_menu,&mm_menuhdr,0,ITEMS_N,0,0);
}


void soft_key(void)
{
	WSHDR *wsl = AllocWS(16);
  WSHDR *wsr = AllocWS(16);
  utf8_2ws(wsr,LNG_STOP,strlen(LNG_STOP));
  utf8_2ws(wsl,LNG_MENU,strlen(LNG_MENU));
  DrawString(wsr,screenw-get_string_width(wsr,sk_font)-4,screenh-GetFontYSIZE(sk_font)-2,screenw,screenh,sk_font,32,sk_col,GetPaletteAdrByColorIndex(23)); 
  DrawString(wsl,2,screenh-GetFontYSIZE(sk_font)-2,screenw,screenh,sk_font,32,sk_col,GetPaletteAdrByColorIndex(23)); 
  FreeWS(wsr);
  FreeWS(wsl);
}


void onRedraw(MAIN_GUI *data)
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  DrawRectangle(0,0,screenw,screenh,0,gui_main_bg_col,gui_main_bg_col);
  soft_key();
  //������
  WSHDR *ws_song_name=AllocWS(64);
  const char *p=strrchr(procfile,'\\')+1;
  str_2ws(ws_song_name,p,64);
  DrawString(ws_song_name,gui_name_x,gui_name_y,screenw,screenh,gui_name_font,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,gui_name_col,gui_frame_col); 
  FreeWS(ws_song_name);
  //����
  char *sta=malloc(64);
  WSHDR *ws_sta=AllocWS(64);
  //����//����״̬
  char c_sta[16];
  switch(play_flag)
  {
    case 0:
      sprintf(c_sta,LNG_STOP);//ֹͣ
      break;
    case 1:
      sprintf(c_sta,LNG_PLAYING);//���ڲ���
      break;
    case 2:
      sprintf(c_sta,LNG_PAUSE);//��ͣ
      break;
  }
  sprintf(sta,LNG_VOL": %d\n"LNG_STATUS": %s", sndVolume, c_sta);
  utf8_2ws(ws_sta,sta,strlen(sta));
  DrawString(ws_sta,gui_sta_x,gui_sta_y,screenw,screenh,gui_sta_font,TEXT_OUTLINE,gui_sta_col,gui_sta_frame_col); 
  mfree(sta);
  FreeWS(ws_sta);
}

void control(int type)
{
  //type 0:play, 1: Pause, 2:Resume, 3: Stop, 4:change vol
    switch(type)
    {
      case 0:
        if(playhandle&&(play_flag!=0)) PlayMelody_StopPlayback(playhandle);//ͣ�����ڲ��ŵĸ���
        if(play_flag!=0)
        {
          Play(procfile);
          play_flag=1;
        }
        break;
      case 1:
        if(playhandle) PlayMelody_PausePlayback(playhandle);
        play_flag=2;
        break;
      case 2:
        if(playhandle) PlayMelody_ResumePlayBack(playhandle);
        play_flag=1;
        break;
      case 3:
        if(playhandle) PlayMelody_StopPlayback(playhandle);
        play_flag=0;
        break;
      case 4:
        if(playhandle) PlayMelody_ChangeVolume(playhandle,sndVolume);
        break;
    }
}

void play_next(void)
{
	get_next_song();
	control(0);
}

void play_prev(void)
{
	get_prev_song();
	control(0);
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if(msg->gbsmsg->msg==KEY_UP)
  {
    int i=msg->gbsmsg->submess;
    switch(i)
    {
      case RIGHT_SOFT:
        control(3);
        REDRAW();
        break;
      case LEFT_SOFT:
        create_main_menu();
        //if(is_new_file_selected)
        //{
        //  control(0);
        //  is_new_file_selected=0;
        //}
        REDRAW();
        break;
      case ENTER_BUTTON:
      case '5':
        if(play_flag==0)
        {
          play_flag=1; //�ڲ����������£��ȸı����ֵ��ʹcontrol(0);����ִ��
          control(0);
          REDRAW();
          break;
        }
        if(play_flag==1)
        {
          control(1);
          REDRAW();
          break;
        }
        if(play_flag==2) control(2);
        REDRAW();
        break;
      case LEFT_BUTTON:
      case '4':
        if(sndVolume)
        {
          sndVolume--;
          control(4);
        }
        REDRAW();
        break;
      case RIGHT_BUTTON:
      case '6':
        if(sndVolume!=6)
        {
          sndVolume++;
          control(4);
        }
        REDRAW();
        break;
      case UP_BUTTON:
      case '2':
        play_prev();
        REDRAW();
        break;
      case DOWN_BUTTON:
      case '8':
        play_next();
        REDRAW();
        break;
      default: 
        REDRAW();
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


void add_ws_idle_name(void)
{
	const char *p=strrchr(procfile,'\\')+1;
  str_2ws(ws_idle_name,p,64);
}
const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  ws_idle_name=AllocWS(64);
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

#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  void *icsm;
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)ELF_NAME" config updated!");
      InitConfig();
    }
  }
  if((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if(msg->msg==MSG_PLAYFILE_REPORT) 
  {
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if (pmsg->handler==playhandle)
    {
      if (pmsg->cmd==M_SAE_PLAYBACK_ERROR || pmsg->cmd==M_SAE_PLAYBACK_DONE)
      {
        if(play_flag!=0) 
          play_next();
      }
    }
  }
  icsm=FindCSMbyID(CSM_root()->idle_id);
  if (icsm)
  {
    if (IsGuiOnTop(idlegui_id(icsm)))
    {
      GUI *igui=GetTopGUI();
      {
        if (igui)
        {
#ifdef ELKA
          void *canvasdata = BuildCanvas();
          {
#else
          void *idata = GetDataOfItemByID(igui, 2);
          if (idata)
          {
            void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
            add_ws_idle_name();
            DrawCanvas(canvasdata,name_pos.x,name_pos.y,name_pos.x2,name_pos.y2,1);
            DrawString(ws_idle_name,name_pos.x,name_pos.y,name_pos.x2,name_pos.y2,name_font,TEXT_OUTLINE,name_col,frame_col);
          }
        }
      }
    }
  }
  return(1);
}

int my_keyhook(int submsg, int msg)
{
  if (msg==LONG_PRESS)
  {
    switch(submsg)
    {
      case '5':
        if(play_flag==0)
        {
          ShowMSG(1,(int)LGP_PLAY);
          play_flag=1;
          control(0);
          return KEYHOOK_BREAK;
        }
        if(play_flag==1)
        {
          ShowMSG(1,(int)LGP_PAUSE);
          control(1);
          return KEYHOOK_BREAK;
        }
        if(play_flag==2) 
          ShowMSG(1,(int)LGP_RESUME);
          control(2);
        return KEYHOOK_BREAK;
      case '4':
        if(sndVolume)
        {
          ShowMSG(1,(int)LGP_VOLDOWN);
          sndVolume--;
          control(4);
        }
        return KEYHOOK_BREAK;
      case '6':
        if(sndVolume!=6)
        {
          ShowMSG(1,(int)LGP_VOLUP);
          sndVolume++;
          control(4);
        }
        return KEYHOOK_BREAK;
      case '2':
        ShowMSG(1,(int)LGP_PREV);
        play_prev();
        return KEYHOOK_BREAK;
      case '8':
        ShowMSG(1,(int)LGP_NEXT);
        play_next();
        return KEYHOOK_BREAK;
    }
  }
  return KEYHOOK_NEXT;
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  FreeWS(ws_idle_name);
  RemoveKeybMsgHook((void *)my_keyhook);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), ELF_NAME);
}

int main(char *initday)
{
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  sndVolume=defau_vol;
  screenw=ScreenW()-1;
  screenh=ScreenH()-1;
  load_list();
  UpdateCSMname();
  
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  AddKeybMsgHook((void *)my_keyhook);
  UnlockSched();
  
  return 0;
}
