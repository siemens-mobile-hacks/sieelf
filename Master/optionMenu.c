#include "..\inc\swilib.h"
#include "rect_patcher.h"
#include "lang.h"
#include "main.h"
#include "optionMenu.h"
#include "getConfig.h"
#include "usedstr.h"

#define MAIN_MENU_ITEMS_N 7

const int mmenusoftkeys[]={0,1,2};

const SOFTKEY_DESC mmenu_sk[]=
{
	{0x0018,0x0000,(int)LGP_SELECT},
	{0x0001,0x0000,(int)LGP_BACK},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB mmenu_skt=
{
	mmenu_sk,0
};


void option_menu_ghook(void *data, int cmd)
{
	if (cmd==0x0A)
	{
		DisableIDLETMR();
	}
}

void menu_exit(GUI *gui)
{
	GeneralFuncF1(1);
	CloseCSM(MAIN_CSM_ID);
}

void menu_about(GUI *gui)
{
	GeneralFuncF1(1);
	ShowMSG(0, (int)COPYRIGHT);
}

void createProfileOnoffMenu(void);
void menu_profile(GUI *gui)
{
	GeneralFuncF1(1);
	createProfileOnoffMenu();
}

void deleteAllConfig(void);
void menu_del_all(GUI *gui)
{
	GeneralFuncF1(1);
	deleteAllConfig();
}

void deleteThis(void);
void menu_del_this(GUI *gui)
{
	GeneralFuncF1(1);
	deleteThis();
}

void delUnusedConfig(void);
void menu_del_unused(GUI *gui)
{
	GeneralFuncF1(1);
	delUnusedConfig();
}

void showPatchInfo(void);
void menu_info(GUI *gui)
{
	GeneralFuncF1(1);
	showPatchInfo();
}
const MENUPROCS_DESC option_menu_HNDLS[MAIN_MENU_ITEMS_N]=
{
	menu_profile,
	menu_info,
	menu_del_this,
	menu_del_unused,
	menu_del_all,
	menu_about,
	menu_exit,
};

const MENUITEM_DESC option_menu_ITEMS[MAIN_MENU_ITEMS_N]=
{
	{NULL,(int)LGP_PROFILE,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_PATCH_INFO,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL_THIS,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL_UNUSED,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL_ALL,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_ABOUT,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_QUIT,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const HEADER_DESC option_menu_header={0, 0, 0, 0,NULL,(int)LGP_OPTIONS,LGP_NULL};

const MENU_DESC option_menu=
{
	8,NULL,option_menu_ghook,NULL,
	mmenusoftkeys,
	&mmenu_skt,
	0x10,//MENU_FLAG,
	NULL,
	option_menu_ITEMS,//menuitems,
	option_menu_HNDLS,//menuprocs,
	MAIN_MENU_ITEMS_N
};

void show_option_menu(void)
{
	patch_header(&option_menu_header);
	CreateMenu(0, 0, &option_menu, &option_menu_header, 0, MAIN_MENU_ITEMS_N, 0, 0);
}

void deleteAllConfig(void)
{
	char path[128];
	char folder[128]=PATCH_DIR;
	char tp[128];
	DIR_ENTRY de;
	unsigned int err;
	strcat(folder, PTC_FOLDR);
	strcpy(path, folder);
	strcat(path, "*.ptc");
	if(FindFirstFile(&de, path, &err))
	{
		do
		{
			sprintf(tp, "%s%s", folder, de.file_name);
			unlink(tp, &err);
		}while(FindNextFile(&de,&err));
	}
	FindClose(&de,&err);
	fuckThemAll();
	patch_n=0;
	if(!readConfig(0, 0))
	{
		MsgBoxError(1, (int)LGP_RELOAD_CONFIG_ERR);
		CloseCSM(MAIN_CSM_ID);
	}
}

void deleteThis(void)
{
	char path[128];
	PTC_CONFIG *ptcfg=getPatchConfigItem(PTCFG_CUR);
	if(ptcfg)
	{
		FSTATS fstats;
		unsigned int err;
		sprintf(path, "%s%s%08s", PATCH_DIR, PTC_FOLDR, ptcfg->patchInfo->patchID);
		if(GetFileStats(path,&fstats,&err)!=-1)
		{
			unlink(path, &err);
		}
		reloadThisPatch(ptcfg);
	}
}



const HEADER_DESC profile_menu_header={0, 0, 0, 0,NULL,(int)LGP_PROFILE,LGP_NULL};

int profile_menu_onkey(void *data, GUI_MSG *msg)
{
	PTC_CONFIG *ptcfg;
	int c=GetCurMenuItem(data);
	if(msg->gbsmsg->msg==KEY_DOWN)
	{
		int i=msg->gbsmsg->submess;
		switch(i)
		{
		case LEFT_SOFT:
			return 1;       
		case ENTER_BUTTON:
		case RIGHT_SOFT:
			{
				//int i=GetCurMenuItem(data);
				ptcfg=getPatchConfigItem(PTCFG_CUR);
				if(ptcfg)
				{
					setPatchOnOff(ptcfg, c);
					SetMenuItemIcon(data, c, getPatchOnOff(ptcfg, c));
					REDRAW();
				}
				return (-1);
			}
		}
	}
	return 0;
}

char profileName[7][16]=
{
	LGP_PROFILE1,
	LGP_PROFILE2,
	LGP_PROFILE3,
	LGP_PROFILE4,
	LGP_PROFILE5,
	LGP_PROFILE6,
	LGP_PROFILE7,
};

void profile_menu_iconhndl(void *data, int curitem, void *unk)
{
	PTC_CONFIG *ptcfg;
	void *item=AllocMenuItem(data);
	ptcfg=getPatchConfigItem(PTCFG_CUR);
	WSHDR *ws;
	int n=2;
	if(ptcfg)
	{
		ws=AllocMenuWS(data,128);
	#ifdef BUG
		gb2ws(ws, profileName[curitem], 128);
	#else
		wsprintf(ws, PERCENT_T, profileName[curitem]);
	#endif
		if(getPatchOnOff(ptcfg, curitem))
			n=1;
		else
			n=0;
	}
	else
	{
		ws=AllocMenuWS(data,16);
	#ifdef BUG
		gb2ws(ws, ERR_STR, 16);
	#else
		wsprintf(ws, PERCENT_T, ERR_STR);
	#endif
		n=2;
	}
	SetMenuItemIconArray(data, item, S_ICONS);
	SetMenuItemText(data, item, ws,curitem);
	SetMenuItemIcon(data, curitem, n);
}

void profile_menu_ghook(void *data, int cmd)
{
	if (cmd==0x0A)
		DisableIDLETMR();
}
const SOFTKEY_DESC profile_menu_sk[]=
{
	{0x0018,0x0000,(int)LGP_OK},
	{0x0001,0x0000,(int)LGP_ONOFF},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};
const SOFTKEYSTAB profile_menu_skt=
{
	profile_menu_sk,0
};

const MENU_DESC profile_menu=
{
	8,
	profile_menu_onkey,
	profile_menu_ghook,
	NULL,
	mmenusoftkeys,
	&profile_menu_skt,
	0x11,
	profile_menu_iconhndl,
	NULL,   //Items
	NULL,   //Procs
	0   //n
};

void createProfileOnoffMenu(void)
{
	patch_header(&profile_menu_header);
	CreateMenu(0, 0, &profile_menu, &profile_menu_header, 0, 7, 0, 0);
}


void delUnusedConfig(void)
{
	char patchID[16];
	char path[128];
	char folder[128]=PATCH_DIR;
	char tp[128];
	DIR_ENTRY de;
	unsigned int err;
	strcat(folder, PTC_FOLDR);
	strcpy(path, folder);
	strcat(path, "*.ptc");
	if(FindFirstFile(&de, path, &err))
	{
		do
		{
			strncpy(patchID, de.file_name, 8);
			patchID[8]=0;
			if(isPatchExistedByID(patchID))
			{
				sprintf(tp, "%s%s", folder, de.file_name);
				unlink(tp, &err);
			}
		}while(FindNextFile(&de,&err));
	}
	FindClose(&de,&err);
}
int infoOnKey(GUI *data, GUI_MSG *msg)
{
	if(msg->keys==0xFFF)  // OK
	{
		return (1);    
	}
	if(msg->keys==0xFFE)  // Back
	{
		return (0xFF);
	}
	return 0;
}
void infoGHook(GUI *data, int cmd)
{
	if(cmd==2)
	{
		EDIT_SetFocus(data, 0);
	}
}
void info_locret(void){}
HEADER_DESC INFO_HDR={0,0,0,0,NULL,(int)LGP_PATCH_INFO,LGP_NULL};
INPUTDIA_DESC INFO_DESC=
{
	1,
	infoOnKey,
	infoGHook,
	(void *)info_locret,
	0,
	&mmenu_skt,
	{0,0,0,0},
	FONT_SMALL,
	100,
	101,
	0,
	0,
	0x40000000
};
void showPatchInfo(void)
{
	PTC_CONFIG *ptcfg=getPatchConfigItem(PTCFG_CUR);
	if(ptcfg)
	{
		WSHDR *ws=AllocWS(256);
		void *ma=malloc_adr();
		void *eq;
		EDITCONTROL ec;
		PrepareEditControl(&ec);
		eq=AllocEQueue(ma,mfree_adr());
		
		wsprintf(ws, "%t%t", LGP_PATCH_NAME, ptcfg->patchInfo->patchName);
		ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ws,256);
		AddEditControlToEditQend(eq,&ec,ma);
		
		wsprintf(ws, "%t%t", LGP_PATCH_AUTHOR, ptcfg->patchInfo->author);
		ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ws,256);
		AddEditControlToEditQend(eq,&ec,ma);
		
		wsprintf(ws, "%t%t", LGP_PATCH_ID, ptcfg->patchInfo->patchID);
		ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ws,256);
		AddEditControlToEditQend(eq,&ec,ma);
		
		wsprintf(ws, "%t%t", LGP_PATCH_VERSION, ptcfg->patchInfo->version);
		ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ws,256);
		AddEditControlToEditQend(eq,&ec,ma);
		
		if(ptcfg->patchInfo->info)
		{
			wsprintf(ws, "%t%t", LGP_PATCH_INFO_OTH, ptcfg->patchInfo->info);
			ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ws,256);
			AddEditControlToEditQend(eq,&ec,ma);
		}
		patch_header(&INFO_HDR);
		patch_input(&INFO_DESC);
		CreateInputTextDialog(&INFO_DESC, &INFO_HDR, eq, 1, 0);
		FreeWS(ws);
	}
}
