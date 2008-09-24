#include "language.h"
#include "MySMSYS_ipc.h"

const char my_ipc_name[]=MY_SMSYS_IPC_NAME;

const char ELFNAME[]="MySMSYS";
const char ELFNAME_D[]="MySMSYS_D";
const char COPY_RIGHT[]="MySMSYS\n(c)BingK(binghelingxi)\n(r)titron";

const char PERCENT_T[]="%t";

const char STR_UNK_ED[]="Unknow EdGUI Type (%d)!";
const char STR_LINES[]="----------------";
const char STR_UNK_TXTT[]="Unkown Text Encode Type (%d)!";
const char STR_UNK_TYPE[]="Unknow Type (%d)!";

const char FLDR_IN[]="In\\";
const char FLDR_OUT[]="Out\\";
const char FLDR_DRAFT[]="Draft\\";
const char FLDR_MAIN[]="0:\\ZBin\\MySMSYS\\";
const char FLDR_UNK[]="Unknow\\";

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
const char LGP_ALL[]="所有信息";
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
const char STR_FROM[]="来自:";
const char LGP_SAVEALL[]="保存所有为文件";
#endif

