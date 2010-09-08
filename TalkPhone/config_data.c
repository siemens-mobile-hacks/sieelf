#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef ELKA
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_CBOX,"��TalkPhone",0,2};
__root const int on_off=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"��","��"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"û��������ʱ�Ƿ�ʱ",0,2};
__root const int keypad_lock=0;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"��","��"};

__root const CFG_HDR cfghdr2={CFG_UINT,"ָ��������ʱ��ʱ�ȼ�",0,65535};
__root const unsigned int CALL_BUTTON=0;

//---------------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"ʱ���趨",1,0};

__root const CFG_HDR cfghdr1_1={CFG_TIME,"��ʼʱ��",0,0};
__root const TTime TimeFrom={8,0};

__root const CFG_HDR cfghdr1_2={CFG_TIME,"����ʱ��",0,0};
__root const TTime TimeTo={23,0};

__root const CFG_HDR cfghdr1_3={CFG_UINT,"��ʱ���� 1 =",0,59};
__root const unsigned int begin_minute1=0;

__root const CFG_HDR cfghdr1_4={CFG_UINT,"��ʱ���� 2 =",0,59};
__root const unsigned int begin_minute2=30;

__root const CFG_HDR cfghdr1_5={CFG_UINT,"��ʱ���� 3 =",0,59};
__root const unsigned int begin_minute3=0;

__root const CFG_HDR cfghdr1_6={CFG_TIME,"��ʱ�ų�ʱ�俪ʼ",0,0};
__root const TTime TimeExFrom={0,0};

__root const CFG_HDR cfghdr1_7={CFG_TIME,"��ʱ�ų�ʱ�����",0,0};
__root const TTime TimeExTo={0,0};

__root const CFG_HDR cfghdr1_8={CFG_UINT,"���龰�²��Զ���ʱ",1,8};
__root const unsigned int ExProfile=2;

__root const CFG_HDR cfghdr1_9={CFG_CBOX,"����ʱ���Զ���ʱ",0,2};
__root const int music_cut=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"��","��"};


__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"��Ч�趨",1,0};

__root const CFG_HDR cfghdr2_1={CFG_UINT,"����",0,6};
__root const unsigned int volume=6;

__root const CFG_HDR cfghdr2_2={CFG_STR_UTF8,"��ʱ*.WAV�ļ�·��",0,127};
__root const char folder_path[128]=DEFAULT_DISK ":\\ZBin\\TalkPhone\\";

__root const CFG_HDR cfghdr2_3={CFG_CBOX,"ÿ��Сʱ����",0,2};
__root const int PLAY_PARAM=1;
__root const CFG_CBOX_ITEM cfgcbox7[2]={"��","ȫ��"};

__root const CFG_HDR cfghdr2_4={CFG_CBOX,"�ȼ���ʱ",0,2};
__root const int PLAY_PARAM_BTN_CALL=1;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"��","��"};

__root const CFG_HDR cfghdr2_5={CFG_STR_UTF8,"��ʱǰ׺�ļ�",0,127};
__root const char kurant_path[128]=DEFAULT_DISK ":\\ZBin\\TalkPhone\\x.wav";

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"ͼ���趨",1,0};

__root const CFG_HDR cfghdr3_1={CFG_CBOX,"��ʾͼ��",0,2};
__root const int show_icon=0;
__root const CFG_CBOX_ITEM cfgcbox5[2]={"��","��"};

__root const CFG_HDR cfghdr3_2={CFG_COORDINATES,"ͼ��λ��",0,0};
__root const unsigned int cfgX=0;
__root const unsigned int cfgY=30;

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"������",1,0};

__root const CFG_HDR cfghdr4_1={CFG_CBOX,"������",0,2};
__root const int Is_Vibra_Enabled=0;
__root const CFG_CBOX_ITEM cfgcbox6[2]={"��","��"};

__root const CFG_HDR cfghdr4_2 = {CFG_UINT, "�񶯴���", 0, 10};
__root const unsigned int vibra_count = 1;

__root const CFG_HDR cfghdr4_3 = {CFG_UINT, "��ǿ��", 0, 100};
__root const unsigned int vibra_power = 50;

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};
