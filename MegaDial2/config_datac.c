#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
//暑眙桡箴圉?


__root const CFG_HDR cfghdr_m5={CFG_LEVEL,"基本功能控制",1,0};

__root const CFG_HDR cfghdr101 = {CFG_CHECKBOX,"大字体",0,0};
__root const int big_font=0;

__root const CFG_HDR cfghdr102 = {CFG_CHECKBOX,"区号秀",0,0};
__root const int cfg_cs_enable=1;

__root const CFG_HDR cfghdr103 = {CFG_CHECKBOX,"拨号禁止",0,0};
__root const int disable_when_calling=1;

__root const CFG_HDR cfghdr104 = {CFG_CHECKBOX,"单码禁用",0,0};
__root const int cfg_disable_one_number=1;

__root const CFG_HDR cfghdr107 = {CFG_CHECKBOX,"部分区号秀",0,0};
__root const int cfg_cs_part=0;
/*
__root const CFG_HDR cfghdr108 = {CFG_UINT,"c1",0,65535};
__root const unsigned int CALL_BTN=VOL_DOWN_BUTTON;
*/

__root const CFG_HDR cfghdr108 = {CFG_CHECKBOX,"大头贴显示",0,0};
__root const int show_pic=1;

__root const CFG_HDR cfghdr_m4={CFG_LEVEL,"",0,0};


/*
__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"振动选项",1,0};

__root const CFG_HDR cfghdr18={CFG_CHECKBOX,"使用振动",0,0};
__root const int ENA_VIBRA = 0;

__root const CFG_HDR cfghdr19={CFG_UINT,"振动强度",0,100};
__root const unsigned int vibraPower=20;

__root const CFG_HDR cfghdr20={CFG_UINT,"持续时间(ms)",0,100};
__root const unsigned int vibraDuration=50;

__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};
*/

__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"选号相关颜色",1,0};

__root const CFG_HDR cfghdr123={CFG_COLOR,"姓名颜色",0,99};
__root const int COLOR_SELECTED=1;

__root const CFG_HDR cfghdr112={CFG_COLOR,"号码颜色",0,99};
__root const int COLOR_NUMBER=1;

__root const CFG_HDR cfghdr124={CFG_COLOR,"选择条背景",0,99};
__root const int COLOR_SELECTED_BG=6;

__root const CFG_HDR cfghdr125={CFG_COLOR,"选择条边框",0,99};
__root const int COLOR_SELECTED_BRD=23;

__root const CFG_HDR cfghdr113={CFG_COLOR,"号码标识背景",0,99};
__root const int COLOR_NUMBER_BG=23;

__root const CFG_HDR cfghdr114={CFG_COLOR,"号码标识边框",0,99};
__root const int COLOR_NUMBER_BRD=1;

__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"菜单其他颜色",1,0};

__root const CFG_HDR cfghdr120={CFG_COLOR,"菜单背景",0,99};
__root const int COLOR_MENU_BK=23;

__root const CFG_HDR cfghdr121={CFG_COLOR,"菜单边框",0,99};
__root const int COLOR_MENU_BRD=1;

__root const CFG_HDR cfghdr122={CFG_COLOR,"未选择姓名",0,99};
__root const int COLOR_NOTSELECTED=0;

__root const CFG_HDR cfghdr126={CFG_COLOR,"滚动条颜色",0,99};
__root const int COLOR_SCROLLBAR=0;  

__root const CFG_HDR cfghdr127={CFG_COLOR,"滚动条背景",0,99};
__root const int COLOR_SCROLLBAR_BG=0;  

__root const CFG_HDR cfghdr128={CFG_COLOR,"快选标识",0,0};
__root const char COLOR_SEARCH_MARK[4]={0xFF,0x0,0x0,0x64};

__root const CFG_HDR cfghdr129={CFG_COLOR,"快选未标识",0,0};
__root const char COLOR_SEARCH_UNMARK[4]={0xFF,0xFF,0xFF,0x64};

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"其他相关设定",1,0};

__root const CFG_HDR cfghdr130 = {CFG_COLOR,"区号秀颜色",0,99};
__root const int cfg_cs_font_color=0;

__root const CFG_HDR cfghdr140 = {CFG_COLOR,"区号秀背景",0,99};
__root const int CS_NUMBER_BG=2;

__root const CFG_HDR cfghdr131 = {CFG_UINT,"区号秀地址",0,0xFFFFFFFF};
__root const int cfg_cs_adr=0xA0CC0000;

__root const CFG_HDR cfghdr132={CFG_STR_UTF8,"通信录地址",3,127};
__root const char root_dir[128]="0:\\\x1F\xE7\xB3\xBB\xE7\xBB\x9F\\apo\\addr";

__root const CFG_HDR cfghdr133 = {CFG_UINT,"IP号码",0,0xFFFFFFFF};
__root const int cfg_ip_number = 17951;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};



