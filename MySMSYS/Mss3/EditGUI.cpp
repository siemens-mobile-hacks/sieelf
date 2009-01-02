#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "AdrList.h"
#include "EditGUI.h"

#include "NativeAddressbook.h"
#include "CSMswaper.h"
#include "Template.h"

#ifdef	LANG_CN
#define TEXT_INPUT_OPTION ECT_CURSOR_STAY
#else
#define	TEXT_INPUT_OPTION ECT_NORMAL_TEXT
#endif

const SOFTKEY_DESC edgui_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB edgui_skt=
{
  edgui_sk,0
};

HEADER_DESC editgui_hdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};

EditGUI::EditGUI()
{
  this->edit.one=1;
  this->edit.onKey=(int (*)(GUI *, GUI_MSG *))this->OnKey;
  this->edit.global_hook_proc=(void (*)(GUI *, int ))this->GHook;
  this->edit.locret=(void *)this->Locret;
  this->edit.zero1=0;
  this->edit.softkeystab=&edgui_skt;
  this->edit.rc.x=0;
  this->edit.rc.y=0;
  this->edit.rc.x2=0;
  this->edit.rc.y2=0;
  this->edit.font=FONT_SMALL;
  this->edit._100=100;
  this->edit._101=101;
  this->edit.zero2=0;
  this->edit.zero3=0;
  this->edit._0x40000000=0x40000000;
  this->gui_prop=0;
  this->sdl=NULL;
  this->dlg_csm=NULL;
  this->gui_id=0;
  this->n_focus=0;
  this->cl=NULL;
}

EditGUI::~EditGUI()
{
}

void EditGUI::EditSendSMS(DLG_CSM *dlg_csm, WSHDR *text, const char *number)
{
  WSHDR *ws;
  int len;
  if(!dlg_csm || !text || !number)
    return;
  len=text->wsbody[0];
  if(!len || !strlen(number))
  {
    MsgBoxError(1, (int)"Nothing!!!");
    return;
  }
  ws=AllocWS(len+3);
  wstrcpy(ws, text);
  SendSMS(ws, number, MMI_CEPID, MSG_SMS_RX-1, 6);
  if(CFG_ENA_SAVE_SENT) SMSDATA->SaveMss(text, number, NULL, TYPE_OUT, 2);
  DoSendBackGround(dlg_csm);
}

#define USER_ITEM_N 4
void EditGUI::EdOpUserItem(USR_MENU_ITEM *item)
{
  if(item->type==0)
  {
    switch(item->cur_item)
    {
    case 0:
      wsprintf(item->ws, PERCENT_T, LGP->lgp.LGP_SEND);
      break;
    case 1:
      wsprintf(item->ws, PERCENT_T, LGP->lgp.LGP_ADRBK);
      break;
    case 2:
      wsprintf(item->ws, PERCENT_T, LGP->lgp.LGP_TEMPLATE);
      break;
    case 3:
      wsprintf(item->ws, PERCENT_T, LGP->lgp.LGP_CANCEL);
      break;
    }
  }
  else if(item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
      {
	EditGUI *edg=(EditGUI *)EDIT_GetUserPointer(item->user_pointer);
	EDITCONTROL ec;
	ExtractEditControl(item->user_pointer, 3, &ec);
	edg->EditSendSMS(edg->dlg_csm, ec.pWS, edg->number);
      }
      //send
      break;
    case 1:
      {
	EditGUI *edg=(EditGUI *)EDIT_GetUserPointer(item->user_pointer);
	NAbCSM *nab=new NAbCSM;
	nab->CreateNAbCSM(item->user_pointer, edg->gui_id, 0, (EDIT_GetFocus(item->user_pointer)==1)?NAB_SETC:NAB_TEXT);
      }
      //addressbook
      break;
    case 2:
      {
	TplMenu *tpm=new TplMenu;
	tpm->CreateTplMenu(item->user_pointer);
      }
      break;
      //template
    case 3:
      {
	EditGUI *edg=(EditGUI *)EDIT_GetUserPointer(item->user_pointer);
	GeneralFunc_flag1(edg->gui_id, 1);
      }
      //close
      break;
    }
  }
}

int EditGUI::OnKey(void *data, GUI_MSG *msg)
{
  SDLIST *sdl;
  EditGUI *edg=(EditGUI *)EDIT_GetUserPointer(data);
  if(!IsUnlocked()) TempLightOn(3, 0x7FFF);
/*
keys

right: 0x27
left: 0x28
up: 0x26
down: 0x25
  *: 0x14
edit
enter: 0x3

*/
  if(msg->keys==0x1)
    return 1;
  if((edg->gui_prop&ED_VIEW))
  {
    if(msg->keys==0x0F00 || msg->keys==0x0F02)
    {
      EditOptionMenu *edo=new EditOptionMenu;
      edo->CreateEditOptionMenu(edg->dlg_csm, edg->sdl, edg->gui_id, edg->list_type, (edg->gui_prop&ND_FREE)?1:0);
    }
    else if (msg->keys==0x5)
    {
      int id;
      EditGUI *edx=new EditGUI;
      if((edg->gui_prop&ND_FREE))
      {
	sdl=SMSDATA->CopyOneSDL(edg->sdl);
      }
      else sdl=edg->sdl;
      id=edx->CreateEditGUI(edg->dlg_csm, sdl, ED_REPLY, edg->list_type, (edg->gui_prop&ND_FREE)?1:0);
      if(edg->dlg_csm->gui_id==edg->gui_id && id) edg->dlg_csm->gui_id=id;
      return 1;
    }
    else if (msg->keys==0x27) //next
    {
      if ((sdl=SMSDATA->FindNextSDL(edg->sdl, edg->list_type)))
      {
	int id;
	EditGUI *edx=new EditGUI;
	id=edx->CreateEditGUI(edg->dlg_csm, sdl, ED_VIEW, edg->list_type, 0);
	if(edg->dlg_csm->gui_id==edg->gui_id && id) edg->dlg_csm->gui_id=id;
	return 1;
      }
    }
    else if (msg->keys==0x28) //prev
    {
      if ((sdl=SMSDATA->FindPrevSDL(edg->sdl, edg->list_type)))
      {
	int id;
	EditGUI *edx=new EditGUI;
	id=edx->CreateEditGUI(edg->dlg_csm, sdl, ED_VIEW, edg->list_type, 0);
	if(edg->dlg_csm->gui_id==edg->gui_id && id) edg->dlg_csm->gui_id=id;
	return 1;
      }
    }
    else if (msg->keys==0x14)
    {
      ShowMSG(1, (int)(edg->sdl->number));
    }
  }
  else
  {
    if (msg->keys==0x0F0F)
    {
      NAbCSM *nab=new NAbCSM;
      nab->CreateNAbCSM(data, edg->gui_id, 0, NAB_SETC);
    }
    else if (msg->keys==0x0F00 || msg->keys==0x0F02) //left enter
    {
      EDIT_OpenOptionMenuWithUserItems(data, edg->EdOpUserItem, data, USER_ITEM_N);
    }
    else if (msg->keys==0x5)
    {
      EDITCONTROL ec;
      ExtractEditControl(data, 3, &ec);
      edg->EditSendSMS(edg->dlg_csm, ec.pWS, edg->number);
      return 1;
    }
    else if (msg->keys==0x25) //down
    {
      EDITCONTROL ec;
      ExtractEditControl(data,edg->n_focus,&ec);
      if(EDIT_GetFocus(data)==edg->n_focus
	&&!EDIT_IsMarkModeActive(data)
	&&!EDIT_IsBusy(data)
	&&EDIT_GetCursorPos(data)>=(ec.pWS->wsbody[0]+1))
      {
	EDIT_SetFocus(data, 1);
	return -1;
      }
    }
    else if (msg->keys==0x26) //up
    {
      EDITCONTROL ec;
      ExtractEditControl(data,1,&ec);
      if(EDIT_GetFocus(data)==1
	&&!EDIT_IsMarkModeActive(data)
	&&!EDIT_IsBusy(data)
	&&EDIT_GetCursorPos(data)<=1)
      {
	EDIT_SetFocus(data, edg->n_focus);
	return -1;
      }
    }
  }
  return 0;
}

SOFTKEY_DESC SK_OPTIONS={0x0F00,0x0000,(int)LGP_NULL};
SOFTKEY_DESC SK_ADRBK={0x0F0F,0x0000,(int)LGP_NULL};
SOFTKEY_DESC SK_CANCEL={0x001,0x0000,(int)LGP_NULL};
SOFTKEY_DESC SK_OP_PIC={0x0F02,0x0000,(int)LGP_OPTION_PIC};

void EditGUI::DoSmsWorkBG(void *ed_gui, int gui_id)
{
  void *data;
  if((data=FindGUIbyId(gui_id, NULL)))
  {
    if(data==ed_gui && ((GUI *)data)->methods==((GUI *)ed_gui)->methods && ((GUI *)data)->definition==((GUI *)ed_gui)->definition)
    {
      SDLIST *sdl;
      EditGUI *edg=(EditGUI *)EDIT_GetUserPointer(data);
      if(!edg || !edg->sdl) return;
      sdl=edg->sdl;
      //set state
      if(sdl->type==TYPE_IN_N)
      {
	SMSDATA->NewToReadSMS(sdl);
      }
      //save file
      if(CFG_ENA_AUTO_SAF
	&&(!(sdl->msg_prop&ISFILE))
	&&(!(sdl->msg_prop&ISDES))
	&&(!(sdl->msg_prop&ISUNKE))
	&&(!(sdl->msg_prop&ISUNKT))
	&&(sdl->text))
      {
	int res;
	//GetCPUClock();
	res=SMSDATA->SaveMss(sdl->text, sdl->number, sdl, sdl->type, 2);
	if((unsigned int)res>>28==0xA)
	{
	  edg->sdl=(SDLIST *)res;
	  SMSDATA->DeleteMessage(sdl);
	  //SMSDATA->FreeOneSDL(sdl);
	}
      }
    }
  }
}

void EditGUI::GHook(void *data, int cmd)
{
  EditGUI *edg=(EditGUI *)EDIT_GetUserPointer(data);
  if(cmd==TI_CMD_DESTROY)
  {
    if((edg->gui_prop&ND_FREE)) SMSDATA->FreeOneSDL(edg->sdl);
    delete edg;
  }
  else if (cmd==TI_CMD_REDRAW)
  {
    SDLIST *sdl;
    EDITCONTROL ec;
    if((edg->gui_prop&ED_VIEW))
    {
      SetSoftKey(data,&SK_OP_PIC,SET_SOFT_KEY_M);
      SetSoftKey(data,&SK_OPTIONS,SET_SOFT_KEY_N);
      SetSoftKey(data,&SK_CANCEL,!SET_SOFT_KEY_N);
    }
    sdl=edg->sdl;
    // set sms state and save as file on backround
    //if(sdl && (!(sdl->msg_prop&ISFILE) || sdl->type==TYPE_IN_N))
    //{
    //  SUBPROC((void *)edg->DoSmsWorkBG, data, edg->gui_id);
    //}
    //is sdl exist
    if(!(edg->gui_prop&ND_FREE))
    {
      if(sdl && (!(sdl->msg_prop&ISFILE) || sdl->type==TYPE_IN_N))
      {
	SUBPROC((void *)edg->DoSmsWorkBG, data, edg->gui_id);
      }
      if(!SMSDATA->IsExistSDL(edg->sdl))
      {
	GeneralFunc_flag1(edg->gui_id, 1);
	return;
      }
    }
    //set header text
    ExtractEditControl(data, edg->n_focus, &ec);
    WSHDR *hdr_t=AllocWS(64);
    void *hdr_p=GetHeaderPointer(data);
    void *ma=malloc_adr();
    void *mf=mfree_adr();
    wsprintf(hdr_t, "%t: %d %d", LGP->lgp.LGP_CHAR_COUNT, ec.pWS->wsbody[0],
      IsWsSmall(ec.pWS)?((ec.pWS->wsbody[0]-1)/SEG7_MAX+1):((ec.pWS->wsbody[0]-1)/SEGN_MAX+1));
    SetHeaderText(hdr_p, hdr_t, ma, mf);
    //chkeck number
    if(!(edg->gui_prop&ED_VIEW) && EDIT_GetFocus(data)==1 && !EDIT_IsBusy(data)) //number
    {
      ExtractEditControl(data, 1, &ec);
      if(!ec.pWS->wsbody[0])
      {
	edg->cl=NULL;
	SetSoftKey(data,&SK_ADRBK,SET_SOFT_KEY_N);
      }
      else
      {
	if(IsNum(ec.pWS))
	{
	  ws_2num(ec.pWS, edg->number, 49);
	  edg->cl=ADRLST->FindCList(edg->number);
	  if(edg->cl && edg->cl->name) EDIT_SetTextToEditControl(data, 1, edg->cl->name);
	  SetSoftKey(data,&SK_OPTIONS,SET_SOFT_KEY_N);
	}
	else
	{
	  if(!edg->cl || !edg->cl->name || wstrcmp_nocase(ec.pWS, edg->cl->name))
	  {
	    WSHDR *wsx, wsxn;
	    unsigned short wsxb[32];
	    wsx=CreateLocalWS(&wsxn, wsxb, 32);
	    CutWSTR(wsx, 0);
	    EDIT_SetTextToEditControl(data, 1, wsx);
	    edg->number[0]=0;
	    edg->cl=NULL;
	    SetSoftKey(data,&SK_ADRBK,SET_SOFT_KEY_N);
	    SetSoftKey(data,&SK_CANCEL,!SET_SOFT_KEY_N);
	  }
	  else
	    SetSoftKey(data,&SK_OPTIONS,SET_SOFT_KEY_N);
	}
      }
      SetSoftKey(data,&SK_OP_PIC,SET_SOFT_KEY_M);
    }
    //set unfocused name
    /*
    if(!(edg->gui_prop&ED_VIEW) && EDIT_GetUnFocus(data)==1)
    {
      ExtractEditControl(data, 1, &ec);
      if(IsNum(ec.pWS))
      {
	ws_2num(ec.pWS, edg->number, 49);
	edg->cl=ADRLST->FindCList(edg->number);
	if(edg->cl && edg->cl->name) EDIT_SetTextToEditControl(data, 1, edg->cl->name);
      }
    }*/
    //set edit text softkey
    if(!(edg->gui_prop&ED_VIEW) && EDIT_GetFocus(data)==3 && !EDIT_IsBusy(data))
    {
      SetSoftKey(data,&SK_OPTIONS,SET_SOFT_KEY_N);
      SetSoftKey(data,&SK_OP_PIC,SET_SOFT_KEY_M);
    }
  }
  else if (cmd==0x2)
  {
    if(!(edg->gui_prop&ED_VIEW))
    {
      EDIT_SetFocus(data, edg->n_focus);
    }
  }
  else if (cmd==0xA)
  {
    DisableIDLETMR();
  }
  else if (cmd==0x5)
  {
    edg->UpdateCSMName(edg->dlg_csm, (int)((edg->gui_prop&ED_VIEW)?LGP->lgp.LGP_VIEW:LGP->lgp.LGP_EDIT));
  }
}

void EditGUI::Locret(void)
{
}

#define EDIT_FONT_DEFAULT 0
#define EDIT_FONT_SMALL 1
#define EDIT_FONT_SMALL_BOLD 2
#define EDIT_FONT_MEDIUM 3
#define EDIT_FONT_MEDIUM_BOLD 4
#define EDIT_FONT_LARGE 5
#define EDIT_FONT_LARGE_BOLD 6

int EditGUI::CreateEditGUI(DLG_CSM *dlg_csm, SDLIST *sdl, int gui_prop, int list_type, int need_free)
{
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ews, ewsn;
  CLIST *clx;
  unsigned short ewsb[MAX_TEXT];
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  if(!dlg_csm || !sdl)
  {
    delete this;
    return 0;
  }
  ews=CreateLocalWS(&ewsn, ewsb, MAX_TEXT);
  if((gui_prop&ED_VIEW)) this->edit._0x40000000=0x40000002;
  if(need_free) this->gui_prop|=ND_FREE;
  this->gui_prop|=gui_prop;
  this->sdl=sdl;
  this->dlg_csm=dlg_csm;
  this->list_type=list_type;
  eq=AllocEQueue(ma,mfree_adr());
  PrepareEditControl(&ec);
  PrepareEditCOptions(&ec_options);

  //-------number
  if(!strlen(sdl->number))
    strcpy(sdl->number, CFG_DEFAULT_SENT_NUM);
  if((clx=ADRLST->FindCList(sdl->number)))
  {
    wstrcpy(ews, clx->name);
    this->cl=clx;
  }
  else num_2ws(ews, sdl->number, 32);
  strcpy(this->number, sdl->number);
  if(!ews->wsbody[0] && (this->gui_prop&ED_VIEW))
  {
    wsprintf(ews, "%c", ' ');
  }
  ConstructEditControl(&ec,((this->gui_prop&ED_VIEW))?ECT_READ_ONLY:ECT_NORMAL_TEXT,ECF_DEFAULT_DIGIT+ECF_APPEND_EOL,ews,256);
  SetFontToEditCOptions(&ec_options,EDIT_FONT_SMALL);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);
  this->n_focus++;

  //--------time
  if((this->gui_prop&ED_VIEW))
  {
    num_2ws(ews, sdl->time, 32);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
    AddEditControlToEditQend(eq,&ec,ma);
    this->n_focus++;
  }

  //--------line
  num_2ws(ews, STR_LINES, 256);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);
  this->n_focus++;

  //--------text
  if((this->gui_prop&ED_REPLY) || !sdl->text)
    CutWSTR(ews, 0);
  else
    wstrcpy(ews, sdl->text);
  if((this->gui_prop&ED_VIEW))
  {
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,MAX_TEXT);
  }
  else
  {
    ConstructEditControl(&ec,TEXT_INPUT_OPTION,ECF_APPEND_EOL|ECF_DEFAULT_BIG_LETTER,ews,MAX_TEXT);
  }
  SetFontToEditCOptions(&ec_options,CFG_TEXT_FONT);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);
  this->n_focus++;

  patch_header(&editgui_hdr);
  patch_input(&this->edit);
  this->gui_id=CreateInputTextDialog(&this->edit, &editgui_hdr, eq, 1, this);
  return this->gui_id;
}

// option menu

/*
SOFTKEY_DESC edo_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB edo_menu_skt=
{
  edo_menu_sk,0
};
*/
const HEADER_DESC edo_menuhdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};

#define EDO_MENU_ITEM_N 6

EditOptionMenu::EditOptionMenu()
{
  this->menu.flag=8;
  this->menu.onkey=this->OnKey;
  this->menu.ghook=this->GHook;
  this->menu.proc3=NULL;
  this->menu.softkeys=softkeys;
  this->menu.softkeystab=&sel_menu_skt;
  this->menu.flags2=0x11; //icon
  this->menu.itemproc=this->ItemProc;
  this->menu.items=NULL;
  this->menu.procs=NULL;
  this->menu.n_items=0;
}

EditOptionMenu::~EditOptionMenu()
{
}

int EditOptionMenu::OnKey(void *data, GUI_MSG *msg)
{
  EditOptionMenu *edo=(EditOptionMenu *)MenuGetUserPointer(data);
  int cur=GetCurMenuItem(data);
  if(msg->keys==1)
    return 1;
  if(msg->keys==0x18 || msg->keys==0x3D)
  {
    switch(cur)
    {
    case 0:
      {
	SDLIST *sdx;
	int id;
	EditGUI *edg=new EditGUI;
	if(edo->nd_free) sdx=SMSDATA->CopyOneSDL(edo->sdl);
	else sdx=edo->sdl;
	id=edg->CreateEditGUI(edo->dlg_csm, sdx, ED_REPLY, edo->list_type, edo->nd_free);
	if(edo->dlg_csm->gui_id==edo->edit_id && id) edo->dlg_csm->gui_id=id;
      }
      GeneralFunc_flag1(edo->edit_id, 1);
      break;
    case 1:
      {
	SDLIST *sdx;
	int id;
	EditGUI *edg=new EditGUI;
	if(edo->nd_free) sdx=SMSDATA->CopyOneSDL(edo->sdl);
	else sdx=edo->sdl;
	id=edg->CreateEditGUI(edo->dlg_csm, sdx, ED_EDIT, edo->list_type, edo->nd_free);
	if(edo->dlg_csm->gui_id==edo->edit_id && id) edo->dlg_csm->gui_id=id;
      }
      GeneralFunc_flag1(edo->edit_id, 1);
      break;
    case 2:
      {
	SMSDATA->DeleteMessage(edo->sdl);
      }
      GeneralFunc_flag1(edo->edit_id, 1);
      break;
    case 3:
      if (edo->sdl)
      {
	NAbCSM *nab=new NAbCSM;
	nab->CreateNAbCSM(NULL, 0, edo->sdl->number, NAB_SAVE);
      }
      break;
    case 4:
      {
	SMSDATA->MoveToArchive(edo->sdl);
      }
      GeneralFunc_flag1(edo->edit_id, 1);
      break;
    case 5:
      GeneralFunc_flag1(edo->edit_id, 1);
      break;
    }
    return 1;
  }
  return 0;
}

void EditOptionMenu::GHook(void *data, int cmd)
{
  EditOptionMenu *edo=(EditOptionMenu *)MenuGetUserPointer(data);
  if(cmd==0x3)
  {
    delete edo;
  }
  else if (cmd==0xA)
  {
    DisableIDLETMR();
  }
  else if (cmd==0x2)
  {
    WSHDR *hdr_t=AllocWS(32);
    wsprintf(hdr_t, PERCENT_T, LGP->lgp.LGP_OPTIONS);
    SetHeaderText(GetHeaderPointer(data), hdr_t, malloc_adr(), mfree_adr());
  }
}


int EDO_ITEM_LGPS[EDO_MENU_ITEM_N]=
{
  LGP_NULL, //reply
  LGP_NULL, //edit
  LGP_NULL, //del
  LGP_SAVE_TO_AB,
  LGP_NULL, //move to archive
  LGP_NULL, //exit
};

const int EDO_ITEM_ICONS[]={ICON_BLANK,0};

void EditOptionMenu::ItemProc(void *data, int curitem, void *user_pointer)
{
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data, 150);
  wsprintf(ws, PERCENT_T, EDO_ITEM_LGPS[curitem]);
  SetMenuItemIconArray(data, item, EDO_ITEM_ICONS);
  SetMenuItemIcon(data, curitem, 0);
  SetMenuItemText(data, item, ws, curitem);
}

int EditOptionMenu::CreateEditOptionMenu(DLG_CSM *dlg_csm, SDLIST *sdl, int edit_id, int list_type, int nd_free)
{
  this->edit_id=edit_id;
  this->sdl=sdl;
  this->dlg_csm=dlg_csm;
  this->nd_free=nd_free;
  this->list_type=list_type;
  patch_option_header(&edo_menuhdr);
  return CreateMenu(&this->menu, &edo_menuhdr, 0, EDO_MENU_ITEM_N, this, 1);
}




void EditGUI::UpdateCSMName(DLG_CSM *dlg_csm, int lgp)
{
  wsprintf(&((DLGCSM_DESC *)dlg_csm->csm_ram.constr)->csm_name, PERCENT_T, lgp);
}
