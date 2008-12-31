#ifndef _SMSLISTMENU_H_
#define _SMSLISTMENU_H_


class SmsListMenu :
  public CrtMenu
{
public:
  SmsListMenu();
  ~SmsListMenu();
  int CreateSmsListMenu(int type, int is_tab, DLG_CSM *dlg_csm);
  void *GetSmsListMenuGUI(int type, int is_tab, DLG_CSM *dlg_csm);
private:
	void UpdateCSMName(DLG_CSM *dlg_csm, int lgp);
  ML_MENU_DESC menu;
  int gui_id;
  int type;
  int is_tab;
  DLG_CSM *dlg_csm;
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
  static void ItemProc(void *data, int curitem, void *user_pointer);
};


class SmsOptionMenu :
  public CrtMenu
{
public :
  SmsOptionMenu();
  ~SmsOptionMenu();
  int CreateSmsOptionMenu(DLG_CSM *dlg_csm, int slm_id, int list_type, SDLIST *sdl);
private:
  MENU_DESC menu;
  DLG_CSM *dlg_csm;
  SDLIST *sdl;
  int slm_id;
  int list_type;
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
  static void ItemProc(void *data, int curitem, void *user_pointer);
};
#endif


