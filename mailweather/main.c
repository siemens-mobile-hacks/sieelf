#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "print.h"

#define IPC_WEATH_NAME "MailWeather"
#define IPC_UPDATE_STAT 1
#define BUFSIZE 16383

//#define LOG

const char ipc_my_name[32]=IPC_WEATH_NAME;
const IPC_REQ gipc={ipc_my_name,ipc_my_name,NULL};
const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;


extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline=forced

int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

char temp[32];
char speed[32];
char davlenie[32];
char vlaznost[32];
char prognoze[128];
char ICON[128];
char buf[BUFSIZE+1];

int sock;
int connect_state=0;
int pbuf=0;
int traf=0;

const char per_d[]="%d";
const char per_s[]="%s";

extern const int fullfont;

extern const unsigned int date_X;
extern const unsigned int date_Y;
extern const unsigned int weather_X;
extern const unsigned int weather_Y;
extern const unsigned int date_X2;
extern const unsigned int date_Y2;
extern const unsigned int date_X3;
extern const unsigned int date_Y3;
extern const unsigned int date_X4;
extern const unsigned int date_Y4;
extern const unsigned int date_X5;
extern const unsigned int date_Y5;
extern const char color[];
extern const unsigned int refresh;
extern const int ENA_HELLO_MSG;
extern const int ENA_MSG;
extern const int show_temp;
extern const int show_speed;
extern const int show_prognoze;
extern const int show_davlenie;
extern const int show_vlaznost;

extern const char str_vlaznost[];
extern const char str_davlenie[];
extern const char str_temp[];
extern const char id_tower[];
extern const char weather_img_path[];

extern const int IKONA;
extern const int chekeris1;
extern const int chekeris2;
extern const int chekeris3;
extern const int chekeris4;
extern const int chekeris5;

//------------- pngfont -------------//

extern const char fontpath[];
extern const int align1;
extern const int align2;
extern const int align3;
extern const int align4;
extern const int align5;
extern const unsigned int space;
extern const unsigned int font;

void *canvasdata;

//-------------pngfont end------------//

GBSTMR mytmr;

void start_again(void);

void create_connect(void)
{
  zeromem(buf,sizeof(buf));
  SOCK_ADDR sa;
  connect_state=0;
  pbuf=0;
  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
 //   sa.ip=htonl(IP_ADDR(194,67,45,236));//94.100.178.193
    sa.ip=htonl(IP_ADDR(94,100,178,193));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
    }
    else
    {
      closesocket(sock);
      GBS_StartTimerProc(&mytmr, 12960, start_again);
    }
  }
  else
    GBS_StartTimerProc(&mytmr, 12960, start_again);
}

void start_again()
{
  if(IsGPRSConnected())
  {
   SUBPROC((void *)create_connect);
  }
  else
   GBS_StartTimerProc(&mytmr, 2160, start_again);
}

void send_req(void)
{
  char *req_buf=malloc(1200);
  sprintf(req_buf,"GET /index.xhtml?&city=%s HTTP/1.1\n"
            "Accept-Language: en-us\n"
              "Accept-Encoding: gzip, deflate\n"
                "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\n"
                  "Host: wap.weather.mail.ru\n"
                    "Connection: Close\n"
                      "\n"
                        , id_tower);
  send(sock,req_buf,strlen(req_buf),0);
  connect_state=2;
  mfree(req_buf);
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
    connect_state=0;
  }
}

int buf_len=0;

void get_answer(void)
{
  int i=pbuf;
  if (connect_state<2) return;
  char s[1024];
  traf+=i=recv(sock,s,sizeof(s),0);
  if(i>0)
  {
    pbuf+=i;      
    strcat(buf,s);
  }
  else
  {
    end_socket();
  }
}


#ifdef LOG
void save_to_file()
{
  volatile int hFile;
  unsigned int io_error = 0;
  unsigned int ul;
  FSTATS stat;
  GetFileStats("4:\\debug_weather.txt",&stat,&ul);
  hFile = fopen("4:\\debug_weather.txt",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE, &io_error);
  if(hFile!=-1)
   {
     fwrite(hFile, buf, strlen(buf), &io_error);
     fclose(hFile, &io_error);
   }
}

void log(const char *s)
{
  volatile int hFile;
  unsigned int io_error = 0;
  unsigned int ul;
  FSTATS stat;
  GetFileStats("4:\\weather.txt",&stat,&ul);
  hFile = fopen("4:\\weather.txt",A_ReadWrite+A_Create+A_Append,P_READ+P_WRITE, &io_error);
  if(hFile!=-1)
   {
     fwrite(hFile, s, strlen(s), &io_error);
     fwrite(hFile, "\n", 1, &io_error);
     fclose(hFile, &io_error);
   }
}
#endif


void utf82win(char*d,const char *s)
{
  for (; *s; s+=2)
  {
    unsigned char ub = *s, lb = *(s+1);
    if (ub == 208)
      if (lb != 0x81)
        {*d = lb + 48; d++;}
      else
        {*d = '�'; d++;}

    if (ub == 209)
      if (lb != 0x91)
        {*d = lb + 112; d++;}
      else
        {*d = '�'; d++;}

    if ((ub != 208) && (ub != 209) && (lb != 91) && (lb != 81))
    {
      *d = ub;
      d++;
      s--;
    }
  }
  *d = 0;
}

GBSTMR delaytmr;
//int test=0;
/*
<div class="forecastblock">
<h3>6.04, �����������</h3>
<div class="forecast">
  ������<img src="/img/new/pict_weather_med_7.gif" width="41" height="41" alt="����" />
                                                                        <span class="spec">+9&deg;</span>
</div>
<div class="forecasttext">
  <div><strong>757</strong>&#032;mmHg, <strong>42</strong>%, <strong>� 1</strong>&#032;�/�</div>
  ����
</div>
*/
//int forecast = 0, forecasttext = 0;


#define _pic 0
#define _temp 1
#define _dav 2
#define _speed 3
#define _vlaznost 4
#define _comfort 5

int flags[6]={0,0,0,0,0,0};
void Parsing()
{
#ifdef LOG
   save_to_file();
   log("start parsing");
#endif
   for(int i=0;i<6;i++) flags[i] = 0; //����� ��������
   char *s1,*s2;
   char forecast[]="forecast";
   char forecasttext[]="forecasttext";
   int i = 0;
   //���� ������� ��� ��������� ������ ��� ��������...
   if((s1=strstr(buf,forecast)) && (s2=strstr(buf,forecasttext)))
   {
     if(s1=strstr(s1,"<img src"))//��������
     {
#ifdef LOG
       log("pictures");
#endif       
       flags[_pic] = 1;
       s1+=strlen("<img src=")+1+strlen("/img/new/");
       char picname[32];
       zeromem(picname,32);
       while(*s1!='.')
       {
         picname[i] = *s1;
         i++;
         *s1++;
       }
       zeromem(ICON,sizeof(ICON));
       sprintf(ICON,"%s%s.png",weather_img_path,picname);
       ICON[strlen(ICON)]=0;
#ifdef LOG
       log(ICON);
#endif
     }
    
     if(s1=strstr(s1,"><span class="))//�����������
     {
#ifdef LOG       
       log("temperature");
#endif       
       flags[_temp] = 1;
       i = 0;
       s1+=strlen("><span class=")+strlen("spec")+3;
       zeromem(temp,sizeof(temp));
       while(*s1 != '&')
       {
         temp[i] = *s1;
         *s1++;
         i++;
       }
       temp[strlen(temp)+1] = 0;
#ifdef LOG
       log(temp);
#endif
     }
     
     //s2 += strlen(forecasttext);
     if(s2)
      {
         //<div class="forecasttext">
         //<div><strong>757</strong>&#032;mmHg, <strong>42</strong>%, <strong>� 1</strong>&#032;�/�</div>����
        if(s2=strstr(s2,"<strong>"))//��������
        {
#ifdef LOG          
          log("davlenie");
#endif
          flags[_dav] = 1;
          s2+=strlen("<strong>")+1;
          i=0;
          zeromem(davlenie,sizeof(davlenie));
          while(*s2 != '<')
          {
            davlenie[i] = *s2;
            *s2++;
            i++;
          }
          davlenie[strlen(davlenie)+1] = 0;
          strcat((char*)(davlenie+strlen(davlenie))," mmHg");
#ifdef LOG
          log(davlenie);
#endif
        }
        
        if(s2=strstr(s2,"<strong>"))//���������
        {
#ifdef LOG
          log("vlaznost");
#endif          
          flags[_vlaznost] = 1;
          s2+=strlen("<strong>")+1;
          i=0;
          zeromem(vlaznost,sizeof(vlaznost));
          while(*s2 != '<')
          {
            vlaznost[i] = *s2;
            *s2++;
            i++;
          }
          vlaznost[strlen(vlaznost)+1] = 0;
          strcat((char*)(vlaznost+strlen(vlaznost))," %");
#ifdef LOG
          log(vlaznost);
#endif
        }
        
        if(s2=strstr(s2,"<strong>"))//�������� �����
        {
#ifdef LOG          
          log("speed veter");
#endif
          char tmp[128];
          zeromem(tmp,128);
          flags[_speed] = 1;
          s2+=strlen("<strong>")+2;
          i=0;
          while(*s2 != '<')
          {
            tmp[i] = *s2;
            *s2++;
            i++;
          }
          
          tmp[strlen(tmp)] = 0;
          strcat((char*)(tmp+strlen(tmp))," �/�");
          tmp[strlen(tmp)] = 0;
          utf82win(speed,tmp);
#ifdef LOG
          log(speed);
#endif
        }
        
        if(s2=strstr(s2,"</div>"))//������
        {
#ifdef LOG
          log("prognoze");
#endif
          char tmp[128];
          zeromem(tmp,128);
          flags[_comfort] = 1;
          s2+=strlen("</div>")+3;//+3 ��� \n\r + ������
          i=0;
          while(*s2 != '\n' && *(s2+1) != '\r')
          {
            tmp[i] = *s2;
            *s2++;
            i++;
          }
          
          tmp[strlen(tmp)] = 0;  
          utf82win(prognoze,tmp);
#ifdef LOG
          log(prognoze);
#endif
        }
      }//if(s2)
     if(ENA_MSG) ShowMSG(1,(int)"All data reciev and parse!");
   }
   else//if(strstr(buf,"forecast"))
   {
    ShowMSG(1,(int)"Wrong reciev data! Waiting 60 second!");
    GBS_StartTimerProc(&mytmr, 60*216*5, start_again);
   }
   
//   if(s1) mfree(s1);
  // if(s2) mfree(s2);
}
 
void DrawTemp(void *canv)//�����������
{
  if(!flags[_temp]) return;
  char *tempera=malloc(256);
  sprintf(tempera, "%s%s%c", str_temp, temp,2224);
  if(chekeris1==0)
  {
    PrintField(date_X,date_Y, tempera, align1, font, space);
  }
  else
   {
    if((chekeris1==1)&&(IsUnlocked()))
     {
       PrintField(date_X,date_Y, tempera, align1, font, space);
     }
    else
     if((chekeris1==2)&&(!IsUnlocked()))
      {
       PrintField(date_X,date_Y, tempera, align1, font, space);
      }
    }
  mfree(tempera);
}

void DrawSpeed(void *canv)//�������� �����
{
  if(!flags[_speed])return;
  if(chekeris2==0)
  {
   PrintField(date_X2,date_Y2, speed, align2, font, space);
  }
  else
  {
   if((chekeris2==1)&&(IsUnlocked()))
   {
    PrintField(date_X2,date_Y2, speed, align2, font, space);
   }
   else
    if((chekeris2==2)&&(!IsUnlocked()))
     {
      PrintField(date_X2,date_Y2, speed, align2, font, space);
     }
  }
}

void DrawComfort(void *canv)//�������
{
  if(!flags[_comfort])return;
  if(chekeris3==0)
  {
     PrintField(date_X3,date_Y3, prognoze, align1, font, space);
  }
  else
  {
   if((chekeris3==1)&&(IsUnlocked()))
   {
      PrintField(date_X3,date_Y3, prognoze, align3, font, space);
   }
   else
    if((chekeris3==2)&&(!IsUnlocked()))
    {
       PrintField(date_X3,date_Y3, prognoze, align3, font, space);
    }
   }
}

void DrawDavlenie(void *canv)//��������
{
  if(!flags[_dav])return;
  char *tempera=malloc(256);
  sprintf(tempera, "%s%s", str_davlenie, davlenie);
  if(chekeris4==0)
  {
     PrintField(date_X4,date_Y4, tempera, align4, font, space);
  }
  else
  {
   if((chekeris4==1)&&(IsUnlocked()))
    {
      PrintField(date_X4,date_Y4, tempera, align4, font, space);
    }
    else
     if((chekeris4==2)&&(!IsUnlocked()))
      {
        PrintField(date_X4,date_Y4, tempera, align4, font, space);
      }
   }
  mfree(tempera);
}

void DrawVlaznost(void *canv)//���������
{
  if(!flags[_vlaznost])return;
  char *tempera=malloc(256);
  sprintf(tempera, "%s%s", str_vlaznost, vlaznost);
  if(chekeris5==0)
  {
   PrintField(date_X5,date_Y5, tempera, align5, font, space);
  }
  else
  {
    if((chekeris5==1)&&(IsUnlocked()))
    {
     PrintField(date_X5,date_Y5, tempera, align5, font, space);
    }
    else
     if((chekeris5==2)&&(!IsUnlocked()))
      {
       PrintField(date_X5,date_Y5, tempera, align1, font, space);
      }
   }
  mfree(tempera);
}


//----------------------------Scroll String---------------------------------//


//#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])

//extern const unsigned int x;
//extern const unsigned int y;
extern const RECT pos1;
extern const int al;
//extern const unsigned int scrollsize;
extern const int ENA_SCROLL;
extern const unsigned int TimeUpdateScroll;
extern const char fontColor[];//��� ���������� �����
extern const char bgrColor[];//��� ���������� �����
extern const int isOutline;//��� ���������� �����
extern const unsigned int scrollDelay;
char *s;
GBSTMR scrollTmr;
CSM_RAM *icsm;
GUI *igui;
char scrollstr[256];
#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
int checkGui(int id)
{
 int retval = 0; 
 if (IsGuiOnTop(id)) 
 {
    GUI* igui = GetTopGUI();
    if (igui)
    {
#ifdef ELKA
      canvasdata = BuildCanvas();
      retval = 1;
#else
      void *idata = GetDataOfItemByID(igui, 2);
      if (idata)
      {
        canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
        retval = 1;
      }
#endif
    }  
 }
 return retval;
}


void DrawScrollStr()
{
  int isScroll=1;
  char *buf;
  icsm=FindCSMbyID(CSM_root()->idle_id);
/*  if(IsGuiOnTop(idlegui_id)&&!IsScreenSaver())
  {
   igui=GetTopGUI();
   if(igui)
   {*/
     icsm=FindCSMbyID(CSM_root()->idle_id);
     if (icsm && checkGui(idlegui_id(icsm)))
      {
        canvasdata=BuildCanvas();
        buf=malloc(strlen(scrollstr)+1);
        strcpy(buf,scrollstr);
        PrintText(pos1.x,pos1.y,buf,al,font,space,0,isScroll,0,pos1.x2);
        mfree(buf);
     }
  //}
}

void SaveWeath()
{
 // return;
#ifdef LOG
  log("saveweath");
#endif
  char *s=malloc(256), *s2=malloc(256);
#ifdef LOG
  log("malloc");
#endif
  sprintf(s, "%s%s%c", str_temp, temp,2224); 
  sprintf(s2, "%s%s", str_vlaznost, vlaznost);
#ifdef LOG
  log("s s2");
#endif
  //if(test==5)
  {
    if(show_temp)
    {
      //strcat(s,s2);
      strcat(s," | ");
#ifdef LOG
  log("show temp");
#endif
    }
    
    if(show_speed)
     {
#ifdef LOG
  log("show_speed");
#endif
      strcat(s,speed);
      strcat(s," | ");
     }
    
    if(show_prognoze)
      {
#ifdef LOG
  log("show prognoze");
#endif
      strcat(s,prognoze);
      strcat(s," | ");
     }
    
    if(show_davlenie)
     {
#ifdef LOG
  log("show davl");
#endif
      strcat(s,davlenie);
      strcat(s," | ");
     }
    
    if(show_vlaznost)
     {
#ifdef LOG
  log("show_vlazn");
#endif
       strcat(s,s2);
     }  
  }
  strcpy(scrollstr,s);
  mfree(s);
  mfree(s2);
}


//-------------------------------------------------------------//

void TimerProc()// ����������� �� �������
{
   DrawScrollStr();
   GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
}


int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"MailWeather 2.4 config updated!");
      InitConfig();
      PrintLibFree();
      PrintLibInit(1);
      FontPathInit((char*)fontpath, fullfont);
      SetScrollEdgeDelay(1);
      SetFontColor((char*)fontColor,(char*)bgrColor,isOutline);
      GBS_DelTimer(&mytmr);
      GBS_DelTimer(&scrollTmr);
      SUBPROC((void *)create_connect);
    }
  }
  
  if (msg->msg==MSG_IPC)// IPC
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)// ���� ������� ����������� ���������
      {
        switch (msg->submess)
        {
        case IPC_UPDATE_STAT:
          GBS_StartTimerProc(&scrollTmr,TimeUpdateScroll, TimerProc);
          break;
        }
      }
    }
  }

  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    if ((int)msg->data1==sock)
    {
      //���� ��� �����
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
        if (connect_state==1)
        {
          //ShowMSG(1,(int)"send req");
          //���� �������� ������
          SUBPROC((void *)send_req);        
        }
        else
          {
          //  ShowMSG(1,(int)"create connect");
          SUBPROC((void *)create_connect); 
          }
        break;
      case ENIP_SOCK_DATA_READ:
        if (connect_state==2)
        {
        //  ShowMSG(1,(int)"get_answer");
          //���� �������� send
          SUBPROC((void *)get_answer);
        }
        else
        {
      //    ShowMSG(1,(int)"create_connect");
          SUBPROC((void *)create_connect);
        }
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
    //    ShowMSG(1,(int)"sock remote closed");
        //������ �� ������� �������
        if (connect_state) SUBPROC((void *)end_socket);
        break;
      case ENIP_SOCK_CLOSED:
  //      ShowMSG(1,(int)"sock closed");
        //������ ������� closesocket
        if (connect_state) SUBPROC((void *)end_socket);
        connect_state=3;
    //    GBS_StartTimerProc(&delaytmr, 262*10,Parsing);
        Parsing();
//        ShowMSG(1,(int)"all recv!");
        if(ENA_SCROLL)
        {
          SaveWeath();
          GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
        }
        sock=-1;
        break;
      }
    }
  }  
  
 
 /* if(msg->msg == MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,"IdleUpd")==0)
      {
        switch (msg->submess)
        {
        case 0:
          {*/
            icsm=FindCSMbyID(CSM_root()->idle_id);
            if (icsm && checkGui(idlegui_id(icsm)))
            {
              canvasdata=BuildCanvas();
           // {
              if(!(ENA_SCROLL)/* && (test==5)*/)
              {
                if(show_temp)
                  DrawTemp(canvasdata);
                if(show_speed)
                  DrawSpeed(canvasdata);
                if(show_prognoze)
                  DrawComfort(canvasdata);
                if(show_davlenie)
                  DrawDavlenie(canvasdata);
                if(show_vlaznost)
                  DrawVlaznost(canvasdata); 
              }
              
              if(IKONA && flags[_pic])
              {
                DrawCanvas(canvasdata,weather_X,weather_Y,weather_X+GetImgWidth((int)ICON)-1,weather_Y+GetImgHeight((int)ICON)-1,1);
                DrawImg(weather_X,weather_Y,(int)ICON);
              }
             }
        /*  }
        }
      }
    }
  }*/


  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{
   //  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
}

static void Killer(void)
{
  PrintLibFree();
  GBS_DelTimer(&scrollTmr);
  GBS_DelTimer(&mytmr);
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MailWeather v3.0");
}



int main(char *filename)
{
  //char *s;
//  int len;
  extern const char *successed_config_filename;
  WSHDR *ws;
  
  InitConfig();
  //s=strrchr(filename,'\\');
  //len=(s-filename)+1;
  //strncpy(elf_path,filename,len);
//  elf_path[len]=0;
  if(strlen(fontpath)==0 && font<100)
  {
    LockSched();
    ShowMSG(1,(int)"Please set config!");
    ws=AllocWS(150);
    str_2ws(ws,successed_config_filename,128);
    ExecuteFile(ws,0,0);
    UnlockSched();
    SUBPROC((void *)Killer);
    return 0;
  }
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  UpdateCSMname(); 
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  if(ENA_HELLO_MSG)
    ShowMSG(1,(int)"MailWeather v3.0 (c)evilfox, kluchnik");

  PrintLibInit(1);
  FontPathInit((char *)fontpath, fullfont);
  SetScrollEdgeDelay(scrollDelay);
  SetFontColor((char*)fontColor,(char*)bgrColor,isOutline);
  start_again();
  return 0;
}
