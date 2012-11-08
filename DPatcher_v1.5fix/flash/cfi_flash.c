#include "cfi_flash.h"



void flash_cmd_send(unsigned int flash_base, unsigned short cmd)
{
 FLASH_BUS_16(flash_base + FLASH_OFFSET_CFI_ALT*FLASH_BUS_16_MUL) = AMD_CMD_UNLOCK_START;
 FLASH_BUS_16(flash_base + FLASH_OFFSET_UNK*FLASH_BUS_16_MUL) = FLASH_OFFSET_CFI;
 FLASH_BUS_16(flash_base + FLASH_OFFSET_CFI_ALT*FLASH_BUS_16_MUL) = cmd;
}


void flash_get_info(FLASH_INFO *f_info, unsigned int flash_base)
{
 flash_cmd_send(flash_base, FLASH_CMD_READ_ID);
 //Replace 2 parametres = OK determing
 f_info->dev_id  = FLASH_BUS_16(flash_base + FLASH_OFFSET_DEVICE_ID*FLASH_BUS_16_MUL);
 f_info->man_id  = FLASH_BUS_16(flash_base + FLASH_OFFSET_MANUFACTURER_ID*FLASH_BUS_16_MUL);

 f_info->dev_id2 = FLASH_BUS_16(flash_base + FLASH_OFFSET_DEVICE_ID2*FLASH_BUS_16_MUL);
 f_info->dev_id3 = FLASH_BUS_16(flash_base + FLASH_OFFSET_DEVICE_ID3*FLASH_BUS_16_MUL);
 
 if (f_info->dev_id == MAN_AMD) FLASH_BUS_16(flash_base) = AMD_CMD_RESET;
  else FLASH_BUS_16(flash_base) = FLASH_CMD_RESET;
 
 FLASH_BUS_16(flash_base + FLASH_OFFSET_CFI*FLASH_BUS_16_MUL) = FLASH_CMD_CFI;
 
 f_info->f_size  = 1<<FLASH_BUS_16(flash_base + FLASH_OFFSET_SIZE*FLASH_BUS_16_MUL);
 f_info->b_size  = 1<<FLASH_BUS_16(flash_base + FLASH_OFFSET_BUFFER_SIZE*FLASH_BUS_16_MUL);
 
 f_info->alt_work = 0;
 
 if (!f_info->f_size)
  {
   FLASH_BUS_16(flash_base + FLASH_OFFSET_CFI_ALT*FLASH_BUS_16_MUL) = FLASH_CMD_CFI;
 
   f_info->f_size  = 1<<FLASH_BUS_16(flash_base + FLASH_OFFSET_SIZE*FLASH_BUS_16_MUL);
   f_info->b_size  = 1<<FLASH_BUS_16(flash_base + FLASH_OFFSET_BUFFER_SIZE*FLASH_BUS_16_MUL);
   f_info->alt_work = 1;
  }
 
 
 f_info->wtype  =  FLASH_BUS_16(flash_base + FLASH_OFFSET_TYPE_WRITE*FLASH_BUS_16_MUL);
 
  if (f_info->dev_id == MAN_AMD) FLASH_BUS_16(flash_base) = AMD_CMD_RESET;
  else FLASH_BUS_16(flash_base) = FLASH_CMD_RESET;
  
  FLASH_BUS_16(flash_base + FLASH_OFFSET_CFI*FLASH_BUS_16_MUL) = FLASH_CMD_CFI; 
  
 f_info->num_er = FLASH_BUS_16(flash_base + FLASH_OFFSET_NUM_ERASE_REGIONS*FLASH_BUS_16_MUL);
 f_info->er   = FLASH_BUS_16(flash_base + FLASH_OFFSET_ERASE_REGIONS*FLASH_BUS_16_MUL) + 1;
 
 if (f_info->dev_id == MAN_AMD) FLASH_BUS_16(flash_base) = AMD_CMD_RESET;
  else FLASH_BUS_16(flash_base) = FLASH_CMD_RESET;
}

int flash_erase_block_amd(void *addr_block)
{
 flash_cmd_send((unsigned int)addr_block, AMD_CMD_ERASE_START);
 flash_cmd_send((unsigned int)addr_block, AMD_CMD_ERASE_SECTOR);
 
 for (int i = 0; i < 0x20000; i++)
   if (FLASH_BUS_16(addr_block) == 0xFFFF) 
     if (FLASH_BUS_16(addr_block) == 0xFFFF) 
       if (FLASH_BUS_16(addr_block) == 0xFFFF) 
        {
         FLASH_BUS_16(addr_block) = FLASH_CMD_READ_ID;
         FLASH_BUS_16(addr_block) = 0x00;
         FLASH_BUS_16(addr_block) = AMD_CMD_RESET;
         return 1;
        }
 
 FLASH_BUS_16(addr_block) = AMD_CMD_RESET;
 return 0;
}


int flash_write_word_amd(void *address, unsigned short word, unsigned int block_size)
{
 unsigned int addr_block = (unsigned int)address&(~(block_size-1));
 flash_cmd_send((unsigned int)addr_block, AMD_CMD_UNLOCK_BYPASS_ENTRY);
 
 FLASH_BUS_16((unsigned int)address) = AMD_CMD_WRITE; 
 FLASH_BUS_16((unsigned int)address) = word; 
   
 for (int i = 0; i < 0x20000; i++)
  {
   if (FLASH_BUS_16((unsigned int)address) == word) 
     if (FLASH_BUS_16((unsigned int)address) == word) 
       if (FLASH_BUS_16((unsigned int)address) == word) 
        {
         FLASH_BUS_16((unsigned int)address) = FLASH_CMD_READ_ID;
         FLASH_BUS_16((unsigned int)address) = 0x00;
         FLASH_BUS_16((unsigned int)address) = AMD_CMD_RESET;
         return 1;
        }
   }
 

 FLASH_BUS_16((unsigned int)addr_block) = AMD_CMD_RESET;
 
 return 0;
}

void flash_write_block_ext_amd(void *addr_block, unsigned short *block, unsigned int block_size)
{
 flash_cmd_send((unsigned int)addr_block, AMD_CMD_UNLOCK_BYPASS_ENTRY_ALT);
  
 FLASH_BUS_16(addr_block) = AMD_CMD_WRITE;
 FLASH_BUS_16(addr_block) = AMD_CMD_ONE;
 FLASH_BUS_16(addr_block) = FLASH_CMD_READ_ID;
 FLASH_BUS_16(addr_block) = AMD_CMD_ZERO;
 
 flash_cmd_send((unsigned int)addr_block, AMD_CMD_ERASE_START);
 flash_cmd_send((unsigned int)addr_block, AMD_CMD_ERASE_SECTOR);
 
 while (FLASH_BUS_16(addr_block) != 0xFFFF); 
 
 flash_cmd_send((unsigned int)addr_block, AMD_CMD_UNLOCK_BYPASS_ENTRY);
 
 
 for (int i = 0; i < block_size / 2; i++) 
  {
   FLASH_BUS_16(addr_block) = AMD_CMD_WRITE;
   FLASH_BUS_16((unsigned int)addr_block + i*2) = block[i];
   while (FLASH_BUS_16((unsigned int)addr_block + i*2) != block[i]); 
  }
 
 FLASH_BUS_16(addr_block) = FLASH_CMD_READ_ID;
 FLASH_BUS_16(addr_block) = AMD_CMD_ZERO;
 
 FLASH_BUS_16(addr_block) = AMD_CMD_RESET;
}


void flash_erase_block_intel(void *addr_block)
{
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_PROTECT;
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_PROTECT_CLEAR;

 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_BLOCK_ERASE;
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_ERASE_CONFIRM;
  
 while (!(FLASH_BUS_16((unsigned int)addr_block)&FLASH_STATUS_DONE));
 
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_PROTECT;
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_PROTECT_SET; 
 
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_RESET;
}


void flash_write_word_intel(void *addr_word, unsigned short word)
{
 FLASH_BUS_16((unsigned int)addr_word) = FLASH_CMD_PROTECT;
 FLASH_BUS_16((unsigned int)addr_word) = FLASH_CMD_PROTECT_CLEAR; 
 
 FLASH_BUS_16((unsigned int)addr_word) = FLASH_CMD_WRITE;
 FLASH_BUS_16((unsigned int)addr_word) = word;
 
 FLASH_BUS_16((unsigned int)addr_word) = FLASH_CMD_READ_STATUS;
 
 while (!(FLASH_BUS_16((unsigned int)addr_word)&FLASH_STATUS_DONE));
 
 FLASH_BUS_16((unsigned int)addr_word) = FLASH_CMD_PROTECT;
 FLASH_BUS_16((unsigned int)addr_word) = FLASH_CMD_PROTECT_SET; 
 
 FLASH_BUS_16((unsigned int)addr_word) = FLASH_CMD_RESET;
}

void flash_write_buf_ext_intel(void *address, unsigned short *buffer, unsigned short buffer_size, unsigned int block_size, int wtype)
{
 unsigned int addr_block = (unsigned int)address&(~(block_size-1)); 
  
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_PROTECT;
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_PROTECT_CLEAR;
 
 if (wtype == 2) FLASH_BUS_16((unsigned int)address) = FLASH_CMD_WRITE_TO_BUFFER_ALT;
  else FLASH_BUS_16((unsigned int)address) = FLASH_CMD_WRITE_TO_BUFFER;

 while (!(FLASH_BUS_16((unsigned int)addr_block)&FLASH_STATUS_DONE));
 
 FLASH_BUS_16((unsigned int)address) = ( buffer_size / 2 ) - 1;
 
 for (int i = 0; i < (buffer_size / 2); i++) FLASH_BUS_16((unsigned int)((unsigned int)address + i*2)) =  buffer[i];
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_WRITE_BUFFER_CONFIRM;
 
 while (!(FLASH_BUS_16((unsigned int)addr_block)&FLASH_STATUS_DONE));
 
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_PROTECT;
 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_PROTECT_SET;

 FLASH_BUS_16((unsigned int)addr_block) = FLASH_CMD_RESET; 
}



