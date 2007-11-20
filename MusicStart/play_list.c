#include "..\inc\swilib.h"
#include "filelist.h"
#include "main.h"

extern const char g_path[128];
extern char procfile[128];
extern int playhandle;
char list_path[128];
char list_text[16384];
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
  while(*p)
  {
    if((*(p+1)==':')&&(*(p+2)=='\\'))//以":\"为标记
      break;
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
  p=strrchr(list_text,':'); //搜索到最后一个':'字符
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

void load_list(int type) //0: load his fail, 1:load his succ... 2:reload
{
  unsigned int err;
  if(type==0)
  {
    strncpy(list_path,g_path,strlen(g_path));
    strcat(list_path,"PlayList\\mylist.lst\0");
  }
  int f=fopen(list_path,A_ReadOnly+A_BIN,P_READ,&err);
  if(f!=-1)
  {
    list_size=fread(f,list_text,32767,&err);
    fclose(f,&err);
  }
  if (list_size>=0)
    list_text[list_size]=0;
    
  if(type==0||type==2) //load his fail or reload
  {
    p_list=list_text; //初始化一次
    get_currect_song_name();
  }
  else
  {
    char *p=strstr(list_text,procfile); //转到列表中的位置
    if(*p)
      p_list=p;
  }
}


void select_list_gui(void)
{
  open_select_file_gui(1,1);
}


/*============================play mode============================*/

void play_next(void) //顺序循环
{
	get_next_song();
	control(0);
}

void play_prev(void) //倒序循环
{
	get_prev_song();
	control(0);
}

/***************************************************************
以下为随机算法，by binghelingxi(bingk)
原理：先获取正在播放歌曲的handle，这本身就是一个随机正整数
然后将它除以3，按得到的余数0，1，2，分别定位到列表的上中下三段
再将原来得到的handle乘以0x18(大约为一首歌路径的长度)
循环减去handle/2，直到它出现在它被定位在列表的范围内的为止
然后把歌曲在列表中的位置指针定位到这个数
经过get_currect_song_name函数处理就可以得到准确的歌曲名
****************************************************************/

void play_shuff(void)
{
  if(playhandle)
  {
    int y;
    int x=playhandle;
    int c=x%3;
    switch(c)
    {
      case 0:
        y=x*0x18;
        while(y>=list_size/3)
        {
          y-=list_size/3;
        }
        break;
      case 1:
        y=list_size/3+x*0x18;
        while(y>=list_size/3*2)
        {
          y-=list_size/3;
        }
        break;
      case 2:
        y=list_size/3*2+x*0x18;
        while(y>=list_size)
        {
          y-=list_size/3;
        }
        break;
    }
    p_list=list_text;
    p_list+=y;
    get_currect_song_name();
    control(0);
  }
}

