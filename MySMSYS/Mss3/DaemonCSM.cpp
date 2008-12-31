#include "include.h"

#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "SmsListMenu.h"
#include "DialogCSM.h"
#include "DaemonCSM.h"

#include "AdrList.h"
#include "..\..\inc\playsound.h"

DaemonCSM::DaemonCSM()
{
  daemon_csm_desc.csm_desc.onMessage=OnMessage;
  daemon_csm_desc.csm_desc.onCreate=OnCreate;
  daemon_csm_desc.csm_desc.onClose=OnClose;
#ifdef NEWSGOLD
  daemon_csm_desc.csm_desc.zero1=0;
  daemon_csm_desc.csm_desc.zero2=0;
  daemon_csm_desc.csm_desc.zero3=0;
  daemon_csm_desc.csm_desc.zero4=0;
#endif
  daemon_csm_desc.csm_desc.datasize=sizeof(DAEMON_CSM);
  daemon_csm_desc.csm_desc.statesize=1;
  daemon_csm_desc.csm_desc.states=&minus11;
  daemon_csm_desc.csm_name.wsbody=this->csm_name_body;
  daemon_csm_desc.csm_name.ws_malloc=NAMECSM_MAGIC1;
  daemon_csm_desc.csm_name.ws_mfree=NAMECSM_MAGIC2;
  daemon_csm_desc.csm_name.isbody_allocated=0;
  daemon_csm_desc.csm_name.maxlen=DAEMON_NAME_LEN;
  zeromem(this->DLGCSM_IDS, sizeof(this->DLGCSM_IDS));
  this->is_new_proc=0;
  this->temp_tmr_index=0;
#ifdef ICONBAR
  //this->daemon_csm_desc.iconbar_handler.check_name="IconBar";
  strcpy(this->daemon_csm_desc.iconbar_handler.check_name, "IconBar");
  this->daemon_csm_desc.iconbar_handler.addr=(int)this->AddIconBar;
#endif
}

DaemonCSM::~DaemonCSM()
{
}

void DaemonCSM::CreateDaemonCSM(void)
{
  CSM_RAM *save_cmpc;
  CSMROOT *csmr;
  DAEMON_CSM daemon_csm;
  zeromem(&daemon_csm, sizeof(DAEMON_CSM));
  daemon_csm.daemon=this;
  //csm name
  wsprintf(&daemon_csm_desc.csm_name, "%t", ELFFNAMED);
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=(CSM_RAM *)csmr->csm_q->csm.first;
  CreateCSM(&daemon_csm_desc.csm_desc,&daemon_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
}

void DaemonCSM::OnCreate(CSM_RAM *data)
{
  LGP=new LangPack;
  IP=new IconPack;
  ADRLST=new AdrList;
  SMSDATA=new SmsData;
}

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

//int temp_tmr_index=0;
//int is_new_proc=0;

int DaemonCSM::OnMessage(CSM_RAM *data, GBS_MSG *msg)
{
#ifdef NEWSGOLD

#ifdef ELKA
#define MSG_EMS_FFS_WRITE 0x6105
#else
#define MSG_EMS_FFS_WRITE 0x61CB
#endif

#ifdef ELKA
#define MSG_EMS_INCOMING 0x6106 //ELKA,À´×Ôsmsman
#else
#define MSG_EMS_INCOMING 0x61CC
#define MSG_EMS_INCOMING_2 0x61D6
#endif

#endif

  extern short PLAY_ID;//popup new
  DAEMON_CSM *daemon_csm=(DAEMON_CSM *)data;
  DaemonCSM *daemon=daemon_csm->daemon;
  if (msg->msg==MSG_EMS_FFS_WRITE)
  {
    if ((int)msg->data1==0x8 || (int)msg->data1==0x408)
    {
      if (SMSDATA->IsNewSMS((int)msg->data0))
      {
	if(IsTimerProc(&daemon->chktmr)) GBS_DelTimer(&daemon->chktmr);
	daemon->is_new_proc=1;
	daemon->temp_tmr_index=(int)msg->data0;
	GBS_StartTimerProc(&daemon->chktmr, 216/2, daemon->DoNewProc);
      }
      else goto CHK_IT;
    }
    else
    {
    CHK_IT:
      int chk_res;
      chk_res=SMSDATA->CheckSMS((int)msg->data0);
      if(chk_res==2)
      {
	if(daemon->IsOnTopMyCSM())
	  RefreshGUI();
      }
      else if(chk_res==1)
      {
	if(!daemon->is_new_proc)
	{
	  if(IsTimerProc(&daemon->chktmr)) GBS_DelTimer(&daemon->chktmr);
	  daemon->temp_tmr_index=(int)msg->data0;
	  GBS_StartTimerProc(&daemon->chktmr, 216/2, daemon->UpdateNProc);
	}
      }
    }
    if((!(SMSDATA->n_new=SMSDATA->GetSMSCount(TYPE_IN_N)))&&(CFG_ENA_NOTIFY))
    {
      SetVibration(0);
      if(PLAY_ID)
      {
	PlayMelody_StopPlayback(PLAY_ID);
	PLAY_ID=0;
      }
    }
  }
  if(msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if((ipc=(IPC_REQ *)msg->data0))
    {
      if(!strcmp(ipc->name_to, IPC_NAME))
      {
	switch(msg->submess)
	{
	case SMSYS_IPC_SMS_DATA_UPDATE:
	  if(daemon->IsOnTopMyCSM())
	    RefreshGUI();
	  break;
	case SMSYS_IPC_UPDATE_CLIST:
	  SUBPROC((void *)ADRLST->ConstructListFRC, ADRLST);
	  break;
	//case SMSYS_IPC_READ_NEW_SECC:
	//  if (!CFG_ENA_NOTIFY && daemon->IsOnTopMyCSM())
	//  {
	//    RefreshGUI();
	//  }
	//  break;
	case SMSYS_IPC_READ_NEW:
	  if (daemon->temp_tmr_index)
	  {
	    if (SMSDATA->ReadMessageOne(daemon->temp_tmr_index))
	    {
	      MyIpcMessage myipc;
	      if (CFG_ENA_NOTIFY) myipc.SendIpc(SMSYS_IPC_NEW_IN_WIN, (void *)daemon->temp_tmr_index);
	      else if (daemon->IsOnTopMyCSM()) RefreshGUI();
	    }
	    daemon->temp_tmr_index=0;
	  }
	  daemon->is_new_proc=0;
	  break;
	case SMSYS_IPC_READ_SMS:
	  if (daemon->temp_tmr_index)
	  {
	    if (SMSDATA->ReadMessageOne(daemon->temp_tmr_index))
	    {
	      if (daemon->IsOnTopMyCSM()) RefreshGUI();
	    }
	    daemon->temp_tmr_index=0;
	  }
	  break;
	case SMSYS_IPC_NAB_CREATE:
	  if(ipc->data)
	  {
	    if(!daemon->AddDlgCsmID((int)ipc->data))
	      daemon->AddDlgCsmID_Forced0((int)ipc->data);
	  }
	  break;
	case SMSYS_IPC_ARCHIVE:
extern void OpenArchive(void); //othmenu.cpp
	  SUBPROC((void *)OpenArchive);
	  break;
	default:
	  {
	    int id;
	    DialogCSM *dlg=new DialogCSM;
	    id=dlg->CreateDialogCSM(msg->submess, ipc->data);
	    if(!daemon->AddDlgCsmID(id))
	      daemon->AddDlgCsmID_Forced0(id);
	  }
	  break;
	}
      }
    }
  }
  if(msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    extern void InitSetting(void); //main.cpp
    if(!strcmp_nocase(successed_config_filename,(char *)msg->data0))
    {
      InitSetting();
      ShowMSG(1,(int)LGP->lgp.LGP_CONFIG_UPDATE);
      ADRLST->ConstructListCFGUPD();
    }
  }
  if(msg->msg==MSG_CSM_DESTROYED)
  {
    daemon->DelDlgCsmID((int)msg->data0);
  }
  if(PLAY_ID && (msg->msg==MSG_INCOMMING_CALL || IsCalling()))
  {
    PlayMelody_StopPlayback(PLAY_ID);
    PLAY_ID=0;
  }
  if(msg->msg==MSG_PLAYFILE_REPORT && PLAY_ID) 
  {
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if(pmsg->handler==PLAY_ID)
    {
      if(pmsg->cmd==M_SAE_PLAYBACK_ERROR || pmsg->cmd==M_SAE_PLAYBACK_DONE)
	PLAY_ID=0;
    }
  }
  return 1;
}

void DaemonCSM::OnClose(CSM_RAM *data)
{
  DAEMON_CSM *daemon_csm=(DAEMON_CSM *)data;
  daemon_csm->daemon->CloseAllDlgCSM();
  delete LGP;
  delete IP;
  delete ADRLST;
  delete SMSDATA;
  delete daemon_csm->daemon;
  extern void ElfKiller(void); //main.cpp
  SUBPROC((void *)ElfKiller);
}


int DaemonCSM::AddDlgCsmID(int id)
{
  int i;
  for(i=0;i<DLGCSM_ID_MAX;i++)
  {
    if(!this->DLGCSM_IDS[i])
    {
      this->DLGCSM_IDS[i]=id;
      return 1;
    }
  }
  return 0;
}

void DaemonCSM::AddDlgCsmID_Forced0(int id)
{
  CloseCSM(this->DLGCSM_IDS[0]);
  this->DLGCSM_IDS[0]=id;
}

void DaemonCSM::CloseAllDlgCSM(void)
{
  int i;
  for(i=0;i<DLGCSM_ID_MAX;i++)
  {
    if(this->DLGCSM_IDS[i])
    {
      CloseCSM(this->DLGCSM_IDS[i]);
      this->DLGCSM_IDS[i]=0;
    }
  }
}

void DaemonCSM::DelDlgCsmID(int id)
{
  int i;
  for(i=0;i<DLGCSM_ID_MAX;i++)
  {
    if(this->DLGCSM_IDS[i]==id)
    {
      this->DLGCSM_IDS[i]=0;
      return;
    }
  }
}

int DaemonCSM::IsOnTopMyCSM(void)
{
  int i;
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if(!icsm) return 0;
  while(icsm->next) icsm=(CSM_RAM *)icsm->next;
  if(!icsm->id) return 0;
  for(i=0;i<DLGCSM_ID_MAX;i++)
  {
    if(this->DLGCSM_IDS[i]==icsm->id)
      return 1;
  }
  return 0;
}

void DaemonCSM::DoNewProc(void)
{
/*  if (temp_tmr_index)
  {
    if (SMSDATA->ReadMessageOne(temp_tmr_index))
    {
      MyIpcMessage myipc;
      if (CFG_ENA_NOTIFY) myipc.SendIpc(SMSYS_IPC_NEW_IN_WIN, (void *)temp_tmr_index);
      else myipc.SendIpc(SMSYS_IPC_READ_NEW_SECC);
    }
    temp_tmr_index=0;
  }
  is_new_proc=0;*/
  MyIpcMessage myipc;
  myipc.SendIpc(SMSYS_IPC_READ_NEW);
}

void DaemonCSM::UpdateNProc()
{
/*  if (temp_tmr_index)
  {
    if (SMSDATA->ReadMessageOne(temp_tmr_index))
    {
      MyIpcMessage myipc;
      myipc.SendIpc(SMSYS_IPC_READ_NEW_SECC);
    }
    temp_tmr_index=0;
  }*/
  MyIpcMessage myipc;
  myipc.SendIpc(SMSYS_IPC_READ_SMS);
}

#ifdef ICONBAR
void DaemonCSM::AddIconBar(short* num)
{
  if(CFG_ENA_IB && SMSDATA->n_new) AddIconToIconBar(CFG_ICON_IB, num);
}
#endif

