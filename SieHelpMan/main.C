#include "..\inc\swilib.h"

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;


extern void kill_data(void *p, void (*func_p)(void *));

int num=0;
int flag=0;
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
int status_flag=0;
WSHDR *ws_info;
GBSTMR mytmr;
#define TMR_SECOND 216
#define IPC_MY_IPC "SieHelpMan"
#define IPC_UPDATE_STAT 1
const char ipc_my_name[]=IPC_MY_IPC;

unsigned int REFRESH=5;

const IPC_REQ my_ipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
	rc->x=x;
	rc->y=y;
	rc->x2=x2;
	rc->y2=y2;
}

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}

void lgp(void)
{
  WSHDR *ws = AllocWS(256);
  WSHDR *ws1 = AllocWS(20);
  wsprintf(ws1, "LGP_ID: %d",num);
  wsprintf(ws, "%t",num);
  DrawString(ws1,5,70,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  DrawString(ws,5,100,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  FreeWS(ws);
  FreeWS(ws1);
}


void keycode(int code)
{
  WSHDR *ws = AllocWS(20);
  WSHDR *wsd = AllocWS(20);
  WSHDR *wsx = AllocWS(20);
  wsprintf(ws, "Keycode:");
  wsprintf(wsd, "Dec: %d", code);
  wsprintf(wsx, "Hex: %X", code);
  DrawRectangle(0,24,ScreenW(),ScreenH(),0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  DrawString(ws,5,70,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  DrawString(wsd,5,100,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  DrawString(wsx,5,130,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  FreeWS(ws);
  FreeWS(wsd);
  FreeWS(wsx);
}

void pic()
{
  WSHDR *ws = AllocWS(50);
  wsprintf(ws, "Num:%d(D) %X(H)\nInfo:%d(W) %d(H)",num,num,GetImgWidth(num),GetImgHeight(num));
  DrawString(ws,5,24,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  DrawImg(0,24+2*GetFontYSIZE(8)+2,num);
  FreeWS(ws);
}

void font()
{
  int font_max;
  char test_str[]="Test String";
  #ifdef NEWSGOLD
  #ifdef ELKA
  font_max=11;
  #else
  font_max=16;
  #endif
  #else
  font_max=10;
  #endif
  WSHDR *ws = AllocWS(64);
  WSHDR *ws1 = AllocWS(32);
  wsprintf(ws1,"Font Size: %d",num);
  DrawString(ws1,5,70,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  if (num<0||num>font_max)
  {
    wsprintf(ws,"No such font");
    DrawString(ws,5,100,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  }
  else
  {
    wsprintf(ws,test_str);
    DrawString(ws,5,100,ScreenW(),ScreenH(),num,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  }
  FreeWS(ws1);
  FreeWS(ws);
}

void status(void)
{
  RAMNET *net=RamNet();
  int temp=GetAkku(1,3)-0xAAA+15;
  int volt=GetAkku(0,9);
  #ifdef NEWSGOLD
  #ifdef ELKA
  char model[]="Siemens X85";
  #else
  char model[]="Siemens X75";
  #endif
  #else
  char model[]="Siemens X65";
  #endif
  DrawRectangle(0,24,ScreenW(),ScreenH(),0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  wsprintf(ws_info,"Phone: %s\nNet: %c%ddB\nBts: %d-%d:%d\nC1: %d C2: %d\nTemp: %d.%d°C\nVoltage:%d.%02dV\nAccuCap: %02d%%\nCpuLoad: %d%% CpuClock: %dMHz\nRam: %u Bytes",model,(net->ch_number>=255)?'=':'-',net->power,net->ci,net->lac,net->ch_number,net->c1,net->c2,temp/10,temp%10,volt/1000,(volt%1000)/10,*RamCap(),GetCPULoad(),GetCPUClock(),GetFreeRamAvail());
  DrawString(ws_info,5,24,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
}


void TimerProc(void)
{
  if (!IsGuiOnTop(MAINGUI_ID)) status_flag=0;
  if(status_flag) status();
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

void rgb24()
{
  WSHDR *ws1 = AllocWS(32);
  WSHDR *ws = AllocWS(32);
  wsprintf(ws1,"RGB24 COLOR: %d",num);
  DrawString(ws1,5,70,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  if (num<0||num>23)
  {
    wsprintf(ws,"No such color");
    DrawString(ws,5,100,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  }
  else DrawRoundedFrame(5,105,ScreenW()-5,ScreenH()-10,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(num));
  FreeWS(ws);
  FreeWS(ws1);
}

void sound()
{
  WSHDR *ws = AllocWS(32);
  wsprintf(ws, "Sound Num: %d", num);
  DrawString(ws,5,70,ScreenW(),ScreenH(),8,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  PlaySound(1,0,0,num,0);
  FreeWS(ws);
}

void onRedraw(MAIN_GUI *data)
{
  DrawRectangle(0,24,ScreenW(),ScreenH(),0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  if (flag!=4)
  {
    status_flag=0;
  }
  switch(flag)
  {
    case 0: lgp(); break;
    case 1: pic(); break;
    case 2: keycode(ENTER_BUTTON); break;
    case 3: font(); break;
    case 4: status(); status_flag=1; break;
    case 5: rgb24(); break;
    case 6: sound(); break;
    default : flag=0; break;
  }
}


void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

void create_num(int numx)
{
  num=num*10+numx;
  REDRAW();
}

void back_to_menu(void)
{
  status_flag=0;
  GeneralFuncF1(1); 
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{

  if (flag==2)
  {
    keycode(msg->gbsmsg->submess);
    if (msg->gbsmsg->submess==LEFT_SOFT)
    {
      if (msg->gbsmsg->msg==LONG_PRESS)
        back_to_menu();
    }
  }
/*  if (flag==4)
  {
    status_flag=0;
  }*/
  else
  {
    if (msg->gbsmsg->msg==KEY_UP)                      
    {                                                  
      switch(msg->gbsmsg->submess)                     
      {                                                
        case '0': create_num(0); break;                
        case '1': create_num(1); break;                
        case '2': create_num(2); break;                
        case '3': create_num(3); break;                
        case '4': create_num(4); break;                
        case '5': create_num(5); break;                
        case '6': create_num(6); break;                
        case '7': create_num(7); break;                
        case '8': create_num(8); break;                
        case '9': create_num(9); break;
        case '*': num=0; REDRAW(); break;
        case '#': num=num/10; REDRAW(); break; 
        case UP_BUTTON: num=num+1; REDRAW(); break;    
        case DOWN_BUTTON: num=num-1; REDRAW(); break;
        case RIGHT_BUTTON: num=num+1; REDRAW(); break; 
        case LEFT_BUTTON: num=num-1; REDRAW(); break;  
        case RIGHT_SOFT: CloseCSM(MAINCSM_ID); break;
        case LEFT_SOFT: back_to_menu(); break;
        //default : status_flag=0; break;
      }
    }
    if (msg->gbsmsg->msg==LONG_PRESS)
    {                                                  
      switch(msg->gbsmsg->submess)
      {                                                
        case UP_BUTTON: num=num+1; REDRAW(); break;    
        case DOWN_BUTTON: num=num-1; REDRAW(); break;  
        case RIGHT_BUTTON: num=num+1; REDRAW(); break; 
        case LEFT_BUTTON: num=num-1; REDRAW(); break;  
        //default : status_flag=0; break;
      }
    }
    //if (msg->gbsmsg->msg==KEY_DOWN) status_flag=0;
  }
  return(0);
}

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)onRedraw,	//Redraw
	(void *)onCreate,	//Create
	(void *)onClose,	//Close
	(void *)onFocus,	//Focus
	(void *)onUnfocus,	//Unfocus
	(void *)OnKey,		//OnKey
	0,
	(void *)kill_data,	//Destroy
	(void *)method8,
	(void *)method9,
	0
};

const RECT Canvas={0,0,0,0};

void startgui(void)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
	zeromem(main_gui,sizeof(MAIN_GUI));	
	patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();	
	MAINGUI_ID=CreateGUI(main_gui);
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}


int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
        switch (msg->submess)
        {
        case IPC_UPDATE_STAT:
#ifdef NEWSGOLD
          if (!getCpuUsedTime_if_ena())
          {
            StartCpuUsageCount();
          }
#endif
          GBS_StartTimerProc(&mytmr, REFRESH*TMR_SECOND/10, TimerProc);
        }
      }
    }
    
  }
  return(1);
}


const int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Exit"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

#define ITEMS_N 8

MENUITEM_DESC menu_items[ITEMS_N]=
{
  {NULL,(int)"SystemInfo",     LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Picture",        LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"LGP_ID",         LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Sound",         LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Font",           LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"RGB24",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"KeyCode",        LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"About",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

void lgp_gui(GUI *data)
{
  flag=0;
  startgui();
}

void pic_gui(GUI *data)
{
  flag=1;
  startgui();
}

void keycode_gui(GUI *data)
{
  flag=2;
  startgui();
}

void font_gui(GUI *data)
{
  flag=3;
  startgui();
}

void status_gui(GUI *data)
{
  flag=4;
  startgui();
}

void rgb24_gui(GUI *data)
{
  flag=5;
  startgui();
}

void sound_gui(GUI *data)
{
  flag=6;
  startgui();
}


void about(GUI *data)
{
  ShowMSG(1, (int)"SieHelpMan\n(c)BingK,\nbinghelingxi\n2007");
}

const MENUPROCS_DESC menu_hndls[ITEMS_N]=
{
  status_gui,
  pic_gui,
  lgp_gui,
  sound_gui,
  font_gui,
  rgb24_gui,
  keycode_gui,
  about,
};


int menu_onkey(void *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
      case RIGHT_SOFT : CloseCSM(MAINCSM_ID); break;
      case LEFT_SOFT : GBS_SendMessage(MMI_CEPID,KEY_UP,ENTER_BUTTON); break;
    }
  }
  return (0);
}

void mm_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

HEADER_DESC mm_menuhdr={0,0,0,0,NULL,(int)"SieHelpMan",LGP_NULL};

const MENU_DESC mm_menu=
{
  8,menu_onkey,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  menu_items,   //Items
  menu_hndls,   //Procs
  ITEMS_N   //n
};

void maincsm_oncreate(CSM_RAM *data)
{
  ws_info = AllocWS(256);
  MAIN_CSM *csm=(MAIN_CSM *)data;
  csm->csm.state=0;
  csm->csm.unk1=0;
  patch_header(&mm_menuhdr);
  csm->gui_id=CreateMenu(0,0,&mm_menu,&mm_menuhdr,0,ITEMS_N,0,0);
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}


void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  FreeWS(ws_info);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
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

void UpdateCSMname(void) 
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "SieHelpMan");
}

int main()
{
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
