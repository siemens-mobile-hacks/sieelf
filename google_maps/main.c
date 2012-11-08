/*
* GugloKarty
* Danil_e71
* Work through an intermediate php-script
* Displays a map of parts of
*/

#include "include.h"
#include "string_works.h"
#include "conf_loader.h"


const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;
typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  WSHDR *ws5;
  int i1;
}MAIN_GUI;

static void OnRedraw(MAIN_GUI *data)
{
for(int j=0;j<MAP_Y;j++)
for(int i=0;i<MAP_X;i++)
DrwImg(map[i][j],i*cub,j*cub);

if(mode==1)wsprintf(data->ws1,"加载地图流量:%d kb",all_traf/1024);
else if(mode==0) wsprintf(data->ws1,"按任意键流量:%d kb",all_traf/1024);
else if(mode==2)wsprintf(data->ws1,"加载缓存中...");

DrawString(data->ws1,0,0,ScreenW()-1,Get_WS_width(data->ws1,FONT),FONT,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
DrawRectangle(cur_x,cur_y,cur_x+cub,cur_y+cub,0,GetPaletteAdrByColorIndex(2),0);
}
static void Redraw()
{
  #ifdef ELKA
DisableIconBar(1);
#endif
  
#ifdef ELKA
  if(mode)timer=100;
  else timer=100;
  #else
    if(mode)timer=30;
  else timer=60;
#endif
  GBS_StartTimerProc(&tmr,timer,Redraw);
  DirectRedrawGUI();
}

void free_imghdr(IMGHDR *i)
{
if(i->bitmap)mfree(i->bitmap);
if(i)mfree(i);
}

int a=0;
void LoadCache()
{
  FSTATS fs;
  mode=2;
   

  DIR_ENTRY de;
  char folder[128];
  strcpy(folder,fname);
  strcat(folder,"*.*");
  
    if (FindFirstFile(&de,folder,0))
  {
    do
    {
      if(strstr(de.file_name,"cache"))
      {
        strcpy(folder,de.file_name);
        goto next;
      }
    }
    while(FindNextFile(&de,0));
  }
  
  
next:
   sscanf(folder,"cache%lf_%lf",&Lon,&Lat);
    zoom=Zoom;
    FindClose(&de,0);
  for(int j=0;j<MAP_Y;j++)
  for(int i=0;i<MAP_X;i++)
  {
  sprintf(filename,"%scache%f_%f\\map_%d_%d_%d_%d.png",fname,Lon,Lat,i,j,zoom,map_type);
  if(GetFileStats(filename,&fs,0)==-1)
  sprintf(filename,"%simg\\not.png",fname);
  map[i][j]=CreateIMGHDRFromPngFile(filename,2);
  }
  mode=0;
}



static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
#ifdef ELKA
DisableIconBar(1);
#endif
  SUBPROC((void*)LoadCache);
  data->ws1=AllocWS(256);
  data->gui.state=1;
}
static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  for(int j=0;j<MAP_Y;j++)
      for(int i=0;i<MAP_X;i++)
        free_imghdr(map[i][j]);
      
  data->gui.state=0;
  FreeWS(data->ws1);
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  #ifdef ELKA
  DisableIconBar(1);
  #endif
  data->gui.state=2;
  DisableIDLETMR();
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  #ifdef ELKA
  DisableIconBar(1);
  #endif
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

static void IMGHDR_cpy(IMGHDR *dest, IMGHDR *src)
{
if(!src->bitmap)return;
dest->w = src->w;
dest->h = src->h;
dest->bpnum = src->bpnum;
if(dest->bitmap)dest->bitmap=realloc(dest->bitmap,src->w*src->h*2+1);
else dest->bitmap=malloc(src->w*src->h*2);
memcpy(dest->bitmap, src->bitmap, src->w*src->h*2);
}

static void ShiftMap(int t)
{
  if(mode)return;
  
  Type=t;
  switch(Type)
  {
case RIGHT:
  for(int j=0;j<MAP_Y;j++)//MAP_Y-1 series
    for(int i=0;i<MAP_X-1;i++)//last row do not touch MAP_X-2 series
      IMGHDR_cpy(map[i][j],map[i+1][j]);
      mapi=MAP_X-1;
      mapj=0;
      Lon=XToL(LToX(Lon) + (cub<<(21-zoom))); 
break;

case LEFT:
 for(int j=0;j<MAP_Y;j++)
    for(int i=MAP_X-1;i>0;i--)
      IMGHDR_cpy(map[i][j],map[i-1][j]);
      mapi=0;
      mapj=0;
      Lon=XToL(LToX(Lon) + ((-cub)<<(21-zoom))); 
break;


case UP:
 for(int j=MAP_Y-1;j>0;j--)
    for(int i=0;i<MAP_X;i++)
      IMGHDR_cpy(map[i][j],map[i][j-1]);
      mapi=0;
      mapj=0;
      Lat=YToL(LToY(Lat) + (-cub<<(21-zoom)));
break;


case DOWN:
for(int j=0;j<MAP_Y-1;j++)
  for(int i=0;i<MAP_X;i++)
     IMGHDR_cpy(map[i][j],map[i][j+1]);
     mapi=0;
     mapj=MAP_Y-1; 
     Lat=YToL(LToY(Lat) + (cub<<(21-zoom)));
break;
  }
  sprintf(filename,"%simg\\loading.png",fname);
  free_imghdr(map[mapi][mapj]);
  map[mapi][mapj]=CreateIMGHDRFromPngFile(filename,2);
  c();
}


static void cur(int i)
{
  
  switch(i)
  {
    case UP:
    if(cur_y>=cub)cur_y-=cub;
    else ShiftMap(i);
    break;
    
    
    case DOWN:
    if(cur_y<ScreenH()-cub)cur_y+=cub;
    else ShiftMap(i);
    break;
  
    case LEFT:
    if(cur_x>=cub)cur_x-=cub;
    else ShiftMap(i);
    break;
    
    
    case RIGHT:
    if(cur_x<ScreenW()-cub)cur_x+=cub;
    else ShiftMap(i);
    break;
  
  }
  DirectRedrawGUI();
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{

  switch(msg->gbsmsg->msg)
  {      
  case KEY_UP: break;

    case KEY_DOWN:
      
       switch(msg->gbsmsg->submess)
         { 
         case RIGHT_SOFT:  return 1;
         case '5':if(mode==0){if(zoom<19)zoom++;Type=RIGHT;mapi=0;mapj=0;c();}break;
         case '0':if(mode==0){if(zoom> 0)zoom--;Type=RIGHT;mapi=0;mapj=0;c();}break;
         case GREEN_BUTTON:if(mode==0){Type=RIGHT;mapi=0;mapj=0;Lat=0;Lon=0;mlat=0;mlon=0;c();}break;
         case '2':case UP_BUTTON:cur(UP);break;
         case '4':case LEFT_BUTTON:cur(LEFT);break;
         case '6':case RIGHT_BUTTON:cur(RIGHT);break;
         case '8':case DOWN_BUTTON:cur(DOWN);break;
         }
  }     
 return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));



const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)0,
};


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
  
int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg){
    if(msg->msg == MSG_RECONFIGURE_REQ){
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0){
      InitConfig();
    }
    }
      MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
    
    if (msg->msg==MSG_HELPER_TRANSLATOR){
    if ((int)msg->data1==sock){
      //If our socket
      switch((int)msg->data0){
        case ENIP_SOCK_CONNECTED:
          if (connect_state==1){
            //If you send an inquiry
        //    SUBPROC((void *)send_req);
          //  send_req();
          }
          break;
        case ENIP_SOCK_DATA_READ:
          if (connect_state==2)

           SUBPROC((void *)get_answer);
         // get_answer();
          break;
        case ENIP_SOCK_REMOTE_CLOSED:
          //Closed by the server
          if (connect_state)
           SUBPROC((void *)end_socket);
        //    end_socket();
          break;
        case ENIP_SOCK_CLOSED:
          //Closed call closesocket
        //  send_or_connect=CONNECT;
          break;
      }
    }
  }
  return (1);
}

extern void kill_data(void *p, void (*func_p)(void *));
static void maincsm_oncreate(CSM_RAM *data){
   const RECT Canvas={0,0,ScreenW()-1,ScreenH()-1};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  Type=RIGHT;
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm){

  GBS_DelTimer(&tmr);
  SUBPROC((void *)Killer);
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

static void UpdateCSMname(void){
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"ElfGoogleMaps");
}

void DrwImg(IMGHDR *img, int x, int y)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  DrawObject(&drwobj);
}



int main(){
  InitConfig();
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  Redraw();
  SUBPROC((void *)create_connect);
  return 0;
}
