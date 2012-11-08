#include "..\..\inc\swilib.h"

#ifdef  DEBUG
#define ADD_ITEMS_COUNT   1
#else
#define ADD_ITEMS_COUNT   0
#endif

#define MENU_ITEMS_COUNT  8 + ADD_ITEMS_COUNT

#define MENU_OPEN_LOG     "Open Log"
#define MENU_OPEN_FILE    "Open File"
#define MENU_FINFO        "Flash Info"
#define MENU_APPLY        "Apply Patch"
#define MENU_UNDO         "Undo Patch"
#define MENU_DEBUG        "Parser Test"
#define MENU_ABOUT        "About"
#define MENU_MODENAME_DP  "Mode: DPatcher"
#define MENU_MODENAME_VP  "Mode: VPatcher"
#define MENU_TEST         "DEBUG"
#define MENU_EXIT         "Exit"

#define MENU_S_SELECT     "Select"
#define MENU_S_EXIT       "Exit"

#define MENU_NAME         "Menu"


void GUI_OpenMainMenu();

void dp_menu_ghook(void *data, int cmd);
int  dp_menu_onkey(void *data, GUI_MSG *msg);

void dp_menu_open_item(GUI *data);
void dp_menu_apply_item(GUI *data);
void dp_menu_undo_item(GUI *data);
void dp_menu_about_item(GUI *data);
void dp_menu_exit_item(GUI *data);

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



