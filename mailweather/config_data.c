#include "..\inc\cfg_items.h"
#include "swilib.h"
//������������
__root const CFG_HDR cfghdr0={CFG_CBOX,"���������� �������� ��� ������",0,2};
__root const int ENA_HELLO_MSG = 1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"���","��"};

__root const CFG_HDR cfghdr330={CFG_CBOX,"���������� ���������",0,2};
__root const int ENA_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox1_0[2]={"���","��"};

__root const CFG_HDR cfghdr3 = {CFG_UINT, "����� ����������(���)", 0, 120};
__root const unsigned int refresh = 60;

__root const CFG_HDR cfghdr14={CFG_STR_UTF8,"�� ������",0,63};
__root const char id_tower[64]="1956";



__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"��������� ��������",1,0};

  __root const CFG_HDR cfghdr20={CFG_STR_UTF8,"���� � ���������",0,63};
  __root const char weather_img_path[64]="4:\\zbin\\mailweather\\";
  
  __root const CFG_HDR cfghdr21 = {CFG_COORDINATES,"�������",0,0};
  __root const unsigned int weather_X = 0;
  __root const unsigned int weather_Y = 90;
  
  __root const CFG_HDR cfghdr22={CFG_CBOX,"���������� ��������",0,2};
  __root const int IKONA=0;
  __root const CFG_CBOX_ITEM cfgcbox6[2]={"No","Yes"};

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};




__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"��������� ������",1,0};
  
  __root const CFG_HDR cfghdr2_8 = {CFG_UINT, "�����(1-png/1xx-sys)", 0, 250};
  __root const unsigned int font = FONT_SMALL+100;
  
  __root const CFG_HDR cfghdr23 = {CFG_STR_UTF8, "���� � png ������", 0, 127};
  __root const char fontpath[128] = "";
  
  __root const CFG_HDR cfghdr28={CFG_CBOX,"������������ ������ �����",0,2};
  __root const int fullfont=1;
  __root const CFG_CBOX_ITEM cfgcbox7[2]={"No","Yes"};
  
  __root const CFG_HDR cfghdr2_2 = {CFG_UINT, "���������� ����� �������", 0, 10};
  __root const unsigned int space = 1;
  
    __root const CFG_HDR cfghdr60_2={CFG_COLOR,"���� ����. ������",0,0};
    __root const char fontColor[4]={0xFF,0xFF,0xFF,100};
    
    __root const CFG_HDR cfghdr60_3={CFG_COLOR,"���� ���� ����.������",0,0};
    __root const char bgrColor[4]={0x00,0x00,0x00,100};
    
    __root const CFG_HDR cfghdr60_4={CFG_CBOX,"�������� �����",0,2};
    __root const int isOutline=1;
    __root const CFG_CBOX_ITEM cfgcbox7_1[2]={"No","Yes"};

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};




__root const CFG_HDR cfghdr_m212={CFG_LEVEL,"��������� ���.������",1,0};
  
  __root const CFG_HDR cfghdr112_0={CFG_CBOX,"������������ ������� ������",0,2};
  __root const int ENA_SCROLL=1;
  __root const CFG_CBOX_ITEM cfgcbox1_1[2]={"No","Yes"};
  
  __root const CFG_HDR cfghdr13 = {CFG_RECT,"�����. ������",0,0};
  __root const RECT pos1={5,285,234,295};
//  __root const unsigned int x = 2;
//  __root const unsigned int y = 303;
  
  //__root const CFG_HDR cfghdr_0={CFG_UINT,"������ ������� ������",0,240};
  //__root const unsigned int scrollsize=236;
  
  __root const CFG_HDR cfghdr2_25 = {CFG_UINT, "��������(1���=216)", 0, 65535};
  __root const unsigned int TimeUpdateScroll = 140;
  
  __root const CFG_HDR cfghdr2_26 = {CFG_UINT, "�������� � ���. � �����", 0, 65535};
  __root const unsigned int scrollDelay = 5;
  
  
  __root const CFG_HDR cfghdr22_35 = {CFG_CBOX, "������������ ���.������", 0, 3};
  __root const int al = 0;
  __root const CFG_CBOX_ITEM cfgcbox6_5[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr_m21_4={CFG_LEVEL,"",0,0};




__root const CFG_HDR cfghdr_m61={CFG_LEVEL,"����������a",1,0};
  
  __root const CFG_HDR cfghdr4={CFG_CBOX,"���������� �����������",0,2};
  __root const int show_temp=1;
  __root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};
  
  __root const CFG_HDR cfghdr5 = {CFG_COORDINATES,"�����. ����.",0,0};
  __root const unsigned int date_X = 0;
  __root const unsigned int date_Y = 40;
  
  __root const CFG_HDR cfghdr6={CFG_STR_WIN1251,"����. �����",0,127};
  __root const char str_temp[128]="����: ";
  
  __root const CFG_HDR cfghdr40={CFG_CBOX,"��� �������� ����",0,3};
  __root const int chekeris1=1;
  __root const CFG_CBOX_ITEM cfgcbox10[3]={"everywhere","unlocked","locked"};
  
  __root const CFG_HDR cfghdr22_1 = {CFG_CBOX, "������������", 0, 3};
  __root const int align1 = 0;
  __root const CFG_CBOX_ITEM cfgcbox6_1[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"",0,0};




__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"�������� �����",1,0};
  
  __root const CFG_HDR cfghdr7={CFG_CBOX,"���������� �������� �����",0,2};
  __root const int show_speed=1;
  __root const CFG_CBOX_ITEM cfgcbox2[2]={"No","Yes"};
  
  __root const CFG_HDR cfghdr15 = {CFG_COORDINATES,"�����. ��������",0,0};
  __root const unsigned int date_X2 = 0;
  __root const unsigned int date_Y2 = 50;
  
  __root const CFG_HDR cfghdr41={CFG_CBOX,"��� �������� ����",0,3};
  __root const int chekeris2=1;
  __root const CFG_CBOX_ITEM cfgcbox11[3]={"everywhere","unlocked","locked"};
  
  __root const CFG_HDR cfghdr22_2 = {CFG_CBOX, "������������", 0, 3};
  __root const int align2 = 0;
  __root const CFG_CBOX_ITEM cfgcbox6_2[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};




__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"������",1,0};
  
  __root const CFG_HDR cfghdr8={CFG_CBOX,"���������� ������",0,2};
  __root const int show_prognoze=1;
  __root const CFG_CBOX_ITEM cfgcbox3[2]={"No","Yes"};
  
  __root const CFG_HDR cfghdr9 = {CFG_COORDINATES,"�����. ������",0,0};
  __root const unsigned int date_X3 = 0;
  __root const unsigned int date_Y3 = 60;
  
  __root const CFG_HDR cfghdr43={CFG_CBOX,"��� �������� ����",0,3};
  __root const int chekeris3=1;
  __root const CFG_CBOX_ITEM cfgcbox13[3]={"everywhere","unlocked","locked"};
  
  __root const CFG_HDR cfghdr22_3 = {CFG_CBOX, "������������", 0, 3};
  __root const int align3 = 0;
  __root const CFG_CBOX_ITEM cfgcbox6_3[3] = {"Left", "Center", "Right"};
  
__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};
  
  
  
  
__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"��������",1,0};
  
  __root const CFG_HDR cfghdr10={CFG_CBOX,"���������� ��������",0,2};
  __root const int show_davlenie=1;
  __root const CFG_CBOX_ITEM cfgcbox4[2]={"No","Yes"};
  
  __root const CFG_HDR cfghdr11 = {CFG_COORDINATES,"�����. ��������",0,0};
  __root const unsigned int date_X4 = 0;
  __root const unsigned int date_Y4 = 70;
  
  __root const CFG_HDR cfghdr16={CFG_STR_WIN1251,"�������� �����",0,127};
  __root const char str_davlenie[128]="��������: ";
  
  __root const CFG_HDR cfghdr44={CFG_CBOX,"��� �������� ����",0,3};
  __root const int chekeris4=1;
  __root const CFG_CBOX_ITEM cfgcbox14[3]={"everywhere","unlocked","locked"};
  
  __root const CFG_HDR cfghdr22_4 = {CFG_CBOX, "������������", 0, 3};
  __root const int align4 = 0;
  __root const CFG_CBOX_ITEM cfgcbox6_4[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};




__root const CFG_HDR cfghdr_m81={CFG_LEVEL,"���������",1,0};
  
  __root const CFG_HDR cfghdr12={CFG_CBOX,"���������� ���������",0,2};
  __root const int show_vlaznost=1;
  __root const CFG_CBOX_ITEM cfgcbox5[2]={"No","Yes"};
  
  __root const CFG_HDR cfghdr133 = {CFG_COORDINATES,"�����. ���������",0,0};
  __root const unsigned int date_X5 = 0;
  __root const unsigned int date_Y5 = 80;
  
  __root const CFG_HDR cfghdr17={CFG_STR_WIN1251,"��������� �����",0,127};
  __root const char str_vlaznost[128]="���������: ";
  
  __root const CFG_HDR cfghdr45={CFG_CBOX,"��� �������� ����",0,3};
  __root const int chekeris5=1;
  __root const CFG_CBOX_ITEM cfgcbox15[3]={"everywhere","unlocked","locked"};
  
  __root const CFG_HDR cfghdr22_5 = {CFG_CBOX, "������������", 0, 3};
  __root const int align5 = 0;
  __root const CFG_CBOX_ITEM cfgcbox6_25[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr_m80={CFG_LEVEL,"",0,0};
