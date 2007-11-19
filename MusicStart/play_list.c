#include "..\inc\swilib.h"
#include "filelist.h"

//extern const char g_path[128];
extern char procfile[128];
char list_path[128]="4:\\ZBin\\MusicStart\\PlayList\\mylist.lst";
char list_text[32768];
int list_size=0;
char *p_list=list_text; //该指针指向当前正在播放的歌曲



void get_currect_song_name(void)
{
  char *p;
  p=p_list;
  int c;
  int i=0;
  char ss[128];
  int is_1st_utf8=0;
  while((*p!='\0')&&(*(p+1)!=':')&&(*(p+2)!='\\')) //以":\"为标记
  {
    p++;
  }
  p_list=p;
  while((*p!=0)&&(*p!='\n'))
  {
    c=*p;
    if(c>=' ')
    {
      if((is_1st_utf8==0)&&(c>0x80))//第一个UTF8中文识别（暂时），0x80为ASCII单字节字符最大值
      {
        ss[i]=0x1F;
        i++;
        is_1st_utf8=1;
      }
      if (i<(sizeof(ss)-1)) ss[i]=c;
      i++;
    }
    p++;
  }
  ss[i]='\0';
  strcpy(procfile,ss);
}

void top2end(void)
{
  char *p;
  p=strrchr(list_text,':');
  p_list=p-1;
  get_currect_song_name();
}

void end2top(void)
{
  p_list=list_text;
  get_currect_song_name();
}

void get_next_song(void)
{
  char *p;
  p=p_list;
  while(*p!='\n')
  {
    p++;
  }
  while((*p=='\n')||(*p==' '))//排除中间多个换行符，空格，以及到达末尾
  {
    p++;
    if(*p=='\0')
    {
      end2top();
      return;
    }
  }
  //p++;
  p_list=p;
  get_currect_song_name();
}

void get_prev_song(void)
{
  char *p;
  p=p_list;
  while(*p)
  {
    p--;
    if((*(p+1)==':')&&(*(p+2)=='\\')) //以":\"为标记搜索上一首
      break;
  }
  if(*p==0)
  {
    top2end();
    return;
  }
  p_list=p;
  get_currect_song_name();
}

void load_list(void)
{
  unsigned int err;
  int f=fopen(list_path,A_ReadOnly+A_BIN,P_READ,&err);
  if(f==-1)
  {
    list_path[0]='0';
    f=fopen(list_path,A_ReadOnly+A_BIN,P_READ,&err);
  }
  if(f!=-1)
  {
    list_size=fread(f,list_text,32767,&err);
    fclose(f,&err);
  }
  if (list_size>=0) list_text[list_size]=0;
  get_currect_song_name();
}


void select_list_gui(void)
{
  open_select_file_gui(1,1);
}
