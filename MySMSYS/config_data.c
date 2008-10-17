
#include "..\inc\cfg_items.h"
#include "language.h"

__root const CFG_HDR cfghdr0 = {CFG_STR_UTF8, LGP_CFG_MAIN_FOLDER, 3, 127};
__root const char CFG_MAIN_FOLDER[128] = "0:\\ZBin\\MySMSYS\\";

__root const CFG_HDR cfghdr1 = {CFG_STR_UTF8, LGP_CFG_SYSTEM_FOLDER, 3, 127};
__root const char CFG_SYSTEM_FOLDER[128] = "0:\\System\\";

__root const CFG_HDR cfghdr2 = {CFG_CHECKBOX, LGP_CFG_ENA_AUTO_SAF, 0, 3};
__root const int CFG_ENA_AUTO_SAF = 1;

__root const CFG_HDR cfghdr4 = {CFG_CHECKBOX, LGP_CFG_ENA_SAVE_SENT, 0, 3};
__root const int CFG_ENA_SAVE_SENT = 1;

__root const CFG_HDR cfghdr5 = {CFG_CHECKBOX, LGP_CFG_ENA_AUTO_DEL_RP, 0, 3};
__root const int CFG_ENA_AUTO_DEL_RP = 1;

__root const CFG_HDR cfghdr6 = {CFG_CHECKBOX, LGP_CFG_ENA_EXIT_SAVE_DRAFT, 0, 3};
__root const int CFG_ENA_EXIT_SAVE_DRAFT = 1;

__root const CFG_HDR cfghdr3 = {CFG_CBOX, LGP_CFG_EXPORT_CHARSET, 0, 2};
__root const int CFG_EXPORT_CHARSET = 1;
#ifdef LANG_CN
__root const CFG_CBOX_ITEM cfgcbox0[2] = {"ASCII", "UTF8"};
#else
__root const CFG_CBOX_ITEM cfgcbox0[2] = {"WIN1251", "UTF8"};
#endif
__root const CFG_HDR cfghdr1_0 = {CFG_LEVEL, LGP_CFG_NOTIFY_SET, 1, 0};

__root const CFG_HDR cfghdr1_1 = {CFG_CHECKBOX, LGP_CFG_ENA_NOTIFY, 0, 3};
__root const int CFG_ENA_NOTIFY = 1;

__root const CFG_HDR cfghdr1_2 = {CFG_UINT, LGP_CFG_VIBRA_POWER, 0, 100};
__root const unsigned int CFG_VIBRA_POWER = 50;

__root const CFG_HDR cfghdr1_3 = {CFG_UINT, LGP_CFG_NOTIFY_TIME, 0, 100};
__root const int CFG_NOTIFY_TIME = 10;

__root const CFG_HDR cfghdr1_4 = {CFG_CHECKBOX, LGP_CFG_ENA_NEWSMS_ICON, 0, 3};
__root const int CFG_ENA_NEWSMS_ICON = 1;

__root const CFG_HDR cfghdr1_5= {CFG_STR_UTF8, LGP_CFG_ICONNEW_PATH, 3, 127};
__root const char CFG_ICONNEW_PATH[128] = "0:\\ZBin\\MySMSYS\\new.png";

__root const CFG_HDR cfghdr1_6= {CFG_COORDINATES, LGP_CFG_ICONNEW_POS, 0, 0};
__root const unsigned int CFG_ICONNEW_POS_X = 2;
__root const unsigned int CFG_ICONNEW_POS_Y = 140;

__root const CFG_HDR cfghdr1_7 = {CFG_CHECKBOX, LGP_CFG_ENA_SOUND, 0, 3};
__root const int CFG_ENA_SOUND = 1;

__root const CFG_HDR cfghdr1_8= {CFG_STR_UTF8, LGP_CFG_SOUND_PATH, 3, 127};
__root const char CFG_SOUND_PATH[128] = "2:\\Default\\MessageMelody.wav";

__root const CFG_HDR cfghdr1_a = {CFG_UINT, LGP_CFG_SOUND_VOL, 0, 10};
__root const unsigned int CFG_SOUND_VOL = 5;

__root const CFG_HDR cfghdr1_9 = {CFG_LEVEL, "", 0, 0};



