#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
//������������


#ifdef ELKA

__root const CFG_HDR cfghdr_00={CFG_LEVEL,"������� ����",1,0};

__root const CFG_HDR cfghdr0_0 = {CFG_UINT, "��������� (�����)", 0, 20};
__root const unsigned int bcfg_gamew_head_font = FONT_NUMERIC_SMALL_BOLD;

__root const CFG_HDR cfghdr0_1 = {CFG_COLOR,"��������� (����)",0,0};
__root const char bcfg_gamew_head_col[4]={0x00,0x8B,0xFF,0x64};

__root const CFG_HDR cfghdr0_2 = {CFG_COLOR,"������ (����)",0,0};
__root const char bcfg_gamew_timer_col[4]={0x00,0xFF,0xFF,0x64};

__root const CFG_HDR cfghdr0_3 = {CFG_UINT, "���������� ���� (X)", 0, 320};
__root const int bcfg_pole_x = 0;

__root const CFG_HDR cfghdr0_4={CFG_CHECKBOX,"����� (X)",0,0};
__root const int bcfg_pole_x_min = 0;

__root const CFG_HDR cfghdr0_5 = {CFG_UINT, "���������� ���� (Y)", 0, 320};
__root const int bcfg_pole_y = 0;

__root const CFG_HDR cfghdr0_6={CFG_CHECKBOX,"����� (Y)",0,0};
__root const int bcfg_pole_y_min = 0;

__root const CFG_HDR cfghdr0_7 = {CFG_COLOR,"����� (����)",0,0};
__root const char bcfg_gamew_grid_col[4]={0xC8,0x00,0x00,0x64};

__root const CFG_HDR cfghdr0_8 = {CFG_COLOR,"������ (����)",0,0};
__root const char bcfg_gamew_kontur_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr0_9 = {CFG_COLOR,"������ (����)",0,0};
__root const char bcfg_gamew_cursor_col[4]={0,0xC7,0xFF,100};

__root const CFG_HDR cfghdr_01={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_10={CFG_LEVEL,"����",1,0};

__root const CFG_HDR cfghdr1_0 = {CFG_UINT, "�. ���� (�����)", 0, 20};
__root const unsigned int bcfg_mmenu_font = FONT_NUMERIC_SMALL_BOLD;

__root const CFG_HDR cfghdr1_1 = {CFG_COLOR,"�. ���� (����)",0,0};
__root const char bcfg_mmenu_col[4]={0,0xFF,0,100};

__root const CFG_HDR cfghdr1_2 = {CFG_COLOR,"�. ���� (���#1)",0,0};
__root const char bcfg_mmenu_bg1_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr1_3 = {CFG_COLOR,"�. ���� (���#2)",0,0};
__root const char bcfg_mmenu_bg2_col[4]={0xC8,0,0,100};



__root const CFG_HDR cfghdr1_4 = {CFG_UINT, "�. ���� (�����)", 0, 20};
__root const unsigned int bcfg_gmenu_font = FONT_SMALL_ITALIC_BOLD;

__root const CFG_HDR cfghdr1_5 = {CFG_COLOR,"�. ���� (����)",0,0};
__root const char bcfg_gmenu_col[4]={0,0xC8,0,100};

__root const CFG_HDR cfghdr1_6 = {CFG_COLOR,"�. ���� (���#1)",0,0};
__root const char bcfg_gmenu_bg1_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr1_7 = {CFG_COLOR,"�. ���� (���#2)",0,0};
__root const char bcfg_gmenu_bg2_col[4]={0,0x64,0,100};



__root const CFG_HDR cfghdr1_8 = {CFG_UINT, "�/�. ���� (�����)", 0, 20};
__root const unsigned int bcfg_smenu_font = FONT_SMALL_ITALIC;

__root const CFG_HDR cfghdr1_9 = {CFG_COLOR,"�/�. ���� (����)",0,0};
__root const char bcfg_smenu_col[4]={0xC8,0,0,100};

__root const CFG_HDR cfghdr1_10 = {CFG_COLOR,"�/�. ���� (���#1)",0,0};
__root const char bcfg_smenu_bg1_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr1_11 = {CFG_COLOR,"�/�. ���� (���#2)",0,0};
__root const char bcfg_smenu_bg2_col[4]={0xFF,0,0,100};


__root const CFG_HDR cfghdr1_12 = {CFG_UINT, "��������� (�����)", 0, 20};
__root const unsigned int bcfg_mmenu_head_font = FONT_SMALL_BOLD;

__root const CFG_HDR cfghdr1_13 = {CFG_COLOR,"��������� (����)",0,0};
__root const char bcfg_mmenu_head_col[4]={0,0,0xC8,100};


__root const CFG_HDR cfghdr1_14 = {CFG_UINT, "C��� ������� (�����)", 0, 20};
__root const unsigned int bcfg_mmenu_sk_font = FONT_SMALL_BOLD;

__root const CFG_HDR cfghdr1_15 = {CFG_COLOR,"C��� ������� (����)",0,0};
__root const char bcfg_mmenu_sk_col[4]={0xC8,0,0,100};

__root const CFG_HDR cfghdr_11={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_20={CFG_LEVEL,"������",1,0};

__root const CFG_HDR cfghdr2_0 = {CFG_UINT, "����� (�����)", 0, 20};
__root const unsigned int bcfg_help_font = FONT_SMALL;

__root const CFG_HDR cfghdr2_1 = {CFG_COLOR,"����� (����)",0,0};
__root const char bcfg_help_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr2_2 = {CFG_UINT, "���������", 0, 20};
__root const unsigned int bcfg_help_scroll = 10;

__root const CFG_HDR cfghdr_21={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_30={CFG_LEVEL,"���������",1,0};

__root const CFG_HDR cfghdr3_0={CFG_CHECKBOX,"�������� ������",0,0};
__root const int bcfg_sys_check_ena = 0;

__root const CFG_HDR cfghdr3_1={CFG_CHECKBOX,"�������",0,0};
__root const int bcfg_sys_logo_ena = 1;

__root const CFG_HDR cfghdr3_2={CFG_CHECKBOX,"������� PNG-��� ��� ������",0,0};
__root const int bcfg_sys_clear_ena = 1;

__root const CFG_HDR cfghdr3_3={CFG_CHECKBOX,"������� ���������",0,0};
__root const int bcfg_illum_ena = 0;

__root const CFG_HDR cfghdr3_4 = {CFG_UINT, "��������� (%)", 0, 100};
__root const unsigned int bcfg_illum_proc = 10;


__root const CFG_HDR cfghdr_31={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_40={CFG_LEVEL,"����������",1,0};

__root const CFG_HDR cfghdr4_0 = {CFG_CBOX, "��� ����������", 0, 2};
__root const int bcfg_key_control = 1;
__root const CFG_CBOX_ITEM cfgcbox0[2] = {"������","������"};

__root const CFG_HDR cfghdr4_1={CFG_CHECKBOX,"����� ��� 5",0,0};
__root const int bcfg_key_5 = 0;

__root const CFG_HDR cfghdr_41={CFG_LEVEL,"",0,0};

#else

__root const CFG_HDR cfghdr_00={CFG_LEVEL,"������� ����",1,0};

__root const CFG_HDR cfghdr0_0 = {CFG_UINT, "��������� (�����)", 0, 20};
__root const unsigned int bcfg_gamew_head_font = FONT_SMALL;

__root const CFG_HDR cfghdr0_1 = {CFG_COLOR,"��������� (����)",0,0};
__root const char bcfg_gamew_head_col[4]={0,0,200,100};

__root const CFG_HDR cfghdr0_2 = {CFG_COLOR,"������ (����)",0,0};
__root const char bcfg_gamew_timer_col[4]={0,200,0,100};

__root const CFG_HDR cfghdr0_3 = {CFG_UINT, "���������� ���� (X)", 0, 320};
__root const int bcfg_pole_x = 0;

__root const CFG_HDR cfghdr0_4={CFG_CHECKBOX,"����� (X)",0,0};
__root const int bcfg_pole_x_min = 0;

__root const CFG_HDR cfghdr0_5 = {CFG_UINT, "���������� ���� (Y)", 0, 320};
__root const int bcfg_pole_y = 0;

__root const CFG_HDR cfghdr0_6={CFG_CHECKBOX,"����� (Y)",0,0};
__root const int bcfg_pole_y_min = 0;

__root const CFG_HDR cfghdr0_7 = {CFG_COLOR,"����� (����)",0,0};
__root const char bcfg_gamew_grid_col[4]={200,0,0,100};

__root const CFG_HDR cfghdr0_8 = {CFG_COLOR,"������ (����)",0,0};
__root const char bcfg_gamew_kontur_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr0_9 = {CFG_COLOR,"������ (����)",0,0};
__root const char bcfg_gamew_cursor_col[4]={0,220,0,100};

__root const CFG_HDR cfghdr_01={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_10={CFG_LEVEL,"����",1,0};

__root const CFG_HDR cfghdr1_0 = {CFG_UINT, "�. ���� (�����)", 0, 20};
__root const unsigned int bcfg_mmenu_font = FONT_SMALL_BOLD;

__root const CFG_HDR cfghdr1_1 = {CFG_COLOR,"�. ���� (����)",0,0};
__root const char bcfg_mmenu_col[4]={0,200,0,100};

__root const CFG_HDR cfghdr1_2 = {CFG_COLOR,"�. ���� (���#1)",0,0};
__root const char bcfg_mmenu_bg1_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr1_3 = {CFG_COLOR,"�. ���� (���#2)",0,0};
__root const char bcfg_mmenu_bg2_col[4]={200,0,0,100};



__root const CFG_HDR cfghdr1_4 = {CFG_UINT, "�. ���� (�����)", 0, 20};
__root const unsigned int bcfg_gmenu_font = FONT_SMALL;

__root const CFG_HDR cfghdr1_5 = {CFG_COLOR,"�. ���� (����)",0,0};
__root const char bcfg_gmenu_col[4]={200,0,0,100};

__root const CFG_HDR cfghdr1_6 = {CFG_COLOR,"�. ���� (���#1)",0,0};
__root const char bcfg_gmenu_bg1_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr1_7 = {CFG_COLOR,"�. ���� (���#2)",0,0};
__root const char bcfg_gmenu_bg2_col[4]={0,100,0,100};



__root const CFG_HDR cfghdr1_8 = {CFG_UINT, "�/�. ���� (�����)", 0, 20};
__root const unsigned int bcfg_smenu_font = FONT_SMALL;

__root const CFG_HDR cfghdr1_9 = {CFG_COLOR,"�/�. ���� (����)",0,0};
__root const char bcfg_smenu_col[4]={200,0,0,100};

__root const CFG_HDR cfghdr1_10 = {CFG_COLOR,"�/�. ���� (���#1)",0,0};
__root const char bcfg_smenu_bg1_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr1_11 = {CFG_COLOR,"�/�. ���� (���#2)",0,0};
__root const char bcfg_smenu_bg2_col[4]={0,100,0,100};


__root const CFG_HDR cfghdr1_12 = {CFG_UINT, "��������� (�����)", 0, 20};
__root const unsigned int bcfg_mmenu_head_font = FONT_SMALL_BOLD;

__root const CFG_HDR cfghdr1_13 = {CFG_COLOR,"��������� (����)",0,0};
__root const char bcfg_mmenu_head_col[4]={0,0,200,100};


__root const CFG_HDR cfghdr1_14 = {CFG_UINT, "C��� ������� (�����)", 0, 20};
__root const unsigned int bcfg_mmenu_sk_font = FONT_SMALL;

__root const CFG_HDR cfghdr1_15 = {CFG_COLOR,"C��� ������� (����)",0,0};
__root const char bcfg_mmenu_sk_col[4]={200,0,0,100};

__root const CFG_HDR cfghdr_11={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_20={CFG_LEVEL,"������",1,0};

__root const CFG_HDR cfghdr2_0 = {CFG_UINT, "����� (�����)", 0, 20};
__root const unsigned int bcfg_help_font = FONT_SMALL;

__root const CFG_HDR cfghdr2_1 = {CFG_COLOR,"����� (����)",0,0};
__root const char bcfg_help_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr2_2 = {CFG_UINT, "���������", 0, 20};
__root const unsigned int bcfg_help_scroll = 10;

__root const CFG_HDR cfghdr_21={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_30={CFG_LEVEL,"���������",1,0};

__root const CFG_HDR cfghdr3_0={CFG_CHECKBOX,"�������� ������",0,0};
__root const int bcfg_sys_check_ena = 1;

__root const CFG_HDR cfghdr3_1={CFG_CHECKBOX,"�������",0,0};
__root const int bcfg_sys_logo_ena = 1;

__root const CFG_HDR cfghdr3_2={CFG_CHECKBOX,"������� PNG-��� ��� ������",0,0};
__root const int bcfg_sys_clear_ena = 1;

__root const CFG_HDR cfghdr3_3={CFG_CHECKBOX,"������� ���������",0,0};
__root const int bcfg_illum_ena = 0;

__root const CFG_HDR cfghdr3_4 = {CFG_UINT, "��������� (%)", 0, 100};
__root const unsigned int bcfg_illum_proc = 10;


__root const CFG_HDR cfghdr_31={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_40={CFG_LEVEL,"����������",1,0};

__root const CFG_HDR cfghdr4_0 = {CFG_CBOX, "��� ����������", 0, 2};
__root const int bcfg_key_control = 0;
__root const CFG_CBOX_ITEM cfgcbox0[2] = {"������","������"};

__root const CFG_HDR cfghdr4_1={CFG_CHECKBOX,"����� ��� 5",0,0};
__root const int bcfg_key_5 = 0;

__root const CFG_HDR cfghdr_41={CFG_LEVEL,"",0,0};

#endif
