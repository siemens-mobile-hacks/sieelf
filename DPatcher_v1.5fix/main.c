#include "..\inc\swilib.h"
#include "main.h"
#include "info.h"

#include "gui\menu.h"
#include "gui\log.h"
#include "gui\fileman.h"

#include "api\high_api.h"

//Main Vars
WSHDR *dp_log_data = 0;
char dp_file_path[FILE_PATH_SIZE];
char dp_bcfg_path[FILE_PATH_SIZE];
char dp_elffolder_path[FILE_PATH_SIZE];
char dp_elf_path[FILE_PATH_SIZE];
char dp_param_path[FILE_PATH_SIZE];

int   MAINCSM_ID = 0;
int   MENUGUI_ID = 0;
int   LOGGUI_ID = 0;
int   FMGUI_ID = 0;
int  *MAINGUI_ID_ADDRESS = 0;

int  CURRENT_GUI = 0; // 0 - Menu, 1 - Log, 2 - FM 

#pragma segment="ELFBEGIN"
void kill_data( void * p, void(*fptr)(void *))
{
  asm("BX R1");
}


void maincsm_oncreate(CSM_RAM *data)
{
  dp_log_data = AllocWS(LOG_SIZE_BUFFER);
  MAIN_CSM *csm = (MAIN_CSM*)data;
  MAINGUI_ID_ADDRESS = (int *)&csm->gui_id;
  GUI_OpenMainMenu();
}

void maincsm_onclose(CSM_RAM *csm)
{
  if (dp_log_data) FreeWS(dp_log_data);
  FreeFileBuffer();
  elf_exit();
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      {
	csm->csm.state=-3;
      }
    }
  }

  return(1);
}

static unsigned short maincsm_name_body[140];
const int minus11=-11;

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),ELF_NAME);
}


int main(char *elfname, char *vkpname, int antihack_id)
{
#ifndef ANTIHACK_DISABLE  
 if (ANTIHACK_ID == antihack_id)
#else
 if (1)
#endif
 {
#ifdef NEWSGOLD
#ifdef ELKA
  if (isnewSGold() == 2)
#else
  if (isnewSGold() == 1)
#endif
#else
  if (isnewSGold() == 0)
#endif
  {
   strcpy(dp_elf_path, elfname);
   strcpy(dp_file_path, vkpname);
   strcpy(dp_param_path, vkpname);
  
   int lenf = strlen(dp_elf_path);
   int leno = strlen(strrchr(dp_elf_path, '\\')+1);
   memcpy(dp_elffolder_path, dp_elf_path, lenf-leno);
   dp_elffolder_path[lenf-leno] = '\0';
   
   if (dp_file_path[1] == ':') CreateFileBuffer();
   FlashInfoSimple();
  
   char dummy[sizeof(MAIN_CSM)];
   LockSched();
   UpdateCSMname();
   MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
   UnlockSched();
   return 1;
  } else
    {
     ShowMSG(1, (int)"Æ½Ì¨´íÎó!");
     elf_exit();
    }
 } else
   {
    BootCoreCleaner();
    elf_exit();
    return -1;
   }
  return 0;
}
