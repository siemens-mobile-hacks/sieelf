#include "..\inc\swilib.h"
#include "main.h"
#include "sms_dat.h"
#include "rect_patcher.h"
#include "smsList.h"
#include "edGui.h"
#include "createMenu.h"
#include "adrList.h"
#include "language.h"

#include "guiIdMan.h"

#include "lgp_pic.h"
#include "CodeShow.h"
#include "popGui.h"

#define MENU_MAX_TXT 30


typedef struct
{
	int type;
	DLG_CSM *dlg_csm;
}SML_OP; //sms list menu user pointer

typedef struct
{
	SMS_DATA *sd;
	DLG_CSM *dlg_csm;
}SL_UP; //sms list option menu user pointer.

//const HEADER_DESC sms_menuhdr_all={0,0,0,0,NULL,(int)LGP_ALL,LGP_NULL};
//const HEADER_DESC sms_menuhdr_in_r={0,0,0,0,NULL,(int)LGP_IN_R,LGP_NULL};
//const HEADER_DESC sms_menuhdr_in_n={0,0,0,0,NULL,(int)LGP_IN_N,LGP_NULL};
//const HEADER_DESC sms_menuhdr_out={0,0,0,0,NULL,(int)LGP_OUT,LGP_NULL};
//const HEADER_DESC sms_menuhdr_draft={0,0,0,0,NULL,(int)LGP_DRAFT,LGP_NULL};
//const HEADER_DESC sms_menuhdr_in_a={0,0,0,0,NULL,(int)LGP_IN_A,LGP_NULL};

const HEADER_DESC sms_menuhdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};

//------------------------------------------------------

#define SLOP_MENU_N 7
#define SLOP_MENU_N_2 (SLOP_MENU_N-1)
const int slop_menusoftkeys[]={0,1,2};
const SOFTKEY_DESC slop_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_SELECT},
  {0x0001,0x0000,(int)LGP_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB slop_menu_skt=
{
  slop_menu_sk,0
};

//char slop_hdr_text[64];
//const HEADER_DESC slop_menu_hdr={0,0,0,0,NULL,(int)smshdr_text,LGP_NULL};

void slop_menu_reply(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	createEditGUI(su->dlg_csm, su->sd, ED_REPLY, 0);
}

void slop_menu_edit(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	createEditGUI(su->dlg_csm, su->sd, ED_EDIT, 0);
}

void slop_menu_exit(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	SGUI_ID *gstop=(SGUI_ID *)(su->dlg_csm->gstop);
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(su->dlg_csm);
	}
	GeneralFuncF1(1);
}

void slop_menu_del(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	if(su->sd->isfile)
		deleteFile(su->sd, 0);
	else
		deleteDat(su->sd, 0);
	delSDList(su->sd);
}

void slop_menu_save_as_file(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	if((!(su->sd->isfile))&&((su->sd->id)>0))
	{
		if(saveFile(su->sd->SMS_TEXT, su->sd->Number, su->sd, su->sd->type, 0))
			deleteDat(su->sd, 1);		
	}
}

void slop_menu_export_txt(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	if(su->sd)
		ShowFileErrCode(ExportOneToTxt(su->sd));
}

void slop_menu_move_to_archive(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	if(su->sd)
	{
		int k=MoveToArchive(su->sd);
		if(k==1)
		{
			if(!su->sd->isfile) deleteDat(su->sd, 0);
			delSDList(su->sd);
		}
		else
			ShowFileErrCode(k);
	}
}

const MENUPROCS_DESC slop_menuprocs[SLOP_MENU_N]=
{
	slop_menu_reply,
	slop_menu_edit,
	slop_menu_del,
	slop_menu_save_as_file,
	slop_menu_export_txt,
	slop_menu_move_to_archive,
	slop_menu_exit,
};

const MENUITEM_DESC slop_menuitems[SLOP_MENU_N]=
{
	{NULL,(int)STR_REPLY,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)STR_EDIT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},	
	{NULL,(int)LGP_SAVE_AS_FILE,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_EXPORT_TXT,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},	
	{NULL,(int)LGP_MOVE_ARCHIVE,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},	
	{NULL,(int)LGP_EXIT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENUPROCS_DESC slop_menuprocs_2[SLOP_MENU_N_2]=
{
	slop_menu_reply,
	slop_menu_edit,
	slop_menu_del,
	slop_menu_export_txt,
	slop_menu_move_to_archive,
	slop_menu_exit,
};

const MENUITEM_DESC slop_menuitems_2[SLOP_MENU_N_2]=
{
	{NULL,(int)STR_REPLY,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)STR_EDIT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_EXPORT_TXT,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},	
	{NULL,(int)LGP_MOVE_ARCHIVE,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},	
	{NULL,(int)LGP_EXIT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENUPROCS_DESC slop_menuprocs_3[1]=
{
	slop_menu_exit,
};

const MENUITEM_DESC slop_menuitems_3[1]=
{
	{NULL,(int)LGP_EXIT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

void slop_menu_ghook(void *data, int cmd)
{
	if(cmd==3)
	{
		SL_UP *su=MenuGetUserPointer(data);
		mfree(su);
	}
}

int slop_menu_onkey(void *data, GUI_MSG *msg)
{
	return 0;
}

const MENU_DESC slop_menu=
{
	8,slop_menu_onkey,slop_menu_ghook,NULL,
	slop_menusoftkeys,
	&slop_menu_skt,
	0x10,//Right align
	NULL,
	slop_menuitems,//menuitems,
	slop_menuprocs,//menuprocs,
	SLOP_MENU_N
};

const MENU_DESC slop_menu_2=
{
	8,slop_menu_onkey,slop_menu_ghook,NULL,
	slop_menusoftkeys,
	&slop_menu_skt,
	0x10,//Right align
	NULL,
	slop_menuitems_2,//menuitems,
	slop_menuprocs_2,//menuprocs,
	SLOP_MENU_N_2
};

const MENU_DESC slop_menu_3=
{
	8,slop_menu_onkey,slop_menu_ghook,NULL,
	slop_menusoftkeys,
	&slop_menu_skt,
	0x10,//Right align
	NULL,
	slop_menuitems_3,//menuitems,
	slop_menuprocs_3,//menuprocs,
	1
};

int CreateslOpMenu(DLG_CSM *dlg_csm, SMS_DATA *sd, int type)
{
	SL_UP *su=malloc(sizeof(SL_UP));
	su->dlg_csm=dlg_csm;
	su->sd=sd;

	patch_header(&sms_menuhdr);
	if(!sd)
		return (CreateSLMenu(&slop_menu_3,&sms_menuhdr,0, 1, su));
	else if(sd->isfile==1)
		return (CreateSLMenu(&slop_menu_2,&sms_menuhdr,0,SLOP_MENU_N_2, su));
	else
		return (CreateSLMenu(&slop_menu,&sms_menuhdr,0,SLOP_MENU_N, su));
}

//------------------------------------------------------

const int sms_menusoftkeys[]={0,1,2};
const SOFTKEY_DESC sms_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_OPTIONS},
  {0x0001,0x0000,(int)LGP_EXIT},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB sms_menu_skt=
{
  sms_menu_sk,0
};
int sms_menu_onkey(void *data, GUI_MSG *msg)
{
	SML_OP *so=MenuGetUserPointer(data);
	SMS_DATA *sd=getSMSDataByType(GetCurMenuItem(data), so->type);
	int n=GetMenuItemCount(data);
#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);
	
	if(!IsUnlocked())
		TempLightOn(3, 0x7FFF);

	if(msg->keys==0x05)
	{
		if(n) createEditGUI(so->dlg_csm, sd, ED_REPLY, 0);
	}
	else if((msg->keys==0x18))//||(msg->keys==0x3D))
	{
		if(!n)
			CreateslOpMenu(so->dlg_csm, 0, so->type);
		else
			CreateslOpMenu(so->dlg_csm, sd, so->type);
	}
	else if(msg->keys==0x3D)
	{
		if(n) createEditGUI(so->dlg_csm, sd, ED_VIEW, so->type);
	}
	else if(msg->keys==0x1)
	{
		popGS(so->dlg_csm);
		return 1;
	}
	if((msg->gbsmsg->msg==KEY_DOWN)&&(n>0)&&(sd))
	{
		int i=msg->gbsmsg->submess;
		if((i=='7')) //key 7 for delete
		{
			if(sd->isfile)
				deleteFile(sd, 0);
			else
				deleteDat(sd, 0);
			delSDList(sd);
			RefreshGUI();
			return (-1);
		}
		else if((i=='9')&&(!sd->isfile))
		{
			if(saveFile(sd->SMS_TEXT, sd->Number, sd, sd->type, 0))
				deleteDat(sd, 1);
			RefreshGUI();
			return (-1);
		}
		else if((i=='*')) //*键,查看号码信息
		{
			WSHDR *msg=AllocWS(128);
		#ifdef NO_CS
			wsprintf(msg, "%t:\n%s", STR_FROM, sd->Number);
		#else
			{
				char num[32];
				WSHDR csloc, *cs;
				unsigned short csb[30];
				cs=CreateLocalWS(&csloc,csb,30);
				strcpy(num, sd->Number);
				GetProvAndCity(cs->wsbody, num);
				wsprintf(msg, "%t:\n%s\n%t:\n%w", STR_FROM, sd->Number, STR_CODESHOW, cs);
			}
		#endif
			ShowMSG_ws(1, msg);
		}
		else if((i=='8'))
		{
			int k;
		//	extern int ExportOneToTxt(SMS_DATA *sd);
			k=ExportOneToTxt(sd);
			ShowFileErrCode(k);
		}
		else if(i=='4')
		{
			int k;
			extern int MoveToArchive(SMS_DATA *sd);
			k=MoveToArchive(sd);
			if(k==1)
			{
				if(!sd->isfile) deleteDat(sd, 0);
				delSDList(sd);
				RefreshGUI();
				return (-1);
			}
			ShowFileErrCode(k);
		}
	}
	return 0;
}

#ifdef ELKA
#define ICON_UNK 0x5B8
#define ICON_OUT 0x5B8
#define ICON_IN_R 0x5B5
#define ICON_IN_N	0x5B6
#define ICON_DRAFT 0x5B8
#define ICON_IN_ALL 0x5B5
#else
#define ICON_UNK 0x5E4
#define ICON_OUT 0x5E4
#define ICON_IN_R 0x5E1
#define ICON_IN_N	0x5E2
#define ICON_DRAFT 0x5E4
#define ICON_IN_ALL 0x5E1
#endif

const int SL_ICONS[7]={ICON_UNK, ICON_OUT, ICON_IN_R, ICON_IN_N, ICON_DRAFT, ICON_IN_ALL, 0};
void sms_menu_itemhndl(void *data, int curitem, void *user_pointer)
{
	SML_OP *so=(SML_OP *)user_pointer;
	int type=so->type;
	void *item=AllocMLMenuItem(data);
	WSHDR *ws1=AllocMenuWS(data, MENU_MAX_TXT);
	WSHDR *ws2=AllocMenuWS(data, 150);
	WSHDR wsloc, *wn;
	unsigned short wsb[150];
	wn=CreateLocalWS(&wsloc,wsb,150);
	SMS_DATA *sdl=getSMSDataByType(curitem, type);
	if(sdl)
	{
		if(sdl->SMS_TEXT)
			wstrncpy(ws1, sdl->SMS_TEXT, MENU_MAX_TXT);
		else
			goto AL_ERR;
			
		if(!strlen(sdl->Number))
			CutWSTR(ws2, 0);
	#ifdef LANG_CN
		else
		{
			int is_fetion=0;
			if(!strncmp(num_fetion, sdl->Number, 5)) is_fetion=1;
			if(findNameByNum(wn, is_fetion?(sdl->Number+5):sdl->Number))
			{
				if(is_fetion) wsprintf(ws2, "%w(%t)", wn, STR_FETION);
				else	wstrcpy(ws2, wn);
			}
			else
				wsprintf(ws2, PERCENT_S, sdl->Number);
		}
	#else
		else if(findNameByNum(wn, sdl->Number))
			wstrcpy(ws2, wn);
		else
			wsprintf(ws2, PERCENT_S, sdl->Number);
	#endif
	}
	else
	{
AL_ERR:
		wsprintf(ws1, PERCENT_T, LGP_ERR);
		CutWSTR(ws2, 0);
	}
	SetMenuItemIconArray(data, item, SL_ICONS);
	SetMenuItemIcon(data, curitem, (sdl)?(sdl->type):6);
	SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

const char SM_FORMAT[]="%t%c%d/%d";
const SOFTKEY_DESC SK_VIEW_PIC={0x003D,0x0000,(int)LGP_VIEW_PIC};
void sms_menu_ghook(void *data, int cmd)
{
	SML_OP *so=MenuGetUserPointer(data);
	if(cmd==0x0A)
	{
		int n=getCountByType(so->type);
		int cur=GetCurMenuItem(data);
		if(cur>=n)
			SetCursorToMenuItem(data, 0);
		Menu_SetItemCountDyn(data, n);
		DisableIDLETMR();
	}
	if(cmd==7)
	{
		//extern void SetMenuSoftKey(void *gui, const SOFTKEY_DESC *,int n);
		int n=getCountByType(so->type);
		int cur_n=GetCurMenuItem(data)+1;
		if(!n) cur_n=0;
		WSHDR *hdr_t=AllocWS(64);
		switch(so->type)
		{
		case 0:
			wsprintf(hdr_t, SM_FORMAT, LGP_ALL, 0xE01D, cur_n, n);
			break;
		case TYPE_IN_R:
			wsprintf(hdr_t, SM_FORMAT, LGP_IN_R, 0xE01D, cur_n, n);
			break;
		case TYPE_IN_N:
			wsprintf(hdr_t, SM_FORMAT, LGP_IN_N, 0xE01D, cur_n, n);
			break;
		case TYPE_OUT:
			wsprintf(hdr_t, SM_FORMAT, LGP_OUT, 0xE01D, cur_n, n);
			break;
		case TYPE_DRAFT:
			wsprintf(hdr_t, SM_FORMAT, LGP_DRAFT, 0xE01D, cur_n, n);
			break;
		case TYPE_IN_ALL:
			wsprintf(hdr_t, SM_FORMAT, LGP_IN_A, 0xE01D, cur_n, n);
			break;
		default:
			CutWSTR(hdr_t, 0);
			break;
		}
		SetHeaderText(GetHeaderPointer(data), hdr_t, malloc_adr(), mfree_adr());
		//if(n) SetSoftKey(data,&SK_VIEW_PIC,SET_SOFT_KEY_M);
		if(n) SetMenuSoftKey(data,&SK_VIEW_PIC,SET_SOFT_KEY_M);
	}
	if(cmd==3)
	{
		mfree(so);
	}
}
const ML_MENU_DESC sms_menu=
{
  8,sms_menu_onkey,sms_menu_ghook,NULL,
  sms_menusoftkeys,
  &sms_menu_skt,
  0x11,//0x11,
  sms_menu_itemhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  1 //line
};

int showSMSList(void *dlg_csm, int type)
{
	unsigned int id;
	SML_OP *so=malloc(sizeof(SML_OP));
	so->type=type;
	so->dlg_csm=dlg_csm;

	patch_header(&sms_menuhdr);
	id=CreateMLMenu(&sms_menu,&sms_menuhdr,0,getCountByType(type), so);
	pushGS(dlg_csm, id);
	return id;
}
