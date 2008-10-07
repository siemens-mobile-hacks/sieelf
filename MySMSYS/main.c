#include "..\inc\swilib.h"

#include "MySMSYS_ipc.h"
#include "adrList.h"
#include "rect_patcher.h"
#include "sms_dat.h"
#include "smsList.h"
#include "language.h"
#include "edGui.h"

#include "main.h"
#include "createMenu.h"

#include "guiIdMan.h"

#include "popGui.h"
#include "config_data.h"
#include "conf_loader.h"

extern void kill_data(void *p, void (*func_p)(void *));

unsigned int DAEMON_CSM_ID=0;
unsigned int DIALOG_CSM_ID=0;
unsigned int DIALOG_GUI_ID=0;

typedef struct
{
	unsigned int csm_id;
	int code;
	char *fname;
}IPC_DATA_DAEMON;

typedef struct
{
	int ipc_msg;
}IPC_DATA_DLG;

#define MAX_DLG 32

typedef struct
{
  CSM_RAM csm;
}DEAMON_CSM;

int IPC_SUB_MSG=0;
int SMS_INDEX=0;
IPC_REQ daemon_ipc=
{
	my_ipc_name,
	my_ipc_name,
	NULL
};
IPC_DATA_DAEMON ipc_data_daemon;

IPC_REQ dlg_ipc=
{
	my_ipc_name,
	my_ipc_name,
	NULL
};
IPC_DATA_DLG ipc_data_dlg;
const int minus11=-11;

char *num_from_ipc=0;
char *text_utf8=0;
int opmsg_id=0;

int is_fview=0;
char filename[128]={0};
int new_sms_n=0;
//---------------------------------------
//csm_id man

unsigned int DlgCsmIDs[MAX_DLG];

void dlgIDsInit(void)
{
	int i=0;
	for(;i<MAX_DLG;i++)
		DlgCsmIDs[i]=0;
}

int addCSMid(unsigned int *id_pool, unsigned int id)
{
	int i=0;
	for(;i<MAX_DLG;i++)
	{
		if(id_pool[i]==0)
		{
			id_pool[i]=id;
			return i;
		}
	}
	return -1;
}
void addCSMidForced0(unsigned int *id_pool, unsigned int id)
{
	CloseCSM(id_pool[0]);
	id_pool[0]=id;
}
void delCSMid(unsigned int *id_pool, unsigned int id)
{
	int i=0;
	for(;i<MAX_DLG;i++)
	{
		if(id_pool[i]==id)
		{
			id_pool[i]=0;
			return;
		}
	}
}

void closeAllDlgCSM(unsigned int *id_pool)
{
	int i=0;
	for(;i<MAX_DLG;i++)
	{
		if(id_pool[i]!=0)
		{
			CloseCSM(id_pool[i]);
			id_pool[i]=0;
		}
	}
}

int IsNoDlg(unsigned int *id_pool)
{
	int i=0;
	for(;i<MAX_DLG;i++)
	{
		if(id_pool[i])
			return 0;
	}
	return 1;
}

int isTheLastDlg(unsigned int *id_pool, unsigned int id)
{
	return 0;
}

//---------------------------------------

//---------------------------------------
//main menu
const int main_menusoftkeys[]={0,1,2};
const SOFTKEY_DESC main_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_SELECT},
  {0x0001,0x0000,(int)LGP_QUIT},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};


const SOFTKEYSTAB main_menu_skt=
{
  main_menu_sk,0
};
HEADER_DESC main_menuhdr={0,0,0,0,NULL,(int)ELFNAME,LGP_NULL};
#define MAIN_MENU_N 7

void mm_newsms(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	newSMS(dlg_csm);
}

void mm_insms_n(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, TYPE_IN_N);
}

void mm_insms_r(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, TYPE_IN_R);
}

void mm_insms_all(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, TYPE_IN_ALL);
}

void mm_outsms(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, TYPE_OUT);
}

void mm_draftsms(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, TYPE_DRAFT);
}

void mm_allsms(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, 0);
}

unsigned int CreateOthMenu(void);

void mm_oth(GUI *gui)
{
	CreateOthMenu();
}


const char *MENU_TEXT[MAIN_MENU_N]=
{
	LGP_NEW,
	LGP_IN_N,
	LGP_IN_A,
	LGP_OUT,
	LGP_DRAFT,
	LGP_ALL,
	LGP_OTHERS
};
int main_menu_onkey(void *data, GUI_MSG *msg)
{
#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);
	
	if(!IsUnlocked())
		TempLightOn(3, 0x7FFF);

	if(msg->keys==0x1)
	{
		void *dlg_csm=MenuGetUserPointer(data);
		popGS(dlg_csm);
		return 1;
	}
	if((msg->keys==0x18)||(msg->keys==0x3D))
	{
		int n=GetCurMenuItem(data);
		switch(n)
		{
		case 0:
			mm_newsms((GUI *)data);
			break;
		case 1:
			mm_insms_n((GUI *)data);
			break;
		case 2:
			mm_insms_all((GUI *)data);
			break;
		case 3:
			mm_outsms((GUI *)data);
			break;
		case 4:
			mm_draftsms((GUI *)data);
			break;
		case 5: 
			mm_allsms((GUI *)data);
			break;
		case 6:
			mm_oth((GUI *)data);
			break;
		}
	}
	return 0;
}

const char MM_FORMAT[]="%t%c%d";
void main_menu_itemhndl(void *data, int curitem, void *user_pointer)
{
	void *item=AllocMenuItem(data);
	WSHDR *ws=AllocMenuWS(data, 150);
	switch(curitem)
	{
	case 6:
	case 0:
		wsprintf(ws, PERCENT_T, MENU_TEXT[curitem]);
		break;
	case 1:
		wsprintf(ws, MM_FORMAT, MENU_TEXT[curitem], 0xE01D, getCountByType(TYPE_IN_N));
		break;
	case 2:
		wsprintf(ws, MM_FORMAT, MENU_TEXT[curitem], 0xE01D, getCountByType(TYPE_IN_ALL));
		break;
	case 3:
		wsprintf(ws, MM_FORMAT, MENU_TEXT[curitem], 0xE01D, getCountByType(TYPE_OUT));
		break;
	case 4:
		wsprintf(ws, MM_FORMAT, MENU_TEXT[curitem], 0xE01D, getCountByType(TYPE_DRAFT));
		break;
	case 5:
		wsprintf(ws, MM_FORMAT, MENU_TEXT[curitem], 0xE01D, getCountByType(0));
		break;
	default:
		wsprintf(ws, PERCENT_T, LGP_ERR);
		break;
	}
	SetMenuItemText(data, item, ws, curitem);
}
const MENU_DESC main_menu=
{
	8,main_menu_onkey,NULL,NULL,
	main_menusoftkeys,
	&main_menu_skt,
	0x10,//Right align
	main_menu_itemhndl,
	NULL,//main_menuitems,//menuitems,
	NULL, //main_menuprocs,//menuprocs,
	MAIN_MENU_N
};

int CreateMainMenu(DLG_CSM *dlg_csm)
{
	int id;
	patch_header(&main_menuhdr);
	id=CreateSLMenu(&main_menu, &main_menuhdr, 0, MAIN_MENU_N, dlg_csm);
	pushGS(dlg_csm, id);
	return id;
}

//--------------------------------------------------

int dialogcsm_onmessage(CSM_RAM *data,GBS_MSG* msg)
{
	DLG_CSM *csm=(DLG_CSM *)data;
	if(msg->msg==MSG_GUI_DESTROYED)
	{
		if((int)msg->data0==csm->gui_id)
			data->state=-3;
	}
/*	if(msg->msg==MSG_IPC)
	{
		IPC_REQ *ipc;
		if(ipc=(IPC_REQ *)msg->data0)
		{
			if(!strcmp(ipc->name_to, my_ipc_name))
			{
				if(msg->submess==SMSYS_IPC_SMS_DATA_UPDATE)
				{
					SGUI_ID *gs=(SGUI_ID *)(csm->gstop);
					while(gs)
					{
						DirectRedrawGUI_ID(gs->id);
						gs=gs->next;
					}
					//RefreshGUI();
				}
			}
		}
	}*/
	return 1;
}
static void dialogcsm_oncreate(CSM_RAM *data)
{
	DLG_CSM *csm=(DLG_CSM *)data;
	csm->gstop=0;
	if(
		(IPC_SUB_MSG!=SMSYS_IPC_FVIEW)
		&&(IPC_SUB_MSG!=SMSYS_IPC_NEWSMS)
		&&(IPC_SUB_MSG!=SMSYS_IPC_NEWSMS_NUM)
		&&(IPC_SUB_MSG!=SMSYS_IPC_SEND_UTF8)
		)
	{
		readAllSMS();
	}
	switch(IPC_SUB_MSG)
	{
	case MY_SMSYS_IPC_START:
	case SMSYS_IPC_MAIN:
		csm->gui_id=CreateMainMenu(csm);
		break;
	case SMSYS_IPC_NEWSMS:
		csm->gui_id=newSMS(csm);
		break;
	case SMSYS_IPC_IN_NEW:
		csm->gui_id=showSMSList(csm, TYPE_IN_N);
		break;
	case SMSYS_IPC_IN_RD:
		csm->gui_id=showSMSList(csm, TYPE_IN_R);
		break;
	case SMSYS_IPC_OUT:
		csm->gui_id=showSMSList(csm, TYPE_OUT);
		break;
	case SMSYS_IPC_DRAFT:
		csm->gui_id=showSMSList(csm, TYPE_DRAFT);
		break;
	case SMSYS_IPC_ALL:
		csm->gui_id=showSMSList(csm, 0);
		break;
	case SMSYS_IPC_TLAST:
		if(!(csm->gui_id=viewTheLastNew(csm)))
			csm->gui_id=CreateMainMenu(csm);
		break;
	case SMSYS_IPC_IN_ALL:
		csm->gui_id=showSMSList(csm, TYPE_IN_ALL);
		break;
	case SMSYS_IPC_NEW_IN_WIN:
		csm->gui_id=StartIncomingWin(csm);
		break;
	case SMSYS_IPC_NEWSMS_NUM:
		if((!num_from_ipc)||(!(csm->gui_id=newSMSWithNum(csm, num_from_ipc))))
			csm->gui_id=CreateMainMenu(csm);
		num_from_ipc=0;
		break;
	case SMSYS_IPC_SEND_UTF8:
		if((!text_utf8)||(!(csm->gui_id=newSMSWithUtf8Text(csm, text_utf8))))
			csm->gui_id=CreateMainMenu(csm);
		text_utf8=0;
		break;
	case SMSYS_IPC_QN_OPMSG:
	case SMSYS_IPC_QR_OPMSG:
	case SMSYS_IPC_VIEW_OPMSG:
	case SMSYS_IPC_REPLY_OPMSG:
		if(!(csm->gui_id=DoByOpmsgId(csm, IPC_SUB_MSG, opmsg_id)))
			csm->gui_id=CreateMainMenu(csm);
		opmsg_id=0;
		break;
	case SMSYS_IPC_FVIEW:
		if (!strlen(filename) || !(csm->gui_id=ViewFile(csm, filename)))
		{
			readAllSMS();
			csm->gui_id=CreateMainMenu(csm);
		}
		filename[0]=0;
		break;
	default:
		csm->gui_id=CreateMainMenu(csm);
	}
	if(addCSMid(DlgCsmIDs, csm->csm.id)<0)
		addCSMidForced0(DlgCsmIDs, csm->csm.id);
}
static void dialogcsm_onclose(CSM_RAM *data)
{
	DLG_CSM *dlg_csm=(DLG_CSM *)data;
	delCSMid(DlgCsmIDs, dlg_csm->csm.id);
}
static unsigned short dialogcsm_name_body[140];
static const struct
{
	CSM_DESC dialogcsm;
	WSHDR dialogcsm_name;
}DIALOGCSM =
{
	{
	dialogcsm_onmessage,
	dialogcsm_oncreate,
#ifdef NEWSGOLD
	0,
	0,
	0,
	0,
#endif
	dialogcsm_onclose,
	sizeof(CSM_RAM),
	1,
	&minus11
	},
	{
		dialogcsm_name_body,
		NAMECSM_MAGIC1,
		NAMECSM_MAGIC2,
		0x0,
		139
	}
};

static void UpdateDialogCSMname(void)
{
	wsprintf((WSHDR *)(&DIALOGCSM.dialogcsm_name),ELFNAME);
}

unsigned int CreateDialogCSM(void)
{

	DLG_CSM dlg_csm;
	zeromem(&dlg_csm, sizeof(DLG_CSM));
	UpdateDialogCSMname();
	
	if(!cltop)
		SUBPROC((void *)ConstructList);
		//ConstructList();
	return (CreateCSM(&DIALOGCSM.dialogcsm,&dlg_csm,2));
}

static void daemoncsm_oncreate(CSM_RAM *data)
{
	daemon_ipc.data=&ipc_data_daemon;
	ipc_data_daemon.csm_id=DAEMON_CSM_ID;
	if(is_fview&&strlen(filename))
	{
		ipc_data_daemon.code=MY_SMSYS_FVIEW;
		ipc_data_daemon.fname=filename;
	}
	else
	{
		ipc_data_daemon.code=MY_SMSYS_CREATE;
		ipc_data_daemon.fname=0;
	}
	GBS_SendMessage(MMI_CEPID,MSG_IPC,MY_SMSYS_IPC_START,&daemon_ipc);
}


const IPC_REQ my_ipc_n=
{
	my_ipc_name,
	my_ipc_name,
	NULL
};

GBSTMR chk_tmr;
GBSTMR n_update_tmr;

void CheckNewProc(void)
{
		//readAllSMS();
		if(IsHaveNewSMS())
		{
			GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEW_IN_WIN,&my_ipc_n);
		}
}

void UpdateNProc(void)
{
	new_sms_n=IsHaveNewSMS();
	if((!new_sms_n)&&(CFG_ENA_NOTIFY))
		SetVibration(0);
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

int daemoncsm_onmessage(CSM_RAM *data,GBS_MSG* msg)
{
#ifdef NEWSGOLD

#ifdef ELKA
#define MSG_EMS_FFS_WRITE 0x6105
#else
#define MSG_EMS_FFS_WRITE 0x61CB
#endif

#ifdef ELKA
#define MSG_EMS_INCOMING 0x6106 //ELKA,来自smsman
#else
#define MSG_EMS_INCOMING 0x61CC
#endif

#endif
//0x61CC ?? SMS_incoming
//如果使用Browser-killer之类的补丁,将不会有新信息弹出窗口,使用这个MSG可以进行检查是否来新短信了
	if((msg->msg==MSG_EMS_INCOMING)&&(CFG_ENA_NOTIFY))
	{
		if(!IsTimerProc(&chk_tmr)) //接收到MSG半秒之后开始检查,直接开始检查会死机.
			GBS_StartTimerProc(&chk_tmr, 216/2, CheckNewProc);
	}
	if(msg->msg==MSG_EMS_FFS_WRITE)
	{
		if(!IsTimerProc(&n_update_tmr))
			GBS_StartTimerProc(&n_update_tmr, 216, UpdateNProc);
	}
	if(msg->msg==MSG_RECONFIGURE_REQ)
	{
		extern const char *successed_config_filename;
		if(!strcmp_nocase(successed_config_filename,(char *)msg->data0))
		{
			InitConfig();
			ShowMSG(1,(int)LGP_CONFIG_UPDATE);
			if(!cltop)
				SUBPROC((void *)ConstructList);
		}
	}
	if(msg->msg==MSG_IPC)
	{
		IPC_REQ *ipc;
		if(ipc=(IPC_REQ *)msg->data0)
		{
			if(!strcmp(ipc->name_to, my_ipc_name))
			{
				if(msg->submess==MY_SMSYS_IPC_START)
				{
					IPC_DATA_DAEMON *ipcd=(IPC_DATA_DAEMON *)ipc->data;
					if((ipcd)&&(ipcd->csm_id!=DAEMON_CSM_ID))
					{
						switch(ipcd->code)
						{
						case MY_SMSYS_CREATE:
							//if(ipcd->csm_id!=DAEMON_CSM_ID)
							{
								daemon_ipc.data=&ipc_data_daemon;
								ipc_data_daemon.csm_id=ipcd->csm_id;
								ipc_data_daemon.code=MY_SMSYS_CLOSE;
								ipc_data_daemon.fname=0;
								GBS_SendMessage(MMI_CEPID,MSG_IPC,MY_SMSYS_IPC_START,&daemon_ipc);
								IPC_SUB_MSG=MY_SMSYS_IPC_START;
								CreateDialogCSM();
							}
							break;
						case MY_SMSYS_CLOSE:
							//if(ipcd->csm_id!=DAEMON_CSM_ID)
								CloseCSM(ipcd->csm_id);
							break;
						case MY_SMSYS_FVIEW:
							daemon_ipc.data=&ipc_data_daemon;
							ipc_data_daemon.csm_id=ipcd->csm_id;
							ipc_data_daemon.code=MY_SMSYS_CLOSE;
							ipc_data_daemon.fname=0;
							if(ipcd->fname)
								strcpy(filename, ipcd->fname);
							else
								filename[0]=0;
							GBS_SendMessage(MMI_CEPID,MSG_IPC,MY_SMSYS_IPC_START,&daemon_ipc);
							IPC_SUB_MSG=SMSYS_IPC_FVIEW;
							CreateDialogCSM();
							break;
						}
					}
				}
				else if(msg->submess <= SMSYS_IPC_MSG_MAX)
				{
					IPC_SUB_MSG=msg->submess;
					CreateDialogCSM();
				}
				else if(msg->submess == SMSYS_IPC_NEW_IN_WIN)
				{
					IPC_SUB_MSG=msg->submess;
					CreateDialogCSM();
				}
				else if(msg->submess == SMSYS_IPC_NEWSMS_NUM)
				{
					num_from_ipc=(char *)ipc->data;
					IPC_SUB_MSG=msg->submess;
					CreateDialogCSM();
				}
				else if(msg->submess == SMSYS_IPC_SEND_UTF8)
				{
					text_utf8=(char *)ipc->data;
					IPC_SUB_MSG=msg->submess;
					CreateDialogCSM();
				}
				else if((msg->submess>=SMSYS_IPC_VIEW_OPMSG)&&(msg->submess<=SMSYS_IPC_QN_OPMSG))
				{
					opmsg_id=(int)ipc->data;
					IPC_SUB_MSG=msg->submess;
					CreateDialogCSM();
				}
				else if(msg->submess == SMSYS_IPC_FVIEW)
				{
					IPC_SUB_MSG=SMSYS_IPC_FVIEW;
					if(ipc->data)
					{
						strcpy(filename, (char *)ipc->data);
						mfree(ipc->data);
					}
					else
						filename[0]=0;
					CreateDialogCSM();
				}
				else if(msg->submess == SMSYS_IPC_UPDATE_CLIST)
				{
					SUBPROC((void *)ConstructList);
					//ConstructList();
				}
			}
		}
	}
	if((new_sms_n>0)&&(CFG_ENA_NEWSMS_ICON))
	{
		#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
		CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
		if(IsGuiOnTop(idlegui_id))
		{
			GUI *igui=GetTopGUI();
			if(igui)
			{
				DrawImg(CFG_ICONNEW_POS_X, CFG_ICONNEW_POS_Y, (int)CFG_ICONNEW_PATH);
			}
		}
	}
	return 1;
}

static void ElfKiller(void)
{
	extern void *ELF_BEGIN;
	closeAllDlgCSM(DlgCsmIDs);
	FreeCLIST();
	freeSDList();
	GBS_DelTimer(&chk_tmr);
	GBS_DelTimer(&n_update_tmr);
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void daemoncsm_onclose(CSM_RAM *csm)
{
	SUBPROC((void *)ElfKiller);
}

static unsigned short daemoncsm_name_body[140];

static const struct
{
	CSM_DESC daemoncsm;
	WSHDR daemoncsm_name;
}DAEMONCSM =
{
	{
	daemoncsm_onmessage,
	daemoncsm_oncreate,
#ifdef NEWSGOLD
	0,
	0,
	0,
	0,
#endif
	daemoncsm_onclose,
	sizeof(CSM_RAM),
	1,
	&minus11
	},
	{
		daemoncsm_name_body,
		NAMECSM_MAGIC1,
		NAMECSM_MAGIC2,
		0x0,
		139
	}
};

static void UpdateDaemonCSMname(void)
{
	wsprintf((WSHDR *)(&DAEMONCSM.daemoncsm_name),ELFNAME_D);
}

int main(char *exename, char *fname)
{
	DEAMON_CSM d_csm;
	CSM_RAM *save_cmpc;
	CSMROOT *csmr=CSM_root();
	zeromem(&d_csm, sizeof(DEAMON_CSM));
	UpdateDaemonCSMname();
	dlgIDsInit();
	InitConfig();
	if(fname)
	{
		if ( fname[0] < '0' || fname[0] > '4' || fname[1] != ':' || strlen(fname) > 128 )
		{
			SUBPROC((void *)ElfKiller);
			return 0;
		}
		strcpy(filename, fname);
		is_fview=1;
	}
	LockSched();
	save_cmpc=csmr->csm_q->current_msg_processing_csm;
	csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
	DAEMON_CSM_ID=CreateCSM(&DAEMONCSM.daemoncsm,&d_csm,0);
	csmr->csm_q->current_msg_processing_csm=save_cmpc;
	UnlockSched();
	return 0;
}

//--------------------------------------------------------
//Others Menu
#define OTH_MENU_N 6
const SOFTKEY_DESC oth_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_SELECT},
  {0x0001,0x0000,(int)LGP_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};


const SOFTKEYSTAB oth_menu_skt=
{
  oth_menu_sk,0
};

void OpenConfig(void)
{
  extern const char *successed_config_filename;
  WSHDR *file=AllocWS(128);
  str_2ws(file, successed_config_filename, 128);
  ExecuteFile(file, 0, 0);
  FreeWS(file);
}

void oth_menu_config(GUI *data)
{
  GeneralFuncF1(1);
  OpenConfig();
}

void oth_save_one_txt(GUI *data)
{
  GeneralFuncF1(1);
  PathInputDlg(INPUT_EXP_TXT, 0);
}

void oth_move_all_mss(GUI *data)
{
  int k;
  char msg[64];
  GeneralFuncF1(1);
  k=MoveAllMssToArchive();
  sprintf(msg, STR_MOVE_MSSARCHIVER_N, k);
  ShowMSG(1, (int)msg);
  readAllSMS();
}


void OpenArchive(void);

void oth_open_archive(GUI *data)
{
  GeneralFuncF1(1);
  OpenArchive();
}

void oth_about(GUI *data)
{
  GeneralFuncF1(1);
  ShowMSG_noff(1, COPY_RIGHT);
}

void oth_cov_dat_txt(GUI *data)
{
  GeneralFuncF1(1);
  PathInputDlg(INPUT_COV_DAT, 0);
}
/*
void oth_func_test(GUI *data)
{
  GeneralFuncF1(1);
  extern void FuncTest(void);
  FuncTest();
}*/

const MENUPROCS_DESC oth_menuprocs[OTH_MENU_N]=
{
  oth_menu_config,
  oth_open_archive,
  oth_save_one_txt,
  oth_move_all_mss,
  oth_cov_dat_txt,
  oth_about,
  //oth_func_test
};

const MENUITEM_DESC oth_menuitems[OTH_MENU_N]=
{
  {NULL,(int)LGP_CONFIG,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_OPEN_ARCHIVE,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_SAVE_ALL_ONE,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_MOVE_ALL_MSS,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_COV_DAT_TXT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_ABOUT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  //{NULL,(int)"FuncTest",	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENU_DESC oth_menu=
{
  8,NULL,NULL,NULL,
  main_menusoftkeys,
  &oth_menu_skt,
  0x10,//Right align
  NULL,
  oth_menuitems,//menuitems,
  oth_menuprocs,//menuprocs,
  OTH_MENU_N
};

HEADER_DESC oth_menuhdr={0,0,0,0,NULL,(int)LGP_OTHERS,LGP_NULL};

unsigned int CreateOthMenu(void)
{
  patch_header(&oth_menuhdr);
  return (CreateSLMenu(&oth_menu, &oth_menuhdr, 0, OTH_MENU_N, 0));
}

//open archive
void OpenArchive(void)
{
  int len, c;
  char folder[128];
  unsigned int err;
  NativeExplorerData data;
  WSHDR *ws, wsn;
  unsigned short wsb[128];
  ws=CreateLocalWS(&wsn, wsb, 128);
  strcpy(folder, CFG_MAIN_FOLDER);
  len=strlen(folder);
  c=folder[len-1];
  if(c!='\\' && c!='/')
  {
    folder[len]='\\';
    folder[len+1]=0;
  }
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  strcat(folder, FLDR_ARCHIVE);
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  if(!isdir(folder, &err))
    return;
  str_2ws(ws, folder, 128);
  zeromem(&data,sizeof(NativeExplorerData));
  data.mode=0;
  data.dir_enum=0x26;
  data.path_to_file=ws;
  data.is_exact_dir=1;
  data.full_filename=ws;
  data.unk9=1;
  //data.this_struct_addr=&data;
  StartNativeExplorer(&data);
}


