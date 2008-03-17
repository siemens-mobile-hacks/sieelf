#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
#include "FesRemind.h"

__root const CFG_HDR cfghdr0 = {CFG_CBOX, "显示时机", 0, 3};
__root const int cfgShowIn = 1;
__root const CFG_CBOX_ITEM cfgcbox1_0[3] = {"锁键盘", "未锁键盘", "锁键盘+未锁键盘"};

// -------------------------------------------------------------------------- 
//显示自定义文本
__root const CFG_HDR cfghdr_mTSI11={CFG_LEVEL,"文本选项",1,0};
__root const CFG_HDR cfghdrTSI1_1={CFG_CHECKBOX, "屏显", 0, 2};
__root const int TEXT_ENA=1;

__root const CFG_HDR cfghdrTSI1_2={CFG_COORDINATES,"位置",0,0};
__root const unsigned int TEXT_X=20;
__root const unsigned int TEXT_Y=70;

__root const CFG_HDR cfghdrTSI1_3={CFG_STR_GB,"文字",0,31};
__root const char TEXT_FMT[32]="我爱我家";

__root const CFG_HDR cfghdrTSI1_4={CFG_COLOR,"文字颜色",0,0};
__root const char TEXT_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrTSI1_5={CFG_COLOR,"边框颜色",0,0};
__root const char TEXT_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrTSI1_6={CFG_CBOX,"字体",0,17};
__root const unsigned int TEXT_FONT=0;
__root const CFG_CBOX_ITEM cfgcboxTSI11[17]={FontSyCN};
__root const CFG_HDR cfghdr_mTSI10={CFG_LEVEL,"",0,0};

// -------------------------------------------------------------------------- //

__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"星期",1,0};

__root const CFG_HDR cfghdr9_1 = {CFG_CHECKBOX, "显示", 0, 2};
__root const int WEEK_ENA = 1;

__root const CFG_HDR cfghdr9_2={CFG_COORDINATES,"位置坐标",0,0};
__root const unsigned int WEEK_X=40;
__root const unsigned int WEEK_Y=140;

__root const CFG_HDR cfghdr9_3={CFG_COLOR,"文字颜色",0,0};
__root const char WEEK_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr9_6={CFG_COLOR,"边框颜色",0,0};
__root const char WEEK_FRINGING_COLORS[4]={0,0,0,100};

__root const CFG_HDR cfghdr9_4={CFG_CBOX,"字体",0,17};
__root const unsigned int WEEK_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxWeek[17]={FontSyCN};

__root const CFG_HDR cfghdr9_7={CFG_CBOX,"样式",0,2};
__root const int WEEK_STYLE = 1;
__root const CFG_CBOX_ITEM cfgcbox9_0[2] = {"MON", "星期一"};

__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};

// -------------------------------------------------------------------------- //
//显示农历年份
__root const CFG_HDR cfghdr_mTSI81={CFG_LEVEL,"农历年份",1,0};
__root const CFG_HDR cfghdrTSI8_1={CFG_CHECKBOX, "屏显", 0, 2};
__root const int CYEAR_ENA=1;

__root const CFG_HDR cfghdrTSI8_2={CFG_COORDINATES,"位置",0,0};
__root const unsigned int CYEAR_X=75;
__root const unsigned int CYEAR_Y=20;

__root const CFG_HDR cfghdrTSI8_3={CFG_COLOR,"文字颜色",0,0};
__root const char CYEAR_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrTSI8_4={CFG_COLOR,"边框颜色",0,0};
__root const char CYEAR_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrTSI8_5={CFG_CBOX,"字体",0,17};
__root const unsigned int CYEAR_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxTSI81[17]={FontSyCN};

__root const CFG_HDR cfghdr_mTSI80={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------
//显示农历日期
__root const CFG_HDR cfghdr_mTSI91={CFG_LEVEL,"农历日期",1,0};
__root const CFG_HDR cfghdrTSI9_1={CFG_CHECKBOX, "屏显", 0, 2};
__root const int CDATE_ENA=1;

__root const CFG_HDR cfghdrTSI9_2={CFG_COORDINATES,"位置",0,0};
__root const unsigned int CDATE_X=2;
__root const unsigned int CDATE_Y=20;

__root const CFG_HDR cfghdrTSI9_3={CFG_COLOR,"文字颜色",0,0};
__root const char CDATE_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrTSI9_4={CFG_COLOR,"边框颜色",0,0};
__root const char CDATE_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrTSI9_5={CFG_CBOX,"字体",0,17};
__root const unsigned int CDATE_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxTSI91[17]={FontSyCN};

__root const CFG_HDR cfghdr_mTSI90={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------
//阴历节日选项设置
__root const CFG_HDR cfghdr_mFESTA1={CFG_LEVEL,"节日设置",1,0};

__root const CFG_HDR cfghdrFESTA={CFG_CHECKBOX, "屏显", 0, 2};
__root const int BIR_ENA=1;

__root const CFG_HDR cfghdrBIRFILE={CFG_STR_UTF8,"数据文件",0,63};
__root const char BIRS_FILE[64]="0:\\ZBin\\etc\\day.txt";

__root const CFG_HDR cfghdr_mAPP1={CFG_LEVEL,"重要记事",1,0};
__root const CFG_HDR cfghdrAPP_1={CFG_COORDINATES,"位置",0,0};
__root const unsigned int APP_X=2;
__root const unsigned int APP_Y=126;

__root const CFG_HDR cfghdrAPP_2={CFG_COLOR,"文字颜色",0,0};
__root const char APP_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrAPP_3={CFG_COLOR,"边框颜色",0,0};
__root const char APP_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrAPP_4={CFG_CBOX,"字体",0,17};
__root const unsigned int APP_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxAPP1[17]={FontSyCN};

__root const CFG_HDR cfghdr_mAPP0={CFG_LEVEL,"",0,0};

         /*------------------------------------*/
__root const CFG_HDR cfghdr_mTSIA1={CFG_LEVEL,"阴历节日",1,0};

__root const CFG_HDR cfghdrOBIR_1={CFG_COORDINATES,"位置",0,0};
__root const unsigned int OBIR_X=2;
__root const unsigned int OBIR_Y=36;

__root const CFG_HDR cfghdrOBIR_2={CFG_COLOR,"文字颜色",0,0};
__root const char OBIR_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrOBIR_3={CFG_COLOR,"边框颜色",0,0};
__root const char OBIR_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrOBIR_4={CFG_CBOX,"字体",0,17};
__root const unsigned int OBIR_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxOBIR1[17]={FontSyCN};

__root const CFG_HDR cfghdr_mTSIA0={CFG_LEVEL,"",0,0};

       /*-----------------------------------------------*/
//阳历节日选项设置
__root const CFG_HDR cfghdr_mTSIB1={CFG_LEVEL,"阳历节日",1,0};

__root const CFG_HDR cfghdrNBIR_1={CFG_COORDINATES,"位置",0,0};
__root const unsigned int NBIR_X=2;
__root const unsigned int NBIR_Y=126;

__root const CFG_HDR cfghdrNBIR_2={CFG_COLOR,"文字颜色",0,0};
__root const char NBIR_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrNBIR_3={CFG_COLOR,"边框颜色",0,0};
__root const char NBIR_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrNBIR_4={CFG_CBOX,"字体",0,17};
__root const unsigned int NBIR_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxNBIR1[17]={FontSyCN};

__root const CFG_HDR cfghdr_mTSIB0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_mFESTA0={CFG_LEVEL,"",0,0};

