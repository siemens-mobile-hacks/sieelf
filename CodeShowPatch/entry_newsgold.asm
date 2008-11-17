#include "addr.h"

	EXTERN	AppendInfoW
	EXTERN	UpdateLocaleToItem
	EXTERN	AddNewLine	
	EXTERN	GetProvAndCity
	EXTERN	GetNumFromIncomingPDU
	EXTERN	setMenuText
	
	RSEG	CODE
	DATA
MENU_HDR_ICON
	DCD	0x156
	DCD	0
	
	CODE16
RecoedWindow_:
	PUSH	{LR}
	LDRB	R0, [R5, #9]
	CMP	R0, #7
	BCS	EX_PBACK
	LDR	R1, [R5, #4] //ºÅÂë WS ,ÅÐ¶ÏÒþ²ØºÅÂë
	LDR	R0, [R1, #0] //wsbody
	LDRH	R0, [R0, #0] //wslen
	CMP	R0, #0
	BEQ	EX_PBACK
	MOV	R0, R4
	BL	AddNewLine
	BL	AppendInfoW
EX_PBACK
	MOV	R0, R4
	BL	AddNewLine
	MOV	R2, #1
	POP	{R0}
	ADD	R0, #4
	BX	R0

Callinwindow_:
	PUSH	{LR}
	LDR	R0, =ADDR_IsCalling
	BLX	R0
	MOV	R1, R0
	MOV	R0, #0
	MOV	R2, R4
	BL	UpdateLocaleToItem
	LDR	R0, =ADDR_CallIN
	BLX	R0
	CMP	R0, #0	
	POP	{R0}
	BEQ	HOOK1_EQ
	ADD	R0, #4
	BX	R0
HOOK1_EQ
	ADD	R0, #0xC
	BX	R0
	
CallOutWindow_:
	CMP	R0, R6
	BEQ	SHOW_EQ
	MOV	R1, SP
	PUSH	{LR}
	LDR	R2, =ADDR_CallOUT2
	BLX	R2
	POP	{R2}
	ADD	R2, #4
	BX	R2
SHOW_EQ
	PUSH	{LR}
	LDR	R0, =ADDR_IsCalling
	BLX	R0
	MOV	R1, R0
	MOV	R0, #3
	MOV	R2, R4
	BL	UpdateLocaleToItem
	POP	{R0}
	ADD	R0, #0x16
	BX	R0

AddrBookWindow_:
	CMP	R6, #0
	BNE	D_EBACK
	PUSH	{LR}
	MOV	R0, R4
	BL	AddNewLine
	MOV	R1, R4
	BL	AppendInfoW
	MOV	R0, #1
	POP	{PC}
D_EBACK
	MOV	R0, #1
	BX	LR

SIMBOOK:
	PUSH	{LR}
	MOV	R0,R4
	MOV	R1,R4
	BL	AddNewLine
	BL	AppendInfoW
	MOV	R3, #3
	POP	{PC}

#ifndef WITHOUT_SMS_IN_WIN
SMS_IN
	LDR	R0, [SP, #8]
	LDR	R2, [SP, #4]
	PUSH	{R0-R7, LR}
	MOV	R7, R0
	SUB	SP, #0x20
	LDR	R6, =0xAC5 //LGP ÐÂÐÅÏ¢
	CMP	R6, R2
	BNE	GoBack
	ADD	R0, SP, #0
	BL	GetNumFromIncomingPDU
	CMP	R0, #0
	BEQ	GoBack
	MOV	R0, R7
	BL	AddNewLine
	LDR	R0, [R7, #0]
	ADD	R1, SP, #0
	BL	GetProvAndCity
GoBack
	ADD	SP, #0x20
	POP	{R0-R7}
	POP	{R2}
	LDR	R0, [R0, #0] //WSTRLEN
	LDRH	R0, [R0, #0]
	STR	R0, [SP,#0xD8]
	ADD	R2, R2, #4
	BX	R2

#endif

NUM_SELECT_MENU_PSETTEXT: //R2, WS, 
	MOV	R4, LR
	BL	setMenuText
	BX	R4
	
	RSEG	RecordWindow:CODE(2)
	CODE16
	LDR	R0, =RecoedWindow_
	BLX	R0
	
	RSEG	Callinwindow:CODE(2)
	CODE16
	LDR	R0, =Callinwindow_
	BLX	R0
	
	
	RSEG	CallOutWindow:CODE(2)
	CODE16
	LDR	R1, P_CallOutWindow_
	BLX	R1
	DATA
P_CallOutWindow_
	DCD	CallOutWindow_
	CODE16
	NOP
	
	RSEG	AddrBookWindow2:DATA(1)
	DATA
	DCB	0xFF
	
	RSEG	AddrBookWindow:CODE(2)
	CODE32
	BLX	AddrBookWindow_
	
	
	RSEG	PHONEBOOKHOOK:CODE(2)
	CODE32
	BLX	SIMBOOK
	
#ifndef WITHOUT_SMS_IN_WIN
	RSEG	SMS_IN_HOOK:CODE(2)
	CODE16
	LDR	R0, =SMS_IN
	BLX	R0
#endif
	
	RSEG	NUM_SELECT_MENU_HDR_ICON:DATA(2)
	DATA
	DCD	MENU_HDR_ICON
	
	RSEG	NUM_SELECT_MENU_LINES:DATA(2)
	DATA
	DCD	1
	
	RSEG	NUM_SELECT_MENU_ALITEM:CODE(2)
	CODE32
	BLX	AllocMLMenuItem_adr //void *AllocMLMenuItem(void *data)
	
	RSEG	NUM_SELECT_MENU_TEXT:CODE(2)
	CODE32
	BLX	NUM_SELECT_MENU_PSETTEXT

	RSEG	NUM_SELECT_MENU_GUI:CODE(2)
	CODE32
	BLX	GetMLMenuGUI_adr //ml menu gui
	
	END
