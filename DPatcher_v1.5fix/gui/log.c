#include "..\..\inc\swilib.h"

#include "..\info.h"

#include "menu.h"
#include "log.h"
#include "fileman.h"

#include "rect_patcher.h"
#include "siemens_unicode.h"

#include "uni.h"
#include <stdarg.h>

static const char percent_t[]="%t";

GUI *ddata;

char log_data[LOG_SIZE_BUFFER];
char log_for_lprint[LOG_SIZE_PRINT];
unsigned int log_size = 0;
int log_for_lprint_status = 0;

void   (*log_post_proc)();
int log_post_proc_status = 0;


void  (*log_quest_proc)(int a);
int log_quest_prov_variants = 0;
int log_quest_proc_status = 0;


void log_recovery()
{
      EDITCONTROL ec;
      ExtractEditControl(ddata,1,&ec);
      WSHDR *log;
      log=AllocWS(ec.pWS->wsbody[0]+strlen(log_data)+10);
      
      char w_per[]="%w";
      wsprintf(log, w_per, ec.pWS);
      
      for (int i=0; log_data[i]!=0; i++) {wsAppendChar(log,char8to16(log_data[i]));}
      
      EDIT_SetTextToEditControl(ddata,1,log);
      REDRAW();   
}


void lprint(char *s)
{
 EDITCONTROL ec;
 WSHDR *log;
 if (CURRENT_GUI == 1)
  {
      ExtractEditControl(ddata,1,&ec);
      log = AllocWS(ec.pWS->wsbody[0]+strlen(s)+10);
      
      char w_per[]="%w";
      wsprintf(log, w_per, ec.pWS);
      
      for (int i=0; s[i]!=0; i++) {wsAppendChar(log,char8to16(s[i]));}
  }
      memcpy((char *)((int)&log_data[0] + log_size), s, strlen(s));
      log_size += strlen(s);
 if (CURRENT_GUI == 1)
  {
      if(wstrlen(log)>LOG_SIZE_BUFFER-1)
       {
         wsRemoveChars(log,0,wstrlen(log)-LOG_SIZE_BUFFER-1 );
         log_size = 0;
       }
  } else 
     {
      if (log_size > LOG_SIZE_BUFFER-1) log_size = 0;
     }
 if (CURRENT_GUI == 1)
  {
      EDIT_SetTextToEditControl(ddata,1,log);
      REDRAW();   
  }
}


void lclear()
{
 if (CURRENT_GUI == 1)
    {
      WSHDR *ws=AllocWS(2);
      char _empty[]="";
      wsprintf(ws,_empty);
      EDIT_SetTextToEditControl(ddata,3,ws);
      FreeWS(ws);
    }
      log_size = 0;
}

void lquest(char *quest, int variants, void proc(int a))
{
   log_quest_proc = proc;
   log_quest_prov_variants = variants;
   log_quest_proc_status = 1;
   lprint(quest);
}


SOFTKEY_DESC dp_log_sk[]=
{
  {0x0018,0x0000,(int)"<C"},
  {0x0001,0x0000,(int)"OK"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB dp_log_skt=
{
  dp_log_sk,0
};



void dp_log_locret(void){}




int dp_log_onkey(GUI *data, GUI_MSG *msg)
{
   //Lock Digital keys & Quest Engine
   if (msg->gbsmsg->submess >= '0' && msg->gbsmsg->submess <= '9')
    {
      if (log_quest_proc_status  && ((log_quest_prov_variants + 0x30) > msg->gbsmsg->submess))
       {
        if (msg->gbsmsg->msg == KEY_DOWN)
         {
          log_quest_prov_variants = 0;
          log_quest_proc_status = 0;
          log_quest_proc(msg->gbsmsg->submess - 0x30);
         } 
       }
      return -1;
    }
  
   //Lock * & #
   if (msg->gbsmsg->submess == '*' || msg->gbsmsg->submess == '#') return -1;
   
   //Clear Log
   if (msg->gbsmsg->submess == GREEN_BUTTON)
    {
     lclear();
     log_for_lprint_status = 0;
     log_post_proc_status = 0;
     log_quest_prov_variants = 0;
     log_quest_proc_status = 0;
     return -1;
    }
 
   //Lock Left Soft
#ifndef NEWSGOLD
   if (msg->gbsmsg->submess == LEFT_SOFT) return -1;
#else
   if (msg->gbsmsg->submess == RIGHT_SOFT) return -1;
#endif

   
   if (msg->gbsmsg->msg==KEY_DOWN)
    { 
 //Lock Right Soft
#ifndef NEWSGOLD
   if (msg->gbsmsg->submess == RIGHT_SOFT || msg->gbsmsg->submess==RED_BUTTON ) 
#else
   if (msg->gbsmsg->submess == LEFT_SOFT || msg->gbsmsg->submess==RED_BUTTON )
#endif
    {
      CURRENT_GUI = 0;
      return(1);
    }
  }
  
  return(0); //Do standart keys
  //1: close
}


void dp_log_ghook(GUI *data, int cmd)
{
  if(cmd==TI_CMD_CREATE)
   {
     ddata=data;
     log_recovery();
     if (log_for_lprint_status) lprint(log_for_lprint);
     log_for_lprint_status = 0;
     if (log_post_proc_status) log_post_proc();
     log_post_proc_status = 0;
     
     DisableIDLETMR();
   }
  if (cmd==TI_CMD_FOCUS)  DisableIDLETMR(); 
}

HEADER_DESC dp_log_header={0, 0, 0, 0, NULL, (int)NULL, LGP_NULL};

INPUTDIA_DESC ed1_desc=
{
  1,
  dp_log_onkey,
  dp_log_ghook,
  (void *)dp_log_locret,
  0,
  &dp_log_skt,
  {0,0,0,0},
  7,
  100,
  101,
  0,

//  0x00000001 - Выровнять по правому краю
//  0x00000002 - Выровнять по центру
//  0x00000004 - Инверсия знакомест
//  0x00000008 - UnderLine
//  0x00000020 - Не переносить слова
//  0x00000200 - bold
  0,
//  0x00000002 - ReadOnly
//  0x00000004 - Не двигается курсор
  0x40000000 // Поменять местами софт-кнопки
};

void GUI_OpenLog()
{
  void *ma=malloc_adr();
  void *eq;  
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  wsprintf(dp_log_data,percent_t,ELF_NAME" v"ELF_VERSION" (c)"ELF_COPYRIGHT"\n-----\n");
  ConstructEditControl(&ec,3,0x40,dp_log_data,16384);
    PrepareEditCOptions(&ec_options);
    SetFontToEditCOptions(&ec_options,1);
    CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);

  patch_header(&dp_log_header, NULL, (int)(int)ELF_NAME" "LOG_NAME);
  patch_input(&ed1_desc);
  LOGGUI_ID = CreateInputTextDialog(&ed1_desc,&dp_log_header,eq,1,0);
  CURRENT_GUI = 1;
}

void GUI_OpenLogForPrint(char *log)
{
  void *ma=malloc_adr();
  void *eq;  
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  wsprintf(dp_log_data,percent_t,ELF_NAME" v"ELF_VERSION" (c)"ELF_COPYRIGHT"\n-----\n");
  ConstructEditControl(&ec,3,0x40,dp_log_data,16384);
    PrepareEditCOptions(&ec_options);
    SetFontToEditCOptions(&ec_options,1);
    CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);
  
  strcpy(log_for_lprint, log);
  log_for_lprint_status = 1;
  
  patch_header(&dp_log_header, NULL, (int)(int)ELF_NAME" "LOG_NAME);
  patch_input(&ed1_desc);
  LOGGUI_ID = CreateInputTextDialog(&ed1_desc,&dp_log_header,eq,1,0);
  CURRENT_GUI = 1;
}

void GUI_OpenLogForPrintWithProc(char *log, void post_proc())
{
  void *ma=malloc_adr();
  void *eq;  
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  wsprintf(dp_log_data,percent_t,ELF_NAME" v"ELF_VERSION" (c)"ELF_COPYRIGHT"\n-----\n");
  ConstructEditControl(&ec,3,0x40,dp_log_data,16384);
    PrepareEditCOptions(&ec_options);
    SetFontToEditCOptions(&ec_options,1);
    CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);
  
  strcpy(log_for_lprint, log);
  log_for_lprint_status = 1;
  
  log_post_proc = post_proc;
  log_post_proc_status = 1;
  
  patch_header(&dp_log_header, NULL, (int)(int)ELF_NAME" "LOG_NAME);
  patch_input(&ed1_desc);
  LOGGUI_ID = CreateInputTextDialog(&ed1_desc,&dp_log_header,eq,1,0);
  CURRENT_GUI = 1;
}
