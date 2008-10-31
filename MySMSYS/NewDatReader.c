#include "..\inc\swilib.h"
#include "config_data.h"
#include "sms_dat.h"
#include "language.h"

#define MAX_SMS 100
typedef struct
{
  char unk0;
  char unk1;
  unsigned short index_id; //0xFFFF, no
  char num[12]; //hex, num[0],len
  short txt_len;
  short w_char[7]; //
  char unk2;
  char unk3;
  short unk_0x160F;
  char unk4[8];
  int opmsg_id;
  unsigned short data_id;//SMS: (data_id-0x2A)*sizeof(PDU)= the position of this sms in sms.dat, EMS: 0xFFF4 ?
  short unk5; //0xA800 ?
}EMS_ADM;

void Add2WS_NEW(char *data, unsigned short *wsbody, int len)
{
  int i;
  char *p=(char *)wsbody;
  for(i=0;i<len;i+=2)
  {
    p[i+2]=data[i+1];
    p[i+3]=data[i];
  }
  wsbody[0]=len/2;
}

int PduDecodeTxt(SMS_DATA *sd, char *data) //0: fail, 1: successful, //2: unktype
{
  int c;
  int ttype;
  int isplus, wlen, isems, skip;
  char *p;
  WSHDR *ws, wsn, *wst;
  unsigned short wsb[150];
  ws=CreateLocalWS(&wsn, wsb, 150);
  p=data;
  if(*p++!=0x11)
    return 0;
  if(*p++!=0x11)
    return 0;
  c=*p++;
  if(!c)
    return 0;
  c=*p++; //sms center
  p+=c;
  c=*p++;
  if((c>>4)%2) isplus=1;
  else isplus=0;
  if((c>>6)%2) isems=1;
  else isems=0;
  if((sd->type==TYPE_OUT)||(sd->type==TYPE_DRAFT)) //out
  {
    p++;
  }
  c=*p++;
  if(c)
  {
    if(c%2)
      c=c/2+2;
    else
      c=c/2+1;
  }
  else
  {
    c=1;
    //sd->Number[0]=0;
  }
  p+=c+1; //num
  ttype=*p++;
  if((sd->type==TYPE_IN_R)||(sd->type==TYPE_IN_N))
  {
    p+=7; //time
  }
  if(isplus&&((sd->type==TYPE_OUT)||(sd->type==TYPE_DRAFT))) p++; //
  c=*p++;
  //...text,
  if(isems)
  {
    skip=*p;
    if(ttype==8)
    {
      p+=skip+1;
      c-=skip+1;
    }
  }
  if(ttype==0x8)
  {
    Add2WS_NEW(p, ws->wsbody, c);
  }
  else if(ttype==0x0) //7bit
  {
    GSMTXT_Decode(ws,(void*)p,c*7/8+1, ttype, (void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
    if(wstrlen(ws)>c)
    {
      CutWSTR(ws, c);
    }
  }
  else 
  {
    wsprintf(ws, STR_UNK_TXTT, ttype);
  }
  wst=sd->SMS_TEXT;
  wlen=wstrlen(ws);
  if(wlen)
  {
    if(wst)
    {
      wlen+=wstrlen(wst);
      sd->SMS_TEXT=AllocWS(wlen);
      wstrcpy(sd->SMS_TEXT, wst);
      wstrcat(sd->SMS_TEXT, ws);
      FreeWS(wst);
    }
    else
    {
      sd->SMS_TEXT=AllocWS(wlen);
      wstrcpy(sd->SMS_TEXT, ws);
    }
  }
  return 1;
}

void DoMsgReport(SMS_DATA *sd, char *data, WSHDR *ws)
{
  char time[32];
  int status, i;
  char *pp=time, *p=data;
  for(i=0;i<6;i++) //time
  {
    *pp++=p[i]%0x10+'0';
    *pp++=p[i]/0x10+'0';
    if(i<2)
      *pp++='-';
    if(i==2)
      *pp++=' ';
    if(i>2&&i<5)
      *pp++=':';
  }
  *pp=0;
  p+=7; //time 
  status=*p;
  if(status==0)
    wsprintf(ws, "%t\r%t: 20%s", lgp.LGP_MSG_REPORT, lgp.LGP_MSG_REVEICED, time);
  else
    wsprintf(ws, "%t\r%t: 20%s\r%s (%d)!", lgp.LGP_MSG_REPORT, lgp.LGP_TIME, time, lgp.LGP_UNK_RP_STATUS, status);
}
int PduDecodeAll(SMS_DATA *sd, char *data) //0: fail, 1: successful, //2: unktype
{
  int c;
  int ttype, wlen;
  int isplus, isems, skip, isreport=0;
  char *p;
  WSHDR *ws, wsn;
  unsigned short wsb[150];
  ws=CreateLocalWS(&wsn, wsb, 150);
  p=data;
  if(*p++!=0x11)
    return 0;
  if(*p++!=0x11)
    return 0;
  c=*p++;
  if(!c)
    return 0;
  switch(c)
  {
  case 0x01:
    sd->type=TYPE_IN_R;
    break;
  case 0x03:
    sd->type=TYPE_IN_N;
    break;
  case 0x05:
    sd->type=TYPE_OUT;
    break;
  case 0x07:
    sd->type=TYPE_DRAFT;
    break;
  default:
    sd->type=TYPE_UNK;
    wsprintf(ws, STR_UNK_TYPE, c);
    goto TEND;
    //return 2; //back 
  }
  c=*p++; //sms center
  p+=c;
  c=*p++;
  if(c==0x6)
  {
    isreport=1;
    p++;
  }
  if((c>>4)%2) isplus=1;
  else isplus=0;
  if((c>>6)%2) isems=1;
  else isems=0;
  if((sd->type==TYPE_OUT)||(sd->type==TYPE_DRAFT)) //out
  {
    p++;
  }
  c=*p++;
  if(c)
  {
    if(c%2)
      c=c/2+2;
    else
      c=c/2+1;
    Hex2Num(p, sd->Number, c);
  }
  else
  {
    c=1;
    sd->Number[0]=0;
  }
  if(isreport)
    p+=c;
  else
  {
    p+=c+1; //num
    ttype=*p++;
  }
  if((sd->type==TYPE_IN_R)||(sd->type==TYPE_IN_N))
  {
    char *pp=sd->Time;
    int i;
    for(i=0;i<6;i++) //time
    {
      *pp++=p[i]%0x10+'0';
      *pp++=p[i]/0x10+'0';
      if(i<2)
	*pp++='-';
      if(i==2)
	*pp++=' ';
      if(i>2&&i<5)
	*pp++=':';
    }
    *pp=0;
    p+=7; //time
  }
  if(isreport)
  {
    sd->msg_type=ISREPORT;
    DoMsgReport(sd, p, ws);
    goto TEND;
  }
  if(isplus&&((sd->type==TYPE_OUT)||(sd->type==TYPE_DRAFT))) p++; //
  c=*p++;
  //...text,
  if(isems)
  {
    skip=*p;
    if(ttype==8)
    {
      p+=skip+1;
      c-=skip+1;
    }
  }
  if(ttype==0x8)
  {
    Add2WS_NEW(p, ws->wsbody, c);
  }
  else if(ttype==0x0) //7bit
  {
    GSMTXT_Decode(ws,(void*)p,c*7/8+1, ttype, (void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
    if(wstrlen(ws)>c)
    {
      CutWSTR(ws, c);
    }
  }
  else 
  {
    wsprintf(ws, STR_UNK_TXTT, ttype);
  }
TEND:
  wlen=wstrlen(ws);
  if(!wlen)
    wlen=1;
  sd->SMS_TEXT=AllocWS(wlen);
  wstrcpy(sd->SMS_TEXT, ws);
  return 1;
}

int DoMsgList(SMS_DATA_LIST *lst, char *sms_buf, char *ems_admin_buf, int sms_size, int ems_admin_size)
{
  extern void AddToSdlByTime(SMS_DATA *sd);
  extern void FreeSdOne(SMS_DATA *sd);
  SMS_POS_INDEX_DATA sid;
  SMS_DATA *sdx;
  char *sms_buf_end=sms_buf+sms_size-sizeof(PDU);
  char *ems_admin_buf_end=ems_admin_buf+ems_admin_size-sizeof(EMS_ADM);
  EMS_ADM *pea;
  INDEX_ID_DATA *idd;
  short *pid;
  char *pd;
  int cnt, index, i, res=0;
  if(!(idd=lst->index_id_data))
    return 0;
  if(!(pid=idd->data_id))
    return 0;
  if(!(cnt=idd->cnt_received))
    return 0;
  if(cnt!=idd->cnt_all)
    return 0;
  index=idd->index;
  if(!index || index>MAX_SMS)
    return 0;
  pea=(EMS_ADM *)(ems_admin_buf+(index-1)*sizeof(EMS_ADM));
  if(pea>(EMS_ADM *)ems_admin_buf_end)
    return 0;
  if(pea->data_id != 0xFFF4) //sms
  {
    if(cnt!=1) //¶ÌÐÅÌõÊý
      return res;
    if(!GetSmsPosIndex(&sid, pid[0]))
      return res;
    if((pd=sms_buf+sid.pos_index*sizeof(PDU))>sms_buf_end)
      return res;
    sdx=AllocSD();
    if(PduDecodeAll(sdx, pd))
    {
      res++;
      sdx->opmsg_id=pea->opmsg_id;
      sdx->id=index;
      LockSched();
      AddToSdlByTime(sdx);
      UnlockSched();
    }
    else
      FreeSdOne(sdx);
  }
  else //ems
  {
    sdx=AllocSD();
    for(i=0;i<cnt;i++)
    {
      if(!GetSmsPosIndex(&sid, pid[i]))
	break;
      if((pd=sms_buf+sid.pos_index*sizeof(PDU))>sms_buf_end)
	break;
      if(i==0)
      {
	if(!PduDecodeAll(sdx, pd))
	  break;
      }
      else
      {
	if(!PduDecodeTxt(sdx, pd))
	  break;
      }
    }
    if(i)
    {
      res++;
      sdx->opmsg_id=pea->opmsg_id;
      sdx->id=index;
      sdx->msg_type=ISEMS;
      LockSched();
      AddToSdlByTime(sdx);
      UnlockSched();
    }
    else
      FreeSdOne(sdx);
  }
  return res;
}
int DoAllDatMsg(char *sms_buf, char *ems_admin_buf, int sms_size, int ems_admin_size)
{
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LLIST outll=sdroot->out_msg;
  SMS_DATA_LIST *lst;
  lst=inll.first;
  while(lst)
  {
    DoMsgList(lst, sms_buf, ems_admin_buf, sms_size, ems_admin_size);
    lst=lst->next;
  }
  lst=outll.first;
  while(lst)
  {
    DoMsgList(lst, sms_buf, ems_admin_buf, sms_size, ems_admin_size);
    lst=lst->next;
  }
  return 0;
}

int NewMsgReader(void)
{
  char sms_dat[128];
  char ems_admin_dat[128];
  int fin;
  unsigned int err;
  char *sms_buf;
  char *ems_admin_buf;
  int res=0, sms_size, ems_admin_size, x, xl;
  strcpy(sms_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(sms_dat))>0)
    x=sms_dat[xl-1];
  if((x!='\\')&&(x!='/'))
  {
    sms_dat[xl]='\\';
    sms_dat[xl+1]=0;
  }
  strcat(sms_dat, "SMS\\SMS.dat");
  strcpy(ems_admin_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(ems_admin_dat))>0)
    x=ems_admin_dat[xl-1];
  if((x!='\\')&&(x!='/'))
  {
    ems_admin_dat[xl]='\\';
    ems_admin_dat[xl+1]=0;
  }
  strcat(ems_admin_dat, "SMS\\EMS_Admin.dat");
  if((fin=fopen(sms_dat, A_BIN+A_ReadOnly, P_READ, &err))<0)
    return 0;
  sms_size=lseek(fin, 0, S_END, &err, &err)-2;
  sms_buf=malloc(sms_size);
  lseek(fin, 2, S_SET, &err, &err);
  if(fread(fin, sms_buf, sms_size, &err)!=sms_size)
  {
    fclose(fin, &err);
    res=0;
    goto EXIT0;
  }
  fclose(fin, &err);
  if((fin=fopen(ems_admin_dat, A_BIN+A_ReadOnly, P_READ, &err))<0)
  {
    res=0;
    goto EXIT0;
  }
  ems_admin_size=lseek(fin, 0, S_END, &err, &err)-0x9A4;
  ems_admin_buf=malloc(ems_admin_size);
  lseek(fin, 0x9A4, S_SET, &err, &err);
  if(fread(fin, ems_admin_buf, ems_admin_size, &err)!=ems_admin_size)
  {
    fclose(fin, &err);
    res=0;
    goto EXIT1;
  }
  fclose(fin, &err);
  res=DoAllDatMsg(sms_buf, ems_admin_buf, sms_size, ems_admin_size);
EXIT1:
  mfree(ems_admin_buf);
EXIT0:
  mfree(sms_buf);
  return res;
}

int IsHaveNewSMS(void)
{
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  if(!sdroot->cnt_in_new_sms_dat)
    return 0;
  inll=sdroot->in_msg;
  if(!(lst=inll.last))
    return 0;
  if(!(idd=lst->index_id_data))
    return 0;
  if(idd->cnt_all != idd->cnt_received)
    return 0;
  if(idd->type==1)
    return 1;
  return 1;
}

SMS_DATA *GetTheLastNew(int reload) //1, reload, 0, no
{
  SMS_DATA *sdl;
  if(reload)
  {
    freeSDList();
    NewMsgReader();
  }
  sdl=sdltop;
  while(sdl)
  {
    if(sdl->type==TYPE_IN_N)
      return sdl;
    sdl=sdl->next;
  }
  return 0;
}

SMS_DATA *FindSmsByIndex(int index)
{
  SMS_DATA *sdl=sdltop;
  while(sdl)
  {
    if(sdl->id==index)
      return sdl;
    sdl=sdl->next;
  }
  return 0;
}

int CheckThisSMS(int index) //return, 0:do nothing, 1:need to reload all, 2:need to refresh gui
{
  SMS_DATA *sd;
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LLIST outll=sdroot->out_msg;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  //int exist=0;
  if(!index)
    return 0;
  lst=inll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==index)
      {
	//exist=1;
	if(idd->cnt_all != idd->cnt_received) //not full received or not full deleted
	  goto FindAndDel;
	if((sd=FindSmsByIndex(index)))
	{
	  if(idd->type==1)
	  {
	    if(sd->type!=TYPE_IN_N)
	    {
	      sd->type=TYPE_IN_N;
	      return 2;
	    }
	  }
	  else
	  {
	    if(sd->type==TYPE_IN_N)
	    {
	      sd->type=TYPE_IN_R;
	      return 2;
	    }
	  }
	}
	else return 1;
	return 0;
      }
    }
    lst=lst->next;
  }
  lst=outll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==index)
      {
	//exist=1;
	if(idd->cnt_all != idd->cnt_received) //not full received or not full deleted
	  goto FindAndDel;
	if(!(sd=FindSmsByIndex(index))) return 1;
	return 0;
      }
    }
    lst=lst->next;
  }
  //is not exist, del form list
FindAndDel:
  if((sd=FindSmsByIndex(index)))
  {
    delSDList(sd);
    return 2;
  }
  return 0;
}

int IsThisSmsNewIn(int index)
{
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  //int exist=0;
  if(!index)
    return 0;
  lst=inll.last;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index == index)
      {
	if(idd->cnt_all != idd->cnt_received)
	  return 0;
	if(idd->type==1)
	  return 1;
      }
    }
    lst=lst->prev;
  }
  return 0;
}

