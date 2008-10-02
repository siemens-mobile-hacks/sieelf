#include "..\..\inc\swilib.h"
#include "..\MySMSYS_ipc.h"

#pragma swi_number=0x9E
__swi __arm int GetMissedEventCount(unsigned int Event);

#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);

#define RAM_SMS_dat_FileHandler 0xA8DADE14
#define RAM_WB_dat_FileHandler 0xA8DADE16
#define RAM_EMS_Admin_dat_FileHandler 0xA8DEEA20

extern __thumb void OpenInbox(void);
extern __thumb void Update_MissedEventsPtr(void);
const char my_ipc_name[]=MY_SMSYS_IPC_NAME;
const IPC_REQ my_ipc=
{
	my_ipc_name,
	my_ipc_name,
	NULL
};

__arm void send_ipc(int ipc_msg)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,ipc_msg,&my_ipc);
}

/*
__thumb int new_keylock_onkey(GUI *data, GUI_MSG *msg)
{
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    if(msg->gbsmsg->submess==LEFT_SOFT)
    {
      int all, sms;
      Update_MissedEventsPtr();
      all=GetMissedEventCount(0);
      sms=GetMissedEventCount(2);
      if((sms>0)&&(all==sms))
      {
	TempLightOn(3, 0x7FFF);
	send_ipc(SMSYS_IPC_IN_ALL);
	//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_IN_ALL,&my_ipc);
      }
      else if(all>0)
      {
	OpenInbox();
      }
    }
  }
  if(msg->gbsmsg->msg==LONG_PRESS)
    TempLightOn(3, 0x7FFF);
  return 0;
}

extern WSHDR *GetMenuItemText(void *gui, int n);
//extern WSHDR *GetMLMenuItemWS2(void *gui, int n);
extern WSHDR *GetMLMenuItemWS2L2(void *gui, int n);
__arm void inbox_view(void *gui)
{
  WSHDR **data;
  WSHDR *ws1, *w1;
  WSHDR *ws2, *w2;
  IPC_REQ my_ipc2=
  {
    my_ipc_name,
    my_ipc_name,
    NULL
  };
  int n=GetCurMenuItem(gui);
  if((w1=GetMenuItemText(gui,n))!=0 && (w2=GetMLMenuItemWS2L2(gui, n))!=0)
  {
    data=malloc(2*sizeof(void *));
    ws1=AllocWS(w1->wsbody[0]+4);
    ws2=AllocWS(w2->wsbody[0]+4);
    wstrcpy(ws1, w1);
    wstrcpy(ws2, w2);
    data[0]=ws1;
    data[1]=ws2;
    my_ipc2.data=data;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_INBOX_VIEW,&my_ipc2);
  }
}
*/
typedef struct
{
	char header[8];
	int version;
//	int type;
	char time[32];
	char number[32];
//	unsigned short len;
//	unsigned short *txt;
}MSS_FILE_P1;

#define TYPE_UNK	0
#define TYPE_OUT	1
#define TYPE_IN_R	2 //readed
#define TYPE_IN_N 	3 //new
#define TYPE_DRAFT	4
#define TYPE_IN_ALL 	5


const char FLDR_IN[]="In\\";
const char FLDR_OUT[]="Out\\";
const char FLDR_DRAFT[]="Draft\\";
const char FLDR_MAIN[]="0:\\ZBin\\MySMSYS\\";

__thumb int getFileCount(int type)
{
	//char path[128];
	unsigned int err;
//	int fp;
//	const char *folder;
	char dir[128];
//	char fullpath[128];
	int n=0;
	//FSTATS fst;
	DIR_ENTRY de;
//	int c=GetProfile();
	strcpy(dir, FLDR_MAIN);
	switch(type)
	{
	case TYPE_DRAFT:
		strcat(dir, FLDR_DRAFT);
		break;
	case TYPE_OUT:
		strcat(dir, FLDR_OUT);
		break;
//	case TYPE_IN_N:
//	case TYPE_IN_R:
	case TYPE_IN_ALL:
		strcat(dir, FLDR_IN);
		break;
//	default:
//		folder=FLDR_UNK;
//		break;
	}
//	strcat(dir, folder);
	if(!isdir(dir, &err))
		return 0;
	strcat(dir, "*.mss");
	if(FindFirstFile(&de, dir, &err))
	{
		do
		{
		  if(de.file_size>=(sizeof(MSS_FILE_P1)))
		    n++;
		}
		while(FindNextFile(&de, &err));
	}
	FindClose(&de, &err);
	return n;
}

/*
__arm void getInSMSCount(int *all, int *inn) //all, new
{
  const char sms_dat[]="0:\\System\\SMS\\SMS.dat";
  unsigned int err;
  int fin;//=*(short *)RAM_SMS_dat_FileHandler;
  int size;//=lseek(fin, 0, S_END, &err, &err)-2;
  char *dat_buf;
  int i, n;
  char *p;
  if((fin=fopen(sms_dat, A_BIN+A_ReadOnly, P_READ, &err))<0)
    goto FILE1;
  *all=0;
  *inn=0;
  size=lseek(fin, 0, S_END, &err, &err)-2;
  if(size%(sizeof(PDU))!=0)
  {
    fclose(fin, &err);
    goto FILE1;
  }
  n=size/(sizeof(PDU));
  dat_buf=malloc(size);
  lseek(fin, 2, S_SET, &err, &err);
  if((fread(fin, dat_buf, size, &err)!=size))
  {
    fclose(fin, &err);
    mfree(dat_buf);
    goto FILE1;
  }
  fclose(fin, &err);
  for(i=0;i<n;i++)
  {
    p=dat_buf+i*(sizeof(PDU));
    if((p[2]==0x1)||(p[2]==0x3))
    {
      (*all)++;
      if(p[2]==0x3)
	(*inn)++;
    }
  }
  mfree(dat_buf);
FILE1:
  (*all)+=getFileCount(TYPE_IN_ALL);
}

__arm int getOtherCount(int type)
{
  const char sms_dat[]="0:\\System\\SMS\\SMS.dat";
  int res=0;
  unsigned int err;
  int fin;//=*(short *)RAM_SMS_dat_FileHandler;
  int size;//=lseek(fin, 0, S_END, &err, &err)-2;
  char *dat_buf;
  int i, n;
  char *p;
  if((fin=fopen(sms_dat, A_BIN+A_ReadOnly, P_READ, &err))<0)
    goto FILE;
  size=lseek(fin, 0, S_END, &err, &err)-2;
  if(size%(sizeof(PDU))!=0)
  {
    fclose(fin, &err);
    goto FILE;
  }
  n=size/(sizeof(PDU));
  dat_buf=malloc(size);
  lseek(fin, 2, S_SET, &err, &err);
  if((fread(fin, dat_buf, size, &err)!=size))
  {
    fclose(fin, &err);
    mfree(dat_buf);
    goto FILE;
  }
  fclose(fin, &err);
  for(i=0;i<n;i++)
  {
    p=dat_buf+i*(sizeof(PDU));
    switch(type)
    {
    case TYPE_DRAFT:
      if(p[2]==0x07)
	res++;
      break;
    case TYPE_OUT:
      if(p[2]==0x05)
	res++;
      break;
//    case TYPE_IN_N:
//    case TYPE_IN_R:
//    case TYPE_IN_ALL:
//      break;
//    default:
//      break;
    }
  }
  mfree(dat_buf);
FILE:
  res+=getFileCount(type);
  return res;
}
*/
void CreateSmsWithNum(char *num)
{
   IPC_REQ my_ipc3=
  {
    my_ipc_name,
    my_ipc_name,
    NULL
  };
//  IPC_REQ *my_ipc3;
  char *data;
  LockSched();
//  my_ipc3=malloc(sizeof(IPC_REQ));
  data=malloc(strlen(num)+2);
//  my_ipc3->name_to=my_ipc_name;
//  my_ipc3->name_from=my_ipc_name;
  strcpy(data, num);
  my_ipc3.data=data;
//  my_ipc3->data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEWSMS_NUM,&my_ipc3);
  UnlockSched();
}

void CreateSmsWithNum_2(char *num)
{

  IPC_REQ *my_ipc3;
  char *data;
  my_ipc3=malloc(sizeof(IPC_REQ));
  data=malloc(strlen(num)+2);
  my_ipc3->name_to=my_ipc_name;
  my_ipc3->name_from=my_ipc_name;
  strcpy(data, num);
  my_ipc3->data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEWSMS_NUM,my_ipc3);

/*
   IPC_REQ my_ipc3=
  {
    my_ipc_name,
    my_ipc_name,
    NULL
  };
  char *data;
  data=malloc(strlen(num)+2);
  strcpy(data, num);
  my_ipc3.data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEWSMS_NUM,&my_ipc3);*/
}

void CreateSmsWithNum_3(char *num)
{

  IPC_REQ *my_ipc3;
  char *data;
  LockSched();
  my_ipc3=malloc(sizeof(IPC_REQ));
  data=malloc(strlen(num)+2);
  my_ipc3->name_to=my_ipc_name;
  my_ipc3->name_from=my_ipc_name;
  strcpy(data, num);
  my_ipc3->data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEWSMS_NUM,my_ipc3);
  UnlockSched();
}

void OrgSendText(char *text) //utf8
{
   IPC_REQ my_ipc4=
  {
    my_ipc_name,
    my_ipc_name,
    NULL
  };
  char *data;
  data=malloc(strlen(text)+2);
  strcpy(data, text);
  my_ipc4.data=data;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SEND_UTF8,&my_ipc4);
}

void OpmsgIDSend(int submsg, int opmsg_id)
{
   IPC_REQ my_ipc5=
  {
    my_ipc_name,
    my_ipc_name,
    NULL
  };
  my_ipc5.data=(void *)opmsg_id;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,submsg,&my_ipc5);
}

