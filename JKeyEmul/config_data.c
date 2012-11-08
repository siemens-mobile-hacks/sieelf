#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"主菜单",1,0};


__root const CFG_HDR cfghdr1_0={CFG_CBOX,"键盘类型",0,3};
__root const int bcfg_ke_keyboard = 0;
__root const CFG_CBOX_ITEM cfgcbox1_0[3]={"SE/Nokia","Motorola", "自定义"};


__root const CFG_HDR cfghdr1_2={CFG_STR_WIN1251,"Java CSM (CSMList)",0,8};
__root const char bcfg_ke_javacsm[9]="A0A630F8";


__root const CFG_HDR cfghdr1_3={CFG_KEYCODE,"激活热键",0,99};
__root const int bcfg_ke_key = 0x30;


__root const CFG_HDR cfghdr1_4={CFG_CBOX,"按键方式",0,2};
__root const int bcfg_ke_keytype = 1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"短按","长按"};



__root const CFG_HDR cfghdr1_5={CFG_CHECKBOX,"通知",0,0};
__root const int bcfg_ke_msg = 1;



__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"自定义设置",1,0};


__root const CFG_HDR cfghdr4_3={CFG_UINT,"左软键(dec)",0,99};
__root const int bcfg_alt_ls=0;


__root const CFG_HDR cfghdr4_4={CFG_UINT,"右软键(dec)",0,99};
__root const int bcfg_alt_rs=0;


__root const CFG_HDR cfghdr4_5={CFG_UINT,"方向上(dec)",0,99};
__root const int bcfg_alt_du=0;


__root const CFG_HDR cfghdr4_6={CFG_UINT,"方向下(dec)",0,99};
__root const int bcfg_alt_dd=0;


__root const CFG_HDR cfghdr4_7={CFG_UINT,"方向左(dec)",0,99};
__root const int bcfg_alt_dl=0;


__root const CFG_HDR cfghdr4_8={CFG_UINT,"方向右(dec)",0,99};
__root const int bcfg_alt_dr=0;


__root const CFG_HDR cfghdr4_9={CFG_UINT,"中键(dec)",0,99};
__root const int bcfg_alt_dc=0;


__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"",0,0};


