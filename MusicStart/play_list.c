#include "..\inc\swilib.h"

extern char procfile[128];
char list_text[32768];
int list_size=0;
char *p_list=list_text; //��ָ��ָ��ǰ���ڲ��ŵĸ���

void get_currect_song_name(void)
{
  char *p;
  p=p_list;
  int c;
  int i=0;
  char ss[128];
  int is_1st_utf8=0;
  char m3u_header[]="#EXTM3U";//M3U��ͷ
  if(strncmp(list_text,m3u_header,7)==0)  //M3Uͷ�ж�
  {
    if(*p==0x23)
    {
      p+=9;
      p_list=p; //ָ����ȷ��·����ʼλ��
    }
  }
  if (*p==0xEF) //��UTF8ͷ�ж�
  {
    p+=3;//utf8�����ļ�ͷ����ʱ��
    p_list=p; //ָ����ȷ��·����ʼλ��
  }
  while(*p!='\n')
  {
    c=*p;
    if(c>=' ')
    {
      if((is_1st_utf8==0)&&(c>0x80))//��һ��UTF8����ʶ����ʱ����0x80ΪASCII���ֽ��ַ����ֵ
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
  while((*p=='\n')||(*p==' '))//�ų��м������з����ո��Լ�����ĩβ
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
  if((*(p-1)==0x0A)&&(*(p-2)==0x0D)&&(*(p-3)==0x55)) //�Ѿ��ڵ�һ���ж�,M3U����ʱ��
  {
    top2end();
    return;
  }
  if((*(p-1)==0xBF)||(*p==0xEF)) //�Ѿ��ڵ�һ���ж�,��UTF8����ʱ��
  {
    top2end();
    return;
  }
  else p=p-2;
  while(*p!='\n')
  {
    if((*p==0xBF)&&(*(p-1)==0xBB)) //�����һ���жϣ���UTF8������ʱ��
      break;
    p--;
  }
  //p++;
  p_list=p+1;
  get_currect_song_name();
}

void load_list(void)
{
  char list_path[]="4:\\ZBin\\MusicStart\\mylist.lst";
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

