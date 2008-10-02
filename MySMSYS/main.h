
typedef struct
{
	char numhdr[64];
	char adlhdr[64];
	char edtihdr[64];
	char edophdr[64];
	char slhdr[64];
}HDR_TEXTS;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
  int sdl_update;
  void *gstop;
}DLG_CSM;


typedef struct
{
	WSHDR *txt;
	WSHDR *time;
}INBOX_DATA;

extern int new_sms_n;
int CreateMainMenu(DLG_CSM *dlg_csm);

