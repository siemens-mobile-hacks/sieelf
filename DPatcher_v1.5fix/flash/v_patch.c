
#include "cfi_flash.h"
#include "../api/low_api.h"
#include "patch.h"
#include <string.h>

void v_patch(PATCH_DATA *patch_data, int count, int patch_action)
{
#ifndef NEWSGOLD
 UnLockSYSAccess();
 int *trans_base = GetTBaseSYSAddr();
#else
 UnLockAccess();
 int *trans_base = GetTBaseAddr();
#endif
 for (int i = 0; i < count; i++)
  {
    unsigned int addr = FLASH_BASE + patch_data[i].address;
    unsigned short element = ((int)addr>>0x14)&0xFFF;
    int *coarse_table = (int *)(((int)trans_base[element])&0xFFFFF000);
    unsigned short subelement = ((int)addr>>0x0C)&0xFF;
    char *rampage = (char *)((coarse_table[subelement])&0xFFFFF000);
    short patch_byte = ((int)addr)&0xFFF;
#ifndef NEWSGOLD
    ExecuteSYSIMB();
    if (patch_action == PATCH_APPLY)
    rampage[patch_byte] = patch_data[i].new_data;
    else
     {
      if (patch_data[i].olddata_exist)
      rampage[patch_byte] = patch_data[i].old_data;
     }
#else
    ExecuteIMB();
    DisableInterrupts();
    if (patch_action == PATCH_APPLY)
    rampage[patch_byte] = patch_data[i].new_data;
    else
     {
      if (patch_data[i].olddata_exist)
      rampage[patch_byte] = patch_data[i].old_data;
     }
    EnableInterrupts();
#endif
  }
}
