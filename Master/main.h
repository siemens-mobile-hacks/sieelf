#ifndef _MAIN_H_
#define _MAIN_H_

#include "master.h"

//#define BUG

#define PTC_SIZE	(2*1024)
#define CONFIG_SIZE	(32*1024)

extern char *ptc_buf;
extern char *cfg_buf;
extern int patch_n;
extern unsigned int MAIN_GUI_ID;
extern unsigned int MAIN_CSM_ID;
extern int PTCFG_CUR;
extern int S_ICONS[3];

#define PATCH_DIR	"0:\\Misc\\Patches\\"
#define PTC_FOLDR	"ptc1\\"


#endif
