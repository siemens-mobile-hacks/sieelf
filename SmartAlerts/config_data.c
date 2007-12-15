#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"Alerts",1,0};

__root const CFG_HDR cfghdr2_9={CFG_CHECKBOX,"No Vibra",0,0};
__root const int amelody=0;

__root const CFG_HDR cfghdr2_1={CFG_UINT,"OnlyFrom",0,24};
__root const unsigned int min=0;

__root const CFG_HDR cfghdr2_2={CFG_UINT,"OnlyTo",0,24};
__root const unsigned int max=24;

__root const CFG_HDR cfghdr2_3={CFG_UINT,"melody",0,200};
__root const unsigned int melody=60;

__root const CFG_HDR cfghdr2_4={CFG_UINT,"minute",0,59};
__root const unsigned int minute=0;



__root const CFG_HDR cfghdr2_5={CFG_CHECKBOX,"Voice",0,0};
__root const int voice=0;

__root const CFG_HDR cfghdr2_6={CFG_UINT,"volume",0,6};
__root const unsigned int volume=6;

__root const CFG_HDR cfghdr2_7={CFG_UINT,"filter",0,8};
__root const unsigned int filter=0;

__root const CFG_HDR cfghdr2_8={CFG_STR_UTF8,"Address",0,63};
__root const char wav[64]=DEFAULT_DISK ":\\ZBin\\alerts\\";


__root const CFG_HDR cfghdr2_10={CFG_CHECKBOX,"twice",0,0};
__root const int twice=0;

__root const CFG_HDR cfghdr2_11={CFG_UINT,"melody2",0,200};
__root const unsigned int melody2=60;

__root const CFG_HDR cfghdr2_12={CFG_UINT,"minute2",0,59};
__root const unsigned int minute2=0;

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Auto-profile",1,0};

__root const CFG_HDR cfghdr100={CFG_UINT,"minute",0,59};
__root const unsigned int minute3=0;

__root const CFG_HDR cfghdr101={CFG_STR_UTF8,"Day1",0,24};
__root const char day1[25]="000000000000000000000000";

__root const CFG_HDR cfghdr102={CFG_STR_UTF8,"Day2",0,24};
__root const char day2[25]="000000000000000000000000";

__root const CFG_HDR cfghdr103={CFG_STR_UTF8,"Day3",0,24};
__root const char day3[25]="000000000000000000000000";

__root const CFG_HDR cfghdr104={CFG_STR_UTF8,"Day4",0,24};
__root const char day4[25]="000000000000000000000000";

__root const CFG_HDR cfghdr105={CFG_STR_UTF8,"Day5",0,24};
__root const char day5[25]="000000000000000000000000";

__root const CFG_HDR cfghdr106={CFG_STR_UTF8,"Day6",24,24};
__root const char day6[25]="000000000000000000000000";

__root const CFG_HDR cfghdr107={CFG_STR_UTF8,"Day7",0,24};
__root const char day7[25]="000000000000000000000000";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m5={CFG_LEVEL,"FullBattery",1,0};

__root const CFG_HDR cfghdr20={CFG_CHECKBOX,"FullBattery",0,0};
__root const int ch_bat=0;

__root const CFG_HDR cfghdr21={CFG_UINT,"melody",0,200};
__root const unsigned int melody3=51;

__root const CFG_HDR cfghdr_m4={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"Runfile",1,0};

__root const CFG_HDR cfghdr200={CFG_CHECKBOX,"Runfile",0,0};
__root const int runfile=0;

__root const CFG_HDR cfghdr201={CFG_UINT,"hour1",0,23};
__root const unsigned int rhour1=0;

__root const CFG_HDR cfghdr202={CFG_UINT,"minute1",0,59};
__root const unsigned int rminute1=0;

__root const CFG_HDR cfghdr203={CFG_STR_UTF8,"Address1",0,63};
__root const char name1[64]="";

__root const CFG_HDR cfghdr204={CFG_UINT,"hour2",0,23};
__root const unsigned int rhour2=0;

__root const CFG_HDR cfghdr205={CFG_UINT,"minute2",0,59};
__root const unsigned int rminute2=0;

__root const CFG_HDR cfghdr206={CFG_STR_UTF8,"Address2",0,63};
__root const char name2[64]="";

__root const CFG_HDR cfghdr207={CFG_UINT,"hour3",0,23};
__root const unsigned int rhour3=0;

__root const CFG_HDR cfghdr208={CFG_UINT,"minute3",0,59};
__root const unsigned int rminute3=0;

__root const CFG_HDR cfghdr209={CFG_STR_UTF8,"Address3",0,63};
__root const char name3[64]="";

__root const CFG_HDR cfghdr210={CFG_UINT,"hour4",0,23};
__root const unsigned int rhour4=0;

__root const CFG_HDR cfghdr211={CFG_UINT,"minute4",0,59};
__root const unsigned int rminute4=0;

__root const CFG_HDR cfghdr212={CFG_STR_UTF8,"Address4",0,63};
__root const char name4[64]="";

__root const CFG_HDR cfghdr213={CFG_UINT,"hour5",0,23};
__root const unsigned int rhour5=0;

__root const CFG_HDR cfghdr214={CFG_UINT,"minute5",0,59};
__root const unsigned int rminute5=0;

__root const CFG_HDR cfghdr215={CFG_STR_UTF8,"Address5",0,63};
__root const char name5[64]="";


__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m17={CFG_LEVEL,"Missed Alerts",1,0};

__root const CFG_HDR cfghdr5_1={CFG_CHECKBOX,"Missed Alerts",0,0};
__root const int miss=0;

__root const CFG_HDR cfghdr5_2={CFG_CHECKBOX,"Only vibra",0,0};
__root const int mvib=0;

__root const CFG_HDR cfghdr5_3={CFG_UINT,"melody",0,200};
__root const unsigned int melodym=60;

__root const CFG_HDR cfghdr5_4={CFG_UINT,"Intervall",0,59};
__root const unsigned int mminute=1;

__root const CFG_HDR cfghdr_m16={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"Auto-call",1,0};

__root const CFG_HDR cfghdr3_1={CFG_CHECKBOX,"call",0,0};
__root const int call=0;

__root const CFG_HDR cfghdr3_2={CFG_UINT,"hour",0,23};
__root const unsigned int chour1=0;

__root const CFG_HDR cfghdr3_3={CFG_UINT,"minute",0,59};
__root const unsigned int cminute1=0;

__root const CFG_HDR cfghdr3_4={CFG_STR_UTF8,"number",0,29};
__root const char num[30]="";

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"Auto-Sms",1,0};

__root const CFG_HDR cfghdr4_1={CFG_CHECKBOX,"Auto-Sms",0,0};
__root const int sms=0;

__root const CFG_HDR cfghdr4_2={CFG_UINT,"hour",0,23};
__root const unsigned int shour1=0;

__root const CFG_HDR cfghdr4_3={CFG_UINT,"minute",0,59};
__root const unsigned int sminute1=0;

__root const CFG_HDR cfghdr4_4={CFG_STR_UTF8,"number",0,29};
__root const char snum[30]="";

__root const CFG_HDR cfghdr4_5={CFG_STR_UTF8,"Tmo Address",0,63};
__root const char tmo[64]="";

__root const CFG_HDR cfghdr_m14={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m19={CFG_LEVEL,"Vibra setting",1,0};

__root const CFG_HDR cfghdr6_2={CFG_UINT,"vibra count",0,10};
__root const unsigned int count2=3;

__root const CFG_HDR cfghdr6_3={CFG_UINT,"Vibra power",0,100};
__root const unsigned int vibra_pow=100;

__root const CFG_HDR cfghdr_m18={CFG_LEVEL,"",0,0};
