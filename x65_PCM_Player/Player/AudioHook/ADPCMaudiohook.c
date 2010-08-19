/*    ��������� ��� ����� ����.
������� � �������� ������:
�������� PlayMelodyInMem ����������� ������������ �������
� ���������� wave �����. PlayMelodyInMem ������� ����
������, �������� ���� ������ ��� ��������� wave � ���
������ ��������
������ � DSP. ������� ���� ������ ����������� �� ���.
�� ������� ����� ����� ������� � ��������� ��� ��
������������ ��������� ���� ��� ��������, ���� ������
���������������. ��� ������ :)
�� �� �����-�� ������������ ���������������
������ ������ ~2 ������ �������� � ����� � ������������.
ILYA_ZX.
mailto: rusman2005@mail.ru
*/

#include "IMA_ADPCM.C"

extern signed char Volume;
/* ������� ������������� */
extern int samplerate;
/* ����� � ���(�� ���������� �������) */
long * WaveParameters;
/* ������, ����������� �������� PlayMelodyInMem */
char * buffer;
/* ����� ���������� ������� ��� ����������. ���� ������ ������� ������� �� ��� */
extern unsigned char nextbuff;
/* ������, ������������ ��� ������� ������������ */
unsigned char * imabuf=0;
/* ������ ��� PCM ������ */
signed short * pcmbuff=0;
/* ���������� ���������� ����������������. ��� ���������: Playing=0; */
extern signed char Playing;
/* ����� ������������ � 1/16000 ������� */
extern signed long PlayingTime;
/* ��������� ���������� ������������� */
void AdpcmPlayingProc();
/* ������ �������. ������ ���� ������ 256(������ ����� IMA ADPCM) */
static const int AD_BUFFERSIZE = 32768;

int writebufpos;


/* ��������� wave IMA ADPCM */
unsigned char Ad_WavHdr[60] =
{
  0x52, 0x49, 0x46, 0x46, 0x34, 0x4D, 0x4B, 0x00, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20, 0x14, 0x00, 0x00, 0x00, 0x11,
       0x00, 0x01, 0x00, 0x80, 0x3E, 0x00, 0x00, 0xAE, 0x1F, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x02, 0x00, 0xF9, 0x01, 0x66,
       0x61, 0x63, 0x74, 0x04, 0x00, 0x00, 0x00, 0x00, 0x89, 0x94, 0x00, 0x64, 0x61, 0x74, 0x61, 0x00, 0x4D, 0x4B, 0x00
};


/* ������� ��������� � ���������� ������������ �������, �� 0 - ������������ �������� */
void Ad_SetHookState( unsigned char hookstate )
{
  WaveParameters[-0x1C] = hookstate;
}

/* ���������� ����� ����� �������, ���������� �������� PlayMelodyInMem */
long GetBuffEnd()
{
  return ( WaveParameters[0x08] );
}

/* ���������� ����� ������� ������� � ������ */
long GetAd_BuffPosAddr()
{
  return ( WaveParameters[0x07] );
}

/* ���������� ������� � ������� */
unsigned long Ad_BuffPos()
{
  return ( GetAd_BuffPosAddr() - ( long )buffer );
}

/* ������� ���������� ������� ������� � imabuf */
void Ad_FillBuffer()
{
  unsigned int i;

  writebufpos = 60;

  while ( writebufpos < ( 60+4096) )
  {
    i = 0;
    while ( i < 1012 )
    {
      pcmbuff[i] = 0;
      i++;
    }
    if ( Playing !=1 )
    {
      writebufpos=-1;
      return;
    }
    ImaCodeBlock( pcmbuff, & imabuf[writebufpos] );
    writebufpos = writebufpos + 256;
    PlayingTime += 506;
  }
  

  while ( writebufpos < ( AD_BUFFERSIZE/2 + 60 ) )
  {
    i = 0;
    GetSound(pcmbuff,1012);
    if ( Playing !=1 )
    {
      writebufpos=-1;
      return;
    }
    ImaCodeBlock( pcmbuff, & imabuf[writebufpos] );
    writebufpos = writebufpos + 256;
    PlayingTime += 506;
  }
  writebufpos=-1;
}

int Ad_PlayStatus(){
return(WaveParameters[0x16]);  
};
/* ������� ���������� ������� ������� */
void Ad_FillBuffer1()
{
  unsigned int i; 
  int add=0;
  writebufpos = 0;
  while ( writebufpos < ( AD_BUFFERSIZE / 2 ) )
  {
    if ( Paused )
    {
      zeromem( pcmbuff, 1012 );
    }
    else
    {
      i = 0;
      GetSound(pcmbuff,1012);
      PlayingTime += 506;
    }
    if ( Playing !=1 )
    {
      writebufpos=-1;
      return;
    }
    ImaCodeBlock( pcmbuff, & buffer[writebufpos] );
    writebufpos = writebufpos + 256;
  }
  writebufpos=-1;
}

/* ������� ���������� ������� ������� */
void Ad_FillBuffer2()
{
  unsigned int i, writebufpos;
  writebufpos = AD_BUFFERSIZE / 2;
  while ( writebufpos < AD_BUFFERSIZE )
  {
    if ( Paused )
    {
      zeromem( pcmbuff, 1012 );
    }
    else
    {
      GetSound(pcmbuff,1012);
      PlayingTime += 506;
    }
    if ( Playing !=1 )
    {
      writebufpos=-1;
      return;
    }
    ImaCodeBlock( pcmbuff, & buffer[writebufpos] );
    writebufpos = writebufpos + 256;
  }
  if(!AudioActive){
    Playing=0;
    PlayerCmd=CMD_OPEN | CMD_NEXT | CMD_STOP | CMD_PLAY;
  }
}

void Ad_AudioInit()
{
  Volume = 1;
  /* ����� ���������� wave �� ���������� �������,
  ������� ������� ��� �������� � �� ����� */
  //WaveParameters = ( void * ) 0xA0FD426C;  
 // WaveParameters = ( void * ) WaveParameters[0]; 
  WaveParameters= AudioParamsAdr();
  /* +60 - �� ��������� wave */
  imabuf = malloc( AD_BUFFERSIZE + 60 );
  pcmbuff = malloc( 1014*2 );
  /*�������� ��������� wave */
  memcpy( imabuf, ( void * ) ( Ad_WavHdr ), 60 );
}

void Ad_AudioStart()
{ 
  /* ��������������� ������� */
  Playing = 1;
  /*0xFF - ��� ��������� ��������� � ��������� ������ �������*/
  nextbuff = 0xFF;
  /*�������������� ������*/
  Ad_FillBuffer();
  /*������������� ������������*/
  Ad_SetHookState( 1 );
  
  /* ������������� ������� ������������� */
  memcpy(imabuf+24,&samplerate,4);
  *(( (char *) PcmWaveParams)+0x85) = ( 48 - ( Volume * 2 ) ) + 1;
  /*��������� ������ �� ������������*/
  PlayMelodyInMem( 0x11, imabuf, AD_BUFFERSIZE + 60, 0xFFFF, 0, 0 );
  /*��������� ���� ������������ ������������*/  
  GBS_StartTimerProc( & ahtimer, 64, AdpcmPlayingProc );
}

/*��������� ���������������.
������� ���������� ���� Playing=0 */
void Ad_AudioStop()
{
  /* ��������� ��� */
  Ad_SetHookState( 0 );
  AudioActive=0;
  /* ����������� �������� ���� ��� ��������� ������������ ��������� ������� */
  //PlayMelodyInMem( 0x11, imabuf, 256 + 60, 0xFFFF, 0, 0 );
}


void Ad_AudioTerminate()
{
  Playing=0;
  Ad_AudioStop();
  if(imabuf!=0){
  mfree( imabuf );
  imabuf=0;
  }
  if(pcmbuff!=0){
  mfree( pcmbuff );
  pcmbuff=0;
  }
}

void AdpcmPlayingProc()
{
  int BUFPOS;
  
  if(writebufpos==-1)
  {
  switch (Playing)
  {
  case 0:
    Ad_AudioStop();    
    return;
  case -1:
    Ad_AudioTerminate();
    return;
  }

  }
  
  if ( nextbuff == 0xFF )
  {
    nextbuff = 2;
    buffer = ( void * ) ( GetBuffEnd() - AD_BUFFERSIZE );
  //  ChangeVolume( Volume );
  }

  BUFPOS = Ad_BuffPos();

  if ( ( nextbuff == 1 ) && ( BUFPOS > ( AD_BUFFERSIZE / 2 ) ) )
  {
    /* ���������� �����-�� �������. ���� ����� �� ������
    �� �������� ����� 10 ����� ������������ ������� �������� */
    WaveParameters[0x0B] = 0;
    /* ��������� ������ ������ */
    Ad_FillBuffer1();
    //SUBPROC((void*)Ad_FillBuffer1);
    nextbuff = 2;
  }

  if ( ( nextbuff == 2 ) && ( BUFPOS < ( AD_BUFFERSIZE / 2 ) ) )
  {
    Ad_FillBuffer2();
    //SUBPROC((void*)Ad_FillBuffer2);
    nextbuff = 1;  
  }

    GBS_StartTimerProc( & ahtimer, 8, AdpcmPlayingProc );
}
