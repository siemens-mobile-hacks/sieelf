#ifndef _TABGUI_H_
#define _TABGUI_H_
class TabGUI
{
public:
	int ReCreateTabGUI(DLG_CSM *dlg_csm);
//	int CreateTabGUI(DLG_CSM *dlg_csm, int cur1, int cur2, int cur3, int  cur4, int cur5);
  TabGUI();
  ~TabGUI();
  int CreateTabGUI(DLG_CSM *dlg_csm);
private:
  TABGUI_DESC *tab_desc;
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
  static void Locret(void);
};
#endif


