#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include "..\inc\xtask_ipc.h"
#include "swaper.h"

#ifdef NEWSGOLD
#define USE_ONE_KEY
#endif

volatile int SHOW_LOCK;

CSM_DESC icsmd;
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);


CSM_RAM *under_idle;

extern const int ACTIVE_KEY;
extern const int ACTIVE_KEY_STYLE;
extern const int RED_BUT_MODE;
extern const int ENA_LONG_PRESS;
extern const int ENA_LOCK;
extern int my_csm_id;

extern void kill_data(void *p, void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

extern void ShowMenu(void);

// -1 - XTask GUI present
// 0 - XTask GUI absent
// 1 - IBUT longpressed, ready for exit
int mode;

// 0 - no press
// 1 - long press REDBUT
int mode_red;

// 0 - no press
// 1 - long press ENTER_BUTTON
// 2 - disable KEY_UP process
int mode_enter;

int my_keyhook(int submsg, int msg)
{
#ifdef NEWSGOLD
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((submsg==RED_BUTTON)&&(RED_BUT_MODE))
  {
    if ((CSM_root()->csm_q->csm.last==icsm)||(IsCalling())) //(IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))
    {
      if (msg==KEY_UP)
      {
        if (mode_red!=2)
        {
          mode_red=0;
          return KEYHOOK_BREAK;
        }
      }
      mode_red=2; //Lozhim to release
    }
    else
    {
      if (msg==KEY_DOWN)
      {
        if (mode_red==1)
        {
          mode_red=0;
          return KEYHOOK_NEXT; //Long press, continue with REDB PRESS
        }
      }
      if (msg==KEY_UP)
      {
        if (mode_red)
        {
          mode_red=0; //Release after longpress
          return KEYHOOK_NEXT;
        }
        else
        {
	  //Release after short press
          if (RED_BUT_MODE==1)
          {
            GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT);
          }
          else
          {
            if (!my_csm_id)
            {
              CSMtoTop(CSM_root()->idle_id,-1);
            }
          }
        }
      }
      if (msg==LONG_PRESS)
      {
        mode_red=1;
        GBS_SendMessage(MMI_CEPID,KEY_DOWN,RED_BUTTON);
      }
      return KEYHOOK_BREAK;
    }
  }
#endif
  if ((ACTIVE_KEY_STYLE==1)||(ENA_LONG_PRESS==3))
  {
    if (submsg!=ACTIVE_KEY) return KEYHOOK_NEXT;
    /*if (my_csm_id)
    {
      if (((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=my_csm_id)
      {
        CloseCSM(my_csm_id);
      }
      return KEYHOOK_NEXT;
    }*/
    switch(msg)
    {
    case KEY_DOWN:
      if (mode_enter==2)
      {
        GBS_SendMessage(MMI_CEPID,KEY_UP,ACTIVE_KEY);
        return KEYHOOK_NEXT;
      }
      mode_enter=0;
      return KEYHOOK_BREAK;
    case KEY_UP:
      if (mode_enter==0)
      {
        mode_enter=2;
        GBS_SendMessage(MMI_CEPID,KEY_DOWN,ACTIVE_KEY);
        return KEYHOOK_BREAK;
      }
      if (mode_enter==2)
      {
        mode_enter=0;
        return KEYHOOK_NEXT;
      }
      mode_enter=0;
      return KEYHOOK_BREAK;      
    case LONG_PRESS:
      mode_enter=1;
      if (IsUnlocked()||ENA_LOCK)
      {
        ShowMenu();
      }
      mode=0;
      return KEYHOOK_BREAK;
    }
  }
  // * + # implementation
  if ((ACTIVE_KEY_STYLE==2) && !(my_csm_id))
  {
    if (msg==KEY_UP)
    {
      mode=0;
      return KEYHOOK_NEXT;
    }
    if (msg==KEY_DOWN)
    {
      switch (submsg)
      {
      case '*':
        mode=1;
        return (0);
      case '#':
        if (mode==1)
        {
          if (IsUnlocked()||ENA_LOCK)
            ShowMenu();
          else mode=0;
        }
        else return KEYHOOK_NEXT;
      }
    }
  }
  if (ACTIVE_KEY_STYLE==0)
  {
    if (submsg!=ACTIVE_KEY) return KEYHOOK_NEXT;
    if (my_csm_id)
    {
      /*if (((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=my_csm_id)
      {
        CloseCSM(my_csm_id);
      }*/
      if (msg==KEY_UP)
      {
        GBS_SendMessage(MMI_CEPID,KEY_DOWN,ENTER_BUTTON);
      }
      return KEYHOOK_BREAK;
    }
    switch(msg)
    {
    case KEY_DOWN:
      mode=0;
      return KEYHOOK_BREAK;
    case KEY_UP:
      if (mode==1)
      {
        //Release after longpress
        mode=0;
        if (ENA_LONG_PRESS==2)
        {
          CSMtoTop(CSM_root()->idle_id,-1);
          return KEYHOOK_BREAK;
        }
        if (ENA_LONG_PRESS==1) return KEYHOOK_BREAK;
        break;
      }
      if (ACTIVE_KEY_STYLE==0)
      {
        if (IsUnlocked()||ENA_LOCK)
        {
          ShowMenu();
        }
        return KEYHOOK_BREAK;
      }
      break;
    case LONG_PRESS:
      mode=1;
    }
  }
  return KEYHOOK_NEXT;
}

volatile int callhide_mode=0;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

const char my_ipc_name[]=IPC_XTASK_NAME;

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;
  int icgui_id;
  //  int ocgui_id;
  int idlegui_id;
  
#ifndef NEWSGOLD 
#define EXT_BUTTON 0x63  
  if ((ACTIVE_KEY_STYLE!=2)&&(ACTIVE_KEY_STYLE!=3)) //no "* # +" and "Enter Button" 
  {//To be called a browser with these regimes 
    if (ACTIVE_KEY==EXT_BUTTON) //alleged browser button 
    {
      if (msg->msg==439) //called browser 
      {
        switch (msg->submess) 
        {
	case 1:
	  GBS_SendMessage(MMI_CEPID,LONG_PRESS,EXT_BUTTON);
          break;
	case 2:
	  GBS_SendMessage(MMI_CEPID,KEY_UP,EXT_BUTTON);
          break; // No default! ! ! 
        }
      }
      else //browser does not show 
	goto L1;
    }
    else //call button is not alleged call button browser 
      goto L1;
  }
  else
L1:
  csm_result=old_icsm_onMessage(data,msg);
#else    
  csm_result = old_icsm_onMessage(data, msg); //call old handler events 	
#endif
  
  icgui_id=((int *)data)[DISPLACE_OF_INCOMMINGGUI/4];
  idlegui_id=((int *)data)[DISPLACE_OF_IDLEGUI_ID/4];
  //  ocgui_id=((int *)data)[DISPLACE_OF_OUTGOINGGUI/4];
  if (!icgui_id) callhide_mode=0;
  //  if (!ocgui_id) callhide_mode=0;
  
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"XTask config updated!");
      InitConfig();
    }
  }
  //IPC
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp(ipc->name_to,my_ipc_name)==0)
      {
	switch (msg->submess)
	{
	case IPC_XTASK_SHOW_CSM:
	  if (my_csm_id) break;
	  if ((!IsCalling())&&(!SHOW_LOCK))
	  {
	    if ((CSM_root()->csm_q->csm.last!=data)||IsGuiOnTop(idlegui_id))
	    {
	      CSMtoTop((int)(ipc->data),-1);
	    }
	  }
	  break;
	case IPC_XTASK_IDLE:
	  if (my_csm_id) break;
	  if ((!IsCalling())/*&&(!SHOW_LOCK)*/)
	    CSMtoTop(CSM_root()->idle_id,-1);
	  break;
	case IPC_XTASK_LOCK_SHOW:
	  SHOW_LOCK++;
	  break;
	case IPC_XTASK_UNLOCK_SHOW:
	  if (SHOW_LOCK) SHOW_LOCK--;
	  break;
	}
      }
    }
  }
  if (msg->msg==MSG_INCOMMING_CALL)
  {
    callhide_mode=1;
  }
  //  #ifdef NEWSGOLD
  //  if ((msg->msg==MSG_STATE_OF_CALL)&&(msg->submess==0)&&((int)msg->data0==3)) callhide_mode=1;
  //  #else
  //if ((msg->msg==MSG_STATE_OF_CALL)&&(msg->submess==0)&&((int)msg->data0==0)) callhide_mode=1;
  // Govno! ! ! ! Treat! ! !
  //  #endif   
  if (callhide_mode)
  {
    if ((IsGuiOnTop(icgui_id))/*||(IsGuiOnTop(ocgui_id))*/)
    {
      CSMtoTop(CSM_root()->idle_id,((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id);
      callhide_mode=0;
    }
  }
  return csm_result;  
}

void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  RemoveKeybMsgHook((void *)my_keyhook);
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

void main(void)
{
  mode=0;
  InitConfig();
  extern const int SHOW_DAEMONS;
  extern int show_daemons;
  show_daemons=SHOW_DAEMONS;
  LockSched();
  /*if (!AddKeybMsgHook_end((void *)my_keyhook))
  {
    ShowMSG(1,(int)"Unable to register a handler!");
    SUBPROC((void *)ElfKiller);
  }
  else*/
  AddKeybMsgHook_end((void *)my_keyhook);
  {
    extern const int ENA_HELLO_MSG;
    if (ENA_HELLO_MSG) ShowMSG(1,(int)"XTask3 Started!");
    {
      CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
      memcpy(&icsmd,icsm->constr,sizeof(icsmd));
      old_icsm_onClose=icsmd.onClose;
      old_icsm_onMessage=icsmd.onMessage;
      icsmd.onClose=MyIDLECSM_onClose;
      icsmd.onMessage=MyIDLECSM_onMessage;
      icsm->constr=&icsmd;
    }
    under_idle=(FindCSMbyID(CSM_root()->idle_id))->prev; //We are looking for idle_dialog
  }
  UnlockSched();
}
