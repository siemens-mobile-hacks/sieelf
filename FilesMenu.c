char * curpath;
int FilesMenuOnKey( unsigned char key );

void ShowFilesMenu()
{
  ClearMenu();
  zeromem( curpath, 256 );
  MenuOnKeySub = FilesMenuOnKey;
  AddMenuItem( "0:", 0);
  AddMenuItem( "1:", 0 );
  AddMenuItem( "2:", 0 );
  ButtonsText = "0:\\           Open";
  MenuActive = 1;

}

int IsFile(char *name)
{ int i;
i=0;
while(i<200){
if(name[i]==0)break;
if(name[i]=='.')return(1);  
i++; 
}
return(0);  
}

int IsMP3(char *name)
{ int i;
i=0;
while(name[i]!=0)i++;
i--;
if((name[i]!='3'))return(0);
i--;
if((name[i]!='p')&&(name[i]!='P'))return(0);
i--;
if((name[i]!='m')&&(name[i]!='M'))return(0);
return(1);  
}    

void EnumFolder( char *folder )
{
  DIR_ENTRY * dir;
  char * mask;
  mask = malloc( 256 );
  dir = malloc( sizeof( DIR_ENTRY ) );
  zeromem( dir, sizeof( DIR_ENTRY ) );
  if(folder[0]==0x2E){
  err=0;
  while(curpath[err]>0)err++;   
   if(curpath[err-2]==0x3A){
    ShowFilesMenu();
    return;
  };
  err-=2;  
  while(curpath[err]!=0x5C)err--;  
  curpath[err]=0;      
  folder[0]=0;
   }
  sprintf( mask, "%s%s%s", curpath, folder,"\\" );
  memcpy(curpath,mask,256);
  sprintf( mask, "%s%s", curpath, "*.*" );  
  ClearMenu();
  AddMenuItem( "..", 0 );
  if ( FindFirstFile( dir, mask, & err ) == 1 )
  {
    AddMenuItem( dir->file_name, IsFile(&dir->file_name[0]));
    while ( FindNextFile( dir, & err ) == 1 ) AddMenuItem( dir->file_name, IsFile(&dir->file_name[0]) );
  }
  FindClose( dir, & err );
  mfree( mask );
  mfree( dir );
  MenuActive = 1;
}

int FilesMenuOnKey( unsigned char key )
{
 
  switch ( key )
  {
    case RED_BUTTON:
      ShowMainMenu();
      return(0);
    break;        
    case RIGHT_SOFT: 
    case ENTER_BUTTON:
      if(ItemTypes[Selected]==0)EnumFolder( & MenuItems[Selected * 256] );
      else
      {
   
    if(IsMP3(&MenuItems[Selected*256]))
    {
      sprintf(&files[numfiles*256],"%s%s",curpath,&MenuItems[Selected * 256]);
      numfiles++;
      return(0);
    }
      }
    break;
  case LEFT_SOFT:
     EnumFolder( & MenuItems[0] );  
    break;
  }
  ButtonsText = "Back";
  if(MenuItems[Selected*256+1]==0x3A)ButtonsText = "0:\\           Open";
  if(ItemTypes[Selected]==0)ButtonsText = "Back         Open"; else
  {
  if(IsMP3(&MenuItems[Selected*256]))ButtonsText = "Back           Add";
  }
  return ( 0 );
}
