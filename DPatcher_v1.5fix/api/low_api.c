#include "low_api.h"

#include "..\flash\cfi_flash.h"


//EBU API
unsigned int ebu_lock_write[7];

void UnlockFlashWrite()
{

 for (int i = 0; i < 7; i++)  ebu_lock_write[i] = (WORD_REG( EBU_BUSCON0 + i*8 )&0x80000000);

 WORD_REG( EBU_BUSCON0 )  = WORD_REG( EBU_BUSCON0 )&(~0x80000000) ;
 WORD_REG( EBU_BUSCON1 )  = WORD_REG( EBU_BUSCON1 )&(~0x80000000) ;
 WORD_REG( EBU_BUSCON2 )  = WORD_REG( EBU_BUSCON2 )&(~0x80000000) ;
 WORD_REG( EBU_BUSCON3 )  = WORD_REG( EBU_BUSCON3 )&(~0x80000000) ;
 WORD_REG( EBU_BUSCON4 )  = WORD_REG( EBU_BUSCON4 )&(~0x80000000) ;
 WORD_REG( EBU_BUSCON5 )  = WORD_REG( EBU_BUSCON5 )&(~0x80000000) ;
 WORD_REG( EBU_BUSCON6 )  = WORD_REG( EBU_BUSCON6 )&(~0x80000000) ;
}

void LockFlashWrite()
{
 for (int i = 0; i < 7; i++)  WORD_REG( EBU_BUSCON0 + i*8 ) = (WORD_REG( EBU_BUSCON0 + i*8 ) | ebu_lock_write[i]);
}

//Watch Dog API
#ifdef NEWSGOLD
void WDT_Serve()
{
 unsigned int pcl_wdt_value = WORD_REG(PCL_WDT);
 if (!(pcl_wdt_value&0x200)) 
 {
  unsigned int wdt_avail = WORD_REG(WDT_OS_AVAIL);
  if (!wdt_avail) WORD_REG(PCL_WDT) = WORD_REG(PCL_WDT)|0x200;
   else return;
 }  else WORD_REG(PCL_WDT) = WORD_REG(PCL_WDT)&(~0x200);
 WORD_REG(WDT_OS_COUNT) = WORD_REG(STM_TIMER0);
 WORD_REG(WDT_OS_STAT) = 0;
}
#else
void WDT_Serve()
{
 unsigned int pcl_wdt_value = WORD_REG(PCL_WDT);
 if (!(pcl_wdt_value&0x200)) WORD_REG(PCL_WDT) = WORD_REG(PCL_WDT)|0x200;
  else WORD_REG(PCL_WDT) = WORD_REG(PCL_WDT)&(~0x200);
 WORD_REG(WDT_OS_COUNT) = WORD_REG(STM_TIMER0);
 WORD_REG(WDT_OS_STAT) = 0;
}
#endif

int isWDT_Serveable()
{
 unsigned int stm0_cur = WORD_REG(STM_TIMER0);
 unsigned int wdt_cur = WORD_REG(WDT_OS_COUNT);
 if ((stm0_cur - wdt_cur) < WDT_PERIOD) return 0;
  else return 1;
}

void WDT_ServeIfPossible()
{
 if (isWDT_Serveable()) WDT_Serve();
}

void WDT_WaitAndServe()
{
 while (!isWDT_Serveable());
 WDT_Serve();
}

//IRQ

unsigned int IRQ_PRIO_DISABLE_LIST[0x80];

void IRQ_DisableEventsOpen()
{
 for (int i = 0; i < 0x80; i++) IRQ_PRIO_DISABLE_LIST[i] = 0x11223344;
}

void IRQ_DisableEventsSaver(unsigned int_loc)
{
 IRQ_PRIO_DISABLE_LIST[int_loc] = WORD_REG(IRQ_PTABLE + int_loc*4);
 WORD_REG(IRQ_PTABLE + int_loc*4) = 0x00;
}

void IRQ_DisableEventsClose()
{
  for (int i = 0; i < 0x80; i++)
   {
    if (IRQ_PRIO_DISABLE_LIST[i] != 0x11223344)
     {
       WORD_REG(IRQ_PTABLE + i*4) = IRQ_PRIO_DISABLE_LIST[i];
     }
   }
  for (int i = 0; i < 0x80; i++) IRQ_PRIO_DISABLE_LIST[i] = 0x11223344;
}

unsigned int irq_fiq[2] = {0,0};

void DisableIRQ_Manually()
{
 irq_fiq[IRQ_GREED] = WORD_REG(IRQ_VECTOR_ADDRESS);
 WORD_REG(IRQ_VECTOR_ADDRESS)   = SUBS_PC_LR_4_OPCODE;
}

void DisableFIQ_Manually()
{
 irq_fiq[FIQ_GREED] = WORD_REG(IRQ_VECTOR_ADDRESS);
 WORD_REG(FIQ_VECTOR_ADDRESS)   = SUBS_PC_LR_4_OPCODE;
}

void EnableIRQ_Manually()
{
 WORD_REG(IRQ_VECTOR_ADDRESS)   = irq_fiq[IRQ_GREED];
}

void EnableFIQ_Manually()
{
 WORD_REG(FIQ_VECTOR_ADDRESS)   = irq_fiq[FIQ_GREED];
}


//IRQ + WDT

unsigned int irq_hand_value = 0;

void WDT_IRQInstall()
{
 irq_hand_value = WORD_REG(IRQ_VECTOR_PROC);
 IRQ_DisableEventsOpen();
 WORD_REG(IRQ_VECTOR_PROC) = (unsigned int)&IRQ_WDTimer;
}


void WDT_IRQUnInstall()
{
 WORD_REG(IRQ_VECTOR_PROC) = irq_hand_value;
 IRQ_DisableEventsClose();
}


void WDT_IRQServeProc()
{
 WORD_REG(GSM_TPU_ICR2) = WORD_REG(GSM_TPU_ICR2) | 0x4000;
 WDT_ServeIfPossible();
}

void L1_IRQServeProc()
{
 WORD_REG(GSM_TPU_ICR3) = WORD_REG(GSM_TPU_ICR3) | 0x4000;
}

