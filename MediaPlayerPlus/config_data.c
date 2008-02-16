#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
#include "lang.h"

__root const CFG_HDR cfghdr0={CFG_COORDINATES, CFG_STR_POS, 0, 0};
__root const unsigned int pos_x=5;
__root const unsigned int pos_y=220;

__root const CFG_HDR cfghdr1={CFG_UINT, CFG_STR_LENGTH, 0, 512};
__root const unsigned int length=240;

__root const CFG_HDR cfghdr2={CFG_UINT, CFG_STR_FONT, 0, 16};
__root const unsigned int font=FONT_SMALL;

__root const CFG_HDR cfghdr3={CFG_COLOR, CFG_STR_COLOR, 0, 0};
__root const char color[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr4={CFG_COLOR, CFG_STR_FRMCOLOR, 0, 0};
__root const char frmcolor[4]={0, 0, 0, 80};

__root const CFG_HDR cfghdr5={CFG_UINT, CFG_STR_ATTR, 0, 512};
__root const unsigned int txt_attr=10;

__root const CFG_HDR cfghdr6={CFG_CHECKBOX, CFG_STR_SHOWLOCK, 0, 2};
__root const int ENA_LOCK=0;
