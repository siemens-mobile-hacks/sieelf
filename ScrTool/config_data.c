#include <swilib.h>
#include <cfg_items.h>
#include <sieapi.h>
#include "scrtool.h"

//中文配置为 config_DATE_c.c

__root const CFG_HDR cfghdr0={CFG_CBOX, "Display menu", 0,2}; 
__root const int MENU_ENA= 1;
__root const CFG_CBOX_ITEM cfgcbox0[2] = {"No", "Yes"};
//菜单配置信息
//开始按键配置
__root const CFG_HDR cfghdr_mBAR1={CFG_LEVEL,"MAIN Setup",1,0};
__root const CFG_HDR cfghdrBAR_1={CFG_UINT,"Auto exit(sec)",0,20};
__root const uint AUTO_CLOSE=5;
__root const CFG_HDR cfghdrBAR_2={CFG_UINT,"Default action",0,20};
__root const int SELECTED=0;
__root const CFG_HDR cfghdrBAR_3={CFG_UINT,"Exit key",0,80};
__root const uint EXIT_BTN=RIGHT_SOFT;
__root const CFG_HDR cfghdrBAR_4={CFG_UINT,"Show key",0,80};
__root const uint CALL_BTN=RED_BUTTON;
__root const CFG_HDR cfghdrBAR_5={CFG_CBOX,"Key mode",0,3};
__root const int MODE_KBD=0;
__root const CFG_CBOX_ITEM cfgcbox03[3]={"KEY_DOWN","KEY_UP","LONG_PRESS"};
__root const CFG_HDR cfghdrBAR_6={CFG_CBOX,"BAR Postion",0,2};
__root const uint BARPOS=1;
__root const CFG_CBOX_ITEM cfgcbox030[2]={"TOP","BOTTOM"};
__root const CFG_HDR cfghdrBAR_7={CFG_UINT,"BAR Offset",0,400};
__root const uint OFFSET=0;
__root const CFG_HDR cfghdrBAR_8={CFG_COLOR,"BAR Frame color",0,0};
__root const char cfgPanBorderCol[4]={255,255,255,100};
__root const CFG_HDR cfghdrBAR_9={CFG_COLOR,"BAR BKG Color",0,0};
__root const char cfgPanBGCol[4]={88,200,32,100};
__root const CFG_HDR cfghdrBAR_A={CFG_COLOR,"ICON Frame Color",0,0};
__root const char cfgBookBorderCol[4]={255,255,255,100};
__root const CFG_HDR cfghdrBAR_B={CFG_COLOR,"ICON BKG Color",0,0};
__root const char cfgBookBGCol[4]={255,255,255,20};
__root const CFG_HDR cfghdrBAR_C={CFG_COLOR,"APPTEXT Color",0,0};
__root const char APPTEXT_COLORS[4]={255,255,255,100};
__root const CFG_HDR cfghdrBAR_D={CFG_COLOR,"APPTEXT Frame",0,0};
__root const char APPTEXT_FCOLOR[4]={0,0,255,75};
__root const CFG_HDR cfghdrBAR_G={CFG_CBOX,"APPTEXT Font",0,12};
__root const uint APPTEXT_FONT=4;
__root const CFG_CBOX_ITEM cfgcboxBAR[12]={FontStyle};
__root const CFG_HDR cfghdrBAR_E={CFG_STR_UTF8,"SET ICON",0,63};
__root const char AI00[64]=DEFAULT_DISK ":\\ZBin\\ScrTool\\set.png";
__root const CFG_HDR cfghdrBAR_F={CFG_STR_UTF8,"NO ICON",3,63};
__root const char AINO[64]=DEFAULT_DISK ":\\ZBin\\ScrTool\\no.png";
__root const CFG_HDR cfghdr_mBAR0={CFG_LEVEL,"",0,0};
//程序设置
__root const CFG_HDR cfghdr_mAPP1={CFG_LEVEL,"APPS Setup",1,0};
__root const CFG_HDR cfghdr_mA011={CFG_LEVEL,"APP 01 Setup",1,0};
__root const CFG_HDR cfghdrA01_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN01[LEN]="\xE5\x85\xB3\xE9\x97\xAD\xE6\x89\x8B\xE6\x9C\xBA";
__root const CFG_HDR cfghdrA01_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI01[64]=DEFAULT_DISK ":\\ZBin\\ScrTool\\off.png";
__root const CFG_HDR cfghdrA01_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF01[64]="A0562F70";
__root const CFG_HDR cfghdrA01_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT01 = 2; 
__root const CFG_CBOX_ITEM cfgcboxA01[3] = { "File", "Shortcut", "Address"}; 
__root const CFG_HDR cfghdr_mA010={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA021={CFG_LEVEL,"APP 02 Setup",1,0};
__root const CFG_HDR cfghdrA02_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN02[LEN]="\xE9\x87\x8D\xE5\x90\xAF\xE7\xB3\xBB\xE7\xBB\x9F";
__root const CFG_HDR cfghdrA02_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI02[64]=DEFAULT_DISK ":\\ZBin\\ScrTool\\reboot.png";
__root const CFG_HDR cfghdrA02_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF02[64]="A0562F7C";
__root const CFG_HDR cfghdrA02_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT02 = 2; 
__root const CFG_CBOX_ITEM cfgcboxA02[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA020={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA031={CFG_LEVEL,"APP 03 Setup",1,0};
__root const CFG_HDR cfghdrA03_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN03[LEN]="\xE9\x94\x81\xE5\xAE\x9A\xE9\x94\xAE\xE7\x9B\x98";
__root const CFG_HDR cfghdrA03_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI03[64]=DEFAULT_DISK ":\\ZBin\\ScrTool\\lock.png";
__root const CFG_HDR cfghdrA03_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF03[64]="A08FF6EB";
__root const CFG_HDR cfghdrA03_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT03 = 2; 
__root const CFG_CBOX_ITEM cfgcboxA03[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA030={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA041={CFG_LEVEL,"APP 04 Setup",1,0};
__root const CFG_HDR cfghdrA04_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN04[LEN]="\xE7\xA9\xBA\xE7\x99\xBD";
__root const CFG_HDR cfghdrA04_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI04[64]="";
__root const CFG_HDR cfghdrA04_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF04[64]="";
__root const CFG_HDR cfghdrA04_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT04 = 0; 
__root const CFG_CBOX_ITEM cfgcboxA04[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA040={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA051={CFG_LEVEL,"APP 05 Setup",1,0};
__root const CFG_HDR cfghdrA05_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN05[LEN]="\xE7\xA9\xBA\xE7\x99\xBD";
__root const CFG_HDR cfghdrA05_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI05[64]="";
__root const CFG_HDR cfghdrA05_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF05[64]="";
__root const CFG_HDR cfghdrA05_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT05 = 0; 
__root const CFG_CBOX_ITEM cfgcboxA05[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA050={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA061={CFG_LEVEL,"APP 06 Setup",1,0};
__root const CFG_HDR cfghdrA06_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN06[LEN]="\xE7\xA9\xBA\xE7\x99\xBD";
__root const CFG_HDR cfghdrA06_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI06[64]="";
__root const CFG_HDR cfghdrA06_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF06[64]="";
__root const CFG_HDR cfghdrA06_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT06 = 0; 
__root const CFG_CBOX_ITEM cfgcboxA06[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA060={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA071={CFG_LEVEL,"APP 07 Setup",1,0};
__root const CFG_HDR cfghdrA07_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN07[LEN]="\xE7\xA9\xBA\xE7\x99\xBD";
__root const CFG_HDR cfghdrA07_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI07[64]="";
__root const CFG_HDR cfghdrA07_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF07[64]="";
__root const CFG_HDR cfghdrA07_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT07 = 0; 
__root const CFG_CBOX_ITEM cfgcboxA07[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA070={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA081={CFG_LEVEL,"APP 08 Setup",1,0};
__root const CFG_HDR cfghdrA08_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN08[LEN]="\xE7\xA9\xBA\xE7\x99\xBD";
__root const CFG_HDR cfghdrA08_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI08[64]="";
__root const CFG_HDR cfghdrA08_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF08[64]="";
__root const CFG_HDR cfghdrA08_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT08 = 0; 
__root const CFG_CBOX_ITEM cfgcboxA08[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA080={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA091={CFG_LEVEL,"APP 09 Setup",1,0};
__root const CFG_HDR cfghdrA09_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN09[LEN]="\xE7\xA9\xBA\xE7\x99\xBD";
__root const CFG_HDR cfghdrA09_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI09[64]="";
__root const CFG_HDR cfghdrA09_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF09[64]="";
__root const CFG_HDR cfghdrA09_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT09 = 0; 
__root const CFG_CBOX_ITEM cfgcboxA09[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA090={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA101={CFG_LEVEL,"APP 10 Setup",1,0};
__root const CFG_HDR cfghdrA10_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN10[LEN]="\xE7\xA9\xBA\xE7\x99\xBD";
__root const CFG_HDR cfghdrA10_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI10[64]="";
__root const CFG_HDR cfghdrA10_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF10[64]="";
__root const CFG_HDR cfghdrA10_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT10 = 0; 
__root const CFG_CBOX_ITEM cfgcboxA10[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA100={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA111={CFG_LEVEL,"APP 11 Setup",1,0};
__root const CFG_HDR cfghdrA11_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN11[LEN]="\xE7\xA9\xBA\xE7\x99\xBD";
__root const CFG_HDR cfghdrA11_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI11[64]="";
__root const CFG_HDR cfghdrA11_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF11[64]="";
__root const CFG_HDR cfghdrA11_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT11 = 0; 
__root const CFG_CBOX_ITEM cfgcboxA11[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA110={CFG_LEVEL,"",0,0};
//-------------------------------------------------
__root const CFG_HDR cfghdr_mA121={CFG_LEVEL,"APP 12 Setup",1,0};
__root const CFG_HDR cfghdrA12_1={CFG_UTF8_STRING,"DEPICT",0,LEN-1};
__root const char AN12[LEN]="\xE7\xA9\xBA\xE7\x99\xBD";
__root const CFG_HDR cfghdrA12_2={CFG_STR_UTF8,"ICON",0,63};
__root const char AI12[64]="";
__root const CFG_HDR cfghdrA12_3={CFG_STR_UTF8,"CALL",0,63};
__root const char AF12[64]="";
__root const CFG_HDR cfghdrA12_4 ={CFG_CBOX, "TYPE", 0,3}; 
__root const int  AT12 = 0; 
__root const CFG_CBOX_ITEM cfgcboxA12[3] = { "File", "Shortcut", "Address"};
__root const CFG_HDR cfghdr_mA120={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_mAPP0={CFG_LEVEL,"",0,0};
//TextInfo begin
__root const CFG_HDR cfghdr_mTSI1={CFG_LEVEL,"TEXT Setup",1,0};
//显示自定义文本
__root const CFG_HDR cfghdrTSI={CFG_UINT,"Refresh speed(sec)",0,600};
__root const uint REFRESH=10;
__root const CFG_HDR cfghdr_mTSI11={CFG_LEVEL,"Title Setup",1,0};
__root const CFG_HDR cfghdrTSI1_1 = {CFG_CBOX, "Title Display", 0, 2};
__root const int TEXT_ENA = 1;
__root const CFG_CBOX_ITEM cfgcboxTSI10[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSI1_2={CFG_COORDINATES,"Title Position",0,0};
__root const uint TEXT_X=20;
__root const uint TEXT_Y=70;
__root const CFG_HDR cfghdrTSI1_3={CFG_UTF8_STRING,"Title Value",0,LEN-1};
__root const char TEXT_FMT[LEN]="\xE7\x8E\xAB\xE7\x91\xB0\xE5\xB7\xA5\xE4\xBD\x9C\xE5\xAE\xA4";
__root const CFG_HDR cfghdrTSI1_4={CFG_COLOR,"Title Color",0,0};
__root const char TEXT_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrTSI1_5={CFG_COLOR,"Title Frame",0,0};
__root const char TEXT_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSI1_6={CFG_CBOX,"Title Font",0,12};
__root const uint TEXT_FONT=0;
__root const CFG_CBOX_ITEM cfgcboxTSI11[12]={FontStyle};
__root const CFG_HDR cfghdr_mTSI10={CFG_LEVEL,"",0,0};
//显示温度
__root const CFG_HDR cfghdr_mTSI21={CFG_LEVEL,"Temperature Setup",1,0};
__root const CFG_HDR cfghdrTSI2_1 = {CFG_CBOX, "Temperature Display", 0, 2};
__root const int TEMP_ENA = 1;
__root const CFG_CBOX_ITEM cfgcboxTSI20[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSI2_2={CFG_COORDINATES,"Temperature Position",0,0};
__root const uint TEMP_X=3;
__root const uint TEMP_Y=25;
__root const CFG_HDR cfghdrTSI2_3={CFG_CBOX,"Temperature Font",0,12};
__root const uint TEMP_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxTSI21[12]={FontStyle};
__root const CFG_HDR cfghdrTSI2_4={CFG_STR_WIN1251,"Temperature Format",0,15};
__root const char TEMP_FMT[16]="%d.%d癈";
__root const CFG_HDR cfghdrTSI2_5={CFG_COLOR,"Temperature Color",0,0};
__root const char TEMP_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrTSI2_6={CFG_COLOR,"Temperature Frame",0,0};
__root const char TEMP_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdr_mTSI20={CFG_LEVEL,"",0,0};
//显示电压
__root const CFG_HDR cfghdr_mTSI31={CFG_LEVEL,"Voltage Setup",1,0};
__root const CFG_HDR cfghdrTSI3_1 = {CFG_CBOX, "Voltage Display", 0, 2};
__root const int VOLT_ENA = 1;
__root const CFG_CBOX_ITEM cfgcboxTSI30[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSI3_2={CFG_COORDINATES,"Voltage Position",0,0};
__root const uint VOLT_X=175;
__root const uint VOLT_Y=25;
__root const CFG_HDR cfghdrTSI3_3={CFG_COLOR,"Voltage Color",0,0};
__root const char VOLT_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrTSI3_6={CFG_COLOR,"Voltage Frame",0,0};
__root const char VOLT_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSI3_4={CFG_CBOX,"Voltage Font",0,12};
__root const uint VOLT_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxTSI31[12]={FontStyle};
__root const CFG_HDR cfghdrTSI3_5={CFG_STR_WIN1251,"Voltage Format",0,15};
__root const char VOLT_FMT[16]="%d.%02dV";
__root const CFG_HDR cfghdr_mTSI30={CFG_LEVEL,"",0,0};
//显示内存
__root const CFG_HDR cfghdr_mTSI41={CFG_LEVEL,"AvailRAM Setup",1,0};
__root const CFG_HDR cfghdrTSI4_1 = {CFG_CBOX, "AvailRAM Display", 0, 2};
__root const int RAM_ENA = 1;
__root const CFG_CBOX_ITEM cfgcboxTSI40[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSI4_2={CFG_COORDINATES,"AvailRAM Position",0,0};
__root const uint RAM_X=0;
__root const uint RAM_Y=293;
__root const CFG_HDR cfghdrTSI4_3={CFG_COLOR,"AvailRAM Color",0,0};
__root const char RAM_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrTSI4_5={CFG_COLOR,"AvailRAM Frame",0,0};
__root const char RAM_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSI4_6={CFG_CBOX,"AvailRAM Font",0,12};
__root const uint RAM_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxTSI41[12]={FontStyle};
__root const CFG_HDR cfghdr_mTSI40={CFG_LEVEL,"",0,0};
//显示星期
__root const CFG_HDR cfghdr_mTSI51={CFG_LEVEL,"WEEK Setup",1,0};
__root const CFG_HDR cfghdrTSI5_1 = {CFG_CBOX, "WEEK Display", 0, 2};
__root const int WEEK_ENA = 1;
__root const CFG_CBOX_ITEM cfgcboxTSI50[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSI5_2={CFG_COORDINATES,"WEEK Position",0,0};
__root const uint WEEK_X=90;
__root const uint WEEK_Y=25;
__root const CFG_HDR cfghdrTSI5_3={CFG_COLOR,"WEEK Color",0,0};
__root const char WEEK_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrTSI5_6={CFG_COLOR,"WEEK Frame",0,0};
__root const char WEEK_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSI5_4={CFG_CBOX,"WEEK font",0,12};
__root const uint WEEK_FONT=10;
__root const CFG_CBOX_ITEM cfgcboxTSI51[12]={FontStyle};
__root const CFG_HDR cfghdrTSI5_5={CFG_CBOX,"Format",0,6};
__root const int WEEK_FMT=4;
__root const CFG_CBOX_ITEM cfgcboxTSI52[6] = {"SUNDAY", "SUN","Sunday","Sun","星期日","日"};
__root const CFG_HDR cfghdr_mTSI50={CFG_LEVEL,"",0,0};
//显示日期
__root const CFG_HDR cfghdr_mTSI61={CFG_LEVEL,"DATE Setup",1,0};
__root const CFG_HDR cfghdrTSI6_1 = {CFG_CBOX, "DATE Display", 0, 2};
__root const int DATE_ENA = 1;
__root const CFG_CBOX_ITEM cfgcboxTSI60[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSI6_2={CFG_COORDINATES,"DATE Position",0,0};
__root const uint DATE_X=85;
__root const uint DATE_Y=293;
__root const CFG_HDR cfghdrTSI6_3={CFG_COLOR,"DATE Color",0,0};
__root const char DATE_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrTSI6_6={CFG_COLOR,"DATE Frame",0,0};
__root const char DATE_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSI6_4={CFG_CBOX,"DATE Font",0,12};
__root const uint DATE_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxTSI61[12]={FontStyle};
__root const CFG_HDR cfghdrTSI6_5={CFG_CBOX,"DATE Format",0,10};
__root const int DATE_FMT=5;
__root const CFG_CBOX_ITEM cfgcboxTSI62[10] = {"year/month/day","year-month-day","year.month.day","year month day","month/day","month-day","month.day","month day","年月日","月日"};
__root const CFG_HDR cfghdr_mTSI60={CFG_LEVEL,"",0,0};
//显示时间
__root const CFG_HDR cfghdr_mTSI71={CFG_LEVEL,"TIME Setup",1,0};
__root const CFG_HDR cfghdrTSI7_1 = {CFG_CBOX, "TIME Display", 0, 2};
__root const int TIME_ENA = 1;
__root const CFG_CBOX_ITEM cfgcboxTSI70[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSI7_2={CFG_COORDINATES,"TIME Position",0,0};
__root const uint TIME_X=30;
__root const uint TIME_Y=140;
__root const CFG_HDR cfghdrTSI7_3={CFG_COLOR,"TIME Color",0,0};
__root const char TIME_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrTSI7_6={CFG_COLOR,"TIME Frame",0,0};
__root const char TIME_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSI7_4={CFG_CBOX,"TIME Font",0,12};
__root const uint TIME_FONT=0;
__root const CFG_CBOX_ITEM cfgcboxTSI71[12]={FontStyle};
__root const CFG_HDR cfghdrTSI7_5={CFG_CBOX,"TIME Format",0,7};
__root const int TIME_FMT=3;
__root const CFG_CBOX_ITEM cfgcboxTSI72[7] = {"13:00","PM 01:00","01:00","13:00:00","PM 01:00:00","03D00F","03D00F00M"};
__root const CFG_HDR cfghdr_mTSI70={CFG_LEVEL,"",0,0};
//显示农历年份
__root const CFG_HDR cfghdr_mTSI81={CFG_LEVEL,"CHSYear Setup",1,0};
__root const CFG_HDR cfghdrTSI8_1 = {CFG_CBOX, "CHSYear Display", 0, 2};
__root const int NongLiNian_ENA = 0;
__root const CFG_CBOX_ITEM cfgcboxTSI80[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSI8_2={CFG_COORDINATES,"CHSYear Position",0,0};
__root const uint NongLiNian_X=80;
__root const uint NongLiNian_Y=260;
__root const CFG_HDR cfghdrTSI8_3={CFG_COLOR,"CHSYear Color",0,0};
__root const char NongLiNian_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrTSI8_4={CFG_COLOR,"CHSYear Frame",0,0};
__root const char NongLiNian_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSI8_5={CFG_CBOX,"CHSYear Font",0,12};
__root const uint NongLiNian_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxTSI81[12]={FontStyle};
__root const CFG_HDR cfghdr_mTSI80={CFG_LEVEL,"",0,0};
//显示农历日期
__root const CFG_HDR cfghdr_mTSI91={CFG_LEVEL,"CHSDate Setup",1,0};
__root const CFG_HDR cfghdrTSI9_1 = {CFG_CBOX, "CHSDate Display", 0, 2};
__root const int NongLiDATE_ENA = 1;
__root const CFG_CBOX_ITEM cfgcboxTSI90[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSI9_2={CFG_COORDINATES,"CHSDate Position",0,0};
__root const uint NongLiDATE_X=150;
__root const uint NongLiDATE_Y=293;
__root const CFG_HDR cfghdrTSI9_3={CFG_COLOR,"CHSDate Color",0,0};
__root const char NongLiDATE_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrTSI9_4={CFG_COLOR,"CHSDate Frame",0,0};
__root const char NongLiDATE_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSI9_5={CFG_CBOX,"CHSDate Font",0,12};
__root const uint NongLiDATE_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxTSI91[12]={FontStyle};
__root const CFG_HDR cfghdr_mTSI90={CFG_LEVEL,"",0,0};
//NET begin
__root const CFG_HDR cfghdr_mTSIA1={CFG_LEVEL,"Net Setup",1,0};
__root const CFG_HDR cfghdrTSIA_1 = {CFG_CBOX, "Net display", 0, 2};
__root const int NET_ENA = 0;
__root const CFG_CBOX_ITEM cfgcboxTSIA0[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSIA_2={CFG_COORDINATES,"Net position",0,0};
__root const uint NET_X=0;
__root const uint NET_Y=50;
__root const CFG_HDR cfghdrTSIA_3={CFG_COLOR,"Net color",0,0};
__root const char NET_COLORS[4]={0,0,0,100};
__root const CFG_HDR cfghdrTSIA_4={CFG_COLOR,"Net frame color",0,0};
__root const char NET_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSIA_5={CFG_CBOX,"Net font",0,12};
__root const uint NET_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxTSIA1[12]={FontStyle};
__root const CFG_HDR cfghdrTSIA_6={CFG_STR_WIN1251,"Net string format",0,15};
__root const char NET_FMT[16]="%c%ddB";
__root const CFG_HDR cfghdr_mTSIA0={CFG_LEVEL,"",0,0};
//NET end
//AccuCAP begin
__root const CFG_HDR cfghdr_mTSIB1={CFG_LEVEL,"AccuCap Setup",1,0};
__root const CFG_HDR cfghdrTSIB_1 = {CFG_CBOX, "AccuCap display", 0, 2};
__root const int CAP_ENA = 0;
__root const CFG_CBOX_ITEM cfgcboxTSIB0[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSIB_2={CFG_COORDINATES,"AccuCap position",0,0};
__root const uint ACCU_X=0;
__root const uint ACCU_Y=170;
__root const CFG_HDR cfghdrTSIB_3={CFG_COLOR,"AccuCap color",0,0};
__root const char ACCU_COLORS[4]={0,0,0,80};
__root const CFG_HDR cfghdrTSIB_4={CFG_COLOR,"AccuCap frame color",0,0};
__root const char ACCU_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSIB_5={CFG_CBOX,"AccuCap font",0,12};
__root const uint ACCU_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxTSIB1[12]={FontStyle};
__root const CFG_HDR cfghdrTSIB_6={CFG_STR_WIN1251,"AccuCap string format",0,15};
__root const char CAP_FMT[16]="%02d%%";
__root const CFG_HDR cfghdr_mTSIB0={CFG_LEVEL,"",0,0};
//AccuCAP end
//GPRS begin
__root const CFG_HDR cfghdr_mTSIC1={CFG_LEVEL,"GPRS Traff Setup",1,0};
__root const CFG_HDR cfghdrTSIC_1 = {CFG_CBOX, "GPRS Traff display", 0, 2};
__root const int GPRS_ENA = 0;
__root const CFG_CBOX_ITEM cfgcboxTSIC0[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSIC_2={CFG_COORDINATES,"GPRS position",0,0};
__root const uint GPRS_X=0;
__root const uint GPRS_Y=210;
__root const CFG_HDR cfghdrTSIC_3={CFG_COLOR,"GPRS color",0,0};
__root const char GPRS_COLORS[4]={0,0,0,100};
__root const CFG_HDR cfghdrTSIC_6={CFG_COLOR,"GPRS frame color",0,0};
__root const char GPRS_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSIC_4={CFG_CBOX,"GPRS font",0,12};
__root const uint GPRS_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxTSIC1[12]={FontStyle};
__root const CFG_HDR cfghdr_mTSIC0={CFG_LEVEL,"",0,0};
//GPRS end
//CPULoad begin
__root const CFG_HDR cfghdr_mTSID1={CFG_LEVEL,"CPULoad Setup",1,0};
__root const CFG_HDR cfghdrTSID_1 = {CFG_CBOX, "CPULoad display", 0, 2};
__root const int CPU_ENA = 0;
__root const CFG_CBOX_ITEM cfgcboxTSID0[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrTSID_2={CFG_COORDINATES,"CPULoad position",0,0};
__root const uint CPU_X=90;
__root const uint CPU_Y=293;
__root const CFG_HDR cfghdrTSID_3={CFG_COLOR,"CPULoad color",0,0};
__root const char CPU_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrTSID_6={CFG_COLOR,"CPULoad frame color",0,0};
__root const char CPU_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrTSID_4={CFG_CBOX,"CPULoad font",0,12};
__root const uint CPU_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxTSID1[12]={FontStyle};
__root const CFG_HDR cfghdrTSID_5={CFG_STR_WIN1251,"CPULoad string format",0,15};
__root const char CPU_FMT[16]="%02d%%";
__root const CFG_HDR cfghdr_mTSID0={CFG_LEVEL,"",0,0};
//CPULoad end
//Format begin
__root const CFG_HDR cfghdr_mTSIE1={CFG_LEVEL,"Format Setup",1,0};
__root const CFG_HDR cfghdrTSIE_1={CFG_STR_WIN1251,"Bytes string format",0,15};
__root const char BYTES_FMT[16]="%u%s";
__root const CFG_HDR cfghdrTSIE_2={CFG_STR_WIN1251,"Bytes sign",0,7};
__root const char BYTES_SG[8]="B";
__root const CFG_HDR cfghdrTSIE_3={CFG_STR_WIN1251,"KiloBytes sign",0,7};
__root const char KBYTES_SG[8]="KB";
__root const CFG_HDR cfghdr_mTSIE0={CFG_LEVEL,"",0,0};
//Format end
__root const CFG_HDR cfghdr_mTSI0={CFG_LEVEL,"",0,0};
//TextInfo end
__root const CFG_HDR cfghdr_mBIR1={CFG_LEVEL,"BDAY Setup",1,0};
__root const CFG_HDR cfghdr_mBIR011={CFG_LEVEL,"BDAY 01 Setup",1,0};
__root const CFG_HDR cfghdrBIR01_3 = {CFG_CBOX, "TYPE", 0, 2};
__root const int BIRT01 = 0;
__root const CFG_CBOX_ITEM cfgcboxBIR010[2] = {"NewStyle", "OldStyle"};
__root const CFG_HDR cfghdrBIR01_1={CFG_UTF8_STRING,"DATE",0,15};
__root const char BIRD01[16] = "";
__root const CFG_HDR cfghdrBIR01_2={CFG_UTF8_STRING,"TITLE",0,LEN-1};
__root const char BIRS01[LEN] = "";
__root const CFG_HDR cfghdr_mBIR010={CFG_LEVEL,"",0,0};
//--------------------------
__root const CFG_HDR cfghdr_mBIR021={CFG_LEVEL,"BDAY 02 Setup",1,0};
__root const CFG_HDR cfghdrBIR02_3 = {CFG_CBOX, "TYPE", 0, 2};
__root const int BIRT02 = 0;
__root const CFG_CBOX_ITEM cfgcboxBIR020[2] = {"NewStyle", "OldStyle"};
__root const CFG_HDR cfghdrBIR02_1={CFG_UTF8_STRING,"DATE",0,15};
__root const char BIRD02[16] = "";
__root const CFG_HDR cfghdrBIR02_2={CFG_UTF8_STRING,"TITLE",0,LEN-1};
__root const char BIRS02[LEN] = "";
__root const CFG_HDR cfghdr_mBIR020={CFG_LEVEL,"",0,0};
//--------------------------
__root const CFG_HDR cfghdr_mBIR031={CFG_LEVEL,"BDAY 03 Setup",1,0};
__root const CFG_HDR cfghdrBIR03_3 = {CFG_CBOX, "TYPE", 0, 2};
__root const int BIRT03 = 0;
__root const CFG_CBOX_ITEM cfgcboxBIR030[2] = {"NewStyle", "OldStyle"};
__root const CFG_HDR cfghdrBIR03_1={CFG_UTF8_STRING,"DATE",0,15};
__root const char BIRD03[16] = "";
__root const CFG_HDR cfghdrBIR03_2={CFG_UTF8_STRING,"TITLE",0,LEN-1};
__root const char BIRS03[LEN] = "";
__root const CFG_HDR cfghdr_mBIR030={CFG_LEVEL,"",0,0};
//--------------------------
__root const CFG_HDR cfghdr_mBIR041={CFG_LEVEL,"BDAY 04 Setup",1,0};
__root const CFG_HDR cfghdrBIR04_3 = {CFG_CBOX, "TYPE", 0, 2};
__root const int BIRT04 = 0;
__root const CFG_CBOX_ITEM cfgcboxBIR040[2] = {"NewStyle", "OldStyle"};
__root const CFG_HDR cfghdrBIR04_1={CFG_UTF8_STRING,"DATE",0,15};
__root const char BIRD04[16] = "";
__root const CFG_HDR cfghdrBIR04_2={CFG_UTF8_STRING,"TITLE",0,LEN-1};
__root const char BIRS04[LEN] = "";
__root const CFG_HDR cfghdr_mBIR040={CFG_LEVEL,"",0,0};
//--------------------------
__root const CFG_HDR cfghdr_mBIR051={CFG_LEVEL,"BDAY 05 Setup",1,0};
__root const CFG_HDR cfghdrBIR05_3 = {CFG_CBOX, "TYPE", 0, 2};
__root const int BIRT05 = 0;
__root const CFG_CBOX_ITEM cfgcboxBIR050[2] = {"NewStyle", "OldStyle"};
__root const CFG_HDR cfghdrBIR05_1={CFG_UTF8_STRING,"DATE",0,15};
__root const char BIRD05[16] = "";
__root const CFG_HDR cfghdrBIR05_2={CFG_UTF8_STRING,"TITLE",0,LEN-1};
__root const char BIRS05[LEN] = "";
__root const CFG_HDR cfghdr_mBIR050={CFG_LEVEL,"",0,0};
//--------------------------
__root const CFG_HDR cfghdr_mBIR061={CFG_LEVEL,"BDAY 06 Setup",1,0};
__root const CFG_HDR cfghdrBIR06_3 = {CFG_CBOX, "TYPE", 0, 2};
__root const int BIRT06 = 0;
__root const CFG_CBOX_ITEM cfgcboxBIR060[2] = {"NewStyle", "OldStyle"};
__root const CFG_HDR cfghdrBIR06_1={CFG_UTF8_STRING,"DATE",0,15};
__root const char BIRD06[16] = "";
__root const CFG_HDR cfghdrBIR06_2={CFG_UTF8_STRING,"TITLE",0,LEN-1};
__root const char BIRS06[LEN] = "";
__root const CFG_HDR cfghdr_mBIR060={CFG_LEVEL,"",0,0};
//--------------------------
__root const CFG_HDR cfghdr_mBIR071={CFG_LEVEL,"BDAY 07 Setup",1,0};
__root const CFG_HDR cfghdrBIR07_3 = {CFG_CBOX, "TYPE", 0, 2};
__root const int BIRT07 = 0;
__root const CFG_CBOX_ITEM cfgcboxBIR070[2] = {"NewStyle", "OldStyle"};
__root const CFG_HDR cfghdrBIR07_1={CFG_UTF8_STRING,"DATE",0,15};
__root const char BIRD07[16] = "";
__root const CFG_HDR cfghdrBIR07_2={CFG_UTF8_STRING,"TITLE",0,LEN-1};
__root const char BIRS07[LEN] = "";
__root const CFG_HDR cfghdr_mBIR070={CFG_LEVEL,"",0,0};
//--------------------------
__root const CFG_HDR cfghdr_mBIR081={CFG_LEVEL,"BDAY 08 Setup",1,0};
__root const CFG_HDR cfghdrBIR08_3 = {CFG_CBOX, "TYPE", 0, 2};
__root const int BIRT08 = 0;
__root const CFG_CBOX_ITEM cfgcboxBIR080[2] = {"NewStyle", "OldStyle"};
__root const CFG_HDR cfghdrBIR08_1={CFG_UTF8_STRING,"DATE",0,15};
__root const char BIRD08[16] = "";
__root const CFG_HDR cfghdrBIR08_2={CFG_UTF8_STRING,"TITLE",0,LEN-1};
__root const char BIRS08[LEN] = "";
__root const CFG_HDR cfghdr_mBIR080={CFG_LEVEL,"",0,0};
//--------------------------
__root const CFG_HDR cfghdrBIR_1 = {CFG_CBOX, "BDAY display", 0, 2};
__root const int BIR_ENA = 1;
__root const CFG_CBOX_ITEM cfgcboxBIR0[2] = {"No", "Yes"};
__root const CFG_HDR cfghdrBIR_2={CFG_COORDINATES,"BDAY position",0,0};
__root const uint BIR_X=30;
__root const uint BIR_Y=200;
__root const CFG_HDR cfghdrBIR_3={CFG_COLOR,"BDAY color",0,0};
__root const char BIR_COLORS[4]={0,0,255,75};
__root const CFG_HDR cfghdrBIR_4={CFG_COLOR,"BDAY frame color",0,0};
__root const char BIR_FCOLOR[4]={255,255,255,100};
__root const CFG_HDR cfghdrBIR_5={CFG_CBOX,"BDAY font",0,12};
__root const uint BIR_FONT=8;
__root const CFG_CBOX_ITEM cfgcboxBIR1[12]={FontStyle};
__root const CFG_HDR cfghdr_mBIR0={CFG_LEVEL,"",0,0};



