#include "language.h"
#include "MySMSYS_ipc.h"

const char my_ipc_name[]=MY_SMSYS_IPC_NAME;

const char ELFNAME[]="MySMSYS";
const char ELFNAME_D[]="MssD";
const char COPY_RIGHT[]="MySMSYS v1.8.4\n(c)BingK (binghelingxi)\n(r)titron";

const char PERCENT_T[]="%t";
const char PERCENT_S[]="%s";
const char num_fetion[]="12520";

const char STR_UNK_ED[]="Unknow EdGUI Type (%d)!";
const char STR_LINES[]="----------------";
const char STR_UNK_TXTT[]="Unkown Text Encode Type (%d)!";
const char STR_UNK_TYPE[]="Unknow Type (%d)!";

const char FLDR_IN[]="In\\";
const char FLDR_OUT[]="Out\\";
const char FLDR_DRAFT[]="Draft\\";
//const char FLDR_MAIN[]="0:\\ZBin\\MySMSYS\\";
const char FLDR_UNK[]="Unknow\\";
const char FLDR_ARCHIVE[]="Archive\\";

#ifdef LANG_EN
const char LGP_OK[]="OK";
const char LGP_BACK[]="Back";
const char LGP_ADRBK[]="AddressBook";
const char LGP_ERR[]="Error!";
const char LGP_SELECT[]="Select";
const char LGP_QUIT[]="Quit";
const char LGP_NEW[]="NewSMS";
const char LGP_IN_R[]="InReaded";
const char LGP_IN_N[]="InNew";
const char LGP_IN_A[]="InBox";
const char LGP_OUT[]="Sent";
const char LGP_DRAFT[]="Draft";
const char LGP_ALL[]="AllSMS";
const char LGP_OPTIONS[]="Options";
const char LGP_ERR_0NUM[]="No Number !";
const char LGP_EXIT[]="Exit";

const char LGP_CANCEL[]="Cancel";
const char LGP_SEND[]="Send";
const char LGP_DEL[]="Delete";
const char LGP_SAVE_AS_FILE[]="Save As File";

const char LGP_SAVE_AS_DRAFT[]="Save As Draft";

const char LGP_INSERT_ADRNUM[]="Insert Number Form AddressBook";
const char LGP_INSERT_BLANKNUM[]="Inert Blank Number";
const char LGP_CHAR_COUNT[]="";

const char STR_VIEW[]="View";
const char STR_EDIT[]="Edit";
const char STR_REPLY[]="Reply";

const char STR_NEW_MSG[]="New Message!";
const char STR_FROM[]="From:";
const char LGP_SAVEALL[]="Save All As File";
const char LGP_CONFIG_UPDATE[]="MySMSYS Config Updated!";
const char STR_UNK_NUM[]="Unknow Number";
const char STR_NUMBER[]="Number";
const char STR_TEXT[]="Text";
const char STR_TO[]="To";
const char STR_TIME[]="Time";
const char STR_UNK[]="Unknow";
const char LGP_CONFIG[]="Setting";
const char LGP_SAVE_ALL_ONE[]="Export All To One TXT";
const char LGP_PLS_INPUT_PATH[]="Please Input The File Path:";
const char LGP_OTHERS[]="Others";
const char STR_UNK_NUM_UTF8[]="Unknow Number";
const char STR_NUMBER_UTF8[]="Number";
const char STR_TEXT_UTF8[]="Text";
const char STR_TO_UTF8[]="To";
const char STR_FROM_UTF8[]="From";
const char STR_TIME_UTF8[]="Time";
const char STR_UNK_UTF8[]="Unknow";
const char LGP_FILE_FAILED[]="File Operate Failed!";
const char LGP_FILE_EXIST[]="File Existed!";
const char LGP_EXPORT_TXT[]="Export As Txt";
const char LGP_MOVE_ARCHIVE[]="Move To Archive";
const char LGP_MOVE_ALL_MSS[]="Move All MSS To Archive";
const char LGP_OPEN_ARCHIVE[]="Open Archive";
const char STR_EXPORT_N[]="Export %d SMS Successfully!";
const char STR_MOVE_MSSARCHIVER_N[]="Move %d Mss File to Archive Successfully!";
const char LGP_DEL_ALL_MSS[]="Delete All Mss Files?";
const char LGP_ABOUT[]="About...";
const char LGP_COV_DAT_TXT[]="Cov SMS.dat To Txt";
const char LGP_SAVE_ALL_AS_FILE[]="Save All As Files";
const char STR_SAF_N[]="Save %d SMS Successfully!";
const char LGP_DEL_ALL[]="Delete All?";
const char LGP_DEL_ALL_MSG[]="Delete All Message";
const char LGP_MOVE_ALL[]="Move All To Archive";
const char LGP_DEL_ALL_MSG_MSS[]="Delete All Mss";
const char LGP_SAVE[]="Save";
const char LGP_MSG_REPORT[]="Message Report";
const char LGP_MSG_REVEICED[]="Message received at"; //后加时间
const char LGP_UNK_RP_STATUS[]="SMS Report: Unknow Status";
#endif

#ifdef LANG_CN

const char LGP_OK[]="确定";
const char LGP_BACK[]="返回";
const char LGP_ADRBK[]="通讯录";
const char LGP_ERR[]="Error!";
const char LGP_SELECT[]="选择";
const char LGP_QUIT[]="退出";
const char LGP_NEW[]="新建短信";
const char LGP_IN_R[]="已读短信";
const char LGP_IN_N[]="未读短信";
const char LGP_IN_A[]="收件箱";
const char LGP_OUT[]="已发送";
const char LGP_DRAFT[]="草稿";
const char LGP_ALL[]="全部信息";
const char LGP_OPTIONS[]="选项";
const char LGP_ERR_0NUM[]="无号码!";
const char LGP_EXIT[]="离开";

const char LGP_CANCEL[]="取消";
const char LGP_SEND[]="发送";
const char LGP_DEL[]="删除";
const char LGP_SAVE_AS_FILE[]="转存为文件";
const char LGP_SAVE_AS_DRAFT[]="保存为草稿";
const char LGP_INSERT_ADRNUM[]="从通讯录插入";
const char LGP_INSERT_BLANKNUM[]="插入空白号码";
const char LGP_CHAR_COUNT[]="字数";

const char STR_VIEW[]="查看";
const char STR_EDIT[]="编辑";
const char STR_REPLY[]="回复";

const char STR_NEW_MSG[]="新信息!";
const char STR_FROM[]="来自";
const char STR_CODESHOW[]="区号秀";
const char STR_FETION[]="飞信";
const char LGP_SAVEALL[]="保存所有为文件";
const char LGP_CONFIG_UPDATE[]="MySMSYS 配置更新!";
const char STR_UNK_NUM[]="未知号码";
const char STR_NUMBER[]="号码";
const char STR_TEXT[]="正文";
const char STR_TO[]="发送到";
const char STR_TIME[]="时间";
const char STR_UNK[]="未知";
const char LGP_CONFIG[]="配置...";
const char LGP_SAVE_ALL_ONE[]="导出所有到TXT";
const char LGP_PLS_INPUT_PATH[]="请输入文件路径:";
const char LGP_OTHERS[]="其它...";
const char STR_UNK_NUM_UTF8[]="\xE6\x9C\xAA\xE7\x9F\xA5\xE5\x8F\xB7\xE7\xA0\x81";
const char STR_NUMBER_UTF8[]="\xE5\x8F\xB7\xE7\xA0\x81";
const char STR_TEXT_UTF8[]="\xE6\xAD\xA3\xE6\x96\x87";
const char STR_TO_UTF8[]="\xE5\x8F\x91\xE9\x80\x81\xE5\x88\xB0";
const char STR_FROM_UTF8[]="\xE6\x9D\xA5\xE8\x87\xAA";
const char STR_TIME_UTF8[]="\xE6\x97\xB6\xE9\x97\xB4";
const char STR_UNK_UTF8[]="\xE6\x9C\xAA\xE7\x9F\xA5";
const char LGP_FILE_FAILED[]="文件操作失败!";
const char LGP_FILE_EXIST[]="文件已存在!";
const char LGP_EXPORT_TXT[]="导出为TXT";
const char LGP_MOVE_ARCHIVE[]="移动到档案柜";
const char LGP_MOVE_ALL_MSS[]="全部MSS移到档案柜";
const char LGP_OPEN_ARCHIVE[]="打开档案柜";
const char STR_EXPORT_N[]="成功导出%d条短信!";
const char STR_MOVE_MSSARCHIVER_N[]="成功转移%d个Mss文件!";
const char LGP_DEL_ALL_MSS[]="删除所有Mss文件?";
const char LGP_ABOUT[]="关于...";
const char LGP_COV_DAT_TXT[]="转换SMS.dat到Txt";
const char LGP_SAVE_ALL_AS_FILE[]="保存所有到文件";
const char STR_SAF_N[]="成功保存%d条短信!";
const char LGP_DEL_ALL[]="删除所有信息?";
const char LGP_DEL_ALL_MSG[]="删除所有信息";
const char LGP_MOVE_ALL[]="全部移到档案柜";
const char LGP_DEL_ALL_MSG_MSS[]="删除所有Mss文件";
const char LGP_SAVE[]="保存";
const char LGP_MSG_REPORT[]="信息报告";
const char LGP_MSG_REVEICED[]="信息已收到于"; //后加时间
const char LGP_UNK_RP_STATUS[]="SMS Report: Unknow Status";
#endif

