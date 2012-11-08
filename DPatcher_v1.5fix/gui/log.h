#include "..\..\inc\swilib.h"

#define LOG_SIZE_BUFFER 32*1024 
#define LOG_SIZE_PRINT   1*1024

#define LOG_NAME         "Log"

void GUI_OpenLog();
void GUI_OpenLogForPrint(char *log);
void GUI_OpenLogForPrintWithProc(char *log, void post_proc());

void lprint(char *s);
extern void lprintf(char *format, ...);
void lclear();
void lquest(char *quest, int variants, void proc(int a));

void dp_log_locret();
int  dp_log_onkey(GUI *data, GUI_MSG *msg);
void dp_log_ghook(GUI *data, int cmd);

extern WSHDR *dp_log_data;

extern char  dp_file_path[];
extern char  dp_bcfg_path[];
extern char  dp_elf_path[];
extern char  dp_elffolder_path[];
extern char  dp_param_path[];

extern int   MAINCSM_ID;
extern int   MENUGUI_ID;
extern int   LOGGUI_ID;
extern int   FMGUI_ID;
extern int  *MAINGUI_ID_ADDRESS;

extern int   CURRENT_GUI;



