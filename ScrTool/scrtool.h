#ifndef _SCRTOOL_H_
 #define _SCRTOOL_H_ 
 #include <sieapi.h> 
#define DAEMON
#define SCR_NAME "ScrTool"
#define UPDATE_STAT 1
#define TMR_SECOND 216
#define MAX_SCR 13
#define MAX_APP 14
#define SCR_ALARM 3
#define SCR_MENUS 2
#define SCR_TASKS 1
#define LEN 32
#define NoName "空白"
#define ExcuteTyen "File", "Shortcut", "Address", "Directory"
#define ExcuteTycn "文件", "快捷", "地址", "目录"
#define AgainEN "Default", "AgainLeft", "Center", "AgainRight"
#define AgainCN "默认", "靠左", "居中", "靠右"
#define ScrMode "锁键", "解锁", "总是", "禁止"
#define ExcuteLen 4
#define DateFmt "YYYY/MM/DD","YYYY-MM-DD","YYYY.MM.DD","YYYY MM DD","MM/DD","MM-DD","MM.DD","MM DD","年月日","月日"
#define TimeFmt "13:00","PM 01:00","01:00","13:00:00","PM 01:00:00","=点分=","点分秒"

 typedef struct{
  CSM_RAM CSM;
 }DAEMON_CSM;
 typedef struct{
  CSM_RAM CSM;
  int TaskID; 
 }TASK_GUI;
 typedef struct{  
  WSHDR *WS;
  char  PEN[4];
  char  BUH[4];
  short Size;
  short Style;
  short Show;
  short L;//left
  short T;//top
  short R;//right
  short B;//bottom
 }TSCR; 
 typedef struct{
  char *Pic;
  char *File;
  char *Name;
  short Type;
 }TAPP; 
  //刷新速度
 extern const uint REFRESH;
 extern const uint TASK_ENA;
 extern const uint INFO_ENA;
 extern const uint SHOW_EXT;
 extern const uint MODE_KBD;
 extern const uint CALL_BTN; 
 extern const uint DEST_ENA; 
 extern const uint PicSize;
//运行软件
 extern const uint OFFSET;
 extern const uint AUTO_CLOSE;
 extern const char ATEXT_CS[];
 extern const uint ATEXT_FT;
 extern const char cfgPBDCol[];
 extern const char cfgPBGCol[];
 extern const char cfgBBDCol[];
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
//定义节日参数
 extern const int  NBIR_ENA;
 extern const uint NBIR_XT;
 extern const uint NBIR_X;
 extern const uint NBIR_Y;
 extern const char NBIR_CS[];
 extern const char NBIR_CB[];
 extern const uint NBIR_FT; 
 //定义阴历节日
 extern const int  OBIR_ENA;
 extern const uint OBIR_XT;
 extern const uint OBIR_X;
 extern const uint OBIR_Y;
 extern const char OBIR_CS[];
 extern const char OBIR_CB[];
 extern const uint OBIR_FT;
//节日文件
 extern const char BIRS_FILE[];
//显示文本
 extern const int  TEXT_ENA;
 extern const uint TEXT_XT;
 extern const uint TEXT_X;
 extern const uint TEXT_Y;
 extern const char TEXT_CS[];
 extern const char TEXT_CB[];
 extern const char TEXT_CP[];
 extern const uint TEXT_FT;
//显示温度
 extern const int  TEMP_ENA;
 extern const uint TEMP_XT;
 extern const uint TEMP_X;
 extern const uint TEMP_Y;
 extern const char TEMP_CS[];
 extern const char TEMP_CB[];
 extern const uint TEMP_FT;
//显示电压
 extern const int  VOLT_ENA;
 extern const int  VOLT_TY;
 extern const uint VOLT_XT;
 extern const uint VOLT_X;
 extern const uint VOLT_Y;
 extern const char VOLT_CS[];
 extern const char VOLT_CB[];
 extern const uint VOLT_FT;
//显示内存
 extern const int  RAMT_ENA;
 extern const uint RAMT_XT;
 extern const uint RAMT_X;
 extern const uint RAMT_Y;
 extern const char RAMT_CS[];
 extern const char RAMT_CB[];
 extern const uint RAMT_FT;
//显示星期
 extern const int  WEEK_ENA;
 extern const uint WEEK_XT;
 extern const uint WEEK_X;
 extern const uint WEEK_Y;
 extern const char WEEK_CS[];
 extern const char WEEK_CB[];
 extern const uint WEEK_FT;
 extern const int  WEEK_FMT;
//显示日期
 extern const int  DATE_ENA;
 extern const uint DATE_XT;
 extern const uint DATE_X;
 extern const uint DATE_Y;
 extern const char DATE_CS[];
 extern const char DATE_CB[];
 extern const uint DATE_FT;
 extern const int  DATE_FMT;
//显示时间
 extern const int  TIME_ENA;
 extern const uint TIME_XT;
 extern const uint TIME_X;
 extern const uint TIME_Y;
 extern const char TIME_CS[];
 extern const char TIME_CB[];
 extern const uint TIME_FT;
 extern const int  TIME_FMT;
//显示农历年月日节气
 extern const int  CHSD_ENA;
 extern const uint CHSD_XT;
 extern const uint CHSD_X;
 extern const uint CHSD_Y;
 extern const char CHSD_CS[];
 extern const char CHSD_CB[];
 extern const uint CHSD_FT;
//显示信号强度
 extern const int  NETI_ENA;
 extern const uint NETI_XT;
 extern const uint NETI_X;
 extern const uint NETI_Y;
 extern const char NETI_CS[];
 extern const char NETI_CB[];
 extern const uint NETI_FT;
//显示GPRS流量
 extern const int  GPRS_ENA;
 extern const uint GPRS_XT;
 extern const uint GPRS_X;
 extern const uint GPRS_Y;
 extern const char GPRS_CS[];
 extern const char GPRS_CB[];
 extern const uint GPRS_FT;
 //显示CPU使用率
 extern const int  CPUI_ENA;
 extern const uint CPUI_XT;
 extern const uint CPUI_X;
 extern const uint CPUI_Y;
 extern const char CPUI_CS[];
 extern const char CPUI_CB[];
 extern const uint CPUI_FT;
//铃声参数
 extern const char ALRM_FILE[];
 extern const char ALRM_PIC[];
 extern const char ALRM_CBK[];
 extern const char ALRM_CTX[];
 extern const uint ALRM_FT;
 extern const uint ALRM_VOL;
 extern const uint ALRM_COT;
 extern const int  ALRM_ENA;
 extern const uint ALRM_NUM;
 extern const int  ALRV_ENA;
 extern const uint ALRM_VIB;
 extern const int  ALIU_ENA;
//自动关机
 extern const uint  SHUT_ENA;
 extern const TTime SHUT_TIME;
//自动重启
 extern const uint  ROOT_ENA;
 extern const TTime ROOT_TIME;

#endif
