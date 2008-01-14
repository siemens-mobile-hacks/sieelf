#ifndef _SCRTOOL_H_
 #define _SCRTOOL_H_ 
 #include <sieapi.h> 
 #define DAEMON  
 #define SCRTOOL_NAME "ScrTool"
 #define UPDATE_STAT 1
 #define TMR_SECOND 216
 #define MAX_IDS 15
 #define MAX_APP 14
 #define MAX_BIR 8
 #define LEN 32
 #define NoName "\xE7\xA9\xBA\xE7\x99\xBD"
 #define ExcuteTyen "File", "Shortcut", "Address", "Directory"
 #define ExcuteTycn "�ļ�", "���", "��ַ", "Ŀ¼"
 #define AgainEN "Default", "AgainLeft", "Center", "AgainRight"
 #define AgainCN "Ĭ��", "����", "����", "����"
 #define ExcuteLen 4
 #define DateFmt "YYYY/MM/DD","YYYY-MM-DD","YYYY.MM.DD","YYYY MM DD","MM/DD","MM-DD","MM.DD","MM DD","������","����"
 #define TimeFmt "13:00","PM 01:00","01:00","13:00:00","PM 01:00:00","03D00F","03D00F00M"

 #ifdef DAEMON
 typedef struct{
  CSM_RAM csm;
 }DAEMON_CSM;
 #endif
 
 typedef struct{
  CSM_RAM csm;
  int menu_id; 
  int file_id;
 }DAEMON_GUI;

 typedef struct{  
  RECT  rc;
  WSHDR *ws;
  char Pen[4];
  char Brush[4];
  int  Size;
  int  Type;
  int  Show;
 }TSCR;
 
 typedef struct{
  WSHDR *ws;  
  char  *Pic;
  char  *File;
  int    Type;
 }TAPP;
 
 extern const uint MENU_ENA;
 extern const uint INFO_ENA;
// extern const uint SCEN_ENA;
 extern const uint SHOW_EXT;
 extern const uint EXIT_BTN;
 extern const uint MODE_KBD;
#ifdef DAEMON
 extern const uint CALL_BTN; 
 extern const uint RINS_BTN;
#endif
//�������
 extern const uint OFFSET;
 extern const uint AUTO_CLOSE;
 extern const char ATEXT_CS[];
 extern const uint ATEXT_FONT;
 extern const char cfgPBDCol[];
 extern const char cfgPBGCol[];
 extern const char cfgBBDCol[];
 extern const char cfgBBGCol[];
 //û��ͼ��
 extern const char AINO[];
 //�����ڲ���ַ
 extern const int AT04;
 extern const int AT05;
 extern const int AT06;
 extern const int AT07;
 extern const int AT08;
 extern const int AT09;
 extern const int AT10;
 extern const int AT11;
 extern const int AT12;
 extern const int AT13;
 //��������
 extern const char AN04[];
 extern const char AN05[];
 extern const char AN06[];
 extern const char AN07[];
 extern const char AN08[];
 extern const char AN09[];
 extern const char AN10[];
 extern const char AN11[];
 extern const char AN12[];
 extern const char AN13[];
 //����ͼ�� 
 extern const char AIST[];
 extern const char AITO[];
 extern const char AIRT[];
 extern const char AILK[];
 extern const char AI04[]; 
 extern const char AI05[]; 
 extern const char AI06[]; 
 extern const char AI07[];
 extern const char AI08[];
 extern const char AI09[];
 extern const char AI10[];
 extern const char AI11[];
 extern const char AI12[];
 extern const char AI13[];
 //���ܵ���
 extern const char AF04[];
 extern const char AF05[];
 extern const char AF06[];
 extern const char AF07[]; 
 extern const char AF08[];
 extern const char AF09[];
 extern const char AF10[];
 extern const char AF11[];
 extern const char AF12[];
 extern const char AF13[];
 //ˢ���ٶ�
 extern const uint REFRESH;
//������������
 extern const int  NBIR_ENA;
 extern const uint NBIR_XT;
 extern const uint NBIR_X;
 extern const uint NBIR_Y;
 extern const char NBIR_CS[];
 extern const char NBIR_CB[];
 extern const uint NBIR_FONT; 
//������������
 extern const int  OBIR_ENA;
 extern const uint OBIR_XT;
 extern const uint OBIR_X;
 extern const uint OBIR_Y;
 extern const char OBIR_CS[];
 extern const char OBIR_CB[];
 extern const uint OBIR_FONT;
 extern const char BIRS_FILE[];
//��ʾ�ı�
 extern const int  TEXT_ENA;
 extern const uint TEXT_XT;
 extern const uint TEXT_X;
 extern const uint TEXT_Y;
 extern const char TEXT_CS[];
 extern const char TEXT_CB[];
 extern const uint TEXT_FONT;
 extern const char TEXT_FMT[];
//��ʾ�¶�
 extern const int  TEMP_ENA;
 extern const uint TEMP_XT;
 extern const uint TEMP_X;
 extern const uint TEMP_Y;
 extern const char TEMP_CS[];
 extern const char TEMP_CB[];
 extern const uint TEMP_FONT;
 extern const char TEMP_FMT[];
//��ʾ��ѹ
 extern const int  VOLT_ENA;
 extern const uint VOLT_XT;
 extern const uint VOLT_X;
 extern const uint VOLT_Y;
 extern const char VOLT_CS[];
 extern const char VOLT_CB[];
 extern const uint VOLT_FONT;
 extern const char VOLT_FMT[];
//��ʾ�ڴ�
 extern const int  RAM_ENA;
 extern const uint RAM_XT;
 extern const uint RAM_X;
 extern const uint RAM_Y;
 extern const char RAM_CS[];
 extern const char RAM_CB[];
 extern const uint RAM_FONT;
//��ʾ����
 extern const int  WEEK_ENA;
 extern const uint WEEK_XT;
 extern const uint WEEK_X;
 extern const uint WEEK_Y;
 extern const char WEEK_CS[];
 extern const char WEEK_CB[];
 extern const uint WEEK_FONT;
 extern const int  WEEK_FMT;
//��ʾ����
 extern const int  DATE_ENA;
 extern const uint DATE_XT;
 extern const uint DATE_X;
 extern const uint DATE_Y;
 extern const char DATE_CS[];
 extern const char DATE_CB[];
 extern const uint DATE_FONT;
 extern const int  DATE_FMT;
//��ʾʱ��
 extern const int  TIME_ENA;
 extern const uint TIME_XT;
 extern const uint TIME_X;
 extern const uint TIME_Y;
 extern const char TIME_CS[];
 extern const char TIME_CB[];
 extern const uint TIME_FONT;
 extern const int  TIME_FMT;
//��ʾũ����
 extern const int  CYEAR_ENA;
 extern const uint CYEAR_XT;
 extern const uint CYEAR_X;
 extern const uint CYEAR_Y;
 extern const char CYEAR_CS[];
 extern const char CYEAR_CB[];
 extern const uint CYEAR_FONT;
//��ʾũ������
 extern const int  CDATE_ENA;
 extern const uint CDATE_XT;
 extern const uint CDATE_X;
 extern const uint CDATE_Y;
 extern const char CDATE_CS[];
 extern const char CDATE_CB[];
 extern const uint CDATE_FONT;
//��ʾ�ź�ǿ��
 extern const int  NET_ENA;
 extern const uint NET_XT;
 extern const uint NET_X;
 extern const uint NET_Y;
 extern const char NET_CS[];
 extern const char NET_CB[];
 extern const uint NET_FONT;
 extern const char NET_FMT[];
//��ʾCPUʹ����
 extern const int  ACCU_ENA;
 extern const uint ACCU_XT;
 extern const uint ACCU_X;
 extern const uint ACCU_Y;
 extern const char ACCU_CS[];
 extern const char ACCU_CB[];
 extern const uint ACCU_FONT;
 extern const char ACCU_FMT[];
//��ʾGPRS����
 extern const int  GPRS_ENA;
 extern const uint GPRS_XT;
 extern const uint GPRS_X;
 extern const uint GPRS_Y;
 extern const char GPRS_CS[];
 extern const char GPRS_CB[];
 extern const uint GPRS_FONT;
 //��ʾCPUʹ����
 extern const int  CPU_ENA;
 extern const uint CPU_XT;
 extern const uint CPU_X;
 extern const uint CPU_Y;
 extern const char CPU_CS[];
 extern const char CPU_CB[];
 extern const uint CPU_FONT;
 extern const char CPU_FMT[];
//ת����ʽ
 extern const char BYTES_FMT[];
 extern const char BYTES_SG[];
 extern const char KBYTES_SG[];
//��������
 extern const char RINS_FILE[];
 extern const uint RINS_VOLUME;
 extern const int  RINS_ENA;
 extern const uint RINS_NUM;
 extern const uint RINS_VIB;
 extern const int  VIB_ENA;
//�Զ��ػ�
 extern const int  AUTOSD_ENA;
 extern const char AUTOSD_TIME[];
#endif
