
#define IRQ_VECTOR_ADDRESS      0x18  
#define FIQ_VECTOR_ADDRESS      0x1C 

#define IRQ_VECTOR_PROC         0x34

#define IRQ_GREED               0x00
#define FIQ_GREED               0x01 

#ifndef NEWSGOLD
//SGold
#define WDT_OS_BASE             0x80414
#define WDT_OS_0                WDT_OS_BASE + 0x00
#define WDT_OS_1                WDT_OS_BASE + 0x04
#define WDT_OS_COUNT            WDT_OS_BASE + 0x08
#define WDT_OS_STAT             WDT_OS_BASE + 0x0C
#define WDT_PERIOD              600000  
#else
#ifdef ELKA
//NewSGold E/EL71
#define WDT_OS_BASE             0x82238
#define WDT_OS_0                WDT_OS_BASE + 0x00
#define WDT_OS_1                WDT_OS_BASE + 0x04
#define WDT_OS_COUNT            WDT_OS_BASE + 0x08
#define WDT_OS_STAT             WDT_OS_BASE + 0x0C
#define WDT_OS_AVAIL            WDT_OS_BASE + 0x10
#define WDT_PERIOD              2200000  
#else
//NewSGold S/SL75 - C/M81
#define WDT_OS_BASE             0x817F0
#define WDT_OS_0                WDT_OS_BASE + 0x00
#define WDT_OS_1                WDT_OS_BASE + 0x04
#define WDT_OS_COUNT            WDT_OS_BASE + 0x08
#define WDT_OS_STAT             WDT_OS_BASE + 0x0C
#define WDT_OS_AVAIL            WDT_OS_BASE + 0x10
#define WDT_PERIOD              2200000  
#endif
#endif


#define SUBS_PC_LR_4_OPCODE     0xE25EFF01  
 
#define EBU_BASE                0xF0000000

#define EBU_BUSCON0             EBU_BASE + 0x0C0  //EBU Memory Region 0 External Bus Configuration Register
#define EBU_BUSCON1             EBU_BASE + 0x0C8  //EBU Memory Region 1 External Bus Configuration Register
#define EBU_BUSCON2             EBU_BASE + 0x0D0  //EBU Memory Region 2 External Bus Configuration Register
#define EBU_BUSCON3             EBU_BASE + 0x0D8  //EBU Memory Region 3 External Bus Configuration Register
#define EBU_BUSCON4             EBU_BASE + 0x0E0  //EBU Memory Region 4 External Bus Configuration Register
#define EBU_BUSCON5             EBU_BASE + 0x0E8  //EBU Memory Region 5 External Bus Configuration Register
#define EBU_BUSCON6             EBU_BASE + 0x0F0  //EBU Memory Region 6 External Bus Configuration Register

#define STM_BASE                0xF4B00000
#define STM_TIMER0              STM_BASE + 0x10

#define PCL_BASE                0xF4300000
#define PCL_WDT                 PCL_BASE + 0x118

#define IRQ_BASE                0xF2800000
#define IRQ_ICURINT             IRQ_BASE + 0x1C
#define IRQ_IRESET              IRQ_BASE + 0x14
#define IRQ_FCURINT             IRQ_BASE + 0x18
#define IRQ_FRESET              IRQ_BASE + 0x08
#define IRQ_PTABLE              IRQ_BASE + 0x30
#define IRQ_GSM_TPU0            0x77
#define IRQ_GSM_TPU1            0x78


#define GSM_TPU_BASE            0xF6400000
#define GSM_TPU_ICR2            GSM_TPU_BASE + 0xF8
#define GSM_TPU_ICR3            GSM_TPU_BASE + 0xFC

#define WORD_REG(w)            *( (unsigned int   *) ( w ) )
#define HWRD_REG(h)            *( (unsigned short *) ( h ) )
#define BYTE_REG(b)            *( (unsigned char  *) ( b ) )

extern void UnLockAccess();
extern void UnLockSYSAccess();
extern void UnlockCFI();
extern int *GetTBaseAddr();
extern int *GetTBaseSYSAddr();
extern void ExecuteIMB();
extern void ExecuteSYSIMB();

extern void InitSystemMode();
extern void InitUserMode();

extern void DisableInterrupts();
extern void EnableInterrupts();

extern void IRQ_WDTimer();


void UnlockFlashWrite();
void LockFlashWrite();

void WDT_Serve();
int  isWDT_Serveable();
void WDT_ServeIfPossible();
void WDT_WaitAndServe();

void WDT_IRQInstall();
void WDT_IRQUnInstall();

void DisableIRQ_Manually();
void DisableFIQ_Manually();

void EnableIRQ_Manually();
void EnableFIQ_Manually();

