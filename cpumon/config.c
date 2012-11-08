#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"


#ifdef ELKA
__root const CFG_HDR cfghdr0 = {CFG_RECT, "ÏÔÊ¾Î»ÖÃ", 0, 239};

__root const RECT position = {65,108,131,153};
#else
__root const CFG_HDR cfghdr0 = {CFG_RECT, "ÏÔÊ¾Î»ÖÃ", 0, 239};
__root const RECT position = {110,224,239,280};
#endif

//KeyLock
__root const CFG_HDR cfghdr7 = {CFG_CBOX, "ÏÔÊ¾ÓÚ", 0, 3};
__root const int cfgShowIn = 2;
__root const CFG_CBOX_ITEM cfgcbox1[3] = {"Ëø¼üÅÌ", "Î´Ëø¼ü", "È«²¿"};

//© string
__root const CFG_HDR cfghdr8 = {CFG_CBOX, "¿ªÊ¼Ê±ÏÔÊ¾°æÈ¨", 0, 2};
__root const int cfgStTxt = 1;
__root const CFG_CBOX_ITEM cfgcbox2[2] = {"·ñ", "ÊÇ"};

//Update Time
__root const CFG_HDR cfghdr9 = {CFG_UINT, "Ë¢ÐÂÊ±¼ä(1/10Ãë)", 0, 50};
__root const unsigned int cfgUpTime = 10;

//Sensors...
//CPU
__root const CFG_HDR cfghdr1={CFG_LEVEL,"CPUÍ¼»­",1,0};
  __root const CFG_HDR cfghdr5 = {CFG_CBOX, "Í¼»­ÀàÐÍ", 0, 3};
  __root const int cfgLoadType = 2;
  __root const CFG_CBOX_ITEM cfgcbox3[3] = {"ÎÞ", "ÏßÐÍ", "¹ÌÌå"};

  __root const CFG_HDR cfghdr11 = {CFG_UINT, "¸üÐÂÊ±¼ä", 1, 500};
  __root const unsigned int cfgCpuDiv = 1;

  __root const CFG_HDR cfghdr4_1 = {CFG_COLOR, "ÑÕÉ«208MHz", 0, 0};
  __root const char cfgLoad208[4] = {0,0xff,0,100};

  __root const CFG_HDR cfghdr4_2 = {CFG_COLOR, "ÑÕÉ«104MHz", 0, 0};
  __root const char cfgLoad104[4] = {0,0xd0,0,100};

  __root const CFG_HDR cfghdr4_4 = {CFG_COLOR, "ÑÕÉ«52MHz", 0, 0};
  __root const char cfgLoad52[4] = {0,0xa0,0,100};
__root const CFG_HDR cfghdr3={CFG_LEVEL,"",0,0};

//RAM
__root const CFG_HDR cfghdr2={CFG_LEVEL,"RAMÍ¼»­",1,0};
  __root const CFG_HDR cfghdr6 = {CFG_CBOX, "Í¼»­ÀàÐÍ", 0, 3};
  __root const int cfgRamType = 1;
  __root const CFG_CBOX_ITEM cfgcbox4[3] = {"ÎÞ", "ÏßÐÍ", "¹ÌÌå"};

  __root const CFG_HDR cfghdr10 = {CFG_UINT, "¸üÐÂÊ±¼ä", 1, 500};
  __root const unsigned int cfgRamDiv = 10;

  __root const CFG_HDR cfghdr4_3 = {CFG_COLOR, "ÑÕÉ«", 0, 0};
  __root const char cfgFreeRAM[4] = {0,0,0xff,100};
__root const CFG_HDR cfghdr4={CFG_LEVEL,"",0,0};

//Net
__root const CFG_HDR cfghdr12={CFG_LEVEL,"NetÍ¼»­",1,0};
  __root const CFG_HDR cfghdr13 = {CFG_CBOX, "Í¼»­ÀàÐÍ", 0, 3};
  __root const int cfgNetType = 1;
  __root const CFG_CBOX_ITEM cfgcbox5[3] = {"ÎÞ", "ÏßÐÍ", "¹ÌÌå"};

  __root const CFG_HDR cfghdr14 = {CFG_UINT, "¸üÐÂÊ±¼ä", 1, 500};
  __root const unsigned int cfgNetDiv = 1;

  __root const CFG_HDR cfghdr151 = {CFG_COLOR, "ÑÕÉ«900Mhz", 0, 0};
  __root const char cfgNet900[4] = {0xff,0x70,0,100};

  __root const CFG_HDR cfghdr152 = {CFG_COLOR, "ÑÕÉ«e900Mhz", 0, 0};
  __root const char cfgNete900[4] = {0xff,0xa0,0,100};

  __root const CFG_HDR cfghdr153 = {CFG_COLOR, "ÑÕÉ«1800Mhz", 0, 0};
  __root const char cfgNet1800[4] = {0xff,0xff,0,100};

__root const CFG_HDR cfghdr16={CFG_LEVEL,"",0,0};

//Disk
__root const CFG_HDR cfghdr17={CFG_LEVEL,"´ÅÅÌÍ¼»­",1,0};
  __root const CFG_HDR cfghdr18 = {CFG_CBOX, "Í¼»­ÀàÐÍ", 0, 3};
  __root const int cfgDiskType = 2;
  __root const CFG_CBOX_ITEM cfgcbox6[3] = {"ÎÞ", "ÏßÐÍ", "¹ÌÌå"};

  __root const CFG_HDR cfghdr19 = {CFG_UINT, "¸üÐÂÊ±¼ä", 1, 5000};
  __root const unsigned int cfgDiskDiv = 1000;

  __root const CFG_HDR cfghdr20 = {CFG_COLOR, "ÑÕÉ«", 0, 0};
  __root const char cfgDisk[4] = {0,0xaa,0xaa,100};
__root const CFG_HDR cfghdr21={CFG_LEVEL,"",0,0};
