
extern void ShowMainMenu();

int MainMenuOnKey( unsigned char key )
{ 
  switch ( key )
  {   
     
    case RED_BUTTON:
    case LEFT_SOFT:
      MenuActive = 0;
    break;
    case RIGHT_SOFT:
    case ENTER_BUTTON:
      MenuActive = 0;
      switch ( Selected )
      {
        case 0:
          ShowPlaylist();
          return(0);
        case 1:
          ShowFilesMenu();
        break;
        case 2:
          Playing = 0;
          RipLen = 30;
        break;
      case 3:
        loop = loop^1;
        ShowMainMenu();
        Selected=3;
        return(0);
        break;
      case 4:
        if(SoftVol!=16)SoftVol=16; else SoftVol=1;
        ShowMainMenu();
        Selected=4;
        return(0);
        break;
      case 5:
        randomplay=randomplay^1;
        ShowMainMenu();
        Selected=5;
        return(0);
        break;
      case 6:
        ShowAbout();
        break;
      }
    break;
  }

  return ( 0 );
}

void ShowMainMenu()
{ 
 
  ClearMenu();
  MenuOnKeySub = MainMenuOnKey;
  AddMenuItem( "Playlist", 0 );
  AddMenuItem( "Add files to playlist", 0 );
  AddMenuItem( "Rip to wave", 0 );
  if(loop)AddMenuItem( "Repeat On", 0 ); else AddMenuItem( "Repeat Off", 0 );  
  if(SoftVol==1)AddMenuItem("Silent mode", 0 ); else AddMenuItem("Aloud mode", 0 );
  if(randomplay)AddMenuItem( "Random On", 0 ); else AddMenuItem( "Random Off" ,0);
  AddMenuItem( "About", 0 );
  ButtonsText = "Cancel     Select";
  MenuActive = 1;  
}
