/* IRQ Watchdog Timer API */

#define IRQ_BASE             0xF2800000
#define IRQ_ICURINT          IRQ_BASE + 0x1C
#define IRQ_IRESET           IRQ_BASE + 0x14
#define IRQ_FCURINT          IRQ_BASE + 0x18
#define IRQ_FRESET           IRQ_BASE + 0x08
#define IRQ_PTABLE           IRQ_BASE + 0x30
#define IRQ_GSM_TPU0         0x77
#define IRQ_GSM_TPU1         0x78

                   RSEG CODE:CODE
        
                   //MODE  = IRQ = 0b10010
                   //THUMB = DISABLE
                   //IRQ   = DISABLE
                   //--------------
                   //CPSR_c = 0x92
                   //SPSR_irq = CPSR_sys
                   //LR_irq = LR_sys
                   //SP_irq =

                   EXTERN  WDT_IRQServeProc
                   EXTERN  L1_IRQServeProc
                   EXTERN  IRQ_DisableEventsSaver

                   PUBLIC  IRQ_WDTimer
                   
       IRQ_WDTimer:
       
                   SUB     LR, LR, #0x04
                   STMFD   SP!, {R0-R3, LR}
                   
                   
                   
                   LDR     R0, =IRQ_ICURINT
                   LDR     R0, [R0, #0x00]
                   
                   CMP     R0, #IRQ_GSM_TPU0
                   BEQ     IRQ_GSMTimer
                   
                   CMP     R0, #IRQ_GSM_TPU1
                   BEQ     IRQ_L1Serve
                   
                   BL      IRQ_DisableEventsSaver
                   
                   
  IRQ_WDTimer_end:  
  
                   MOV     R0, #1
                   LDR     R1, =IRQ_IRESET
                   STR     R0, [R1, #0x00]
                   
  
                   LDMFD   SP!, {R0-R3, PC}^
                   
                   
     IRQ_GSMTimer:
     
                   BL      WDT_IRQServeProc
                   B       IRQ_WDTimer_end
                   
      IRQ_L1Serve:
     
                   BL      L1_IRQServeProc
                   B       IRQ_WDTimer_end
                   
                   END