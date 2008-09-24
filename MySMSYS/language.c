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

const char LGP_OK[]="ȷ��";
const char LGP_BACK[]="����";
const char LGP_ADRBK[]="ͨѶ¼";
const char LGP_ERR[]="Error!";
const char LGP_SELECT[]="ѡ��";
const char LGP_QUIT[]="�˳�";
const char LGP_NEW[]="�½�����";
const char LGP_IN_R[]="�Ѷ�����";
const char LGP_IN_N[]="δ������";
const char LGP_IN_A[]="�ռ���";
const char LGP_OUT[]="�ѷ���";
const char LGP_DRAFT[]="�ݸ�";
const char LGP_ALL[]="������Ϣ";
const char LGP_OPTIONS[]="ѡ��";
const char LGP_ERR_0NUM[]="�޺���!";
const char LGP_EXIT[]="�뿪";

const char LGP_CANCEL[]="ȡ��";
const char LGP_SEND[]="����";
const char LGP_DEL[]="ɾ��";
const char LGP_SAVE_AS_FILE[]="ת��Ϊ�ļ�";
const char LGP_SAVE_AS_DRAFT[]="����Ϊ�ݸ�";
const char LGP_INSERT_ADRNUM[]="��ͨѶ¼����";
const char LGP_INSERT_BLANKNUM[]="����հ׺���";
const char LGP_CHAR_COUNT[]="����";

const char STR_VIEW[]="�鿴";
const char STR_EDIT[]="�༭";
const char STR_REPLY[]="�ظ�";

const char STR_NEW_MSG[]="����Ϣ!";
const char STR_FROM[]="����:";
const char LGP_SAVEALL[]="��������Ϊ�ļ�";
#endif

