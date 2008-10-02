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
	DLG_CSM *dg=(DLG_CSM *)dlg_csm;
	SGUI_ID *gstop=(SGUI_ID *)(dg->gstop);
	zeromem(gs, sizeof(SGUI_ID));
	gs->id=id;
	dg->gstop=gs;
	gs->next=gstop;
}

void popGS(void *dlg_csm)
{
	DLG_CSM *dg=(DLG_CSM *)dlg_csm;
	SGUI_ID *gs=(SGUI_ID *)(dg->gstop);
	if(gs)
	{
		dg->gstop=gs->next;
		mfree(gs);
	}
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


