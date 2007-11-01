#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
__root const CFG_HDR cfghdr0 = {CFG_CBOX, "Check events", 0, 4};
__root const int cfgEvents = 0;
__root const CFG_CBOX_ITEM cfgcbox0[4] = {"All", "Calls", "SMS", "Other"};
#else
__root const CFG_HDR cfghdr0 = {CFG_CBOX, "Check events",0,3};
__root const int cfgEvents=2;
__root const CFG_CBOX_ITEM cfgcbox0[3]={"Calls","SMS", "Both"};
#endif

__root const CFG_HDR cfghdr9 = {CFG_UINT, "Max events", 0, 20};
__root const unsigned int cfgMaxEv = 5;

__root const CFG_HDR cfghdr1 = {CFG_UINT, "Check interval, sec", 0, 600};
__root const unsigned int cfgInterval = 10;

__root const CFG_HDR cfghdr2 = {CFG_CHECKBOX, "Only when locked", 0, 2};
__root const int cfgLockOnly = 1;

__root const CFG_HDR cfghdr3 = {CFG_UINT, "Blink period, 1/10 sec", 0, 100};
__root const unsigned int cfgPeriod = 2;

__root const CFG_HDR cfghdr4 = {CFG_UINT, "Blink brightness", 0, 100};
__root const unsigned int cfgBright = 50;

__root const CFG_HDR cfghdr5 = {CFG_CHECKBOX, "Blink keyboard", 0, 2};
__root const int cfgKbd = 1;

__root const CFG_HDR cfghdr6 = {CFG_CHECKBOX, "Blink display", 0, 2};
__root const int cfgDispl = 1;

#ifndef NEWSGOLD
__root const CFG_HDR cfghdr7 = {CFG_CHECKBOX, "Blink dynlights", 0, 2};
__root const int cfgDyn = 1;
#else
__root const CFG_HDR cfghdr8 = {CFG_CHECKBOX, "Blink lighter", 0, 2};
__root const int cfgLighter = 1;
#endif

__root const CFG_HDR cfghdr10={CFG_CHECKBOX,"Use vibra",0,2};
__root const int use_vib=1;

__root const CFG_HDR cfghdr11={CFG_UINT,"Vibra power",0,100};
__root const unsigned int vibra_pow=50;

__root const CFG_HDR cfghdr12={CFG_CHECKBOX,"Use sound",0,2};
__root const int use_snd=1;

__root const CFG_HDR cfghdr13={CFG_UINT,"Sound number",0,65535};
__root const unsigned int sndNum=10;
