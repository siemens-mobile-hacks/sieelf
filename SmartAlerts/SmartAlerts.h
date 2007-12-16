#ifndef _SmartAlerts_H_
  #define _SmartAlerts_H_

extern const int ch_bat;
extern const unsigned int melody3;

extern const unsigned int melody;
extern const unsigned int min;
extern const unsigned int max;
extern const unsigned int minute;

extern const int voice;
extern const unsigned int volume;
extern const unsigned int filter;
extern const char wav[64];
extern const int amelody;

extern const int twice;
extern const unsigned int minute2;
extern const unsigned int melody2;

extern const unsigned int minute3;
extern const int merge;
extern const char day1[25];
extern const char day2[25];
extern const char day3[25];
extern const char day4[25];
extern const char day5[25];
extern const char day6[25];
extern const char day7[25];


extern const int runfile;
extern const char name1[64];
extern const unsigned int rhour1;
extern const unsigned int rminute1;
/*
extern const char name2[64];
extern const unsigned int rhour2;
extern const unsigned int rminute2;
extern const char name3[64];
extern const unsigned int rhour3;
extern const unsigned int rminute3;
extern const char name4[64];
extern const unsigned int rhour4;
extern const unsigned int rminute4;
extern const char name5[64];
extern const unsigned int rhour5;
extern const unsigned int rminute5;
*/

extern const int call;
extern const char num[30];
extern const unsigned int chour1;
extern const unsigned int cminute1;

extern const int sms;
extern const char snum[30];
extern const unsigned int shour1;
extern const unsigned int sminute1;
extern const char tmo[64];

extern const int miss;
extern const int mvib;
extern const unsigned int melodym;
extern const unsigned int mminute;

extern const unsigned int count2;
extern const unsigned int vibra_pow;


#ifdef NEWSGOLD
#pragma swi_number=0x9E
__swi __arm GetMissedEventCount(unsigned int Event);
#endif

#endif
