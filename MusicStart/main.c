#include "..\inc\swilib.h"
#include "..\inc\playsound.h" 
#include "conf_loader.h"
#include "rect_patcher.h"
#include "filelist.h"
#include "play_list.h"
#include "lang.h"
#include "history.h"
#include "menu.h"

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
extern const RECT gui_name_pos;
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
int play_mode=0;//0:t2b, 1:b2t, 2:shuf
char procfile[128];
char song_name[128];
unsigned int sndVolume=6;
//int is_new_file_selected=0;
WSHDR *ws_idle_name;
//WSHDR *ws_song_name;
char *list_text;

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
    else ShowMSG(1,(int)fname);//测试用
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

/*
GBSTMR mytmr;
char *p_song_name;
void drawnameproc(void)
{
  if(IsGuiOnTop(MAINGUI_ID))
  {
    str_2ws(ws_song_name,p_song_name,64);
    if(get_string_width(ws_song_name, gui_name_font)>=(gui_name_pos.x2-gui_name_pos.x))
    {
      p_song_name++;
    }
    DrawString(ws_song_name,gui_name_pos.x,gui_name_pos.y,gui_name_pos.x2,gui_name_pos.y2,gui_name_font,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,gui_name_col,gui_frame_col); 
  }    
  GBS_StartTimerProc(&mytmr,216/2,drawnameproc);
}

void drawname(void)
{
  p_song_name=strrchr(procfile,'\\')+1;
  DrawRoundedFrame(gui_name_pos.x-1,gui_name_pos.y-1,gui_name_pos.x2+1,gui_name_pos.y2+2,0,0,0,GetPaletteAdrByColorIndex(7),GetPaletteAdrByColorIndex(23));
  drawnameproc();
}
*/

void onRedraw(MAIN_GUI *data)
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  DrawRectangle(0,0,screenw,screenh,0,gui_main_bg_col,gui_main_bg_col);
  soft_key();
  //歌曲名
  //drawname();
  WSHDR *ws_song_name=AllocWS(64);
  const char *p=strrchr(procfile,'\\')+1;
  str_2ws(ws_song_name,p,64);
  DrawRoundedFrame(gui_name_pos.x-1,gui_name_pos.y-1,gui_name_pos.x2+1,gui_name_pos.y2+3,0,0,0,GetPaletteAdrByColorIndex(7),GetPaletteAdrByColorIndex(23));
  DrawString(ws_song_name,gui_name_pos.x,gui_name_pos.y,gui_name_pos.x2,gui_name_pos.y2,gui_name_font,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,gui_name_col,gui_frame_col); 
                      
  //str_2ws(ws_song_name,procfile,128);
  
  //音量
  char *sta=malloc(256);
  WSHDR *ws_sta=AllocWS(256);
  //音量//播放状态
  char c_sta[16];
  switch(play_flag)
  {
    case 0:
      sprintf(c_sta,LNG_STOP);//停止
      break;
    case 1:
      sprintf(c_sta,LNG_PLAYING);//正在播放
      break;
    case 2:
      sprintf(c_sta,LNG_PAUSE);//暂停
      break;
  }
  //播放模式
  char c_mode[16];
  switch(play_mode)
  {
    case 0:
      sprintf(c_mode,LNG_MODE_T2B);
      break;
    case 1:
      sprintf(c_mode,LNG_MODE_B2T);
      break;
    case 2:
      sprintf(c_mode,LNG_MODE_SHUF);
      break;
  }
  sprintf(sta,LNG_VOL": %d\n"LNG_STATUS": %s\n"LNG_PLAYMODE": %s", sndVolume, c_sta, c_mode);
  utf8_2ws(ws_sta,sta,strlen(sta));
  DrawString(ws_sta,gui_sta_x,gui_sta_y,screenw,screenh,gui_sta_font,TEXT_OUTLINE,gui_sta_col,gui_sta_frame_col); 
  mfree(sta);
  FreeWS(ws_song_name);
  FreeWS(ws_sta);
}

void control(int type)
{
  //type 0:play, 1: Pause, 2:Resume, 3: Stop, 4:change vol
    switch(type)
    {
      case 0:
        if(playhandle&&(play_flag!=0)) PlayMelody_StopPlayback(playhandle);//停掉正在播放的歌曲
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
        REDRAW();
        break;
      case ENTER_BUTTON:
      case '5':
        if(play_flag==0)
        {
          play_flag=1; //在不播放条件下，先改变这个值，使control(0);继续执行
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
      case '3':
        play_shuff();
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

void play_mode_switch(void)
{
  switch(play_mode)
  {
    case 0:
      play_next();
      break;
    case 1:
      play_prev();
      break;
    case 2:
      play_shuff();
      break;
  }
}

const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  //ws_song_name=AllocWS(64);
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

int is_call_pause=0;

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
  if(msg->msg==MSG_INCOMMING_CALL)
  {
    is_call_pause=1;
    control(1);
  }
  if(msg->msg==MSG_END_CALL)
  {
    if(is_call_pause)
      control(2);
    is_call_pause=0;
  }
  if(msg->msg==MSG_PLAYFILE_REPORT) 
  {
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if (pmsg->handler==playhandle)
    {
      if (pmsg->cmd==M_SAE_PLAYBACK_ERROR)
      {
        control(3);
      }
      if (pmsg->cmd==M_SAE_PLAYBACK_DONE)
      {
        if(play_flag!=0) 
          play_mode_switch();
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

void long_press_switch(int key)
{
  switch(key)
  {
    case 0://2
      play_prev();
      break;
    case 1://8
      play_next();
      break;
    case 2://4
      if(sndVolume>0)
      {
        sndVolume--;
        control(4);
      }
      break;
    case 3://6
      if(sndVolume<6)
      {
        sndVolume++;
        control(4);
      }
      break;
    case 4://5
      if(play_flag==0)
      {
        play_flag=1;
        control(0);
        break;
      }
      if(play_flag==1)
      {
        control(1);
        break;
      }
      if(play_flag==2) 
      control(2);
      break;
    case 5://3
      play_shuff();
      break;
  }
}

int hot_key_mode=0;
int my_keyhook(int submsg, int msg)
{
  int i;
  int hot_keys[6]={'2','8','4','6','5','3'};
  for(i=0;i<6;i++)
  {
    if(submsg==hot_keys[i])
    {
      switch(msg)
      {
        case KEY_DOWN:
          if(hot_key_mode==2)
          {
            GBS_SendMessage(MMI_CEPID,KEY_UP,hot_keys[i]);
            return KEYHOOK_NEXT;
          }
          hot_key_mode=0;
          return KEYHOOK_BREAK;
        case KEY_UP:
          if(hot_key_mode==0)
          {
            hot_key_mode=2;
            GBS_SendMessage(MMI_CEPID,KEY_DOWN,hot_keys[i]);
            return KEYHOOK_BREAK;
          }
          if (hot_key_mode==2)
          {
            hot_key_mode=0;
            return KEYHOOK_NEXT;
          }
          hot_key_mode=0;
          return KEYHOOK_BREAK;
        case LONG_PRESS:
          hot_key_mode=1;
          long_press_switch(i);
          break;
      }
    }
  }
  return KEYHOOK_NEXT;
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  //FreeWS(ws_song_name);
  FreeWS(ws_idle_name);
  save_his();
  mfree(list_text);
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
  list_text=malloc(16384);
  sndVolume=defau_vol;
  screenw=ScreenW()-1;
  screenh=ScreenH()-1;
  
  load_list(load_history());
  
  UpdateCSMname();
  
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  AddKeybMsgHook((void *)my_keyhook);
  UnlockSched();
  
  return 0;
}
