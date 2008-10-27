#include "..\inc\swilib.h"
#include "..\inc\mplayer.h"
#include "language.h"
#include "sms_dat.h"
#include "popGui.h"
#include "main.h"
#include "edGui.h"
#include "adrList.h"
#include "CodeShow.h" 
#include "config_data.h"
#include "lgp_pic.h"
#include "NewDatReader.h"
//int sndVolume=5;
short PLAY_ID=0;
void Play(const char *fname)
{
  PLAYFILE_OPT _sfo1;
  WSHDR *sndPath,sndPathn;
  WSHDR *sndFName,sndFNamen;
  unsigned short sndPathb[128];
  unsigned short sndFNameb[128];
  char s[128];
  const char *p;
  if(!IsFileExist(fname))
    return;
  sndPath=CreateLocalWS(&sndPathn, sndPathb, 128);
  sndFName=CreateLocalWS(&sndFNamen, sndFNameb, 128);
  p=strrchr(fname,'\\')+1;
  str_2ws(sndFName,p,128);
  strncpy(s,fname,p-fname);
  s[p-fname]='\0';
  str_2ws(sndPath,s,128);
  zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
  _sfo1.repeat_num=1;
  _sfo1.time_between_play=0;
  _sfo1.play_first=0;
  _sfo1.volume=CFG_SOUND_VOL;//
#ifdef NEWSGOLD
  _sfo1.unk6=1;
  _sfo1.unk7=1;
  _sfo1.unk9=2;
  PLAY_ID=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
  _sfo1.unk4=0x80000000;
  _sfo1.unk5=1;
  PLAY_ID=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
  _sfo1.unk5=1;
  PLAY_ID=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
}

#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);

const int popup_softkeys[]={0, 1, 2};
const SOFTKEY_DESC popup_sk[]=
{
  {0x0018,0x0000,(int)STR_VIEW},
  {0x0001,0x0000,(int)LGP_BACK},
  {0x003D,0x0000,LGP_DOIT_PIC}
};
const SOFTKEYSTAB popup_skt={popup_sk, 0};

#ifdef ELKA
const int popup_icons[]={0x52C, 0};
#else
const int popup_icons[]={0x558, 0};
#endif

#define TIME_SECOND 216
/*
typedef struct
{
	void *dlg_csm;
	GBSTMR tmr;
}POP_UP;
*/

GBSTMR poptmr;
int popup_onkey(void *data, GUI_MSG *msg)
{
	//POP_UP *pu=(POP_UP *)GetPopupUserPointer(data);
	if((msg->keys==0x18)||(msg->keys==0x3D))
	{
		//DLG_CSM *dlg_csm=(DLG_CSM *)(pu->dlg_csm);
		DLG_CSM *dlg_csm=GetPopupUserPointer(data);
		if(dlg_csm)
		{
			if(!(dlg_csm->gui_id=viewTheLastNew(dlg_csm)))
				dlg_csm->gui_id=CreateMainMenu(dlg_csm);
		}
		return 1;
	}
	if(msg->keys==0x1)
		return 1;
	if(msg->gbsmsg->msg==KEY_DOWN)
	{	 
		if(!IsUnlocked())
			TempLightOn(3, 0x7FFF);

		if(PLAY_ID) PlayMelody_StopPlayback(PLAY_ID);
		PLAY_ID=0;
		if(CFG_ENA_SOUND && IsPlayerOn() && !GetPlayStatus()) MPlayer_Start();
		SetVibration(0);
		//if(IsTimerProc(&(pu->tmr)))
		//{
		//	GBS_StopTimer(&(pu->tmr));
		//}
	}
	return 0;
}
void StopVibra()
{
	GeneralFuncF1(0x1);
//	SetVibration(0);
//	if(PLAY_ID) PlayMelody_StopPlayback(PLAY_ID);
//	PLAY_ID=0;
//	if(GetPlayStatus()==1) MPlayer_Start();
	GBS_SendMessage(MMI_CEPID,KEY_DOWN,0x63); //update
}
void popup_ghook(void *data, int cmd)
{
	//POP_UP *pu=(POP_UP *)GetPopupUserPointer(data);
	if(cmd==2) //Create
	{
		//if(!IsUnlocked())
		TempLightOn(3, 0x7FFF);
		if(CFG_NOTIFY_TIME && !IsCalling())
		{
			if(CFG_ENA_SOUND && IsFileExist(CFG_SOUND_PATH))
			{
				if(GetPlayStatus()) MPlayer_Stop();
				if(!PLAY_ID) Play(CFG_SOUND_PATH);
			}
			SetVibration(CFG_VIBRA_POWER);
			//GBS_StartTimerProc(&(pu->tmr), TIME_SECOND*CFG_NOTIFY_TIME, StopVibra);
			GBS_StartTimerProc(&poptmr, TIME_SECOND*CFG_NOTIFY_TIME, StopVibra);
		}
	}
	else if(cmd==3) //Close
	{
		if(PLAY_ID) PlayMelody_StopPlayback(PLAY_ID);
		PLAY_ID=0;
		if(CFG_ENA_SOUND && IsPlayerOn() && !GetPlayStatus()) MPlayer_Start();
		SetVibration(0);
		//GBS_DelTimer(&(pu->tmr));
		GBS_DelTimer(&poptmr);
		//mfree(pu);
	}
}

const POPUP_DESC popup=
{
  8,
  popup_onkey,
  popup_ghook,
  NULL,
  popup_softkeys,
  &popup_skt,
  0x1,
  LGP_NULL,
  popup_icons,
  0,
  FONT_MEDIUM,
  100,
  101,
  0
};
int ShowMSG_report(SMS_DATA *sd);
int StartIncomingWin(void *dlg_csm)
{
	//SMS_DATA *sd=getLastTheLast(TYPE_IN_N);
	SMS_DATA *sd;
	WSHDR *ws;
	WSHDR wsloc, *wn;
	WSHDR csloc, *cs;
	unsigned short csb[30];
	unsigned short wsb[150];
	//POP_UP *pu;
	extern unsigned int DlgCsmIDs[]; //main.c
	extern int IsNoDlg(unsigned int *id_pool); //main.c
	if(IsNoDlg(DlgCsmIDs))
		sd=GetTheLastNew(1);
	else
	{
	  readAllSMS();
	  sd=GetTheLastNew(0);
	}
	if(!sd) return 0;
	if(sd->msg_type==ISREPORT) return (ShowMSG_report(sd));
	if(IsTimerProc(&poptmr)) return 0;
	ws=AllocWS(150);
	//pu=malloc(sizeof(POP_UP));
	//zeromem(pu, sizeof(POP_UP));
	//pu->dlg_csm=dlg_csm;
	wn=CreateLocalWS(&wsloc,wsb,150);
	cs=CreateLocalWS(&csloc,csb,30);
	if(sd)
	{
	#ifdef NO_CS 
		if(findNameByNum(wn, sd->Number))
			wsprintf(ws, "%t\n%t:\n%w", STR_NEW_MSG, STR_FROM, wn);
		else
			wsprintf(ws, "%t\n%t:\n%s", STR_NEW_MSG, STR_FROM, sd->Number);
	#else
		char num[32];
		int is_fetion=0;
		if(!strncmp(num_fetion, sd->Number, 5)) is_fetion=1;
		strcpy(num, sd->Number);
		GetProvAndCity(cs->wsbody, num);
		if(findNameByNum(wn, is_fetion?(sd->Number+5):sd->Number))
		{
			if(is_fetion) wsprintf(ws, "%t\n%t:\n%w(%t)\n%w", STR_NEW_MSG, STR_FROM, wn, STR_FETION, cs);
			else wsprintf(ws, "%t\n%t:\n%w\n%w", STR_NEW_MSG, STR_FROM, wn, cs);
		}
		else
			wsprintf(ws, "%t\n%t:\n%s\n%w", STR_NEW_MSG, STR_FROM, sd->Number, cs);
	#endif
	}
//	else
//	{
//		wsprintf(ws, PERCENT_T, STR_NEW_MSG);
//	}
	return (CreatePopupGUI_ws(1, dlg_csm, &popup, ws));
}

const SOFTKEY_DESC msg_popup_sk[]=
{
  {0x0018,0x0000,(int)LGP_OK},
  {0x0001,0x0000,(int)LGP_NONE_PIC},
  {0x003D,0x0000,LGP_DOIT_PIC}
};
const SOFTKEYSTAB msg_popup_skt={msg_popup_sk, 0};

int msg_popup_onkey(void *data, GUI_MSG *msg)
{
	if((msg->keys==0x18)||(msg->keys==0x3D))
		return 1;
	return 0;
}
const POPUP_DESC msg_popup=
{
  0,
  msg_popup_onkey,
  NULL,
  NULL,
  popup_softkeys,
  &msg_popup_skt,
  0x1,
  LGP_NULL,
  NULL,
  0,
  FONT_MEDIUM,
  100,
  101,
  0x7D0 //flag2 ? auto off time?
};

int ShowMSG_ws(int flag, WSHDR *msg)
{
	return (CreatePopupGUI_ws(flag, 0, &msg_popup, msg));
}


int offproc_popup_onkey(void *data, GUI_MSG *msg)
{
	if((msg->keys==0x18)||(msg->keys==0x3D))
		return 1;
	return 0;
}
void offproc_popup_ghook(void *data, int cmd)
{
	if(cmd==3)
	{
		void *proc=GetPopupUserPointer(data);
		((void (*)(void))proc)();
	}
}
const POPUP_DESC offproc_popup=
{
  0,
  offproc_popup_onkey,
  offproc_popup_ghook,
  NULL,
  popup_softkeys,
  &msg_popup_skt,
  0x1,
  LGP_NULL,
  popup_icons,
  0,
  FONT_MEDIUM,
  100,
  101,
  0x7D0 //flag2 ? auto off time?
};

int ShowMSG_offproc(int flag, const char *msg, void proc(void))
{
	return (CreatePopupGUI(flag, (void *)proc, &offproc_popup, (int)msg));
}

const POPUP_DESC msg_noff_popup=
{
  0,
  msg_popup_onkey,
  NULL,
  NULL,
  popup_softkeys,
  &msg_popup_skt,
  0x1,
  LGP_NULL,
  NULL,
  0,
  FONT_MEDIUM,
  100,
  101,
  0 //flag2 ? auto off time?
};

int ShowMSG_noff(int flag, const char *msg)
{
	return (CreatePopupGUI(flag, 0, &msg_noff_popup, (int)msg));
}

void report_popup_ghook(void *data, int cmd)
{
	if(cmd==3)
	{
		SMS_DATA *sd=GetPopupUserPointer(data);
		if(CFG_ENA_AUTO_DEL_RP && IsSdInList(sd) && deleteDat(sd, 0))
			delSDList(sd);
	}
}

const POPUP_DESC msg_report=
{
  0,
  msg_popup_onkey,
  report_popup_ghook,
  NULL,
  popup_softkeys,
  &msg_popup_skt,
  0x1,
  LGP_NULL,
  NULL,
  0,
  FONT_MEDIUM,
  100,
  101,
  0x7D0 //flag2 ? auto off time?
};

int ShowMSG_report(SMS_DATA *sd)
{
	WSHDR wsloc, *wn;
	WSHDR csloc, *cs;
	unsigned short csb[30];
	unsigned short wsb[150];
	WSHDR *ws=AllocWS(256);
	wn=CreateLocalWS(&wsloc,wsb,150);
	cs=CreateLocalWS(&csloc,csb,30);
	#ifdef NO_CS 
		if(findNameByNum(wn, sd->Number))
			wsprintf(ws, "%w\n%t:\n%w", sd->SMS_TEXT, STR_FROM, wn);
		else
			wsprintf(ws, "%w\n%t:\n%s", sd->SMS_TEXT, STR_FROM, sd->Number);
	#else
		char num[32];
		int is_fetion=0;
		if(!strncmp(num_fetion, sd->Number, 5)) is_fetion=1;
		strcpy(num, sd->Number);
		GetProvAndCity(cs->wsbody, num);
		if(findNameByNum(wn, is_fetion?(sd->Number+5):sd->Number))
		{
			if(is_fetion) wsprintf(ws, "%w\n%t:\n%w(%t)\n%w", sd->SMS_TEXT, STR_FROM, wn, STR_FETION, cs);
			else wsprintf(ws, "%w\n%t:\n%w\n%w", sd->SMS_TEXT, STR_FROM, wn, cs);
		}
		else
			wsprintf(ws, "%w\n%t:\n%s\n%w", sd->SMS_TEXT, STR_FROM, sd->Number, cs);
	#endif
	return (CreatePopupGUI_ws(0, sd, &msg_report, ws));
}
