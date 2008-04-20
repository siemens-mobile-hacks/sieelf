
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
    
AddNewLine:
	PUSH		{R0-R7, LR}
	MOV		R1, #0xD
	LDR		R2, =ADDR_wsAppendChar
	BLX		R2
	POP		{R0-R7, PC}

Hook1:
    PUSH  {R0-R1,R4,LR}
    MOV   R4, R0
    LDR   R2, =ADDR_RECORD1
    BLX   R2
    MOV   R0, R4
    BL    AddNewLine
    POP   {R0-R1,R4}
    BL    AppendInfoW	
    POP   {PC}

#ifdef NEWSGOLD
Hook2:
	PUSH		{LR}
	LDR		R0, =ADDR_IsCalling      //0xA0DE7EA4+1,10B5041C????????4121201C????????D4+22
	BLX		R0
	MOV		R1, R0
#ifdef ELKA
	MOV		R0, #1
#else
	MOV		R0, #0
#endif
	MOV		R2, R4
	BL		UpdateLocaleToItem
	LDR		R0, =ADDR_CallIN
	BLX		R0		
	POP		{PC}


Hook3:
	LDR		R0, =ADDR_IsCalling
	BLX		R0
	MOV		R1, R0
#ifdef ELKA
	MOV		R0, #4
#else
	MOV		R0, #3
#endif
	MOV		R2, R4
	BL		UpdateLocaleToItem
	LDR		R0, =ADDR_CallOUT
	BLX		R0

Hook4:
#ifndef ELKA
	ADD		R1, SP, #4
#endif
	PUSH		{LR}
	MOV		R4, R0
	LDR		R2, =ADDR_ADDRBook
	BLX		R2
	MOV		R0, R4
	BL		AddNewLine
	MOV		R1, R4
	BL		AppendInfoW
#ifdef ELKA
	POP		{PC}
#else
	POP		{R2}
	ADD		R2, #4
	BX		R2
#endif

		
		

SIMBOOK:
#ifdef ELKA
	PUSH		{LR}
	ADD		R1, R4, #0
	ADD		R0, R6, #0
	LDR		R3, =ADDR_GetPhoneBookNum
	BLX		R3
	MOV		R0,R4
	MOV		R1,R4
	BL		AddNewLine
	BL		AppendInfoW
	POP		{R3}
	ADD		R3, #4
	BX		R3
#else
	PUSH		{LR}
	MOV		R0,R4
	MOV		R1,R4
	BL		AddNewLine
	BL		AppendInfoW
	MOV		R3, #3
	POP		{PC}
#endif

	RSEG	HOOK_DUMP
	CODE16
HOOKRecoedWindow_DUMP:
	PUSH		{R7,LR}	
	LDR		R7, =Hook1
	BLX		R7
	POP		{R7,PC}
HOOKCallinwindow_DUMP:
	LDR		R7, =Hook2
	BX		R7
HOOKCallOutWindow_DUMP:
	LDR		R7, =Hook3
	BLX		R7
	
#ifdef ELKA
HOOKAddrBookWindow_DUMP:
	PUSH		{R7,LR}	
	LDR		R7, =Hook4
	BLX		R7
	POP		{R7,PC}
#endif

	RSEG	RecordWindow:CODE(1)
	CODE16
	BL		HOOKRecoedWindow_DUMP
	
	RSEG	Callinwindow:CODE(1)
	CODE16
	BL		HOOKCallinwindow_DUMP
	
	
	RSEG	CallOutWindow:CODE(1)
	CODE16
	BL		HOOKCallOutWindow_DUMP

#ifdef ELKA
	RSEG	AddrBookWindow:CODE(1)
	CODE16
	BL		HOOKAddrBookWindow_DUMP
#else
	RSEG	AddrBookWindow
	CODE32
	LDR		R4, =Hook4
	BLX		R4
#endif
#ifdef ELKA
	CODE16
	RSEG	PHONEBOOKHOOK:CODE(2)
	LDR		R1, =SIMBOOK
	BLX		R1
#else
	CODE32
	RSEG	PHONEBOOKHOOK
	BLX		SIMBOOK
#endif	

#ifndef ELKA
	RSEG  AddrBookWindow2:DATA(1)
	DCB		0xFF
#endif

#else
//SGOLD

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
	PUSH		{LR}
	MOV		R4, R0
	LDR		R2, =ADDR_ADDRBook
	BLX		R2
	MOV		R0, R4
	BL		AddNewLine
	MOV		R1, R4
	BL		AppendInfoW
	POP		{PC}

Hook5:
	PUSH		{LR}
	LDR		R0, [SP,#0x174]
	BL		AddNewLine
	LDR		R1, [SP,#0x1D0]
	BL		AppendInfoW
	MOV		R1, #0
	ADD		R0, R7, #0
	POP		{PC}

//���ŷ��Ͷ�������,by BingK(binghelingxi)
	EXTERN		GetProvAndCity
SMS_SEND_WINDOW:
	PUSH		{R4, LR}
	MOV		R2, #0
	ADD		R1, R7, #0
	ADD		R0, R5, #0
	LDR		R3, =ADDR_SMS_SEND
	BLX		R3
	MOV		R0, R5
	BL		AddNewLine
	LDR		R0, [R5, #0]
	POP		{R4}
	MOV		R3, #0xBC
	LDR		R1, [R4, R3]
	BL		GetProvAndCity
	POP		{R0}
	ADD		R0, R0, #4
	BX		R0

//Hook
// ͨ����¼�޸�
	RSEG	RecordWindow:CODE(1)
	CODE16
	BL		Hook1

// ���봰���޸ģ�������group xx����ʾλ��
	RSEG	Callinwindow:CODE(1)
	CODE16
	BL		Hook2

// ���������޸ģ�������group xx����ʾλ��
	RSEG	CallOutWindow:CODE(1)
	CODE16
	BL		Hook3

// ͨѶ¼�����޸�
	RSEG 	AddrBookWindow:CODE(1)
	CODE16
	BL		Hook4

	RSEG	AddrBookWindow2:DATA(1)
	DCB		0x21

// �绰�������޸�
	RSEG	PhonebookWindow:CODE(1)
	CODE16
	BL		Hook5

//���ŷ��Ͷ�������,by BingK(binghelingxi)	
	CODE16
	RSEG	SMS_SEND_HOOK:CODE(2)
	LDR		R2, pSMS_SEND
	BLX		R2
	
	DATA
pSMS_SEND
	DCD		SMS_SEND_WINDOW
	
	CODE16
	NOP
	
#endif
	END