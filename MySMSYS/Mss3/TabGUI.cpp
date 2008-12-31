#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "SmsListMenu.h"
#include "MainMenu.h"
#include "TabGUI.h"


int TABICONS[5][4]=
{
  ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,
  ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,
  ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,
  ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,
  ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,
};

TabGUI::TabGUI()
{
  tab_desc=new TABGUI_DESC;
  tab_desc->flag=8;
  tab_desc->onkey=this->OnKey;
  tab_desc->ghook=this->GHook;
  tab_desc->locret=(void *)this->Locret;
  tab_desc->softkeys=NULL;
  tab_desc->softkeystab=NULL;
}

TabGUI::~TabGUI()
{
}

#define TAB_ITEM_N 5
int TabGUI::CreateTabGUI(DLG_CSM *dlg_csm)
{
  int n, type;
  void *m_gui;
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  void *tab_gui=GetTabGUI(ma, mf);
  SetGUIDefinition(tab_gui, this->tab_desc);
  MainMenu *mm=new MainMenu;
  m_gui=mm->GetMainMenuGUI(dlg_csm);
  SetGUIToTabGUI(tab_gui, 0, TABICONS[0], m_gui);
  for(n=1;n<TAB_ITEM_N;n++)
  {
    switch(n)
    {
    case 1: type=TYPE_IN_ALL;break;
    case 2: type=TYPE_OUT;break;
    case 3: type=TYPE_DRAFT;break;
    //case 4: type=0;break;
    case 4: type=TYPE_FILTER;break;
    }
    SmsListMenu *slm=new SmsListMenu;
    m_gui=slm->GetSmsListMenuGUI(type, 1, dlg_csm);
    SetGUIToTabGUI(tab_gui, n, TABICONS[n], m_gui);
  }
  SetCursorTab(tab_gui, CFG_DEFAULT_TAB);
  UpdateTab1stItem(tab_gui, 0);
  return CreateGUI(tab_gui);
}

int TabGUI::OnKey(void *data, GUI_MSG *msg)
{
  return 0;
}

void TabGUI::GHook(void *data, int cmd)
{
  if(cmd==0x3)
  {
    TABGUI_DESC *tab_desc=(TABGUI_DESC *)(((void **)data)[8/4]);
    delete tab_desc;
  }
  else if(cmd==0x18)
  {
    int n=GetCursorTab(data);
    if(n)
    {
      int type, cnt, cur;
      void *m_gui;
      switch(n)
      {
      case 1: type=TYPE_IN_ALL;break;
      case 2: type=TYPE_OUT;break;
      case 3: type=TYPE_DRAFT;break;
      //case 4: type=0;break;
      case 4: type=TYPE_FILTER;break;
      default : type=0;break;
      }
      m_gui=GetGuiByTab(data, n);
      if(m_gui)
      {
	//SmsListMenu *slm=(SmsListMenu *)MenuGetUserPointer(m_gui);
        cnt=SMSDATA->GetSMSCount(type);
        cur=GetCurMenuItem(m_gui);
        if(cur>=cnt) SetCursorToMenuItem(m_gui, 0);
        Menu_SetItemCountDyn(m_gui, cnt);
      }
    }
    void **methods=(void **)((GUI *)data)->methods;
    ((void (*)(void *))methods[0])(data);
  }
  else if(cmd==0xA)
  {
    DisableIDLETMR();
  }
}

void TabGUI::Locret(void)
{
}


