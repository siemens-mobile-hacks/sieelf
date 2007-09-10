#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

//÷–Œƒ≈‰÷√Œ™ config_data_c.c

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif 

__root const CFG_HDR cfghdr0={CFG_CBOX,"Enable if keyboard locked",0,2};
__root const int ENA_LOCK=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"Default action",0,3};
__root const int MODE=0;
__root const CFG_CBOX_ITEM cfgcbox2[3]={"Sleep","Shutting down","Reboot",};

__root const CFG_HDR cfghdr12={CFG_CBOX,"Direct unlocked",0,2};
__root const int DIRECT=1;
__root const CFG_CBOX_ITEM cfgcbox12[2]={"Yes","No"};

__root const CFG_HDR cfghdr2={CFG_CBOX,"Change profile when locked",0,2};
__root const int CHANGE_PROFILE=0;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"No","Yes"};

__root const CFG_HDR cfghdr4={CFG_UINT,"lock_profile",0,8};
__root const unsigned int set_pr1=6;

__root const CFG_HDR cfghdr5={CFG_UINT,"unlock_profile",0,8};
__root const unsigned int set_pr2=7;

__root const CFG_HDR cfghdr_m1_1={CFG_LEVEL,"Key settings",1,0};

__root const CFG_HDR cfghdr1_1={CFG_UINT,"Close button",0,65535};
__root const unsigned int CLOSE_BTN=RIGHT_SOFT;

__root const CFG_HDR cfghdr1_2={CFG_UINT,"Call button",0,65535};
__root const unsigned int CALL_BTN=RED_BUTTON;

__root const CFG_HDR cfghdr1_3={CFG_CBOX,"Treatment pressing keys",0,3};
__root const int MODE_KBD=0;
__root const CFG_CBOX_ITEM cfgcbox4[3]={"KEY_DOWN","KEY_UP","LONG_PRESS"};

__root const CFG_HDR cfghdr1_4={CFG_UINT,"Call button (Lock)",0,65535};
__root const unsigned int CALL_BTN2=RED_BUTTON;

__root const CFG_HDR cfghdr1_5={CFG_CBOX,"Treatment pressing keys (Lock)",0,3};
__root const int MODE_KBD2=0;
__root const CFG_CBOX_ITEM cfgcbox5[3]={"KEY_DOWN","KEY_UP","LONG_PRESS"};

__root const CFG_HDR cfghdr_m1_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m2_1={CFG_LEVEL,"Icon settings",1,0};

__root const CFG_HDR cfghdr2_0={CFG_STR_UTF8,"Icon off",0,127};
__root const char ICONS_SD[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\off.png";

__root const CFG_HDR cfghdr2_1={CFG_STR_UTF8,"Icon reboot",0,127};
__root const char ICONS_RB[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\reboot.png";

__root const CFG_HDR cfghdr2_2={CFG_STR_UTF8,"Icon sleep",0,127};
__root const char ICONS_SR[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\sleep.png";

__root const CFG_HDR cfghdr2_3={CFG_STR_UTF8,"Icon unlock",0,127};
__root const char ICONS_UL[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\unlock.png";

__root const CFG_HDR cfghdr_m2_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m3_1={CFG_LEVEL,"Sounds options",1,0};

__root const CFG_HDR cfghdr3_0={CFG_CBOX,"Sounds",0,2};
__root const int SND_ENA=1;
__root const CFG_CBOX_ITEM cfgcbox6[2]={"No","Yes"};

__root const CFG_HDR cfghdr3_1={CFG_UINT,"Volume",0,6};
__root const unsigned int VOLUME=1;

__root const CFG_HDR cfghdr3_2={CFG_STR_UTF8,"Sound off",0,127};
__root const char SND_SD[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\TurnOff\\off.wav";

__root const CFG_HDR cfghdr3_3={CFG_STR_UTF8,"Sound reboot",0,127};
__root const char SND_RB[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\TurnOff\\reboot.wav";

__root const CFG_HDR cfghdr3_4={CFG_STR_UTF8,"Sound sleep",0,127};
__root const char SND_SR[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\TurnOff\\sleep.wav";

__root const CFG_HDR cfghdr3_5={CFG_STR_UTF8,"Sound unlock",0,127};
__root const char SND_UL[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\TurnOff\\unlock.wav";

__root const CFG_HDR cfghdr_m3_0={CFG_LEVEL,"",0,0};

