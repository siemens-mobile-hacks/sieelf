#ifndef _MegaDial_H_
  #define _MegaDial_H_
//#include "ussd_process.h"
//#include "main.h"

extern const int ENA_VIBRA;
extern const unsigned int vibraPower;
extern const unsigned int vibraDuration;

//通信录地址
extern const char root_dir[128];
//颜色控制
extern const int COLOR_MENU_BK;
extern const int COLOR_MENU_BRD;
extern const int COLOR_NOTSELECTED;
extern const int COLOR_SELECTED;
extern const int COLOR_SELECTED_BG;
extern const int COLOR_SELECTED_BRD;
extern const int COLOR_SCROLLBAR;
extern const int COLOR_SCROLLBAR_BG;
extern const char COLOR_SEARCH_MARK[4];
extern const char COLOR_SEARCH_UNMARK[4];
extern const int COLOR_NUMBER_BG;
extern const int COLOR_NUMBER_BRD;
extern const int COLOR_NUMBER;
extern const int CS_NUMBER_BG;
//区号秀
extern const int cfg_cs_adr;
extern const int cfg_cs_enable;
extern const int cfg_cs_part;
extern const int cfg_cs_font_color;
extern int GetProvAndCity(unsigned short *pBSTR, char *pNoStr);
//部分功能控制
extern const int cfg_disable_one_number;
extern const int disable_when_calling;
extern const int big_font;
extern const int cfg_ip_number;
extern const int show_pic;
extern const int smsn;
extern const int smsc;
extern const unsigned int volume;

/*
#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])

extern const unsigned int CHECK_HOURS;
extern const int cfgShowIn;
extern const int ENA_CASHTRACE;

extern int CurrentCASH[MAX_CASH_SIZE];
extern int MaxCASH[MAX_CASH_SIZE];

extern const unsigned int IDLE_Y;

extern const char COLOR_CASHPB1[4];
extern const char COLOR_CASHPB2[4];
extern const char COLOR_CASHPB3[4];
extern const char COLOR_CASHPB4[4];
extern const char COLOR_TEXTPB[4];
extern const unsigned int TEXT_FONTSZ;

char cur_imsi[IMSI_DATA_BYTE_LEN];

const char *progress_colors[MAX_CASH_SIZE]=
{
  COLOR_CASHPB1,
  COLOR_CASHPB2,
  COLOR_CASHPB3,
  COLOR_CASHPB4
};
*/
#endif

