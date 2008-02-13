#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_CBOX,"图片",0,4};
__root const int PIC_QUALITY=2;
__root const CFG_CBOX_ITEM cfgcbox0[]={"无","文本（不支持中文）","低质量","高质量"};

__root const CFG_HDR cfghdr01={CFG_STR_UTF8,"主页",0,255};
__root const char homepage[256]="";

__root const CFG_HDR cfghdr1={CFG_STR_GB,"服务器",0,31};
__root const char OM_POST_HOST[32]="80.232.117.10";

__root const CFG_HDR cfghdr2={CFG_UINT,"端口",0,65535};
__root const unsigned int OM_POST_PORT=80;

__root const CFG_HDR cfghdr3={CFG_UINT,"堆大小(kb)",0,65535};
#ifndef  NEWSGOLD
__root const int java_heap_size=768;
#else
__root const int java_heap_size=3*1024;
#endif
