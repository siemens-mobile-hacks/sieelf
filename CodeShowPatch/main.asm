
#include "addr.h"

    EXTERN  AppendInfoW
    EXTERN  UpdateLocaleToItem
    EXTERN  do_phonebook_work 

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

#ifdef NEWSGOLD
#ifdef ELKA

HOOKRecoedWindow:
	PUSH		{R0-R2, R4, LR}
	LDR		R0, [R5,#4]
	MOV		R4, R0
	MOV		R1, #0xD
	LDR		R2, =ADDR_wsAppendChar
	BLX		R2
	MOV		R0, R4
	MOV		R1, R4
	BL		AppendInfoW
	POP		{R0-R2, R4}
	ADD		R1, #0xE
	ADD		R0, R4, #0
	LDR		R2, =ADDR_wsAppendChar
	POP		{R1}
	ADD		R1, #4
	BX		R1
	
HOOKCallinwindow:
	LDR		R0, =ADDR_IsCalling
	BLX		R0
	MOV		R1, R0
	MOV		R0, #1
	MOV		R2, R4
	BL		UpdateLocaleToItem
	LDR		R0, =ADDR_CallIN
	BLX		R0
	CMP		R0, #0
	BEQ		EXIT1
	LDR		R1, =ADDR_CallIN1
	BX		R1
EXIT1:
	LDR		R1, =ADDR_CallIN2
	BX		R1
	

Hook3:
	LDR		R0, =ADDR_IsCalling
	BLX		R0
	MOV		R1, R0
	MOV		R0, #4
	MOV		R2, R4
	BL		UpdateLocaleToItem
	LDR		R0, =ADDR_CallOUT
	BX		R0

HOOKCallOutWindow:
	BEQ		Hook3
	MOV		R1, SP
	LDR		R2, =ADDR_CallOUT1
	BLX		R2
	LDR		R2, =ADDR_CallOUT2
	BX		R2

HOOKAddrBookWindow:
	LDR		R0, =0x4CA
	LDR		R4, =ADDR_AllocWS
	BLX		R4
	ADD		R4, R0, #0
	MOV		R1, SP
	LDR		R2, =ADDR_ADDRBook
	BLX		R2
	MOV		R0, R4
	MOV		R1, #0xD
	LDR		R2, =ADDR_wsAppendChar
	BLX		R2
	MOV		R0, R4
	MOV		R1, R4
	BL		AppendInfoW
	LDR		R0, =ADDR_ADDRBook1
	BX		R0
	
SIMBOOK:
	PUSH		{LR}
	ADD		R1, R4, #0
	ADD		R0, R6, #0
	LDR		R3, =ADDR_GetPhoneBookNum
	BLX		R3
	MOV		R0,R4
	MOV		R1,R4
	BL		do_phonebook_work
	POP		{R3}
	ADD		R3, #4
	BX		R3

	CODE16
	RSEG	RecordWindow:CODE(2)
	//BL		HOOKRecoedWindow_DUMP
	LDR		R0, =HOOKRecoedWindow
	BLX		R0

	
	CODE16
	RSEG	Callinwindow:CODE(2)
	//BL		HOOKCallinwindow_DUMP
	LDR		R1,=HOOKCallinwindow
	BX		R1
	
	
	CODE16
	RSEG	CallOutWindow:CODE(2)
	//BL		HOOKCallOutWindow_DUMP
	LDR		R1,=HOOKCallOutWindow
	BX		R1

	CODE16
	RSEG	AddrBookWindow:CODE(2)
	LDR		R0,=HOOKAddrBookWindow
	BX		R0
	//BL		HOOKAddrBookWindow_DUMP

	CODE16
	RSEG	PHONEBOOKHOOK:CODE(2)
	LDR		R1, =SIMBOOK
	BLX		R1

#else
//NEWSGOLD
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
    PUSH	{LR}
    LDR		R0, =ADDR_IsCalling           //0xA0DE7EA4+1,10B5041C????????4121201C????????D4+22
    BLX		R0
    MOV		R1, R0
    MOV		R0, #0
    MOV		R2, R4
    BL		UpdateLocaleToItem
    LDR		R0, =ADDR_CallIN
    BLX		R0		
    POP		{PC}

Hook3:
    LDR		R0, =ADDR_IsCalling
    BLX		R0
    MOV		R1, R0
    MOV		R0, #3
    MOV		R2, R4
    BL		UpdateLocaleToItem
    LDR		R0, =ADDR_CallOUT
    BLX		R0


Hook4:
    ADD		R1, SP, #4
    PUSH	{LR}
    MOV		R4, R0
    LDR		R2, =ADDR_ADDRBook
    BLX		R2
    MOV		R0, R4
    MOV		R1, #0xD
    LDR		R2, =ADDR_NUMX
    BLX		R2
    MOV		R0, R4
    MOV		R1, R4
    BL		AppendInfoW
    POP		{R2}
    ADD		R2, #4
    BX		R2


SIMBOOK:
		PUSH		{LR}
		MOV		R0,R4
		MOV		R1,R4
		BL		do_phonebook_work
		MOV		R3, #3
		POP		{PC}

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

    RSEG  RecordWindow:CODE(1)
    CODE16
    BL    HOOKRecoedWindow_DUMP
    
    RSEG Callinwindow:CODE(1)
    CODE16
    BL    HOOKCallinwindow_DUMP
    
    
    RSEG  CallOutWindow:CODE(1)
    CODE16
    BL    HOOKCallOutWindow_DUMP


    RSEG  AddrBookWindow
    CODE32
    LDR		R4, =Hook4
    BLX		R4


		CODE32
		RSEG	PHONEBOOKHOOK
		BLX		SIMBOOK



    RSEG  AddrBookWindow2:DATA(1)
    DCB		0xFF

#endif
#else
//SGOLD
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
    MOV		R0, #0
    MOV		R1, R4
    MOV		R2, R5
    BL		UpdateLocaleToItem
    LDR		R0, =ADDR_CallIN
    BLX		R0		

Hook3:
    LDR		R0, =ADDR_CALLX
    BLX		R0
    MOV		R1, R0
    MOV		R0, #3
    MOV		R2, R4
    BL		UpdateLocaleToItem
    LDR		R0, =ADDR_CallOUT
    BLX		R0

Hook4:
    PUSH	{LR}
    MOV		R4, R0
    LDR		R2, =ADDR_ADDRBook
    BLX		R2
    MOV		R0, R4
    MOV		R1, #0xD
    LDR		R2, =ADDR_NUMX
    BLX		R2
    MOV		R0, R4
    MOV		R1, R4
    BL		AppendInfoW
    POP		{PC}

Hook5:
    PUSH	{LR}
    LDR		R0, [SP,#0x174]
    MOV		R1, #0xA
    LDR		R2, =ADDR_NUMX
    BLX		R2
    LDR		R0, [SP,#0x174]
    LDR		R1, [SP,#0x1D0]
    LDR		R2, =AppendInfoW
    BLX		R2
    MOV		R1, #0
    ADD		R0, R7, #0
    POP		{PC}


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

    RSEG	AddrBookWindow2:DATA(1)
    DCB		0x21

// 电话本窗口修改
    RSEG	PhonebookWindow:CODE(1)
    CODE16
    BL      Hook5
#endif    

		END