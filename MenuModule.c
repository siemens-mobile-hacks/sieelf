
unsigned char * MenuItems, * ButtonsText;
unsigned int ItemTypes[128];
unsigned char NumOfItems, MenuActive;
signed char Selected,ShowCursor;

int( * MenuOnKeySub ) ( unsigned char key );

void AddMenuItem( char * caption, unsigned int type )
{
  sprintf( & MenuItems[256 * NumOfItems], "%s", caption );
  ItemTypes[NumOfItems] = type;
  NumOfItems++;
}

void DrawMenu()
{
  int i, y;
  if ( NumOfItems == 0 ) return;
  WSHDR * ws = AllocWS( 256 );
  y = 0;
  if(NumOfItems>7) i = Selected - 3; else i=0;
  if ( i < 0 ) i = 0;
  while ( i < NumOfItems )
  {

    wsprintf( ws, & MenuItems[i * 256], RipLen );
    if (( i == Selected )&&(ShowCursor))
    {
      DrawRoundedFrame( 2, y + 7, 127, y + 21, 0, 0, 0, GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 0 ) );
      DrawString( ws, 3, y + 8, 130, y + 21, 3, 1, GetPaletteAdrByColorIndex( 20 ), GetPaletteAdrByColorIndex( 23 ) );
    }
    else
    {
      DrawString( ws, 3, y + 8, 130, y + 21, 3, 1, GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
    }

    i++;
    y += 14;
    if ( y > 84 ) break;
  }
  wsprintf( ws, ButtonsText );
  DrawString( ws, 4, 107, 125, 130, 1, 1, GetPaletteAdrByColorIndex( 20 ), GetPaletteAdrByColorIndex( 23 ) );
  FreeWS( ws );
}

void ClearMenu()
{
  NumOfItems = 0;
  Selected = 0;
  MenuActive = 0;
  ShowCursor=1;
}

void MenuInit()
{
  ClearMenu();
  MenuItems = malloc( 256 * 128 );
}

void MenuFree()
{
  mfree( MenuItems );
}

void MenuTerminate()
{
  mfree( MenuItems );
}

int MenuOnKey(unsigned char key){
  switch(key)
  {
      case DOWN_BUTTON:
      Selected++;
      if(Selected >= NumOfItems)Selected=0;
    break;
    case UP_BUTTON:
      Selected--;
      if(Selected<0)Selected=NumOfItems-1; 
    break;
  }
  return(MenuOnKeySub(key));
}
