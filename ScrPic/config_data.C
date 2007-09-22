#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0 = {CFG_STR_UTF8, "Pic Path", 0, 127};
__root const char pic_path[128] = "";

__root const CFG_HDR cfghdr1 = {CFG_COORDINATES, "Position", 0, 0};
__root const int cfgx = 10;
__root const int cfgy = 50;

__root const CFG_HDR cfghdr2 = {CFG_CHECKBOX, "Enable Locked", 0,2}; 
__root const int ENA_LOCK= 1; 
