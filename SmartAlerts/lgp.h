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
const char on[]="开";
const char off[]="关";
const char on2[]="on";
const char off2[]="off";
const char change[]="更改";
const char select[]="选择";
const char back[]="返回";
const char save[]="保存";
const char ok[]="确认";
const char *an[10]={"音频模式","报时模式","两次音效","时间区间","提示分钟","提示音效","提示分钟2","提示音效2","音频情景禁用"};
const char *wd[7]={"一","二","三","四","五","六","日"};
const char *wd2[7]={"星期一","星期二","星期三","星期四","星期五","星期六","星期日"};
const char name[]="智能提醒设定";
const char *mn[6]={"振动模式","音频模式","起始时间","结束时间","音效编号","提示间隔"};
const char *bn[4]={"电量保护","保护数值","音频编号","提示次数"};
const char rn[]="日期支持";
const char *alerts_name[9]={"多重闹钟","定时提醒","情景变换","未接提醒","电量提醒","运行文件","定时电话","定时短信","其他设置"};
const char *Alarm_name[6]={"闹钟 1","闹钟 2","闹钟 3","闹钟 4","闹钟 5","闹钟 6"};
#ifndef NEWSGOLD
const char *othern[8]={"振动","屏幕","键盘","动感","音频音量","振动次数","振动强度","亮度"};
#else
const char *othern[8]={"振动","屏幕","键盘","闪灯","音频音量","振动次数","振动强度","亮度"};
#endif

#endif

#endif
