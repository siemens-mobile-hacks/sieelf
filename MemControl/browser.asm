//browser launch patch
//�� �ӧ�֧٧ܧ�� �ߧ֧ާߧ�ԧ� ���ڧ٧ӧ�ѧ�ѧݧ�� ...

#include "config\config.h"          
           
            RSEG    PATCH_BROWSER_ENTER1:CODE
            
            CODE16
           
            BLX      browser_arm_jump
            
            RSEG    PATCH_BROWSER_ENTER2:CODE
            
            CODE32
            
browser_arm_jump:

            B      browser_control
            

            RSEG    CODE:CODE
          
           
            
browser_control:
            
            
            BEQ     bc
            CMP     R0, #0x09
            BX      LR
            
         bc:
          
            LDR     R11, =RAMFORPATCHADDR
            LDRB    R11, [R11, #0x08]
            
            CMP     R11, #0x00
            BEQ     end_bc
            LDR     R11, =STARTBROWSER
            
            PUSH   {LR}
            
            BLX     R11
            
            POP    {LR}
            
    end_bc:
    
            ADD     LR, LR, #0x0C
            BX      LR
                       
            
            END