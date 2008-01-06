#ifndef _SmartAlerts_H_
  #define _SmartAlerts_H_


extern const char mstyle[];

extern const char vname[];

extern const char name1[];

extern const char callnum[];

extern const char smsnum[];
extern const char content[];

extern const char mname[];


#ifdef NEWSGOLD
#pragma swi_number=0x9E
__swi __arm GetMissedEventCount(unsigned int Event);
#endif

#endif
