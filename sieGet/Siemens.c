/*
  ������ SieGet Downloader
                          */

// Siemens.c
// ��������� ������� ��� ������
// (c) Cbn
// ���������� � ��������� Borman

#include "..\inc\swilib.h"

extern int onStart(char *exename, char *fname); // ����� ����������. ���������� 0 (��) ��� 1 (�����).
extern void onCreate(); // �������� �������
extern void onClose(); // �������� �������
extern void onExit(); // �����
extern void onFocus(); // ����� ����� �� �������
extern void onUnFocus(); // ����� ����� ������ � �������
extern void onRedraw(void); // ����������� ������
extern int onKey(unsigned char keycode, int pressed); // ������� �������. ���������� 0 (��) ��� 1 (GeneralFunc->�����) ��� -1 (Redraw).
extern int onSockEvent(int sock, int event); // ������� ������
extern int onDNREvent(int DNR_ID); //��������� ���������� DNR-�������

void UpdateCSMName(char *new_name);

// ���� ����������
typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void method0(MAIN_GUI *data)// onRedraw
{
  onRedraw();
}
void method1(MAIN_GUI *data, void *(*malloc_adr)(int))// onCreate
{
  onCreate();
  data->gui.state=1;
}
void method2(MAIN_GUI *data, void (*mfree_adr)(void *))// onClose
{
  data->gui.state=0;
}
void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))// onFocus
{
  onFocus();
  data->gui.state=2;
}
void method4(MAIN_GUI *data, void (*mfree_adr)(void *))// onUnFocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}
int method5(MAIN_GUI *data, GUI_MSG *msg)// onKey
{
  return onKey(msg->gbsmsg->submess, msg->gbsmsg->msg);
}
void method7(MAIN_GUI *data, void (*mfree_adr)(void *)){}//  onDestroy
int method8(void){return(0);} // ������ �-�
int method9(void){return(0);} // ������ �-�

const void * const gui_methods[11]={
  (void *)method0,	//Redraw
  (void *)method1,	//Create
  (void *)method2,	//Close
  (void *)method3,	//Focus
  (void *)method4,	//Unfocus
  (void *)method5,	//OnKey
  0,
  (void *)method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM *csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  StoreXYWHtoRECT(&Canvas, 0, YDISP, ScreenW(), ScreenH()-YDISP);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void Killer(void){
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  onExit();
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
  //  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void maincsm_onclose(CSM_RAM *csm)
{
  onClose();
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg){
  MAIN_CSM *csm=(MAIN_CSM*)data;

  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    if ((int)msg->data0==ENIP_DNR_HOST_BY_NAME)
      return onDNREvent((int)msg->data1);
    else
      return onSockEvent((int)msg->data1, (int)msg->data0);
  }

  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
    csm->csm.state=-3;
  return(1);
}

const int minus11=-11;
unsigned short maincsm_name_body[140];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
    maincsm_onmessage,
    maincsm_oncreate,
#ifdef NEWSGOLD
0,
0,
0,
0,
#endif
maincsm_onclose,
sizeof(MAIN_CSM),
1,
&minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMName(char *new_name)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "%t", new_name);
}

int main(char *exename, char *fname){
  char dummy[sizeof(MAIN_CSM)];
  if(onStart(exename,fname)) SUBPROC((void *)Killer);
  else CreateCSM(&MAINCSM.maincsm,dummy,0);
  return 0;
}



