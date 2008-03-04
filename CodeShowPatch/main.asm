
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
#ifdef NEWSGOLD
    PUSH  {LR}
    LDR   R0, =ADDR_IsCalling           //0xA0DE7EA4+1,10B5041C????????4121201C????????D4+22
    BLX   R0
    MOV   R1, R0
    MOV   R0, #1
    MOV   R2, R4
    BL    UpdateLocaleToItem
    LDR   R0, =ADDR_CallIN
    BLX   R0		
    POP   {PC}
#else
    MOV		R0, #0
    MOV		R1, R4
    MOV		R2, R5
    BL    UpdateLocaleToItem
    LDR   R0, =ADDR_CallIN
    BLX   R0		
#endif

Hook3:
#ifdef NEWSGOLD
    LDR	  R0, =ADDR_IsCalling
    BLX	  R0
    MOV	  R1, R0
#ifdef ELKA
    MOV   R0, #4
#else
    MOV   R0, #3
#endif
    MOV   R2, R4
#else
		LDR		R0, =ADDR_CALLX
		BLX		R0
		MOV		R1, R0
		MOV		R0, #3
		MOV		R2, R4
#endif
    BL    UpdateLocaleToItem
    LDR   R0, =ADDR_CallOUT
    BLX   R0

Hook4:
#ifdef NEWSGOLD
#ifndef ELKA
		ADD		R1, SP, #4
#endif
#endif
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
#ifdef NEWSGOLD
#ifdef ELKA
    POP   {PC}
#else
		POP		{R2}
		ADD		R2, #4
		BX		R2
#endif
#else
		POP   {PC}
#endif

#ifndef NEWSGOLD
Hook5:
		PUSH	{LR}
		LDR   R0, [SP,#0x174]
		MOV		R1, #0xA
		LDR		R2, =ADDR_NUMX
		BLX		R2
		LDR   R0, [SP,#0x174]
		LDR   R1, [SP,#0x1D0]
		LDR		R2, =AppendInfoW
		BLX		R2
		MOV   R1, #0
		ADD   R0, R7, #0
		POP	  {PC}
#endif

#ifdef NEWSGOLD
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
    
#ifdef ELKA
HOOKAddrBookWindow_DUMP:
    PUSH  {R7,LR}	
    LDR   R7, =Hook4
    BLX   R7
    POP   {R7,PC}
#endif

    RSEG  RecordWindow:CODE(1)
    CODE16
    BL    HOOKRecoedWindow_DUMP
    
    RSEG Callinwindow:CODE(1)
    CODE16
    BL    HOOKCallinwindow_DUMP
    
    
    RSEG  CallOutWindow:CODE(1)
    CODE16
    BL    HOOKCallOutWindow_DUMP

#ifdef ELKA
    RSEG  AddrBookWindow:CODE(1)
    CODE16
    BL    HOOKAddrBookWindow_DUMP
#else
    RSEG  AddrBookWindow
    CODE32
	  LDR		R4, =Hook4
	  BLX		R4
#endif

#ifndef ELKA
    RSEG  AddrBookWindow2
    DCB		0xFF
#endif


#else
//Hook
// 通话记录修改
    RSEG  RecordWindow:CODE(1)
    CODE16
    BL      Hook1

// 拨入窗口修改，覆盖了group xx的显示位置
    RSEG Callinwindow:CODE(1)
    CODE16
    BL      Hook2

// 拨出窗口修改，覆盖了group xx的显示位置
    RSEG  CallOutWindow:CODE(1)
    CODE16
    BL      Hook3

// 通讯录窗口修改
    RSEG  AddrBookWindow:CODE(1)
    CODE16
    BL      Hook4

		RSEG	AddrBookWindow2:CODE(1)
		CODE16
    DCB		0x21

// 电话本窗口修改
		RSEG	PhonebookWindow:CODE(1)
		CODE16
    BL      Hook5
#endif    
    END