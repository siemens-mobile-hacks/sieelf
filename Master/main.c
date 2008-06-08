/*
 * 文件名: main.c
 * 作者: BingK(binghelingxi)
 *
 * 最后修改日期: 2008.06.07
 *
 * 作用: 建立CSM，GUI，以及一些控制项目
 *
 */

#include "..\inc\swilib.h"
#include "main.h"
#include "getConfig.h"
#include "rect_patcher.h"
#include "lang.h"
#include "ptcFileWork.h"
#include "optionMenu.h"
#include "getConfig.h"
#include "visual.h"
#include "master.h"
#include "usedstr.h"



#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif

typedef struct
{
	CSM_RAM csm;
	int gui_id;
}MAIN_CSM;

typedef struct
{
	GUI gui;
}MAIN_GUI;
#pragma swi_number=0xBE
__swi __arm void RunScaner(void);

char *ptc_buf;
int patch_n=0;
int isSubMenuNeed=0;
int colorEditing=0;
int PTCFG_CUR=0;
unsigned int MAIN_GUI_ID=0;
unsigned int MAIN_CSM_ID=0;
unsigned int MAIN_EDGUI_ID=0;
//unsigned int COLOR_EDITOR_GUI_ID=0;
int S_ICONS[3];
WSHDR *ews;

const HEADER_DESC menuheader={0, 0, 0, 0, NULL, (int)ELFNAME, LGP_NULL};
const int menusoftkeys[]={0, 1, 2};
const SOFTKEY_DESC menu_sk[]=
{
	{0x0018,0x0000,(int)LGP_OPTIONS},
	{0x0001,0x0000,(int)LGP_ONOFF},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};
const SOFTKEYSTAB menu_skt=
{
	menu_sk,0
};


typedef struct
{
	void *next;
	void *prev;
	int editCurItem;
	PTC_CONFIG *ptcfg;
	PATCH_SUBMENU *submenu;
}EDIT_ITEM_LIST;
EDIT_ITEM_LIST * volatile editItemList=0;

void pushToItemStack(PATCH_SUBMENU *submenu)
{
	EDIT_ITEM_LIST *item=malloc(sizeof(EDIT_ITEM_LIST));
	item->next=0;
	item->prev=0;
	item->editCurItem=0;
	item->ptcfg=0;
	item->submenu=submenu;
	if(!editItemList)
		editItemList=item;
	else
	{
		EDIT_ITEM_LIST *titem=editItemList;
		editItemList=item;
		editItemList->next=titem;
		titem->prev=editItemList;
		editItemList->ptcfg=titem->ptcfg;
	}
}

void popItemStack(void)
{
	EDIT_ITEM_LIST *item=editItemList;
	if(item)
	{
		editItemList=item->next;
		if(editItemList)
			editItemList->prev=0;
		mfree(item);
	}
}

void updateStackEditCurItem(int cur)
{
	if(editItemList && cur>=0)
		editItemList->editCurItem=cur;
}
void updateStackPtcfg(PTC_CONFIG *ptcfg)
{
	if(editItemList)
		editItemList->ptcfg=ptcfg;
}

int isTopSubMenu(void)
{
	if(editItemList)
	{
		if(strlen(editItemList->submenu->smName))
			return 1;
	}
	return 0;
}

int getnumwidth(unsigned int num)
{
	int i=1;
	while(num>=10) 
	{
		num/=10;
		i++;
	}
	return i;  
}

void uni2ws(WSHDR *ws, unsigned short *uni, int maxlen)
{
	unsigned short *p=uni;
	ws->wsbody[0]=0;
	int i=1;
	while(*p && (maxlen==0||p-uni<=maxlen))
	{
		ws->wsbody[i]=*p;
		i++;
		p++;
	}
	ws->wsbody[0]=i-1;
}

void hex2ws(WSHDR *ws, unsigned char *hex, int maxlen)
{
	unsigned char *p=hex;
	ws->wsbody[0]=0;
	WSHDR *tws=AllocWS(8);
	while(p-hex<maxlen)
	{
		wsprintf(tws, PERCENT_02X, *p);
		wstrcat(ws, tws);
		p++;
	}
	FreeWS(tws);
}

void ws2hex(WSHDR *ws, char *hex, int maxlen)
{
	char s[256];
	int i=0;
	unsigned char c, c1;
	char *p1=s;
	ws_2str(ws, s, maxlen);
	while((c=*p1++))
	{
		if((c>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'))
		{
			c1=*p1++;
			if((c1>='0'&&c1<='9')||(c1>='a'&&c1<='f')||(c1>='A'&&c1<='F'))
				hex[i++]=chr2num(c)*0x10+chr2num(c1);
			else
				break;
		}
		else
			break;
	}
	for(;i<(maxlen/2);i++)
	{
		hex[i]=0;
	}
}
int createEditGui(void);

int menu_onkey(void *data, GUI_MSG *msg)
{
	PTC_CONFIG *ptcfg;
	int c=GetCurMenuItem(data);
	PTCFG_CUR=c;
	if(msg->gbsmsg->msg==KEY_DOWN)
	{
		int i=msg->gbsmsg->submess;
		switch(i)
		{
		case LEFT_SOFT:
			show_option_menu();
			return 0;
		case RIGHT_SOFT:
			{
				//int i=GetCurMenuItem(data);
				ptcfg=getPatchConfigItem(c);
				if(ptcfg)
				{
					setPatchOnOff(ptcfg, 7);
					SetMenuItemIcon(data, c, getPatchOnOff(ptcfg, 7));
					REDRAW();
				}
				return (-1);
			}
		case ENTER_BUTTON:
			{
				ptcfg=getPatchConfigItem(c);
				if(ptcfg)
				{
					if(ptcfg->mainitem.item)
					{
						pushToItemStack(&ptcfg->mainitem);
						updateStackPtcfg(ptcfg);
						isSubMenuNeed=1;
						return 1;
					}
					else
						createProfileOnoffMenu();
				}
				return 0;
			}
		}
	}
	return 0;
}

void menu_iconhndl(void *data, int curitem, void *unk)
{
	PTC_CONFIG *ptcfg;
	void *item=AllocMenuItem(data);
	ptcfg=getPatchConfigItem(curitem);
	WSHDR *ws;
	int n=2;
	if(ptcfg)
	{
		ws=AllocMenuWS(data,128);
	#ifdef BUG
		gb2ws(ws, ptcfg->patchInfo->patchName, 128);
	#else
		wsprintf(ws, PERCENT_T, ptcfg->patchInfo->patchName);
	#endif
		if(getPatchOnOff(ptcfg, 7))
			n=1;
		else
			n=0;
	}
	else
	{
		ws=AllocMenuWS(data,16);
	#ifdef BUG
		gb2ws(ws, ERR_STR, 128);
	#else
		wsprintf(ws, PERCENT_T, ERR_STR);
	#endif
		n=2;
	}
	SetMenuItemIconArray(data, item, S_ICONS);
	SetMenuItemText(data,item,ws,curitem);
	SetMenuItemIcon(data, curitem, n);
}

void menu_ghook(void *data, int cmd)
{
	if (cmd==0x0A)
		DisableIDLETMR();
}

const MENU_DESC main_menu=
{
	8,
	menu_onkey,
	menu_ghook,
	NULL,
	menusoftkeys,
	&menu_skt,
	0x11,
	menu_iconhndl,
	NULL,   //Items
	NULL,   //Procs
	0   //n
};

int createMainMenu(void)
{
	patch_header(&menuheader);
	return (CreateMenu(0, 0, &main_menu, &menuheader, PTCFG_CUR, patch_n, 0, 0));
}
void maincsm_oncreate(CSM_RAM *data)
{
	MAIN_CSM *csm=(MAIN_CSM*)data;
	csm->gui_id=MAIN_GUI_ID=createMainMenu();
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	MAIN_CSM *csm=(MAIN_CSM*)data;
	if (msg->msg==MSG_GUI_DESTROYED)
	{
		if(((int)msg->data0==csm->gui_id))
		{
			PTC_CONFIG *ptcfg;
			if((int)msg->data1==1)
			{
				if(editItemList)
				{
					ptcfg=editItemList->ptcfg;
					if(ptcfg)
						ptcfg->needSaveData=1;
				}
			}
			else
			{
				if(editItemList)
				{
					ptcfg=editItemList->ptcfg;
					if(ptcfg)
						ptcfg->needSaveData=0;
				}
			}
			if(!isSubMenuNeed)
				popItemStack();
			csm->gui_id=createEditGui();
			if(!csm->gui_id)
			{
				if(ptcfg=getPatchConfigItem(PTCFG_CUR))
				{
					if(ptcfg->needSaveData && !getPatchOnOff(ptcfg, 7))//when patch is off
						setPatchOnOff(ptcfg, 7);
				}
				csm->gui_id=createMainMenu();
			}
			if(csm->gui_id)
				return 1;
			else
				csm->csm.state=-3;
		}
	}
	return(1);
}

void Killer(void)
{
	saveAllConfig();
	mfree(ptc_buf);
	fuckThemAll();
	FreeWS(ews);
	RunScaner();
	extern void *ELF_BEGIN;
	extern void kill_data(void *p, void (*func_p)(void *));
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
	SUBPROC((void *)Killer);
}

const int minus11=-11;
const unsigned short maincsm_name_body[140];

const struct
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
		(unsigned short *)maincsm_name_body,
		NAMECSM_MAGIC1,
		NAMECSM_MAGIC2,
		0x0,
		139
	}
};

void UpdateCSMname(void)
{
	wsprintf((WSHDR *)(&MAINCSM.maincsm_name), ELFNAME);
}

int main(void)
{
	char dummy[sizeof(MAIN_CSM)];
	S_ICONS[0]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);//icon_disabled;
	S_ICONS[1]=GetPicNByUnicodeSymbol(CBOX_CHECKED);//icon_enabled;
	S_ICONS[2]=0;
	ptc_buf=malloc(PTC_SIZE);
	ews=AllocWS(256); 
	if(!getAllPatchData())
	{
		SUBPROC((void *)Killer);
		return 0;
	}
	UpdateCSMname();
	LockSched();
	MAIN_CSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
	UnlockSched();
	return 0;
}

char ED_HDR_BODY[128];
HEADER_DESC ED_HDR={0,0,0,0,NULL,(int)ED_HDR_BODY,LGP_NULL};

PATCH_ITEM *findPatchItemInED(int n)
{
	PATCH_ITEM *pitem;
	int i=0;
	int type;
	if(!editItemList->submenu)
		return 0;
	pitem=editItemList->submenu->item;
	while(pitem)
	{
		type=pitem->itemType;
		if(type==TYPE_DRSTR)
			i++;
		else if(type>0&&type!=TYPE_TP)
			i+=2;
		if(i==n)
			return pitem;
		pitem=pitem->next;
	}
	return 0;
}

int getMaxFocus(void)
{
	PATCH_ITEM *pitem;
	int i=0;
	int type;
	if(!editItemList->submenu)
		return 0;
	pitem=editItemList->submenu->item;
	while(pitem)
	{
		type=pitem->itemType;
		if(type==TYPE_DRSTR)
			i++;
		else if(type>0&&type!=TYPE_TP)
			i+=2;
		pitem=pitem->next;
	}
	pitem=editItemList->submenu->item;
	if(pitem) //get the last item
	{
		while(pitem->next)
			pitem=pitem->next;
		while(pitem)
		{
			if(pitem->itemType==TYPE_DRSTR)
				i--;
			else if(type>0&&type!=TYPE_TP)
				break;
			pitem=pitem->prev;
		}
	}
	return i;
}

int getMinFocus(void)
{
	PATCH_ITEM *pitem;
	int i=0;
	int type;
	if(!editItemList->submenu)
		return 0;
	pitem=editItemList->submenu->item;
	while(pitem)
	{
		type=pitem->itemType;
		if(type==TYPE_DRSTR)
			i++;
		else if(type>0&&type!=TYPE_TP)
		{
			i+=2;
			break;
		}
		pitem=pitem->next;
	}
	return i;
}

void updateEdHdr(char *str)
{
	strcpy(ED_HDR_BODY, str);
}

void ed_locret(void){}

DATA_SF *sfItemTemp=0;
void on_sfec(USR_MENU_ITEM *item)
{
	if (item->type==0)
	{
		switch(item->cur_item)
		{
		case 0:
		#ifdef BUG
			gb2ws(item->ws, LGP_SELECT_FILE, 16);
		#else
			wsprintf(item->ws, PERCENT_T, LGP_SELECT_FILE);
		#endif
			break;
		}
	}
	if (item->type==1)
	{
		switch(item->cur_item)
		{
		case 0:
			open_select_file_gui(item->user_pointer, sfItemTemp?(strlen(sfItemTemp->mask)?sfItemTemp->mask:0):0, 1);
			break;
		}
	}   
}
void on_sdec(USR_MENU_ITEM *item)
{
	if (item->type==0)
	{
		switch(item->cur_item)
		{
		case 0:
		#ifdef BUG
			gb2ws(item->ws, LGP_SELECT_FOLDER, 16);
		#else
			wsprintf(item->ws, PERCENT_T, LGP_SELECT_FOLDER);
		#endif
			break;
		}
	}
	if (item->type==1)
	{
		switch(item->cur_item)
		{
		case 0:
			open_select_file_gui(item->user_pointer, 0, 0);
			break;
		}
	}   
}

int edOnKey(GUI *data, GUI_MSG *msg)
{
	int l;
	int i=EDIT_GetFocus(data);
	updateStackEditCurItem(i);
	isSubMenuNeed=0;
	if(msg->keys==0xFFF)  // OK
	{
		return (1);    
	}
	if(msg->keys==0xFFE)  // Back
	{
		return (0xFF);
	}
	isSubMenuNeed=0;
	if(msg->gbsmsg->msg==KEY_DOWN)
	{
		l=msg->gbsmsg->submess;
		if((l==UP_BUTTON||l==VOL_UP_BUTTON))
		{
			int max=getMaxFocus();
			int min=getMinFocus();
			if(!min||!max)
				return -1;
			if(i==min||i==1) //start
			{
				EDIT_SetFocus(data, max); 
				return -1;
			}
		}
		else if((l==DOWN_BUTTON||l==VOL_DOWN_BUTTON))
		{
			int max=getMaxFocus();
			int min=getMinFocus();
			if(!min||!max)
				return -1;
			if(i==max)
			{
        		EDIT_SetFocus(data, min); 
		  		return -1;
		  	}
		}
		PATCH_ITEM *pitem;
		if(l==LEFT_SOFT||l==ENTER_BUTTON)
		{
			if(pitem=findPatchItemInED(i))
			{
				if(l==ENTER_BUTTON)
				{
					if(pitem->itemType==TYPE_SF)
					{
						sfItemTemp=(DATA_SF *)pitem->itemData;
						EDIT_OpenOptionMenuWithUserItems(data,on_sfec,data,1);
						return (-1);
					}
					if(pitem->itemType==TYPE_SD)
					{
						EDIT_OpenOptionMenuWithUserItems(data,on_sdec,data,1);
						return (-1);
					}
				}
				switch(pitem->itemType)
				{
				case TYPE_SUBMENU:
					{
						PATCH_SUBMENU *psubmenu=(PATCH_SUBMENU *)pitem->itemData;
						pushToItemStack(psubmenu);
						isSubMenuNeed=1;
						return 1;
					}
				case TYPE_CHECKBOX:
					{
						DATA_CHECKBOX *chkbox=(DATA_CHECKBOX *)pitem->itemData;
						chkbox->onoff=!chkbox->onoff;
						return (-1);
					}
				case TYPE_POSB:
				case TYPE_POS:
					{
						DATA_POS *pos=(DATA_POS *)pitem->itemData;
						if(pos->off)
						{
							pos->off=0;
							wsprintf(ews, PERCENT_D_D, pos->x, pos->y);
							EDIT_SetTextToFocused(data, ews);
						}
						EditPostionGUI(&pos->x, &pos->y, pos->w, pos->h);
						break;
					}
				case TYPE_COLOR:
					{
						DATA_COLOR *color=(DATA_COLOR *)pitem->itemData;
						EditColors(color->color);
						break;
					}
				}
			}
		}
		if(l==RIGHT_BUTTON||l==LEFT_BUTTON)
		{
			if(pitem=findPatchItemInED(i))
			{
				if(pitem->itemType==TYPE_POS||pitem->itemType==TYPE_POSB)
				{
					DATA_POS *pos=(DATA_POS *)pitem->itemData;
					if(pos->off)
					{
						pos->off=0;
						wsprintf(ews, PERCENT_D_D, pos->x, pos->y);
						EDIT_SetTextToFocused(data, ews);
					}
					else
					{
						pos->off=1;
						wsprintf(ews, PERCENT_T, LGP_IS_OFF);
						EDIT_SetTextToFocused(data, ews);
					}
					REDRAW();
					return -1;
				}
			}
		}
	}
	return 0;
}
const SOFTKEY_DESC SK_OK={0x0FFF,0x0000,(int)LGP_OK};
const SOFTKEY_DESC SK_BACK={0x0FFE,0x0000,(int)LGP_BACK};
const SOFTKEY_DESC SK_CLOSE={0x0FFE,0x0000,(int)LGP_CLOSE};


void edGHook(GUI *data, int cmd)
{
	int sk_need=0;
	int i,j;
	EDITCONTROL ec;
	PATCH_ITEM *pitem;
	char ss[16];
	if(cmd==2)
	{
		if(editItemList)
			EDIT_SetFocus(data, editItemList->editCurItem);
	}
	if(cmd==0x0A)
	{
		DisableIDLETMR();
	}
	if(cmd==7)
	{
		i=EDIT_GetFocus(data);
		ExtractEditControl(data,i,&ec);
		wstrcpy(ews,ec.pWS);
		ws_2str(ews,ss,15);
		if(pitem=findPatchItemInED(i))
		{
			switch(pitem->itemType)
			{
			case TYPE_CHECKBOX:
				{
					DATA_CHECKBOX *chkbox=(DATA_CHECKBOX *)pitem->itemData;
					CutWSTR(ews,0);
					wsAppendChar(ews, chkbox->onoff?CBOX_CHECKED:CBOX_UNCHECKED);
					EDIT_SetTextToFocused(data,ews);
					sk_need=1;
					break;
				}
			case TYPE_SUBMENU:
				sk_need=1;
				break;
			case TYPE_POSB:
			case TYPE_POS:
				{
					DATA_POS *pos=(DATA_POS *)pitem->itemData;
					if(pos->off)
						wsprintf(ews, PERCENT_T, LGP_IS_OFF);
					else
						wsprintf(ews, PERCENT_D_D, pos->x, pos->y);
				//	wsprintf(ews, PERCENT_D_D, pos->x, pos->y);
					EDIT_SetTextToFocused(data,ews);
					sk_need=1;
					break;
				}
			case TYPE_BYTE:
				{
					DATA_BYTE *dbyte=(DATA_BYTE *)pitem->itemData;
					str2num_char(ss, &dbyte->initData, dbyte->max, dbyte->min, 0);
					break;
				}
			case TYPE_INT:
				{
					DATA_INT *dint=(DATA_INT *)pitem->itemData;
					str2num(ss, &dint->initData, dint->max, dint->min, 0);
					break;
				}
			case TYPE_CBOX:
				{
					int j=EDIT_GetItemNumInFocusedComboBox(data);
					DATA_CBOX *cbox=(DATA_CBOX *)pitem->itemData;
					CBOX_ITEM *cboxitem=0;
					if(cboxitem=getCurCBoxItem(cbox, j-1))
						cbox->initData=cboxitem->data;
					break;
				}
			case TYPE_COLOR:
				{
					DATA_COLOR *color=(DATA_COLOR *)pitem->itemData;
					wsprintf(ews,PERCENT_02X_02X_,color->color[0],color->color[1],color->color[2],color->color[3]);
					EDIT_SetTextToFocused(data,ews);  
					sk_need=1;
					break;
				}
			case TYPE_ADDRESS:
				{
					DATA_ADDRESS *addr=(DATA_ADDRESS *)pitem->itemData;
					str2num(ss, (int *)&addr->addr, 0xA4000000, 0, 1);
					break;
				}
			case TYPE_STRING:
				{
					DATA_STRING *str=(DATA_STRING *)pitem->itemData;
					ws_2str(ews, str->string, str->maxlen?str->maxlen:0x10);
					break;
				}
			case TYPE_UNICODE:
				{
					DATA_UNICODE *uni=(DATA_UNICODE *)pitem->itemData;
					memcpy((ews->wsbody+1), uni->ustr, 2*(ews->wsbody[0]<(uni->maxlen?uni->maxlen:0x10)?ews->wsbody[0]:(uni->maxlen?uni->maxlen:0x10)));
					break;
				}
			case TYPE_HEX:
				{
					DATA_HEX *hex=(DATA_HEX *)pitem->itemData;
					ws2hex(ews, (char *)hex->hex, 2*(hex->maxlen?hex->maxlen:0x1));
					break;
				}
			case TYPE_SF:
				{
					DATA_SF *sf=(DATA_SF *)pitem->itemData;
					ws_2str(ews, sf->path, sf->maxlen?sf->maxlen:58);
					break;
				}
			case TYPE_SD:
				{
					DATA_SD *sd=(DATA_SD *)pitem->itemData;
					ws_2str(ews, sd->path, sd->maxlen?sd->maxlen:58);
					break;
				}
			case TYPE_SL:
				{
					int j=EDIT_GetItemNumInFocusedComboBox(data);
					DATA_SL *sl=(DATA_SL *)pitem->itemData;
					sl->initData=j-1;
					break;
				}
			case TYPE_MS:
				{
					DATA_MS *ms=(DATA_MS *)pitem->itemData;
					str2num(ss, (int *)&ms->ms, 0, 0, 0);
					break;
				}
			}
			if(sk_need)
			{
				sk_need=0;
				SetSoftKey(data, &SK_OK, SET_SOFT_KEY_N);
				SetSoftKey(data, (isTopSubMenu())?&SK_BACK:&SK_CLOSE, !SET_SOFT_KEY_N);
			}
		}
	}
	if(cmd==0x0D)
	{
		//onCombo
		i=EDIT_GetFocus(data);
		ExtractEditControl(data,i,&ec);
		
		if(pitem=findPatchItemInED(i))
		{
			if(pitem->itemType==TYPE_CBOX)
			{
					
				if ((j=EDIT_GetItemNumInFocusedComboBox(data)))
				{
					DATA_CBOX *cbox=(DATA_CBOX *)pitem->itemData;
					CBOX_ITEM *cboxitem=0;
					if(cboxitem=getCurCBoxItem(cbox, j-1))
					#ifdef BUG
						gb2ws(ews, cboxitem->name, 256);
					#else
						wsprintf(ews, PERCENT_T, cboxitem->name);
					#endif
				}
				else
				{
					ExtractEditControl(data,EDIT_GetFocus(data)-1,&ec);
					wstrcpy(ews,ec.pWS);
				}
				EDIT_SetTextToFocused(data,ews);
			}
			else if(pitem->itemType==TYPE_SL)
			{
				if((j=EDIT_GetItemNumInFocusedComboBox(data)))
				{
					//DATA_SL *sl=(DATA_SL *)pitem->itemData;
					wsprintf(ews, PERCENT_D, j-1);
				}
				else
				{
					ExtractEditControl(data,EDIT_GetFocus(data)-1,&ec);
					wstrcpy(ews,ec.pWS);
				}
				EDIT_SetTextToFocused(data,ews);
			}
		}
	}
}
INPUTDIA_DESC ED_DESC=
{
	1,
	edOnKey,
	edGHook,
	(void *)ed_locret,
	0,
	&menu_skt,
	{0,0,0,0},
	FONT_SMALL,
	100,
	101,
	0,
	0,
	0x40000000
};


int createEditGui(void)
{
	PATCH_ITEM *pitem;
	void *ma=malloc_adr();
	void *eq;
	EDITCONTROL ec;
	int type;
	if(!editItemList)
		goto ex_back;
	if(!editItemList->submenu)
		goto ex_back;
	pitem=editItemList->submenu->item;
	if(!pitem)
		goto ex_back;
	if(strlen(editItemList->submenu->smName))
		updateEdHdr(editItemList->submenu->smName);
	else
	{
		if(editItemList->ptcfg)
			updateEdHdr(editItemList->ptcfg->patchInfo->patchName);
	}
	PrepareEditControl(&ec);
	eq=AllocEQueue(ma,mfree_adr());
	while(pitem)
	{
		type=pitem->itemType;
		if(!pitem->itemData)
			goto NextItem;
		if(!type)
			goto NextItem;
		if(type==TYPE_TP) //template
			goto NextItem;
		if(strlen(pitem->itemName))
			wsprintf(ews, "%t:", pitem->itemName);
		else
			CutWSTR(ews,0);
		if(type==TYPE_SUBMENU||type==TYPE_CHECKBOX||type==TYPE_SL)
		{
			ConstructEditControl(&ec,1,0x00,ews,256);
		}
		else if(type==TYPE_DRSTR)
		{
			DATA_DRSTR *dstr=(DATA_DRSTR *)pitem->itemData;
		#ifdef BUG
			gb2ws(ews, dstr->str, 128);
		#else
			wsprintf(ews, PERCENT_T, dstr->str);
		#endif
			ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
			AddEditControlToEditQend(eq,&ec,ma);
			goto NextItem;
		}
		else
			ConstructEditControl(&ec,1,0x40,ews,256);
		AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+2
		switch(type)
		{
		case TYPE_CHECKBOX:
			{
				DATA_CHECKBOX *chkbox=(DATA_CHECKBOX *)pitem->itemData;
				CutWSTR(ews,0);
				wsAppendChar(ews, chkbox->onoff?CBOX_CHECKED:CBOX_UNCHECKED);
				ConstructEditControl(&ec,9,ECF_APPEND_EOL,ews,1);
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_BYTE:
			{
				DATA_BYTE *dbyte=(DATA_BYTE *)pitem->itemData;
				wsprintf(ews, PERCENT_D, dbyte->initData);
				ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_MINUS|ECF_DISABLE_POINT,ews,getnumwidth(dbyte->max));
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_INT:
			{
				DATA_INT *dint=(DATA_INT *)pitem->itemData;
				wsprintf(ews, PERCENT_D, dint->initData);
				ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_MINUS|ECF_DISABLE_POINT,ews,getnumwidth(dint->max));
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_COLOR:
			{
				DATA_COLOR *color=(DATA_COLOR *)pitem->itemData;
				char *p=(char *)color->color;
				wsprintf(ews, PERCENT_02X_02X_, *p, *(p+1), *(p+2), *(p+3));
				ConstructEditControl(&ec,9,ECF_APPEND_EOL,ews,12);
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_ADDRESS:
			{
				DATA_ADDRESS *addr=(DATA_ADDRESS *)pitem->itemData;
				wsprintf(ews, PERCENT_08X, addr->addr);
				ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL|ECF_DISABLE_MINUS|ECF_DISABLE_POINT,ews,10);
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_STRING:
			{
				DATA_STRING *dstr=(DATA_STRING *)pitem->itemData;
			#ifdef BUG
				gb2ws(ews, dstr->string, dstr->maxlen?dstr->maxlen:0x10);
			#else
				wsprintf(ews, PERCENT_T, dstr->string);
			#endif
				ConstructEditControl(&ec,4,0x40,ews,dstr->maxlen?dstr->maxlen:0x10);
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_UNICODE:
			{
				DATA_UNICODE *ustr=(DATA_UNICODE *)pitem->itemData;
				uni2ws(ews, ustr->ustr, ustr->maxlen?ustr->maxlen:0x10);
				ConstructEditControl(&ec,4,0x40,ews,ustr->maxlen?ustr->maxlen:0x10);
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_HEX:
			{
				DATA_HEX *hex=(DATA_HEX *)pitem->itemData;
				hex2ws(ews, hex->hex, hex->maxlen?hex->maxlen:0x1);
				ConstructEditControl(&ec,4,0x40,ews,2*(hex->maxlen?hex->maxlen:0x1));
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_SUBMENU:
			{
			#ifdef BUG
				gb2ws(ews, LGP_ENTER, 256);
			#else
				wsprintf(ews, PERCENT_T, LGP_ENTER);
			#endif
				EDITC_OPTIONS ec_options;
				ConstructEditControl(&ec,8,ECF_APPEND_EOL,ews,256);
				SetPenColorToEditCOptions(&ec_options,2);
				SetFontToEditCOptions(&ec_options,1);
				CopyOptionsToEditControl(&ec,&ec_options);
				AddEditControlToEditQend(eq,&ec,ma);
			}
			break;
		case TYPE_POSB:
		case TYPE_POS:
			{
				DATA_POS *dpos=(DATA_POS *)pitem->itemData;
				if(dpos->off)
					wsprintf(ews, PERCENT_T, LGP_IS_OFF);
				else
					wsprintf(ews, PERCENT_D_D, dpos->x, dpos->y);
				ConstructEditControl(&ec,9,ECF_APPEND_EOL,ews,10);
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_CBOX:
			{
				DATA_CBOX *cbox=(DATA_CBOX *)pitem->itemData;
				CBOX_ITEM *cboxitem=0;
				int cur;
				int max=getMaxCBoxItem(cbox);
				if((cboxitem=getInitCBoxItem(cbox, &cur)))
				{
				#ifdef BUG
					gb2ws(ews, cboxitem->name, 256);
				#else
					wsprintf(ews, PERCENT_T, cboxitem->name);
				#endif
					ConstructComboBox(&ec, 7, ECF_APPEND_EOL, ews, 32, 0, max, cur);
					AddEditControlToEditQend(eq,&ec,ma);
				}
				else if(cboxitem=cbox->cboxitem)//use first item
				{
					cur=1;
					wsprintf(ews, PERCENT_T, cboxitem->name);
					ConstructComboBox(&ec, 7, ECF_APPEND_EOL, ews, 32, 0, max, cur);
					AddEditControlToEditQend(eq,&ec,ma);
				}
				else
				{
				#ifdef BUG
					gb2ws(ews, LGP_CBOX_ERR, 256);
				#else
					wsprintf(ews, PERCENT_T, LGP_CBOX_ERR);
				#endif
					ConstructEditControl(&ec,1,0x40,ews,256);
					AddEditControlToEditQend(eq,&ec,ma);
				}
				break;
			}
		case TYPE_SF:
			{
				DATA_SF *fs=(DATA_SF *)pitem->itemData;
				str_2ws(ews, fs->path, fs->maxlen?fs->maxlen:58);
				ConstructEditControl(&ec,4,0x40,ews,fs->maxlen?fs->maxlen:58);
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_SD:
			{
				DATA_SD *sd=(DATA_SD *)pitem->itemData;
				str_2ws(ews, sd->path, sd->maxlen?sd->maxlen:58);
				ConstructEditControl(&ec,4,0x40,ews,sd->maxlen?sd->maxlen:58);
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_SL:
			{
				DATA_SL *sl=(DATA_SL *)pitem->itemData;
				wsprintf(ews, PERCENT_D, sl->initData);
				ConstructComboBox(&ec, 7, ECF_APPEND_EOL, ews, 8, 0, sl->max+1, sl->initData+1);
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		case TYPE_MS:
			{
				DATA_MS *ms=(DATA_MS *)pitem->itemData;
				wsprintf(ews, PERCENT_D, ms->ms);
				ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_MINUS|ECF_DISABLE_POINT,ews,8);
				AddEditControlToEditQend(eq,&ec,ma);
				break;
			}
		default:
			wsprintf(ews, "%t:%d", LGP_NOTSUPPORT, type);
			ConstructEditControl(&ec,1,ECF_APPEND_EOL,ews,256);
			AddEditControlToEditQend(eq,&ec,ma);
		}
	NextItem:
		pitem=pitem->next;
	}
	
	patch_header(&ED_HDR);
	patch_input(&ED_DESC);
	return (CreateInputTextDialog(&ED_DESC, &ED_HDR, eq, 1, 0));
ex_back:
	return 0;
}



