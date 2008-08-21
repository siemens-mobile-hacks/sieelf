
#include "MenuModule.c"
#include "About.c"
#include "Playlist.c"
#include "FilesMenu.c"
#include "MainMenu.c"

extern void SaveParams();
extern char *ExtractFileName(char *ptr);
const int minus11 = -11; // стремная константа =)
extern int onstart( char * exename, char * fname );
unsigned short maincsm_name_body[140];
extern unsigned short speed;
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
extern void PlayCurrentLong();
#define MSG_GUI_DESTROYED 152



typedef struct
{
  CSM_RAM csm;
  int gui_id;
}
MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR * ws1;
  WSHDR * ws2;
  int i1;
}
MAIN_GUI;

void UpdateShowName()
{
memcpy(showfilename,ExtractFileName(filename),64);
}

void OnRedraw( MAIN_GUI * data ) // OnRedraw
{
  DrawRoundedFrame( 0, 0, 129, 129, 0, 0, 0, GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 20 ) );
  DrawRoundedFrame( 0, 106, 130, 130, 0, 0, 0, GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 0 ) );
  if ( MenuActive )
  {
    DrawMenu();
  }
  else
  {
    WSHDR * ws = AllocWS( 256 );
    if ( Ripping > 0 )
    {
      DrawRoundedFrame( 8, 59, 120, 82, 0, 0, 0, GetPaletteAdrByColorIndex( 4 ), GetPaletteAdrByColorIndex( 20 ) );
      DrawRoundedFrame( 8, 59, 8 + ( ( Ripping - RipLen ) * 112 / Ripping ), 82, 0, 0, 0, GetPaletteAdrByColorIndex( 4 ),
           GetPaletteAdrByColorIndex( 4 ) );
      wsprintf( ws, "Rip %d %", ( ( Ripping - RipLen ) * 100 / Ripping ) );
      DrawString( ws, 0, 60, 130, 130, 1, 2, GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
      wsprintf( ws, "Stop", ( ( Ripping - RipLen ) * 100 / Ripping ) );
      DrawString( ws, 82, 107, 130, 130, 1, 2, GetPaletteAdrByColorIndex( 20 ), GetPaletteAdrByColorIndex( 23 ) );
      FreeWS( ws );
      return;
    }
    if ( RipLen == 0 )
    {

      wsprintf( ws, "%d:%d", PlayTime / 960000, PlayTime / 16000 - ( ( PlayTime / 960000 ) * 60 ) );
      DrawString( ws, 0, 82, 130, 102, 1, 2, GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
      //
      if ( Playing == 1 )
      {
        if ( Paused )
        {
          DrawImg( 60, 112, 284 );
        }
        else
        {
          DrawImg( 60, 112, 283 );
        }
        wsprintf( ws, "Stop         Menu" );
      }
      else
      {
        wsprintf( ws, "Play         Menu" );
      }
      DrawString( ws, 4, 107, 125, 130, 1, 1, GetPaletteAdrByColorIndex( 20 ), GetPaletteAdrByColorIndex( 23 ) );

      wsprintf( ws, showfilename );
      DrawString( ws, 3, 6, 127, 48, 3, 2, GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
      //Volume*8+
      wsprintf( ws, "Volume %d",Volume);
      DrawString( ws, 3, 48, 127, 82, 3, 2, GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
    }
    else
    {
      wsprintf( ws, "Rip <%d> sec", RipLen );
      DrawString( ws, 0, 60, 130, 130, 1, 2, GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
      wsprintf( ws, "Cancel         Rip", RipLen );
      DrawString( ws, 4, 107, 125, 130, 1, 1, GetPaletteAdrByColorIndex( 20 ), GetPaletteAdrByColorIndex( 23 ) );
    }
    FreeWS( ws );
  }
}

void onCreate( MAIN_GUI * data, void * ( * malloc_adr ) ( int ) ) //Create
{
  // Тут можно создать переменные

  data->gui.state = 1;
}

void onClose( MAIN_GUI * data, void( * mfree_adr ) ( void * ) ) //Close
{
  // Тут можно освободить выделяемую память
  SaveParams();
  mfree( showfilename );
  mfree( files );
  MenuFree();
  mfree( filename );
  mfree( curpath );
  AudioTerminate();
  SetLoop( 0 );
  data->gui.state = 0;
}

void onFocus( MAIN_GUI * data, void * ( * malloc_adr ) ( int ), void( * mfree_adr ) ( void * ) ) //Focus
{
  data->gui.state = 2;
}

void onUnfocus( MAIN_GUI * data, void( * mfree_adr ) ( void * ) ) //Unfocus
{
  if ( data->gui.state != 2 ) return;
  data->gui.state = 1;
}

int RipKeys( unsigned char key )
{
  switch ( key )
  {

    case LEFT_SOFT:
    case RED_BUTTON:
      RipLen = 0;
    break;
    case RIGHT_SOFT:
      SUBPROC( ( void * ) RipToFile, 1 );
      return(0);
    case RIGHT_BUTTON:
      if ( RipLen < 600 ) RipLen++;

    break;
    case LEFT_BUTTON:
      if ( RipLen > 5 ) RipLen--;
    break;
  }
  return ( 0 );
}

int ControlKeys( unsigned char key )
{
  switch ( key )
  {
    case RIGHT_BUTTON:
      if ( fromplaylist != 0 )
      {
        if(!randomplay)currentfile++;
        if(randomplay){
        curfilerand=currentfile;
        while(curfilerand==currentfile){
          curfilerand=randint(numfiles);
        }
        currentfile=curfilerand;
      }
        if ( currentfile >= numfiles ) currentfile = 0;
        memcpy( filename, & files[currentfile * 256], 256 );
        UpdateShowName();
        newfile = 1;
      }
    break;

    case LEFT_BUTTON:
      if ( fromplaylist != 0 )
      {
        if(!randomplay)currentfile--;
        if(randomplay){
        curfilerand=currentfile;
        while(curfilerand==currentfile){curfilerand=randint(numfiles);}
        currentfile=curfilerand;
      }
        if ( currentfile < 0 ) currentfile = numfiles - 1;
        memcpy( filename, & files[currentfile * 256], 256 );
        UpdateShowName();
        newfile = 1;
      }
    break;

    case UP_BUTTON:
      if ( Volume < 4 )
      {
          Volume++;
          ChangeVolume( Volume );
        }
  break;

  case DOWN_BUTTON :
  if ( Volume > 0 )
  {
      Volume--;
      ChangeVolume( Volume );
    }    
  break;
  case RED_BUTTON:
   Playing = 0;
  return (1);
  case LEFT_SOFT :
  if ( Playing == 0 )
  {
    PlayCurrent();
  }
  else
  {
    Playing = 0;
  };
  break;

  case ENTER_BUTTON : Paused = Paused ^ 1;
  break;
  case RIGHT_SOFT : ShowMainMenu();
  break;
}
return ( 0 );
}



/* Обработчик нажатий клавиш. Сюда передаются нажатия клавиш в виде сообщения GUI_MSG, пример декодирования ниже. */
int OnKey( MAIN_GUI * data, GUI_MSG * msg ) //OnKey
{
int i = 0;

if ( ( msg->gbsmsg->msg == KEY_DOWN ) || ( msg->gbsmsg->msg == LONG_PRESS ) )
{
if ( MenuActive )
{
i = ( MenuOnKey( msg->gbsmsg->submess ) );
REDRAW();
}
else
{
if ( Ripping > 0 )
{
if ( msg->gbsmsg->submess == RIGHT_SOFT )
{
Ripping = Ripping - RipLen;
RipLen = 0;
}
return ( 0 );
}
if ( RipLen == 0 )
{
i = ControlKeys( msg->gbsmsg->submess );
}
else
{
i = RipKeys( msg->gbsmsg->submess );
}

}
REDRAW();
}

return ( i );
}



#ifdef NEWSGOLD
void onDestroy( MAIN_GUI * data, void( * mfree_adr ) ( void * ) )
{
// Это оставить как есть ;)
mfree_adr( data );
}

#else
extern void kill_data( void * p, void( * func_p ) ( void * ) );



void method7( MAIN_GUI * data, void( * mfree_adr ) ( void * ) )
{
kill_data( data, mfree_adr );
mfree_adr( data );
}



#endif

// Оставить как есть
int method8( void )
{
return ( 0 );
}



// Оставить как есть
int method9( void )
{
return ( 0 );
}



// Массив с методами, чтобы дать ОС информацию, какие когда вызывать
const void * const gui_methods[11] =
{
( void * ) OnRedraw, //Redraw
( void * ) onCreate, //Create
( void * ) onClose, //Close
( void * ) onFocus, //Focus
( void * ) onUnfocus, //Unfocus
( void * ) OnKey, //OnKey
0,
#ifdef NEWSGOLD
( void * ) onDestroy, //Destroy
#else
( void * ) kill_data, //Destroy
#endif
( void * ) method8, ( void * ) method9, 0
};



// Канвас для основного GUI
const RECT Canvas =
{
0, 0, 129, 129
};



// Вызывается при создании главного CSM. В данном примере
// создаётся GUI, его ID записывается в MAINGUI_ID
// на всякий случай - вдруг понадобится ;)
void maincsm_oncreate( CSM_RAM * data )
{
MAIN_GUI * main_gui = malloc( sizeof( MAIN_GUI ) );
MAIN_CSM * csm = ( MAIN_CSM * ) data;
zeromem( main_gui, sizeof( MAIN_GUI ) );
main_gui->gui.canvas = ( void * ) ( & Canvas );
main_gui->gui.flag30 = 2;
main_gui->gui.methods = ( void * ) gui_methods;
main_gui->gui.item_ll.data_mfree = ( void( * ) ( void * ) ) mfree_adr();
csm->csm.state = 0;
csm->csm.unk1 = 0;
csm->gui_id = CreateGUI( main_gui );
MAINGUI_ID = csm->gui_id;
}



// Всё ясно из названия ;) оставить как есть
void ElfKiller( void )
{
extern void kill_data( void * p, void( * func_p ) ( void * ) );
extern void * ELF_BEGIN;
kill_data( & ELF_BEGIN, ( void( * ) ( void * ) ) mfree_adr() );
}



// Вызывается при закрытии главного CSM. Тут и вызывается киллер
void maincsm_onclose( CSM_RAM * csm )
{
SUBPROC( ( void * ) ElfKiller );
}



// Обработчик событий главного CSM
int maincsm_onmessage( CSM_RAM * data, GBS_MSG * msg )
{
MAIN_CSM * csm = ( MAIN_CSM * ) data;
if ( ( msg->msg == MSG_GUI_DESTROYED ) && ( ( int )msg->data0 == csm->gui_id ) )
{
csm->csm.state = -3;
}
return ( 1 );
}

// Инициализация структуры MAINCSM
const struct
{
CSM_DESC maincsm;
WSHDR maincsm_name;
}



MAINCSM =
{
{
maincsm_onmessage, maincsm_oncreate,
#ifdef NEWSGOLD
0, 0, 0, 0,
#endif
maincsm_onclose, sizeof( MAIN_CSM ), 1, & minus11
},
{
maincsm_name_body, NAMECSM_MAGIC1, NAMECSM_MAGIC2, 0x0, 139
}
};



// Функция, которая устанавливает название этого CSM для X-Task.
void UpdateCSMname( void )
{
WSHDR * ws = AllocWS( 256 );
wsprintf( ( WSHDR * ) ( & MAINCSM.maincsm_name ), "MP3 Player" );
FreeWS( ws );
}



// Основная процедура. Она первой получает управление при старте эльфа.
int main( char * exename, char * fname )
{
if ( fname )
{
char dummy[sizeof( MAIN_CSM )];
MAINCSM_ID = CreateCSM( & MAINCSM.maincsm, dummy, 0 );
onstart( exename, fname );
}
else
{
SUBPROC( ( void * ) ElfKiller );
}
return 0;
}
