#include "..\..\inc\cfg_items.h"
#include "..\..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr_m3={CFG_LEVEL,"Alerts",1,0};

__root const CFG_HDR cfghdr1_13={CFG_STR_UTF8,"Folder",0,63};
__root const char sound[64]=DEFAULT_DISK ":\\ZBin\\alerts\\";

__root const CFG_HDR cfghdr1_14={CFG_STR_UTF8,"Media style",0,3};
__root const char mstyle[4]="wav";

__root const CFG_HDR cfghdr1_15={CFG_STR_UTF8,"Address",0,63};
__root const char vname[64]="";

__root const CFG_HDR cfghdr_m2={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"Missed Alerts",1,0};

__root const CFG_HDR cfghdr3_6={CFG_STR_UTF8,"Address",0,63};
__root const char mname[64]="";

__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};




__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Runfile",1,0};

__root const CFG_HDR cfghdr5_4={CFG_STR_UTF8,"Address",0,63};
__root const char name1[64]="";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};





__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"Auto-call",1,0};

__root const CFG_HDR cfghdr6_4={CFG_STR_UTF8,"number",0,29};
__root const char callnum[30]="";

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"Auto-Sms",1,0};

__root const CFG_HDR cfghdr7_6={CFG_STR_UTF8,"number",0,29};
__root const char smsnum[30]="";

__root const CFG_HDR cfghdr7_7={CFG_STR_UTF8,"content",0,209};
__root const char content[210]="";

__root const CFG_HDR cfghdr_m14={CFG_LEVEL,"",0,0};

