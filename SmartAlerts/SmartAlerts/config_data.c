#include "..\..\inc\cfg_items.h"
#include "..\..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr_m3={CFG_LEVEL,"Alerts",1,0};

__root const CFG_HDR cfghdr1_0={CFG_CHECKBOX,"No Vibra",0,0};
__root const int amelody=0;

__root const CFG_HDR cfghdr1_1={CFG_UINT,"OnlyFrom",0,23};
__root const unsigned int amin=0;

__root const CFG_HDR cfghdr1_2={CFG_UINT,"OnlyTo",0,23};
__root const unsigned int amax=23;


__root const CFG_HDR cfghdr1_3={CFG_UINT,"melody",0,200};
__root const unsigned int melody=60;

__root const CFG_HDR cfghdr1_4={CFG_UINT,"minute",0,59};
__root const unsigned int minute=0;

__root const CFG_HDR cfghdr1_10={CFG_CHECKBOX,"Voice",0,0};
__root const int talk=0;

__root const CFG_HDR cfghdr1_13={CFG_STR_UTF8,"Folder",0,63};
__root const char sound[64]=DEFAULT_DISK ":\\ZBin\\alerts\\";


__root const CFG_HDR cfghdr1_14={CFG_STR_UTF8,"Media style",0,3};
__root const char mstyle[4]="wav";

__root const CFG_HDR cfghdr1_16={CFG_CHECKBOX,"Voice",0,0};
__root const int voice=0;

__root const CFG_HDR cfghdr1_15={CFG_STR_UTF8,"Address",0,63};
__root const char vname[64]="";

__root const CFG_HDR cfghdr1_17={CFG_UINT,"filter",0,8};
__root const unsigned int filter=0;


__root const CFG_HDR cfghdr1_20={CFG_CHECKBOX,"twice",0,0};
__root const int twice=0;

__root const CFG_HDR cfghdr1_21={CFG_UINT,"melody2",0,200};
__root const unsigned int melody2=60;

__root const CFG_HDR cfghdr1_22={CFG_UINT,"minute2",0,59};
__root const unsigned int minute2=0;

__root const CFG_HDR cfghdr_m2={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"Missed Alerts",1,0};


__root const CFG_HDR cfghdr3_11={CFG_TIME,"OnlyFrom",0,0};
__root const TTime misstime1={0,0};

__root const CFG_HDR cfghdr3_12={CFG_TIME,"OnlyTo",0,0};
__root const TTime misstime2={23,59};


#ifdef NEWSGOLD
__root const CFG_HDR cfghdr3_1 = {CFG_CBOX, "Missed event", 0, 4};
__root const int events = 0;
__root const CFG_CBOX_ITEM cfgcbox3_1[4] = {"All", "Calls", "SMS", "Other"};
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




__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"BatterySetting",1,0};


__root const CFG_HDR cfghdr4_1={CFG_CHECKBOX,"BatterySave",0,0};
__root const int capsave=0;

__root const CFG_HDR cfghdr4_2={CFG_UINT,"BatteryNum",0,100};
__root const unsigned int capnum=10;

__root const CFG_HDR cfghdr4_3={CFG_UINT,"melody",0,200};
__root const unsigned int melody3=51;

__root const CFG_HDR cfghdr4_4={CFG_UINT,"count",0,20};
__root const unsigned int fcount=3;



__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Runfile",1,0};


__root const CFG_HDR cfghdr5_1={CFG_CHECKBOX,"Day supply",0,0};
__root const int rdate=0;

__root const CFG_HDR cfghdr5_2={CFG_DATE,"Date",0,0};
__root const TDate rundate={2008,1,1};

__root const CFG_HDR cfghdr5_3={CFG_TIME,"Time",0,0};
__root const TTime runtime={0,0};

__root const CFG_HDR cfghdr5_4={CFG_STR_UTF8,"Address1",0,63};
__root const char name1[64]="";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};





__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"Auto-call",1,0};

__root const CFG_HDR cfghdr6_1={CFG_CHECKBOX,"Day supply",0,0};
__root const int cdate=0;

__root const CFG_HDR cfghdr6_2={CFG_DATE,"Date",0,0};
__root const TDate calldate={2008,1,1};

__root const CFG_HDR cfghdr6_3={CFG_TIME,"Time",0,0};
__root const TTime calltime={0,0};

__root const CFG_HDR cfghdr6_4={CFG_STR_UTF8,"number",0,29};
__root const char callnum[30]="";

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"Auto-Sms",1,0};


__root const CFG_HDR cfghdr7_1={CFG_CHECKBOX,"Day supply",0,0};
__root const int sdate=0;

__root const CFG_HDR cfghdr7_2={CFG_TIME,"Date",0,0};
__root const TDate smsdate={8,1,1};

__root const CFG_HDR cfghdr7_3={CFG_TIME,"Time",0,0};
__root const TTime smstime={0,0};

__root const CFG_HDR cfghdr7_6={CFG_STR_UTF8,"number",0,29};
__root const char smsnum[30]="";

__root const CFG_HDR cfghdr7_7={CFG_STR_UTF8,"content",0,209};
__root const char content[210]="";

__root const CFG_HDR cfghdr_m14={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m17={CFG_LEVEL,"Other",1,0};


__root const CFG_HDR cfghdr8_13={CFG_UINT,"Volume",0,6};
__root const unsigned int volume=6;



__root const CFG_HDR cfghdr8_1={CFG_UINT,"vibra count",0,10};
__root const unsigned int count2=3;

__root const CFG_HDR cfghdr8_2={CFG_UINT,"Vibra power",0,100};
__root const unsigned int vibra_pow=100;

__root const CFG_HDR cfghdr8_7={CFG_UINT,"light",0,100};
__root const unsigned int light=100;


__root const CFG_HDR cfghdr_m18={CFG_LEVEL,"",0,0};
