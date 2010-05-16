#include "c:\arm\inc\swilib.h"
#include "c:\arm\inc\mplayer.h"
#include "c:/arm/inc/xtask_ipc.h"
#include "conf_loader.h"
#include "lang.h"

/*------------------------------------------------------|
//  cMPaB - Close MediaPlayer and Base mediafiles     //|
//                                                    //|
//                     (C) Vedan                      //|
//                     (i) Tolsi                      //|
//                                                    //|
<<<<<<<<<<<<<<<<<<       2008      >>>>>>>>>>>>>>>>>>>>>>
-------------------------------------------------------*/

//����� �����
unsigned int MAINCSM_ID = 0;     //����� ����������� ��� CSM'a
const int minus11=-11;

//--------------------------------------------------------------------��� ������
IPC_REQ gipc;
#define IPC_CMPAB_NAME "CMPAB"   //��� ��� ����� ��� ������, ����� �� ������� ���
const char ipc_my_name[32] = IPC_CMPAB_NAME;
const char ipc_xtask_name[]= IPC_XTASK_NAME;
//------------------------------------------------------------------------------

//--------------------------------------------------------��� �������� ���������
#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);
unsigned int base_csmid=0;
void *base_csmadr=NULL;
//------------------------------------------------------------------------------

extern const int TAKTS,          //����� ���������� �� ������� ( 216 ������ = 1 ������)
                 T_CLOCK_1,      //��� ��������
                 T_MIN_1,        //������ ��������
                              
                 ENA_HELLO_MSG,  //�������� �� ������������
                 ENA_BY_MSG,     //�������� �� ���������� ���������
                 MODE_FONE,      //��� �������� � ���������
                 MODE_ACT_MP,    //��� �������� � �����������
                 ENA_SWAP,       //�������� �� ������������
                 ENA_KILL_CMPAB, //������� �� ���� ����� �������� ������
                 PERCENT,        //�������� �������
                 ENA_CHECK_PERC, //�������� �� �������� �� ��������
                 ENA_CHECK_TIME, //�������� �� �������� �� �����
                 ENA_RECO_MSG,   //�������� �� ��������� ��������������
                 ENA_KILL_BASE;  //������� �� ���������


extern const char BY_TEXT[128],   //�����, ������� ����� ������� ����� �������� ������
                  CSMBIBLADR[9];  //�������� ����������

void CURTAIL() //�������� ��
{
  gipc.name_to=ipc_xtask_name;
  gipc.name_from=ipc_my_name;
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
}



GBSTMR mytmr;

typedef struct{CSM_RAM csm;CSM_RAM bmpcsm;}MAIN_CSM;


extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int CHECK_PERC=0;
void RereadSettings()
{
  InitConfig();
  if(ENA_CHECK_PERC)CHECK_PERC=1;
  if(ENA_KILL_BASE) base_csmadr=(void *)strtoul(CSMBIBLADR,NULL,16);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}



void KillBase() //������� ����
{
  if (!base_csmid)
  { CSM_RAM *p=((void **)CSM_root()->csm_q)[2];
    while(p) { if (p->constr==base_csmadr) break;
               p=p->next;}
               if (p)
               base_csmid=p->id;}  
  
  CSM_RAM *csmp=FindCSMbyID(base_csmid);
  if (csmp)//���� ��������� ��� ����, �� ������� � 
    CloseCSM(csmp->id); else base_csmid=0;
}


void Do()
{
  switch(MODE_ACT_MP) //��������� �������� � �������, �������� ����, ������� � �������
  {
  case 0:  MPlayer_Shutdown(); break;
  case 1:  MPlayer_Stop();     break;
  case 2:  MPlayer_Pause();    break;
  }
  
  switch(MODE_FONE) //��������� �������� � ���������, �������� ����, ������� � �������
  {
  case 0: SwitchPhoneOff(); break;
  case 1: RebootPhone();    break;
  case 2: KbdLock();        break;
  }
  
  if(ENA_KILL_BASE)// ���� �������� ���������� ����, ������������ �������� �� � ����������� � ����������� ��������
  KillBase(); 
  if (ENA_BY_MSG) ShowMSG(1,(int) BY_TEXT); //������� ���������
  if (ENA_SWAP) CURTAIL();                  // �������� ��
  if (ENA_KILL_CMPAB) CloseCSM(MAINCSM_ID); //���� �������� ��������, �� �������� ����
 
}


GUI *datagui;
CSM_RAM *csm;
char s[40]; //���� �������� �������� csm ��� �������� ������� ����� ������������ � ���������/������� ��������� � �������
char s1[40];








void TimerProcCheck()
{
  if(CHECK_PERC)            // ���� �������� �������� �� ��������, ������ ��, ��� ����
  {  if(*RamCap()<=PERCENT) // ���������� �������� ��������� ������� � ������ �� �������
     {                      // ���� �������� ������� ������ ��� �����, ��������� �������� ��������
       Do();                // �������� ��������� ��������
       CHECK_PERC=0;       // ����������� ����, ����� �� ��������� ��������
      }
  }
  if(ENA_CHECK_TIME)        // ���� �������� �������� �� ����� ������ ��, ��� ����
  {
    TDate date;
    TTime time;
    GetDateTime(&date,&time); //�������� ����, �����
    if((time.hour==T_CLOCK_1)&&(time.min==T_MIN_1)&&(time.sec==0)) //���� ����� � ������ ������� � ����,��� � �������, ��������� �������� ��������
    Do(); // �������� ��������� ��������
  }
  
  
  GBS_StartTimerProc(&mytmr, TAKTS ,TimerProcCheck); //��������� ��� ��������� �� ��������� TAKTS :)
}


int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg) //����� ���� ��������� ��������� �� ������ ������
{
 if(msg->msg == MSG_RECONFIGURE_REQ) //���� ������� ��������� � ������������, �� ��������� �������� ����
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      if (ENA_RECO_MSG) //���� ������� ����� ��������������, �������� ��������������� ���������
      ShowMSG(1,(int) LGP_MAIN_UPDT_MSG );
      RereadSettings(); //���������������� ������
    }
  }

  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}



static void maincsm_onclose(CSM_RAM *csm) 
{
  SUBPROC((void *)Killer);
  GBS_DelTimer(&mytmr);
}

static unsigned short maincsm_name_body[140];

static const struct
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

static void UpdateCSMname(void) // ����������� ��� �����
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), LGP_MAIN_ELF_NAME );
}

// �������� �������, ����������� ������ ��� ������ �����
int main()
{
  RereadSettings(); //�������������� ������
  TimerProcCheck();
  
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();

  if (ENA_HELLO_MSG)                          // ���� �������� ����������� ,
  ShowMSG(1,(int) LGP_MAIN_INST_MSG );        // ������� ��������� � ������������
  
  return 0;
}
