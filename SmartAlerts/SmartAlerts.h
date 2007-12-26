#ifndef _SmartAlerts_H_
  #define _SmartAlerts_H_

extern const int ch_bat;
extern const unsigned int melody3;
extern const unsigned int fcount;

extern const int amelody;
extern const unsigned int melody;
extern const unsigned int minute;

extern const int voice;
extern const unsigned int volume;
extern const unsigned int filter;
extern const char sound[];
extern const char mstyle[];


extern const int twice;
extern const unsigned int minute2;
extern const unsigned int melody2;

extern const unsigned int minute3;
extern const int merge;
extern const char day1[];
extern const char day2[];
extern const char day3[];
extern const char day4[];
extern const char day5[];
extern const char day6[];
extern const char day7[];


extern const int runfile;
extern const int rdate;
extern const TDate rundate;
extern const TTime runtime;
extern const char name1[];


extern const int call;
extern const int cdate;
extern const TDate calldate;
extern const TTime calltime;
extern const char callnum[];


extern const int sms;
extern const int sdate;
extern const TDate smsdate;
extern const TTime smstime;
extern const char smsnum[];
extern const char content[];

extern const int miss;
#ifdef NEWSGOLD
extern const int events;
#endif
extern const int mvib;
extern const unsigned int melodym;
extern const unsigned int mminute;
extern const int voice2;
extern const char mname[];


extern const unsigned int min;
extern const unsigned int max;
extern const int vib;
extern const unsigned int count2;
extern const unsigned int vibra_pow;
extern const int dis;
extern const int key;
#ifndef NEWSGOLD
extern const int dyn;
#else
extern const int lighter;
#endif
extern const unsigned int light;


#ifdef NEWSGOLD
#pragma swi_number=0x9E
__swi __arm GetMissedEventCount(unsigned int Event);
#endif

#endif
