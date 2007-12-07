#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_UINT,"OnlyFrom",0,23};
__root const unsigned int min=0;

__root const CFG_HDR cfghdr1={CFG_UINT,"OnlyTo",0,23};
__root const unsigned int max=23;

__root const CFG_HDR cfghdr3 = {CFG_CHECKBOX,"FullBattery",0,0};
__root const int ch_bat=0;

__root const CFG_HDR cfghdr4 = {CFG_CHECKBOX,"Setprofile",0,0};
__root const int setp=1;



__root const CFG_HDR cfghdr11={CFG_UINT,"melody",0,200};
__root const unsigned int melody=60;

__root const CFG_HDR cfghdr12={CFG_UINT,"melody FullBattery",0,200};
__root const unsigned int melody2=51;

__root const CFG_HDR cfghdr13={CFG_UINT,"alerts minute",0,59};
__root const unsigned int minute=0;

__root const CFG_HDR cfghdr14={CFG_UINT,"profile minute",0,59};
__root const unsigned int minute2=0;

__root const CFG_HDR cfghdr15={CFG_STR_UTF8,"Address",3,127};
__root const char fname[128]="0:\\ZBIN\\ACP\\";

__root const CFG_HDR cfghdr16={CFG_UINT,"fix",0,59};
__root const unsigned int x=0;
