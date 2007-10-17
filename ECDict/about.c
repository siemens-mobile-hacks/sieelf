#include "..\inc\swilib.h"
#include "about.h"

extern int screenh;
extern int screenw;

char cr[] = "ECDICT\nEnglish-Chinese DICTionary for Siemens ELF.\n\nby CHC,bingk, 2007.\n";

void about(void)
{
  WSHDR *ws = AllocWS(256);
  str_2ws(ws, cr, sizeof(cr));
  DrawString(ws,5,YDISP,screenw,screenh-SoftkeyH(),FONT_SMALL,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}

