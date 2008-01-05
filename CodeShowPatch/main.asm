
#include "addr.h"

    EXTERN  AppendInfoW
    EXTERN  UpdateLocaleToItem

    RSEG  CODE
    
    CODE16
    
    PUBLIC strlen
strlen:
    PUSH  {R4, LR} 
    LDR   R4, =ADDR_strlen
    BLX   R4
    POP   {R4, PC}
    
    PUBLIC memcmp
memcmp:
    PUSH  {R4, LR} 
    LDR	  R4, =ADDR_memcmp
    BLX   R4
    POP   {R4, PC}
    
    PUBLIC atou
atou:
    PUSH  {R4, LR} 
    LDR	  R4, =ADDR_atou
    BLX   R4
    POP   {R4, PC}
    
    PUBLIC WS_InitByZero
WS_InitByZero:
    PUSH  {R4, LR} 
    LDR	  R4, =ADDR_WS_InitByZero
    BLX   R4
    POP   {R4, PC}
    
    PUBLIC GetCalleeNumber
GetCalleeNumber:
    PUSH  {R4, LR} 
    LDR	  R4, =ADDR_GetCalleeNumber
    BLX   R4
    POP   {R4, PC}
    
    PUBLIC UpdateWndItem
UpdateWndItem:
    PUSH  {R4, LR} 
    LDR   R4, =ADDR_UpdateWndItem
    BLX   R4
    POP   {R4, PC}


Hook1:
    PUSH  {R0-R1,R4,LR}
    MOV   R4, R0
    LDR   R2, =ADDR_RECORD1
    BLX   R2
    MOV   R0, R4
    MOV   R1, #0xD
    LDR   R2, =ADDR_NUMX
    BLX   R2
    POP   {R0-R1,R4}
    BL    AppendInfoW	
    POP   {PC}

Hook2:
    PUSH  {LR}
    LDR   R0, =ADDR_IsCalling           //0xA0DE7EA4+1,10B5041C????????4121201C????????D4+22
    BLX   R0
    MOV   R1, R0
    MOV   R0, #1
    MOV   R2, R4
//	MOV		R2, R5
    BL    UpdateLocaleToItem
    LDR   R0, =ADDR_CallIN
    BLX   R0		
    POP   {PC}

Hook3:
    LDR	  R0, =ADDR_IsCalling
    BLX	  R0
    MOV	  R1, R0
    MOV	  R0, #4
    MOV   R2, R4
    BL    UpdateLocaleToItem
    LDR   R0, =ADDR_CallOUT
    BLX   R0

Hook4:
    PUSH  {LR}
    MOV   R4, R0
    LDR   R2, =ADDR_ADDRBook
    BLX   R2
    MOV   R0, R4
    MOV   R1, #0xD
    LDR   R2, =ADDR_NUMX
    BLX   R2
    MOV   R0, R4
    MOV   R1, R4
    BL    AppendInfoW
    POP   {PC}


    RSEG  HOOK_DUMP
    CODE16
HOOKRecoedWindow_DUMP:
    PUSH  {R7,LR}	
    LDR   R7, =Hook1
    BLX   R7
    POP   {R7,PC}
HOOKCallinwindow_DUMP:
    LDR   R7, =Hook2
    BX    R7
HOOKCallOutWindow_DUMP:
    LDR   R7, =Hook3
    BLX   R7
HOOKAddrBookWindow_DUMP:
    PUSH  {R7,LR}	
    LDR   R7, =Hook4
    BLX   R7
    POP   {R7,PC}
    
    RSEG  RecordWindow:CODE(1)
    CODE16
    BL    HOOKRecoedWindow_DUMP
    
    RSEG Callinwindow:CODE(1)
    CODE16
    BL    HOOKCallinwindow_DUMP
    
    
    RSEG  CallOutWindow:CODE(1)
    CODE16
    BL    HOOKCallOutWindow_DUMP

    RSEG  AddrBookWindow:CODE(1)
    CODE16
    BL    HOOKAddrBookWindow_DUMP
    
    END