//A8ED5139 char *RAMPlayingFilename;

//*(20 63 69 64 20 3D 20 25 64 00 00 00+c)+2d


/*
0000000ch: 4D 65 64 69 61 43 53 4D 5F 53 65 6E 64 44 69 73 ; MediaCSM_SendDis
0000001ch: 63 6F 6E 6E 65 63 74 52 65 71 75 65 73 74 54 6F ; connectRequestTo
0000002ch: 43 6F 6E 6E 65 63 74 69 6F 6E 4D 61 6E 61 67 65 ; ConnectionManage
0000003ch: 72 3A 20 63 69 64 20 3D 20 36 35 35 33 35       ; r: cid = 65535
*/
#include "../inc/swilib.h"
#include "lang.h"
#include "conf_loader.h"

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

char utf8_name[128];
int is_music_file=0;
void getname(void)
{
	char *p=RAMPlayingFilename();
	unsigned char c;
	int i=0;
	if(!strncmp_nocase(p, "ager: cid = 65535", 12))//未打开媒体播放器或不在播放状态
	{
		utf8_name[0]=0;
		is_music_file=0;
		goto end;
	}
	while(c=*p)
	{
		if(!strncmp_nocase(p, ".mp3", 4))
		{
			strcpy(&utf8_name[i], ".mp3");
			is_music_file=1;
			break;
		}
		if(!strncmp_nocase(p, ".aac", 4))
		{
			strcpy(&utf8_name[i], ".aac");
			is_music_file=1;
			break;
		}
		if(!strncmp_nocase(p, ".m4a", 4))
		{
			strcpy(&utf8_name[i], ".m4a");
			is_music_file=1;
			break;
		}
		if(!strncmp_nocase(p, ".wav", 4))
		{
			strcpy(&utf8_name[i], ".wav");
			is_music_file=1;
			break;
		}
		if(!strncmp_nocase(p, ".amr", 4))
		{
			strcpy(&utf8_name[i], ".amr");
			is_music_file=1;
			break;
		}
		if(!strncmp_nocase(p, ".mid", 4))
		{
			strcpy(&utf8_name[i], ".mid");
			is_music_file=1;
			break;
		}
		if(!strncmp_nocase(p, ".3gp", 4))
		{
			strcpy(&utf8_name[i], ".3gp");
			is_music_file=1;
			break;
		}
		if(!strncmp_nocase(p, ".mp4", 4))
		{
			strcpy(&utf8_name[i], ".mp4");
			is_music_file=1;
			break;
		}
		if(!strncmp_nocase(p, ".imy", 4))
		{
			strcpy(&utf8_name[i], ".imy");
			is_music_file=1;
			break;
		}
		if(!strncmp_nocase(p, ".srt", 4))
		{
			strcpy(&utf8_name[i], ".srt");
			is_music_file=1;
			break;
		}
		if(!strncmp_nocase(p, ".bmp", 4))
		{
			is_music_file=0;
			break;
		}
		if(!strncmp_nocase(p, ".jpg", 4))
		{
			is_music_file=0;
			break;
		}
		if(!strncmp_nocase(p, ".gif", 4))
		{
			is_music_file=0;
			break;
		}
		if(!strncmp_nocase(p, ".png", 4))
		{
			is_music_file=0;
			break;
		}
		if(!strncmp_nocase(p, ".jpeg", 5))
		{
			is_music_file=0;
			break;
		}
		if(!strncmp_nocase(p, ".bmx", 4))
		{
			is_music_file=0;
			break;
		}
		if(!strncmp_nocase(p, ".svg", 4))
		{
			is_music_file=0;
			break;
		}
		if(!strncmp_nocase(p, ".wbmp", 4))
		{
			is_music_file=0;
			break;
		}
		utf8_name[i]=c;
		i++;
		p++;
	}
//gf
//bmp,bmx,gif,jpeg,jpg,png,svg,wbmp
end:;
	
}

typedef struct
{
	CSM_RAM csm;
}MAIN_CSM;

extern kill_data(void *p, void (*func_p)(void *));

extern const unsigned int pos_x;
extern const unsigned int pos_y;
extern const unsigned int length;
extern const unsigned int font;
extern const char color[4];
extern const char frmcolor[4];
extern const unsigned int txt_attr;
extern const int ENA_LOCK;

WSHDR *ews;

//unsigned int WHITE=0x64FFFFFF;
//unsigned int BLACK=0x64000000;

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
	CSM_RAM *icsm;
	if(msg->msg==MSG_RECONFIGURE_REQ)
	{
		extern const char *successed_config_filename;
		if(strcmp_nocase(successed_config_filename, (char *)msg->data0)==0)
		{
			ShowMSG(1, (int)LGP_UPDATE_CONFIG);
			InitConfig();
		}
	}
	if(IsPlayerOn()&&(ENA_LOCK||IsUnlocked()))
	{
		getname();
		icsm=FindCSMbyID(CSM_root()->idle_id);
		if(icsm&&is_music_file)
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
						str_2ws(ews, utf8_name, 128);
						DrawCanvas(canvasdata,pos_x,pos_y,pos_x+length,pos_y+GetFontYSIZE(font),1);
						DrawString(ews,pos_x,pos_y,pos_x+length,pos_y+GetFontYSIZE(font),font,txt_attr,color,frmcolor);
					}
				}
			}
		}
	}
	return 1;
}

static void maincsm_oncreate(CSM_RAM *data)
{
	ews=AllocWS(128);
}


static void Killer(void)
{
	extern void *ELF_BEGIN;
	FreeWS(ews);
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
	InitConfig();
	UpdateCSMName();
	LockSched();
	save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
	CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
	CreateCSM(&MAINCSM.maincsm, dummy,0);
	CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
	UnlockSched();
	return 0;
}

