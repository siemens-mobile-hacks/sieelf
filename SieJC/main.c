#include "../inc/swilib.h"
#include "../inc/cfg_items.h"
#include "..\inc\zlib.h"
#include "history.h"
#include "conf_loader.h"
#include "main.h"
#include "message_list.h"
#include "xml_parser.h"
#include "bookmarks.h"
#include "adv_login.h"
#include "jabber.h"
#include "string_util.h"
#include "jabber_util.h"
#include "groups_util.h"
#include "clist_util.h"
#include "roster_icons.h"
#include "mainmenu.h"
#include "serial_dbg.h"
#include "../inc/xtask_ipc.h"
#include "lang.h"
#include "smiles.h"
#include "vCard.h"
#include "siejc_ipc.h"


/*
(c) Kibab
(r) Rst7, MasterMind, AD, Borman99
*/

// ============= ������� ������ =============
extern const char JABBER_HOST[];
extern const unsigned int JABBER_PORT;
extern const char USERNAME[];
extern const char PATH_TO_PIC[];
extern const int IS_IP;
extern const int USE_SASL;
extern const int USE_ZLIB;

extern const unsigned int IDLE_ICON_X;
extern const unsigned int IDLE_ICON_Y;

const char RESOURCE[] = "SieJC";
const char VERSION_NAME[]= "Siemens Native Jabber Client";  // �� ������!
const char VERSION_VERS[] = "2.9.C-Z";
const char CMP_DATE[] = __DATE__;
#define TMR_SECOND 216
const unsigned long PING_INTERVAL = 3*60*TMR_SECOND; // 3 ������
#ifdef NEWSGOLD
#ifdef ELKA
  const char OS[] = "NewSGOLD_ELKA_ELF-Platform";
#else
  const char OS[] = "NewSGOLD_ELF-Platform";
#endif
#else
const char OS[] = "SGOLD_ELF-Platform";
#define SEND_TIMER
#endif

extern volatile int total_smiles;
//IPC
const char ipc_my_name[32]=IPC_SIEJC_NAME;
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;

int Is_Sounds_Enabled=1;
int Is_Vibra_Enabled=1;
char *exename2;

char Is_Compression_Enabled = 0;

const char percent_t[]="%t";
const char percent_s[]="%s";
const char empty_t[]="";
const char conference_t[]="conference";
const char png_t[]=".png";
char empty_str[]="";
char logmsg[512];

JABBER_STATE Jabber_state = JS_NOT_CONNECTED;
char My_Presence = PRESENCE_OFFLINE;

// ���� ������������� ��������� ������
char Quit_Required = 0;

int connect_state=0;
/*
0 = OffLine
1 = Socket Connected
2 = ���������� ����� ������, ������� ����� �� �������
*/

int sock=-1;

volatile int is_gprs_online=1;


GBSTMR TMR_Send_Presence; // ������� ��������
GBSTMR reconnect_tmr;
GBSTMR Ping_Timer;
#ifndef NEWSGOLD
  GBSTMR redraw_tmr;
#define Redraw_Time TMR_SECOND*5
#endif

//=============��������� �����====================

  RGBA MAINBG_NOT_CONNECTED =     {50,  50,  50, 100};
  RGBA MAINBG_CONNECTED =         {255, 255, 255, 100};
  RGBA MAINBG_ERROR =             {255,   0,   0, 100};
  RGBA MAINFONT_NOT_CONNECTED =   {200, 200, 200, 100};
  RGBA MAINFONT_CONNECTED =       {100, 100, 100, 100};
  RGBA MAINFONT_ERROR =           {255,   0,   0, 100};

//================================================

extern void kill_data(void *p, void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
//===============================================================================================
// ELKA Compatibility

//#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}


//#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
//#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}
//===============================================================================================
extern int Message_gui_ID;
int maingui_id;

void SMART_REDRAW(void)
{
  int f;
  LockSched();
  f=IsGuiOnTop(maingui_id)||IsGuiOnTop(Message_gui_ID);
  UnlockSched();
  if (f) REDRAW();
}

//===================================================================
extern const unsigned int sndVolume;

void Play(const char *fname)
{
  if ((!IsCalling())&&Is_Sounds_Enabled)
  {
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      PLAYFILE_OPT _sfo1;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);

      zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num=1;
      _sfo1.time_between_play=0;
      _sfo1.play_first=0;
      _sfo1.volume=sndVolume;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
  }
}

//===================================================================

GBSTMR tmr_vibra;
volatile int Vibra_Count;

void _start_vibra()
{
  void _stop_vibra(void);
  if(Is_Vibra_Enabled)
  {
    SetVibration(VIBRA_POWER);
    GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,_stop_vibra);
  }
}

void _stop_vibra(void)
{
  SetVibration(0);
  if (--Vibra_Count)
  {
    GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,_start_vibra);
  }
}

void Vibrate(int Req_Vibra_Count)
{
  if(!Is_Vibra_Enabled)
  {
    Vibra_Count=0;
    return;
  }
  if(Vibra_Count)return;
  Vibra_Count = Req_Vibra_Count;
  if (!IsCalling()) _start_vibra();
}

//===============================================================================================
char My_JID[128];
char My_JID_full[128];

int DNR_ID=0;
int DNR_TRIES=3;

void create_connect(void)
{
  int ***p_res=NULL;
  void do_reconnect(void);
  SOCK_ADDR sa;
  //������������� ����������
  connect_state=0;
  int can_connect=0;
  GBS_DelTimer(&reconnect_tmr);
  DNR_ID=0;
  if(!IS_IP)
  {
    snprintf(logmsg,255,"Send DNR...");
    SMART_REDRAW();
    *socklasterr()=0;
    int err=async_gethostbyname(JABBER_HOST,&p_res,&DNR_ID); //03461351 3<70<19<81
    if (err)
    {
     if ((err==0xC9)||(err==0xD6))
     {
       if (DNR_ID)
       {
  	return; //���� ���������� DNR
       }
     }
     else
     {
       snprintf(logmsg,255,"DNR ERROR %d!",err);
       SMART_REDRAW();
       GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*120,do_reconnect);
       return;
     }
   }
   if(p_res)
   {
     if(p_res[3])
     {
        snprintf(logmsg,255,"DNR Ok, connecting...");
        SMART_REDRAW();
        DNR_TRIES=0;
        sa.ip=p_res[3][0][0];
        can_connect = 1;
     }
   }
   else
   {
    DNR_TRIES--;
    LockSched();
    ShowMSG(1,(int)"Host not found!");
    UnlockSched();
    return;
  }
  }// ���� DNS
  else
  {
      snprintf(logmsg,255,"Using IP address...");
      can_connect = 1;
      sa.ip = str2ip(JABBER_HOST);
      SMART_REDRAW();
  }


  if(can_connect)
  {
    sock=socket(1,1,0);
    if (sock!=-1)
    {
        sa.family=1;
	sa.port=htons(JABBER_PORT);
	if (connect(sock,&sa,sizeof(sa))!=-1)
	{
          connect_state=1;
	  SMART_REDRAW();
	}
	else
	{
	  closesocket(sock);
	  sock=-1;
	  LockSched();
	  ShowMSG(1,(int)"Can't connect!");
	  UnlockSched();
	  GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*120,do_reconnect);
	}
      }
      else
      {
	LockSched();
	ShowMSG(1,(int)"Can't create socket, GPRS restarted!");
	UnlockSched();
	//�� ������� �������� ������, ��������� GPRS-������
	GPRS_OnOff(0,1);
      }
    }	
}

#ifdef SEND_TIMER
GBSTMR send_tmr;
#endif

static void POPUP(const char *msg)
{
  LockSched();
  ShowMSG(1,(int)msg);
  UnlockSched();
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
#ifdef SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

unsigned int virt_buffer_len = 0; // ����������� ����� ��������� ������
z_stream d_stream;                // ����� ��� ZLib
char ZLib_Stream_Init=0;          // ������� ����, ��� ��������������� ����� ������
unsigned int out_bytes_count = 0; // ���������� ������������ ������
char *Rstream_p;                  // ��������� �� ���������� �����
int Rstream_n;                    // ���������� ����

// �������-�������� ��� ZLib
void* zcalloc(int unk,size_t nelem, size_t elsize)
{
  return (malloc(nelem*elsize));
}

void zcfree(int unk, void* ptr)
{
  mfree(ptr);
}

//Context:HELPER
void get_answer(void)
{
  char rb[1024];
  int i=recv(sock,rb,sizeof(rb),0);
  int j;
  int err;
  char *p;
  int c;
  if (i<=0) return; //�������, ��� � ������, ��-��������; ������ ��� ��� ������ ���� ���������

  virt_buffer_len = virt_buffer_len + i;  // ����������� ����� ������ �����������

  if (Is_Compression_Enabled)
  {


  if(!ZLib_Stream_Init)
  {
    ZLib_Stream_Init=1;
    d_stream.zalloc = (alloc_func)zcalloc;
    d_stream.zfree = (free_func)zcfree;
    d_stream.opaque = (voidpf)0;
    err = inflateInit2(&d_stream,MAX_WBITS/*-MAX_WBITS*/);
    if(err!=Z_OK)
    {
	  char s[32];
	  sprintf(s,"inflateInit2 err %d",err);
	  POPUP(s);
      return;
    }
  }

    //���������� ZLib ��� �������� ������ � ���������� �����
    d_stream.next_in  = (Byte*)rb;
    d_stream.avail_in = (uInt)i;
    do
    {
      d_stream.next_out = (Byte*)((Rstream_p=realloc(Rstream_p,Rstream_n+i+1))+Rstream_n); //����� ������ ����������� ������
      d_stream.avail_out = (uInt)i;
      err = inflate(&d_stream, /*Z_NO_FLUSH*/Z_SYNC_FLUSH);
      switch (err)
      {
      case Z_NEED_DICT:
	//ret = Z_DATA_ERROR;     /* and fall through */
      case Z_DATA_ERROR:
      case Z_MEM_ERROR:
	//(void)inflateEnd(&strm);
	{
	  char s[32];
	  sprintf(s,"ZLib Err %d",err);
	  POPUP(s);
	}
	end_socket();
	return;
      }
      Rstream_n+=(i-d_stream.avail_out);
    }
    while(d_stream.avail_out==0);

  }
  else
  {
    memcpy((Rstream_p=realloc(Rstream_p,Rstream_n+i+1))+Rstream_n,rb,i);
    Rstream_n+=i;
  }
  //������ ������� ����
  Rstream_p[Rstream_n]=0; //��������� ������ \0 ��� ���������

  i=0; //������ �����
  j=0; //������ ������
  p=Rstream_p;
  while((p=strstr(p,"<?xml version='1.0'?>"))) {i--; p++;} //������� - ������� ���������� xml, ��� ��� ��� �����������
  p=Rstream_p;
  while((p=strstr(p,"<stream:stream"))) {i--; p++;} //������� - ������� ����� stream, ��� ��� ��� ����������� (fuckin' XMPP)

  p=Rstream_p;

  while((c=*p++))
  {
    if (c=='<')
    {
      j++;
      if (*p!='/') i++; else i--;
    }

    // �������� �� �������� ����: <tag/>
    if(c=='>' && (char) *(p-2) == '/')
    {
      i--;
      goto L_END;
    }

    if (c=='>')
    {
    L_END:
      j--;
      if ((!i)&&(!j))
      {
        //������� ������, ������ �� ���������
	int bytecount=p-Rstream_p;
	IPC_BUFFER* tmp_buffer=malloc(sizeof(IPC_BUFFER)); // ���� ���������
	memcpy(tmp_buffer->xml_buffer=malloc(bytecount),Rstream_p,tmp_buffer->buf_size=bytecount); // ����� � ���������
	memcpy(p=Rstream_p,Rstream_p+bytecount,(Rstream_n-=bytecount)+1); //����������� � ������ � ������ \0
	GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,tmp_buffer,sock); //���������� ������� ����
      }
    }
  }
}

int sendq_l=0;        // ������ ������� ��� send
char *sendq_p=NULL;   // ��������� �������

void ClearSendQ(void)
{
  if(sendq_p)mfree(sendq_p);
  sendq_p=NULL;
  sendq_l=NULL;
#ifdef SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

#ifdef SEND_TIMER
static void resend(void)
{
  void bsend(int len, void *p);
  SUBPROC((void*)bsend,0,0);
}
#endif

//��������������� ������� � �����, c ����������� ������������� ���������
void bsend(int len, void *p)
{
  int i;
  int j;
  if (connect_state<1) return;
  if (p)
  {
    //���������, �� ���� �� �������� � �������
    if (sendq_p)
    {
      //���� �������, ��������� � ���
      memcpy((sendq_p=realloc(sendq_p,sendq_l+len))+sendq_l,p,len);
      //mfree(p);
      sendq_l+=len;
      return;
    }
    //������� ������� ��������
    memcpy(sendq_p=malloc(len),p,sendq_l=len);
  }
  //���������� ��� ������������ � �������
  while((i=sendq_l)!=0)
  {
    if (i>0x400) i=0x400;
    j=send(sock,sendq_p,i,0);
    if (j<0)
    {
      j=*socklasterr();
      if ((j==0xC9)||(j==0xD6))
      {
	return; //������, ���� ����� ��������� ENIP_BUFFER_FREE
      }
      else
      {
	//������
	LockSched();
	ShowMSG(1,(int)"Send error!");
	UnlockSched();
	end_socket();
	return;
      }
    }
    memcpy(sendq_p,sendq_p+j,sendq_l-=j); //������� ����������
    if (j<i)
    {
      //�������� ������ ��� ����������
#ifdef SEND_TIMER
      GBS_StartTimerProc(&send_tmr,216*5,resend);
#endif
      return; //���� ��������� ENIP_BUFFER_FREE1
    }
  }
  mfree(sendq_p);
  sendq_p=NULL;
}

void SendAnswer(char *str)
{
  unsigned int block_len= strlen(str);
  out_bytes_count += block_len;
  //#ifdef LOG_ALL
  //  Log("OUT->", str);
  //#endif

  if(!Is_Compression_Enabled)
  {
    bsend(block_len,str);
  }
  else
  {
    // �������� ���������� ;)
    // ����� ��������� "�����"
#pragma pack(1)
    struct
    {
      char zero;
      unsigned short len;
      unsigned short notlen;
    };
#pragma pack()
    zero=0;
    len=block_len;
    notlen=~block_len;
    bsend(5,&zero);
    out_bytes_count+=5;
    // ��������, ����� ��� ����
    bsend(block_len,str);
  }
}

void SendPing()
{
  //ShowMSG(1,(int)"Ping:)");
  GBS_StartTimerProc(&Ping_Timer,PING_INTERVAL,SendPing);
  if(Jabber_state!=JS_ONLINE)return;
  if(sendq_l)return;
  static char ping_str[]=" ";
  SUBPROC((void*)SendAnswer,ping_str);
}

char Support_Compression = 0;
char Support_MD5_Auth = 0;
char Support_Plain_Auth = 0;
char Support_Resource_Binding = 0;

void Analyze_Stream_Features(XMLNode *nodeEx)
{
  strcat(logmsg, "\nGetting features...");
  XMLNode *Compr_feature = XML_Get_Child_Node_By_Name(nodeEx, "compression");
  if(Compr_feature)
  {
    Support_Compression = 1;
    strcat(logmsg, "\nCompression:  +");
  }

  XMLNode *Res_Binding_feature = XML_Get_Child_Node_By_Name(nodeEx, "bind");
  if(Res_Binding_feature)
  {
    Support_Resource_Binding = 1;
    strcat(logmsg, "\nResBind:       +");
  }

  XMLNode *Auth_Methods = XML_Get_Child_Node_By_Name(nodeEx, "mechanisms");
  if(Auth_Methods)
  {
    XMLNode *Ch_Node=XML_Get_Child_Node_By_Name(Auth_Methods, "mechanism");
    while(Ch_Node)
    {
      if(!strcmp(Ch_Node->value, "DIGEST-MD5"))
      {
        Support_MD5_Auth = 1;
        strcat(logmsg, "\nDIGEST-MD5:  +");
      }
      if(!strcmp(Ch_Node->value, "PLAIN"))
      {
        Support_Plain_Auth = 1;
        strcat(logmsg, "\nPLAIN:  +");
      }
      Ch_Node = Ch_Node->next;
    }
  }
  SMART_REDRAW();
}


/*
    ����������� ������� ������������� XML-������
*/
void Process_Decoded_XML(XMLNode* node)
{
  XMLNode* nodeEx = node;
  while(nodeEx)
  {

//----------------
    if(!strcmp(nodeEx->name,"stream:features"))
    {
      Analyze_Stream_Features(nodeEx);
      if(USE_ZLIB && Support_Compression && Jabber_state == JS_NOT_CONNECTED)Compression_Ask();
      if(Jabber_state == JS_NOT_CONNECTED || Jabber_state==JS_ZLIB_STREAM_INIT_ACK)
      if(Support_MD5_Auth)
      {
        SUBPROC((void*)Use_Md5_Auth_Report);
      }
      else
      if(Support_Plain_Auth)
      {
        SUBPROC((void*)Use_Plain_Auth_Report);
      }
      else
      {
        strcat(logmsg, "\nERROR:  No supported auth methods!");
      }

      if(Support_Resource_Binding && Jabber_state == JS_SASL_NEW_STREAM_ACK)SASL_Bind_Resource();
    }

//----------------

    if(!strcmp(nodeEx->name,"compressed") && Jabber_state == JS_ZLIB_INIT_ACK)
    {
      Compression_Init_Stream();
    }

//----------------
    if(!strcmp(nodeEx->name,"success")&& Jabber_state == JS_SASL_AUTH_ACK)
    {
      SASL_Open_New_Stream();
    }

//----------------
    if(!strcmp(nodeEx->name,"failure")&& Jabber_state < JS_AUTH_OK)
    {
      SASL_Process_Error(nodeEx);
      SUBPROC((void*)end_socket);
    }

//----------------
    if(!strcmp(nodeEx->name,"challenge")&& Jabber_state == JS_SASL_NEG_ANS_WAIT)
    {
      Process_Auth_Answer(nodeEx->value);
    }
//----------------
    if(!strcmp(nodeEx->name,"challenge")&& Jabber_state == JS_SASL_NEGOTIATION)
    {
      Decode_Challenge(nodeEx->value);
      Send_Login_Packet();
    }

//----------------
    if(!strcmp(nodeEx->name,"message"))
    {
      Process_Incoming_Message(nodeEx);
    }
//----------------
    if(!strcmp(nodeEx->name,"iq"))
    {
      Process_Iq_Request(nodeEx);
    }
//----------------
    if(!strcmp(nodeEx->name,"stream:stream"))
    {
      connect_state = 2;
      // ���� �� ���������� SASL-�����������, ����� ������� ����� �����������
      if(!USE_SASL)
      {
        Jabber_state = JS_CONNECTED_STATE;
        SUBPROC((void*)Send_Auth);
      }
      else
        if(nodeEx->subnode)
        {
          Process_Decoded_XML(nodeEx->subnode);
          return;
        }
    }
//----------------
    if(!strcmp(nodeEx->name,"stream:error"))
    {
      connect_state = 0;
      SMART_REDRAW();
      Jabber_state = JS_ERROR;
      char err[]="������ XML-������";
      MsgBoxError(1,(int)err);
      sprintf(logmsg, err);
      SUBPROC((void*)end_socket);
    }
//----------------
    if(!strcmp(nodeEx->name,"presence"))
    {
      Process_Presence_Change(nodeEx);
    }
//----------------

    //if(nodeEx->subnode) Process_Decoded_XML(nodeEx->subnode);
    nodeEx = nodeEx->next;
  }

}

void __log(char* buffer, int size)
{
  char mess[20];
  sprintf(mess,"RECV:%d",size);
#ifdef LOG_TO_COM_PORT
  tx_str(buffer);
#else
  Log(mess,buffer);
#endif
  mfree(buffer);
}

void Process_XML_Packet(IPC_BUFFER* xmlbuf)
{
  // ���� ��������, ���� �� ����������� ������ ��������� �� ������ ������
  LockSched();
  XMLNode *data=XMLDecode(xmlbuf->xml_buffer,xmlbuf->buf_size);
  UnlockSched();

// ���� ���� �� �������� ����������� ���� ������, ��� ����� � ���� ����� ����
// ������� �������� �����, � ����� ������������ ��������
#ifdef LOG_IN_DATA
    char* tmp_buf=malloc(xmlbuf->buf_size+1);
    zeromem(tmp_buf,xmlbuf->buf_size+1);
    memcpy(tmp_buf,xmlbuf->xml_buffer,xmlbuf->buf_size);
    SUBPROC((void*)__log,tmp_buf, xmlbuf->buf_size);
#endif


  if(data)
  {
#ifdef LOG_XML_TREE
    SaveTree(data);
#endif
    Process_Decoded_XML(data);
    DestroyTree(data);
  }

  // ����������� ������ :)
    mfree(xmlbuf->xml_buffer);
    mfree(xmlbuf);
#ifdef NEWSGOLD
    SMART_REDRAW();
#else
#endif
}


//===============================================================================================
// ������ ����� � GUI

RECT ConnPopupRC;
RECT ConnLogRC;
RECT ConnHeaderRC;

void InitConnPopup()
{

}

void DrawConnect()
{

}


void onRedraw(MAIN_GUI *data)
{
  int scr_w=ScreenW();
  int scr_h=ScreenH();

  RGBA font_color, bgr_color;
  if(connect_state<2)
  {
    font_color= MAINFONT_NOT_CONNECTED;
    bgr_color = MAINBG_NOT_CONNECTED;
  }
  if(connect_state==2)
  {
    font_color = MAINFONT_CONNECTED;
    bgr_color = MAINBG_CONNECTED;
  }

  if(Jabber_state==JS_AUTH_ERROR || Jabber_state==JS_ERROR)
  {
    font_color = MAINFONT_ERROR;
    bgr_color  = MAINBG_ERROR;
  }
  DrawRoundedFrame(0,SCR_START,scr_w-1,scr_h-1,0,0,0,
		   0,
		   color(bgr_color));

  CList_RedrawCList();

  LockSched();

  if (CList_GetUnreadMessages()>0) {
    wsprintf(data->ws1,"%d(%d/%d) IN:%d",CList_GetUnreadMessages(), CList_GetNumberOfOnlineUsers(),CList_GetNumberOfUsers(),virt_buffer_len);
  } else {
    wsprintf(data->ws1,"(%d/%d) IN:%d",CList_GetNumberOfOnlineUsers(),CList_GetNumberOfUsers(),virt_buffer_len);
  }
  UnlockSched();

  //������ ����-������
#ifdef USE_PNG_EXT
char mypic[128];

  if (CList_GetUnreadMessages()>0)
    Roster_getIconByStatus(mypic,50); //������ ���������
  else
    Roster_getIconByStatus(mypic, My_Presence);
  Roster_DrawIcon(1, SCR_START+1, (int)mypic);
  DrawString(data->ws1,Roster_getIconWidth(mypic)+2,SCR_START+3,scr_w-4,scr_h-4-16,FONT_SMALL,0,color(font_color),0);

#else
  int img_num=0;
  if (CList_GetUnreadMessages()>0)
    img_num=Roster_getIconByStatus(50); //������ ���������
  else
    img_num=Roster_getIconByStatus(My_Presence);

  Roster_DrawIcon(1, SCR_START+1, img_num); //������ ���������
  DrawString(data->ws1,Roster_getIconWidth(img_num)+2,SCR_START+3,scr_w-4,scr_h-4-16,FONT_SMALL,0,color(font_color),0);
#endif

  if(Jabber_state!=JS_ONLINE)
  {
    wsprintf(data->ws1,"%t", logmsg);
    if (total_smiles)
     {
       wstrcatprintf(data->ws1,"\nLoaded %d smiles",total_smiles);
     }
    DrawString(data->ws1,1,SCR_START+3+GetFontYSIZE(FONT_SMALL)+2,scr_w-4,scr_h-4-16,FONT_SMALL,0,color(font_color),0);
  }

  //DrawString(data->ws2,3,13,scr_w-4,scr_h-4-16,SMALL_FONT,0,GetPaletteAdrByColorIndex(font_color),GetPaletteAdrByColorIndex(23));

#ifdef USE_PNG_EXT

  if(connect_state<2)
  {
    char logo_path[128];
    strcpy(logo_path, PATH_TO_PIC);
    strcat(logo_path,"SieJC_logo.png");
    DrawImg(0,70,(int)logo_path);
  }
#endif
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}


void QuitCallbackProc(int decision)
{
  if(!decision)Quit_Required = 1;
}

void DisplayQuitQuery()
{
  MsgBoxYesNo(1,(int)LG_EXITSIEJC,QuitCallbackProc);
}

void Enter_SiepatchDB()
{

  char room[]= "siepatchdb@conference.jabber.ru";
  char nick_t[]="%s_SieJC";
  char nick[100];
  sprintf(nick, nick_t, USERNAME);
//  char nick[]="Kibab_exp";

  char *room_nick =ANSI2UTF8(nick, strlen(nick)*2);
  char* room_name = ANSI2UTF8(room, strlen(room)*2);
  Enter_Conference(room, nick, 20);
  mfree(room_nick);
  mfree(room_name);
}

void Disp_State()
{
  char q[80];
  sprintf(q,"Jabber_state=%d\nOut bytes: %d\nSend query len: %d", Jabber_state, out_bytes_count, sendq_l);
  ShowMSG(0,(int)q);
}

// ���������������
void Do_Reconnect()
{
  extern TRESOURCE* ActiveContact;
  extern unsigned int NContacts;
  extern unsigned int N_Disp_Contacts;
  extern unsigned int Active_page;
  extern unsigned int N_cont_disp;
  extern unsigned int CursorPos;

  // ���������� ��� �������
        ClearSendQ();
        GBS_DelTimer(&Ping_Timer);
        GBS_DelTimer(&TMR_Send_Presence);
#ifndef NEWSGOLD
        GBS_DelTimer(&redraw_tmr);
#endif
        GBS_DelTimer(&reconnect_tmr);
        SetVibration(0);

        // ��-������������� �������-�����
/*
        ActiveContact = NULL;
        NContacts = 0;
        N_Disp_Contacts = 0;
        N_cont_disp=0;
*/
        Active_page = 1;
        CursorPos = 1;

        // ����������� ������� CL, MUC, ��������, �����, ������� SASL
        LockSched();
//        CList_Destroy();
//        KillGroupsList();
        MUCList_Destroy();
        CList_MakeAllContactsOFFLINE();
        KillBMList();
        UnlockSched();

        virt_buffer_len = 0;
        Destroy_SASL_Ctx();

        // ��-������������� ������
        if(ZLib_Stream_Init)
        {
          inflateEnd(&d_stream);
          zeromem(&d_stream, sizeof(z_stream));
          virt_buffer_len = 0;
          ZLib_Stream_Init=0;
          Is_Compression_Enabled = 0;
          out_bytes_count = 0; // ���������� ������������ ������
          Rstream_n = 0;
          Rstream_p = NULL;
        }

        // �������� ������ ������
        //InitGroupsList();


	DNR_TRIES=3;
        SUBPROC((void *)create_connect);
}


#ifndef NEWSGOLD
volatile char IsRedrawTimerStarted=0;

void SGOLD_RedrawProc()
{
  DirectRedrawGUI();
  extern void SGOLD_RedrawProc(void);
  GBS_StartTimerProc(&redraw_tmr, Redraw_Time, SGOLD_RedrawProc);
}

void SGOLD_RedrawProc_Starter()
{
  if(IsRedrawTimerStarted)return;
  IsRedrawTimerStarted=1;
  SGOLD_RedrawProc();//GBS_StartTimerProc(&redraw_tmr, Redraw_Time, (void*)SGOLD_RedrawProc);
}
#endif

int onKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if(Quit_Required)return 1; //���������� ����� GeneralFunc ��� ���. GUI -> �������� GUI
#ifndef NEWSGOLD
  SGOLD_RedrawProc_Starter();
#endif
  //DirectRedrawGUI();
  if(msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
    case DOWN_BUTTON:
    case '8':
      {
        CList_MoveCursorDown();
        break;
      }

    case UP_BUTTON:
    case '2':
      {
        CList_MoveCursorUp();
        break;
      }
    case '#':
      {
        gipc.name_to=ipc_xtask_name;
        gipc.name_from=ipc_my_name;
        gipc.data=0;
        GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
        if (IsUnlocked())
        {
          KbdLock();
        }
      return(-1);
    }
    case '*':
      {
        gipc.name_to=ipc_xtask_name;
        gipc.name_from=ipc_my_name;
        gipc.data=0;
        GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
        Is_Vibra_Enabled=!Is_Vibra_Enabled;
      }
    }
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {

    case ENTER_BUTTON:
      {
          LockSched();
          extern CLIST *cltop;
          CLIST* ClEx = cltop;
          CLIST* ActiveContact = NULL;
          char *gjid=CList_GetActiveContact()->full_name;
          while(ClEx)
          {
            if(stristr(gjid,ClEx->JID)==gjid) ActiveContact = ClEx;
            ClEx = ClEx->next;
          }
          UnlockSched();
        if (ActiveContact)
        {
          if(ActiveContact->res_list->entry_type!=T_GROUP)
          {
            Display_Message_List(CList_GetActiveContact());
          }
            else
          {
            //ActiveContact->IsVisible = ActiveContact->IsVisible==1?0:1;
            CList_ToggleVisibilityForGroup(ActiveContact->group);
            SMART_REDRAW();
          }
        }
        break;
      }

    case LEFT_SOFT:
      {
        MM_Show();
        break;
      }
#ifndef NEWSGOLD
    case RED_BUTTON:
#endif
    case RIGHT_SOFT:
      {
        DisplayQuitQuery();
        break;
      }
    case GREEN_BUTTON:
      if ((connect_state==0)&&(sock==-1))
      {
        Do_Reconnect();
      }

      if(connect_state==2 && Jabber_state==JS_ONLINE && CList_GetActiveContact()->entry_type!=T_GROUP)
      {
        Init_Message(CList_GetActiveContact(), NULL);
      }

      break;

    case '1':
      {
        CList_MoveCursorHome();
        break;
      }

    case '4':
      {
        Enter_SiepatchDB();
        break;
      }
    case '5':
      {
        CList_Display_Popup_Info(CList_GetActiveContact());
        break;
      }

    case '6':
      {
        Disp_State();
        break;
      }

    case '7':
      {
        /*
        char xz[] = "Test";
        char xz_jid[] = "test@j.ru";
        char xz_jid_full[] = "test@j.ru/QQQ";
        char xz_status_msg[]="Fucking with GPRS";
        CList_AddContact(xz,xz_jid, SUB_BOTH, 0, 0);
        CList_AddResourceWithPresence(xz_jid_full, PRESENCE_CHAT, xz_status_msg);
        */
        SUBPROC((void *)end_socket);
        break;
      }

    case DOWN_BUTTON:
    case '8':
      {
        CList_MoveCursorDown();
        break;
      }

    case UP_BUTTON:
    case '2':
      {
        CList_MoveCursorUp();
        break;
      }


    case '9':
      {
        CList_MoveCursorEnd();
        break;
      }

    case '0':
      {

        CList_ToggleOfflineDisplay();
        break;
      }

    case '*':
      {
        Is_Vibra_Enabled=!(Is_Vibra_Enabled);
        break;
      }
    case '#': //�������� ������ ����� ��������������
      {
        nextUnread();
        break;
      }
    }
  }
  //  onRedraw(data);
  return(0);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)onRedraw,	//SMART_REDRAW
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)onKey,	//OnKey
  0,
  (void *)kill_data, //onDestroy,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  maingui_id=csm->gui_id=CreateGUI(main_gui);
  DNR_TRIES=3;
  InitGroupsList();

  //SUBPROC((void *)InitSmiles);
  SUBPROC((void *)create_connect);
  GBS_StartTimerProc(&Ping_Timer,PING_INTERVAL,SendPing);
#ifdef LOG_ALL
  // ��������� ������ ��������� ��������, �� ������,
  // ���� ������ ����� ������ - ��� ����� ���� ������...
  void* Process_XML_Packet_ADR = (void*)Process_XML_Packet;
  void* Process_Decoded_XML_ADR = (void*) Process_Decoded_XML;
  char msg[80];
  sprintf(msg,"@Process_XML_Packet=0x%X, @Process_Decoded_XML=0x%X\r\n",Process_XML_Packet_ADR, Process_Decoded_XML_ADR);
  Log("SYSTEM", msg);
#endif
}

extern const int DEF_SOUND_STATE;
extern const int DEF_VIBRA_STATE;
extern const int DEF_SHOW_OFFLINE;
extern char Display_Offline;

void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&tmr_vibra);
  GBS_DelTimer(&Ping_Timer);
  GBS_DelTimer(&TMR_Send_Presence);
#ifndef NEWSGOLD
  GBS_DelTimer(&redraw_tmr);
#endif
  GBS_DelTimer(&reconnect_tmr);

  SetVibration(0);

  extern ONLINEINFO OnlineInfo;
  if(OnlineInfo.txt)mfree(OnlineInfo.txt);
  CList_Destroy();
  MUCList_Destroy();
  KillBMList();
  KillGroupsList();
  Destroy_SASL_Ctx();

  if(ZLib_Stream_Init)
  {
    inflateEnd(&d_stream);
  }

  *((int *)&DEF_SOUND_STATE)=Is_Sounds_Enabled;
  *((int *)&DEF_VIBRA_STATE)=Is_Vibra_Enabled;
  *((int *)&DEF_SHOW_OFFLINE)=Display_Offline;

  SaveConfigData(successed_config_filename);

  SUBPROC((void *)FreeSmiles);
  SUBPROC((void *)end_socket);
  SUBPROC((void *)ClearSendQ);
  SUBPROC((void *)ElfKiller);
}

void do_reconnect(void)
{
  if (is_gprs_online)
  {
    DNR_TRIES=3;
    SUBPROC((void*)create_connect);
  }
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  {
    //IPC
    if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      if ((ipc=(IPC_REQ*)msg->data0))
      {
	if (stricmp(ipc->name_to,ipc_my_name)==0)//strcmp_nocase
	{
	  switch (msg->submess)
	  {
	  case IPC_SMILE_PROCESSED:
	    //������ ����������� ������ ;)
	    if (ipc->name_from==ipc_my_name) SUBPROC((void *)ProcessNextSmile);
	    SMART_REDRAW();
	    break;
          case IPC_AVATAR_DECODE_OK:
            vCard_Photo_Display(ipc->data);
            break;
	  }
	}
      }
    }

#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id))
    {
      GUI *igui=GetTopGUI();
      if (igui) //� �� ����������
      {
	#ifdef ELKA
	  {
	void *canvasdata=BuildCanvas();
	#else
	  void *idata=GetDataOfItemByID(igui,2);
	  if (idata)
	  {
	    void *canvasdata=((void **)idata)[DISPLACE_OF_IDLECANVAS/4];
	#endif

#ifdef USE_PNG_EXT
char mypic[128];

  if (CList_GetUnreadMessages()>0)
     Roster_getIconByStatus(mypic,50); //������ ���������
  else
    Roster_getIconByStatus(mypic, My_Presence);
          DrawCanvas(canvasdata,IDLE_ICON_X,IDLE_ICON_Y,IDLE_ICON_X+GetImgWidth((int)mypic)-1,IDLE_ICON_Y+GetImgHeight((int)mypic)-1,1);
	  DrawImg(IDLE_ICON_X,IDLE_ICON_Y,(int)mypic);
#else
          int mypic=0;
          if (CList_GetUnreadMessages()>0)
            mypic=Roster_getIconByStatus(50); //������ ���������
          else
            mypic=Roster_getIconByStatus(My_Presence);
          DrawCanvas(canvasdata,IDLE_ICON_X,IDLE_ICON_Y,IDLE_ICON_X+GetImgWidth(mypic)-1,IDLE_ICON_Y+GetImgHeight(mypic)-1,1);
	  DrawImg(IDLE_ICON_X,IDLE_ICON_Y,mypic);
#endif
	//#ifdef ELKA
	//#else
	  //}
	//#endif
	}
      }
    }
  }
  if(Quit_Required)
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    int id;
    if ((id=((int)msg->data0))==csm->gui_id)
    {
      csm->csm.state=-3;
    }
    if (id==Message_gui_ID) Message_gui_ID=0;
  }
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    switch((int)msg->data0)
    {
    case LMAN_DISCONNECT_IND:
      is_gprs_online=0;
      return(1);
    case LMAN_CONNECT_CNF:
      is_gprs_online=1;
      return(1);
    case ENIP_DNR_HOST_BY_NAME:
      if ((int)msg->data1==DNR_ID)
      {
	if (DNR_TRIES) SUBPROC((void *)create_connect);
      }
      return(1);
    }
    if ((int)msg->data1==sock)
    {
      //���� ��� �����
      if ((((unsigned int)msg->data0)>>28)==0xA)
      {
        //����� XML-������ ����� � ��������� � ��������� �� ��������� � ��������� MMI
        Process_XML_Packet((IPC_BUFFER*)msg->data0);
        return(0);
      }
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
        if (connect_state==1)
        {
          //���������� �����������, �������� ����� Welcome
          SUBPROC((void*)Send_Welcome_Packet);
          SMART_REDRAW();
        }
        else
        {
          ShowMSG(1,(int)"Illegal message ENIP_SOCK_CONNECTED!");
        }
        break;
      case ENIP_SOCK_DATA_READ:
        if (connect_state>=1)
        {
          //���� �������� Welcome, ������� �� �������� � �������� HELPER
          SUBPROC((void *)get_answer);
        }
        else
        {
          ShowMSG(1,(int)"Illegal message ENIP_DATA_READ");
        }
        break;
      case ENIP_BUFFER_FREE:
      case ENIP_BUFFER_FREE1:
	  //�������� �������
	SUBPROC((void *)bsend,0,0);
	break;
      case ENIP_SOCK_REMOTE_CLOSED:
        //������ �� ������� �������
        if (connect_state) SUBPROC((void *)end_socket);
        break;
      case ENIP_SOCK_CLOSED:
	SUBPROC((void *)ClearSendQ);
        if(ZLib_Stream_Init)
        {
          inflateEnd(&d_stream);
        }
        connect_state=0;
        Jabber_state = JS_NOT_CONNECTED;
        sock=-1;
        Vibrate(4);
        SMART_REDRAW();
        GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,Do_Reconnect);
        break;
      }
    }
  }
  return(1);
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
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"SieJC",ws);
  FreeWS(ws);
}

// ��������, ��� ��������� ��� ���������� ������� ���������

unsigned short IsGoodPlatform()
{
#ifdef NEWSGOLD
  return  isnewSGold();
#else
  return  !isnewSGold();
#endif
}

Check_Settings_Cleverness()
{
  if(!USE_SASL && USE_ZLIB)ShowMSG(0,(int)LG_ZLIBNOSASL);
}

int main(char *exename, char *fname)
{
 exename2=exename;
  if(!IsGoodPlatform())
  {
    ShowMSG(1,(int)LG_PLATFORMM);
    return 0;
  }
  char dummy[sizeof(MAIN_CSM)];
  InitConfig(fname);
  if(!strlen(USERNAME))
  {
    ShowMSG(1,(int)LG_ENTERLOGPAS);
    return 0;
  }

   Is_Sounds_Enabled=DEF_SOUND_STATE;
   Is_Vibra_Enabled=DEF_VIBRA_STATE;
   Display_Offline=DEF_SHOW_OFFLINE;

  UpdateCSMname();

  LockSched();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();

  Check_Settings_Cleverness();
  return 0;
}
