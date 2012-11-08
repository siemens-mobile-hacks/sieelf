#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0 = {CFG_STR_UTF8,"�����ļ���ַ", 0, 127};
#ifndef NEWSGOLD
__root const char FUNC_FILE_NAME[128] = "0:\\ZBin\\etc\\DialExt.tmo";
#else
__root const char FUNC_FILE_NAME[128] = DEFAULT_DISK ":\\ZBin\\etc\\DialExt.txt";
#endif
__root const CFG_HDR cfghdr1 = {CFG_STR_UTF8,"ˢ������", 0, 10};
__root const char REFRESH[11] = "*0#";

__root const CFG_HDR cfghdr2 = {CFG_STR_UTF8,"�˳�����", 0, 10};
__root const char QUIT[11] = "*9#";

__root const CFG_HDR cfghdr3 = {CFG_STR_UTF8,"�����ֻ�", 0, 10};
__root const char REBOOT[11] = "*6#";

__root const CFG_HDR cfghdr4 = {CFG_STR_UTF8,"�ر��ֻ�", 0, 10};
__root const char SHUTOFF[11] = "*8#";

__root const CFG_HDR cfghdr5 = {CFG_CBOX,"��ӭ��Ϣ", 0, 2};
__root const int START_FLAG = 1;
__root const CFG_CBOX_ITEM cfgcbox0[2] = {"����ʾ", "��ʾ"};
