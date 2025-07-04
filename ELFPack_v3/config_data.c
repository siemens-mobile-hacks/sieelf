#include <..\inc\cfg_items.h>
#include "loader3\loader.h"


__root CFG_HDR cfghdr1={CFG_UINT,"Alpha-chan threshold",0,255};
__root unsigned int ALPHA_THRESHOLD=128;

__root CFG_HDR cfghdr2={CFG_UINT,"PNG缓存大小",20,200};
__root unsigned int CACHE_PNG=50;


__root CFG_HDR cfghdr3={CFG_CBOX,"默认位深",0,3};
#if NEWSGOLD || X75
__root unsigned int DEFAULT_COLOR = 2;
#else
__root unsigned int DEFAULT_COLOR = 1;
#endif
__root CFG_CBOX_ITEM cfgcbox3_1[3]={"8位","16位","24位alpha"};


__root CFG_HDR cfghdr4={CFG_CHECKBOX,"子流程加载Daemon",0,2};
__root unsigned int load_in_suproc = 1;


__root CFG_HDR cfghdr5={CFG_STR_UTF8, "img目录路径", 0, 127};
#if NEWSGOLD || X75
__root char IMAGE_FOLDER[128]="4:\\ZBin\\img\\";
#else
__root char IMAGE_FOLDER[128]="0:\\ZBin\\img\\";
#endif

__root CFG_HDR cfghdr6={CFG_STR_UTF8, "Daemons目录路径", 0, 127};
#if NEWSGOLD || X75
__root char DAEMONS_FOLDER[128]="4:\\ZBin\\Daemons\\";
#else
__root char DAEMONS_FOLDER[128]="0:\\ZBin\\Daemons\\";
#endif

__root CFG_HDR cfghdr7={CFG_STR_UTF8, "swi.blib路径", 0, 127};
#if NEWSGOLD || X75
__root char SWIBLIB_WAY[128]="0:\\ZBin\\swi.blib";
#else
__root char SWIBLIB_WAY[128]="0:\\ZBin\\swi.blib";
#endif

__root CFG_HDR cfghdr8={CFG_CHECKBOX,"实时lib缓存清理",0,2};
__root unsigned int realtime_libclean = 1;




