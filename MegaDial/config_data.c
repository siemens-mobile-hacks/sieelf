#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
//暑眙桡箴圉?

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Address list",3,127};
__root const char root_dir[128]="0:\\\x1F\xE7\xB3\xBB\xE7\xBB\x9F\\apo\\addr";

__root const CFG_HDR cfghdr1 = {CFG_UINT,"字体",0,9};
__root const int font_size=7;

__root const CFG_HDR cfghdr2 = {CFG_UINT,"条目间距",0,6};
__root const int cfg_item_gaps=3;

__root const CFG_HDR cfghdr3 = {CFG_UINT,"一页显示条目数",0,8};
__root const int count_page=6;

__root const CFG_HDR cfghdr18={CFG_CHECKBOX,"Use vibra",0,0};
__root const int ENA_VIBRA = 0;

__root const CFG_HDR cfghdr19={CFG_UINT,"Vibra power",0,100};
__root const unsigned int vibraPower=20;

__root const CFG_HDR cfghdr20={CFG_UINT,"Vibra duration (ms)",0,100};
__root const unsigned int vibraDuration=50;

__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"Color setting",1,0};

__root const CFG_HDR cfghdr10={CFG_COLOR,"Color Menu background",0,99};
__root const int COLOR_MENU_BK=23;

__root const CFG_HDR cfghdr11={CFG_COLOR,"Color Menu border",0,99};
__root const int COLOR_MENU_BRD=1;

__root const CFG_HDR cfghdr12={CFG_COLOR,"Color Not selected",0,99};
__root const int COLOR_NOTSELECTED=0;

__root const CFG_HDR cfghdr13={CFG_COLOR,"Color Selected",0,99};
__root const int COLOR_SELECTED=1;

__root const CFG_HDR cfghdr14={CFG_COLOR,"Color Selected background",0,99};
__root const int COLOR_SELECTED_BG=7;

__root const CFG_HDR cfghdr15={CFG_COLOR,"Color Selected border",0,99};
__root const int COLOR_SELECTED_BRD=23;

__root const CFG_HDR cfghdr16={CFG_COLOR,"Color Search mark",0,99};
__root const char COLOR_SEARCH_MARK[4]={0xFF,0x0,0x0,0x64};

__root const CFG_HDR cfghdr17={CFG_COLOR,"Color Search unmark",0,0};
__root const char COLOR_SEARCH_UNMARK[4]={0xFF,0xFF,0xFF,0x64};

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"区号秀",1,0};

__root const CFG_HDR cfghdr30 = {CFG_CBOX,"是否显示区号秀",0,2};
__root const int cfg_cs_enable=1;
__root const CFG_CBOX_ITEM cfgcbox38[2] = {"否","是"};

__root const CFG_HDR cfghdr31 = {CFG_COLOR,"区号秀字体颜色",0,24};
__root const int cfg_cs_font_color=0;

__root const CFG_HDR cfghdr32 = {CFG_UINT,"区号秀分隔符",0,0xFFFF};
__root const int cfg_cs_split =' '; //0x2027;

__root const CFG_HDR cfghdr33 = {CFG_UINT,"区号秀数据地址",0,0xFFFFFFFF};
__root const int cfg_cs_adr=0xA0CC0000;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};



