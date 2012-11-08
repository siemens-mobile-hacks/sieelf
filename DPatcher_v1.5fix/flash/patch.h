

typedef struct{
 unsigned int  address;  
 unsigned char old_data;  
 unsigned char new_data;  
 unsigned char olddata_exist;  
 unsigned char status;  
}PATCH_DATA;

#define PATCH_APPLY 0
#define PATCH_UNDO  1

void flash_write_block(unsigned int fblock, unsigned int block_size, unsigned short *ram);
void uni_patch(PATCH_DATA *patch_data, int count, int patch_action, unsigned int block_size, unsigned char *ram);
void v_patch(PATCH_DATA *patch_data, int count, int patch_action);
void bootcore_cleaner();

extern FLASH_INFO fi;




