//#define LANG_CN

extern const char my_ipc_name[];
extern const char ELFNAME[];
extern const char ELFNAME_D[];
extern const char COPY_RIGHT[];

extern const char FLDR_IN[];
extern const char FLDR_OUT[];
extern const char FLDR_DRAFT[];
//extern const char FLDR_MAIN[];
extern const char FLDR_UNK[];
extern const char FLDR_ARCHIVE[];

extern const char PERCENT_T[];
extern const char PERCENT_S[];
extern const char num_fetion[];

extern const char LGP_OK[];
extern const char LGP_BACK[];
extern const char LGP_ADRBK[];
extern const char LGP_ERR[];
extern const char LGP_SELECT[];
extern const char LGP_QUIT[];

extern const char LGP_NEW[];
extern const char LGP_IN_R[];
extern const char LGP_IN_N[];
extern const char LGP_IN_A[];
extern const char LGP_OUT[];
extern const char LGP_DRAFT[];
extern const char LGP_ALL[];
extern const char LGP_OPTIONS[];

extern const char LGP_ERR_0NUM[];
extern const char LGP_EXIT[];

extern const char LGP_CANCEL[];
extern const char LGP_SEND[];
extern const char LGP_DEL[];
//extern const char LGP_BACK[];
extern const char LGP_SAVE_AS_DRAFT[];
extern const char LGP_SAVE_AS_FILE[];
extern const char LGP_INSERT_ADRNUM[];
extern const char LGP_INSERT_BLANKNUM[];
extern const char LGP_CHAR_COUNT[];
extern const char STR_REPLY[];
extern const char STR_UNK_ED[];
extern const char STR_VIEW[];
extern const char STR_EDIT[];
extern const char STR_LINES[];
extern const char STR_UNK_TXTT[];
extern const char STR_UNK_TYPE[];
extern const char STR_NEW_MSG[];
extern const char STR_FROM[];
extern const char LGP_SAVEALL[];
extern const char LGP_CONFIG_UPDATE[];

#ifndef NO_CS
extern const char STR_CODESHOW[];
extern const char STR_FETION[];
#endif

extern const char STR_UNK_NUM[];
extern const char STR_NUMBER[];
extern const char STR_TEXT[];
extern const char STR_TO[];
extern const char LGP_CONFIG[];
extern const char LGP_CONFIG[];
extern const char LGP_SAVE_ALL_ONE[];
extern const char LGP_PLS_INPUT_PATH[];
extern const char LGP_OTHERS[];
extern const char STR_UNK_NUM_UTF8[];
extern const char STR_NUMBER_UTF8[];
extern const char STR_TEXT_UTF8[];
extern const char STR_TO_UTF8[];
extern const char STR_FROM_UTF8[];
extern const char LGP_FILE_FAILED[];
extern const char LGP_FILE_EXIST[];
extern const char LGP_EXPORT_TXT[];
extern const char LGP_MOVE_ARCHIVE[];
extern const char LGP_MOVE_ALL_MSS[];
extern const char LGP_OPEN_ARCHIVE[];
extern const char STR_EXPORT_N[];
extern const char STR_MOVE_MSSARCHIVER_N[];
extern const char STR_TIME_UTF8[];
extern const char STR_UNK_UTF8[];
extern const char STR_TIME[];
extern const char STR_UNK[];
extern const char LGP_DEL_ALL_MSS[];
extern const char LGP_ABOUT[];
extern const char LGP_COV_DAT_TXT[];
extern const char LGP_SAVE_ALL_AS_FILE[];
extern const char STR_SAF_N[];
extern const char LGP_DEL_ALL[];
extern const char LGP_MOVE_ALL[];
extern const char LGP_DEL_ALL_MSG[];
extern const char LGP_DEL_ALL_MSG_MSS[];
extern const char LGP_SAVE[];
extern const char LGP_MSG_REPORT[];
extern const char LGP_MSG_REVEICED[]; //后加时间
extern const char LGP_UNK_RP_STATUS[];
extern const char LGP_TEMPLATE[];
extern const char LGP_CALL_ADDRESSBOOK[];
#ifdef LANG_CN
#define LGP_CFG_MAIN_FOLDER "MySMSYS文件夹"
#define LGP_CFG_SYSTEM_FOLDER "系统文件夹"
#define LGP_CFG_ENA_NOTIFY "弹出新信息窗口"
#define LGP_CFG_VIBRA_POWER "振动强度"
#define LGP_CFG_NOTIFY_SET "新信息提醒设置"
#define LGP_CFG_NOTIFY_TIME "提醒时间长度(秒)"
#define LGP_CFG_ENA_AUTO_SAF "自动保存为文件"
#define LGP_CFG_ENA_NEWSMS_ICON "待机显示新短信图标"
#define LGP_CFG_ICONNEW_PATH "图标文件路径"
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
#define LGP_CFG_ICONNEW_PATH "Icon Path"
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
