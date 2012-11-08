
//Command.c shell BAT files

#include "..\swilib.h"
const char Title[]="\r\n\r\nMS-DOS 0.4 (c)bn";
#define conbufsize 2048
char conbuf[conbufsize], *conend; //lying. buffer

#define MAXPATH 256
char con[MAXPATH]; //The string to display in the sprintf ()
char path[MAXPATH], spath[MAXPATH], curdir[MAXPATH], temp[MAXPATH], ar1[MAXPATH], ar2[MAXPATH];
#define maxset 256
char set[maxset], *setend=set; //environment

// arguments are complex. line
#define maxargv 16
char *argvv[maxargv], **argv;
int argc, fcon; //console
//char *file;

void *SG=0;
char echooff=0, exit=0;

const char link[]="4:\\ZBin\\Link.elf";
const char eline[]="\\", ezap[]=";";
// Open at the start of onstart ()
// End buffer discharge team?// Go to the next. line
//#define crlf {*conend++=0xd;*conend++=0xa;}
// Force a reset buffer
#define flush {fwrite(fcon,conbuf,conend-conbuf,&err);*(conend=conbuf)=0;}

const char *cext[]={".bat",".lnk",".elf",".dll",0};

struct cmdst{ //command
  const char *name; //name of the
  int (*func)(void); //F-I
} *cmd;


enum {ok, error, errcommand, errpath, errarg, errmemory, erropen, errcreate, erroption
};

const char *msg[]={
  "OK",
  "Error",  
  "Bad command or file name",
  "Wrong Way",
  "Not enough arguments",
  "Not enough memory",
  "Failed to open file",
  "Failed to create file",
  "Invalid Option",
};

int striicmp(const char *s, char *ss){
  do{
    if((*s|0x20)-(*ss|0x20)) return 1;
    ++s; ++ss;
  }while(*s);
  return 0;
}



int execbat(char *fname);
  
void print(const char *con){
  if(fcon>0 && *con){
    //crlf
    if(conend+strlen(con)>=conbuf+conbufsize-4) flush
    strcpy(conend, con);
    conend+=strlen(con);
    //*con=0;
  }
}

inline void cr(){
  *conend++=0xd; *conend++=0xa;
}

void arg(char *s){ 
  argc=0;
  do{
    argvv[argc++]=s;
    while(*++s && *s!=' ');
    if(!*s) break;
    *s=0;
    while(*++s && *s==' ');
  }while(*s && argc<maxargv-1);
  argvv[argc]=0;
  argv=argvv;
}

void Killer(void){
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

typedef long Elf(char*, void*, void*, void*);

int rundll(char *exename, void *fc, void *curdir, void *arrgc, void *arrgv){
    int f, l, size, msize, exoff;
    unsigned int err;
    char *mem;
    long *tab;
    if((f=fopen(exename,A_ReadOnly+A_BIN,P_READ,&err))==-1) return erropen;
    if((l=lseek(f,0,2,&err,&err))<16) return error;
    lseek(f,l-4,0,&err,&err);
    fread(f,&size,4,&err);
    lseek(f,0,0,&err,&err);
    //if(size<l-4) return 3;
    msize=(size>l)?size:l;
    if(!(mem=(char*)malloc(msize))) return errmemory;
    zeromem(mem,msize);
    fread(f,mem,msize,&err);
    fclose(f,&err);
    tab=(long*)(mem+l);
    *--tab=0;
    exoff=*--tab;
    *tab=0;
    while(*--tab);
    while(*++tab){
      *(long*)(mem+*tab)+=(long)mem;
      *tab=0;
    }
    l=((Elf*)(mem+exoff))(fc,curdir,arrgc,arrgv);
    mfree(mem);
  return ok;
}


int isfile(char *fname){
  unsigned char at; 
  GetFileAttrib(fname,&at,&err); 
  return !err;
}

void execelf(char *exename, char *fname){
 WSHDR *ws=AllocWS(256);
 str_2ws(ws,exename,strlen(exename)+1);
 ExecuteFile(ws,0,fname); 
 FreeWS(ws);
}

/////////
#include "find.h"
#include "function.h"
///////

int findall(){//char ext){
  char *ptr, **ext=(char**)cext;
  strcat(temp,*argvv);
  if(strrchr(temp,'.'))
    return isfile(temp);
  ptr=temp+strlen(temp);
  while(*ext){
    strcpy(ptr,*ext++);
    if(isfile(temp)) return 1;
  }
  return 0;
}

int gettype(char *s){
  char **ss=(char**)cext;
  if(!(s=strrchr(s,'.'))) return 0;
  while(*ss){
    if(!striicmp(*ss++,s)) return ss-(char**)cext;
  }
  return 0;
}

int command(){ 
  char *s=*argvv, *ss, *sss;

  for(cmd=commands;cmd->name;cmd++){
    if(!striicmp(cmd->name,s)){
      cr(); return cmd->func();
    }
  }
  if(s[1]==':'){ 
    if(isfile(s)){ 
      strcpy(temp,s); goto lexec; //temp!!!
    }
    if(strrchr(s,'.')) return errcommand;
    *(ss=strrchr(s,'\\'))=0;
    strcpy(spath,s);
    strcpy(s,ss+1);
  }else{ 
    strcpy(spath,curdir);
    strcat(spath,";");
    strcat(spath,path);
  }

  ss=spath;
  while(*ss){
    while(*ss==' ') ++ss;
    sss=ss;
    while(*++sss && *sss!=';');
    memcpy(temp,ss,sss-ss);
    temp[sss-ss]=0;
    if(temp[sss-ss-1]!='\\') strcat(temp,eline);
    if(findall()){
lexec:
    switch(gettype(temp)){
    case 1: //bat
      execbat(temp); break; //error recurse????!!!!
    case 2: //lnk
      if(!isfile((char*)link)) *((char*)link)='0';
      execelf((char*)link,temp); break;//??
    case 3: //elf
      execelf(temp,argv[1]); break;
    case 4: //dll
      flush
      rundll(temp,(void*)fcon,curdir,(void*)argc,argvv); break;
    default: 
      return errcommand;
    }
    return 0;
    }
    if(!*sss) break;
    ss=sss+1;
  }
  return errcommand;
}


int exec(char *s){ 
while(*s==' ') ++s;
  if(!*s) return 0; //empty
  if(!echooff){ cr(); print(s);}
  arg(s); 
  return command(); 
}

int execbat(char *fname){ 
  int i,f;
  char *buf, *s, *ss, c;
  if((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) return erropen;
  if(!(i=lseek(f,0,2,&err,&err))
     || !(s=buf=(char*)malloc(i+1))){ fclose(f,&err); return errmemory;}
  lseek(f,0,0,&err,&err);
  fread(f,buf,i,&err);
  buf[i]=0; //eof
  fclose(f,&err);
  //for() exec()
  do{
    ss=s;
    while(*s && *s!=0xd) ++s;
    c=*s; *s=0;
    if(i=exec(ss)){ cr(); print((char*)msg[i]);}
    if(!c) break;
    if(*++s==0xa) ++s;
  }while(*s);
  mfree(buf);
  return ok; 
}

int main(char *exename, char *fname){
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  if(SG=malloc(2500000)) mfree(SG); //S75 
  *(strrchr(exename,'\\')+1)=0;
  strcpy(path,exename);
  strcat(path,";4:\\ZBin\\;0:\\ZBin\\");
  if(fname[1]!=':'){ //no fname
    strcpy(curdir,exename);
  }else{    
    strcpy(curdir,fname);
    *(strrchr(curdir,'\\')+1)=0;
  }
  strcpy(temp,curdir);
  strcat(temp,"Console.txt");
  if((fcon=fopen(temp,A_ReadWrite+A_Append+A_Create,P_READ+P_WRITE,&err))>0)
    lseek(fcon,0,2,&err,&err); 
  conend=conbuf; 
  print(Title);
  sprintf(con,"\r\nDate: %d.%02d.%d  %d:%02d\n",
          date.day,date.month,date.year, time.hour,time.min);
  print(con);
  strcpy(temp,exename);
  strcat(temp,"autoexec.bat");
  execbat(temp);
  if(fname[1]==':'){
    execbat(fname);
  }
  if(fcon>0){ cr(); flush fclose(fcon,&err);}
  SUBPROC((void *)Killer); 
  return 0;
}
