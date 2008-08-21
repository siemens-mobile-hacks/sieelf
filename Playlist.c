
extern void ShowMainMenu();
void ShowPlaylist();

int PlaylistOnKey( unsigned char key )
{ int misc;
  switch ( key )
  {
    case LEFT_SOFT:
      memcpy( & files[Selected * 256], & files[Selected * 256 + 256], 128 * 256 - Selected * 256 );      
      numfiles--;
      misc=Selected;
      ShowPlaylist();
      Selected=misc;
      if(Selected>=NumOfItems)Selected--;
    break;
    case RED_BUTTON:
      ShowMainMenu();
    break;
    case RIGHT_SOFT:
    case ENTER_BUTTON:
      MenuActive = 0;
      memcpy( filename, & files[Selected * 256], 256 );
      UpdateShowName();      
      currentfile = Selected;
      fromplaylist = 1;      
      if(Playing==0)PlayCurrent(); else newfile = 1;
    break;

  }
  return ( 0 );
}

void ShowPlaylist()
{
  int i, p;

  ClearMenu();
  if ( numfiles == 0 ) return;
  MenuOnKeySub = PlaylistOnKey;
  i = 0;
  while ( i < numfiles )
  {
    p = 0;
    while ( files[i * 256 + p] > 0 ) p++;
    while ( files[i * 256 + p] != 0x5C ) p--;
    AddMenuItem( & files[i * 256 + p + 1], 0 );
    i++;
  }

  ButtonsText = "Delete        Play";
  MenuActive = 1;

}



