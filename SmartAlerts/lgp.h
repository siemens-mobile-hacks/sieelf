#ifndef lgp_H
#define lgp_H

#define EN
#ifdef EN
const char on[]="on";
const char off[]="off";
const char on2[]="on";
const char off2[]="off";
const char change[]="change";
const char select[]="select";
const char back[]="back";
const char save[]="save";
const char ok[]="ok";
const char *an[10]={"Voice","Timekeeping","Twice","Time","Minute","Melody","Minute2","Melody2","Filter"};
const char *wd[7]={"Mo","Tu","We","Th","Fr","Sa","Su"};
const char *wd2[7]={"Monday","Tuesday","Wednesday","Thesday","Friday","Saturday","Sunday"};
const char name[]="SmartAlerts Setting";
const char *mn[6]={"OnlyVibra","Voice","OnlyFrom","OnlyTo","Melody","Intervall"};
const char *bn[4]={"BatterySave","BatteryNumerical","Melody","Count"};
const char rn[]="DateSupply";
const char *alerts_name[9]={"Alarm","Alerts","Auto-profile","Missed Alerts","BatterySetting","Runfile","Auto-call","Auto-Sms","Other"};
const char *Alarm_name[6]={"Alarm 1","Alarm 2","Alarm 3","Alarm 4","Alarm 5","Alarm 6"};
#ifndef NEWSGOLD
const char *othern[8]={"Vibra","Displays","Keyboard","Dynlight","Volume","Vibra count","Vibra power","Light"};
#else
const char *othern[8]={"Vibra","Displays","Keyboard","Lighter","Volume","Vibra count","Vibra power","Light"};
#endif

#else
const char on[]="��";
const char off[]="��";
const char on2[]="on";
const char off2[]="off";
const char change[]="����";
const char select[]="ѡ��";
const char back[]="����";
const char save[]="����";
const char ok[]="ȷ��";
const char *an[10]={"��Ƶģʽ","��ʱģʽ","������Ч","ʱ������","��ʾ����","��ʾ��Ч","��ʾ����2","��ʾ��Ч2","��Ƶ�龰����"};
const char *wd[7]={"һ","��","��","��","��","��","��"};
const char *wd2[7]={"����һ","���ڶ�","������","������","������","������","������"};
const char name[]="���������趨";
const char *mn[6]={"��ģʽ","��Ƶģʽ","��ʼʱ��","����ʱ��","��Ч���","��ʾ���"};
const char *bn[4]={"��������","������ֵ","��Ƶ���","��ʾ����"};
const char rn[]="����֧��";
const char *alerts_name[9]={"��������","��ʱ����","�龰�任","δ������","��������","�����ļ�","��ʱ�绰","��ʱ����","��������"};
const char *Alarm_name[6]={"���� 1","���� 2","���� 3","���� 4","���� 5","���� 6"};
#ifndef NEWSGOLD
const char *othern[8]={"��","��Ļ","����","����","��Ƶ����","�񶯴���","��ǿ��","����"};
#else
const char *othern[8]={"��","��Ļ","����","����","��Ƶ����","�񶯴���","��ǿ��","����"};
#endif

#endif

#endif
