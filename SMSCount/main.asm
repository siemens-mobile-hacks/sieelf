#include "addr.h"

#ifdef ELKA
#define	RamUnuse  	0xA8D88E00
#endif
#ifdef NEWSGOLD
#ifdef S68Cv51
#define	RamUnuse  	0xA8D7B800
#else
#define	RamUnuse  	0xA8A7F020
#endif
#endif
  

    RSEG	CODE   
    PUBLIC
InitDay:
    DCB 0x01
TypeALL:
    DCB	0x01 	 
TypeCHM:
    DCB	0x02 
TypeCHU:
    DCB	0x03 
TypeOTH:
    DCB	0x04 

NewLine:
    DCB	0xA,00
InitDay2:
    DCB "InitDay: ",00
FilePath:
    DCB	 "2:\\SMSCount.Dat",00
All:
    DCB   "ALL: ",00
ChinaMobile:
    DCB   "CHMB: ",00
ChinaUnicom:
    DCB   "CHUN: ",00
Others:
    DCB   "OTH: ",00
    

    CODE16
    RSEG	CODE
Ui2Str:
    PUSH  {R4, R6, LR}
    SUB	  SP, #0x10
    ADD	  R1, SP, #0
    LDR   R4, =uitostr
    BLX   R4
    ADD	  R1, SP, #0
    ADD	  SP, #0x10
    POP   {R4, R6, PC} 
tostrcat:
    PUSH    {R6, LR}
    MOV     R0, R5
    SWI     0x17
    POP     {R6, PC}
getthedatetime:
    PUSH   {R6, LR}
    SUB    SP, #16
    ADD	   R0, SP, #0
    ADD	   R1, SP, #8
    SWI	   0xB4
    ADD	   R0, SP, #4
    ADD    SP, #16
    POP    {R6, PC}

//open file and write in it
main:
	PUSH	{R0-R6, LR}
	SUB	SP, #8
	LDR	R0, =FilePath
        LDR     R1, =0x301
	MOV	R2, #1
	LSL	R2, R2, #0x8
	MOV	R3, SP
  SWI     0x0A
	ADD	R5, R0, #0
	ADD     R3, R0, #1
	CMP	R3, #0
	BEQ	exit
	LDR	R6, =RamSMSNum
	MOV	R0, #2
	LDRB	R2, [R6, #0]
	LDRB	R1, [R6, #2]
	CMP	R1, #0x68
	BNE	CheckNumber
	ADD	R0, #1		//定位第一个数字的位置
	SUB	R2, #2
CheckNumber:
	CMP	R2, #0x0B
	BEQ	CheckChinaMblAndUniCom
	B	CheckOthers
CheckChinaMblAndUniCom:
	LDRB	R1, [R6, R0]	//获得前两个数字
	CMP     R1, #0x51
	BEQ     CheckNewMb
	CMP	R1, #0x31
	BNE	CheckOthers
	ADD	R0, #1
	LDRB	R1, [R6, R0]
	MOV	R3,	#0x0F
	AND	R1, R3
	CMP	R1, #4
	BLT	UniCom
Mb:
	MOV	R3, #8
	B	ModfiyCountAndFile
UniCom:
	MOV	R3, #12
	B	ModfiyCountAndFile
CheckNewMb:
	ADD	R0, #1
	LDRB	R1, [R6, R0]
	MOV	R3,	#0x0F
	AND	R1, R3
	CMP     R1, #3
	BEQ     UniCom
	CMP     R1, #6
	BEQ     UniCom
	CMP     R1, #7
	BEQ     Mb
	CMP     R1, #8
	BEQ     Mb
	CMP	R1, #9
	BEQ	Mb
CheckOthers:
	MOV	R3, #16
ModfiyCountAndFile:			
	LDR	R1, =RamUnuse
	LDR     R2, [R1, #4]
	ADD	R2, #1
	STR 	R2, [R1, #4]
	LDR     R2, [R1, R3]
	ADD	R2, #1
	STR 	R2, [R1, R3]
	MOV	R0, R5
	MOV	R2, #20
	MOV	R3, SP
        SWI     0x0C     
	MOV	R0, R5
	MOV	R1,	SP
        SWI     0x0D
exit:
	ADD	SP, #8
	POP	{R0-R6, R7}
	LDR     R0, [R6,#4]
        LDR     R1, [R0,#0x18]
        LDR     R2, [R0,#0x14]
        ADD     R0, R4, #0
	ADD     R7, #4
	BX      R7

/*************
CheckIfinitRam
*************/
initRam:
	PUSH	{R0-R6,LR}
	SUB	SP, #16
	LDR	R1, =RamUnuse
	LDR	R2, [R1, #0]
	CMP	R2, #0x0
	BEQ	needToInit
	B	CheckIfClean
needToInit:
	LDR	R0, =FilePath
	MOV	R1, #0
	MOV	R2, #0x80
	MOV	R3, SP
        SWI     0x0A
	ADD	R5, R0, #0
	ADD     R3, R0, #1
	CMP	R3, #0
	BEQ	exitinit
	MOV	R0, R5
	LDR	R1, =RamUnuse
	MOV	R2, #20
	MOV	R3, SP
        SWI     0x0B
	MOV	R0, R5
	MOV	R1,	SP
        SWI     0x0D

CheckIfClean:
	BL      getthedatetime
        LDRB	R2, [R0, #1]
        LDR     R1, =InitDay
        LDRB	R1, [R1, #0]
	CMP     R1,  #0
	BEQ     exitinit

        CMP	R2, R1
        BNE	exitinit

        LDRB	R2, [R0, #0]
        LDR	R1, =RamUnuse
        LDR 	R0, [R1, #0]
        CMP 	R2, R0
        BEQ 	exitinit

        STRB	R2, [R1, #0]
	MOV	R2, #0
	STR 	R2, [R1, #4]
	STR	R2, [R1, #8]
	STR	R2, [R1, #12]
	STR	R2, [R1, #16]
SaveInit:
	LDR     R0, =FilePath
        MOV     R1, #1
	MOV	R2, #1
	LSL	R2, R2, #8
	MOV	R3, SP
        SWI     0x0A
	ADD	R5, R0, #0
	ADD     R3, R0, #1
	CMP	R3, #0
	BEQ	exitinit
	LDR	R1, =RamUnuse
	MOV	R0, R5
	MOV	R2, #20
	MOV	R3, SP
        SWI     0x0C
	MOV	R0, R5
	MOV	R1,	SP
        SWI     0x0D
exitinit:
#ifdef SHOW_AFTER_NEW
	LDR	R1, =RamUnuse
	LDR     R2, [R1, #0x4]
	LDR     R3, [R1, #0x14]
	CMP     R2, R3
	BNE     ShowMes
Finish:
#endif
	ADD	SP, #16
	POP	{R0-R6, R7}
#ifdef ELKA
	ADD     R3, SP
#endif
        STR     R0, [R3,#0x54]
        LDR     R0, =0xA3C
        LDR     R1, =0xA3C
        ADD     R7, #4
#ifdef NEWSGOLD
        SUB     R0, #0x14
#endif
	BX      R7
#ifdef SHOW_AFTER_NEW
ShowMes:
	BL 	ShowMesMain
        STR     R2, [R1, #0x14]
	B       Finish
#endif
		

/*************
ShowMes
*************/
ShowMesMain:
        PUSH    {R0-R7, LR}
        LDR     R0, =RamUnuse
        MOV     R5, #0x20
        ADD     R5, R0, R5
ShowSMSCount:
        MOV     R0, R5
        LDR     R1, =All
        SWI     0x1A
        LDR	R2, =TypeALL
	LDRB	R0, [R2, #0]
	LSL	R0, R0, #2	 	//get the pos
	LDR	R2, =RamUnuse
	LDR 	R0, [R2, R0]
	BL      Ui2Str
	BL      tostrcat
	LDR     R1, =NewLine
	BL      tostrcat
	//CHM:
        LDR     R1, =ChinaMobile
        BL      tostrcat
        LDR	R2, =TypeCHM
	LDRB	R0, [R2, #0]
	LSL	R0, R0, #2	 	//get the pos
	LDR	R2, =RamUnuse
	LDR 	R0, [R2, R0]
	BL      Ui2Str
	BL      tostrcat
	LDR     R1, =NewLine
	BL      tostrcat
	//CHU	
        LDR     R1, =ChinaUnicom
        BL      tostrcat
        LDR	R2, =TypeCHU
	LDRB	R0, [R2, #0]
	LSL     R0, R0, #2	 	//get the pos
	LDR     R2, =RamUnuse
	LDR 	R0, [R2, R0]
	BL      Ui2Str
	BL      tostrcat
	LDR     R1, =NewLine
	BL      tostrcat
	//OTH
        LDR     R1, =Others
        BL      tostrcat
        LDR	R2, =TypeOTH
        LDRB    R0, [R2, #0]
	LSL     R0, R0, #2	 	//get the pos
	LDR     R2, =RamUnuse
	LDR     R0, [R2, R0]
	BL      Ui2Str
	BL      tostrcat
	LDR     R1, =NewLine
	BL      tostrcat
ShowInitDay:
        LDR     R1, =InitDay2
	BL      tostrcat
	LDR     R1, =InitDay
	LDRB  	R0, [R1, #0]
        BL      Ui2Str
	BL      tostrcat
MesBox:
	MOV     R1, R5
        MOV     R0, #1
	MOV     R2, #0
        SWI	0x4E
Exit:
    POP     {R0-R7, PC}
		
    RSEG SMSHook
    CODE16
    LDR  R2,  =main
    BLX	 R2
		
    RSEG hookwindow
    CODE16
    LDR     R1, =initRam
    BLX     R1
	  
    RSEG HookShow:DATA(2)
    PUBLIC
    DCD	   ShowMesMain
    
    END
    
    