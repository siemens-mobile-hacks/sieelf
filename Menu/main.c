#include "..\inc\swilib.h"

const int minus11=-11;

unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;



static const char percent_t[]="%t";
int x,y,i=1;
//int click;
int flag='mm';  
char mmenu[30]={0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int mode=0;
int show;
int from=0;
char commands[30][15];
char elfs[30][64];
char names[30][64];
int type[30];
char shows[1]="";
char back[64]="0:\\Zbin\\img\\Menu\\bg.png";
int lines=0;
char line[1]="";
int showing=0;
int offset=0;
char start_menu[8][64];
int length[30];
int click=0;


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
  int i1;
}MAIN_GUI;



void exe(char *fname)
{
  PlaySound(1,0,0,51,0);
  int (*p) (void);
  p=(int(*)(void))GetFunctionPointer(fname);
  if(p!=NULL)
    (*p)();
  else
    ShowMSG(1,(int)"NULL pointer function!");
} 

void shif()
{
//  ShowMSG(1,(int)commands[1]);

}

void LoadParams()
{
  unsigned int err;
  int plhandle,j,k;
  char tmp[2]="";
  char temp[10]="";
  char t[2]="";
//  int star_count=0;
//  int names_count=0;
  plhandle = fopen( "0:\\Zbin\\Menu\\Menu.cfg", A_ReadOnly + A_BIN, P_READ, & err );
  if ( plhandle == -1 )
  {
    fclose( plhandle, & err );
    return;
  }
// ShowMSG(1,(int)star);
//  __________________________________________________________________
  fread( plhandle,& line, 1, & err );
  lines=line[0];
  lines=lines-48;         //I do not know why it? but it? works 
  fread( plhandle, & temp, 2, & err );
  fread( plhandle,& shows, 1, & err );
  showing=shows[0];
  showing=showing-48;       //floor? also 
  fread( plhandle, & temp, 2, & err );
  
  for (j=0;j<(lines*3);j++)         //modified
  {
    tmp[0]=NULL;
    m:fread( plhandle, &tmp[0], 1, & err );
     if ((tmp[0]!=124)&&(tmp[0]!=42)&&(tmp[0]!=47)) goto m;
//     ShowMSG(1,(int)tmp);
       if ((int)tmp[0]==42)
        {
        
          t[0]=NULL;
          for (k=0;k<64;k++)
            {
              fread(plhandle,& t[0],1,&err);     
              if (((int)t[0]==42)|((int)t[0]==124)|((int)t[0]==47))
                {
                  type[j]=1;
                nah: fread(plhandle,& t[0],1,&err); 
                if ((int)t[0]!=47) goto nah; //:)
                  goto nm; 
//                  break;
                }
              else
                {
                  sprintf(elfs[j],"%s%s",elfs[j],t);
                }
            }
          type[j]=1;
      } 
   
      if ((int)tmp[0]==124)
         {
        //  ShowMSG(1,(int)"test_shortcut");
          t[0]=NULL;
          int kl=0;
          for (kl=0;kl<64;kl++) 
            {
              t[0]=NULL;
              fread( plhandle, &t[0], 1, & err );
             // ShowMSG(1,(int)t);
              if (((int)t[0]==42)|((int)t[0]==124)|((int)t[0]==47))
                {
                  
                   nah1: fread(plhandle,& t[0],1,&err); 
                  if ((int)t[0]!=47) goto nah1;
                  goto nm; 
//                  break;
                }
            else 
              {
                sprintf(commands[j],"%s%s",commands[j],t);
              }
            }
           t[0]=NULL;
           type[j]=0;
          }
       
       
  nm:if (((int)tmp[0]==47)|((int)t[0]==47))
         {
          t[0]=NULL;
          int klm=0;
          for (klm=0;klm<64;klm++) 
            {
              t[0]=NULL;
              fread( plhandle, &t[0], 1, & err );
              if (((int)t[0]==42)|((int)t[0]==124)|((int)t[0]==47)){/*ShowMSG(1,(int)commands[j]); */ break;}
            else 
              {
                sprintf(names[j],"%s%s",names[j],t);
                length[j]++;
              }
            }
           t[0]=NULL;
          // type[j]=0;
          }
       
    
  }   
  
  
  
 show=showing;
 fclose( plhandle, & err );
}


void bar()
{
/*char cl4[]={0xD1,0xDE,0xE7,0x64};
char cl2[]={0x91,0x9E,0xE7,0x64};

unsigned char* ex;


int ij=y*3+x;

ex=names[ij];
WSHDR *ws=AllocWS(256);
wsprintf(ws,  percent_t ,ex);
DrawString(ws,25,3,123,50,7,36,GetPaletteAdrByColorIndex(1),cl4); 
TDate date;
TTime time; 
GetDateTime(&date,&time);
wsprintf(ws, "        %i:%02i",time.hour,time.min);  
DrawString(ws,25,16,123,100,7,32,GetPaletteAdrByColorIndex(1),cl2); */
//FreeWS(ws);
}


void runst()
{

}



void run()
{
  WSHDR *ws=AllocWS(256); 
  int ij=y*3+x;
   if (((type[ij]==0)&(flag!='st'))|((i==5)&(flag=='st')))
  {
    if (flag=='st')
    {
      exe("STUP_TEXT_INPUT");
    } else
    {
    int hi;
    char com[15]="";
    for (hi=0;hi<15;hi++)
      {
        com[hi]=commands[ij][hi];
      }
   
    exe(com);
    }
  }
  else 
    {

      if (flag=='st'){ str_2ws(ws,start_menu[i],strlen(start_menu[i])+1); ExecuteFile(ws,0,"");} else
      {str_2ws(ws,elfs[ij],strlen(elfs[ij])+1); ExecuteFile(ws,0,"");}
    }

  FreeWS(ws);
}    
    
void Start()
{
  char cl[]={0x00,0x00,0x00,0x16};
  char clt[]={0xD1,0xDE,0xE7,0x64};
  DrawRoundedFrame(0,0,131,176,0,0,0,cl,cl); 
  DrawImg(0,26,(int)"0:\\Zbin\\img\\Menu\\st.png");
  int p[8]={0,0,0,0,0,0,0,0};
  p[i]=32;
  WSHDR *ws = AllocWS(256);
  
  wsprintf(ws,  percent_t,"  ");
  DrawString(ws,5,76,128,172,7,p[0],(p[0]!=0)?GetPaletteAdrByColorIndex(1):clt,(p[0]==0)?GetPaletteAdrByColorIndex(23):clt); 
  
  wsprintf(ws,  percent_t,"  MP3 player");
  DrawString(ws,5,89,128,172,7,p[1],(p[1]!=0)?GetPaletteAdrByColorIndex(1):clt,(p[1]==0)?GetPaletteAdrByColorIndex(23):clt); 
  
  wsprintf(ws,  percent_t,"  Opera");
  DrawString(ws,5,102,128,172,7,p[2],(p[2]!=0)?GetPaletteAdrByColorIndex(1):clt,(p[2]==0)?GetPaletteAdrByColorIndex(23):clt); 
  
  wsprintf(ws,  percent_t,"  NatIcq");
  DrawString(ws,5,115,128,172,7,p[3],(p[3]!=0)?GetPaletteAdrByColorIndex(1):clt,(p[3]==0)?GetPaletteAdrByColorIndex(23):clt); 
  
  wsprintf(ws,  percent_t,"  MC");
  DrawString(ws,5,128,128,172,7,p[4],(p[4]!=0)?GetPaletteAdrByColorIndex(1):clt,(p[4]==0)?GetPaletteAdrByColorIndex(23):clt); 
  
  wsprintf(ws,  percent_t,"  Âûבמ?ÿחûךא");
  DrawString(ws,5,141,128,172,7,p[5],(p[5]!=0)?GetPaletteAdrByColorIndex(1):clt,(p[5]==0)?GetPaletteAdrByColorIndex(23):clt); 
  
 
  FreeWS(ws);
}

void execelf(char *exename, char *fname)
{ //fname-file name? conveyed? Elf 
 /* WSHDR *ws=AllocWS(256); 
  str_2ws(ws,exename,strlen(exename)+1); 
  ExecuteFile(ws,0,fname); 
  FreeWS(ws);*/
}

void Info()
{char cl[]={0x00,0x00,0x00,0x16};
 char clt[]={0xD1,0xDE,0xE7,0x64};
    TDate date;
    TTime time; 
    GetDateTime(&date,&time); 
    
 DrawRoundedFrame(0,0,131,176,0,0,0,cl,cl);
 DrawImg(13,35,(int)"0:\\Zbin\\img\\Menu\\wi.png");
 WSHDR *ws = AllocWS(256);
 wsprintf(ws, "Time: %i:%02i",time.hour,time.min);
 DrawString(ws,18,49,110,100,7,32,clt,GetPaletteAdrByColorIndex(1));

 wsprintf(ws, "RAM: %i Kb",GetFreeRamAvail()/1024);
 DrawString(ws,18,65,110,100,7,32,clt,GetPaletteAdrByColorIndex(1));
 
 wsprintf(ws, "%i,%03i=%i%%, %i°C",GetAkku(0,2)/1000,GetAkku(0,2)%1000,*RamCap(),(GetAkku(1,3)-0xAAA+15)/10);
 DrawString(ws,18,81,110,100,7,32,clt,GetPaletteAdrByColorIndex(1));
 
 RAMNET *rn=RamNet();
  char* std;
  if (rn->ch_number>=255) std="GSM 1800"; else {if (rn->ch_number>=128) std="EGSM 900"; else std="GSM 900";};
  wsprintf(ws, "%i db,%s",rn->power,std);
  DrawString(ws,18,97,110,120,7,32,clt,GetPaletteAdrByColorIndex(1));
 
 
 
 FreeWS(ws);
 
}



void Menu()
{
  int a;
  int ta=1;
  int b=0;
  char cl4[]={0xD1,0xDE,0xE7,0x64};
//  char cl2[]={0x91,0x9E,0xE7,0x64};
  WSHDR *ws=AllocWS(256);
  char* ex;
  int ij=y*3+x;
  
  int active,active_ta,active_b;
  char temp[64];
  char path[64]="0:\\Zbin\\img\\Menu\\";
  char full_path[64]="0:\\Zbin\\img\\Menu\\";
  char cut_ex[11]="";
  int g=0;
  int lim=0;
  DrawImg(0,0,(int)back);
  
  for (a=from;a<(3*show);a++)
  {
    
  
    if (mmenu[a]==0) 
    {
      sprintf(temp,"%i_s.png",a+1);
      sprintf(full_path,"%s%s",path,temp);
      DrawImg(47*(ta-1),3+176/showing*b,(int)full_path);
      ex=names[a];
      if (strlen(ex)>5) lim=5;
        else lim=strlen(ex);
        for (g=0;g<lim;g++)
          {
              cut_ex[g]=ex[g];
            }
      if (strlen(ex)>5)
        wsprintf(ws,"%t%t",cut_ex,"...");
      else wsprintf(ws,"%t",ex);
    if (a%3==0)
        DrawString(ws,0,(6)+(176/showing)*b+24,176,(30)+(121/showing)*b+60,7,32,GetPaletteAdrByColorIndex(1),cl4); 
    if (a%3==1)
        DrawString(ws,41*(ta-1)+22-(strlen(cut_ex)*8)/2,(6)+(176/showing)*b+24,41*(ta-1)+32+(strlen(cut_ex)*8)/2,(30)+(121/showing)*b+60,7,32,GetPaletteAdrByColorIndex(1),cl4); 
    if (a%3==2)
        DrawString(ws,41*(ta-1)+48-(strlen(cut_ex)*8),(6)+(176/showing)*b+24,176,(30)+(121/showing)*b+60,7,32,GetPaletteAdrByColorIndex(1),cl4); 
    }
    else if (mmenu[a]==1) 
    {
      active=a;
      active_ta=ta;   /*having? from bug pererisovk*/
      active_b=b;
    }
  ta++;
  
  if ((ta%4==0)&&(a!=0) )
    {
      b++;
      ta=1;

    }
  }
      sprintf(temp,"%i_b.png",active+1);
      sprintf(full_path,"%s%s",path,temp);
      DrawImg(41*(active_ta-1),7+(163/showing)*active_b,(int)full_path);  

 ex=names[ij];

wsprintf(ws,  percent_t ,ex);
if (x==0)
DrawString(ws,0,(13)+(163/showing)*active_b,176,(30)+(121/showing)*active_b+50,7,0,GetPaletteAdrByColorIndex(1),cl4); 
if (x==1)
DrawString(ws,41*(active_ta-1)+32-(strlen(ex)*8)/2,(13)+(163/showing)*active_b,41*(active_ta-1)+32+(strlen(ex)*8)/2,(30)+(121/showing)*active_b+50,7,0,GetPaletteAdrByColorIndex(1),cl4); 
if (x==2)
DrawString(ws,0,(13)+(163/showing)*active_b,176,(30)+(121/showing)*active_b+50,7,3,GetPaletteAdrByColorIndex(1),cl4); 

FreeWS(ws);
  bar();
  
  if (flag=='st') Start();
  if (flag=='iw') Info();
}




void OnRedraw(MAIN_GUI *data)
{
Menu();
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

  DisableIDLETMR();
  
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
 
//  REDRAW();

  if (msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
  {
  
    switch(msg->gbsmsg->submess)
    { 
    case RED_BUTTON: if (flag=='mm' ) {return(1);} else {flag='mm';} REDRAW(); break;
    case ENTER_BUTTON:  {   
                                    if (flag=='mm') 
                                      {
                                        run();
                                      } 
                                    if (flag=='st') 
                                      {
                                      run();
                                      }  
                                    } break;
    case LEFT_BUTTON: 
                          {  
                            if (flag=='mm') 
                              {
                                mmenu[y*3+x]=0; 
                                x=(x-1+3)%3;
                                mmenu[y*3+x]=1;
                              } 
                            REDRAW();
                          }break;
    case UP_BUTTON:    
                          {  
                          click++;
                            if (flag=='mm') 
                              {
                                mmenu[y*3+x]=0; 
                                 if (from!=0)
                                  {
                                    if (y<=from/3)
                                    {
                                      from=from-3;
                                     show--;
                                    }
                                    }
                              
                                if (y<=0)
                                {
                                  y=lines;
                                  from=(lines-showing)*3;
                                  show=lines;
                                }
                                 y=y-1;
                                  
                                mmenu[y*3+x]=1;
                              } 
                            if (flag=='st') 
                              {
                                i=(i-1+6)%6;
                              } 
                            REDRAW();
                          }break;
    case RIGHT_BUTTON:  {  if (flag=='mm') {mmenu[y*3+x]=0; x=(x+1+3)%3;mmenu[y*3+x]=1;} REDRAW();}break;
    case DOWN_BUTTON:  
                           {  
                              if (flag=='mm') 
                                {
                                  mmenu[y*3+x]=0;
                                  y=y+1;
                                  if (y>=show)
                                  {
                                    if (y>=lines)
                                    {
                                    y=0;
                                    from=0;
                                    show=showing;
                                    } else{
                                    from=from+3;
                                    show=show+1;}
                                  }
                                   
                                  mmenu[y*3+x]=1;
                                } 
                              if (flag=='st') {i=(i+1+6)%6;} 
                              REDRAW();
                           }
                           break;
 //  case 0x01: {  click++;flag=(flag=='st')?'mm':'st'; REDRAW();}break;
      case '1':{mmenu[y*3+x]=0;x=0;y=(from/3);mmenu[y*3+x]=1;REDRAW(); run();}break;                       
      case '2':{mmenu[y*3+x]=0;x=1;y=(from/3);mmenu[y*3+x]=1;REDRAW(); run();}break;     
      case '3':{mmenu[y*3+x]=0;x=2;y=(from/3);mmenu[y*3+x]=1;REDRAW(); run();}break;     
      case '4':{mmenu[y*3+x]=0;x=0;y=(from/3)+1;mmenu[y*3+x]=1;REDRAW(); run();}break;     
      case '5':{mmenu[y*3+x]=0;x=1;y=(from/3)+1;mmenu[y*3+x]=1;REDRAW(); run();}break;     
      case '6':{mmenu[y*3+x]=0;x=2;y=(from/3)+1;mmenu[y*3+x]=1;REDRAW(); run();}break;     
      case '7':{mmenu[y*3+x]=0;x=0;y=(from/3)+2;mmenu[y*3+x]=1;REDRAW(); run();}break;     
      case '8':{mmenu[y*3+x]=0;x=1;y=(from/3)+2;mmenu[y*3+x]=1;REDRAW(); run();}break;     
      case '9':{mmenu[y*3+x]=0;x=2;y=(from/3)+2;mmenu[y*3+x]=1;REDRAW(); run();}break;
    case 0x2A:{mmenu[y*3+x]=0;x=0;y=(from/3)+3;mmenu[y*3+x]=1;REDRAW(); run();}break;
   case '0':{mmenu[y*3+x]=0;x=1;y=(from/3)+3;mmenu[y*3+x]=1;REDRAW(); run();}break;
   case 0x23:{mmenu[y*3+x]=0;x=2;y=(from/3)+3;mmenu[y*3+x]=1;REDRAW(); run();}break;
    case 0x04: {  flag=(flag=='iw')?'mm':'iw'; REDRAW();}break;
  //  case 0x2A:{if (mode<11){mode++;} else mode=0; REDRAW();}break;
  //  case 0x0B:{InitConfig(); REDRAW();}break;
    }
  }
  
  //REDRAW();
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));

void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
kill_data(data,mfree_adr);
}

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,	
  (void *)onCreate,	
  (void *)onClose,	
  (void *)onFocus,	
  (void *)onUnfocus,
  (void *)OnKey,	
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,
  #else
  (void *)kill_data,	
  #endif
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,129,129};
void maincsm_oncreate(CSM_RAM *data)
{
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
  MAINGUI_ID=csm->gui_id;
  LoadParams();
 
}

void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

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
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Menu");
  FreeWS(ws);
}


int main(char *exename, char *fname)
{
  x=1;
  y=1;
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  UpdateCSMname();
  
  return 0;
}
