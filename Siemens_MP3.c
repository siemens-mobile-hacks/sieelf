

#include "mp3dec\mp3dec.c"

char * MP3Buf, * MP3Bufpos;
HMP3Decoder MP3DEC;
int mp3handle;
int bytesLeft, offset,  framesize;
unsigned int err;
signed short * Wavebuf, * framebuf;
unsigned long samplepos, framepos, samplesize, samplerate;
MP3FrameInfo mp3FrameInfo;
char PlayMp3, endoffile, channels;

//signed int lastvalue;

void ReadMp3File()
{
  int bytes;
  if ( endoffile == 1 ) return;
  memcpy( MP3Buf, MP3Bufpos, bytesLeft );
  bytes = fread( mp3handle, ( void * ) ( MP3Buf + bytesLeft ), MAINBUF_SIZE - bytesLeft, & err );
  if ( bytes == 0 )
  {
    endoffile = 1;
    //lseek(mp3handle,0,0,&err,&err);
  }
  bytesLeft += bytes;
  MP3Bufpos = MP3Buf;
}

void FreeMp3(){
fclose( mp3handle, & err );
if(MP3Buf)mfree( MP3Buf );
if(Wavebuf)mfree( Wavebuf );
if(framebuf)mfree( framebuf );
//MP3FreeDecoder(MP3DEC); //Вырубает телефон
}

signed short GetSound()
{
  int i;
  if ( PlayMp3 == 0 ) return ( 0 );
  samplepos = samplepos + ( ( 65536 * samplerate ) / 16000 );

  if ( samplepos >= ( samplerate * 65536 ) )
  {
    samplepos -= ( samplerate * 65536 );
    i = 0;
    while ( i < samplerate )
    {
      Wavebuf[i] = framebuf[framepos];
      framepos+=channels;
      i++;
      if ( framepos >= samplesize )
      {
        offset = MP3FindSyncWord( MP3Bufpos, bytesLeft );
        if ( offset < 0 )
        {
          PlayMp3 = 0;
          return ( 0 );
        }

        MP3Bufpos = MP3Bufpos + offset;
        bytesLeft = bytesLeft - offset;
        err = MP3Decode( MP3DEC, & MP3Bufpos, & bytesLeft, framebuf, 0 );

        if ( bytesLeft < 2 * MAINBUF_SIZE )
        {
          ReadMp3File();
        }

        framepos=0;
      }
    }
  }
  //ADD=(*62914+2621*lastvalue)/65536;
  //lastvalue=ADD;
  return Wavebuf[samplepos >> 16];
}

void Mp3Init()
{  int i;

  MP3Buf=0;
  Wavebuf=0;
  framebuf=0;
  MP3Buf = malloc( MAINBUF_SIZE );
  mp3handle = fopen( filename, A_ReadOnly + A_BIN, P_READ, & err );
  if(mp3handle==-1){
    PlayMp3 = 0;
    return;
  }
  bytesLeft = fread( mp3handle, MP3Buf, MAINBUF_SIZE, & err );
  //
  MP3DEC = MP3InitDecoder();
  MP3Bufpos = MP3Buf;
  offset = MP3FindSyncWord( MP3Bufpos, bytesLeft );
  MP3Bufpos = MP3Bufpos + offset;
  bytesLeft -= offset;
  framebuf = malloc( 16384 );
  err = MP3Decode( MP3DEC, & MP3Bufpos, & bytesLeft, framebuf, 0 );
  mfree( framebuf );
  MP3GetLastFrameInfo( MP3DEC, & mp3FrameInfo );
  framebuf = malloc( mp3FrameInfo.outputSamps * 2 );
  Wavebuf = malloc( mp3FrameInfo.samprate * 2 );
  zeromem(Wavebuf,mp3FrameInfo.samprate * 2);
  samplesize = mp3FrameInfo.outputSamps;
  samplerate = mp3FrameInfo.samprate;
  channels = mp3FrameInfo.nChans;
  samplepos = 0;
  framepos = 0;
  samplepos = ( samplerate * 65536 );
  PlayMp3 = 1;
  endoffile = 0;
  MP3Bufpos = MP3Buf;
  bytesLeft = 0;
  fclose( mp3handle, & err );
  mp3handle = fopen( filename, A_ReadOnly + A_BIN, 0, & err );
  ReadMp3File();
}
