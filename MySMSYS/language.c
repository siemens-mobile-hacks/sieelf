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
const char LGP_MSG_REVEICED[]="Message received at"; //���ʱ��
const char LGP_UNK_RP_STATUS[]="SMS Report: Unknow Status";
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
const char LGP_ALL[]="ȫ����Ϣ";
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
const char STR_FROM[]="����";
const char STR_CODESHOW[]="������";
const char STR_FETION[]="����";
const char LGP_SAVEALL[]="��������Ϊ�ļ�";
const char LGP_CONFIG_UPDATE[]="MySMSYS ���ø���!";
const char STR_UNK_NUM[]="δ֪����";
const char STR_NUMBER[]="����";
const char STR_TEXT[]="����";
const char STR_TO[]="���͵�";
const char STR_TIME[]="ʱ��";
const char STR_UNK[]="δ֪";
const char LGP_CONFIG[]="����...";
const char LGP_SAVE_ALL_ONE[]="�������е�TXT";
const char LGP_PLS_INPUT_PATH[]="�������ļ�·��:";
const char LGP_OTHERS[]="����...";
const char STR_UNK_NUM_UTF8[]="\xE6\x9C\xAA\xE7\x9F\xA5\xE5\x8F\xB7\xE7\xA0\x81";
const char STR_NUMBER_UTF8[]="\xE5\x8F\xB7\xE7\xA0\x81";
const char STR_TEXT_UTF8[]="\xE6\xAD\xA3\xE6\x96\x87";
const char STR_TO_UTF8[]="\xE5\x8F\x91\xE9\x80\x81\xE5\x88\xB0";
const char STR_FROM_UTF8[]="\xE6\x9D\xA5\xE8\x87\xAA";
const char STR_TIME_UTF8[]="\xE6\x97\xB6\xE9\x97\xB4";
const char STR_UNK_UTF8[]="\xE6\x9C\xAA\xE7\x9F\xA5";
const char LGP_FILE_FAILED[]="�ļ�����ʧ��!";
const char LGP_FILE_EXIST[]="�ļ��Ѵ���!";
const char LGP_EXPORT_TXT[]="����ΪTXT";
const char LGP_MOVE_ARCHIVE[]="�ƶ���������";
const char LGP_MOVE_ALL_MSS[]="ȫ��MSS�Ƶ�������";
const char LGP_OPEN_ARCHIVE[]="�򿪵�����";
const char STR_EXPORT_N[]="�ɹ�����%d������!";
const char STR_MOVE_MSSARCHIVER_N[]="�ɹ�ת��%d��Mss�ļ�!";
const char LGP_DEL_ALL_MSS[]="ɾ������Mss�ļ�?";
const char LGP_ABOUT[]="����...";
const char LGP_COV_DAT_TXT[]="ת��SMS.dat��Txt";
const char LGP_SAVE_ALL_AS_FILE[]="�������е��ļ�";
const char STR_SAF_N[]="�ɹ�����%d������!";
const char LGP_DEL_ALL[]="ɾ��������Ϣ?";
const char LGP_DEL_ALL_MSG[]="ɾ��������Ϣ";
const char LGP_MOVE_ALL[]="ȫ���Ƶ�������";
const char LGP_DEL_ALL_MSG_MSS[]="ɾ������Mss�ļ�";
const char LGP_SAVE[]="����";
const char LGP_MSG_REPORT[]="��Ϣ����";
const char LGP_MSG_REVEICED[]="��Ϣ���յ���"; //���ʱ��
const char LGP_UNK_RP_STATUS[]="SMS Report: Unknow Status";
#endif

