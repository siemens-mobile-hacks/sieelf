
#include "cfi_flash.h"
#include "../api/low_api.h"
#include "patch.h"
#include <string.h>


void flash_write_block(unsigned int fblock, unsigned int block_size, unsigned short *ram)
{
  if (fi.man_id == MAN_AMD || fi.man_id == MAN_FUJITSU)
   {
    flash_write_block_ext_amd((void *)fblock, ram, block_size);
    return;
   } else flash_erase_block_intel((void *)fblock);
   

  if (fi.b_size == 1)
   {
    for (int i = 0; i < block_size/2; i++) 
    flash_write_word_intel((void *)(fblock + i*2), ram[i]);
   } else
     {
      unsigned int ram_buf = (unsigned int)ram;
      for (int i = 0; i < block_size; i+=fi.b_size)
      flash_write_buf_ext_intel((void *)(fblock + i), (unsigned short *)(ram_buf + i), fi.b_size, block_size, fi.wtype);
     }
}

void uni_patch(PATCH_DATA *patch_data, int count, int patch_action, unsigned int block_size, unsigned char *ram)
{
 char s = 0;
 int  i = 0, m = 0;
 unsigned int block_accu = 0xFFFFFFFF;
 while (count)
  {
   char st = patch_data[i].status;
   s = s | (st&0x01);
   if (st == 1)
    {
      if (block_accu == 0xFFFFFFFF)  block_accu = (patch_data[i].address)&(~(block_size - 1));
      unsigned int block_cur = (patch_data[i].address)&(~(block_size - 1));
      if (block_cur == block_accu)
       {
        if (!m)
         {
          memcpy(ram, (char *)(FLASH_BASE_MASK + block_cur), block_size);
          m = 1;
         }
         
        patch_data[i].status = 0;
        int patch_offset = patch_data[i].address - block_cur;
        if (patch_action == PATCH_APPLY)  ram[patch_offset] = patch_data[i].new_data;
        else
         {
          if (patch_data[i].olddata_exist) ram[patch_offset] = patch_data[i].old_data;
         }
       }
    }
    
    if (i < count) i++;
     else 
      {
       if (s == 1)  
       {
         i = 0; s = 0; m = 0; 
         ExecuteSYSIMB();
         flash_write_block(FLASH_BASE_MASK + block_accu, block_size, (unsigned short *)ram);
         block_accu = 0xFFFFFFFF;
       } else break;
      }
  }
}

