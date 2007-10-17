#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "define.h"
#include "gui.h"
#include "dict.h"
#include "rect_patcher.h"
#include <stdbool.h>

//================= extern vars and funcs from dict.c ========================/

#define TEXT_NOAUTOLINEBREAK 128
#define MAX_UNICODE_STR 512

extern char *indexbuf;
extern const int idxbuf_size;

extern char **index;
extern const int wordcount;

extern int dict;

extern bool m_f_err;                //memory or file error;
extern char* err_msg;               //error msg string;
unsigned short mferr_unicode[] =    //"内存不足或读文件错，请退出！"
        {0x5185, 0x5B58, 0x4E0D, 0x8DB3, 0x6216, 0x8BFB, 0x6587,
        0x4EF6, 0x9519, 0xFF0C, 0x8BF7, 0x9000, 0x51FA, 0xFF01, 0};



int start_index = 9;
int highlight_item = 0;

char pre_inputword[128];
bool wanna_quit = false;
int ed1_id;
int is_ed_started=0;

#define TMR_SECOND 216
GBSTMR  timer;
bool fw_showing = false;
unsigned long global_time = 0;
unsigned long last_key_time = 0;
int ed1_last_key_down = 0;

#ifdef DICT_DEBUG
WSHDR* debug_kd_word;
WSHDR* debug_ku_word;
WSHDR* debug_lp_word;
#endif

//============================================================================/

const int minus11 = -11;

bool list_redraw_hooked = false;
void (*old_ed1_redraw)(void *data);

const SOFTKEY_DESC menu_sk[]=
{
    {0x0018,0x0000,(int)"Menu"},
    {0x0001,0x0000,(int)"Exit"},
    {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
	menu_sk,0
};

typedef struct
{
	CSM_RAM csm;
	int gui_id;
}MAIN_CSM;


extern const unsigned int cfg_showfreeram;

extern const RECT win_pos;


extern const unsigned int cfg_item_n;

extern const char cfg_separator_color[4];
extern const unsigned int cfg_dim_fontsize;
extern const char cfg_dim_color[4];

extern const unsigned int cfg_highlight_fontsize;
extern const char cfg_highlight_color[4];

extern const char cfg_highlight_bgcolor[4];
extern const char cfg_bordercolor[4];

extern const char cfg_scrollbar_color[4];
extern const char cfg_scrollbar_blkcolor[4];

//====== instant view ==========//
extern const unsigned int cfg_floatwin;
extern const unsigned int cfg_fw_delay;
extern const unsigned int cfg_fw_phonetic;
extern const unsigned int cfg_fw_height;
extern const unsigned int cfg_fw_width;
extern const unsigned int cfg_fw_fontsize;
extern const char cfg_fw_fontcolor[4];
extern const char cfg_fw_bgcolor[4];
extern const char cfg_fw_bordercolor[4];
//=========== modifiable ============/

// modifiables
unsigned int floatwin;
unsigned int fw_phonetic;

int screenh;
int screenw;


void Error(const char *msg)
{
	m_f_err = true;
	LockSched();
	ShowMSG(1, (int)msg);
	UnlockSched();
}

char* get_inputword(GUI* gui, int editc_id)     //ed1
{
    static char word[64];
    EDITCONTROL ec;
    
    ExtractEditControl(gui, editc_id, &ec);
    ws_2str(ec.pWS, word, sizeof(word));
    
    return word;
}

//hard to write a function to set inputword, maybe because of T9 buffer.
void do_lookup(GUI *data)                       //ed1
{
    int pos;
    char *word = get_inputword(data, 1);
    
    //if input word doesn't changed, then no need to lookup!
    if( strcmp(word, pre_inputword)!=0 && (pos = lookup(word)) >= 0 )
    {
        strcpy(pre_inputword, word);
        start_index = pos;
        highlight_item = 0;
    }
}

void my_ed1_redraw(GUI* gui)
{
  int highlight_font_height = GetFontYSIZE(cfg_highlight_fontsize);
  int dim_font_height = GetFontYSIZE(cfg_dim_fontsize);
  int font_height_diff = 0;   //highlight_font_height - dim_font_height;
  RECT highlight;
  int i;
  WSHDR *ws;
  
  //REDRAW
  old_ed1_redraw(gui);
  
  if( m_f_err )
  {        
    ws = AllocWS(sizeof(mferr_unicode));
    copy_unicode_2ws(ws, mferr_unicode);
    
    DrawString(ws,
               win_pos.x + 2,
               win_pos.y2,
               screenw - 6,
               win_pos.y2 + 120,
               cfg_highlight_fontsize,
               TEXT_ALIGNLEFT,
               cfg_dim_color,
               GetPaletteAdrByColorIndex(23)
               );
    FreeWS(ws);
    return;
  }
  
  ws = AllocWS(MAX_UNICODE_STR);
  
  DrawLine(win_pos.x + 1,
           win_pos.y2 - 2,
           screenw - win_pos.x - 1,
           win_pos.y2 - 2,
           0,
           cfg_separator_color);
  
  //draw items
  for( i=0; i<cfg_item_n; i++ )
  {
    if( (start_index+i)>=wordcount )
    {
      break;
    }
    
    str_2ws(ws, index[start_index+i], strlen(index[start_index+i]));
    if( i == highlight_item )       //draw highlight item and frame
    {
      font_height_diff = highlight_font_height - dim_font_height;
      
      highlight.x  = win_pos.x;
      highlight.y  = win_pos.y2 + i*(dim_font_height + 5);
      highlight.x2 = screenw-4;
      highlight.y2 = highlight.y + dim_font_height + 4 + font_height_diff;
      
      DrawRoundedFrame(highlight.x,
                       highlight.y,
                       highlight.x2,
                       highlight.y2,
                       2,
                       2,
                       2,     //border-type 0=outline 1=dotted 2=inline
                       cfg_bordercolor,
                       cfg_highlight_bgcolor
                           );
      DrawString(ws,
                 highlight.x + 2,
                 highlight.y + 3,
                 highlight.x2 - 2,
                 highlight.y2 - 1,
                 cfg_highlight_fontsize,
                 TEXT_ALIGNLEFT + TEXT_NOAUTOLINEBREAK,
                 cfg_highlight_color,
                 GetPaletteAdrByColorIndex(23)
                     );
      
    }
    else                        //draw dim(normal) item, no frame
    {
      DrawString(ws,
                 win_pos.x + 2,
                 win_pos.y2 + i*(dim_font_height + 5) + 2 + font_height_diff + 1,
                 screenw - 6,
                 win_pos.y2 + (i+1)*(dim_font_height + 5) - 2 + font_height_diff - 1,
                 cfg_dim_fontsize,// - 1, //Make it thin!!!!
                 TEXT_ALIGNLEFT + TEXT_NOAUTOLINEBREAK,
                 cfg_dim_color,
                 GetPaletteAdrByColorIndex(23)
                     );
    }
    
  }
    
  //draw scrollbar
  int barlen = cfg_item_n * (dim_font_height + 5) + font_height_diff;
  int blkpos = barlen * (start_index+highlight_item) / wordcount;
  
  DrawLine(screenw - 2,
           win_pos.y2,
           screenw - 2,
           win_pos.y2 + barlen,
           0,
           cfg_scrollbar_color);
  
  DrawRoundedFrame(screenw - 3,
                   win_pos.y2 + blkpos - 1,
                   screenw - 1,
                   win_pos.y2 + blkpos + 1,
                   0,
                   0,
                   0,     //border-type 0=outline 1=dotted 2=inline
                   cfg_scrollbar_blkcolor,
                   cfg_scrollbar_blkcolor);
  
  //draw instant view
  if( floatwin && (global_time-last_key_time)>=cfg_fw_delay )
  {
      fw_showing = true;
      
      int fw_x, fw_y;
      
      fw_x = highlight.x2 - 2 - cfg_fw_width;
      
      if( (highlight.y2 + cfg_fw_height > screenh - 18)     //下方放不下，18=软键高度
         && (highlight.y  >= win_pos.y2 + cfg_fw_height))   //且上方能放下
      {
          fw_y = highlight.y - cfg_fw_height;             //放到上方
      }
      else
      {
          fw_y = highlight.y2;                            //放到下方
      }
      
      DrawRoundedFrame(fw_x,
                       fw_y,
                       fw_x + cfg_fw_width,
                       fw_y + cfg_fw_height,
                       4,
                       4,
                       2,     //border-type 0=outline 1=dotted 2=inline
                       cfg_fw_bordercolor,
                       cfg_fw_bgcolor
                           );
      
      construct_entry_text(ws, index[start_index + highlight_item], 0, fw_phonetic, 1);
      DrawString(ws,
                 fw_x + 2,
                 fw_y + 2,
                 fw_x + cfg_fw_width - 2,
                 fw_y + cfg_fw_height - 2,
                 cfg_fw_fontsize,
                 TEXT_ALIGNLEFT + TEXT_NOAUTOLINEBREAK,
                 cfg_fw_fontcolor,
                 GetPaletteAdrByColorIndex(23)
                     );
                 
  }
  else
  {
      fw_showing = false;
  }
  
  //draw debug info
  if( cfg_showfreeram )
  {
    int fr = GetFreeRamAvail();
    wsprintf(ws, "FreeRam: %dKB", fr/1024);
    DrawString(ws,
           2,
           screenh-SoftkeyH()-GetFontYSIZE(FONT_SMALL),
           screenw - 6,
           screenh-SoftkeyH(),
           FONT_SMALL,// - 1, 
           TEXT_ALIGNRIGHT + TEXT_OUTLINE,
           GetPaletteAdrByColorIndex(0),
           GetPaletteAdrByColorIndex(1)
               );
  }
  FreeWS(ws);
}


void ed1_locret(void){}
void ed2_locret(void){}

int create_ed1(void);



void QuitProc(int really_quit)  //回调函数不是立即调用的
{
    if( !really_quit )
    {
        wanna_quit = true;
    }
}

void quit(void)
{
  wanna_quit = false; 
  MsgBoxYesNo(1, (int)"Quit ECDict?", QuitProc); 
}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
#define RET_REDRAW  -1
#define RET_DEFAULT 0
#define RET_CLOSE   1
    
    int ret = RET_DEFAULT;
    int keycode = msg->gbsmsg->submess;
    int keymsg = msg->gbsmsg->msg;
    
    if( keycode == 99 )     //virtual redraw demand keycode
    {
        return RET_REDRAW;
    }
    
    if( m_f_err )
    {
        wanna_quit = true;
        return RET_CLOSE;
    }
    
    if( keymsg==KEY_DOWN )  //...for showing cr...
    {
        ed1_last_key_down = keycode;
    }
    if( keymsg==LONG_PRESS )
    {
        ed1_last_key_down = 0;
    }
    
	if ( keymsg==KEY_DOWN || keymsg==LONG_PRESS)
	{
	  int upthres, downthres;                                                                    
    upthres = 2;                                                                                   
    downthres = cfg_item_n - 3;                                                                    
    switch(keycode)                                                                                
    {                                                                                              
      case DOWN_BUTTON:                                                                                         
        if( (highlight_item==downthres || highlight_item==cfg_item_n)                              
           && (start_index < wordcount-highlight_item-1) )                                         
        {                                                                                          
            //move whole                                                                           
            start_index ++;                                                                        
        }                                                                                          
        else if( highlight_item < cfg_item_n-1                                                     
                && (start_index < wordcount-highlight_item-1) )                                    
        {                                                                                          
            //move highlight                                                                       
            highlight_item ++;                                                                     
        }                                                                                          
        ret = RET_REDRAW;
        break;                                                                                           
      case UP_BUTTON:                                                                                                                                                            
        if( (highlight_item==upthres || highlight_item==0) && (start_index>0) )                    
        {                                                                                          
            //move whole                                                                           
            start_index --;                                                                        
        }                                                                                          
        else if( highlight_item>0 )                                                                
        {                                                                                          
            //move highlight                                                                       
            highlight_item --;                                                                     
        }                                                                                          
        ret = RET_REDRAW;
        break;
      case ENTER_BUTTON:
        //ret = RET_CLOSE;    
        create_gui();
        break;    
      case GREEN_BUTTON:
        fw_phonetic = 1 - fw_phonetic;
        ret = RET_REDRAW; 
        break;      
      case LEFT_SOFT://可能显示版权信息
        if( keymsg == KEY_DOWN && get_inputword(data, 1)[0]==0 )
          ret = RET_CLOSE;            
        break;                                      
#ifdef NEWSGOLD                                                                                                      
      case '*':
        if(keymsg==LONG_PRESS)  
        {
          quit();
          ret = RET_REDRAW;  
        }   
        else
        {
          floatwin = 1 - floatwin;                                                                   
          ret = RET_REDRAW;
        }
        break;                                                                                        
#else                                                                                                         
      case '*':                                                                        
        floatwin = 1 - floatwin;                                                                   
        ret = RET_REDRAW;   
        break;                                                          
      case RED_BUTTON:
        quit();                                             
        ret = RET_REDRAW;
        break;                                                                                          
#endif        
      case '#':
        break;
      default:
        last_key_time = global_time; 
        break;
    }   
  }   
	return ret;
}

void ed1_ghook(GUI *gui, int cmd)
{
  if( !list_redraw_hooked ) 
  {
	  static void *methods[16];
	  void **m=GetDataOfItemByID(gui,4);
      
	  if (m)
	  {
	  	if (m[1])
	  	{
	  		memcpy(methods,m[1],sizeof(methods));
	  		old_ed1_redraw=(void (*)(void *))(methods[0]);
	  		methods[0]=(void *)my_ed1_redraw;
                
	  		m[1]=methods;
                list_redraw_hooked = true;
	  	}
	  }
  }
  else if( cmd == 7 ) //?? OnRun ??
  {
      do_lookup(gui);
  }     
}



//unsigned short thdr1[] = {0xF182, 0x496C, 0x8BCD, 0x5178, 0}; //"英汉词典"
HEADER_DESC ed1_hdr={0, 0, 131, 19, NULL, (int)"En-Cn Dictionary", LGP_NULL};

INPUTDIA_DESC ed1_desc=
{
	1,
	ed1_onkey,
	ed1_ghook,
	(void *)ed1_locret,
	0,
	&menu_skt,
	{2,YDISP+2,scrw,scrh},
	FONT_SMALL,
	100,
	101,
	0,
    
	0,
    
	0x40000000
};

int create_ed1(void)
{
  is_ed_started=1;
	void *ma=malloc_adr();
	void *eq;
	WSHDR *pws;
	EDITCONTROL ec;
    
	PrepareEditControl(&ec);
	eq=AllocEQueue(ma,mfree_adr());
	pws=AllocWS(MAX_UNICODE_STR);

	wsprintf(pws, "%t", pre_inputword);
	ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, pws, 16);    //最长输入16个字母？
	AddEditControlToEditQend(eq, &ec, ma);
	FreeWS(pws);
    
  patch_dialog(&ed1_desc, win_pos.x, win_pos.y, win_pos.x2, win_pos.y2);  
  list_redraw_hooked = false;
	ed1_id =  CreateInputTextDialog(&ed1_desc, NULL/*&ed1_hdr*/, eq, 1, 0);
    
  return ed1_id;
}

void Killer(void)
{
	extern void *ELF_BEGIN;
	extern void kill_data(void *p, void (*func_p)(void *));
	CloseDict();
	UnloadDictIndex();
  GBS_DelTimer(&timer);
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_oncreate(CSM_RAM *data)
{
  screenh=ScreenH();
  screenw=ScreenW();
	MAIN_CSM *csm=(MAIN_CSM*)data;
    
	csm->gui_id=create_gui();
    
  floatwin = cfg_floatwin;
  fw_phonetic = cfg_fw_phonetic;
  LoadDictIndex();
  OpenDict();
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	MAIN_CSM *csm=(MAIN_CSM*)data;
	if (msg->msg==MSG_GUI_DESTROYED)
	{
		if ((int)msg->data0==csm->gui_id)
		{
			csm->csm.state=-3;
		}
	}
  if( wanna_quit )
  {
    csm->csm.state=-3;
  }
	return(1);
}

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
	unsigned short csmname1[] = {0x82F1, 0x6C49, 0x8BCD, 0x5178, 0}; //"英汉词典"
	copy_unicode_2ws((WSHDR *)(&MAINCSM.maincsm_name), csmname1);
}

void TimeCounterProc(void)
{
    global_time ++;
    
    if( !fw_showing && (global_time-last_key_time)>=cfg_fw_delay )
    {
        GBS_SendMessage(MMI_CEPID, KEY_DOWN, 99);           //暂时先用键码99做刷新。。
    }
    GBS_StartTimerProc(&timer, TMR_SECOND/10, TimeCounterProc);
}

int main()
{
	char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();
  
	LockSched();
	CreateCSM(&MAINCSM.maincsm, dummy, 0);
	UnlockSched(); 
	
	GBS_StartTimerProc(&timer, TMR_SECOND, TimeCounterProc);
	return 0;
}
