#ifndef lgp_H
#define lgp_H

#define EN
#ifdef EN
const char on[]="on";
const char off[]="off";
const char alarm_name[]="Alarm";
const char change[]="change";
const char save[]="save";
const char ok[]="ok";
const char *wd[7]={"Mo","Tu","We","Th","Fr","Sa","Su"};
const char *wd2[7]={"Monday","Tuesday","Wednesday","Thesday","Friday","Saturday","Sunday"};
#else
const char on[]="��?";
const char off[]="����.";
const char alarm_name[]="��������?;
const char change[]="����?";
const char save[]="����.";
const char ok[]="��";
const char *wd[7]={"��","��","��","��","��","��","��"};
const char *wd2[7]={"����������?,"������?,"����?,"������?,"?����?,"������?,"����������?};
#endif

#endif
