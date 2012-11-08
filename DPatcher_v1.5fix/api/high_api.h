#include "..\..\inc\swilib.h"

#define WORD_REG(w)            *( (unsigned int   *) ( w ) )
#define HWRD_REG(h)            *( (unsigned short *) ( h ) )
#define BYTE_REG(b)            *( (unsigned char  *) ( b ) )

#define APPLY                  0
#define UNDO                   1

#define YES                    0
#define NO                     1
#define YES_WITH_RP            2

#define DP_MODE                0
#define VP_MODE                1


// ---------- Patcher Mode API ----------
void DPatcher_SetMode();
void VPatcher_SetMode();
int  isPatcherMode();


void FlashInfoSimple();
void FlashInfoLog();
void BootCoreCleaner();

void CreateFileBuffer();
void FreeFileBuffer();

void NucleusStop();
void NucleusResume();

void InitVKPWorks();
void VKP_TestParse();

// ---------- Apply ----------
void VKP_PatchEntry_Apply();
void VKP_PatchConflictQuest_Apply(int a);
void VKP_PatchNoOldDataQuest_Apply(int a);
void VKP_PatchUserQuest_Apply(int a);
void VKP_PatchNoOldDataQuestExt_Apply(int a);

// ---------- Undo ----------
void VKP_PatchEntry_Undo();
void VKP_PatchConflictQuest_Undo(int a);
void VKP_PatchUserQuest_Undo(int a);



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



