#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

/*
#ifdef NEWSGOLD
 #define DEFAULT_DISK "4"
#else
 #define DEFAULT_DISK "0"
#endif
*/

__root const CFG_HDR cfghdr_m5={CFG_LEVEL,"基本功能控制",1,0};

__root const CFG_HDR cfghdr101 = {CFG_CHECKBOX,"大字体",0,0};
__root const int big_font=0;

__root const CFG_HDR cfghdr102 = {CFG_CHECKBOX,"区号秀",0,0};
__root const int cfg_cs_enable=1;

__root const CFG_HDR cfghdr103 = {CFG_CHECKBOX,"拨号禁止",0,0};
__root const int disable_when_calling=1;

__root const CFG_HDR cfghdr104 = {CFG_CHECKBOX,"单码禁用",0,0};
__root const int cfg_disable_one_number=1;

__root const CFG_HDR cfghdr105 = {CFG_CHECKBOX,"部分区号秀",0,0};
__root const int cfg_cs_part=0;

__root const CFG_HDR cfghdr106 = {CFG_CHECKBOX,"大头贴显示",0,0};
__root const int show_pic=0;

__root const CFG_HDR cfghdr111 = {CFG_CHECKBOX,"大头贴缩放",0,0};
__root const int resampled=0;

__root const CFG_HDR cfghdr107 = {CFG_CHECKBOX,"短信号码",0,0};
__root const int smsn=0;

__root const CFG_HDR cfghdr108 = {CFG_CHECKBOX,"短信区号秀",0,0};
__root const int smsc=0;

__root const CFG_HDR cfghdr109 = {CFG_CHECKBOX,"界面音效",0,0};
__root const int voice=0;

__root const CFG_HDR cfghdr110 = {CFG_CHECKBOX,"IP扩展",0,0};
__root const int ipx2=0;

__root const CFG_HDR cfghdr_m4={CFG_LEVEL,"",0,0};


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

//振动
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"接通振动设置",1,0};

 __root const CFG_HDR cfghdr2_1={CFG_CBOX, "使用振动", 0, 4};
 __root const int ENA_VIBRA = 0;
 __root const CFG_CBOX_ITEM cfgcbox7[4]={"不", "来电", "去电", "全部"};

__root const CFG_HDR cfghdr2_2={CFG_UINT,"振动强度",0,100};
__root const unsigned int vibraPower=20;

__root const CFG_HDR cfghdr2_3={CFG_UINT,"持续时间(ms)",0,100};
__root const unsigned int vibraDuration=50;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"其他相关设定",1,0};

__root const CFG_HDR cfghdr130 = {CFG_COLOR,"区号秀颜色",0,99};
__root const int cfg_cs_font_color=0;

__root const CFG_HDR cfghdr140 = {CFG_COLOR,"区号秀背景",0,99};
__root const int CS_NUMBER_BG=2;

__root const CFG_HDR cfghdr131 = {CFG_UINT,"区号秀地址",0,0xFFFFFFFF};
__root const int cfg_cs_adr=0xA0CC0000;

__root const CFG_HDR cfghdr132={CFG_STR_UTF8,"通信录地址",3,127};
__root const char root_dir[128]="0:\\\x1F\xE7\xB3\xBB\xE7\xBB\x9F\\apo\\addr";

__root const CFG_HDR cfghdr133 = {CFG_UINT,"IP号码1",0,0xFFFFFFFF};
__root const int cfg_ip_number1 = 17951;

__root const CFG_HDR cfghdr134 = {CFG_UINT,"IP号码2",0,0xFFFFFFFF};
__root const int cfg_ip_number2 = 12593;

__root const CFG_HDR cfghdr135={CFG_UINT,"音效音量",0,6};
__root const unsigned int volume=6;

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};

/*

__root const CFG_HDR cfghdr_m23={CFG_LEVEL,"Setup Cash",1,0};

 __root const CFG_HDR cfghdr10_0={CFG_STR_WIN1251,"Number for Cash Request",0,31};
 __root const char CASHREQNUM[32]="*#";

 __root const CFG_HDR cfghdr10_000={CFG_UINT,"Auto cash check, hours",0,24};
 __root const unsigned int CHECK_HOURS=1;

 __root const CFG_HDR cfghdr10_01={CFG_CHECKBOX,"Enable Cash Trace",0,0};
 __root const int ENA_CASHTRACE = 1;
 
 __root const CFG_HDR cfghdr10_022={CFG_CHECKBOX,"Enable Op USSD Trace",0,0};
 __root const int ENA_AUTOCASHTRACE = 0; 

 __root const CFG_HDR cfghdr10_08={CFG_CHECKBOX,"Enable Cash Trace logging",0,0};
 __root const int ENA_CASHTRACELOG = 1;
 
 __root const CFG_HDR cfghdr02={CFG_STR_WIN1251,"Cash pattern 0",0,31};
 __root const char CashPat0[32]="alans #hrn";

 __root const CFG_HDR cfghdr10_03={CFG_STR_WIN1251,"Cash pattern 1",0,31};
 __root const char CashPat1[32]="onus #hrn";

 __root const CFG_HDR cfghdr10_04={CFG_STR_WIN1251,"Cash pattern 2",0,31};
 __root const char CashPat2[32]="# hv";

 __root const CFG_HDR cfghdr10_05={CFG_STR_WIN1251,"Cash pattern 3",0,31};
 __root const char CashPat3[32]="# Kb GPRS";

 __root const CFG_HDR cfghdr10_06 = {CFG_STR_UTF8,"Temp file path",0,127};
 __root const char cashTEMP_PATH[128]=DEFAULT_DISK ":\\ZBin\\var\\";

 __root const CFG_HDR cfghdr10_07 = {CFG_STR_UTF8,"Log file",0,127};
 __root const char cashLOG_FILE[128]=DEFAULT_DISK ":\\ZBin\\var\\CallCenter_cash.log";

 __root const CFG_HDR cfghdr10_072 = {CFG_STR_UTF8,"Log format",0,127};
 __root const char cashLOG_Format[128]="%02d.%02d.%04d %02d:%02d %.0s %d %d %d %d";

__root const CFG_HDR cfghdr10_073 = {CFG_CBOX, "Show In", 0, 3};
__root const int cfgShowIn = 1;
__root const CFG_CBOX_ITEM cfgcbox1[3] = {"Lock", "Unlock", "Both"};

 __root const CFG_HDR cfghdr10_19={CFG_COORDINATES,"Idle icon position",0,0};
 __root const unsigned int IDLE_X=0;
 __root const unsigned int IDLE_Y=95;
 
 
 
 
  __root const CFG_HDR cfghdr10_10={CFG_COLOR,"Cash Progressbar 1",0,0};
  __root const char COLOR_CASHPB1[4]={0xFF,0x00,0x00,0x32};

  __root const CFG_HDR cfghdr10_11={CFG_COLOR,"Cash Progressbar 2",0,0};
  __root const char COLOR_CASHPB2[4]={0x00,0xFF,0x00,0x32};

  __root const CFG_HDR cfghdr10_12={CFG_COLOR,"Cash Progressbar 3",0,0};
  __root const char COLOR_CASHPB3[4]={0x00,0xFF,0xFF,0x32};

  __root const CFG_HDR cfghdr10_13={CFG_COLOR,"Cash Progressbar 4",0,0};
  __root const char COLOR_CASHPB4[4]={0xFF,0xFF,0x00,0x32};
  
  __root const CFG_HDR cfghdr10_14={CFG_COLOR,"Font Color",0,0};
  __root const char COLOR_TEXTPB[4]={0xFF,0xFF,0xFF,0x64};
  
  __root const CFG_HDR cfghdr10_15={CFG_UINT,"Font Size",0,100};
  __root const unsigned int TEXT_FONTSZ=FONT_NUMERIC_XSMALL;
  

__root const CFG_HDR cfghdr_m22={CFG_LEVEL,"",0,0};
*/

