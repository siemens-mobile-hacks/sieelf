#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
//Êîíôèãóðàö?

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Address list",3,127};
__root const char root_dir[128]="0:\\\x1F\xE7\xB3\xBB\xE7\xBB\x9F\\apo\\addr";

//__root const CFG_HDR cfghdr1 = {CFG_UINT,"Font",0,9};
//__root const int font_size=7;
__root const CFG_HDR cfghdr50 = {CFG_CHECKBOX,"Disable when calling",0,0};
__root const int disable_when_calling=1;

__root const CFG_HDR cfghdr52 = {CFG_CHECKBOX,"Show number",0,0};
__root const int show_number=1;

__root const CFG_HDR cfghdr53 = {CFG_CHECKBOX,"Show more number",0,0};
__root const int show_more_number=1;

__root const CFG_HDR cfghdr54 = {CFG_CHECKBOX,"Big font",0,0};
__root const int big_font=1;

__root const CFG_HDR cfghdr1_55={CFG_UINT,"Numberlist button",0,65535};
__root const unsigned int CALL_BTN=VOL_UP_BUTTON;


/*
//Õñ¶¯
__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"Vibra sitting",1,0};

__root const CFG_HDR cfghdr18={CFG_CHECKBOX,"Use vibra",0,0};
__root const int ENA_VIBRA = 0;

__root const CFG_HDR cfghdr19={CFG_UINT,"Vibra power",0,100};
__root const unsigned int vibraPower=20;

__root const CFG_HDR cfghdr20={CFG_UINT,"Vibra duration (ms)",0,100};
__root const unsigned int vibraDuration=50;

__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};
*/


//ÑÕÉ«
__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"Color setting",1,0};

__root const CFG_HDR cfghdr10={CFG_COLOR,"Color Menu background",0,99};
__root const int COLOR_MENU_BK=23;

__root const CFG_HDR cfghdr11={CFG_COLOR,"Color Menu border",0,99};
__root const int COLOR_MENU_BRD=1;

__root const CFG_HDR cfghdr40={CFG_COLOR,"Number menu background",0,99};
__root const int COLOR_NMENU_BK=23;

__root const CFG_HDR cfghdr41={CFG_COLOR,"Number menu border",0,99};
__root const int COLOR_NMENU_BRD=1;

__root const CFG_HDR cfghdr12={CFG_COLOR,"Color Not selected",0,99};
__root const int COLOR_NOTSELECTED=0;

__root const CFG_HDR cfghdr13={CFG_COLOR,"Color Selected",0,99};
__root const int COLOR_SELECTED=1;

__root const CFG_HDR cfghdr51={CFG_COLOR,"Number color",0,99};
__root const int COLOR_NUMBER=0;

__root const CFG_HDR cfghdr14={CFG_COLOR,"Color Selected background",0,99};
__root const int COLOR_SELECTED_BG=7;

__root const CFG_HDR cfghdr15={CFG_COLOR,"Color Selected border",0,99};
__root const int COLOR_SELECTED_BRD=23;

__root const CFG_HDR cfghdr24={CFG_COLOR,"Number selected background",0,99};
__root const int COLOR_NUMBER_BG=23;

__root const CFG_HDR cfghdr25={CFG_COLOR,"Number selected border",0,99};
__root const int COLOR_NUMBER_BRD=0;

__root const CFG_HDR cfghdr16={CFG_COLOR,"Color Search mark",0,99};
__root const char COLOR_SEARCH_MARK[4]={0xFF,0x0,0x0,0x64};

__root const CFG_HDR cfghdr17={CFG_COLOR,"Color Search unmark",0,0};
__root const char COLOR_SEARCH_UNMARK[4]={0xFF,0xFF,0xFF,0x64};

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};



//ÇøºÅÐã
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"CodeShow",1,0};

__root const CFG_HDR cfghdr30 = {CFG_CHECKBOX,"Show CodeShow",0,0};
__root const int cfg_cs_enable=1;

__root const CFG_HDR cfghdr31 = {CFG_CHECKBOX,"Part show",0,0};
__root const int cfg_cs_part=0;

__root const CFG_HDR cfghdr32 = {CFG_COLOR,"CodeShow color",0,24};
__root const int cfg_cs_font_color=0;

__root const CFG_HDR cfghdr33 = {CFG_UINT,"CodeShow address",0,0xFFFFFFFF};
__root const int cfg_cs_adr=0xA0CC0000;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};



