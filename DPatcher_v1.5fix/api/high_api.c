#include "..\..\inc\swilib.h"

#include "high_api.h"
#include "low_api.h"

#include "..\gui\log.h"
#include "..\flash\cfi_flash.h"
#include "..\flash\patch.h"

#include "..\virtual\virtual.h"

#include "..\fwork\fwork.h"
#include "..\parser\vkp_parser.h" 

// ---------- Patcher Mode API ----------


int patcher_mode = 0;
void DPatcher_SetMode()
{
 patcher_mode = 0;
 lprintf("模式设为 \"RAM模式\"!\n");
}

void VPatcher_SetMode()
{
 patcher_mode = 1;
 lprintf("模式设为 \"RAM模式\"!\n");
}

int isPatcherMode()
{
 return patcher_mode;
}


//---------------- Flash Info API ----------------//  

FLASH_INFO fi;
unsigned int flash_support_status = 0;
char *flash_block_buffer = 0;

void FlashInfoSimple()
{
 UnlockCFI();
 flash_get_info((FLASH_INFO *)&fi, FLASH_BASE_MASK); 
 if (!fi.f_size)
  {
   flash_support_status = 0;
   return;
  } else 
     {
      if (fi.f_size > 0x100000*1024)
       {
        flash_support_status = 0;
        return;
       }
     }
 
 switch (fi.man_id)
      {
       case MAN_FLASH_NOSUP:
         flash_support_status = 0;
         return;
       case MAN_INTEL:
         flash_support_status = 1;
         return;
       case MAN_ST:
         flash_support_status = 1;
         return;
       case MAN_AMD:
         flash_support_status = 1;
         return;
       case MAN_FUJITSU:
         flash_support_status = 1;
         return;
       default:
         flash_support_status = 0;
         return;
      }
}
  
void FlashInfoLog()
{
 UnlockCFI();
 flash_get_info((FLASH_INFO *)&fi, FLASH_BASE_MASK);
 
 char p[]="FlashID %04X:%04X\nBank size: 0x%X\nBlock size: 0x%X\n";
                   
 lprintf(p, fi.man_id, fi.dev_id, fi.f_size, fi.f_size/0x100);
 
 
 if (!fi.f_size)
  {
   lprintf("Flash Error!\nZero size!\n\n");
   flash_support_status = 0;
   return;
  } else 
     {
      if (fi.f_size > 0x100000*1024)
       {
        lprintf("Flash Error!\nBig size: 0x%08X bytes!\n\n", fi.f_size);
        flash_support_status = 0;
        return;
       }
     }
 
 
 switch (fi.man_id)
      {
       case MAN_FLASH_NOSUP:
        {
         lprintf("Flash isn\'t detect!\nERROR!\n\n");
         flash_support_status = 0;
         break;
        }
       case MAN_INTEL:
        {
         lprintf("Flash Manuf: Intel\n\n");
         flash_support_status = 1;
         break;
        }
       case MAN_ST:
        {
         lprintf("Flash Manuf: ST\n\n");
         flash_support_status = 1;
         break;
        }
      case MAN_AMD:
        {
         if (!fi.alt_work)
         lprintf("Flash Manuf: AMD\n\n");
         else
         lprintf("Flash Manuf: Spansion\n\n");
         flash_support_status = 1;
         break;
        }
      case MAN_FUJITSU:
        {
         lprintf("Flash Manuf: Fujitsu\n\n");
         flash_support_status = 1;
         break;
        }
      default:
        {
         lprintf("Flash Manuf: Unknown\nNot support\nERROR!\n\n");
         flash_support_status = 0;
         break;
        }
      }
}

//

void BootCoreCleaner()
{
 ShowMSG(1, (int)"Hi, haker!");
 UnlockCFI();
 flash_get_info((FLASH_INFO *)&fi, FLASH_BASE_MASK);
 //bootcore_cleaner();
}


//---------------- File Buffer API ----------------//  


char *file_buffer = 0;
unsigned int file_size = 0;

void CreateFileBuffer()
{
 file_buffer = (char *)LoadFile(dp_file_path, &file_size);
 if (file_buffer) lprintf("File loaded!\n\"%s\", %d bytes\n\n", dp_file_path, file_size);
  else lprintf("File load error!\n\n");
 InitVKPWorks();
}

void FreeFileBuffer()
{
 if (file_buffer) mfree(file_buffer);
}


//---------------- Nucleus RTOS API Stop/Resume RTOS ----------------//  

void NucleusStop()
{
 WDT_WaitAndServe();
 UnLockAccess();
 DisableIRQ_Manually();
 DisableFIQ_Manually();
 
 InitSystemMode();
 DisableInterrupts();
 WDT_IRQInstall();
 
 EnableIRQ_Manually();
 EnableInterrupts();
}

void NucleusResume()
{
 DisableIRQ_Manually();
 DisableFIQ_Manually();
 
 DisableInterrupts();
 
 WDT_IRQUnInstall();
 
 EnableIRQ_Manually();
 EnableFIQ_Manually();
 
 EnableInterrupts();
 InitUserMode();
 
 WDT_WaitAndServe();
}




//---------------- VKP Work API ----------------//  



int vkp_noolddata = 0;
int vkp_conflict_apply  = 0;
int vkp_conflict_undo   = 0;
int vkp_conflict_repair = 0;

int vkp_error = 1;
char confilct_string_apply[256];
char confilct_string_undo[256];

PATCH_DATA *patch_data = 0;
unsigned int vkp_patched_bytes = 0;
unsigned int vkp_current = 0;

void InitVKPWorks()
{
 vkp_noolddata = 0;
 vkp_conflict_apply  = 0;
 vkp_conflict_undo   = 0;
 vkp_conflict_repair = 0;
 vkp_error = 1;
 patch_data = 0;
 vkp_patched_bytes = 0;
 vkp_current = 0;
}

void LogParseReturn(int e)
{
      lprintf("Return:\n");
      switch (e)
       { 
       case RET_SUCCESS:
         lprintf("RET_SUCCESS");
         break;
       case RET_VKPBODY_IS_NULL: 
         lprintf("RET_VKPBODY_IS_NULL");
         break;
       case RET_UNK_PRAGMA: 
         lprintf("RET_UNK_PRAGMA");
         break;
       case RET_WRONG_PLUS_OFFSET: 
         lprintf("RET_WRONG_PLUS_OFFSET");
         break;
       case RET_WRONG_MINUS_OFFSET: 
         lprintf("RET_WRONG_MINUS_OFFSET");
         break;
       case RET_WRONG_STRING_SYMBOL: 
         lprintf("RET_WRONG_STRING_SYMBOL");
         break;
       case RET_BIG_PLUS_OFFSET: 
         lprintf("RET_BIG_PLUS_OFFSET");
         break;
       case RET_BIG_ADDRESS: 
         lprintf("RET_BIG_ADDRESS");
         break;
       case RET_NOPARITY_DATA: 
         lprintf("RET_NOPARITY_DATA");
         break;
       case RET_OLD_NOT_EQU_NEW: 
         lprintf("RET_OLD_NOT_EQU_NEW");
         break;
       case RET_IS_NO_MEM: 
         lprintf("RET_IS_NO_MEM");
         break;
       case RET_ACTION_PROC_ERROR: 
         lprintf("RET_ACTION_PROC_ERROR");
         break;
       case RET_NONEWDATA: 
         lprintf("RET_NONEWDATA");
         break;
       case RET_HEXVALUE_IS_NULL: 
         lprintf("RET_HEXVALUE_IS_NULL");
         break;
       default: 
         lprintf("RET_UNKNOWN_ERR");
         break;
       }
      lprintf("\n");
}


// ---------- Parser Test ----------

int vkp_test_parser(unsigned int offset, int old_byte, int new_byte,
                                                   int warn_no_old_on_apply,
                                                   int warn_if_new_exist_on_apply,
                                                   int warn_if_old_exist_on_undo,
                                                   int undo)
{
 unsigned char mode = 0; 
  
 char fp_str[544];
 char fp_p[]="%s.log";
 sprintf(fp_str, fp_p, dp_file_path);
 
 mode |= undo&0x01;
 mode |= (warn_if_old_exist_on_undo&0x01)<<1;
 mode |= (warn_if_new_exist_on_apply&0x01)<<2;
 mode |= (warn_no_old_on_apply&0x01)<<3;
 
 if (old_byte == -1)  fbprintf(fp_str, "ADDR: 0x%08X, NEW: 0x%02X, MODE: 0x%X\r\n", offset, new_byte, mode);
   else fbprintf(fp_str, "ADDR: 0x%08X, OLD: 0x%02X, NEW: 0x%02X, MODE: 0x%X\r\n", offset, old_byte, new_byte, mode);
   
 vkp_patched_bytes++; 
 return 1;
}


void VKP_TestParse()
{
 InitVKPWorks();
  
 char fp_str[544];
 char fp_p[]="%s.log";
 sprintf(fp_str, fp_p, dp_file_path);
 
 if (!file_size) 
  {
    lprintf("File buffer is clear!\nParsing Aborted\n\n"); 
    return;
  }
 
 fpclear(fp_str);
 fbprintf(fp_str, "File: %s\r\n----- DPatcher Parser Log Begin -----\r\n", dp_file_path);
 
 int e = VKP_Parse(file_buffer, file_size, vkp_test_parser);
 
 if (vkp_patched_bytes == 0) e = RET_NONEWDATA;
 vkp_error = e;
 if (e == RET_SUCCESS) lprintf("Patch bytes: %d\n", vkp_patched_bytes);
 LogParseReturn(e);
 
 fbprintf(fp_str, "Return: %d\r\n----- DPatcher Parser Log End -----\r\n\r\n", e);
 fbflush(fp_str);
 lprintf("Log: \"%s\"\n\n", fp_str);
}


// ---------- Apply + Undo ----------

char conflict_quest[]=  "\n-------\nConflict detect:\n%s\nContinue?\n-------\n0 - YES\n1 - No\n\n";
char noolddata_quest[]= "\n-------\nOld data isn't detect:\nContinue?\n-------\n0 - YES\n1 - No\n\n";
char conflict_quest_ext[]=  "\n-------\nConflict detect:\n%s\nContinue?\n-------\n0 - YES\n1 - No\n2 - YES with Repair Patch\n\n";
char noolddata_quest_ext[]= "\n-------\nOld data isn't detect:\nContinue?\n-------\n0 - YES\n1 - No\n2 - YES with Repair Patch\n\n";
char apply_user_quest[]="\n-------\nApply Patch?\n-------\n0 - YES\n1 - No\n\n";
char undo_user_quest[]= "\n-------\nUndo Patch?\n-------\n0 - YES\n1 - No\n\n";
char patch_abort[]="Patching Aborted\n\n";

int vkp_counter(unsigned int offset, int old_byte, int new_byte,
                                                   int warn_no_old_on_apply,
                                                   int warn_if_new_exist_on_apply,
                                                   int warn_if_old_exist_on_undo,
                                                   int undo)
{

 unsigned int flash_base = 0;
 if (!isPatcherMode()) flash_base = FLASH_BASE_MASK;
  else flash_base = FLASH_BASE;
  
 if (old_byte == -1 && warn_no_old_on_apply == 1) vkp_noolddata = 1;
 else
  {
   if (vkp_conflict_apply == 0 && BYTE_REG(flash_base + offset) != old_byte && warn_if_new_exist_on_apply == 1) 
    {
      sprintf(confilct_string_apply, "%08X: %02X %02X", offset, old_byte, new_byte);
      vkp_conflict_apply = 1;
    }
   if (vkp_conflict_undo == 0 && BYTE_REG(flash_base + offset) != new_byte && warn_if_old_exist_on_undo == 1) 
    {
      sprintf(confilct_string_undo, "%08X: %02X %02X", offset, old_byte, new_byte);
      vkp_conflict_undo = 1;
    }
  }
   
 vkp_patched_bytes++;  
 return 1;
}

int vkp_struct_builder(unsigned int offset, int old_byte, int new_byte,
                                                int warn_no_old_on_apply,
                                                int warn_if_new_exist_on_apply,
                                                int warn_if_old_exist_on_undo,
                                                int undo)
{
 patch_data[vkp_current].address = offset;
 patch_data[vkp_current].new_data = new_byte;
 if (old_byte == -1 || undo == 0)
  {
   patch_data[vkp_current].old_data = 0;
   patch_data[vkp_current].olddata_exist = 0;
  } else
     {
      patch_data[vkp_current].old_data = old_byte;
      patch_data[vkp_current].olddata_exist = 1;
     }
 patch_data[vkp_current].status = 1;
 
 vkp_current++;
 return 1;
}

int vkp_struct_builder_virtual(unsigned int offset, int old_byte, int new_byte,
                                                int warn_no_old_on_apply,
                                                int warn_if_new_exist_on_apply,
                                                int warn_if_old_exist_on_undo,
                                                int undo)
{
 patch_data[vkp_current].address = offset;
 patch_data[vkp_current].new_data = new_byte;
 if (old_byte == -1 || undo == 0)
  {
   patch_data[vkp_current].old_data = 0;
   patch_data[vkp_current].olddata_exist = 0;
  } else
     {
      patch_data[vkp_current].old_data = old_byte;
      patch_data[vkp_current].olddata_exist = 1;
     }
 patch_data[vkp_current].status = 1;
 
 vkp_current++;
 
 return RelocateFAddresToRAM((void *)(FLASH_BASE + offset));
}

void RepairPatchCreate(PATCH_DATA *patch_data, int count)
{
 char fp_str[544];
 char fp_p[]="%sREPAIR.vkp";
 sprintf(fp_str, fp_p, dp_file_path);
 
 fpclear(fp_str);
 lprintf("Repair Patch:\n\"%s\"\n", fp_str);
 fbprintf(fp_str, ";REPAIR UNDO PATCH\r\n"
                  ";Generated by DPatcher (C)Dimadze\r\n"
                  ";File: \"%s\"\r\n\r\n", dp_file_path);
 
 for (int i = 0; i < count; i++)
   fbprintf(fp_str, "%08X: %02X %02X\r\n", patch_data[i].address, BYTE_REG(FLASH_BASE + patch_data[i].address), patch_data[i].new_data);

 fbprintf(fp_str, "\r\n;---------- END ----------\r\n");
 fbflush(fp_str);
}


void BuildPatchDataAndPatchFlash(int patch_action)
{
 vkp_current = 0;
 patch_data = malloc(sizeof(PATCH_DATA)*vkp_patched_bytes);  
 flash_block_buffer = malloc(fi.f_size/0x100);
 if (patch_data)
  {
   int e = VKP_MainParser(file_buffer, file_size, vkp_struct_builder);
   if (e == RET_SUCCESS && vkp_conflict_repair == 1) RepairPatchCreate(patch_data, vkp_current);
   if (e == RET_SUCCESS)
    {
      if (flash_block_buffer)
       {
        if (flash_support_status)
         {
          NucleusStop();
          UnlockFlashWrite();
          uni_patch(patch_data, vkp_patched_bytes, patch_action, fi.f_size/0x100, (unsigned char *)flash_block_buffer);
          LockFlashWrite();
          NucleusResume();
          lprintf("Patching Complete!\n\n");
         } else lprintf("Patching Aborted!\nYour flash is not support!\n\n");
       } else lprintf("Patching Aborted!\nBlockMem isn't created!\n\n");
    } else lprintf("Patching Aborted!\nUnpredictable Error!\n\n");
  } else lprintf("Patching Aborted!\nNo memory!\n\n");
 if (flash_block_buffer) mfree(flash_block_buffer);
 if (patch_data) mfree(patch_data);
}

void BuildPatchDataAndPatchFRAM(int patch_action)
{
 vkp_current = 0;
 patch_data = malloc(sizeof(PATCH_DATA)*vkp_patched_bytes);  
 if (patch_data)
  {
   int e = VKP_MainParser(file_buffer, file_size, vkp_struct_builder_virtual);
   if (e == RET_SUCCESS && vkp_conflict_repair == 1) RepairPatchCreate(patch_data, vkp_current);
   if (e == RET_SUCCESS)
    {
#ifndef NEWSGOLD
     NucleusStop();
     UnlockFlashWrite();
#endif
     v_patch(patch_data, vkp_patched_bytes, patch_action);
#ifndef NEWSGOLD
     LockFlashWrite();
     NucleusResume();
#endif
     lprintf("Patching Complete!\n\n");
    } else lprintf("Patching Aborted!\nUnpredictable Error!\n\n");
  } else lprintf("Patching Aborted!\nNo memory!\n\n");
 if (patch_data) mfree(patch_data);
}


// ---------- Apply ----------

void VKP_PatchEntry_Apply()
{
 InitVKPWorks();
 if (!file_size) 
  {
    lprintf("File buffer is clear!\nPatching Aborted\n\n"); 
    return;
  }
 
 int e = VKP_Parse(file_buffer, file_size, vkp_counter);

 if (vkp_patched_bytes == 0) e = RET_NONEWDATA;
 vkp_error = e;
 
 if (e == RET_SUCCESS) lprintf("Patch bytes: %d\n", vkp_patched_bytes);
 LogParseReturn(e);
 if (e != RET_SUCCESS) 
  {
    lprintf("Parse error!\nPatching Aborted\n\n"); 
    return;
  }
 
 if (vkp_conflict_apply) 
  {
   char msg[512];
   sprintf(msg, conflict_quest_ext, confilct_string_apply);
   lquest(msg, 3, VKP_PatchConflictQuest_Apply);
  } else
     {
      if (vkp_noolddata) lquest(noolddata_quest_ext, 3, VKP_PatchNoOldDataQuestExt_Apply);
       else lquest(apply_user_quest, 2, VKP_PatchUserQuest_Apply);
     }
}


void VKP_PatchConflictQuest_Apply(int a)
{
 if (a == YES || a == YES_WITH_RP)
  {
   if (a == YES_WITH_RP) vkp_conflict_repair = 1;
   if (vkp_noolddata)  lquest(noolddata_quest, 2, VKP_PatchNoOldDataQuest_Apply);
     else lquest(apply_user_quest, 2, VKP_PatchUserQuest_Apply);
  } else lprintf(patch_abort); 
}

void VKP_PatchNoOldDataQuest_Apply(int a)
{
 if (a == YES) lquest(apply_user_quest, 2, VKP_PatchUserQuest_Apply);
  else lprintf(patch_abort); 
}

void VKP_PatchNoOldDataQuestExt_Apply(int a)
{
 if (a == YES || a == YES_WITH_RP) 
  {
    if (a == YES_WITH_RP) vkp_conflict_repair = 1;
    lquest(apply_user_quest, 2, VKP_PatchUserQuest_Apply);
  }
  else lprintf(patch_abort); 
}

void VKP_PatchUserQuest_Apply(int a)
{
 if (a == YES)
  {
   if (!isPatcherMode()) BuildPatchDataAndPatchFlash(APPLY);
                   else BuildPatchDataAndPatchFRAM(APPLY);
  } else lprintf(patch_abort); 
}

// ---------- Undo ----------

void VKP_PatchEntry_Undo()
{
 InitVKPWorks();
 if (!file_size) 
  {
    lprintf("File buffer is clear!\nPatching Aborted\n\n"); 
    return;
  }
 
 int e = VKP_Parse(file_buffer, file_size, vkp_counter);

 if (vkp_patched_bytes == 0) e = RET_NONEWDATA;
 vkp_error = e;
 
 if (e == RET_SUCCESS) lprintf("Patch bytes: %d\n", vkp_patched_bytes);
 LogParseReturn(e);
 if (e != RET_SUCCESS) 
  {
    lprintf("Parse error!\nPatching Aborted\n\n"); 
    return;
  }
 
 if (vkp_noolddata) 
  {
    lprintf("Not old data!\nPatching Aborted\n\n"); 
    return;
  }
 
 if (vkp_conflict_undo) 
  {
   char msg[512];
   sprintf(msg, conflict_quest, confilct_string_undo);
   lquest(msg, 2, VKP_PatchConflictQuest_Undo);
  } else lquest(undo_user_quest, 2, VKP_PatchUserQuest_Undo);

}

void VKP_PatchConflictQuest_Undo(int a)
{
 if (a == YES) lquest(undo_user_quest, 2, VKP_PatchUserQuest_Undo);
  else lprintf(patch_abort); 
}


void VKP_PatchUserQuest_Undo(int a)
{
 if (a == YES)
  {
   if (!isPatcherMode()) BuildPatchDataAndPatchFlash(UNDO);
                    else BuildPatchDataAndPatchFRAM(UNDO);
  } else lprintf(patch_abort); 
}











