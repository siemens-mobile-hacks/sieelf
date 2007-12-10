#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif 

__root const CFG_HDR cfghdr0={CFG_UINT,"起始时间",0,23};
__root const unsigned int min=0;

__root const CFG_HDR cfghdr1={CFG_UINT,"结束时间",0,23};
__root const unsigned int max=24;

__root const CFG_HDR cfghdr3 = {CFG_CHECKBOX,"满电提示",0,0};
__root const int ch_bat=0;

__root const CFG_HDR cfghdr4 = {CFG_CHECKBOX,"情景变换",0,0};
__root const int setp=1;

__root const CFG_HDR cfghdr5 = {CFG_CHECKBOX,"两次提示",0,0};
__root const int twice=0;

__root const CFG_HDR cfghdr11={CFG_UINT,"提示音效",0,200};
__root const unsigned int melody=60;

__root const CFG_HDR cfghdr12={CFG_UINT,"满电音效",0,200};
__root const unsigned int melody2=51;

__root const CFG_HDR cfghdr13={CFG_UINT,"提示分钟1",0,59};
__root const unsigned int minute=0;

__root const CFG_HDR cfghdr14={CFG_UINT,"提示分钟2",0,59};
__root const unsigned int minute2=0;

__root const CFG_HDR cfghdr15={CFG_UINT,"提醒情景禁用",0,8};
__root const unsigned int filter=0;

__root const CFG_HDR cfghdr16={CFG_UINT,"情景切换分钟",0,59};
__root const unsigned int minute3=0;

__root const CFG_HDR cfghdr17={CFG_STR_UTF8,"数据目录",3,127};
__root const char fname[128]=DEFAULT_DISK ":\\ZBIN\\ACP\\";










