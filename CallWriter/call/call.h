static volatile char is_call=0; //0 - No Call  1 - ishodschy(not written) 2 - incoming(not written) 3 - ishodschy(written) 4 - incoming(written) 5 - auto-recording(incoming)
#define CALL_NULL 0
#define CALL_OUT 1
#define CALL_IN 2
#define CALL_OUTW 3
#define CALL_INW 4
#define CALL_AUTOW 5
#define SEC 216
TDate d;
TTime real_time,t;
unsigned int in=0,out=0,autom=0;
char name[32];
extern const int profile;
extern const int time_on_sec,time_on_min,time_off_sec,time_off_min;
extern const int time_on_on,time_off_off;
extern const int opmod,add,ena_loud;
extern const unsigned int Key1,Key1Type,Key2,Key2Type;
extern const char mic[9],loud[9];
GBSTMR tmr;

void OpenCall();
void CloseCall();
void Close();
void Auto();
void UpdateCSMname();
void func(const char *adr);
