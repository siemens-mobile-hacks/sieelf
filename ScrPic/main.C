#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"


const int minus11=-11;
extern void kill_data(void *p, void (*func_p)(void *));

extern const int ENA_LOCK;
extern const int cfgx;
extern const int cfgy;
extern const char pic_path[];

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  #define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM *icsm;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"Screen Pic config updated!");
      InitConfig();
    }
  }
  if(ENA_LOCK||IsUnlocked())
  {
    icsm=FindCSMbyID(CSM_root()->idle_id);
    if (icsm)                                                                                                                                                                                                                                                       
    {                                                                                                                                                                                                                                                               
      if (IsGuiOnTop(idlegui_id(icsm)))                                                                                                                                                                                                                          
      {                                                                                                                                                                                                                                                             
        GUI *igui=GetTopGUI();                                                                                                                                                                       
        if (igui)                                                                                                                                                                                                                                                   
        {                                                                                                                                                                                                                                                           
          #ifdef ELKA                                                                                                                                                                                                                                               
          void *canvasdata = BuildCanvas();                                                                                                                                                                                                                         
          {                                                                                                                                                                                                                                                         
          #else                                                                                                                                                                                                                                                     
          void *idata = GetDataOfItemByID(igui, 2);                                                                                                                                                                                                                 
          if (idata)                                                                                                                                                                                                                                                
          {                                                                                                                                                                                                                                                         
            void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];                                                                                                                                                                                        
          #endif                                                                                                                                                                                                                                                    
              FSTATS fstats;                                                                                                                                                                                                                                        
              unsigned int err;                                                                                                                                                                                                                                     
              if (GetFileStats(pic_path,&fstats,&err)!=-1)                                                                                                                                                                                                          
              {                                                                                                                                                                                                                                                     
                DrawCanvas(canvasdata, cfgx, cfgy, cfgx + GetImgWidth((int)pic_path), cfgy + GetImgHeight((int)pic_path), 1);                                                                                                                                       
                DrawImg(cfgx, cfgy, (int)pic_path);                                                                                                                                                                                                                 
              }                                                                                                     
          }                                                                                                                                                                                                                                                         
        }                                                                                                                                                                                                                                                           
      }
    }
  }                                                                                                                                               
  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
}

static void maincsm_onclose(CSM_RAM *csm)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static unsigned short maincsm_name_body[140];

static const struct
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Screen Pic");
}

int main(void)
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();  
  LockSched();
  
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  
  UnlockSched();  
  return 0;
}

