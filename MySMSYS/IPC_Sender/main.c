#include "..\..\inc\swilib.h"
#include "..\MySMSYS_ipc.h"
#include "..\popGui.h"

extern void kill_data(void *p, void (*func_p)(void *));

IPC_REQ myipc=
{
	MY_SMSYS_IPC_NAME,
	MY_SMSYS_IPC_NAME,
	NULL
	//(void *)0xC6E
};

//int ViewIndex;

void ElfKiller(void)
{
	extern void *ELF_BEGIN;
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
/*
const int softkeys[]={0, 1, 2};
const SOFTKEY_DESC sk[]=
{
  {0x0018,0x0000,0xF5F},
  {0x0001,0x0000,0xF5E},
  {0x003D,0x0000,LGP_DOIT_PIC}
};
const SOFTKEYSTAB skt={sk, 0};
const int icons[]={0x5EA, 0};
const POPUP_DESC popup=
{
  8,
  NULL,
  NULL,
  NULL,
  softkeys,
  &skt,
  0x1,
  LGP_NULL,
  icons,
  0,
  2,
  100,
  101,
  0
};
*/
int main(void)
{
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_MAIN,&myipc);
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEWSMS,&myipc);
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_IN_NEW,&myipc);
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_IN_RD,&myipc);
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_OUT,&myipc);
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_DRAFT,&myipc);
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_ALL,&myipc);
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_TLAST,&myipc);
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_IN_ALL,&myipc);
	//-------------
//	ViewIndex=0xC6E;
	//myipc.data=(void *)0xC6E;
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_VIEW_BY_INDEX,&myipc);
	//-------------
//  GBS_SendMessage(0x4077,0x190,0,0,0);

//extern void SendXToR(void *buf,int pos,int size, int cepid_x_4077, int _190, int _0);
 // int size=sizeof(PDU);
 // void *buf=malloc(2*size);
 // SendXToR(IncommingPDU(),0x37A,0xB2, 0x4077, 0x190, 0); 
//extern void CreatePopupGUI(int flag, void *proc, const POPUP_DESC *, int lgp);
//	CreatePopupGUI(1, 0, &popup, 0xF63);
//  	GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEW_IN_WIN,&myipc);
//	myipc.data=(void *)0xE7C;

//  IPC_REQ *ipcr=malloc(sizeof(IPC_REQ));
//  ipcr->name_to=MY_SMSYS_IPC_NAME;
//  ipcr->name_from=MY_SMSYS_IPC_NAME;
//  ipcr->data=NULL;
//  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_ARCHIVE,ipcr);
	GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_ARCHIVE,&myipc);
//  	ShowMSG(1, LGP_DOIT_PIC);
	SUBPROC((void *)ElfKiller);
	return 0;
}

