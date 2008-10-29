
extern const char my_ipc_name[];
extern const char ELFNAME[];
extern const char ELFNAME_D[];
extern const char COPY_RIGHT[];

extern const char FLDR_IN[];
extern const char FLDR_OUT[];
extern const char FLDR_DRAFT[];
extern const char FLDR_UNK[];
extern const char FLDR_ARCHIVE[];

extern const char PERCENT_T[];
extern const char PERCENT_S[];
extern const char num_fetion[];
extern const char STR_LINES[];
extern const char STR_UNK_TXTT[];
extern const char STR_UNK_TYPE[];

#ifdef LANG_CN
#define LGP_CFG_MAIN_FOLDER "MySMSYS文件夹"
#define LGP_CFG_SYSTEM_FOLDER "系统文件夹"
#define LGP_CFG_ENA_NOTIFY "弹出新信息窗口"
#define LGP_CFG_VIBRA_POWER "振动强度"
#define LGP_CFG_NOTIFY_SET "新信息提醒设置"
#define LGP_CFG_NOTIFY_TIME "提醒时间长度(秒)"
#define LGP_CFG_ENA_AUTO_SAF "自动保存为文件"
#define LGP_CFG_ENA_NEWSMS_ICON "待机显示新短信图标"
#define LGP_CFG_ICONNEW_PATH "图标"
#define LGP_CFG_ICONNEW_POS "图标坐标"
#define LGP_CFG_EXPORT_CHARSET "导出文本字符编码"
#define LGP_CFG_ENA_SAVE_SENT "保存已发送短信"
#define LGP_CFG_ENA_SOUND "使用声音提醒"
#define LGP_CFG_SOUND_VOL "音量"
#define LGP_CFG_SOUND_PATH "声音文件路径"
#define LGP_CFG_ENA_AUTO_DEL_RP "自动删除信息报告"
#define LGP_CFG_ENA_EXIT_SAVE_DRAFT "保存草稿后退出"
#define LGP_CFG_TEXT_FONT "文本字体"
#define LGP_EDIT_FONT_DEFAULT "使用默认" 
#define LGP_EDIT_FONT_SMALL "小号字体"
#define LGP_EDIT_FONT_SMALL_BOLD "小字体加粗"
#define LGP_EDIT_FONT_MEDIUM "中号字体"
#define LGP_EDIT_FONT_MEDIUM_BOLD "中字体加粗"
#define LGP_EDIT_FONT_LARGE "大号字体"
#define LGP_EDIT_FONT_LARGE_BOLD "大字体加粗"
#endif

#ifdef LANG_EN
#define LGP_CFG_MAIN_FOLDER "MySMSYS Folder"
#define LGP_CFG_SYSTEM_FOLDER "System Folder"
#define LGP_CFG_ENA_NOTIFY "Popup New SMS"
#define LGP_CFG_VIBRA_POWER "Vibra Power"
#define LGP_CFG_NOTIFY_SET "Notify Setup"
#define LGP_CFG_NOTIFY_TIME "Notify Time (s)"
#define LGP_CFG_ENA_AUTO_SAF "Auto Save As File"
#define LGP_CFG_ENA_NEWSMS_ICON "Show NewSMS Icon Idle"
#define LGP_CFG_ICONNEW_PATH "Icon"
#define LGP_CFG_ICONNEW_POS "Icon Position"
#define LGP_CFG_EXPORT_CHARSET "Export Text Charset"
#define LGP_CFG_ENA_SAVE_SENT "Save Sent SMS"
#define LGP_CFG_ENA_SOUND "Enable Sound Notify"
#define LGP_CFG_SOUND_VOL "Volume"
#define LGP_CFG_SOUND_PATH "Sound File Path"
#define LGP_CFG_ENA_AUTO_DEL_RP "Auto Delete Message Report"
#define LGP_CFG_ENA_EXIT_SAVE_DRAFT "Exit After Save Draft"
#define LGP_CFG_TEXT_FONT "Text Font"
#define LGP_EDIT_FONT_DEFAULT "Default" 
#define LGP_EDIT_FONT_SMALL "Small"
#define LGP_EDIT_FONT_SMALL_BOLD "Small+Bold"
#define LGP_EDIT_FONT_MEDIUM "Medium"
#define LGP_EDIT_FONT_MEDIUM_BOLD "Medium+Bold"
#define LGP_EDIT_FONT_LARGE "Large"
#define LGP_EDIT_FONT_LARGE_BOLD "Large+Bold"
#endif

typedef struct{
  const char *LGP_OK;
  const char *LGP_BACK;
  const char *LGP_ADRBK;
  const char *LGP_ERR;
  const char *LGP_SELECT;
  const char *LGP_QUIT;
  const char *LGP_NEW;
  const char *LGP_IN_R;
  const char *LGP_IN_N;
  const char *LGP_IN_A;
  const char *LGP_OUT;
  const char *LGP_DRAFT;
  const char *LGP_ALL;
  const char *LGP_OPTIONS;
  const char *LGP_ERR_0NUM;
  const char *LGP_EXIT;
  const char *LGP_CANCEL;
  const char *LGP_SEND;
  const char *LGP_DEL;
  const char *LGP_SAVE_AS_FILE;
  const char *LGP_SAVE_AS_DRAFT;
  const char *LGP_INSERT_ADRNUM;
  const char *LGP_INSERT_BLANKNUM;
  const char *LGP_CHAR_COUNT;
  const char *LGP_VIEW;
  const char *LGP_EDIT;
  const char *LGP_REPLY;
  const char *LGP_NEW_MSG;
  const char *LGP_FROM;
  const char *LGP_CODESHOW;
  const char *LGP_FETION;
  const char *LGP_SAVEALL;
  const char *LGP_CONFIG_UPDATE;
  const char *LGP_CONFIG;
  const char *LGP_SAVE_ALL_ONE;
  const char *LGP_PLS_INPUT_PATH;
  const char *LGP_OTHERS;
  const char *LGP_FILE_FAILED;
  const char *LGP_FILE_EXIST;
  const char *LGP_EXPORT_TXT;
  const char *LGP_MOVE_ARCHIVE;
  const char *LGP_MOVE_ALL_MSS;
  const char *LGP_OPEN_ARCHIVE;
  const char *LGP_EXPORT_N;
  const char *LGP_MOVE_MSSARCHIVER_N;
  const char *LGP_DEL_ALL_MSS;
  const char *LGP_ABOUT;
  const char *LGP_COV_DAT_TXT;
  const char *LGP_SAVE_ALL_AS_FILE;
  const char *LGP_SAF_N;
  const char *LGP_DEL_ALL;
  const char *LGP_DEL_ALL_MSG;
  const char *LGP_MOVE_ALL;
  const char *LGP_DEL_ALL_MSG_MSS;
  const char *LGP_SAVE;
  const char *LGP_MSG_REPORT;
  const char *LGP_MSG_REVEICED; //后加时间
  const char *LGP_UNK_RP_STATUS;
  const char *LGP_TEMPLATE;
  const char *LGP_CALL_ADDRESSBOOK;
  const char *LGP_STATISTICS;
  const char *LGP_IN_SMSDAT;
  const char *LGP_IS_MSSFILE;
  const char *LGP_DAT_FREE;
  const char *LGP_DISK_FREE;
  const char *LGP_MSS_MAINMENU;
  const char *LGP_TRANSLIT;
  const char *LGP_TIME;
  const char *LGP_UNK_NUM;
  const char *LGP_NUMBER;
  const char *LGP_TEXT;
  const char *LGP_TO;
  const char *LGP_UNK;
}LGPACK;

extern LGPACK lgp;
/*
extern const char STR_FROM[];
extern const char STR_UNK_NUM[];
extern const char STR_NUMBER[];
extern const char STR_TEXT[];
extern const char STR_TO[];
extern const char STR_TIME[];
extern const char STR_UNK[];
*/
extern const char STR_UNK_NUM_UTF8[];
extern const char STR_NUMBER_UTF8[];
extern const char STR_TEXT_UTF8[];
extern const char STR_TO_UTF8[];
extern const char STR_FROM_UTF8[];
extern const char STR_TIME_UTF8[];
extern const char STR_UNK_UTF8[];

//-------------
void LoadLangPack(void);
void FreeLangPack(void);




