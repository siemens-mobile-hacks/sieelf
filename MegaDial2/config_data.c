#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
//暑眙桡箴圉?

__root const CFG_HDR cfghdr_m5={CFG_LEVEL,"Basic sitting",1,0};

__root const CFG_HDR cfghdr101 = {CFG_CHECKBOX,"Big font",0,0};
__root const int big_font=0;

__root const CFG_HDR cfghdr102 = {CFG_CHECKBOX,"Show CodeShow",0,0};
__root const int cfg_cs_enable=1;

__root const CFG_HDR cfghdr103 = {CFG_CHECKBOX,"Disable when calling",0,0};
__root const int disable_when_calling=1;

__root const CFG_HDR cfghdr104 = {CFG_CHECKBOX,"Disable one number",0,0};
__root const int cfg_disable_one_number=1;

__root const CFG_HDR cfghdr107 = {CFG_CHECKBOX,"CodeShow part show",0,0};
__root const int cfg_cs_part=0;
/*
__root const CFG_HDR cfghdr108 ={CFG_UINT,"Numberlist button",0,65535};
__root const unsigned int CALL_BTN=ENTER_BUTTON;
*/
__root const CFG_HDR cfghdr108 = {CFG_CHECKBOX,"Show pic",0,0};
__root const int show_pic=1;

__root const CFG_HDR cfghdr_m4={CFG_LEVEL,"",0,0};
/*
//振动
__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"Vibra sitting",1,0};

__root const CFG_HDR cfghdr18={CFG_CHECKBOX,"Use vibra",0,0};
__root const int ENA_VIBRA = 0;

__root const CFG_HDR cfghdr19={CFG_UINT,"Vibra power",0,100};
__root const unsigned int vibraPower=20;

__root const CFG_HDR cfghdr20={CFG_UINT,"Vibra duration (ms)",0,100};
__root const unsigned int vibraDuration=50;

__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};
*/

//颜色1
__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"Number color",1,0};

__root const CFG_HDR cfghdr123={CFG_COLOR,"Name color",0,99};
__root const int COLOR_SELECTED=1;

__root const CFG_HDR cfghdr112={CFG_COLOR,"Number color",0,99};
__root const int COLOR_NUMBER=1;

__root const CFG_HDR cfghdr124={CFG_COLOR,"Selected background",0,99};
__root const int COLOR_SELECTED_BG=6;

__root const CFG_HDR cfghdr125={CFG_COLOR,"Selected border",0,99};
__root const int COLOR_SELECTED_BRD=23;

__root const CFG_HDR cfghdr113={CFG_COLOR,"Icon selected background",0,99};
__root const int COLOR_NUMBER_BG=23;

__root const CFG_HDR cfghdr114={CFG_COLOR,"Icon selected border",0,99};
__root const int COLOR_NUMBER_BRD=1;

__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};


//颜色2
__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"Menu other Color",1,0};

__root const CFG_HDR cfghdr120={CFG_COLOR,"Color Menu background",0,99};
__root const int COLOR_MENU_BK=23;

__root const CFG_HDR cfghdr121={CFG_COLOR,"Color Menu border",0,99};
__root const int COLOR_MENU_BRD=1;

__root const CFG_HDR cfghdr122={CFG_COLOR,"Color Not selected",0,99};
__root const int COLOR_NOTSELECTED=0;

__root const CFG_HDR cfghdr126={CFG_COLOR,"Color ScrollBar",0,99};
__root const int COLOR_SCROLLBAR=0;  

__root const CFG_HDR cfghdr127={CFG_COLOR,"Color ScrollBar background",0,99};
__root const int COLOR_SCROLLBAR_BG=0;  

__root const CFG_HDR cfghdr128={CFG_COLOR,"Color Search mark",0,0};
__root const char COLOR_SEARCH_MARK[4]={0xFF,0x0,0x0,0x64};

__root const CFG_HDR cfghdr129={CFG_COLOR,"Color Search unmark",0,0};
__root const char COLOR_SEARCH_UNMARK[4]={0xFF,0xFF,0xFF,0x64};

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};


//其他杂项
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Other",1,0};

__root const CFG_HDR cfghdr130 = {CFG_COLOR,"CodeShow color",0,24};
__root const int cfg_cs_font_color=1;

__root const CFG_HDR cfghdr140={CFG_COLOR,"CodeShow background",0,99};
__root const int CS_NUMBER_BG=0;

__root const CFG_HDR cfghdr131 = {CFG_UINT,"CodeShow address",0,0xFFFFFFFF};
__root const int cfg_cs_adr=0xA0CC0000;

__root const CFG_HDR cfghdr132={CFG_STR_UTF8,"Address list",3,127};
__root const char root_dir[128]="0:\\\x1F\xE7\xB3\xBB\xE7\xBB\x9F\\apo\\addr";

__root const CFG_HDR cfghdr133 = {CFG_UINT,"IP number",0,0xFFFFFFFF};
__root const int cfg_ip_number = 17951;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

