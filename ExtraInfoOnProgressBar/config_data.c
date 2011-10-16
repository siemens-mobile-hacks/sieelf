#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

__root const CFG_HDR cfghdr0={CFG_CHECKBOX,"允许补丁",0,1};
__root const unsigned int enable = 1;

#ifndef ELKA
__root const CFG_HDR cfghdr1={CFG_STR_WIN1251,"文本格式",0,15};
__root const char str_f[16]="%d/%d Kb";
#endif

__root const CFG_HDR cfghdr2={CFG_COLOR,"文本颜色",0,0};
__root const char str_color[4]={0x00,0xFF,0x00,0x64};

__root const CFG_HDR cfghdr3={CFG_COLOR,"文本背景色",0,0};
__root const char str_bgcolor[4]={0x00,0x00,0x00,0x00};

__root const CFG_HDR cfghdr4={CFG_COLOR,"进度条颜色",0,0};
__root const char percent_color[4]={0x00,0xFF,0x00,0x64};

__root const CFG_HDR cfghdr5={CFG_COLOR,"进度条背景色",0,0};
__root const char percent_bgcolor[4]={0x00,0x00,0x00,0x00};


