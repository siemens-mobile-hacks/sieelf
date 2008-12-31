#ifndef _POPUPGUI_H_
#define _POPUPGUI_H_

class PopupNewIn : public CFile
{
public:
  PopupNewIn();
  ~PopupNewIn();
  int CreatePopupNewIn(DLG_CSM *dlg_csm, int dat_index);
private:
	void UpdateCSMName(DLG_CSM *dlg_csm, int lgp);
//  int GetSoundVol(void);
  POPUP_DESC popup;
  DLG_CSM *dlg_csm;
  int dat_index;
  CLIST *cl;
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
//  void SetSoundVibraByProfile(void);
  void Play(const char *fname, int sound_vol);
};

#endif



