#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

__root const CFG_HDR cfghdr0 = {CFG_STR_UTF8, "目录", 1, 127};
__root const char fname[128] = "4:\\Maps\\";

__root const CFG_HDR cfghdr61={CFG_UINT,"缩放",0,19};
__root const int Zoom = 13;

__root const CFG_HDR cfghdr65={CFG_CBOX,"地图类型",0,5};
__root const int map_type = 1;
__root const CFG_CBOX_ITEM cfgcbox2[5]={"街道","手机","卫星", "地形", "混合"};
