#include "../inc/swilib.h"
#include "lang.h"
#include "conf_loader.h"



typedef struct
{
	CSM_RAM csm;
}MAIN_CSM;

extern kill_data(void *p, void (*func_p)(void *));
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

extern const unsigned int pos_x;
extern const unsigned int pos_y;
extern const unsigned int length;
extern const unsigned int font;
extern const char color[4];
extern const char frmcolor[4];
extern const unsigned int txt_attr;
extern const int ENA_LOCK;
extern const char frmmain_color[4];
extern const char frmbg_color[4];
extern const unsigned int xrnd;
extern const unsigned int yrnd;
extern const int style;
extern const unsigned int speed;
extern const unsigned int wait_time;
extern const char CSMADR[];
extern const int show_gp;
extern const int show_ext;

WSHDR *ews;
//WSHDR *ews_2;
WSHDR *temp;
int drawname_needed=0;
int scroll_pos=0;
GBSTMR mytmr;
int is_tmr=0;
//int is_drawname=0;
char utf8_name[128];
char name_temp[128];
int is_music_file=0;
int is_player_active=0;

const char percent_t[]="%t";

unsigned int playercsmid=0;
void *playercsmadr=NULL;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strncmp_nocase(const char *s1,const char *s2,unsigned int n)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))&&(--n)) if (!c) break;
  return(i);
}

#pragma inline
int strcmp_nocase(const char *s1, const char *s2)
{
	int i;
	int c;
	while(!(i=(c=toupper(*s1++))-toupper(*s2++)))
	{
		if(!c)
			break;
	}
	return i;
}
//ad
//amr,imy,m4a,mfi,mid,mp3,srt,wav,

//vd
//mp4,3gp

//gf
//bmp,bmx,gif,jpeg,jpg,png,svg,wbmp

void getname(void)
{
	char *p=strrchr(name_temp, '.');
	//if(show_gp)
	//	if(show_ext)
	//		goto show_ext;
	if(p)
	{
		if(!strncmp_nocase(p, ".mp3", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".mp3");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".aac", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".aac");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".m4a", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".m4a");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".wav", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".wav");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".amr", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".amr");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".mid", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".mid");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".3gp", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".3gp");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".mp4", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".mp4");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".imy", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".imy");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".srt", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".srt");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".bmp", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".jpg", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".gif", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".png", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".jpeg", 5))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".bmx", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".svg", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".wbmp", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
	}
	else
		utf8_name[0]=0;
	
	is_music_file=0;
//gf
//bmp,bmx,gif,jpeg,jpg,png,svg,wbmp
if_show_ext:
	if(!show_ext)
		goto not_show_ext;
	strcpy(utf8_name, name_temp);
	goto end;
	
not_show_ext:
	strncpy(utf8_name, name_temp, p-name_temp);
	utf8_name[p-name_temp]=0;
	
end:
	str_2ws(ews, utf8_name, 128);
}

void RereadSettings(void)
{
	InitConfig();
	playercsmadr=(void *)strtoul(CSMADR,NULL,16);
}

int getMaxChars(unsigned short *wsbody, int len, int font) // 获取可显示的最大字符数 Unicode
{
	int ii,width=0;
	for(ii=0;ii<len;ii++)
	{
		width+=GetSymbolWidth(wsbody[ii], font);
		if (width>=length-4) break;
	}
	return ii;
}

/*
int wstrcmp(WSHDR *ws1, WSHDR *ws2)
{
	int i=0,c,t1,t2;
	while(!(c=(t1=(ws1->wsbody[i]))-(t2=(ws2->wsbody[i]))))
	{
		if(!t1||!t2)
			break;
	}
	return c;
}*/

void drawname_proc(void)
{
	if(drawname_needed)
	{
		/*if(!memcmp(ews, ews_2, sizeof(ews)))
		{
			memcpy(ews_2, ews,sizeof(ews));
			scroll_pos=0;
		}*/
		//DrawString(ews,pos_x+2,pos_y+2,pos_x+length-2,pos_y+GetFontYSIZE(font)+2,font,txt_attr,color,frmcolor);
		if((Get_WS_width(ews, font)>=(length-4))&&speed)
		{
			int sc=getMaxChars(&ews->wsbody[scroll_pos+1], ews->wsbody[0]-scroll_pos, font);
			temp->wsbody[0]=sc;
			for(int ii=1;ii<sc+1;ii++)
				temp->wsbody[ii]=ews->wsbody[ii+scroll_pos];
			DrawString(temp,pos_x+2,pos_y+2,pos_x+length-2,pos_y+GetFontYSIZE(font)+2,font,txt_attr,color,frmcolor);
			scroll_pos++;
			int rest_len=0;
			int i;
			for (i=scroll_pos+1;i<ews->wsbody[0];i++)
				rest_len+=GetSymbolWidth(ews->wsbody[i], font);
			if (rest_len<=(length-4-0x40))
				scroll_pos = 0;
			if(scroll_pos==1)
				GBS_StartTimerProc(&mytmr,wait_time,drawname_proc);
			else
				GBS_StartTimerProc(&mytmr,speed,drawname_proc);
			is_tmr=1;
		}
		else
		{
			DrawString(ews,pos_x+2,pos_y+2,pos_x+length-2,pos_y+GetFontYSIZE(font)+2,font,txt_attr,color,frmcolor);
			is_tmr=0;
		}
	}
	else
	{
		is_tmr=0;
		//is_drawname=0;
	}
}


int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	if(msg->msg==MSG_RECONFIGURE_REQ)
	{
		extern const char *successed_config_filename;
		if(strcmp_nocase(successed_config_filename, (char *)msg->data0)==0)
		{
			ShowMSG(1, (int)LGP_UPDATE_CONFIG);
			//InitConfig();
			RereadSettings();
			getname();
		}
	}
	
	if (playercsmid)
	{
		CSM_RAM *csmp=FindCSMbyID(playercsmid);
		if(csmp)
		{
			WSHDR *fn=((WSHDR **)csmp)[0x2C/4];
			if (!fn) goto L_ACTIVE;
			if (!fn->wsbody) goto L_ACTIVE;
			if (fn->wsbody[0])
			{
				ws_2str(fn, name_temp, 128);
				getname();
				//wstrcpy(ews,fn);
			}
			else
			{
			L_ACTIVE:
				wsprintf(ews, percent_t, "出错!");
			}
			is_player_active=1;
		}
		else
		{
			playercsmid=0;
			is_player_active=0;
			//wsprintf(ws1,"Player not active");
		}
	}
	else
	{
		CSM_RAM *p=CSM_root()->csm_q->csm.first;
		while(p)
		{
			if (p->constr==playercsmadr) break;
			p=p->next;
		}
		if(p)
		{
			playercsmid=p->id;
		}
		else
			is_player_active=0;
	}	
	
	if(is_player_active&&(ENA_LOCK||IsUnlocked()))
	{
		//getname();
#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
		CSM_RAM *icsm;
		icsm=FindCSMbyID(CSM_root()->idle_id);
		if(icsm&&is_music_file)
		//if(icsm)
		{
			if(IsGuiOnTop(idlegui_id(icsm)))
			{
				GUI *igui=GetTopGUI();
				if(igui)
				{
#ifdef ELKA
					void *canvasdata = BuildCanvas();
					{
#else
					void *idata = GetDataOfItemByID(igui, 2);
					if (idata)
					{
						void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
						//str_2ws(ews, utf8_name, 128);
						DrawCanvas(canvasdata,pos_x,pos_y,pos_x+length,pos_y+GetFontYSIZE(font)+4,1);
						DrawRoundedFrame(pos_x,pos_y,pos_x+length,pos_y+GetFontYSIZE(font)+4, xrnd, yrnd, style, frmmain_color, frmbg_color);
						drawname_needed=1;
						//if(!is_drawname)
						//{
						drawname_proc();
						//	is_drawname=0;
						//}
						//DrawString(ews,pos_x+2,pos_y+2,pos_x+length-2,pos_y+GetFontYSIZE(font)+2,font,txt_attr,color,frmcolor);
					}
#ifndef ELKA
					else
						drawname_needed=0;
#endif
				}
				else
					drawname_needed=0;
			}
			else
				drawname_needed=0;
		}
		else
			drawname_needed=0;
	}
	else
		drawname_needed=0;
	return 1;
}

static void maincsm_oncreate(CSM_RAM *data)
{
	ews=AllocWS(128);
	temp=AllocWS(128);
	//ews_2=AllocWS(128);
}


static void Killer(void)
{
	extern void *ELF_BEGIN;
	FreeWS(ews);
	FreeWS(temp);
	//FreeWS(ews_2);
	if(is_tmr) GBS_DelTimer(&mytmr);
	kill_data(&ELF_BEGIN, (void (*)(void *))mfree_adr());
}


static void maincsm_onclose(CSM_RAM *csm)
{
	SUBPROC((void *)Killer);
}


const int minius11=-11;
static unsigned short maincsm_name_body[140];
static const struct
{
	CSM_DESC maincsm;
	WSHDR maincsm_name;
}MAINCSM=
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
		&minius11
	},
	{
		maincsm_name_body,
		NAMECSM_MAGIC1,
		NAMECSM_MAGIC2,
		0,
		139
	}
};


static void UpdateCSMName(void)
{
	wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "%t", ELF_NAME);
}	


int main(void)
{
	CSM_RAM *save_cmpc;
	char dummy[sizeof(MAIN_CSM)];
	//InitConfig();
	RereadSettings();
	UpdateCSMName();
	LockSched();
	save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
	CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
	CreateCSM(&MAINCSM.maincsm, dummy,0);
	CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
	UnlockSched();
	return 0;
}

