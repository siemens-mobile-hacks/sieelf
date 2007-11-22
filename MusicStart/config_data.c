#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#define scrh  319
#define scrw  239
#else 
#define DEFAULT_DISK "0"
#define scrh  175
#define scrw  131
#endif

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"General Path",3,127};
__root const char g_path[128]=DEFAULT_DISK":\\ZBin\\MusicStart\\";


__root const CFG_HDR cfghdr_0_0={CFG_LEVEL,"Idle Screen Setup",1,0};

__root const CFG_HDR cfghdr01= {CFG_RECT, "Name Position", 0, 239};
__root const RECT name_pos = {0,scrh/2,scrw,scrh/2+20};

__root const CFG_HDR cfghdr02={CFG_UINT,"Name Font",0,16};
__root const unsigned int name_font=FONT_SMALL;

__root const CFG_HDR cfghdr03={CFG_COLOR,"Name Color",0,0};
__root const char name_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr04={CFG_COLOR,"Name Frame Color",0,0};
__root const char frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_1={CFG_LEVEL,"GUI Setup",1,0};

__root const CFG_HDR cfghdr10={CFG_COLOR,"Main Backround Color",0,0};
__root const char gui_main_bg_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr11={CFG_RECT,"Name Position",0,0};
__root const RECT gui_name_pos={1,scrh/2,scrw-1,scrh/2+30};

__root const CFG_HDR cfghdr12={CFG_UINT,"Name Font",0,16};
__root const unsigned int gui_name_font=FONT_SMALL;

__root const CFG_HDR cfghdr13={CFG_COLOR,"Name Color",0,0};
__root const char gui_name_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr14={CFG_COLOR,"Name Frame Color",0,0};
__root const char gui_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr1b={CFG_COLOR,"Name Rounded Frame Color",0,0};
__root const char gui_round_frame_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr15={CFG_COORDINATES,"Status Position",0,0};
__root const unsigned int gui_sta_x=20;
__root const unsigned int gui_sta_y=20;

__root const CFG_HDR cfghdr16={CFG_UINT,"Status Font",0,16};
__root const unsigned int gui_sta_font=FONT_SMALL;

__root const CFG_HDR cfghdr17={CFG_COLOR,"Status Color",0,0};
__root const char gui_sta_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr18={CFG_COLOR,"Status Frame Color",0,0};
__root const char gui_sta_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr19={CFG_UINT,"SoftKey Font",0,65535};
__root const unsigned int sk_font=FONT_MEDIUM;

__root const CFG_HDR cfghdr1a={CFG_COLOR,"SoftKey Color",0,0};
__root const char sk_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr_1_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_2={CFG_LEVEL,"Default Player Setup",1,0};

__root const CFG_HDR cfghdr20={CFG_UINT,"Default Vol",0,6};
__root const unsigned int defau_vol=3;

__root const CFG_HDR cfghdr21={CFG_UINT,"Scroll speed",0,999};
__root const unsigned int defau_scroll_speed=80;

__root const CFG_HDR cfghdr_2_0={CFG_LEVEL,"",0,0};

