#ifndef _SCRTOOL_H_
 #define _SCRTOOL_H_ 
 #include <sieapi.h>
 #ifdef NEWSGOLD
  #define DEFAULT_DISK "4"
 #else
  #define DEFAULT_DISK "0"
 #endif 
 #define DAEMON  
 #define SCRTOOL_NAME "ScrTool"
 #define UPDATE_STAT 1
 #define TMR_SECOND 216
 #define MAX_IDS 14
 #define MAX_APP 14
 #define MAX_BIR 8
 #define LEN 32
 #define FontStyle "00","01","02","03","04","05","06","07","08","09","10","11"
 #define NoName "\xE7\xA9\xBA\xE7\x99\xBD"
 #define ExcuteType "File", "Shortcut", "Address", "Path"
 #define ExcuteLen 4
 #define DateFmt "YYYY/MM/DD","YYYY-MM-DD","YYYY.MM.DD","YYYY MM DD","MM/DD","MM-DD","MM.DD","MM DD","������","����"
 #define TimeFmt "13:00","PM 01:00","01:00","13:00:00","PM 01:00:00","03D00F","03D00F00M"
 #define DateStyle "NewStyle", "OldStyle"
 
 #ifdef DAEMON
 typedef struct{
  CSM_RAM csm;
 }MAIN_CSM;
 #endif
 
 typedef struct{
  CSM_RAM csm;
  int tool_id; 
  int menu_id;
 }MAIN_CSM_GUI;

 typedef struct{  
  RECT rc;
  WSHDR *ws;
  char Pen[4];
  char Brush[4];
  int Size;
  int Type;
  int show;
 }TSCR;
 
 typedef struct{
  WSHDR *ws;  
  char  *Pic;
  char  *File;
  int    Type;
 }TAPP;
 
 typedef struct{
  WSHDR *dt;
  WSHDR *ws;
  int Type;
 }TBIR;
 
 typedef struct{
  WSHDR *nd;
  WSHDR *od;
 }TBIRS; 
 

 extern const int MENU_ENA;
 extern const int INFO_ENA;
 extern const int SHOW_EXT;
 extern const uint EXIT_BTN;
#ifdef DAEMON
 extern const uint CALL_BTN;
#endif
//�������
 extern const uint OFFSET;
 extern const uint AUTO_CLOSE;
 extern const char APPTEXT_COLORS[4];
 extern const char APPTEXT_FCOLOR[4];
 extern const uint APPTEXT_FONT;
 extern const char cfgPanBorderCol[4];
 extern const char cfgPanBGCol[4];
 extern const char cfgBookBorderCol[4];
 extern const char cfgBookBGCol[4];
 //û��ͼ��
 extern const char AINO[64];
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
 extern const char AN04[LEN];
 extern const char AN05[LEN];
 extern const char AN06[LEN];
 extern const char AN07[LEN];
 extern const char AN08[LEN];
 extern const char AN09[LEN];
 extern const char AN10[LEN];
 extern const char AN11[LEN];
 extern const char AN12[LEN];
 extern const char AN13[LEN];
 //����ͼ�� 
 extern const char AIST[64];
 extern const char AITO[64];
 extern const char AIRT[64];
 extern const char AILK[64];
 extern const char AI04[64]; 
 extern const char AI05[64]; 
 extern const char AI06[64]; 
 extern const char AI07[64];
 extern const char AI08[64];
 extern const char AI09[64];
 extern const char AI10[64];
 extern const char AI11[64];
 extern const char AI12[64];
 extern const char AI13[64];
 //���ܵ���
 extern const char AF04[64];
 extern const char AF05[64];
 extern const char AF06[64];
 extern const char AF07[64]; 
 extern const char AF08[64];
 extern const char AF09[64];
 extern const char AF10[64];
 extern const char AF11[64];
 extern const char AF12[64];
 extern const char AF13[64];
//����������ʾ
 extern const int BIR_ENA;
 extern const uint BIR_X;
 extern const uint BIR_Y;
 extern const char BIR_COLORS[4];
 extern const char BIR_FCOLOR[4];
 extern const uint BIR_FONT;
 //��ʾ����
 extern const char BIRS01[LEN];
 extern const char BIRS02[LEN];
 extern const char BIRS03[LEN];
 extern const char BIRS04[LEN];
 extern const char BIRS05[LEN];
 extern const char BIRS06[LEN];
 extern const char BIRS07[LEN];
 extern const char BIRS08[LEN];
 //��������
 extern const char BIRD01[16];
 extern const char BIRD02[16];
 extern const char BIRD03[16];
 extern const char BIRD04[16];
 extern const char BIRD05[16];
 extern const char BIRD06[16];
 extern const char BIRD07[16];
 extern const char BIRD08[16];
 //��������
 extern const int BIRT01;
 extern const int BIRT02;
 extern const int BIRT03;
 extern const int BIRT04;
 extern const int BIRT05;
 extern const int BIRT06;
 extern const int BIRT07;
 extern const int BIRT08;
//��ʾ�ı�
 extern const int TEXT_ENA;
 extern const uint TEXT_X;
 extern const uint TEXT_Y;
 extern const char TEXT_COLORS[];
 extern const char TEXT_FCOLOR[];
 extern const uint TEXT_FONT;
 extern const char TEXT_FMT[LEN];
//��ʾ�¶�
 extern const int TEMP_ENA;
 extern const uint TEMP_X;
 extern const uint TEMP_Y;
 extern const char TEMP_COLORS[];
 extern const char TEMP_FCOLOR[];
 extern const uint TEMP_FONT;
 extern const char TEMP_FMT[16];
//��ʾ��ѹ
 extern const int VOLT_ENA;
 extern const uint VOLT_X;
 extern const uint VOLT_Y;
 extern const char VOLT_COLORS[];
 extern const char VOLT_FCOLOR[];
 extern const uint VOLT_FONT;
 extern const char VOLT_FMT[16];
//��ʾ�ڴ�
 extern const int RAM_ENA;
 extern const uint RAM_X;
 extern const uint RAM_Y;
 extern const char RAM_COLORS[];
 extern const char RAM_FCOLOR[];
 extern const uint RAM_FONT;
//ת����ʽ
 extern const char BYTES_FMT[16];
 extern const char BYTES_SG[8];
 extern const char KBYTES_SG[8];
//��ʾ����
 extern const int WEEK_ENA;
 extern const uint WEEK_X;
 extern const uint WEEK_Y;
 extern const char WEEK_COLORS[];
 extern const char WEEK_FCOLOR[];
 extern const uint WEEK_FONT;
 extern const int WEEK_FMT;
//��ʾ����
 extern const int DATE_ENA;
 extern const uint DATE_X;
 extern const uint DATE_Y;
 extern const char DATE_COLORS[];
 extern const char DATE_FCOLOR[];
 extern const uint DATE_FONT;
 extern const int DATE_FMT;
//��ʾʱ��
 extern const int TIME_ENA;
 extern const uint TIME_X;
 extern const uint TIME_Y;
 extern const char TIME_COLORS[];
 extern const char TIME_FCOLOR[];
 extern const uint TIME_FONT;
 extern const int TIME_FMT;
//��ʾũ����
 extern const int NongLiNian_ENA;
 extern const uint NongLiNian_X;
 extern const uint NongLiNian_Y;
 extern const char NongLiNian_COLORS[];
 extern const char NongLiNian_FCOLOR[];
 extern const uint NongLiNian_FONT;
//��ʾũ������
 extern const int NongLiDATE_ENA;
 extern const uint NongLiDATE_X;
 extern const uint NongLiDATE_Y;
 extern const char NongLiDATE_COLORS[];
 extern const char NongLiDATE_FCOLOR[];
 extern const uint NongLiDATE_FONT;
//��ʾ�ź�ǿ��
 extern const int NET_ENA;
 extern const uint NET_X;
 extern const uint NET_Y;
 extern const char NET_COLORS[];
 extern const char NET_FCOLOR[];
 extern const uint NET_FONT;
 extern const char NET_FMT[16];
//��ʾCPUʹ����
 extern const int CAP_ENA;
 extern const uint ACCU_X;
 extern const uint ACCU_Y;
 extern const char ACCU_COLORS[];
 extern const char ACCU_FCOLOR[];
 extern const uint ACCU_FONT;
 extern const char CAP_FMT[16];
//��ʾGPRS����
 extern const int GPRS_ENA;
 extern const uint GPRS_X;
 extern const uint GPRS_Y;
 extern const char GPRS_COLORS[];
 extern const char GPRS_FCOLOR[];
 extern const uint GPRS_FONT;
 //��ʾCPUʹ����
 extern const int CPU_ENA;
 extern const uint CPU_X;
 extern const uint CPU_Y;
 extern const char CPU_COLORS[];
 extern const char CPU_FCOLOR[];
 extern const uint CPU_FONT;
 extern const char CPU_FMT[16];
//ˢ���ٶ�
 extern const uint REFRESH;

#endif
