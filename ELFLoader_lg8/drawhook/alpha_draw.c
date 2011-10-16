//  Draw Hook //
//alpha_draw.c - Drawing translucent images
//(c)Dimadze


//24-bit pixel transform into a 16-bit
#define RGB16(R,G,B) ((B>>3)+((G>>2)<<5)+((R>>3)<<11))

#define PIXEL16  2  //Byte per pixel 16-bit buffer
#define PIXEL32  4  //Byte per pixel 32-bit buffer
#define PIXEL32P 5  //Bytes per pixel equal a packed 32-bit buffer

#include "drawhook.h"


typedef struct{
  short x;
  short y;
  short x2;
  short y2;
}RECT;

typedef struct{
  unsigned char w;
  unsigned char h;
  unsigned short bpnum; //For BW=1, 8bit=5, 16bit=8, 32bit=0x0A, 0x80 - packed
  char *bitmap;
}IMGHDR;

typedef struct{
  unsigned int  bpnum;   // 16bit = 8, 32bit = 0x0A, 0x80 - packed
  unsigned int  w; 
  unsigned int  h;     
  int  zero;    // 0x00000000
  int  trans;   // Sometimes 0xE000 - Use transparency, 0xFFFFFFFF - not used
  char *bitmap;
}EIMGHDR; 


// The following structures are presented in a shortened and sufficient for us as
// in reality they may be longer than ...
// These curves do not I come up with the structure, so do not berate yourself

typedef struct{
  char    id_5;    // 0x05 (ID)
  char    cbyte;   // 0x00, 0x10
  char    zero;    // 0x00
  int     pen;     
  int     brush;
  RECT    rc;  
  IMGHDR  *img;
}DRWOBJ_5;

typedef struct{
  char    id_17;   // 0x17 (ID)
  char    cbyte;   // 0x00, 0x10
  char    zero;    // 0x00
  int     pen;          
  int     brush;
  RECT    rc;  
  EIMGHDR *eimg;
}DRWOBJ_17;

typedef struct{
  int    w;       // Width of the screen
  int    h;       // Height of the screen
  RECT   unk_rc;  // 
  RECT   rc;      // Global border rendering
  char   *buf;    // Address of the screen buffer
  int    col;     // Something with color screen 
}SCREEN_STRUCT;


__thumb unsigned short mixcolor(short bg, char *font) //Calculation of color with alpha channel
{
 char r = (((bg&0xF800)>>8)*(0xFF-font[3])+font[0]*font[3])/0xFF;
 char g = (((bg&0x7E0)>>3)*(0xFF-font[3])+font[1]*font[3])/0xFF;
 char b = (((bg&0x1F)<<3)*(0xFF-font[3])+font[2]*font[3])/0xFF;
 return RGB16(r,g,b);
}


__thumb void DrawObject_0x05_0x0A(DRWOBJ_5 *obj, SCREEN_STRUCT *scr)
{
 //Here pixel-handle / draw IMGHDR
 for (int h=0;h<obj->img->h;h++) 
  {
   for (int w=0;w<obj->img->w*PIXEL32;w+=PIXEL32) 
    {
      if (obj->rc.x+w/PIXEL32 <= scr->rc.x2 && obj->rc.x+w/PIXEL32 >= scr->rc.x && obj->rc.y+h <= scr->rc.y2 && obj->rc.y+h >= scr->rc.y)
       {
        char color[4];
       
        color[3]=obj->img->bitmap[w + obj->img->w*PIXEL32*h + 3]; 
        
        //If alfakanal == 0%, fucking write this pixel in the buffer?
        if (color[3]>0x00)  
         { 
          color[0]=obj->img->bitmap[w + obj->img->w*PIXEL32*h + 2];
          color[1]=obj->img->bitmap[w + obj->img->w*PIXEL32*h + 1];
          color[2]=obj->img->bitmap[w + obj->img->w*PIXEL32*h + 0];  
         
          //That is, if alfakanal == 100% (255), compute the fuck color?
          if (color[3]==0xFF) *(unsigned short *)((char *)scr->buf + obj->rc.y*scr->w*PIXEL16 + PIXEL16*obj->rc.x + w/2 + h*scr->w*PIXEL16) = RGB16(color[0],color[1],color[2]);
          else
           //This alfakanal if <100% (255), but not equal to 0 (the most resource-intensive cases)
           *(unsigned short *)((char *)scr->buf + obj->rc.y*scr->w*PIXEL16 + PIXEL16*obj->rc.x + w/2 + h*scr->w*PIXEL16) = mixcolor(*(unsigned short *)((char *)scr->buf + obj->rc.y*scr->w*PIXEL16 + PIXEL16*obj->rc.x + w/2 + h*scr->w*PIXEL16),color); 
         }
       }
    }
  }
}



__thumb void DrawObject_0x05_0x8A(DRWOBJ_5 *obj, SCREEN_STRUCT *scr)
{
 signed char repeat; //Current number of reps / different pixel
 unsigned int n = 0; //render the current cycle
 unsigned int p = 0; //The current amendment
 short x = 0, y = 0; //Current position, drawn pictures
 
 //Here, handle / draw IMGHDR
 while (n < 0xFFFFFFFF)
  {
   char color[4];
   //Read number of repetitions
   repeat = obj->img->bitmap[n*PIXEL32P + p*4];
   //If ye duplicate pixels
   if (repeat > 0)
    {
     //Koeffetsent transparency
     color[3]=obj->img->bitmap[n*PIXEL32P + p*4 +4];
     //If you do not bother to count the total transparency of the color
     if (color[3] > 0x00)
      {
       color[0]=obj->img->bitmap[n*PIXEL32P + p*4 + 3];
       color[1]=obj->img->bitmap[n*PIXEL32P + p*4 + 2];
       color[2]=obj->img->bitmap[n*PIXEL32P + p*4 + 1];
      }
     //§°§ä§â§Ú§ã§à§Ó§Ü§Ñ §à§Õ§ß§à§Ô§à §á§à§Ó§ä§à§â§ñ§ð§ë§Ö§Ô§ã§ñ §á§Ú§Ü§ã§Ö§Ý§ñ 
     while (repeat > 0)
      {
        //Different boundary scan
        if (obj->rc.x+x <= scr->rc.x2 && obj->rc.x+x >= scr->rc.x && obj->rc.y+y <= scr->rc.y2 && obj->rc.y+y >= scr->rc.y && color[3]>0x00)
         {
           //That is, if alfakanal == 100% (255), compute the fuck color?
           if (color[3]==0xFF) *(unsigned short *)((char *)scr->buf + obj->rc.y*scr->w*PIXEL16 + PIXEL16*obj->rc.x + x*2 + y*scr->w*PIXEL16) = RGB16(color[0],color[1],color[2]);
           else
           //This alfakanal if <100% (255), but not equal to 0 (the most resource-intensive cases)
           *(unsigned short *)((char *)scr->buf + obj->rc.y*scr->w*PIXEL16 + PIXEL16*obj->rc.x + x*2 + y*scr->w*PIXEL16) = mixcolor(*(unsigned short *)((char *)scr->buf + obj->rc.y*scr->w*PIXEL16 + PIXEL16*obj->rc.x + x*2 + y*scr->w*PIXEL16),color); 
         }
        //Office of the coordinates of rendering
        if (x < obj->img->w - 1) x++; else {y++; x = 0;}
        //Reduce the recurrence of
        repeat--;
      }
     } else 
         {
          //If ye different pixels
          while (repeat < 0)
           {
             //§¬§à§ï§æ§æ§Ö§è§Ö§ß§ä §á§â§à§Ù§â§Ñ§é§ß§à§ã§ä§Ú
             color[3]=obj->img->bitmap[n*PIXEL32P + p*4 + 4];
             //If you do not bother to count the total transparency of the color
             if (color[3] > 0x00)
              {
               color[0]=obj->img->bitmap[n*PIXEL32P + p*4 + 3];
               color[1]=obj->img->bitmap[n*PIXEL32P + p*4 + 2];
               color[2]=obj->img->bitmap[n*PIXEL32P + p*4 + 1];
              }
             //Different boundary scan
             if (obj->rc.x+x <= scr->rc.x2 && obj->rc.x+x >= scr->rc.x && obj->rc.y+y <= scr->rc.y2 && obj->rc.y+y >= scr->rc.y && color[3]>0x00)
              {
                //That is, if alfakanal == 100% (255), compute the fuck color?
                if (color[3]==0xFF) *(unsigned short *)((char *)scr->buf + obj->rc.y*scr->w*PIXEL16 + PIXEL16*obj->rc.x + x*2 + y*scr->w*PIXEL16) = RGB16(color[0],color[1],color[2]);
                else
                 //This alfakanal if <100% (255), but not equal to 0 (the most resource-intensive cases)
                 *(unsigned short *)((char *)scr->buf + obj->rc.y*scr->w*PIXEL16 + PIXEL16*obj->rc.x + x*2 + y*scr->w*PIXEL16) = mixcolor(*(unsigned short *)((char *)scr->buf + obj->rc.y*scr->w*PIXEL16 + PIXEL16*obj->rc.x + x*2 + y*scr->w*PIXEL16),color); 
              } 
            //Office of the coordinates of rendering
            if (x < obj->img->w - 1) x++; else {y++; x = 0;}
            //Increase the amendment
            if (repeat < -1) p++;
            //Decrease the repetition
            repeat++;
           }
         }
   //Manage the completion of the main loop, rendering
   if ((x == 0 && y >= obj->img->h) || obj->rc.y + y > scr->h) n = 0xFFFFFFFF; else n++;
  }
}


__thumb void FuncDistributor_0x05(DRWOBJ_5 *obj, SCREEN_STRUCT *scr)  //The distributor is to render the #0x05
{
 if (obj->img->bpnum == 0x0A) DrawObject_0x05_0x0A(obj, scr);
 if (obj->img->bpnum == 0x8A) DrawObject_0x05_0x8A(obj, scr);
}

__thumb void FuncDistributor_0x17(DRWOBJ_17 *obj_17, SCREEN_STRUCT *scr) //The distributor, training, and render the #0x17(Java)
{
  IMGHDR img;
  DRWOBJ_5 *obj_5;
 
  img.w = obj_17->eimg->w;
  img.h = obj_17->eimg->h;
  img.bpnum = obj_17->eimg->bpnum;
  img.bitmap = obj_17->eimg->bitmap;
 
  obj_5 = (DRWOBJ_5 *)obj_17;
  obj_5->img = &img;
  
  if (obj_5->img->bpnum == 0x0A) DrawObject_0x05_0x0A(obj_5, scr);
  if (obj_5->img->bpnum == 0x8A) DrawObject_0x05_0x8A(obj_5, scr);
}
