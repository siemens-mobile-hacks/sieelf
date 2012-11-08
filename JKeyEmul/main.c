//JKeyEmul - emulator soft-keys and Joey from another phone in Java-applications, provides an alternative mode.
//To find the key codes for prog nezvestnyh phones use the utility JKeyFinder.
//(c)Dimadze



#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "..\inc\xtask_ipc.h"


#define ELF_NAME "JKeyEmul" 
#define ELF_AUTHOR "Dimadze" 
#define ELF_VERSION 0    
#define ELF_PREDVERSION 4   

#define PLAYTONE(A) PlaySound(1,0, 0, A, 0)



extern const int bcfg_ke_keyboard;  
extern const char bcfg_ke_javacsm[];  
extern const int bcfg_ke_key;          
extern const int bcfg_ke_keytype;       
extern const int bcfg_ke_msg;        


extern const int bcfg_alt_ls;           
extern const int bcfg_alt_rs;            
extern const int bcfg_alt_du;           
extern const int bcfg_alt_dd;            
extern const int bcfg_alt_dl;            
extern const int bcfg_alt_dr;            
extern const int bcfg_alt_dc;           


int ab_se_du=0,ab_se_dr=0; 
int ab_mt_du=0;            
int ab_ls=0,ab_rs=0,ab_du=0,ab_dd=0,ab_dr=0,ab_dl=0,ab_dc=0; 

int emu_switch   = 0; 
int press_cancel = 0;


const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

int my_keyhook(int submsg, int msg);

int str2hex(const char *str)
{
  int i;
  sscanf(str,"%08X",&i);
  return i;
}


int IsCSMOnTop(int CSM) //CSM = addr CSM of CSMList.txt, 1 = CSM on top
{
  if (CSM == 0xA0000000) return 1; 
  CSM_RAM *csm = CSM_root()->csm_q->csm.last;
  CSM_DESC *desc = csm->constr;
  if (CSM == (int)desc) return 1;  else return 0;
}


extern void kill_data(void *p, void (*func_p)(void *));

int my_keyhook(int submsg, int msg)
{
 if ( emu_switch == 1 && IsNoJava()==0 && IsCSMOnTop(str2hex(bcfg_ke_javacsm)) == 1 )
  {
   if (bcfg_ke_keyboard == 2)  
    {

      if (submsg==0x3B && bcfg_alt_du!=0 && bcfg_alt_du!=0x3B){   
	 GBS_SendMessage(MMI_CEPID,msg,bcfg_alt_du);
         ab_du=1;
	 return(2); 
       }
     

      if (submsg==0x3C && bcfg_alt_dd!=0 && bcfg_alt_dd!=0x3C && ab_du==0){  
         GBS_SendMessage(MMI_CEPID,msg,bcfg_alt_dd);
         ab_dd=1;
	 return(2); 
       }
     

      if (submsg==0x3D && bcfg_alt_dl!=0 && bcfg_alt_dl!=0x3D && ab_du==0 && ab_dd==0){  
	 GBS_SendMessage(MMI_CEPID,msg,bcfg_alt_dl);
         ab_dl=1;
         return(2); 
       }
     

      if (submsg==0x3E && bcfg_alt_dr!=0 && bcfg_alt_dr!=0x3E && ab_du==0 && ab_dd==0 && ab_dl==0){ 
	  GBS_SendMessage(MMI_CEPID,msg,bcfg_alt_dr);
          ab_dr=1;
	  return(2); 
        }
      

      if (submsg==0x1A && bcfg_alt_dc!=0 && bcfg_alt_dc!=0x1A && ab_du==0 && ab_dd==0 && ab_dl==0 && ab_dr==0){
         GBS_SendMessage(MMI_CEPID,msg,bcfg_alt_dc);
         ab_dc=1;
         return(2); 
       }
      

      if (submsg==0x01 && bcfg_alt_ls!=0 && bcfg_alt_ls!=0x01 && ab_du==0 && ab_dd==0 && ab_dl==0 && ab_dr==0 && ab_dc==0){
         GBS_SendMessage(MMI_CEPID,msg,bcfg_alt_ls);
         ab_ls=1;
	 return(2); 
       }
      

      if (submsg==0x04 && bcfg_alt_rs!=0 && bcfg_alt_rs!=0x04 && ab_du==0 && ab_dd==0 && ab_dl==0 && ab_dr==0 && ab_dc==0 && ab_ls==0){
	GBS_SendMessage(MMI_CEPID,msg,bcfg_alt_rs);
        return(2); 
       }
      
     ab_rs=0;ab_ls=0;ab_du=0;ab_dd=0;ab_dr=0;ab_dl=0;ab_dc=0;
    }   

  if (bcfg_ke_keyboard == 0)
   {

    if (submsg==0x3B){   
	GBS_SendMessage(MMI_CEPID,msg,0x01);
        ab_se_du=1;
	return(2); 
      }
    

    if (submsg==0x3C){  
	GBS_SendMessage(MMI_CEPID,msg,0x02);
	return(2); 
      }
    

    if (submsg==0x3D){  
	GBS_SendMessage(MMI_CEPID,msg,0x03);
        return(2); 
      }
    

    if (submsg==0x3E){ 
	GBS_SendMessage(MMI_CEPID,msg,0x04);
        ab_se_dr=1;
	return(2); 
      }
    

    if (submsg==0x1A){
        GBS_SendMessage(MMI_CEPID,msg,0x05);
        ab_dc=1;
        return(2); 
      }
    

    if (submsg==0x01 && ab_se_du==0){
	GBS_SendMessage(MMI_CEPID,msg,0x06);
        ab_ls=1;
	return(2); 
      }
    

    if (submsg==0x04 && ab_se_dr==0){
	GBS_SendMessage(MMI_CEPID,msg,0x07);
        return(2); 
      }
    
      ab_se_du=0;
      ab_se_dr=0;
  }

  if (bcfg_ke_keyboard == 1) 
   {

    if (submsg==0x3B){   
	GBS_SendMessage(MMI_CEPID,msg,0x01);
        ab_mt_du=1;
	return(2); 
      }

    if (submsg==0x3C){  
	GBS_SendMessage(MMI_CEPID,msg,0x06);
	return(2); 
      }

    if (submsg==0x3D){  
	GBS_SendMessage(MMI_CEPID,msg,0x02);
        return(2); 
      }

    if (submsg==0x3E){ 
	GBS_SendMessage(MMI_CEPID,msg,0x05);
	return(2); 
      }

    if (submsg==0x1A){
        GBS_SendMessage(MMI_CEPID,msg,0x14);
        ab_dc=1;
        return(2); 
      }

    if (submsg==0x01 && ab_mt_du==0){
	GBS_SendMessage(MMI_CEPID,msg,0x15);
        ab_ls=1;
	return(2); 
      }

    if (submsg==0x04){
	GBS_SendMessage(MMI_CEPID,msg,0x16);
        return(2); 
      }
      ab_mt_du=0;
  }
  
 }
 
 if (IsUnlocked()==1)
  {
   if (((bcfg_ke_keytype==0 && msg==KEY_DOWN) || (bcfg_ke_keytype==1 && msg==LONG_PRESS)) && submsg==bcfg_ke_key && press_cancel == 0)
    {
     if (emu_switch == 1) 
      {
       if (bcfg_ke_msg) ShowMSG(1,(int)"JKeyEmul:\ndisabled!"); else PLAYTONE(1);
       emu_switch = 0;
       press_cancel = 1;
      }
  
     if (emu_switch == 0 && press_cancel == 0) 
      {
       if (bcfg_ke_msg)  
        {
         if (bcfg_ke_keyboard == 0) ShowMSG(1,(int)"JKeyEmul:\nSE/Nokia inc.!");
         if (bcfg_ke_keyboard == 1) ShowMSG(1,(int)"JKeyEmul:\nMotorola inc.!");
         if (bcfg_ke_keyboard == 2) ShowMSG(1,(int)"JKeyEmul:\nOthers!");
        } else PLAYTONE(1);
       emu_switch = 1;
       press_cancel = 1;
      }
     
    }
  }

 if (msg == KEY_UP) press_cancel = 0;

return(0);

}

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

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
 if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    InitConfig();
    emu_switch = 0;
  } 
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  RemoveKeybMsgHook((void *)my_keyhook);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "%t v%d.%d",ELF_NAME,ELF_VERSION,ELF_PREDVERSION);
}


int main()
{
  InitConfig();


  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  
  AddKeybMsgHook((void *)my_keyhook);
  
  return 0;
}
