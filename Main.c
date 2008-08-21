#include "..\swilib.h"
//
void PlayCurrent();
char *filename;
char *files,*showfilename;
char fromplaylist;
short currentfile,curfilerand,newfile;
unsigned char numfiles,loop;
unsigned long randseed;


unsigned long randint( long max )
{
  randseed = randseed * 0x08088405;
  randseed++;
  return ((long long)randseed * max ) >> 32;
}


#include "Siemens_MP3.c"
#include "AudioHook.c"
#include "siemens.c"

void LoadParams()
{
  int plhandle, i;
  unsigned short n;
  plhandle = fopen( "0:\\Zbin\\MP3Player.dat", A_ReadOnly + A_BIN, 0, & err );
  if ( plhandle == -1 )
  {
    fclose( plhandle, & err );
    return;
  }
  fread( plhandle, & numfiles, 1, & err );
  
  i = 0;
  while ( i < numfiles )
  {
    fread( plhandle, & n, 2, & err );
    fread( plhandle, & files[i * 256], n, & err );
    i++;
  }
  fread( plhandle,&loop, 1, & err );
  fread( plhandle,&SoftVol, 1, & err );
  fread( plhandle,&randomplay, 1, & err );
  fread( plhandle,&Volume, 1, & err );
  fclose( plhandle, & err );
}


void SaveParams()
{
  int plhandle, i;
  unsigned short n;
  unlink("0:\\Zbin\\MP3Player.dat",&err);
  plhandle = fopen( "0:\\Zbin\\MP3Player.dat", A_ReadWrite + A_BIN + A_Append + A_Create, P_READ + P_WRITE, & err );

  fwrite( plhandle, & numfiles, 1, & err );

  i = 0;
  while ( i < numfiles )
  {

    n = 0;
    while ( files[i * 256 + n] != 0 ) n++;
    n++;
    fwrite( plhandle, & n, 2, & err );
    fwrite( plhandle, & files[i * 256], n, & err );
    i++;
  }
  fwrite( plhandle,&loop, 1, & err );
  fwrite( plhandle,&SoftVol, 1, & err );
  fwrite( plhandle,&randomplay, 1, & err );
  fwrite( plhandle,&Volume, 1, & err );
  fclose( plhandle, & err );
}

void PlayCurrent()
{
  Mp3Init();
  AudioStart();
}

char *ExtractFileName(char *ptr){
 int i;
i=0;
while(ptr[i]!=0){i++;}  
while(ptr[i]!=0x5C){i--;}
return(&ptr[i+1]);
}

//Новые данные
int onstart( char * exename, char * fname )
{ // Старт приложения. Возвращает 0 или 1 для выхода.
  MenuInit();
  showfilename=malloc(64);
  files=malloc(256*256);
  zeromem(files,(256*128));
  numfiles=0;
  filename=malloc(256);
  memcpy(files,fname,128);
  memcpy(filename,files,128);
  AudioInit();  
  curpath=malloc(256);
  fromplaylist=0;
  SoftVol = 1;
  loop=0;
  randomplay=0;
  LoadParams();
  UpdateShowName();
  PlayCurrent();
  return 0;
}
