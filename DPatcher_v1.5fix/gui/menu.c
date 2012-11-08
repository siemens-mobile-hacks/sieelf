#include "..\..\inc\swilib.h"

#include "..\info.h"

#include "menu.h"
#include "log.h"
#include "fileman.h"
#include "rect_patcher.h"

#include "..\api\high_api.h"

char MENU_MODENAME[64]=MENU_MODENAME_DP;


void dp_menu_log_item(GUI *data)
{
 GUI_OpenLog();
}

void dp_menu_open_item(GUI *data)
{
  GUI_OpenFM("Null", IS_FILE);
}

void dp_menu_finfo_item(GUI *data)
{
 GUI_OpenLogForPrintWithProc("Flash Info:\n", FlashInfoLog);
}


void dp_menu_apply_item(GUI *data)
{
 GUI_OpenLogForPrintWithProc("Apply Patch:\n", VKP_PatchEntry_Apply);
}

void dp_menu_undo_item(GUI *data)
{
 GUI_OpenLogForPrintWithProc("Undo Patch:\n", VKP_PatchEntry_Undo);
}

void dp_menu_debug_item(GUI *data)
{
 GUI_OpenLogForPrintWithProc("Parsing:\n", VKP_TestParse);
}

void dp_menu_setmode_item(GUI *data)
{
 if (!isPatcherMode()) 
  {
    VPatcher_SetMode();
    strcpy(MENU_MODENAME, MENU_MODENAME_VP);
  } else
    {
     DPatcher_SetMode();
     strcpy(MENU_MODENAME, MENU_MODENAME_DP);
    }
 RefreshGUI();
}


void dp_menu_exit_item(GUI *data)
{
 CloseCSM(MAINCSM_ID);
}

#ifdef DEBUG

#include "../api/high_api.h"
#include "../api/low_api.h"

void dp_menu_test_item(GUI *data)
{
 NucleusStop();
 
 for (int i = 0; i < 0x40000000; i++); 
 
 NucleusResume();
 
 GUI_OpenLogForPrint("DeBug OK!\n");
}

#endif

HEADER_DESC dp_menu_header={0,0,0,0,NULL,(int)NULL,LGP_NULL};
int dp_menu_softkeys[]={0,1,2};

MENUITEM_DESC dp_menu_items[]=
{
  {NULL,(int)MENU_OPEN_LOG,   LGP_NULL, 0, NULL/*dp_menu_softkeys*/, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)MENU_OPEN_FILE,  LGP_NULL, 0, NULL/*dp_menu_softkeys*/, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)MENU_FINFO,      LGP_NULL, 0, NULL/*dp_menu_softkeys*/, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)MENU_APPLY,      LGP_NULL, 0, NULL/*dp_menu_softkeys*/, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)MENU_UNDO,       LGP_NULL, 0, NULL/*dp_menu_softkeys*/, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)MENU_DEBUG,      LGP_NULL, 0, NULL/*dp_menu_softkeys*/, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)MENU_MODENAME,   LGP_NULL, 0, NULL/*dp_menu_softkeys*/, MENU_FLAG3, MENU_FLAG2},
#ifdef DEBUG
  {NULL,(int)MENU_TEST,       LGP_NULL, 0, NULL/*dp_menu_softkeys*/, MENU_FLAG3, MENU_FLAG2},
#endif
  {NULL,(int)MENU_EXIT,       LGP_NULL, 0, NULL/*dp_menu_softkeys*/, MENU_FLAG3, MENU_FLAG2}
};

MENUPROCS_DESC dp_menu_procs[]={
  dp_menu_log_item,
  dp_menu_open_item,
  dp_menu_finfo_item,
  dp_menu_apply_item,
  dp_menu_undo_item,
  dp_menu_debug_item,
  dp_menu_setmode_item,
#ifdef DEBUG
  dp_menu_test_item,
#endif
  dp_menu_exit_item
};


SOFTKEY_DESC dp_menu_sk[]=
{
  {0x0018,0x0000,(int)MENU_S_SELECT},
  {0x0001,0x0000,(int)MENU_S_EXIT},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB dp_dp_menu_skt=
{
  (SOFTKEY_DESC *)dp_menu_sk,0
};


void dp_menu_ghook(void *data, int cmd)
{
  if (cmd==TI_CMD_CREATE) DisableIDLETMR();
  if (cmd==TI_CMD_FOCUS)  DisableIDLETMR(); 
}


int dp_menu_onkey(void *data, GUI_MSG *msg)
{
 return 0;
}


MENU_DESC dp_menu=
{
  8,
  dp_menu_onkey,
  dp_menu_ghook, NULL,
  dp_menu_softkeys,
  &dp_dp_menu_skt,
  0x10,
  NULL,
  dp_menu_items,
  dp_menu_procs,
  MENU_ITEMS_COUNT
};

void GUI_OpenMainMenu()
{
  patch_header(&dp_menu_header, NULL, (int)ELF_NAME" "MENU_NAME);
  MENUGUI_ID = CreateMenu(0,0, &dp_menu, &dp_menu_header,0,MENU_ITEMS_COUNT,0,0);
 *MAINGUI_ID_ADDRESS = MENUGUI_ID;
  CURRENT_GUI = 0;
}




