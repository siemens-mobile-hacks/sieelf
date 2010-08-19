
/* PCM AudioHook interface */
/*
(c) ILYA_ZX 
mailto:ILYA.ZX@gmail.com
*/

typedef struct
{
  void * FillProc;
  unsigned short * buffer;
  unsigned short * curpos;
  unsigned short * buffend;
}
_wavplayer;

_wavplayer * WAV_PLAYER;

/* ���������� ��� ��������� ��������������� ����� ������ */
int LastIsCalling;
signed char Volume;
/* ������� ������������� */
int samplerate;
/* ������� ������� ��������� ����� ������� */
void GetSound( signed short * ptr, int nsamples );
/* ����� � ���(�� ���������� �������) */
long /* * AdpcmWaveParams */ * pcm_ram_player;
/* ����� ���������� ������� ��� ����������. ���� ������ ������� ������� �� ��� */
unsigned char nextbuff;
/* ������, ������������ ��� ������� ������������ */
signed short * AudioBuf = 0;
signed short * TempBuf;
/* ������ ��� PCM ������ */
//signed short * pcmbuff=0;
/* ���������� ���������� ����������������. ��� ���������: Playing=0; */
signed char Playing;
/* ����� ������������ � 1/16000 ������� */
signed long PlayingTime;
/* ��������� ���������� ������������� */
void PlayingProc();
/* ������ :) */
GBSTMR ahtimer;
/* ������ �������. ������ ���� ������ 256(������ ����� IMA ADPCM) */
static const int BUFFERSIZE = 96000;

char Paused = 0;
/* ��������� wave PCM */
unsigned char WavHdr[44] = {
	0x52, 0x49, 0x46, 0x46, 0x6A, 0x88, 0x04, 0x00, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20, 
	0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x40, 0x1F, 0x00, 0x00, 0x80, 0x3E, 0x00, 0x00, 
	0x02, 0x00, 0x08, 0x00, 0x64, 0x61, 0x74, 0x61, 0x06, 0x88, 0x04, 0x00
};


char WaveFill()
{
    
  unsigned long i = 0xA0/16;
  unsigned short * curpos = WAV_PLAYER->curpos;
 unsigned long * rambuf = pcm_ram_player+0x23;
 
  while ( i>0 )
  {
    * rambuf = *curpos;
    * (rambuf+1) = *(curpos+1);
    * (rambuf+2) = *(curpos+2);
    * (rambuf+3) = *(curpos+3);    
    * (rambuf+4) = *(curpos+4);
    * (rambuf+5) = *(curpos+5);
    * (rambuf+6) = *(curpos+6);
    * (rambuf+7) = *(curpos+7);    
    * (rambuf+8) = *(curpos+8);
    * (rambuf+9) = *(curpos+9);
    * (rambuf+10) = *(curpos+10);    
    * (rambuf+11) = *(curpos+11);
    * (rambuf+12) = *(curpos+12);
    * (rambuf+13) = *(curpos+13);
    * (rambuf+14) = *(curpos+14);
    * (rambuf+15) = *(curpos+15);
    rambuf+=16;
    curpos+=16;
    i--;
  }
  
  if ( curpos >= WAV_PLAYER->buffend )
  {
    WAV_PLAYER->curpos = WAV_PLAYER->buffer;
    return;
  }
  WAV_PLAYER->curpos = curpos;

}


/* ������� ��������� � ���������� ������������ �������, �� 0 - ������������ �������� */
void SetHookState( unsigned char hookstate )
{
  if ( hookstate ) pcm_ram_player[32]=(long)WAV_PLAYER; 
  else
    pcm_ram_player[32]=0; 

}


/* ���������� ������� � ������� */
unsigned long BuffPos()
{
  return (long)(WAV_PLAYER->curpos-WAV_PLAYER->buffer);
  ;
}

void SetVolume( char Vol )
{


  Volume = Vol;
  if ( Volume > 24 ) Volume = 24;
  if ( Volume < 0 ) Volume = 0;
  
  if ( Volume )
  {
    *(( (char *) pcm_ram_player)+0x85) = ( 48 - ( Volume * 2 ) ) + 1;
    ChangeVolume( 1 );
}
  else ChangeVolume( 0 );
}



int PlayStatus()
{
  return ( pcm_ram_player[0x18] );
};

void FillBuffer1()
{
  if ( Paused )
  {
    zeromem( ( void * ) & AudioBuf[0], BUFFERSIZE / 2 );
    return;
  }
  GetSound(AudioBuf,BUFFERSIZE / 4);
}

/* ������� ���������� ������� ������� */
void FillBuffer2()
{
  if ( Paused )
  {
    zeromem( ( void * ) & AudioBuf[BUFFERSIZE / 4], BUFFERSIZE / 2 );
    return;
  }
  GetSound(AudioBuf+(BUFFERSIZE / 4),BUFFERSIZE / 4);

}

void AudioInit()
{

  Volume = 1;
  pcm_ram_player = ( void * ) 0xA879F7C0; //S65v58
  WAV_PLAYER = malloc( sizeof( _wavplayer ) );
  AudioBuf = malloc(BUFFERSIZE);
  TempBuf=malloc(8192);
  zeromem( AudioBuf, BUFFERSIZE);
  zeromem( TempBuf, 8192);
  WAV_PLAYER->buffer=AudioBuf;
  WAV_PLAYER->curpos=AudioBuf;
  WAV_PLAYER->buffend=AudioBuf+BUFFERSIZE/2;
  WAV_PLAYER->FillProc = ( void * ) WaveFill;
  //pcmbuff = malloc( 1014 );
  /* �������� ��������� wave */
  memcpy( ( char * ) TempBuf, ( void * ) ( WavHdr ), 44 );

}

void P_AudioStart()
{

  WAV_PLAYER->curpos=AudioBuf;
  LastIsCalling = 0;
  /* ��������������� ������� */
  Playing = 1;
  /* 0xFF - ��� ��������� ��������� � ��������� ������ ������� */
  nextbuff = 0xFF;
  /* �������������� ������ */
  GetSound(AudioBuf,BUFFERSIZE / 2);
  /* ������������� ���) */
  SetHookState( 1 );
  /* �������� ��������� wave */
  memcpy( ( char * ) TempBuf, ( void * ) ( WavHdr ), 44 );
    /* ������������� ������� ������������� */
  memcpy( ( char * ) TempBuf + 24, & samplerate, 4 );
   *(( (char *) pcm_ram_player)+0x85) = ( 48 - ( Volume * 2 ) ) + 1;
   *(( (char *) pcm_ram_player)+0x86)=9;
  /* ��������� ������ �� ������������ */
  PlayMelodyInMem( 0x11, TempBuf, 0x140 * 16, 0xFFFF, 0, 0 );
  /* ��������� ���� ������������ ������������ */
  GBS_StartTimerProc( & ahtimer, 16, PlayingProc );

}

/* ��������� ���������������. ������� ���������� ���� Playing=0 */
void P_AudioStop()
{
  /* ��������� ��� */
  SetHookState( 0 );

  /* ����������� �������� ���� ��� ��������� ������������ ��������� ������� */
  //PlayMelodyInMem( 0x11, AudioBuf, 256 + 44, 0xFFFF, 0, 0 );
}


void AudioTerminate()
{
  Playing = 0;
  P_AudioStop();
  if ( AudioBuf != 0 )
  {
    mfree( AudioBuf );
    mfree(TempBuf);
    mfree(WAV_PLAYER);
    AudioBuf = 0;
  }
  //if(pcmbuff!=0){
  //mfree( pcmbuff );
  // pcmbuff=0;
  //}
}

void PlayingProc()
{
  long BUFPOS;

  if ( ( IsCalling() == 0 ) & ( LastIsCalling == 1 ) )
  {
    //playsamplerate=samplerate;
    GBS_StartTimerProc( & ahtimer, 300, P_AudioStart );
    return;
  }
  LastIsCalling = IsCalling();

  switch ( Playing )
  {
    case 0:
      P_AudioStop();
      return;
    case - 1:
      AudioTerminate();
      return;
  }

  if ( nextbuff == 0xFF )
  {
    nextbuff = 1;
    //* ( ( char * ) 0xA879DB90 ) = 0;
    //zeromem( AudioBuf, 44 );
    //AudioBuf = ( void * ) ( GetBuffEnd() - BUFFERSIZE );
    //* ( long * ) 0xA879DC3C = 0;
  }

  BUFPOS = BuffPos();

  if ( ( nextbuff == 1 ) && ( BUFPOS > ( BUFFERSIZE / 4 ) ) )
  {
 

   FillBuffer1(); 
   

    
    nextbuff = 2;
  }

  if ( ( nextbuff == 2 ) && ( BUFPOS < ( BUFFERSIZE / 4 ) ) )
  {
   
   FillBuffer2(); 
   
     
    nextbuff = 1;
  }

  GBS_StartTimerProc( & ahtimer, 8, PlayingProc );
}
