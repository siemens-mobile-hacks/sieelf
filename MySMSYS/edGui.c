#include "..\inc\swilib.h"
#include "sms_dat.h"
#include "rect_patcher.h"
#include "language.h"
#include "adrList.h"
#include "guiIdMan.h"
#include "main.h"
#include "edGui.h"
#include "createMenu.h"
#include "numList.h"
#include "MySMSYS_ipc.h"
#include "lgp_pic.h"
#include "CodeShow.h"
#include "popGui.h"
#include "config_data.h"

#ifdef	LANG_CN
#define TEXT_INPUT_OPTION	ECT_CURSOR_STAY
#else
#define	TEXT_INPUT_OPTION	ECT_NORMAL_TEXT
#endif

HEADER_DESC ED_HDR={0,0,0,0,NULL,LGP_NULL,LGP_NULL};
const int ed_menusoftkeys[]={0,1,2};
const SOFTKEY_DESC ed_menu_sk[]=
{
	{0x0018,0x0000,(int)LGP_SELECT},
	{0x0001,0x0000,(int)LGP_BACK},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};
const SOFTKEYSTAB ed_menu_skt=
{
	ed_menu_sk,0
};

HEADER_DESC ed_menuhdr={0,0,0,0,NULL,(int)ELFNAME,LGP_NULL};
#define ED_MENU_N 4
#define ED_MENU_N_1 (ED_MENU_N+1)

void ed_menu_reply(GUI *gui)
{
	int update=0;
	USER_OP *uo=MenuGetUserPointer(gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)uo->dlg_csm;
	SGUI_ID *gstop=(SGUI_ID *)dlg_csm->gstop;
	if(gstop->id==dlg_csm->gui_id)
		update=1;
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(dlg_csm);
	}
	if(uo->sd)
	{
		if(uo->gui_type==ED_FVIEW)
		{
			SMS_DATA *sd=SdCopyOne(uo->sd);
			if(update)
				dlg_csm->gui_id=createEditGUI(dlg_csm, sd, ED_FREPLY, 0);
			else
				createEditGUI(dlg_csm, sd, ED_FREPLY, 0);
		}
		else
		{
			if(update)
				dlg_csm->gui_id=createEditGUI(dlg_csm, uo->sd, ED_REPLY, 0);
			else
				createEditGUI(dlg_csm, uo->sd, ED_REPLY, 0);
		}
	}
	GeneralFuncF1(1);
}

void ed_menu_edit(GUI *gui)
{
	int update=0;
	USER_OP *uo=MenuGetUserPointer(gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)uo->dlg_csm;
	SGUI_ID *gstop=(SGUI_ID *)dlg_csm->gstop;
	if(gstop->id==dlg_csm->gui_id)
		update=1;
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(dlg_csm);
	}
	if(uo->sd)
	{
		if(uo->gui_type==ED_FVIEW)
		{
			SMS_DATA *sd=SdCopyOne(uo->sd);
			if(update)
				dlg_csm->gui_id=createEditGUI(dlg_csm, sd, ED_FEDIT, 0);
			else
				createEditGUI(dlg_csm, sd, ED_FEDIT, 0);
		}
		else
		{
			if(update)
				dlg_csm->gui_id=createEditGUI(dlg_csm, uo->sd, ED_EDIT, 0);
			else
				createEditGUI(dlg_csm, uo->sd, ED_EDIT, 0);
		}
	}
	GeneralFuncF1(1);
}

void ed_menu_exit(GUI *gui)
{
	USER_OP *uo=MenuGetUserPointer(gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
	SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(dlg_csm);
	}
	GeneralFuncF1(1);
}

void ed_menu_del(GUI *gui)
{
	USER_OP *uo=MenuGetUserPointer(gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
	SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);	
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(dlg_csm);
	}
	if(uo->sd)
	{
		if(uo->sd->isfile)
			deleteFile(uo->sd, 0);
		else
			deleteDat(uo->sd, 0);
		if(uo->gui_type!=ED_FVIEW) delSDList(uo->sd);
	}
	GeneralFuncF1(1);
}

void ed_menu_save_as_file(GUI *gui)
{
	USER_OP *uo=MenuGetUserPointer(gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
	SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);	
	if((uo->sd!=0)&&(uo->sd->isfile==0)&&(uo->sd->SMS_TEXT))
	{
		char time[32];
		char sdnum[32];
		SMS_DATA *sdx;
		WSHDR *ws=AllocWS(MAX_TEXT);
		wstrcpy(ws, uo->sd->SMS_TEXT);
		strcpy(time, uo->sd->Time);
		strcpy(sdnum, uo->sd->Number);
		if(saveFile(uo->sd->SMS_TEXT, uo->sd->Number, uo->sd, uo->sd->type, 0))
		{
			deleteDat(uo->sd, 1);
			if(!(sdx=FindSdByTxtTimeNum(ws, time, sdnum))) //重新查找sd失败,直接返回列表
			{
				if(gstop!=0)
				{
					GeneralFunc_flag1(gstop->id, 1);
					popGS(dlg_csm);
				}
				else
				{
				//如果完全出错,直接退出
					GeneralFunc_flag1(dlg_csm->gui_id, 1);
				}
			}
			else
				uo->sd=sdx;
		}
		FreeWS(ws);
	}
	GeneralFuncF1(1);
} 
/*
int ed_menuonkey(void *data, GUI_MSG *msg)
{
	SMS_DATA *sd=MenuGetUserPointer(data);
	if(msg->keys==0x01)
	{
		if(sd) createEditGUI(sd, ED_VIEW);
		return 1;
	}
	return 0;
}


void ed_menughook(void *data, int cmd)
{
	if(cmd==3)
	{
		MU_OP *mo=MenuGetUserPointer(data);
		mfree(mo);
	}
}
*/
const MENUPROCS_DESC ed_menuprocs[ED_MENU_N]=
{
	ed_menu_reply,
	ed_menu_edit,
	ed_menu_del,
	ed_menu_exit,
};

const MENUITEM_DESC ed_menuitems[ED_MENU_N]=
{
	{NULL,(int)STR_REPLY,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)STR_EDIT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_EXIT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENU_DESC ed_menu=
{
	8,NULL,NULL,NULL,
	ed_menusoftkeys,
	&ed_menu_skt,
	0x10,//Right align
	NULL,
	ed_menuitems,//menuitems,
	ed_menuprocs,//menuprocs,
	ED_MENU_N
};

const MENUPROCS_DESC ed_menuprocs_1[ED_MENU_N_1]=
{
	ed_menu_reply,
	ed_menu_edit,
	ed_menu_del,
	ed_menu_save_as_file,
	ed_menu_exit,
};

const MENUITEM_DESC ed_menuitems_1[ED_MENU_N_1]=
{
	{NULL,(int)STR_REPLY,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)STR_EDIT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_SAVE_AS_FILE,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_EXIT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENU_DESC ed_menu_1=
{
	8,NULL,NULL,NULL,
	ed_menusoftkeys,
	&ed_menu_skt,
	0x10,//Right align
	NULL,
	ed_menuitems_1,//menuitems,
	ed_menuprocs_1,//menuprocs,
	ED_MENU_N_1
};

int createEditOpMenu(USER_OP *uo)
{
	patch_header(&ed_menuhdr);

	if(uo->sd->isfile)
		return (CreateSLMenu(&ed_menu, &ed_menuhdr, 0, ED_MENU_N, uo));
	else
		return (CreateSLMenu(&ed_menu_1, &ed_menuhdr, 0, ED_MENU_N_1, uo));
}



int Ed_SendSMS(void *gui)
{
	EDITCONTROL ec;
	USER_OP *uo=EDIT_GetUserPointer(gui);
	NUM_LIST *nl=(NUM_LIST *)(uo->nltop);
	if(!(IsHaveNumInList(uo)))
	{
		ShowMSG(1, (int)LGP_ERR_0NUM);
		return 0;
	}
	ExtractEditControl(gui,uo->focus_n,&ec);
	while(nl)
	{
		if(strlen(nl->num))
		{
			WSHDR *ws=AllocWS(ec.pWS->wsbody[0]);
			wstrcpy(ws,ec.pWS);
			SendSMS(ws,nl->num,MMI_CEPID,MSG_SMS_RX-1,6);
			saveFile(ec.pWS, nl->num, uo->sd, TYPE_OUT, 1);
		}
		nl=nl->next;
	}
	return 1;
}

void Ed_SaveFile(WSHDR *txt, USER_OP *uo, int type)
{
	NUM_LIST *nl=(NUM_LIST *)(uo->nltop);
	while(nl)
	{
		saveFile(txt, nl->num, uo->sd, type, 0);
		nl=nl->next;
	}
	readAllSMS();
}

void on_ed_ec(USR_MENU_ITEM *item)
{
	if(item->type==0)
	{
		switch(item->cur_item)
		{
		case 0:
			wsprintf(item->ws, PERCENT_T, LGP_SEND);
			break;
		case 1:
			wsprintf(item->ws, PERCENT_T, LGP_CANCEL);
			break;
		case 2:
			wsprintf(item->ws, PERCENT_T, LGP_SAVE_AS_DRAFT);
			break;
		}
	}
	else if(item->type==1)
	{
		USER_OP *uo=EDIT_GetUserPointer(item->user_pointer);
		DLG_CSM *dlg_csm=(DLG_CSM *)uo->dlg_csm;
		SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);
		switch(item->cur_item)
		{
		case 0:
			if((Ed_SendSMS(item->user_pointer))&&(gstop!=0))
			{
				GeneralFunc_flag1(gstop->id, 1); //close ed
				popGS(dlg_csm);
			}
			break;
		case 1:
			if(gstop!=0)
			{
				GeneralFunc_flag1(gstop->id, 1);
				popGS(dlg_csm);
			}
			break;
		case 2:
			{
				EDITCONTROL ec;
				ExtractEditControl(item->user_pointer,uo->focus_n,&ec);
				Ed_SaveFile(ec.pWS, uo, TYPE_DRAFT);
			}
			break;
		}
	}
}


void on_adr_ec(USR_MENU_ITEM *item)
{
	if(item->type==0)
	{
		switch(item->cur_item)
		{
		case 0:
			wsprintf(item->ws, PERCENT_T, LGP_SEND);
			break;
		case 1:
			wsprintf(item->ws, PERCENT_T, LGP_ADRBK);
			break;
//		case 2:
//			wsprintf(item->ws, PERCENT_T, LGP_INSERT_ADRNUM);
//			break;
		case 2:
			wsprintf(item->ws, PERCENT_T, LGP_CANCEL);
			break;
		case 3:
			wsprintf(item->ws, PERCENT_T, LGP_SAVE_AS_DRAFT);
			break;
		}
	}
	else if(item->type==1)
	{
		USER_OP *uo=EDIT_GetUserPointer(item->user_pointer);
		DLG_CSM *dlg_csm=(DLG_CSM *)uo->dlg_csm;
		SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);
		switch(item->cur_item)
		{
		case 0:
			//sendSMSwithUP(item->user_pointer);
			//if(sendSMSwithUP(item->user_pointer)&&gstop)
			if((Ed_SendSMS(item->user_pointer))&&(gstop))
			{
				GeneralFunc_flag1(gstop->id, 1);
				popGS(dlg_csm);
			}
			break;
		case 1:
//			uo->adr_type=TYPE_SET;
			CreateAdrMenu(item->user_pointer);
			break;
//		case 2:
//			uo->adr_type=TYPE_INSERT;
//			CreateAdrMenu(item->user_pointer);
//			break;
		case 2:
			if(gstop)
			{
				GeneralFunc_flag1(gstop->id, 1);
				popGS(dlg_csm);
			}
			break;
		case 3:
			{
				EDITCONTROL ec;
				ExtractEditControl(item->user_pointer,uo->focus_n,&ec);
				Ed_SaveFile(ec.pWS, uo, TYPE_DRAFT);
			}
			break;
		}
	}
}

int edOnKey(GUI *data, GUI_MSG *msg)
{
//0x29 keys, ENTER,no op
//0x05 keys, Green
//0x03 keys, ENTER,op
//0x3D keys, ENTER,select char
//0x1A keys, LSK
//0x01 keys, RSK
	USER_OP *uo=EDIT_GetUserPointer(data);
	int n=EDIT_GetFocus(data);
	DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
	SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);
	SMS_DATA *sdl=0;
#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);
	
	if(!IsUnlocked())
		TempLightOn(3, 0x7FFF);
		
	if(msg->keys==0x05)
	{
		if(uo->gui_type==ED_VIEW)
		{
			int update=0;
			if(gstop->id==dlg_csm->gui_id)
				update=1;
			popGS(uo->dlg_csm);
			if(update)
				dlg_csm->gui_id=createEditGUI(uo->dlg_csm, uo->sd, ED_REPLY, 0);
			else
				createEditGUI(uo->dlg_csm, uo->sd, ED_REPLY, 0);
			return 1;
		}
		else if((uo->gui_type==ED_FVIEW)&&(uo->sd))
		{
			SMS_DATA *sd=SdCopyOne(uo->sd);
			int update=0;
			if(gstop->id==dlg_csm->gui_id)
				update=1;
			popGS(uo->dlg_csm);
			if(update)
				dlg_csm->gui_id=createEditGUI(uo->dlg_csm, sd, ED_FREPLY, 0);
			else
				createEditGUI(uo->dlg_csm, sd, ED_FREPLY, 0);
			return 1;
		}
		else
		{
			if(!Ed_SendSMS(data))
				return 0;
		}

		popGS(uo->dlg_csm);
		return 1;
	}
	else if((msg->keys==0x29)&&((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW)))
	{
		createEditOpMenu(uo);
	}
	else if(msg->keys==0x18)
	{
		if((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW))
		{
			createEditOpMenu(uo);
		}
		else
		{
			if(n==uo->focus_n)
			{
				uo->adr_type=TYPE_TXT;
				EDIT_OpenOptionMenuWithUserItems(data,on_adr_ec,data,4);
				//EDIT_OpenOptionMenuWithUserItems(data,on_ed_ec,data,3);
			}
			else if(n<=(uo->focus_n-2)) //号码位置
			{
				uo->adr_type=TYPE_SET;
				EDIT_OpenOptionMenuWithUserItems(data,on_adr_ec,data,4);
			}
			return (-1);
		}
	}

	else if(msg->keys==0x1)
	{
		popGS(uo->dlg_csm);
		return 1;
	}
	else if(msg->keys==0x0F00)
	{
		uo->adr_type=TYPE_SET;
		CreateAdrMenu(data);
	}
	//else if((msg->keys==0)&&(uo->gui_type==ED_VIEW)) //禁止输入编辑
	//{
	//	return -1;
	//}
	if(((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))&&(!EDIT_IsBusy(data)))
	{
		int i=msg->gbsmsg->submess;
		EDITCONTROL ec;
		ExtractEditControl(data,n,&ec);
		//中键
		if((i==ENTER_BUTTON)&&(uo->gui_type!=ED_VIEW)&&(uo->gui_type!=ED_FVIEW))
		{
			if(n==uo->focus_n)
			{
				uo->adr_type=TYPE_TXT;
				EDIT_OpenOptionMenuWithUserItems(data,on_adr_ec,data,4);
				//EDIT_OpenOptionMenuWithUserItems(data,on_ed_ec,data,3);
			}
			else if(n<=(uo->focus_n-2)) //号码位置
			{
				uo->adr_type=TYPE_SET;
				EDIT_OpenOptionMenuWithUserItems(data,on_adr_ec,data,4);
			}
			return (-1);
		}
		//上方向, 侧上键
		if(((i==UP_BUTTON)||(i==VOL_UP_BUTTON)) //循环
				&&(n==1)
				&&(!(EDIT_IsMarkModeActive(data)))
				&&(EDIT_GetCursorPos(data)<=1)) //第一行第一个字符
		{
			EDIT_SetFocus(data, uo->focus_n);
			return (-1);
		}
		//下方向, 侧下键
		if(((i==DOWN_BUTTON)||(i==VOL_DOWN_BUTTON))
				&&(n==uo->focus_n)
				&&(!(EDIT_IsMarkModeActive(data)))
				&&(EDIT_GetCursorPos(data)>=(ec.pWS->wsbody[0]+1))) //最后一个字
		{
			EDIT_SetFocus(data, 1);
			return (-1);
		}
		//右方向键,下一条
		if((i==RIGHT_BUTTON)&&(uo->gui_type==ED_VIEW)&&(sdl=FindNextByType(uo->sd, uo->list_type)))
		{
			int update=0;
			if(gstop->id==dlg_csm->gui_id)
				update=1;
			popGS(uo->dlg_csm);
			if(update)
				dlg_csm->gui_id=createEditGUI(uo->dlg_csm, sdl, ED_VIEW, uo->list_type);
			else
				createEditGUI(uo->dlg_csm, sdl, ED_VIEW, uo->list_type);
			return 1;
		}
		//左方向键,上一条
		if((i==LEFT_BUTTON)&&(uo->gui_type==ED_VIEW)&&(sdl=FindPrevByType(uo->sd, uo->list_type)))
		{
			int update=0;
			if(gstop->id==dlg_csm->gui_id)
				update=1;
			popGS(uo->dlg_csm);
			if(update)
				dlg_csm->gui_id=createEditGUI(uo->dlg_csm, sdl, ED_VIEW, uo->list_type);
			else
				createEditGUI(uo->dlg_csm, sdl, ED_VIEW, uo->list_type);
			return 1;
		}
		//*键,查看号码信息
		if((i=='*')&&((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW))&&(uo->sd))
		{
			NUM_LIST *nl=(NUM_LIST *)(uo->nltop);
			WSHDR *msg=AllocWS(128);
		#ifdef NO_CS
			wsprintf(msg, "%t:\n%s", STR_FROM, nl->num);
		#else
			{
				char num[32];
				WSHDR csloc, *cs;
				unsigned short csb[30];
				cs=CreateLocalWS(&csloc,csb,30);
				strcpy(num, nl->num);
				GetProvAndCity(cs->wsbody, num);
				wsprintf(msg, "%t:\n%s\n%t:\n%w", STR_FROM, nl->num, STR_CODESHOW, cs);
			}
		#endif
			ShowMSG_ws(1, msg);
		}
	}
	return 0;
}


const SOFTKEY_DESC SK_OPTIONS={0x0018,0x0000,(int)LGP_OPTIONS};
const SOFTKEY_DESC SK_ADRBK={0x0F00,0x0000,(int)LGP_ADRBK};
const SOFTKEY_DESC SK_CANCEL={0x0001,0x0000,(int)LGP_CANCEL};
const SOFTKEY_DESC SK_OP_PIC={0x0029,0x0000,(int)LGP_OPTION_PIC};

void edGHook(GUI *data, int cmd)
{
	USER_OP *uo=EDIT_GetUserPointer(data);
	if(cmd==TI_CMD_CREATE)
	{
		if((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW))
			EDIT_SetFocus(data, 1); //从号码开始看
		else
			EDIT_SetFocus(data, uo->focus_n);//光标跳到文本位置
	}
	else if(cmd==TI_CMD_DESTROY)
	{

		if(((uo->gui_type==ED_FREE)
				||(uo->gui_type==ED_FVIEW)
				||(uo->gui_type==ED_FEDIT)
				||(uo->gui_type==ED_FREPLY)
				)&&(uo->sd))
		{
			FreeSdOne(uo->sd);
		}
		FreeNumList(uo);
		mfree(uo);
	}
	else if(cmd==TI_CMD_FOCUS)
	{
		DisableIDLETMR();
	}
	else if(cmd==TI_CMD_REDRAW)
	{
		NUM_LIST *nl;
		EDITCONTROL ec;
		char time[32];
		char num[32];
		WSHDR txtl, *text;
		unsigned short txtb[MAX_TEXT];
		SMS_DATA *sdx;
		DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
		SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);	
		int n=EDIT_GetFocus(data);
		text=CreateLocalWS(&txtl, txtb, MAX_TEXT);
		if((uo->gui_type==ED_VIEW)&&(!IsSdInList(uo->sd)))
		{
			ExtractEditControl(data, uo->focus_n, &ec);
			wstrcpy(text, ec.pWS);
			if(uo->focus_n>2) //简单判断时间是否存在
			{
				ExtractEditControl(data, uo->focus_n-2, &ec);
				ws_2str(ec.pWS, time, 31);
			}
			else
				time[0]=0;
			nl=uo->nltop;
			if(nl) strcpy(num, nl->num);
			else num[0]=0;
			if(!(sdx=FindSdByTxtTimeNum(text, time, num)))
			{
				if(gstop)
				{
					GeneralFunc_flag1(gstop->id, 1);
					popGS(dlg_csm);
				}
				else
				{
				//如果完全出错,直接退出
					GeneralFunc_flag1(dlg_csm->gui_id, 1);
				}
			}
			else
				uo->sd=sdx;
		}
		if((uo->gui_type==ED_VIEW)&&(uo->sd->type==TYPE_IN_N))
			newToRead(uo->sd);
		if((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW))
			SetSoftKey(data,&SK_OP_PIC,SET_SOFT_KEY_M);
//auto save as file
		if((uo->gui_type==ED_VIEW)&&(CFG_ENA_AUTO_SAF)&&(!uo->sd->isfile)&&(uo->sd->id))      
		{
			wstrcpy(text, uo->sd->SMS_TEXT);
			strcpy(time, uo->sd->Time);
			strcpy(num, uo->sd->Number);
			if(saveFile(uo->sd->SMS_TEXT, uo->sd->Number, uo->sd, uo->sd->type, 0))
			{
				deleteDat(uo->sd, 1);
				if(!(sdx=FindSdByTxtTimeNum(text, time, num))) //重新查找sd失败,直接返回列表
				{
					if(gstop!=0)
					{
						GeneralFunc_flag1(gstop->id, 1);
						popGS(dlg_csm);
					}
					else
					{
					//如果完全出错,直接退出
						GeneralFunc_flag1(dlg_csm->gui_id, 1);
					}
				}
				else
					uo->sd=sdx;
			}
		}
//-------------------
		//if((n==uo->focus_n)&&(!EDIT_IsBusy(data)))
		{
			ExtractEditControl(data, uo->focus_n, &ec);
			WSHDR *hdr_t=AllocWS(64);
		#ifdef DEBUG
			wsprintf(hdr_t, "%t:%d,p:%d", LGP_CHAR_COUNT, ec.pWS->wsbody[0], EDIT_GetCursorPos(data));
		#else
			wsprintf(hdr_t, "%t: %d", LGP_CHAR_COUNT, ec.pWS->wsbody[0]);
		#endif
			SetHeaderText(GetHeaderPointer(data), hdr_t, malloc_adr(), mfree_adr());
		}
		if((uo->gui_type!=ED_VIEW)&&(uo->gui_type!=ED_FVIEW)&&(n<=(uo->focus_n-2))&&(nl=GetNumListCur(uo, n)))
		{
			ExtractEditControl(data,n,&ec);
			if(isNum(ec.pWS))
			{
				char num[50];
				ws_2str(ec.pWS, num, 49);
				if(strcmp(num, nl->num))
				{
					strcpy(nl->num, num);
					str_2ws(nl->name, num, 50);
				}
			}
			else
			{
				if(wstrcmp_nocase(ec.pWS, nl->name))
				{
					DelNumList(uo, nl);
					if((uo->focus_n-2)>1) //多于一个号码就直接删除这个
					{
						EDIT_RemoveEditControl(data, n);
						(uo->focus_n)--;
						if(n>(uo->focus_n-2))
							n=(uo->focus_n-2);
						if(n>0)
							EDIT_SetFocus(data, n);
					}
					else
					{
						EDIT_SetTextToEditControl(data, n, ((NUM_LIST *)(uo->nltop))->name);
						SetSoftKey(data,&SK_CANCEL,!SET_SOFT_KEY_N);
					}
				}
			}
		}
		ExtractEditControl(data,n,&ec);
		if(!EDIT_IsBusy(data))
		{
			if((n<=(uo->focus_n-2))&&(ec.pWS->wsbody[0]==0))
				SetSoftKey(data,&SK_ADRBK,SET_SOFT_KEY_N);
			else
				SetSoftKey(data,&SK_OPTIONS,SET_SOFT_KEY_N);
		}
	}
}

void ed_locret(void)
{
	;
}

const INPUTDIA_DESC ED_DESC=
{
	1,
	edOnKey,
	edGHook,
	(void *)ed_locret,
	0,
	&ed_menu_skt,
	{0,0,0,0},
	FONT_SMALL,
	100,
	101,
	0,
	0,
	0x40000000
};

const INPUTDIA_DESC ED_DESC_RO=
{
	1,
	edOnKey,
	edGHook,
	(void *)ed_locret,
	0,
	&ed_menu_skt,
	{0,0,0,0},
	FONT_SMALL,
	100,
	101,
	0,
	0,
	0x00000002
};

int createEditGUI(void *dlg_csm, SMS_DATA *sd, int type, int list_type) //edit, view
{
	int gui_id;
	void *ma=malloc_adr();
	void *eq;
	WSHDR *ews;
	const INPUTDIA_DESC *edd;
	EDITCONTROL ec;
	EDITC_OPTIONS ec_options;
//----------- uo
	USER_OP *uo=malloc(sizeof(USER_OP));
	zeromem(uo, sizeof(USER_OP));

	AddToNumList(uo);
	uo->sd=sd; //?
	uo->dlg_csm=dlg_csm;
	strcpy(((NUM_LIST *)(uo->nltop))->num, sd->Number);
	uo->gui_type=type;
	uo->list_type=list_type;
	uo->focus_n=0;
//----------
	eq=AllocEQueue(ma,mfree_adr());
	PrepareEditControl(&ec);
	ews=AllocWS(256);
//-----------

//----------- header

//------------

//------------ num
	{
		if((!strlen(sd->Number))||(!findNameByNum(ews, sd->Number)))
			str_2ws(ews, sd->Number, 256);
#ifdef DEBUG
		{
			if(strlen(sd->Number))
			{
				WSHDR *ws=AllocWS(50);
				str_2ws(ws, sd->Number, 50);
				wsAppendChar(ews, '|');
				wstrcat(ews, ws);
				FreeWS(ws);
			}
		}
#endif
		wstrcpy(((NUM_LIST *)(uo->nltop))->name, ews);
		ConstructEditControl(&ec,(type==ED_VIEW||type==ED_FVIEW)?ECT_READ_ONLY:ECT_NORMAL_TEXT,ECF_DEFAULT_DIGIT+ECF_APPEND_EOL,ews,256);
		//ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
		PrepareEditCOptions(&ec_options);
		SetFontToEditCOptions(&ec_options,FONT_SMALL);
		CopyOptionsToEditControl(&ec,&ec_options);
		AddEditControlToEditQend(eq,&ec,ma);
		uo->focus_n++;
	}
//------------
//------------ time
	if((type==ED_FVIEW)||(type==ED_VIEW)&&strlen(sd->Time)) //time
	{
		str_2ws(ews, sd->Time, 256);
		ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
		AddEditControlToEditQend(eq,&ec,ma);
		uo->focus_n++;
	}
//------------
//------------ line
	str_2ws(ews, STR_LINES,256);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
	AddEditControlToEditQend(eq,&ec,ma);
	uo->focus_n++;
//------------
//------------ TXT
	if(sd->SMS_TEXT)
		wstrcpy(ews, sd->SMS_TEXT);
	else
		CutWSTR(ews, 0);
	switch(type)
	{
	case ED_VIEW:
	case ED_FVIEW:
		ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,256);
		break;
	case ED_FREE:
	case ED_EDIT:
	case ED_FEDIT:
		ConstructEditControl(&ec,TEXT_INPUT_OPTION,ECF_APPEND_EOL,ews,256);
		break;
	case ED_NEW:
	case ED_REPLY:
	case ED_FREPLY:
		CutWSTR(ews, 0);
		ConstructEditControl(&ec,TEXT_INPUT_OPTION,ECF_APPEND_EOL,ews,256);
		break;
	default:
		ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ews,256);
		break;
	}
	//
	PrepareEditCOptions(&ec_options);
	SetFontToEditCOptions(&ec_options,FONT_SMALL);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);
	uo->focus_n++;
//----------	
	FreeWS(ews);
	
	if (type==ED_VIEW || type==ED_FVIEW)
		edd=&ED_DESC_RO;
	else
		edd=&ED_DESC;
	patch_header(&ED_HDR);
	patch_input(edd);
	gui_id=CreateInputTextDialog(edd, &ED_HDR, eq, 1, uo);
	pushGS(dlg_csm, gui_id);
	return gui_id;
}

int newSMS(void *dlg_csm)
{
	SMS_DATA sd;
	zeromem(&sd, sizeof(SMS_DATA));
	return (createEditGUI(dlg_csm, &sd, ED_NEW, 0));
}
int viewTheLastNew(void *dlg_csm)
{
	SMS_DATA *sd=getLastTheLast(TYPE_IN_N);
	if(!sd)
		return 0;
	return(createEditGUI(dlg_csm, sd, ED_VIEW, TYPE_IN_N));
}

int newSMSWithNum(void *dlg_csm, char *num)
{
	SMS_DATA sd;
	if(!num)
		return 0;
	zeromem(&sd, sizeof(SMS_DATA));
	strcpy(sd.Number, num);
	mfree(num);
	return (createEditGUI(dlg_csm, &sd, ED_NEW, 0));
}

int newSMSWithUtf8Text(void *dlg_csm, char *text_utf8)
{
	SMS_DATA *sd;
	WSHDR *ws;
	if(!text_utf8)
		return 0;
	sd=malloc(sizeof(SMS_DATA));
	zeromem(sd, sizeof(SMS_DATA));
	ws=AllocWS(MAX_TEXT);
	sd->SMS_TEXT=ws;
	utf8_2ws(ws, text_utf8, MAX_TEXT);
	mfree(text_utf8);
	return (createEditGUI(dlg_csm, sd, ED_FREE, 0));
}

int DoByOpmsgId(void *dlg_csm, int msg, int opmsg_id)
{
	SMS_DATA *sd;
	if((!opmsg_id)||(!(sd=FindSDByOpmsgId(opmsg_id))))
		return 0;
	switch(msg)
	{
	case SMSYS_IPC_VIEW_OPMSG:
		return (createEditGUI(dlg_csm, sd, ED_VIEW, TYPE_IN_ALL));
	case SMSYS_IPC_REPLY_OPMSG:
		return (createEditGUI(dlg_csm, sd, ED_REPLY, 0));
	case SMSYS_IPC_QR_OPMSG:
		return (createEditGUI(dlg_csm, sd, ED_EDIT, 0));
	case SMSYS_IPC_QN_OPMSG:
		{
			SMS_DATA *sdx=malloc(sizeof(SMS_DATA));
			WSHDR *ws=AllocWS(MAX_TEXT);
			zeromem(sdx, sizeof(SMS_DATA));
			sdx->SMS_TEXT=ws;
			wstrcpy(ws, sd->SMS_TEXT);
			return (createEditGUI(dlg_csm, sdx, ED_FREE, 0));
		}
	}
	return 0;
}

unsigned int ViewFile(void *dlg_csm, char *fname)
{
	SMS_DATA *sd;
	if(!strlen(fname))
		return 0;
	sd=malloc(sizeof(SMS_DATA));
	zeromem(sd, sizeof(SMS_DATA));
	sd->SMS_TEXT=AllocWS(MAX_TEXT);
	if(!ReadMSS(fname, sd))
	{
		FreeSdOne(sd);
		return 0;
	}
	return (createEditGUI(dlg_csm, sd, ED_FVIEW, 0));
}

