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
 #define ExcuteType "文件", "快捷", "地址", "目录"
 #define ExcuteLen 4
 #define DateFmt "YYYY/MM/DD","YYYY-MM-DD","YYYY.MM.DD","YYYY MM DD","MM/DD","MM-DD","MM.DD","MM DD","年月日","月日"
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
 
 extern const int  MENU_ENA;
 extern const int  INFO_ENA;
 extern const int  SHOW_EXT;
 extern const uint EXIT_BTN;
#ifdef DAEMON
 extern const uint CALL_BTN;
#endif
//运行软件
 extern const uint OFFSET;
 extern const uint AUTO_CLOSE;
 extern const char APPTEXT_COLORS[];
 extern const char APPTEXT_FCOLOR[];
 extern const uint APPTEXT_FONT;
 extern const char cfgPanBorderCol[];
 extern const char cfgPanBGCol[];
 extern const char cfgBookBorderCol[];
 extern const char cfgBookBGCol[];
 //没有图标
 extern const char AINO[];
 //运行内部地址
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
 //功能描述
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
 //功能图标 
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
 //功能调用
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
//定义生日显示
 extern const int  NBIR_ENA;
 extern const uint NBIR_X;
 extern const uint NBIR_Y;
 extern const char NBIR_COLORS[];
 extern const char NBIR_FCOLOR[];
 extern const uint NBIR_FONT; 
 extern const int  OBIR_ENA;
 extern const uint OBIR_X;
 extern const uint OBIR_Y;
 extern const char OBIR_COLORS[];
 extern const char OBIR_FCOLOR[];
 extern const uint OBIR_FONT;
 extern const char BIR_FILE[];
//显示文本
 extern const int  TEXT_ENA;
 extern const uint TEXT_X;
 extern const uint TEXT_Y;
 extern const char TEXT_COLORS[];
 extern const char TEXT_FCOLOR[];
 extern const uint TEXT_FONT;
 extern const char TEXT_FMT[];
//显示温度
 extern const int  TEMP_ENA;
 extern const uint TEMP_X;
 extern const uint TEMP_Y;
 extern const char TEMP_COLORS[];
 extern const char TEMP_FCOLOR[];
 extern const uint TEMP_FONT;
 extern const char TEMP_FMT[];
//显示电压
 extern const int  VOLT_ENA;
 extern const uint VOLT_X;
 extern const uint VOLT_Y;
 extern const char VOLT_COLORS[];
 extern const char VOLT_FCOLOR[];
 extern const uint VOLT_FONT;
 extern const char VOLT_FMT[];
//显示内存
 extern const int  RAM_ENA;
 extern const uint RAM_X;
 extern const uint RAM_Y;
 extern const char RAM_COLORS[];
 extern const char RAM_FCOLOR[];
 extern const uint RAM_FONT;
//转换格式
 extern const char BYTES_FMT[];
 extern const char BYTES_SG[];
 extern const char KBYTES_SG[];
//显示星期
 extern const int  WEEK_ENA;
 extern const uint WEEK_X;
 extern const uint WEEK_Y;
 extern const char WEEK_COLORS[];
 extern const char WEEK_FCOLOR[];
 extern const uint WEEK_FONT;
 extern const int  WEEK_FMT;
//显示日期
 extern const int  DATE_ENA;
 extern const uint DATE_X;
 extern const uint DATE_Y;
 extern const char DATE_COLORS[];
 extern const char DATE_FCOLOR[];
 extern const uint DATE_FONT;
 extern const int  DATE_FMT;
//显示时间
 extern const int  TIME_ENA;
 extern const uint TIME_X;
 extern const uint TIME_Y;
 extern const char TIME_COLORS[];
 extern const char TIME_FCOLOR[];
 extern const uint TIME_FONT;
 extern const int  TIME_FMT;
//显示农历年
 extern const int  CHSYEAR_ENA;
 extern const uint CHSYEAR_X;
 extern const uint CHSYEAR_Y;
 extern const char CHSYEAR_COLORS[];
 extern const char CHSYEAR_FCOLOR[];
 extern const uint CHSYEAR_FONT;
//显示农历月日
 extern const int  CHSDATE_ENA;
 extern const uint CHSDATE_X;
 extern const uint CHSDATE_Y;
 extern const char CHSDATE_COLORS[];
 extern const char CHSDATE_FCOLOR[];
 extern const uint CHSDATE_FONT;
//显示信号强度
 extern const int  NET_ENA;
 extern const uint NET_X;
 extern const uint NET_Y;
 extern const char NET_COLORS[];
 extern const char NET_FCOLOR[];
 extern const uint NET_FONT;
 extern const char NET_FMT[];
//显示CPU使用率
 extern const int  CAP_ENA;
 extern const uint ACCU_X;
 extern const uint ACCU_Y;
 extern const char ACCU_COLORS[];
 extern const char ACCU_FCOLOR[];
 extern const uint ACCU_FONT;
 extern const char CAP_FMT[];
//显示GPRS流量
 extern const int  GPRS_ENA;
 extern const uint GPRS_X;
 extern const uint GPRS_Y;
 extern const char GPRS_COLORS[];
 extern const char GPRS_FCOLOR[];
 extern const uint GPRS_FONT;
 //显示CPU使用率
 extern const int  CPU_ENA;
 extern const uint CPU_X;
 extern const uint CPU_Y;
 extern const char CPU_COLORS[];
 extern const char CPU_FCOLOR[];
 extern const uint CPU_FONT;
 extern const char CPU_FMT[];
//刷新速度
 extern const uint REFRESH;
//铃声参数
 extern const char RIN_FILE[];
 extern const uint RIN_VOLUME;
 extern const int  RIN_ENA;
 extern const uint RIN_NUM;
 extern const uint RIN_VIB;
 extern const uint RIN_BTN;
 extern const int  VIB_ENA;
 //自动关机
 extern const int  AUTOSD_ENA;
 extern const char AUTOSD_TIME[];
#endif
