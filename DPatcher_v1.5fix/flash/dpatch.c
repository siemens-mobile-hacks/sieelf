
#include "../flash/cfi_flash.h"
#include "dpatch.h"
#include <string.h>


#define memcpy_wdt memcpy

extern FLASH_INFO fi;

void flash_write_block(unsigned int fblock, unsigned int block_size, unsigned short *ram)
{
  int k = 0, amd_errors = 50;
  if (fi.man_id == MAN_AMD) flash_erase_block_amd((void *)fblock);
                       else flash_erase_block_intel((void *)fblock);

  for (int i = 0; i < block_size/2; i++)
   {
    if (k > 64)
     {
      k = 0;
     } else k++;
           
     if (fi.man_id == MAN_AMD)
      {
       int e = flash_write_word_amd((void *)(fblock + i*2), ram[i], block_size);
       if (!e)
        {
         i--;
         amd_errors--;
         if (!amd_errors) break;
        }
      } else 
       {
         flash_write_word_intel((void *)(fblock + i*2), ram[i]);
       }
   }
}
                                                                         // 0 - apply / 1 - undo / 2 -  check
int dp_patch(unsigned int fbase, char *ram_buf, char *patch_body, int patch_size, char patch_action)
{
 int current_b = 0; 
 int current_o = 0; 
 unsigned short num_block = 0, lenght = 0, p = 0;
 int offset = 0;
 int block_size = 0;

 if (patch_body[patch_size - 1] == '|') 
  {
   block_size = patch_body[patch_size - 4]*0x10000 + patch_body[patch_size - 3]*0x100 + patch_body[patch_size - 2];
   if (block_size != fi.f_size/0x100) return DPR_WEB;
  } else return DPR_NOEND;
 
 while (1)
  {
   current_o = 4; p = 0;
   if (patch_body[current_b + 0] == '[' && patch_body[current_b + 3] == ']')
    {
     num_block = patch_body[current_b + 1]*0x100 + patch_body[current_b + 2];
     if (num_block == 0xFFFF) return DPR_DONE; //Ok
     else 
      {
       if (patch_action != 2)
       memcpy_wdt(ram_buf, (char *)(fbase + num_block*block_size), block_size);
       
       while ((patch_body[current_b + current_o] != '[') || p == 0)
        {
         offset = patch_body[current_b + current_o  + 0]*0x10000 + patch_body[current_b + current_o  + 1]*0x100 + patch_body[current_b + current_o  + 2];
         if (offset > block_size - 1) return DPR_ROE; //Range offset error
         else
          {
           lenght = patch_body[current_b + current_o + 4];
           if (lenght == 0) return DPR_ZLD; //Zero lenght data
           else 
            {
             //if no oldata then
             if (patch_body[current_b + current_o + 5] == ';')
              {
               if (patch_action == 1 && patch_action != 2) for (int i = 0; i < lenght; i++) ram_buf[offset + i] = 0xFF;
               if (patch_action == 0 && patch_action != 2)
               memcpy_wdt((char *)(ram_buf + offset), (char *)(patch_body + current_b + current_o + 6), lenght);
                 
               current_o += (lenght + 7);
               p++;
              } else 
                  {
                   if (patch_action == 1 && patch_action != 2)
                   memcpy_wdt((char *)(ram_buf + offset), (char *)(patch_body + current_b + current_o + 6), lenght);
                 
                   current_o += lenght;
                   
                   if (patch_action == 0 && patch_action != 2)
                   memcpy_wdt((char *)(ram_buf + offset), (char *)(patch_body + current_b + current_o + 7), lenght);
                   
                   current_o += (lenght + 8);
                   p++ ;
                  }
              }
            }
          }
        
          current_b += current_o;
          if (patch_action != 2)
          flash_write_block(fbase + num_block*block_size, block_size,  (unsigned short *)ram_buf);
        }
      }  else return DPR_NOEND; // No END
   }
}

