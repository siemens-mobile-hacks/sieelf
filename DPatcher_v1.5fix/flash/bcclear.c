
#include "cfi_flash.h"
#include "patch.h"


void bootcore_cleaner()
{
 if (fi.man_id == MAN_AMD || fi.man_id == MAN_FUJITSU) flash_erase_block_amd((void *)FLASH_BASE_MASK);
                                                  else flash_erase_block_intel((void *)FLASH_BASE_MASK);

}

