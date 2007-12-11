#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"



__root const CFG_HDR cfghdr0={CFG_CHECKBOX,"两次提示",0,0};
__root const int twice=0;

__root const CFG_HDR cfghdr1={CFG_CHECKBOX,"满电提示",0,0};
__root const int ch_bat=0;


//__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"定时提醒",1,0};

__root const CFG_HDR cfghdr10={CFG_UINT,"起始时间",0,23};
__root const unsigned int min=0;

__root const CFG_HDR cfghdr11={CFG_UINT,"结束时间",0,23};
__root const unsigned int max=24;

__root const CFG_HDR cfghdr12={CFG_UINT,"提示音效",0,200};
__root const unsigned int melody=60;

__root const CFG_HDR cfghdr13={CFG_UINT,"满电音效",0,200};
__root const unsigned int melody2=51;

__root const CFG_HDR cfghdr14={CFG_UINT,"提示分钟1",0,59};
__root const unsigned int minute=0;

__root const CFG_HDR cfghdr15={CFG_UINT,"提示分钟2",0,59};
__root const unsigned int minute2=0;

//__root const CFG_HDR cfghdr16={CFG_UINT,"提醒情景禁用",0,8};
//__root const unsigned int filter=0;

//__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr24={CFG_UINT,"情景切换分钟",0,59};
__root const unsigned int minute3=0;


__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"星期数据",1,0};

__root const CFG_HDR cfghdr101={CFG_STR_UTF8,"星期一",0,24};
__root const char day1[25]="000000000000000000000000";

__root const CFG_HDR cfghdr102={CFG_STR_UTF8,"星期二",0,24};
__root const char day2[25]="000000000000000000000000";

__root const CFG_HDR cfghdr103={CFG_STR_UTF8,"星期三",0,24};
__root const char day3[25]="000000000000000000000000";

__root const CFG_HDR cfghdr104={CFG_STR_UTF8,"星期四",0,24};
__root const char day4[25]="000000000000000000000000";

__root const CFG_HDR cfghdr105={CFG_STR_UTF8,"星期五",0,24};
__root const char day5[25]="000000000000000000000000";

__root const CFG_HDR cfghdr106={CFG_STR_UTF8,"星期六",24,24};
__root const char day6[25]="000000000000000000000000";

__root const CFG_HDR cfghdr107={CFG_STR_UTF8,"星期日",0,24};
__root const char day7[25]="000000000000000000000000";

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};










