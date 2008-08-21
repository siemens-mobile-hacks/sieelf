
int AboutOnKey( unsigned char key )
{
  switch ( key )
  {   
    case RIGHT_SOFT:
    case RED_BUTTON:
      MenuActive = 0;
    break;
      }

  return ( 0 );
}

void ShowAbout(){ 
  ClearMenu();
  ShowCursor=0;
  MenuOnKeySub = AboutOnKey;
  AddMenuItem( "  MP3 Player elf 1.0", 0 );
  AddMenuItem( "          ILYA_ZX", 0 );  
  AddMenuItem( "rusman2005@mail.ru", 0 );  
  MenuActive = 1;  
  ButtonsText = "                    OK";
}
