#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr_m3={CFG_LEVEL,"定时提醒",1,0};

__root const CFG_HDR cfghdr1_0={CFG_CHECKBOX,"无振动",0,0};
__root const int amelody=0;

__root const CFG_HDR cfghdr1_1={CFG_UINT,"起始时间",0,23};
__root const unsigned int min=0;

__root const CFG_HDR cfghdr1_2={CFG_UINT,"结束时间",0,23};
__root const unsigned int max=23;

__root const CFG_HDR cfghdr1_3={CFG_UINT,"提示音效",0,200};
__root const unsigned int melody=60;

__root const CFG_HDR cfghdr1_4={CFG_UINT,"提示分钟",0,59};
__root const unsigned int minute=0;



__root const CFG_HDR cfghdr1_10={CFG_CHECKBOX,"音频模式",0,0};
__root const int voice=0;

__root const CFG_HDR cfghdr1_11={CFG_UINT,"音频音量",0,6};
__root const unsigned int volume=6;

__root const CFG_HDR cfghdr1_12={CFG_UINT,"音频情景禁用",0,8};
__root const unsigned int filter=0;

__root const CFG_HDR cfghdr1_13={CFG_STR_UTF8,"音频地址",0,63};
__root const char sound[64]=DEFAULT_DISK ":\\ZBin\\alerts\\";

__root const CFG_HDR cfghdr1_14={CFG_STR_UTF8,"文件类型",0,3};
__root const char mstyle[4]="wav";

__root const CFG_HDR cfghdr1_20={CFG_CHECKBOX,"两次音效",0,0};
__root const int twice=0;

__root const CFG_HDR cfghdr1_21={CFG_UINT,"提示音效2",0,200};
__root const unsigned int melody2=60;

__root const CFG_HDR cfghdr1_22={CFG_UINT,"提示分钟2",0,59};
__root const unsigned int minute2=0;

__root const CFG_HDR cfghdr_m2={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m5={CFG_LEVEL,"情景切换",1,0};

__root const CFG_HDR cfghdr2_0={CFG_CHECKBOX,"五天模式",0,0};
__root const int merge=0;

__root const CFG_HDR cfghdr2_1={CFG_UINT,"切换分钟",0,59};
__root const unsigned int minute3=0;


__root const CFG_HDR cfghdr2_11={CFG_STR_UTF8,"星期一",0,24};
__root const char day1[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_12={CFG_STR_UTF8,"星期二",0,24};
__root const char day2[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_13={CFG_STR_UTF8,"星期三",0,24};
__root const char day3[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_14={CFG_STR_UTF8,"星期四",0,24};
__root const char day4[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_15={CFG_STR_UTF8,"星期五",0,24};
__root const char day5[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_16={CFG_STR_UTF8,"星期六",24,24};
__root const char day6[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_17={CFG_STR_UTF8,"星期日",0,24};
__root const char day7[25]="000000000000000000000000";

__root const CFG_HDR cfghdr_m4={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"未接提示",1,0};

__root const CFG_HDR cfghdr3_0={CFG_CHECKBOX,"未接提示",0,0};
__root const int miss=0;

#ifdef NEWSGOLD
__root const CFG_HDR cfghdr3_1 = {CFG_CBOX, "未接事件", 0, 4};
__root const int events = 0;
__root const CFG_CBOX_ITEM cfgcbox0[4] = {"All", "Calls", "SMS", "Other"};
#endif


__root const CFG_HDR cfghdr3_2={CFG_CHECKBOX,"无音效",0,0};
__root const int mvib=0;

__root const CFG_HDR cfghdr3_3={CFG_UINT,"未接音效",0,200};
__root const unsigned int melodym=60;

__root const CFG_HDR cfghdr3_4={CFG_UINT,"提示间隔",0,59};
__root const unsigned int mminute=1;

__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"满电提醒",1,0};

__root const CFG_HDR cfghdr4_0={CFG_CHECKBOX,"满电提醒",0,0};
__root const int ch_bat=0;

__root const CFG_HDR cfghdr4_1={CFG_UINT,"满电音效",0,200};
__root const unsigned int melody3=51;

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"运行文件",1,0};

__root const CFG_HDR cfghdr5_0={CFG_CHECKBOX,"运行文件",0,0};
__root const int runfile=0;

__root const CFG_HDR cfghdr5_11={CFG_UINT,"运行小时1",0,23};
__root const unsigned int rhour1=0;

__root const CFG_HDR cfghdr5_12={CFG_UINT,"运行分钟1",0,59};
__root const unsigned int rminute1=0;

__root const CFG_HDR cfghdr5_13={CFG_STR_UTF8,"文件位置1",0,63};
__root const char name1[64]="";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"定时电话",1,0};

__root const CFG_HDR cfghdr6_1={CFG_CHECKBOX,"定时电话",0,0};
__root const int call=0;

__root const CFG_HDR cfghdr6_2={CFG_UINT,"小时",0,23};
__root const unsigned int chour1=0;

__root const CFG_HDR cfghdr6_3={CFG_UINT,"分钟",0,59};
__root const unsigned int cminute1=0;

__root const CFG_HDR cfghdr6_4={CFG_STR_UTF8,"电话号码",0,29};
__root const char num[30]="";

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"定时短信",1,0};

__root const CFG_HDR cfghdr7_1={CFG_CHECKBOX,"定时短信",0,0};
__root const int sms=0;

__root const CFG_HDR cfghdr7_2={CFG_UINT,"小时",0,23};
__root const unsigned int shour1=0;

__root const CFG_HDR cfghdr7_3={CFG_UINT,"分钟",0,59};
__root const unsigned int sminute1=0;

__root const CFG_HDR cfghdr7_4={CFG_STR_UTF8,"电话号码",0,29};
__root const char snum[30]="";

__root const CFG_HDR cfghdr7_5={CFG_STR_UTF8,"短信地址",0,63};
__root const char tmo[64]="";

__root const CFG_HDR cfghdr_m14={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m17={CFG_LEVEL,"其他设置",1,0};

__root const CFG_HDR cfghdr8_0={CFG_CHECKBOX,"振动",0,0};
__root const int vib=0;

__root const CFG_HDR cfghdr8_1={CFG_UINT,"振动次数",0,10};
__root const unsigned int count2=3;

__root const CFG_HDR cfghdr8_2={CFG_UINT,"振动强度",0,100};
__root const unsigned int vibra_pow=100;

__root const CFG_HDR cfghdr8_3={CFG_CHECKBOX,"屏幕",0,0};
__root const int dis=0;

__root const CFG_HDR cfghdr8_4={CFG_CHECKBOX,"键盘",0,0};
__root const int key=0;
#ifndef NEWSGOLD
__root const CFG_HDR cfghdr8_5={CFG_CHECKBOX,"动感",0,0};
__root const int dyn=0;
#else
__root const CFG_HDR cfghdr8_6={CFG_CHECKBOX,"闪灯",0,0};
__root const int lighter=0;
#endif
__root const CFG_HDR cfghdr8_7={CFG_UINT,"light",0,100};
__root const unsigned int light=100;

__root const CFG_HDR cfghdr_m16={CFG_LEVEL,"",0,0};
