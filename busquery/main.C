#include "..\inc\swilib.h"
#include <stdbool.h>

extern const char name[128];

char pt[]="%t";
const int minus11=-11;

char *buf=0;
int fsize=0;
int num=0;
int len=0;

const SOFTKEY_DESC menu_sk[]=
{
    {0x0018,0x0000,(int)"select"},
    {0x0001,0x0000,(int)"Close"},
    {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
    menu_sk,0
};

void Loaddata();


WSHDR *ews;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void ed1_locret(void){}

void ed1_ghook(GUI *data, int cmd){}


void lookup(void)
{

}



void doit(GUI *data)
{
  EDITCONTROL ec, ec2,ec3;
  {
   // WSHDR *ws;   
   // WSHDR *ws2;
   // WSHDR *ws3;
    ExtractEditControl(data,1,&ec);
    ExtractEditControl(data,2,&ec2);
    ExtractEditControl(data,3,&ec3);
    int utf8conv_res_len;
    char word[40];
    char word2[40];
    ws_2utf8(ec.pWS,word,&utf8conv_res_len,40);
    ws_2utf8(ec2.pWS,word2,&utf8conv_res_len,40);
    
  int find=0; 
  char *pos=buf;
  int c;
  int cc=0;
  int cc1=0;

  char *s;
  int i=0;
  int i1=0;
  int i2=0;
  int k;
  int l;
  int k1;
  int l1; 
  char cr[1024][1024]; 
  char( *p)[1024]=&cr[1024];  
  char cr2[50][50]; 
  char( *p2)[50]=&cr2[50];  
  char cr3[50][50]; 
  char( *p3)[50]=&cr3[50];  
  
  if(strlen(word)!=0||strlen(word2)!=0)
  {
  while((c=*pos))
  {
    pos++;
    switch(c)
    {
   case '\r':
        if(*pos++=='\n')
        {
        s=(p+i)[1024];
        i++;
        while(*pos!='\r'&&*pos!='\n'&&*pos)
        {
          *s++=*pos++;
        }
        *s=0;
        }
        break;
        
     default:
      break;
    }
  }
  }
 

  if(strlen(word)!=0&&strlen(word2)==0)
  for(k=0;k<=i;k++)
  {
       if(cc!=num+1)
       {
       if(strstr((p+k)[1024],word))
         {
          utf8_2ws(ec3.pWS,(p+k)[1024],1024);
          StoreEditControl(data ,3, &ec3); 
          cc++;
         }
      
       else
       {
       wsprintf(ec3.pWS, pt, "No bus!");
       StoreEditControl(data ,3, &ec3); 
       }
      
       }
  }
  
  if(strlen(word)==0&&strlen(word2)!=0)
  for(k=0;k<=i;k++)
  {
       if(cc!=num+1)
       {
       if(strstr((p+k)[1024],word2))
         {
          utf8_2ws(ec3.pWS,(p+k)[1024],1024);
          StoreEditControl(data ,3, &ec3); 
          cc++;
         }
      
       else
       {
       wsprintf(ec3.pWS, pt, "No bus!");
       StoreEditControl(data ,3, &ec3); 
       }
      
       }
  }
  

  if(strlen(word2)!=0&&strlen(word)!=0)
  {
    for(k=0;k<=i;k++)
     { 
    
     if(cc!=num+1)
       {

       if(strstr((p+k)[1024],word)&&strstr((p+k)[1024],word2))
         {
          utf8_2ws(ec3.pWS,(p+k)[1024],1024);
          StoreEditControl(data ,3, &ec3); 
          find=1;
          cc++; 
         }
       }
    }
    
   if(find==0)
   {

  for(l=0;l<=i;l++)
      {   
     for(k=0;k<=i;k++)
       {
        if(cc1!=num+1)
        {
         
         if(strstr((p+k)[1024],word)&&strstr((p+l)[1024],word2))
         {
           char *pos2=(p+k)[1024];
           while((c=*pos2))
           {
            pos2++;
            switch(c)
            {
             case '*':
             s=(p2+i1)[50];
             i1++;
             while(*pos2!='*'&&*pos2)
             {
              if(*pos2++=='@') break; 
             *s++=*pos2++;
             }
             *s=0;
             break;
        
             default:
             break;
            }
           }
           /*
            char *pos3=(p+l)[1024];
           while((c=*pos3))
           {
            pos3++;
            switch(c)
            {
             case '*':
             s=(p3+i2)[50];
             i2++;
             while(*pos3!='*'&&*pos3)
             {
              if(*pos3++=='@') break; 
             *s++=*pos3++;
             }
             *s=0;
             break;
        
             default:
             break;
              }
           }*/
           utf8_2ws(ec3.pWS,(p+k)[1024],1024);
           StoreEditControl(data ,3, &ec3); 
           cc1++;
           
         }
       }
       }
      }
   }
 // }
 /*
      if(i1!=0&&i2!=0)
      {
        for(k1=0;k1<=i1;k1++)
          {
          for(l1=0;l1<=i2;l1++)
          {
           if(!strcmp((p2+k1)[50],word))
           {  
            utf8_2ws(ws,(p2+k1)[50],50);
           }
           else if(!strcmp((p3+l1)[50],word2))
           {    
            utf8_2ws(ws2,(p3+l1)[50],50);   
           }
           else if(!strcmp((p2+k1)[50],(p3+l1)[50]))
           {
            utf8_2ws(ws3,(p2+k1)[50],50);
           }
          }
         }
      }
  
         if(cc!=num+1)
         {
          //wsprintf(ec3.pWS,"%w %w %w",ws,ws2,ws3);
          StoreEditControl(data ,3, &ec3); 
          cc++;    
           }
         }
         }
*/
  
     if(cc==0)
          {
           wsprintf(ec3.pWS, pt, "No bus!");
            StoreEditControl(data ,3, &ec3); 
          }
      // FreeWS(ws);
      // FreeWS(ws2);
      // FreeWS(ws3);
  }
  }

}




int onkey(GUI *data, unsigned char keycode, int pressed){
  if(pressed==KEY_DOWN){
    switch(keycode)
    {
    case ENTER_BUTTON: num=0;doit(data); return -1;
    case GREEN_BUTTON: if(num>0) num--;doit(data); return -1;
    case RED_BUTTON: num++;doit(data); return -1;
   
    }
  }
  return 0;
}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  //-1 - do redraw
 // return(0); //Do standart keys
  //1: close
    return onkey(data, msg->gbsmsg->submess, msg->gbsmsg->msg);
}



HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)"busquery",0x7FFFFFFF};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0, 5, 132, 160},
  4,
  100,
  101,
  0,

//  0x00000001 - Align Right 
//  0x00000002 - Align Center 
//  0x00000004 - inversion characters
//  0x00000008 - UnderLine
//  0x00000020 - not carry the word 
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - Not moving the cursor 
//  0x40000000 - Change field coaching buttons 
  0
};

int create_ed(void)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  wsprintf(ews,"%t","");
  ConstructEditControl(&ec,4,0x40,ews,256); 
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"%t","");
  ConstructEditControl(&ec,4,0x40,ews,256); 
  AddEditControlToEditQend(eq,&ec,ma);
  
  wsprintf(ews,"%t","Bus number!");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  return CreateInputTextDialog(&ed1_desc,0,eq,1,0);
}

void ErrorMsg(const char *msg)
{
  LockSched();
  ShowMSG(1,(int)msg);
  UnlockSched();
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void Loaddata()
{ 
  int f;
  unsigned int err;
  char fname[128];
  
  if (buf != 0)
   mfree(buf);
  snprintf(fname,128,"%s",name);
  if ((f=fopen(fname, A_ReadOnly+A_BIN, 0, &err))==-1)
  {
         ErrorMsg("Can't open data!");
         return;    
  }
  fsize=lseek(f,0,S_END,&err,&err);
  lseek(f,0,S_SET,&err,&err);
  if (fsize<=0)
  {
    ErrorMsg("Zero lenght of data!");
    fclose(f,&err);
  } 
  else if ((buf=malloc(fsize))==0)
  {
     ErrorMsg("Can't malloc!");
  }  
  else if (fread(f,buf,fsize,&err)!=fsize)
  {
        ErrorMsg("Can't read data!");
      fclose(f, &err);
      mfree(buf);
      buf=0;
  }
  fclose(f,&err);
}


void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(256);
  csm->gui_id=create_ed();
  Loaddata();
}

void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ews);
  if (buf != 0)
    mfree(buf);
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      {
	csm->csm.state=-3;
      }
    }
  }
  return(1);
}

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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"busquery");
}

int main()
{
  char dummy[sizeof(MAIN_CSM)];
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
