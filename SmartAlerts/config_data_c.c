#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr_m5={CFG_LEVEL,"��������",1,0};

__root const CFG_HDR cfghdr20={CFG_CHECKBOX,"��������",0,0};
__root const int ch_bat=0;

__root const CFG_HDR cfghdr21={CFG_UINT,"������Ч",0,200};
__root const unsigned int melody3=51;

__root const CFG_HDR cfghdr_m4={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"�����ļ�",1,0};

__root const CFG_HDR cfghdr200={CFG_CHECKBOX,"�����ļ�",0,0};
__root const int runfile=0;

__root const CFG_HDR cfghdr201={CFG_UINT,"����Сʱ1",0,23};
__root const unsigned int rhour1=0;

__root const CFG_HDR cfghdr202={CFG_UINT,"���з���1",0,59};
__root const unsigned int rminute1=0;

__root const CFG_HDR cfghdr203={CFG_STR_UTF8,"�ļ�Ŀ¼1",0,63};
__root const char name1[64]="";

__root const CFG_HDR cfghdr204={CFG_UINT,"����Сʱ2",0,23};
__root const unsigned int rhour2=0;

__root const CFG_HDR cfghdr205={CFG_UINT,"���з���2",0,59};
__root const unsigned int rminute2=0;

__root const CFG_HDR cfghdr206={CFG_STR_UTF8,"�ļ�Ŀ¼2",0,63};
__root const char name2[64]="";

__root const CFG_HDR cfghdr207={CFG_UINT,"����Сʱ3",0,23};
__root const unsigned int rhour3=0;

__root const CFG_HDR cfghdr208={CFG_UINT,"���з���3",0,59};
__root const unsigned int rminute3=0;

__root const CFG_HDR cfghdr209={CFG_STR_UTF8,"�ļ�Ŀ¼3",0,63};
__root const char name3[64]="";


__root const CFG_HDR cfghdr210={CFG_UINT,"����Сʱ4",0,23};
__root const unsigned int rhour4=0;

__root const CFG_HDR cfghdr211={CFG_UINT,"���з���4",0,59};
__root const unsigned int rminute4=0;

__root const CFG_HDR cfghdr212={CFG_STR_UTF8,"�ļ�Ŀ¼4",0,63};
__root const char name4[64]="";

__root const CFG_HDR cfghdr213={CFG_UINT,"����Сʱ5",0,23};
__root const unsigned int rhour5=0;

__root const CFG_HDR cfghdr214={CFG_UINT,"���з���5",0,59};
__root const unsigned int rminute5=0;

__root const CFG_HDR cfghdr215={CFG_STR_UTF8,"�ļ�Ŀ¼5",0,63};
__root const char name5[64]="";

__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"��ʱ����",1,0};


__root const CFG_HDR cfghdr2_1={CFG_UINT,"��ʼʱ��",0,23};
__root const unsigned int min=0;

__root const CFG_HDR cfghdr2_2={CFG_UINT,"����ʱ��",0,23};
__root const unsigned int max=24;

__root const CFG_HDR cfghdr2_3={CFG_UINT,"��ʾ��Ч",0,200};
__root const unsigned int melody=60;

__root const CFG_HDR cfghdr2_4={CFG_UINT,"��ʾ����",0,59};
__root const unsigned int minute=0;

__root const CFG_HDR cfghdr2_5={CFG_CHECKBOX,"��Ƶģʽ",0,0};
__root const int voice=0;

__root const CFG_HDR cfghdr2_6={CFG_UINT,"��Ƶ����",0,6};
__root const unsigned int volume=6;

__root const CFG_HDR cfghdr2_7={CFG_UINT,"��Ƶ�龰����",0,8};
__root const unsigned int filter=0;

__root const CFG_HDR cfghdr2_8={CFG_STR_UTF8,"��Ƶ��ַ",0,63};
__root const char wav[64]=DEFAULT_DISK ":\\ZBin\\alerts\\";

__root const CFG_HDR cfghdr2_9={CFG_CHECKBOX,"����Ч",0,0};
__root const int amelody=0;

__root const CFG_HDR cfghdr2_10={CFG_CHECKBOX,"������Ч",0,0};
__root const int twice=0;

__root const CFG_HDR cfghdr2_11={CFG_UINT,"��Ч2",0,200};
__root const unsigned int melody2=60;

__root const CFG_HDR cfghdr2_12={CFG_UINT,"����2",0,59};
__root const unsigned int minute2=0;

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"�龰�л�",1,0};

__root const CFG_HDR cfghdr100={CFG_UINT,"�л�����",0,59};
__root const unsigned int minute3=0;

__root const CFG_HDR cfghdr101={CFG_STR_UTF8,"����һ",0,24};
__root const char day1[25]="000000000000000000000000";

__root const CFG_HDR cfghdr102={CFG_STR_UTF8,"���ڶ�",0,24};
__root const char day2[25]="000000000000000000000000";

__root const CFG_HDR cfghdr103={CFG_STR_UTF8,"������",0,24};
__root const char day3[25]="000000000000000000000000";

__root const CFG_HDR cfghdr104={CFG_STR_UTF8,"������",0,24};
__root const char day4[25]="000000000000000000000000";

__root const CFG_HDR cfghdr105={CFG_STR_UTF8,"������",0,24};
__root const char day5[25]="000000000000000000000000";

__root const CFG_HDR cfghdr106={CFG_STR_UTF8,"������",24,24};
__root const char day6[25]="000000000000000000000000";

__root const CFG_HDR cfghdr107={CFG_STR_UTF8,"������",0,24};
__root const char day7[25]="000000000000000000000000";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"��ʱ�绰",1,0};

__root const CFG_HDR cfghdr3_1={CFG_CHECKBOX,"��ʱ�绰",0,0};
__root const int call=0;

__root const CFG_HDR cfghdr3_2={CFG_UINT,"Сʱ",0,23};
__root const unsigned int chour1=0;

__root const CFG_HDR cfghdr3_3={CFG_UINT,"����",0,59};
__root const unsigned int cminute1=0;

__root const CFG_HDR cfghdr3_4={CFG_STR_UTF8,"�绰����",0,29};
__root const char num[30]="";

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"��ʱ����",1,0};

__root const CFG_HDR cfghdr4_1={CFG_CHECKBOX,"��ʱ����",0,0};
__root const int sms=0;

__root const CFG_HDR cfghdr4_2={CFG_UINT,"Сʱ",0,23};
__root const unsigned int shour1=0;

__root const CFG_HDR cfghdr4_3={CFG_UINT,"����",0,59};
__root const unsigned int sminute1=0;

__root const CFG_HDR cfghdr4_4={CFG_STR_UTF8,"�绰����",0,29};
__root const char snum[30]="";

__root const CFG_HDR cfghdr4_5={CFG_STR_UTF8,"���ŵ�ַ",0,63};
__root const char tmo[64]="";

__root const CFG_HDR cfghdr_m14={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m17={CFG_LEVEL,"δ����ʾ",1,0};

__root const CFG_HDR cfghdr5_1={CFG_CHECKBOX,"δ����ʾ",0,0};
__root const int miss=0;

__root const CFG_HDR cfghdr5_2={CFG_CHECKBOX,"����",0,0};
__root const int mvib=0;

__root const CFG_HDR cfghdr5_3={CFG_UINT,"δ����Ч",0,200};
__root const unsigned int melodym=60;

__root const CFG_HDR cfghdr_m16={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m19={CFG_LEVEL,"������",1,0};

__root const CFG_HDR cfghdr6_2={CFG_UINT,"�񶯴���",0,10};
__root const unsigned int count2=3;

__root const CFG_HDR cfghdr6_3={CFG_UINT,"��ǿ��",0,100};
__root const unsigned int vibra_pow=100;

__root const CFG_HDR cfghdr_m18={CFG_LEVEL,"",0,0};
