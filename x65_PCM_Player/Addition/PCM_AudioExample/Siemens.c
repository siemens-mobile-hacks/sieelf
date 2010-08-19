
#include "..\swilib.h"
#include "audiohook\pcmaudiohook.c"
#include "Sinegen.c"

const int minus11 = -11; // �������� ��������� =)
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


void OnRedraw( MAIN_GUI * data ) // OnRedraw
{
  DrawRoundedFrame( 0, 0, ScreenW()-1, ScreenH()-1, 0, 0, 0, GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 20 ) );
  WSHDR * ws = AllocWS( 256 );
  wsprintf( ws, "Any key - play/stop, red button - exit.");
  DrawString( ws, 0, 3, 127, 130, 1, 2, GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
  FreeWS( ws );

}

void onCreate( MAIN_GUI * data, void * ( * malloc_adr ) ( int ) ) //Create
{
  // ��� ����� ������� ����������
  data->gui.state = 1;
}

void onClose( MAIN_GUI * data, void( * mfree_adr ) ( void * ) ) //Close
{
  // ��� ����� ���������� ���������� ������


  Playing=0;
  AudioTerminate();
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

/* ���������� ������� ������. ���� ���������� ������� ������ � ���� ��������� GUI_MSG, ������ ������������� ����. */
int OnKey( MAIN_GUI * data, GUI_MSG * msg ) 
{  
  if (( msg->gbsmsg->msg == KEY_DOWN ))
  {
  
    if(msg->gbsmsg->submess==RED_BUTTON) return(1);
    Paused=!Paused;
  } 

  return (0);
}

#ifdef NEWSGOLD
void onDestroy( MAIN_GUI * data, void( * mfree_adr ) ( void * ) )
{
  // ��� �������� ��� ���� ;)
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

// �������� ��� ����
int method8( void )
{
  return ( 0 );
}

// �������� ��� ����
int method9( void )
{
  return ( 0 );
}

// ������ � ��������, ����� ���� �� ����������, ����� ����� ��������
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

// ������ ��� ��������� GUI
const RECT Canvas =
{
  0, 0, 129, 129
};

// ���������� ��� �������� �������� CSM. � ������ �������
// �������� GUI, ��� ID ������������ � MAINGUI_ID
// �� ������ ������ - ����� ����������� ;)
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

// �� ���� �� �������� ;) �������� ��� ����
void ElfKiller( void )
{
  extern void kill_data( void * p, void( * func_p ) ( void * ) );
  extern void * ELF_BEGIN;
  kill_data( & ELF_BEGIN, ( void( * ) ( void * ) ) mfree_adr() );
}

// ���������� ��� �������� �������� CSM. ��� � ���������� ������
void maincsm_onclose( CSM_RAM * csm )
{
  SUBPROC( ( void * ) ElfKiller );
}

// ���������� ������� �������� CSM
int maincsm_onmessage( CSM_RAM * data, GBS_MSG * msg )
{
  MAIN_CSM * csm = ( MAIN_CSM * ) data;
  if ( ( msg->msg == MSG_GUI_DESTROYED ) && ( ( int )msg->data0 == csm->gui_id ) )
  {
    csm->csm.state = -3;
  }
  return ( 1 );
}

// ������������� ��������� MAINCSM
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

// �������, ������� ������������� �������� ����� CSM ��� X-Task.
void UpdateCSMname( void )
{
  WSHDR * ws = AllocWS( 256 );
  wsprintf( ( WSHDR * ) ( & MAINCSM.maincsm_name ), "HelloWorld" );
  FreeWS( ws );
}


// �������� ���������. ��� ������ �������� ���������� ��� ������ �����.
int main( char * exename, char * fname )
{
  if ( fname )
  {
    char dummy[sizeof( MAIN_CSM )];
    MAINCSM_ID = CreateCSM( & MAINCSM.maincsm, dummy, 0 );
    AudioInit(); 
    samplerate=16000;
    SetVolume(14);
    P_AudioStart(); 

  }
  else
  {
    SUBPROC( ( void * ) ElfKiller );
  }
  return 0;
}
