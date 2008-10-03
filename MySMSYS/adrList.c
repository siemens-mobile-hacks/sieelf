#include "../inc/swilib.h"
#include "sms_dat.h"
#include "adrList.h"
#include "rect_patcher.h"
#include "language.h"
#include "edGui.h"
#include "createMenu.h"
#include "numList.h"
#include "config_data.h"

//char *s_ab_main="0:\\System\\apo\\addr\\main";
//#ifdef NEWSGOLD
//char *s_ab_entry="0:\\System\\apo\\addr\\data\\%02d\\%02d\\%02d";
//#else
//char *s_ab_entry="0:\\System\\apo\\addr\\%02x\\%02x";
//#endif

#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);

volatile CLIST *cltop=0;
int cl_n;

int wstrcmp_nocase(WSHDR *ws1, WSHDR *ws2)
{
  int l1=wslen(ws1);
  int l2=wslen(ws2);
  int pos=1;
  int cs, ds;
  while((pos<=l1)&&(pos<=l2))
  {
    cs=ws1->wsbody[pos];
    if(cs>='A'&&cs<='Z')
    	cs+='a'-'A';
    ds=ws2->wsbody[pos];
    if(ds>='A'&&ds<='Z')
    	ds+='a'-'A';
    cs-=ds;
    if (cs) return cs;
    pos++;
  }
  return(l1-l2);
}

int wstrncmp_nocase(WSHDR *ws1, WSHDR *ws2, int n)
{
  int l1=wslen(ws1);
  int l2=wslen(ws2);
  int pos=1;
  int cs, ds;
  n++;
  while((pos<=l1)&&(pos<=l2)&&(pos<=n))
  {
    cs=ws1->wsbody[pos];
    if(cs>='A'&&cs<='Z')
    	cs+='a'-'A';
    ds=ws2->wsbody[pos];
    if(ds>='A'&&ds<='Z')
    	ds+='a'-'A';
    cs-=ds;
    if (cs) return cs;
    pos++;
  }
  return 0;
}

void FreeCLIST(void)
{
	LockSched();
	CLIST *cl0=(CLIST*)cltop;
	cltop=0;
	UnlockSched();
	while(cl0)
	{
		CLIST *p;
		if(cl0->name) FreeWS(cl0->name);
		if(cl0->nm[0]) FreeWS(cl0->nm[0]);
		if(cl0->nm[1]) FreeWS(cl0->nm[1]);
		if(cl0->nm[2]) FreeWS(cl0->nm[2]);
		for(int i=0;i<NUMBERS_MAX;i++) 
		{
			if(cl0->num[i])
				FreeWS(cl0->num[i]);
		}
		p=cl0;
		cl0=(CLIST*)(cl0->next);
		mfree(p);
	}
}

void ConstructList(void)
{
	int fin;
	unsigned int ul;
	char recname[128];
	char s_ab_main[128];
	char s_ab_entry[128];
	
	AB_UNPRES ur;
	void *buffer;

#pragma pack(1)
	struct {
#ifdef NEWSGOLD
		long dummy1;
		short dummy2;
		char bitmap[MAX_RECORDS/8];
#else
		long dummy1;
		char bitmap[MAX_RECORDS/8];
#endif
	} ABmain;
#pragma pack()

	unsigned int rec=0;
	int fsz;
	int x, xl;
	CLIST contact;

	FreeCLIST();
	cl_n=0;
	strcpy(s_ab_main, CFG_SYSTEM_FOLDER);
	
	if((xl=strlen(s_ab_main))>0)
		x=s_ab_main[xl-1];
	if((x!='\\')&&(x!='/'))
		strcat(s_ab_main, "\\");
	strcat(s_ab_main, "apo\\addr\\main");
	
	strcpy(s_ab_entry, CFG_SYSTEM_FOLDER);
	if((xl=strlen(s_ab_entry))>0)
		x=s_ab_entry[xl-1];
	if((x!='\\')&&(x!='/'))
		strcat(s_ab_entry, "\\");
#ifdef NEWSGOLD
	strcat(s_ab_entry, "apo\\addr\\data\\%02d\\%02d\\%02d");
#else
	strcat(s_ab_entry, "apo\\addr\\%02x\\%02x");
#endif
	zeromem(&contact,sizeof(contact));
	if ((buffer=malloc(65536)))
	{
		zeromem(&ABmain,sizeof(ABmain));
		if ((fin=fopen(s_ab_main, A_ReadOnly+A_BIN, P_READ, &ul))!=-1)
		{
#ifdef ELKA
			if (fread(fin,&ABmain,sizeof(ABmain),&ul)>=194)
#else
			if (fread(fin,&ABmain,sizeof(ABmain),&ul)==sizeof(ABmain))
#endif
			{
				fclose(fin,&ul);
				do
				{
#ifdef NEWSGOLD
					if (ABmain.bitmap[rec>>3]&(0x80>>(rec&7)))
#else
					if (ABmain.bitmap[rec>>3]&(1<<(rec&7)))
#endif
					{
#ifdef NEWSGOLD
						unsigned int rl1;
						unsigned int rl2;
						unsigned int rl3;
						rl1=rec/LEVEL1_RN;
						rl2=(rec%LEVEL1_RN)/LEVEL2_RN;
						rl3=rec%LEVEL2_RN;
						snprintf(recname, 128, s_ab_entry, rl1, rl2, rl3);
#else
						unsigned int rl1=rec/LEVEL1_RN;
						unsigned int r12=rec%LEVEL1_RN;
						snprintf(recname, 128, s_ab_entry, rl1, r12);
#endif
						if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
						{
							zeromem(&ur,sizeof(AB_UNPRES));
							fsz=lseek(fin,0,S_END,&ul,&ul);
							lseek(fin,0,S_SET,&ul,&ul);
							fread(fin,buffer,fsz,&ul);
							fclose(fin,&ul);
#ifdef NEWSGOLD
							UnpackABentry(&ur,((char *)buffer+8),fsz,0x28);
#else
							UnpackABentry(&ur,((char *)buffer+4),fsz-4,0x28);
#endif
							int i=0;
							zeromem(&contact,sizeof(contact));
							while(i<ur.number_of_records)
							{
								AB_UNPRES_ITEM *r=ur.record_list+i;
								if (r->no_data!=1)
								{
									switch(GetTypeOfAB_UNPRES_ITEM(r->item_type))
									{
										case 0x05:
#ifdef NEWSGOLD
											if (
												r->item_type==LAST_NAME||
												r->item_type==FIRST_NAME||
												r->item_type==DISPLAY_NAME
											   )
#else
											if (
												r->item_type==LAST_NAME||
												r->item_type==FIRST_NAME||
												r->item_type==COMPANY_NAME
											   )
#endif
											{
												if (r->data)
												{
													if (!contact.name)
													{
														cl_n++;
														wstrcpy(contact.nm[0]=AllocWS(150),(WSHDR *)(r->data));
														wstrcpy(contact.name=AllocWS(150),(WSHDR *)(r->data));
														contact.next = (void*)1;
													}
													else if (!contact.nm[1])
													{
														wstrcpy(contact.nm[1]=AllocWS(150),(WSHDR *)(r->data));
														wsAppendChar(contact.name,',');
														wsAppendChar(contact.name,' ');
														wstrcat(contact.name, (WSHDR*)(r->data));
														contact.next = (void*)1;
													}
													else
													{
														wstrcpy(contact.nm[2]=AllocWS(150),(WSHDR *)(r->data));
														wsAppendChar(contact.name,',');
														wsAppendChar(contact.name,' ');
														wstrcat(contact.name, (WSHDR*)(r->data));
														contact.next = (void*)1;
													}
												}
											}
											break;
										case 0x01:
										{
											PKT_NUM *p=(PKT_NUM*)r->data;
											unsigned int n=r->item_type;
											int j;
											unsigned int c;
											WSHDR *ws0;
#ifdef NEWSGOLD
											if (n!=106) n-=0x62;
											else n=4;
											if (n<5)
#else
											switch(r->item_type)
											{
												case PHONE_NUMBER:
													n=0;    break;
												case PHONE_OFFICE:
													n=1;    break;
												case PHONE_MOBILE:
													n=2;    break;
												case PHONE_FAX:
													n=3;    break;
												case PHONE_FAX2:
													n=4;    break;
												default:
													continue;
											}
#endif
											{
												if (p)
												{
													unsigned int c1;
													int m;
													ws0=contact.num[n]=AllocWS(50);
													j=0;
													m=0;
													if (p->format==0x91)
														wsAppendChar(ws0,'+');
													while(j<p->data_size)
													{
														if (m&1) {c1=c>>4; j++;}
														else c1=(c=p->data[j])&0x0F;
														if (c1==0x0F) break;

														if (c1==0xA) c1='*';
														else if (c1==0xB) c1='#';
														else if (c1==0xC) c1='+';
														else if (c1==0xD) c1='?';
														else c1+='0';
														wsAppendChar(ws0,c1);
														m++;
													}
													contact.next = (void*)1;
												}
											}
											break;
										}
									}
								}
								i++;
							}
							if (!contact.next)
							{
								if(contact.name) FreeWS(contact.name);
								if(contact.nm[0]) FreeWS(contact.nm[0]);
								if(contact.nm[1]) FreeWS(contact.nm[1]);
								if(contact.nm[2]) FreeWS(contact.nm[2]);
								for(int i=0;i<NUMBERS_MAX;i++)
								{
									if(contact.num[i])
										FreeWS(contact.num[i]);
								}
							}
							FreeUnpackABentry(&ur,mfree_adr());
							/**/ //排序加入链表
							LockSched();
							if (contact.next)
							{
								int n=0;
								CLIST *p=malloc(sizeof(contact));
								CLIST *t;
								CLIST *b=(CLIST *)(&cltop);
								contact.next=0;
								memcpy(p,&contact,sizeof(contact));
								for(;;)
								{
									if (t=b->next)
									{
										if (wstrcmp_nocase(contact.name,t->name)<0)
										{
											p->next=t;
											b->next=p;
											break;
										}
										b=t;
										n++;
									}
									else
									{
										b->next=p;
										break;
									}
								}
							}
							UnlockSched();
						}
					}
					rec++;
				}
				while(rec<MAX_RECORDS);
			}
			else
			{
				fclose(fin,&ul);
			}
		}
		  mfree(buffer);
	}
	if (contact.next)
	{
		if(contact.name) FreeWS(contact.name);
		if(contact.nm[0]) FreeWS(contact.nm[0]);
		if(contact.nm[1]) FreeWS(contact.nm[1]);
		if(contact.nm[2]) FreeWS(contact.nm[2]);
		for(int i=0;i<NUMBERS_MAX;i++) 
		{
			if(contact.num[i])
				FreeWS(contact.num[i]);
		}
	}
}


CLIST *GetClistItem(int n)
{
	int i=0;
	CLIST *cl0=(CLIST *)cltop;
	while(cl0)
	{
		if(i==n)
			return cl0;
		cl0=cl0->next;
		i++;
	}
	return 0;
}

int SearchInCList(WSHDR *searchstr)
{
	int i=0;
	CLIST *cl=(CLIST *)cltop;
	while(cl)
	{
		if(cl->name)
			if(!wstrncmp_nocase(cl->name, searchstr, wslen(searchstr)))
				return i;
		cl=cl->next;
		i++;
	}
	return -1;
}

int findNameByNum(WSHDR *name_to, char *num)
{
	CLIST *cl=(CLIST *)cltop;
	int i, la, lb, ld;
	char bn[50];
	char *p1;
	char *pp;
	if((!num)||(!name_to)||(strlen(num)<=3))
		return 0;
	while(cl)
	{
		i=0;
		for(;i<NUMBERS_MAX;i++)
		{
			if(cl->num[i])
			{
				//号码查找比较,根据短的比较长的后面部分
				ws_2str(cl->num[i], bn, 49);
				p1=bn;
				if(*p1=='+')
					p1++;
				pp=num;
				if(*pp=='+')
					pp++;
				la=strlen(pp);
				lb=strlen(p1);
				if(la>lb)
				{
					ld=lb;
					pp+=la-lb;
				}
				else
				{
					ld=la;
					p1+=lb-la;
				}
				if(!strncmp(pp, p1, ld))
				{
					if(cl->name)
					{
						wstrcpy(name_to, cl->name);
						return 1;
					}
				}
			}
		}
		cl=cl->next;
	}
	return 0;
}

int getNumCount(CLIST *cl)
{
	int i=0;
	int j=0;
	for(;j<NUMBERS_MAX;j++)
	{
		if(cl->num[j])
			i++;
	}
	return i;
}

WSHDR *getNumFromCL(CLIST *cl, int n)
{
	int i=0, j=0;
	for(;j<NUMBERS_MAX;j++)
	{
		if(cl->num[j]!=0)
		{
			if(i==n)
				return cl->num[j];
			else
				i++;
		}
	}
	return 0;
}

WSHDR *getPrefNumFromCL(CLIST *cl)
{
	int i=NUMBERS_MAX-1;
	for(;i>=0;i--)
	{
		if(cl->num[i]!=0)
			return cl->num[i];
	}
	return 0;
}
//---------------------------------------------
//menu.
//---------------------------------------------
const int adrmenusoftkeys[]={0,1,2};
const SOFTKEY_DESC adrmenu_sk[]=
{
  {0x0018,0x0000,(int)LGP_OK},
  {0x0001,0x0000,(int)LGP_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB adrmenu_skt=
{
  adrmenu_sk,0
};
char numhdr[50];
HEADER_DESC nummenuhdr={0,0,0,0,NULL,(int)numhdr,LGP_NULL};

//#define TYPE_SET 0
//#define TYPE_INSERT 1

typedef struct
{
	void *ed_gui;
	CLIST *cl;
}NUM_MENU_UP;

void wsInsert(WSHDR *ws, WSHDR *txt, int pos, int max) //start form 0;
{
	unsigned short *st;
	int cplen;	
	if((!ws)||(!txt)||(!wstrlen(txt)))
		return;
	if(pos>(ws->wsbody[0]))
		return;
	if((pos+(txt->wsbody[0]))>=max)
	{
		CutWSTR(ws, pos);
		wstrncat(ws, txt, max-pos); 
		return;
	}
	if(ws->wsbody[0]+txt->wsbody[0] >= max)
		cplen=max-(pos+txt->wsbody[0]);
	else
		cplen=ws->wsbody[0]-pos;
	st=malloc(cplen*sizeof(unsigned short));
	memcpy(st, ws->wsbody+pos+1, cplen*sizeof(unsigned short));
	memcpy(ws->wsbody+pos+1, txt->wsbody+1, (txt->wsbody[0])*sizeof(unsigned short));
	memcpy(ws->wsbody+1+pos+(txt->wsbody[0]), st, cplen*sizeof(unsigned short));
	ws->wsbody[0]=pos+(txt->wsbody[0])+cplen;
	mfree(st);
}

void InsertAsTxt(void *ed_gui, WSHDR *num)
{
	WSHDR csloc, *wcs;
	EDITCONTROL ec;
	int k=EDIT_GetCursorPos(ed_gui);
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	unsigned short csb[MAX_TEXT];
	int n=EDIT_GetFocus(ed_gui);
	if(n!=(uo->focus_n))
		return;
	if(k<=0)
		return;
	wcs=CreateLocalWS(&csloc,csb,MAX_TEXT);
	ExtractEditControl(ed_gui,n,&ec);
	wstrcpy(wcs, ec.pWS);
	wsInsert(wcs, num, k-1, MAX_TEXT);
	EDIT_SetTextToEditControl(ed_gui, n, wcs);
	EDIT_SetCursorPos(ed_gui, k+num->wsbody[0]);
}

void SetNumToED(void *ed_gui, WSHDR *num, WSHDR *name)
{
	//EDITCONTROL ec;
	NUM_LIST *nl;
	
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	int n=EDIT_GetFocus(ed_gui);
	if(n>(uo->focus_n-2))
		return;
	if(!(nl=GetNumListCur(uo, n)))
		return;
	//ExtractEditControl(ed_gui,n,&ec);
	ws_2str(num, nl->num, 49);
	wstrcpy(nl->name, name);
	EDIT_SetTextToEditControl(ed_gui, n, name);
}
/*
void InsertNumToED(void *ed_gui, WSHDR *num, WSHDR *name) //插入到列表光标后面
{
	EDITCONTROL ec;
	EDITC_OPTIONS ec_options;

	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	int n=EDIT_GetFocus(ed_gui);
	NUM_LIST *nl=malloc(sizeof(NUM_LIST));
	zeromem(nl, sizeof(NUM_LIST));
	nl->name=AllocWS(150);
	if((n>(uo->focus_n-2))||(!InsertToNumList(uo, nl, n))) //insert fail
	{
		FreeWS(nl->name);
		mfree(nl);
		return;
	}
	ws_2str(num, nl->num, 49);
	wstrcpy(nl->name, name);
	PrepareEditControl(&ec);
	PrepareEditCOptions(&ec_options);
	SetFontToEditCOptions(&ec_options,FONT_SMALL);
	CopyOptionsToEditControl(&ec,&ec_options);
	ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_DEFAULT_DIGIT+ECF_APPEND_EOL,name,150);
	EDIT_InsertEditControl(ed_gui, n+1, &ec);
	(uo->focus_n)++;
	EDIT_SetFocus(ed_gui, n+1);
}
*/
int nummenu_onkey(void *data, GUI_MSG *msg)
{
		
	if(!IsUnlocked())
		TempLightOn(3, 0x7FFF);

	if((msg->keys==0x18)||(msg->keys==0x3D))
	{
		NUM_MENU_UP *up=MenuGetUserPointer(data);
		WSHDR *num=getNumFromCL(up->cl, GetCurMenuItem(data));
		if(num)
		{
			USER_OP *uo=EDIT_GetUserPointer(up->ed_gui);
			#ifdef DEBUG
				{
					WSHDR *xws=AllocWS(150);
					wsprintf(xws, "%w|%s",up->cl->name, num);
					//if(uo->adr_type==TYPE_INSERT)
					//	InsertNumToED(up->ed_gui, num, xws);
					//else if(uo->adr_type==TYPE_TXT)
					if(uo->adr_type==TYPE_TXT)
					{
						InsertAsTxt(up->ed_gui, num);
					}
					else if(uo->adr_type==TYPE_SET)
					{
						SetNumToED(up->ed_gui, num, xws);
					}
					FreeWS(xws);
				}
			#else
				//if(uo->adr_type==TYPE_INSERT)
				//	InsertNumToED(up->ed_gui, num, up->cl->name);
				//else if(uo->adr_type==TYPE_TXT)
				if(uo->adr_type==TYPE_TXT)
				{
					InsertAsTxt(up->ed_gui, num);
				}
				else if(uo->adr_type==TYPE_SET)
				{
					SetNumToED(up->ed_gui, num, up->cl->name);
				}
			#endif
				return 1;
		}
	}
	if(msg->keys==0x1)
	{
		return 1;
	}
	return 0;
}
void nummenu_ghook(void *gui, int cmd)
{
	if(cmd==3)
	{
		NUM_MENU_UP *up=MenuGetUserPointer(gui);
		mfree(up);
	}
}
void nummenuitemhdl(void *data, int curitem, void *user_pointer)
{
	NUM_MENU_UP *up=(NUM_MENU_UP *)user_pointer;
	void *item=AllocMenuItem(data);
	WSHDR *ws=AllocMenuWS(data, 150);
	WSHDR *ws1=getNumFromCL(up->cl, curitem);
	if(ws1)
		wstrcpy(ws, ws1);
	else
		wsprintf(ws, PERCENT_T, LGP_ERR);
	SetMenuItemText(data, item, ws, curitem);
}
const MENU_DESC nummenu=
{
	8,nummenu_onkey,nummenu_ghook,NULL,
	adrmenusoftkeys,
	&adrmenu_skt,
	0x10,//
	nummenuitemhdl,
	NULL,//menuitems,
	NULL,//menuprocs,
	0
};

int CreateNumMenu(CLIST *cl, void *ed_gui, int n)
{
//	return 0;
	NUM_MENU_UP *up=malloc(sizeof(NUM_MENU_UP));
	up->ed_gui=ed_gui;
	up->cl=cl;
	patch_header(&nummenuhdr);
	if(cl->name)
#ifdef LANG_CN
		ws2gb(cl->name, numhdr, 49);
#else
		ws_2str(cl->name, numhdr, 49);
#endif 
	return (CreateMenu(0,0,&nummenu,&nummenuhdr,n-1,n,up,0));
}


HEADER_DESC adrmenuhdr={0,0,0,0,NULL,(int)LGP_ADRBK,LGP_NULL};

static int adrmenu_keyhook(void *data, GUI_MSG *msg)
{
	
	if(!IsUnlocked())
		TempLightOn(3, 0x7FFF);

	if((msg->keys==0x18)||(msg->keys==0x3D))
	{
		void *ed_gui=MenuGetUserPointer(data);
		CLIST *cl=GetClistItem(GetCurMenuItem(data));
		int n;
		if((cl!=0)&&((n=getNumCount(cl))!=0))
		{
			if(n>1)
				CreateNumMenu(cl, ed_gui, n);
			else
			{
				USER_OP *uo=EDIT_GetUserPointer(ed_gui);
				WSHDR *num=0;
				for(n=0;n<NUMBERS_MAX;n++)
				{
					if(cl->num[n])
					{
						num=cl->num[n];
						break;
					}
				}
				if(num)
				{
			#ifdef DEBUG
					{
						WSHDR *xws=AllocWS(150);
						wsprintf(xws, "%w|%s",cl->name, num);
						//if(uo->adr_type==TYPE_INSERT)
						//	InsertNumToED(ed_gui, num, xws);
						//else if(uo->adr_type==TYPE_TXT)
						if(uo->adr_type==TYPE_TXT)
						{
							InsertAsTxt(ed_gui, num);
						}
						else if(uo->adr_type==TYPE_SET)
						{
							SetNumToED(ed_gui, num, xws);
						}
						FreeWS(xws);
					}
			#else
					//if(uo->adr_type==TYPE_INSERT)
					//	InsertNumToED(ed_gui, num, cl->name);
					//else if(uo->adr_type==TYPE_TXT)
					if(uo->adr_type==TYPE_TXT)
					{
						InsertAsTxt(ed_gui, num);
					}
					else if(uo->adr_type==TYPE_SET)
					{
						SetNumToED(ed_gui, num, cl->name);
					}
			#endif
				}
			}
			return 1;
		}
	}
	if(msg->keys==0x1)
	{
		return 1;
	}
	return 0;
}

int adrMenuSearchProc(void *gui, WSHDR *searchstr)
{
	int n;
	if(wslen(searchstr)>0&&(n=SearchInCList(searchstr))>=0)
	{
		UpdateMenuCursorItem(gui, n);
	}
	return -1;
}

void adrmenu_ghook(void *gui, int cmd)
{
	if(cmd==1) //?
		SetMenuSearchCallBack(gui, adrMenuSearchProc);
}

static void adrmenuitemhdl(void *data, int curitem, void *user_pointer)
{
	void *item=AllocMLMenuItem(data);
	WSHDR *ws1=AllocMenuWS(data, 150);
	WSHDR *ws2=AllocMenuWS(data, 50);
	WSHDR *wn;
	CLIST *cl=GetClistItem(curitem);
	if(cl)
	{
		if(cl->name)
			wstrcpy(ws1, cl->name);
		else
			goto M_ERR;
		if((wn=getPrefNumFromCL(cl))!=0)
			wstrcpy(ws2, wn);
		else
			CutWSTR(ws2, 0);
	}
	else
	{
M_ERR:
		wsprintf(ws1, PERCENT_T, LGP_ERR);
		CutWSTR(ws2, 0);
	}
	SetMLMenuItemText(data, item, ws1, ws2, curitem);
}
static const ML_MENU_DESC adrmenu=
{
	8,adrmenu_keyhook,adrmenu_ghook,NULL,
	adrmenusoftkeys,
	&adrmenu_skt,
	0x10010,//Right align+Enable search
	adrmenuitemhdl,
	NULL,//menuitems,
	NULL,//menuprocs,
	0,
	1
};


int CreateAdrMenu(void *user_pointer)
{
	patch_header(&adrmenuhdr);
	return (CreateMLMenu(&adrmenu, &adrmenuhdr, 0, cl_n, user_pointer));
}
