#include "..\..\inc\swilib.h"

#define FILE_PATH_SIZE  512

#define FM_S_SELECT     "Select"
#define FM_S_EXIT       "Close"
#define FM_S_X          "+"

#define FM_BACK         ".."
#define FM_ROOT         "Root"
#define FM_ERROR        "Error"

#define FM_NAME         "FM"
#define FM_EXT          "*.*"

#define IS_FOLDER 1
#define IS_FILE 0

typedef struct
{
  void *next;
  int is_folder;
  char *fullname;  
  char *name;  
}FLIST;

typedef struct
{
  void *gui;
  int type;
}FVIEW;


void SavePath(void *ed_gui, FLIST *fl);
void GUI_OpenFM(char *path, int type);

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

