
#include "addr.h"

	EXTERN	AppendInfoW
	EXTERN	UpdateLocaleToItem
	EXTERN	do_phonebook_work 

#ifdef NEWSGOLD
	RSEG	CODE
#else
	RSEG	CODE_2
#endif
	
	CODE16
	PUBLIC	strlen
strlen:
	PUSH		{R4, LR} 
	LDR		R4, =ADDR_strlen
	BLX		R4
	POP		{R4, PC}
	
	PUBLIC	memcmp
memcmp:
	PUSH		{R4, LR} 
	LDR		R4, =ADDR_memcmp
	BLX		R4
	POP		{R4, PC}
	
	PUBLIC	atou
atou:
	PUSH		{R4, LR} 
	LDR		R4, =ADDR_atou
	BLX		R4
	POP		{R4, PC}
	
	PUBLIC	WS_InitByZero
WS_InitByZero:
	PUSH		{R4, LR} 
	LDR		R4, =ADDR_WS_InitByZero
	BLX		R4
	POP		{R4, PC}
	
	PUBLIC	GetCalleeNumber
GetCalleeNumber:
	PUSH		{R4, LR} 
	LDR		R4, =ADDR_GetCalleeNumber
	BLX		R4
	POP		{R4, PC}
	
	PUBLIC	UpdateWndItem
UpdateWndItem:
	PUSH		{R4, LR} 
	LDR		R4, =ADDR_UpdateWndItem
	BLX		R4
	POP		{R4, PC}
//#ifndef NEWSGOLD
	//CODE32
	public	AllocWS
AllocWS:
	LDR		R3, =ADDR_AllocWS
	BX		R3
	
	public	FreeWS
FreeWS:
	LDR		R3, =ADDR_FreeWS
	BX		R3
	
	public	DrawString
DrawString:
	PUSH		{R3}
	LDR		R3, =ADDR_DrawString
	MOV		R12, R3
	POP		{R3}
	BX		R12
	
	public		GetCurMenuItem
GetCurMenuItem:
	LDR		R3, =ADDR_GetCurMenuItem
	BX		R3
//#endif	
	CODE16
AddNewLine:
	PUSH		{R0-R7, LR}
	MOV		R1, #0xD
	LDR		R2, =ADDR_wsAppendChar
	BLX		R2
	POP		{R0-R7, PC}

Hook1:
	PUSH		{R0-R1,R4,LR}
	MOV		R4, R0
	LDR		R2, =ADDR_wstrcat
	BLX		R2
	MOV		R0, R4
	BL		AddNewLine
	POP		{R0-R1,R4}
	BL		AppendInfoW	
	POP		{PC}

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



/*	extern	GetProvAndCity
AddrBookMenu:
	LDR		R0, [SP, #0x224]
	LDR		R1, [SP, #0x24C]
	ADD		R2, SP, #0x1C
	PUSH		{R0-R7,LR}
	MOV		R6, R2
	MOV		R7, R0
	MOV		R1, #0x20
	LDR		R2, =ADDR_wsAppendChar
	BLX		R2
	LDR		R0, [R7, #0]
	MOV		R1, R6
	BL		GetProvAndCity
	POP		{R0-R7}
	POP		{R2}
	STR		R0, [R1, #0]
	LDR		R0, [R4, #0x38]
	ADD		R2, R2, #4
	BX		R2*/
	//void store_the_num_2_ram(int pos, char *num)
	
//用于将列表中的号码存到RAM中,by BingK(binghelingxi)
	extern	store_the_num_2_ram
	extern	new_redraw_
	extern	memcpy_n
NUM_SELECT_MENU:
	LSR		R0, R0, #0x10
	ADD		R0, #1
	ADD		R6, SP, #4
	PUSH		{R0-R7, LR}
	MOV		R0, R7
	MOV		R1, R6
	BL		store_the_num_2_ram
	POP		{R0-R7}
	POP		{R6}
	LDR		R1, =ADDR_AllocWS
	BLX		R1
	ADD		R6, R6, #4
	BX		R6
	
//NUM_SELECT_MENU1:
//重建redraw,by BingK(binghelingxi)
	CODE16
new_redraw:
	PUSH		{R4-R7,LR}
	MOV		R7, R0
	LDR		R4, =UNUSERAM_OLD_REDRAW
	LDR		R4, [R4, #0]		//RUN OLD REDRAW
	BLX		R4
	MOV		R0, R7
	BL		new_redraw_
	POP		{R4-R7,PC}
	
//替换原来列表GUI的methods,by BingK(binghelingxi)
	CODE16
NUM_SELECT_MENU1:
	PUSH		{R0-R7, LR}
	MOV		R7, R0			//R0=OLD_GUI
	LDR		R6, =UNUSERAM_METHOD 	//METHODS
	LDR		R1, [R7, #4]		//OLD METHODS
	MOV		R2, #0x60
	MOV		R0, R6
	BL		memcpy_n
	LDR		R5, =UNUSERAM_OLD_REDRAW//FOR OLD METHODS
	LDR		R0, [R7, #4]
	LDR		R0, [R0, #0]		//OLD REDRAW
	STR		R0, [R5, #0]		//STORE OLD REDRAW HERE
	LDR		R0, =new_redraw
	STR		R0, [R6, #0]		//STORE NEW REDRAW
	STR		R6, [R7, #4]		//STORE NEW METHODS
	POP		{R0-R7}
	ADD		R4, R0, #0
	LDR		R1, =ADDR_MENU_DESC
	LDR		R2, =ADDR_CREATE_SELECT_MENU
	BLX		R2
	POP		{R2}
	ADD		R2, R2, #4
	BX		R2

	RSEG	CODE_X
	EXTERN	GetProvAndCity
	EXTERN	GetNumFromIncomingPDU
	CODE16
SMS_IN
	LDR		R0, [SP, #8]
	LDR		R2, [SP, #4]
	PUSH		{R0-R7, LR}
	MOV		R7, R0
	SUB		SP, #0x20
	LDR		R6, =0xAC5 //LGP 新信息
	CMP		R6, R2
	BNE		GoBack
	ADD		R0, SP, #0
	BL		GetNumFromIncomingPDU
	CMP		R0, #0
	BEQ		GoBack
	MOV		R0, R7
	BL		AddNewLine
	LDR		R0, [R7, #0]
	ADD		R1, SP, #0
	BL		GetProvAndCity
GoBack
	ADD		SP, #0x20
	POP		{R0-R7}
	POP		{R2}
	LDR		R0, [R0, #0] //WSTRLEN
	LDRH		R0, [R0, #0]
	STR		R0, [SP,#0xD8]
	ADD		R2, R2, #4
	BX		R2

	
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
	RSEG	AddrBookWindow2:DATA(1)
	DCB		0xFF
#endif

/*
	CODE16
	RSEG	AddrBookMenu_HOOK1:CODE(1)
	MOV		R0, #0x18

	CODE16
	RSEG	AddrBookMenu_HOOK:CODE(2)
	LDR		R0, =AddrBookMenu
	BLX		R0*/
	CODE16
	RSEG	NUM_SELECT_MENU_HOOK
	LDR		R6, =NUM_SELECT_MENU
	BLX		R6
	
	CODE16
	RSEG	NUM_SELECT_MENU_HOOK1
	LDR		R4, =NUM_SELECT_MENU1
	BLX		R4
	
	CODE16
	RSEG	SMS_IN_HOOK
	LDR		R0, =SMS_IN
	BLX		R0
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
	LDR		R0, =ADDR_IsCalling
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

//短信发送动画窗口,by BingK(binghelingxi)
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
	
	extern	store_the_num_2_ram
	extern	new_redraw_
	extern	memcpy_n
	
//用于将列表中的号码存到RAM中,by BingK(binghelingxi)
	CODE16
NUM_SELECT_MENU:
	PUSH		{R3, LR}
	LDR		R3, =ADDR_SELECT_MENU
	BLX		R3
	ADD		R1, SP, #0x0C
	MOV		R0, R7
	BL		store_the_num_2_ram
	POP		{R3, PC}

//重建redraw,by BingK(binghelingxi)
	CODE16
new_redraw:
	PUSH		{R4-R7,LR}
	MOV		R7, R0
	LDR		R4, =UNUSERAM_OLD_REDRAW
	LDR		R4, [R4, #0]		//RUN OLD REDRAW
	BLX		R4
	MOV		R0, R7
	BL		new_redraw_
	POP		{R4-R7,PC}
	
//替换原来列表GUI的methods,by BingK(binghelingxi)
	CODE16
NUM_SELECT_MENU1:
	PUSH		{R0-R7, LR}
	MOV		R7, R0			//R0=OLD_GUI
	LDR		R6, =UNUSERAM_METHOD 	//METHODS
	LDR		R1, [R7, #4]		//OLD METHODS
	MOV		R2, #0x60
	MOV		R0, R6
	BL		memcpy_n
	LDR		R5, =UNUSERAM_OLD_REDRAW//FOR OLD METHODS
	LDR		R0, [R7, #4]
	LDR		R0, [R0, #0]		//OLD REDRAW
	STR		R0, [R5, #0]		//STORE OLD REDRAW HERE
	LDR		R0, =new_redraw
	STR		R0, [R6, #0]		//STORE NEW REDRAW
	STR		R6, [R7, #4]		//STORE NEW METHODS
	POP		{R0-R7}
	ADD		R4, R0, #0
	LDR		R1, =ADDR_MENU_DESC
	POP		{PC}
//Hook
// 通话记录修改
	RSEG	RecordWindow:CODE(1)
	CODE16
	BL		Hook1

// 拨入窗口修改，覆盖了group xx的显示位置
	RSEG	Callinwindow:CODE(1)
	CODE16
	BL		Hook2

// 拨出窗口修改，覆盖了group xx的显示位置
	RSEG	CallOutWindow:CODE(1)
	CODE16
	BL		Hook3

// 通讯录窗口修改
	RSEG 	AddrBookWindow:CODE(1)
	CODE16
	BL		Hook4

	RSEG	AddrBookWindow2:DATA(1)
	DCB		0x21

// 电话本窗口修改
	RSEG	PhonebookWindow:CODE(1)
	CODE16
	BL		Hook5

//短信发送动画窗口,by BingK(binghelingxi)	
	CODE16
	RSEG	SMS_SEND_HOOK:CODE(2)
	LDR		R2, pSMS_SEND
	BLX		R2
	
	DATA
pSMS_SEND
	DCD		SMS_SEND_WINDOW
	
	CODE16
	NOP

//用于将列表中的号码存到RAM中,by BingK(binghelingxi)
	CODE16
	RSEG	NUM_SELECT_MENU_HOOK:CODE(1)
	BL		NUM_SELECT_MENU

//替换原来列表的methods,重建redraw,by BingK(binghelingxi)
	CODE16
	RSEG	NUM_SELECT_MENU_HOOK1:CODE(1)
	BL		NUM_SELECT_MENU1
#endif
	END