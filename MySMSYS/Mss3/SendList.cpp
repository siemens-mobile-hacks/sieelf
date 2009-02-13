#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "SendList.h"


SNDLST * SendList::AllocSL()
{
  SNDLST *sl=new SNDLST;
  zeromem(sl, sizeof(SNDLST));
  return sl;
}

void SendList::FreeList()
{
  SNDLST *sl;
  SNDLST *sl0;
  LockSched();
  sl=this->sltop;
  this->sltop=NULL;
  UnlockSched();
  while(sl)
  {
    sl0=sl->next;
    if(sl->text)
      FreeWS(sl->text);
    delete sl;
    sl=sl0;
  }
}

SendList::SendList()
{
  this->sltop=NULL;
}

SendList::~SendList()
{
  this->FreeList();
}

void SendList::AddToList(SNDLST *sl) //end
{
  if(!sl) return;
  LockSched();
  if(!this->sltop)
  {
    this->sltop=sl;
  }
  else
  {
    SNDLST *s0=this->sltop;
    while(s0->next)
      s0=s0->next;
    s0->next=sl;
    sl->prev=s0;
  }
  UnlockSched();
}

void SendList::AddToList(const char *number, WSHDR *text)
{
  int wlen;
  SNDLST *sl;
  if(!number || !strlen(number) || !text || !(wlen=text->wsbody[0]))
    return;
  sl=AllocSL();
  strcpy(sl->number, number);
  sl->text=AllocWS(wlen);
  wstrcpy(sl->text, text);
  AddToList(sl);
}

void SendList::DeleteSL(SNDLST *sl)
{
  if(!sl) return;
  LockSched();
  if(sl==this->sltop)
  {
    this->sltop=this->sltop->next;
    if(this->sltop) this->sltop->prev=NULL;
  }
  else
  {
    sl->prev->next=sl->next;
    if(sl->next) sl->next->prev=sl->prev;
  }
  UnlockSched();
  if(sl->text) FreeWS(sl->text);
  delete sl;
}

SNDLST * SendList::FindSL(int csm_id)
{
  SNDLST *sl;
  if(!csm_id) return 0;
  sl=this->sltop;
  while(sl)
  {
    if(sl->csm_id==csm_id)
      return sl;
    sl=sl->next;
  }
  return 0;
}

//DEL void SendList::CatList(SendList *lst)
//DEL {
//DEL   SNDLST *sl;
//DEL   LockSched();
//DEL   sl=this->sltop;
//DEL   if(sl)
//DEL   {
//DEL     this->sltop=lst->sltop;
//DEL   }
//DEL   else
//DEL   {
//DEL     while(sl->next)
//DEL       sl=sl->next;
//DEL     sl->next=lst->sltop;
//DEL     lst->sltop->prev=sl;
//DEL   }
//DEL   UnlockSched();
//DEL }

int SendList::IsSending()
{
  SNDLST *sl=this->sltop;
  while(sl)
  {
    if(sl->csm_id)
      return 1;
    sl=sl->next;
  }
  return 0;
}

int SendList::SendStart()
{
  int len;
  int csm_id;
  SNDLST *sl;
  WSHDR *ws;
  if(IsSending())
    return 0;
  sl=this->sltop;
  if(
    !sl
    ||!strlen(sl->number)
    ||!sl->text
    ||!(len=sl->text->wsbody[0])
    )
    return 0;
  ws=AllocWS(len+4);
  wstrcpy(ws, sl->text);
  csm_id=SendSMS(ws, sl->number, MMI_CEPID, MSG_SMS_RX-1, 6);
  sl->csm_id=csm_id;
  return csm_id;
}

//DEL int SendList::SendEnd()
//DEL {
//DEL 
//DEL }

int SendList::SendEnd(int csm_id)
{
  SNDLST *sl;
  if(!csm_id
    || !(sl=FindSL(csm_id))
    )
    return 0;
  if(CFG_ENA_SAVE_SENT) SMSDATA->SaveMss(sl->text, sl->number, NULL, TYPE_OUT, 2);
  DeleteSL(sl);
  return 1;
}

//DEL int SendList::IsSendCSM()
//DEL {
//DEL 
//DEL }

int SendList::IsSendCSM(int csm_id)
{
  SNDLST *sl=this->sltop;
  while(sl)
  {
    if(sl->csm_id==csm_id)
      return 1;
    sl=sl->next;
  }
  return 0;
}

void SendList::CatList(SNDLST *sl)
{
  if(!sl)
    return;
  LockSched();
  if(!this->sltop)
  {
    this->sltop=sl;
  }
  else
  {
    SNDLST *s0=this->sltop;
    while(s0->next)
      s0=s0->next;
    s0->next=sl;
    sl->prev=s0;
  }
  UnlockSched();
}
