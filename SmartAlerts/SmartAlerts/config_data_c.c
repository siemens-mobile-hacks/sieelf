#include "..\..\inc\cfg_items.h"
#include "..\..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr_m3={CFG_LEVEL,"定时提醒",1,0};

__root const CFG_HDR cfghdr1_0={CFG_CHECKBOX,"无振动",0,0};
__root const int amelody=0;

__root const CFG_HDR cfghdr1_1={CFG_UINT,"起始时间",0,23};
__root const unsigned int amin=0;

__root const CFG_HDR cfghdr1_2={CFG_UINT,"结束时间",0,23};
__root const unsigned int amax=23;

__root const CFG_HDR cfghdr1_3={CFG_UINT,"提示音效",0,200};
__root const unsigned int melody=60;

__root const CFG_HDR cfghdr1_4={CFG_UINT,"提示分钟",0,59};
__root const unsigned int minute=0;

__root const CFG_HDR cfghdr1_10={CFG_CHECKBOX,"报时模式",0,0};
__root const int talk=0;

__root const CFG_HDR cfghdr1_13={CFG_STR_UTF8,"音频文件夹",0,63};
__root const char sound[64]=DEFAULT_DISK ":\\ZBin\\alerts\\";

__root const CFG_HDR cfghdr1_14={CFG_STR_UTF8,"文件类型",0,3};
__root const char mstyle[4]="wav";


__root const CFG_HDR cfghdr1_15={CFG_CHECKBOX,"音频模式",0,0};
__root const int voice=0;

__root const CFG_HDR cfghdr1_16={CFG_STR_UTF8,"音频位置",0,63};
__root const char vname[64]="";


__root const CFG_HDR cfghdr1_17={CFG_UINT,"音频情景禁用",0,8};
__root const unsigned int filter=0;

__root const CFG_HDR cfghdr1_20={CFG_CHECKBOX,"两次音效",0,0};
__root const int twice=0;

__root const CFG_HDR cfghdr1_21={CFG_UINT,"提示音效2",0,200};
__root const unsigned int melody2=60;

__root const CFG_HDR cfghdr1_22={CFG_UINT,"提示分钟2",0,59};
__root const unsigned int minute2=0;

__root const CFG_HDR cfghdr_m2={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"未接提示",1,0};


__root const CFG_HDR cfghdr3_11={CFG_TIME,"起始时间",0,0};
__root const TTime misstime1={0,0};

__root const CFG_HDR cfghdr3_12={CFG_TIME,"结束时间",0,0};
__root const TTime misstime2={23,59};

#ifdef NEWSGOLD
__root const CFG_HDR cfghdr3_1 = {CFG_CBOX, "未接事件", 0, 4};
__root const int events = 0;
__root const CFG_CBOX_ITEM cfgcbox3_1[4] = {"All", "Calls", "SMS", "Other"};
#endif


__root const CFG_HDR cfghdr3_2={CFG_CHECKBOX,"无音效",0,0};
__root const int mvib=0;

__root const CFG_HDR cfghdr3_3={CFG_UINT,"未接音效",0,200};
__root const unsigned int melodym=60;

__root const CFG_HDR cfghdr3_4={CFG_UINT,"提示间隔",0,59};
__root const unsigned int mminute=1;

__root const CFG_HDR cfghdr3_5={CFG_CHECKBOX,"音频模式",0,0};
__root const int voice2=0;

__root const CFG_HDR cfghdr3_6={CFG_STR_UTF8,"文件位置",0,63};
__root const char mname[64]="";

__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"电量设置",1,0};

__root const CFG_HDR cfghdr4_1={CFG_CHECKBOX,"电量保护",0,0};
__root const int capsave=0;

__root const CFG_HDR cfghdr4_2={CFG_UINT,"保护数值",0,100};
__root const unsigned int capnum=51;

__root const CFG_HDR cfghdr4_3={CFG_UINT,"满电音效",0,200};
__root const unsigned int melody3=51;

__root const CFG_HDR cfghdr4_4={CFG_UINT,"提醒次数",0,20};
__root const unsigned int fcount=3;

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"运行文件",1,0};

__root const CFG_HDR cfghdr5_1={CFG_CHECKBOX,"日期支持",0,0};
__root const int rdate=0;

__root const CFG_HDR cfghdr5_2={CFG_DATE,"日期",0,0};
__root const TDate rundate={2008,1,1};

__root const CFG_HDR cfghdr5_3={CFG_TIME,"时间",0,0};
__root const TTime runtime={0,0};

__root const CFG_HDR cfghdr5_4={CFG_STR_UTF8,"文件位置1",0,63};
__root const char name1[64]="";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"定时电话",1,0};

__root const CFG_HDR cfghdr6_1={CFG_CHECKBOX,"日期支持",0,0};
__root const int cdate=0;

__root const CFG_HDR cfghdr6_2={CFG_DATE,"日期",0,0};
__root const TDate calldate={2008,1,1};

__root const CFG_HDR cfghdr6_3={CFG_TIME,"时间",0,0};
__root const TTime calltime={0,0};

__root const CFG_HDR cfghdr6_4={CFG_STR_UTF8,"电话号码",0,29};
__root const char callnum[30]="";

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"定时短信",1,0};

__root const CFG_HDR cfghdr7_1={CFG_CHECKBOX,"日期支持",0,0};
__root const int sdate=0;

__root const CFG_HDR cfghdr7_2={CFG_DATE,"日期",0,0};
__root const TDate smsdate={2008,1,1};

__root const CFG_HDR cfghdr7_3={CFG_TIME,"时间",0,0};
__root const TTime smstime={0,0};

__root const CFG_HDR cfghdr7_6={CFG_STR_UTF8,"电话号码",0,29};
__root const char smsnum[30]="";

__root const CFG_HDR cfghdr7_7={CFG_STR_UTF8,"短信内容",0,209};
__root const char content[210]="";

__root const CFG_HDR cfghdr_m14={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m17={CFG_LEVEL,"其他设置",1,0};


__root const CFG_HDR cfghdr8_13={CFG_UINT,"音频音量",0,6};
__root const unsigned int volume=6;

__root const CFG_HDR cfghdr8_1={CFG_UINT,"振动次数",0,10};
__root const unsigned int count2=3;

__root const CFG_HDR cfghdr8_2={CFG_UINT,"振动强度",0,100};
__root const unsigned int vibra_pow=100;

__root const CFG_HDR cfghdr8_7={CFG_UINT,"亮度",0,100};
__root const unsigned int light=100;

__root const CFG_HDR cfghdr_m16={CFG_LEVEL,"",0,0};




