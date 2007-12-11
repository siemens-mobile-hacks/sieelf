#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"


__root const CFG_HDR cfghdr0={CFG_CHECKBOX,"Twice an hour",0,0};
__root const int twice=0;


__root const CFG_HDR cfghdr1 = {CFG_CHECKBOX,"FullBattery",0,0};
__root const int ch_bat=0;

//__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"定时提醒",1,0};

__root const CFG_HDR cfghdr10={CFG_UINT,"OnlyFrom",0,23};
__root const unsigned int min=0;

__root const CFG_HDR cfghdr11={CFG_UINT,"OnlyTo",0,23};
__root const unsigned int max=24;

__root const CFG_HDR cfghdr12={CFG_UINT,"melody",0,200};
__root const unsigned int melody=60;

__root const CFG_HDR cfghdr13={CFG_UINT,"melody FullBattery",0,200};
__root const unsigned int melody2=51;

__root const CFG_HDR cfghdr14={CFG_UINT,"alerts minute2",0,59};
__root const unsigned int minute=0;

__root const CFG_HDR cfghdr15={CFG_UINT,"alerts minute2",0,59};
__root const unsigned int minute2=0;

//__root const CFG_HDR cfghdr16={CFG_UINT,"提醒情景禁用",0,8};
//__root const unsigned int filter=0;

//__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr24={CFG_UINT,"profile minute",0,59};
__root const unsigned int minute3=0;


__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"week data",1,0};

__root const CFG_HDR cfghdr101={CFG_STR_UTF8,"Day1",0,24};
__root const char day1[25]="000000000000000000000000";

__root const CFG_HDR cfghdr102={CFG_STR_UTF8,"Day2",0,24};
__root const char day2[25]="000000000000000000000000";

__root const CFG_HDR cfghdr103={CFG_STR_UTF8,"Day3",0,24};
__root const char day3[25]="000000000000000000000000";

__root const CFG_HDR cfghdr104={CFG_STR_UTF8,"Day4",0,24};
__root const char day4[25]="000000000000000000000000";

__root const CFG_HDR cfghdr105={CFG_STR_UTF8,"Day5",0,24};
__root const char day5[25]="000000000000000000000000";

__root const CFG_HDR cfghdr106={CFG_STR_UTF8,"Day6",24,24};
__root const char day6[25]="000000000000000000000000";

__root const CFG_HDR cfghdr107={CFG_STR_UTF8,"Day7",0,24};
__root const char day7[25]="000000000000000000000000";

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};
