#include "IMA_ADPCM.C"

extern void UpdateShowName();
extern signed short GetSound();
char RipLen, Ripping;
unsigned char Volume = 2;
char * buffer;
char currbuf, offcount,randomplay;
long *WaveParams;
unsigned char WavHdr[60] =
{
  0x52, 0x49, 0x46, 0x46, 0x34, 0x4D, 0x4B, 0x00, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20, 0x14, 0x00, 0x00, 0x00, 0x11,
       0x00, 0x01, 0x00, 0x80, 0x3E, 0x00, 0x00, 0xAE, 0x1F, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x02, 0x00, 0xF9, 0x01, 0x66,
       0x61, 0x63, 0x74, 0x04, 0x00, 0x00, 0x00, 0x00, 0x89, 0x94, 0x00, 0x64, 0x61, 0x74, 0x61, 0x00, 0x4D, 0x4B, 0x00
};


unsigned char * ima1;
signed short * wave;
GBSTMR timer;
unsigned long WB;
char Playing, Paused;
unsigned long PlayTime;
void PB();
const int BUFFERSIZE = 16384;
char SoftVol;

void SetLoop( unsigned char loopstate ){
WaveParams[-0x1C]=loopstate;  
}

void ZeroCounter(){
WaveParams[0x0B]=0;    
}

long GetBuffEnd(){
return(WaveParams[0x08]);  
}

long GetBuffPos(){
return(WaveParams[0x07]);  
}

void RipToFile()
{
  Ripping = RipLen;
  IMA_ADPCM_WAV_HDR * NewWavHeader;
  char * ripfname;
  int wavhandle, i;
  unsigned char * ripbuff;
  ripbuff = malloc( 8192 );
  ripfname = malloc( 256 );
  sprintf( ripfname, "%s.wav", filename );
  wavhandle = fopen( ripfname, A_ReadWrite + A_BIN + A_Append + A_Create, P_READ + P_WRITE, & err );
  mfree( ripfname );
  //Ripping
  Mp3Init();
  fwrite( wavhandle, & WavHdr, 60, & err );
  while ( RipLen > 0 )
  {
    WB = 0;
    while ( WB < 8192 )
    {
      i = 0;
      while ( i < 506 )
      {
        wave[i] = GetSound();
        i++;
      }
      ImaCodeBlock( wave, & ripbuff[WB] );
      WB = WB + 256;
    }

    fwrite( wavhandle, ripbuff, 8192, & err );
    REDRAW();
    RipLen--;
  }
  NewWavHeader = malloc( 60 );
  memcpy( NewWavHeader, & WavHdr, 60 );
  NewWavHeader->DataBytes = Ripping * 8192;
  NewWavHeader->DataSize = Ripping * 8192;
  lseek( wavhandle, 0, 0, & err, & err );
  fwrite( wavhandle, NewWavHeader, 60, & err );
  mfree( NewWavHeader );
  fclose( wavhandle, & err );
  mfree( ripbuff );
  Ripping = 0;
  RipLen = 0;
  REDRAW();

}



void FillBuffer()
{
  int i;
  WB = 60;
  while ( WB < ( ( BUFFERSIZE / 2 ) + 60 ) )
  {
    i = 0;
    while ( i < 506 )
    {
      wave[i] = GetSound() / SoftVol;
      i++;
    }
    if ( Playing == 0 )
    {
      return;
    }
    ImaCodeBlock( wave, & ima1[WB] );
    WB = WB + 256;
  }
}

void FillBuffer1()
{
  int i;
  ZeroCounter();
  WB = 0;
  while ( WB < ( BUFFERSIZE / 2 ) )
  {
    if ( Paused )
    {
      zeromem( wave, 1012 );
    }
    else
    {
      i = 0;
      while ( i < 506 )
      {
        wave[i] = GetSound() / SoftVol;
        i++;
      }
      PlayTime += 506;
    }
    if ( Playing == 0 )
    {
      return;
    }
    ImaCodeBlock( wave, & buffer[WB] );
    WB = WB + 256;
  }
}

void FillBuffer2()
{
  int i;
  WB = BUFFERSIZE / 2;
  while ( WB < BUFFERSIZE )
  {
    if ( Paused )
    {
      zeromem( wave, 1012 );
    }
    else
    {
      i = 0;
      while ( i < 506 )
      {
        wave[i] = GetSound() / SoftVol;
        i++;
      }
      PlayTime += 506;
    }
    if ( Playing == 0 )
    {
      return;
    }
    ImaCodeBlock( wave, & buffer[WB] );
    WB = WB + 256;
  }
}

void AudioInit()
{
  WaveParams=(void*)0xA0FD426C;
  WaveParams=(void*)WaveParams[0];
  newfile = 0;  
  ima1 = malloc( BUFFERSIZE + 60 );
  wave = malloc( 1014 );
  memcpy( ima1, ( void * ) ( WavHdr ), 60 );
  RipLen = Ripping = 0;
}

void AudioStart()
{
  newfile = 0;
  offcount = 0;
  Playing = 1;
  PlayTime = 0;
  Paused = 0;
  currbuf = 2;
  FillBuffer();
  SetLoop( 128 );
  PlayMelodyInMem( 0x11, ima1, BUFFERSIZE + 60, 0xFFFF, 0, 0 );
  GBS_StartTimerProc( & timer, 8, PB );
}

void AudioStop()
{
  Playing = 0;
  FreeMp3();  
  SetLoop( 0 );
  PlayMelodyInMem( 0x11, ima1, 256 + 60, 0xFFFF, 0, 0 );
  PlayTime = 0;
  REDRAW();
}


void AudioTerminate()
{
  PlayMelodyInMem( 0x11, ima1, 256 + 60, 0xFFFF, 0, 0 );
  mfree( ima1 );
  mfree( wave );
}


long BuffPos()
{
  return ( GetBuffPos() - ( long )buffer );
}

void PB()
{
  int BUFPOS;
  if ( Playing == 0 )
  {
    AudioStop();
    return;
  }

  if ( newfile != 0 )
  {
    FreeMp3();
    PlayTime = 0;
    Mp3Init();
    newfile = 0;
  }

  if ( currbuf == 2 )
  {
    currbuf = 1;
    buffer = ( void * ) ( GetBuffEnd() - BUFFERSIZE );
    ChangeVolume( Volume );
  }
  BUFPOS = BuffPos();
  if ( ( currbuf == 0 ) && ( BUFPOS > ( BUFFERSIZE / 2 ) ) )
  {
    FillBuffer1();
    randint(0);
    if ( PlayMp3 == 0 ) offcount++;
    currbuf = 1;
    REDRAW();
  }
  if ( ( currbuf == 1 ) && ( BUFPOS < ( BUFFERSIZE / 2 ) ) )
  {
    FillBuffer2();
    if ( PlayMp3 == 0 ) offcount++;
    currbuf = 0;
    REDRAW();
  }

  if ( offcount > 2 )
  {
    offcount = 0;
    if ( ( loop == 1 ) && ( fromplaylist == 0 ) )
    {
      newfile = 1;
      GBS_StartTimerProc( & timer, 8, PB );
      return;
    }


    if ( ( numfiles > 0 ) && ( fromplaylist != 0 ) )
    {
      if(!randomplay)currentfile++;
      if(randomplay){
        curfilerand=currentfile;
        while(curfilerand==currentfile){curfilerand=randint(numfiles);}
        currentfile=curfilerand;
      }
      if ( currentfile >= numfiles ){
        currentfile = 0;
        if(loop==0){
          Playing = 0;
          GBS_StartTimerProc( & timer, 8, PB );
        }
      }
      memcpy( filename, & files[currentfile * 256], 256 );
      UpdateShowName();
      newfile = 1;
      GBS_StartTimerProc( & timer, 8, PB );
      return;
    }

    Playing = 0;
    GBS_StartTimerProc( & timer, 8, PB );
  }
  GBS_StartTimerProc( & timer, 8, PB );
}
