#include "..\..\inc\swilib.h"

#include "..\info.h"

#include "menu.h"
#include "log.h"
#include "fileman.h"
#include "rect_patcher.h"

#include "..\api\high_api.h"

char back[] = FM_BACK;


char pt[]="%t";
char ps[]="%s";
char pc[]="%c";



volatile FLIST *fltop;

void Free_FLIST(void)
{
  LockSched();
  FLIST *fl=(FLIST *)fltop;
  fltop=0;
  UnlockSched();
  while(fl)
  {
    FLIST *fl_prev;
    fl_prev=fl;
    fl=fl->next;
    mfree(fl_prev->fullname);
    mfree(fl_prev->name);
    mfree(fl_prev);
  }
}


        
int GetFListN()
{
  int i=0;
  FLIST *fl=(FLIST*)&fltop;
  while((fl=fl->next)) i++;
  return (i);
}

int GetFoldersLevel(char *name)
{
  int i=0;
  char *s=name;
  while(*s++)
  {
    if (*s=='\\' &&*(s+1)!=0) i++;    
  }
  return (i);
}

#pragma inline=forced

int toupper(int c)
{if ((c>='a')&&(c<='z')) c+='A'-'a';
 return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{int i,c;
 while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
 return(i);
}

FLIST *AddToFList(const char* full_name, const char *name, int is_folder)
{
  FLIST *fl;
  FLIST *pr;
  FLIST *fn=malloc(sizeof(FLIST));
  fn->fullname=malloc(strlen(full_name)+1);
  strcpy(fn->fullname,full_name);
  
  fn->name=malloc(strlen(name)+1);
  strcpy(fn->name,name);
  
  fn->is_folder=is_folder;
  fn->next=0;
  fl=(FLIST *)fltop;
  if (fl)
  {
    pr=(FLIST *)&fltop;
    while(strcmp_nocase(fl->name,fn->name)<0)
    {
      pr=fl;
      fl=fl->next;
      if (!fl) break;
    }
    fn->next=fl;
    pr->next=fn;
  }
  else
  {
    fltop=fn;
  }
  return (fn);  
}

void FindFiles(char *str, int type)  // type == 0 SelectFolder, type == 1 SelectFile
{
  DIR_ENTRY de;              
  
  unsigned int err;
  int i, c;
  char name[256]; 
  char fname[128];

  Free_FLIST();
  strcpy(name,str);
  strcat(name,FM_EXT);
  
  i=GetFoldersLevel(str);
  if (i==0)
  {
    AddToFList(FM_ROOT,back,IS_FOLDER);
  }
  else
  {
    char *s=str;
    char *d=fname;
    for (int k=0; k!=i && *s; )
    {
      c=*s++;
      *d++=c;
      if (c=='\\')  k++;
    }
    *d=0;
    AddToFList(fname,back,IS_FOLDER);
  }
  
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,de.folder_name);
      strcat(name,"\\");
      strcat(name,de.file_name);
      if (de.file_attr&FA_DIRECTORY)
      {
        strcpy(fname,"\\");
        strcat(fname,de.file_name);
        strcat(name,"\\");
        AddToFList(name,fname,IS_FOLDER);
      }
      else
      {
        if (type!=0)
        {
          AddToFList(name,de.file_name,IS_FILE);
        }
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}



FLIST *FindFLISTtByNS(int *i, int si)
{
  FLIST *fl;
  fl=(FLIST *)fltop;
  while(fl)
  {
    if (fl->is_folder==si)
    {
      if (!(*i)) return (fl);
      (*i)--;
    }    
    fl=fl->next;
  }
  return fl;
}
  
FLIST *FindFLISTtByN(int n)
{
  FLIST *fl;
  fl=FindFLISTtByNS(&n,IS_FOLDER); if ((!n)&&(fl)) return(fl);
  fl=FindFLISTtByNS(&n,IS_FILE); if ((!n)&&(fl)) return(fl);
  return fl;
}


void SavePath(void *ed_gui, FLIST *fl)
{ 
  strcpy(dp_file_path,fl->fullname); 
  CreateFileBuffer();
}


char header[];
int filelist_menu_onkey(void *data, GUI_MSG *msg)
{
  FVIEW *fview=MenuGetUserPointer(data);
  FLIST *fl;
  int i;
  i=GetCurMenuItem(data);
  fl=FindFLISTtByN(i);
  
  if (msg->keys==0x3D)
  {
    if (fl) 
    {
      if (fl->is_folder==IS_FOLDER)
      {
        int len;
        if (strcmp(fl->fullname,FM_ROOT))
        {
          strncpy(header,fl->fullname,127);
          len=strlen(fl->fullname);
          header[len>127?127:len]=0;
          FindFiles(fl->fullname,1);
        }
        else
        {
          void CreateRootMenu();
          CreateRootMenu();
        }         
        Menu_SetItemCountDyn(data,GetFListN());
        SetCursorToMenuItem(data, 0);
        RefreshGUI();
      }
      else
      {
        SavePath(fview->gui,fl);
        CURRENT_GUI=0;
        return (1);
      }
    }
    //    GeneralFunc_F1(1);
    return(-1);
  }
  if (msg->keys==0x18)
  {
    if (fl)
    {
      if (strcmp(fl->name,back))
      {
        SavePath(fview->gui,fl);
        CURRENT_GUI=0;
        return (1);
      }      
    }
    
    return (-1);
  }
  return (0);

}

void filelist_menu_ghook(void *data, int cmd)
{
  FVIEW *fview=MenuGetUserPointer(data);
  if (cmd==3)
  {
    Free_FLIST();
    mfree(fview);    
  }
  DisableIDLETMR();
}

void filelist_menu_iconhndl(void *data, int curitem, void *user_pointer)
{
  FLIST *fl;
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  int len;
  fl=FindFLISTtByN(curitem);
  if (fl)
  {
    len=strlen(fl->name);
    ws=AllocMenuWS(data,len+4);
    
    if (fl->is_folder)
    {
      str_2ws(ws,fl->name,len);
      wsInsertChar(ws,0x0002,1);
      wsInsertChar(ws,0xE008,1);
    }
    else
    {
      str_2ws(ws,fl->name,len);
    }
  }
  else
  {
    ws=AllocMenuWS(data,10);
    wsprintf(ws, FM_ERROR);
  }
  SetMenuItemText(data, item, ws, curitem);
}

int fmenusoftkeys[]={0,1,2};
SOFTKEY_DESC fmenu_sk[]=
{
  {0x0018,0x0000,(int)FM_S_SELECT},
  {0x0001,0x0000,(int)FM_S_EXIT},
  {0x003D,0x0000,(int)FM_S_X}
};

SOFTKEYSTAB fmenu_skt=
{
  fmenu_sk,1
};
char header[128];
HEADER_DESC filelist_HDR={0,0,0,0,NULL,(int)header,LGP_NULL};



MENU_DESC filelist_STRUCT=
{
  8,filelist_menu_onkey,filelist_menu_ghook,NULL,
  fmenusoftkeys,
  &fmenu_skt,
  0x10,
  filelist_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0 
};

void CreateRootMenu()
{
  Free_FLIST();
  AddToFList("0:\\","1.Data (0:)",IS_FOLDER);
  AddToFList("1:\\","2.Cashe (1:)",IS_FOLDER);
  AddToFList("2:\\","3.Config (2:)",IS_FOLDER);
  AddToFList("4:\\","4.MMC (4:)",IS_FOLDER);
  AddToFList("0:\\Misc\\Patches\\","5.Favorites",IS_FOLDER);
  strcpy(header,FM_ROOT);
}



void GUI_OpenFM(char *path, int type)
{
  FVIEW *fview;
  char *s, *rev=0;
  int c, len; 
  fview=malloc(sizeof(FVIEW));
  fview->type=type;
  s=path;
  while((c=*s++))
  {
    if (c=='\\' && *s!='\0') rev=s;  
  }
  if (!rev)
    CreateRootMenu();
  else
  {
    *rev=0;
    strncpy(header,path,sizeof(header)-1);
    len=strlen(path);
    header[len>sizeof(header)-1?sizeof(header)-1:len]=0;
    FindFiles(path,type);
  }    
  patch_header(&filelist_HDR, NULL, (int)header);
  FMGUI_ID = CreateMenu(0,0,&filelist_STRUCT,&filelist_HDR,0,GetFListN(),fview,0);
  CURRENT_GUI = 2;
}



