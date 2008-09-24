#include "..\inc\swilib.h"
#include "MySMSYS_ipc.h"
#include "language.h"
#include "main.h"
#include "guiIdMan.h"
/*
由于在菜单里面没有办法直接关闭edgui,只好暂时用这个来记录GUI_ID
*/
//SGUI_ID *gstop=0;

void pushGS(void *dlg_csm, unsigned int id)
{
	SGUI_ID *gs=malloc(sizeof(SGUI_ID));
	zeromem(gs, sizeof(SGUI_ID));
	gs->id=id;
//	LockSched();
	if(!((DLG_CSM *)dlg_csm)->gstop)
	{
		((DLG_CSM *)dlg_csm)->gstop=gs;
	}
	else
	{
		SGUI_ID *gst=(SGUI_ID *)(((DLG_CSM *)dlg_csm)->gstop);
		((DLG_CSM *)dlg_csm)->gstop=gs;
		((SGUI_ID *)(((DLG_CSM *)dlg_csm)->gstop))->next=gst;
	}
//	UnlockSched();
}

void popGS(void *dlg_csm)
{
	SGUI_ID *gs;
//	LockSched();
	if(((DLG_CSM *)dlg_csm)->gstop)
	{
		gs=(SGUI_ID *)((DLG_CSM *)dlg_csm)->gstop;
		((DLG_CSM *)dlg_csm)->gstop=((SGUI_ID *)(((DLG_CSM *)dlg_csm)->gstop))->next;
		mfree(gs);
	}
//	UnlockSched();
}

void freeAllGS(void *dlg_csm)
{
	SGUI_ID *gst;
	SGUI_ID *gs;
//	LockSched();
	gs=(SGUI_ID *)((DLG_CSM *)dlg_csm)->gstop;
	((DLG_CSM *)dlg_csm)->gstop=0;
	while(gs)
	{
		gst=gs;
		gs=gs->next;
		mfree(gst);
	}
//	UnlockSched();
}


