#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr_m3={CFG_LEVEL,"Alerts",1,0};

__root const CFG_HDR cfghdr1_0={CFG_CHECKBOX,"No Vibra",0,0};
__root const int amelody=0;


__root const CFG_HDR cfghdr1_3={CFG_UINT,"melody",0,200};
__root const unsigned int melody=60;

__root const CFG_HDR cfghdr1_4={CFG_UINT,"minute",0,59};
__root const unsigned int minute=0;



__root const CFG_HDR cfghdr1_10={CFG_CHECKBOX,"Voice",0,0};
__root const int voice=0;

__root const CFG_HDR cfghdr1_11={CFG_UINT,"volume",0,6};
__root const unsigned int volume=6;

__root const CFG_HDR cfghdr1_12={CFG_UINT,"filter",0,8};
__root const unsigned int filter=0;

__root const CFG_HDR cfghdr1_13={CFG_STR_UTF8,"Address",0,63};
__root const char sound[64]=DEFAULT_DISK ":\\ZBin\\alerts\\";


__root const CFG_HDR cfghdr1_14={CFG_STR_UTF8,"Media style",0,3};
__root const char mstyle[4]="wav";

__root const CFG_HDR cfghdr1_20={CFG_CHECKBOX,"twice",0,0};
__root const int twice=0;

__root const CFG_HDR cfghdr1_21={CFG_UINT,"melody2",0,200};
__root const unsigned int melody2=60;

__root const CFG_HDR cfghdr1_22={CFG_UINT,"minute2",0,59};
__root const unsigned int minute2=0;

__root const CFG_HDR cfghdr_m2={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m5={CFG_LEVEL,"Auto-profile",1,0};

__root const CFG_HDR cfghdr2_0={CFG_CHECKBOX,"merge",0,0};
__root const int merge=0;

__root const CFG_HDR cfghdr2_1={CFG_UINT,"minute",0,59};
__root const unsigned int minute3=0;

__root const CFG_HDR cfghdr2_11={CFG_STR_UTF8,"Day1",0,24};
__root const char day1[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_12={CFG_STR_UTF8,"Day2",0,24};
__root const char day2[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_13={CFG_STR_UTF8,"Day3",0,24};
__root const char day3[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_14={CFG_STR_UTF8,"Day4",0,24};
__root const char day4[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_15={CFG_STR_UTF8,"Day5",0,24};
__root const char day5[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_16={CFG_STR_UTF8,"Day6",24,24};
__root const char day6[25]="000000000000000000000000";

__root const CFG_HDR cfghdr2_17={CFG_STR_UTF8,"Day7",0,24};
__root const char day7[25]="000000000000000000000000";

__root const CFG_HDR cfghdr_m4={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"Missed Alerts",1,0};

__root const CFG_HDR cfghdr3_0={CFG_CHECKBOX,"Missed Alerts",0,0};
__root const int miss=0;

#ifdef NEWSGOLD
__root const CFG_HDR cfghdr3_1 = {CFG_CBOX, "Missed event", 0, 4};
__root const int events = 0;
__root const CFG_CBOX_ITEM cfgcbox0[4] = {"All", "Calls", "SMS", "Other"};
#endif


__root const CFG_HDR cfghdr3_2={CFG_CHECKBOX,"Only vibra",0,0};
__root const int mvib=0;

__root const CFG_HDR cfghdr3_3={CFG_UINT,"melody",0,200};
__root const unsigned int melodym=60;

__root const CFG_HDR cfghdr3_4={CFG_UINT,"Intervall",0,59};
__root const unsigned int mminute=1;

__root const CFG_HDR cfghdr3_5={CFG_CHECKBOX,"Voice",0,0};
__root const int voice2=0;

__root const CFG_HDR cfghdr3_6={CFG_STR_UTF8,"Address",0,63};
__root const char mname[64]="";


__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};




__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"FullBattery",1,0};

__root const CFG_HDR cfghdr4_0={CFG_CHECKBOX,"FullBattery",0,0};
__root const int ch_bat=0;

__root const CFG_HDR cfghdr4_1={CFG_UINT,"melody",0,200};
__root const unsigned int melody3=51;

__root const CFG_HDR cfghdr4_2={CFG_UINT,"count",0,20};
__root const unsigned int fcount=3;



__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Runfile",1,0};

__root const CFG_HDR cfghdr5_0={CFG_CHECKBOX,"Runfile",0,0};
__root const int runfile=0;

__root const CFG_HDR cfghdr5_11={CFG_UINT,"hour1",0,23};
__root const unsigned int rhour1=0;

__root const CFG_HDR cfghdr5_12={CFG_UINT,"minute1",0,59};
__root const unsigned int rminute1=0;

__root const CFG_HDR cfghdr5_13={CFG_STR_UTF8,"Address1",0,63};
__root const char name1[64]="";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};





__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"Auto-call",1,0};

__root const CFG_HDR cfghdr6_1={CFG_CHECKBOX,"call",0,0};
__root const int call=0;

__root const CFG_HDR cfghdr6_2={CFG_UINT,"hour",0,23};
__root const unsigned int chour1=0;

__root const CFG_HDR cfghdr6_3={CFG_UINT,"minute",0,59};
__root const unsigned int cminute1=0;

__root const CFG_HDR cfghdr6_4={CFG_STR_UTF8,"number",0,29};
__root const char num[30]="";

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"Auto-Sms",1,0};

__root const CFG_HDR cfghdr7_0={CFG_CHECKBOX,"Auto-Sms",0,0};
__root const int sms=0;

__root const CFG_HDR cfghdr7_1={CFG_CHECKBOX,"Day supply",0,0};
__root const int sdate=0;

__root const CFG_HDR cfghdr7_2={CFG_UINT,"month",1,12};
__root const unsigned int month=1;

__root const CFG_HDR cfghdr7_3={CFG_UINT,"day",1,31};
__root const unsigned int day=1;

__root const CFG_HDR cfghdr7_4={CFG_UINT,"hour",0,23};
__root const unsigned int shour1=0;

__root const CFG_HDR cfghdr7_5={CFG_UINT,"minute",0,59};
__root const unsigned int sminute1=0;

__root const CFG_HDR cfghdr7_6={CFG_STR_UTF8,"number",0,29};
__root const char snum[30]="";

__root const CFG_HDR cfghdr7_7={CFG_STR_UTF8,"content",0,209};
__root const char content[210]="";

__root const CFG_HDR cfghdr_m14={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m17={CFG_LEVEL,"Other",1,0};


__root const CFG_HDR cfghdr8_11={CFG_UINT,"OnlyFrom",0,23};
__root const unsigned int min=0;

__root const CFG_HDR cfghdr8_12={CFG_UINT,"OnlyTo",0,23};
__root const unsigned int max=23;


__root const CFG_HDR cfghdr8_0={CFG_CHECKBOX,"Vibra",0,0};
__root const int vib=0;

__root const CFG_HDR cfghdr8_1={CFG_UINT,"vibra count",0,10};
__root const unsigned int count2=3;

__root const CFG_HDR cfghdr8_2={CFG_UINT,"Vibra power",0,100};
__root const unsigned int vibra_pow=100;

__root const CFG_HDR cfghdr8_3={CFG_CHECKBOX,"display",0,0};
__root const int dis=0;

__root const CFG_HDR cfghdr8_4={CFG_CHECKBOX,"keyboard",0,0};
__root const int key=0;
#ifndef NEWSGOLD
__root const CFG_HDR cfghdr8_5={CFG_CHECKBOX,"dynlights",0,0};
__root const int dyn=0;
#else
__root const CFG_HDR cfghdr8_6={CFG_CHECKBOX,"lighter",0,0};
__root const int lighter=0;
#endif
__root const CFG_HDR cfghdr8_7={CFG_UINT,"light",0,100};
__root const unsigned int light=100;


__root const CFG_HDR cfghdr_m18={CFG_LEVEL,"",0,0};
