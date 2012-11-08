
#ifdef EL71sw45
#define RAM_BEGIN	0xA8D80250
#endif

#ifdef S7Cv47
#define RAM_BEGIN	0xA8A7F190
#endif

    RSEG DUMP
    CODE16
FUNC_
    PUSH    {LR}
    MOV    R0, R3
    BLX     main_
    POP     {PC}

    RSEG CODE
    CODE32
main_:
		B	loc_13042B8
sub_1304004:
		STMFD	SP!, {R4-R6,LR}
		LDR	R6, dword_1304308
		MOV	R4, R0
		MOV	R0, #1
		SWI	0x12E  //char *GetPaletteAdrByColorIndex(int ColorIndex)
		MOV	R5, R0
		MOV	R0, #0
		SWI	0x12E  //char *GetPaletteAdrByColorIndex(int ColorIndex)
		STMFD	SP!, {R5}
		STMFD	SP!, {R0}
		MOV	R3, #0xDC
		MOV	R2, #0xEB
		MOV	R1, #0x64
		MOV	R0, #0
		STMFD	SP!, {R0}
		STMFD	SP!, {R0}
		STMFD	SP!, {R0}
		MOV	R5, #0
		MOV	R0, #5
		SWI	0x150  //void DrawRoundedFrame(int x1,int y1,int x2,int y2,int x_round,int y_round,int flags,const char *pen,const char *brush)
		LDR	R0, [R4,#0x38]
		MOV	R1, #0
		SWI	0x126  //void CutWSTR(void *WSHDR,int len)
		ADD	SP, SP,	#0x14
		B	loc_1304078

loc_1304068:
		LDR	R0, [R4,#0x38]
		MOV	R1, #0x2A
		SWI	0x1C  //void wsAppendChar(WSHDR *ws,int wchar)
		ADD	R5, R5,	#1
		
loc_1304078:
		LDR	R0, [R6]
		CMP	R5, R0
		BLT	loc_1304068
		MOV	R0, #0x17
		SWI	0x12E
		MOV	R5, R0
		MOV	R0, #0
		SWI	0x12E
		STMFD	SP!, {R5}
		STMFD	SP!, {R0}
		MOV	R3, #0xE6
		MOV	R2, #0x96
		MOV	R1, #0xA
		MOV	R0, #0
		STMFD	SP!, {R0}
		MOV	R0, #0xB
		STMFD	SP!, {R0}
		MOV	R0, #0xAA
		STMFD	SP!, {R0}
		LDR	R0, [R4,#0x38]
		SWI	0x14C  //void DrawString(WSHDR *WSHDR, int x1, int y1, int x2, int y2, int font, int text_attribute, const char *Pen, const char *Brush)
		ADD	SP, SP,	#0x14
		LDMFD	SP!, {R4-R6,PC}
		
sub_13040D4:
		STMFD	SP!, {R4,LR}
		MOV	R4, R0
		MOV	R0, #0x100
		SWI	0x125  //WSHDR *AllocWS(int len)
		STR	R0, [R4,#0x34]
		MOV	R0, #0x100
		SWI	0x125
		STR	R0, [R4,#0x38]
		MOV	R0, #1
		STRB	R0, [R4,#0xC]
		LDMFD	SP!, {R4,PC}

sub_1304100:
		STMFD	SP!, {R4,LR}
		MOV	R4, R0
		LDR	R0, [R4,#0x34]
		SWI	0x129  //void FreeWS(WSHDR *wshdr)
		LDR	R0, [R4,#0x38]
		SWI	0x129
		MOV	R0, #0
		STRB	R0, [R4,#0xC]
		LDMFD	SP!, {R4,PC}
; ---------------------------------------------------------------------------
loc_1304124:
		MOV	R1, #2
		STRB	R1, [R0,#0xC]
		BX	LR
; ---------------------------------------------------------------------------
loc_1304130:
		LDRB	R1, [R0,#0xC]
		CMP	R1, #2
		MOVEQ	R1, #1
		STREQB	R1, [R0,#0xC]
		BX	LR

sub_1304144:
		STMFD	SP!, {R4,LR}
		LDR	R0, [R1,#4]
		MOV	R2, #0x93
		LDR	R1, [R0,#4]
		ORR	R2, R2,	#0x100
		CMP	R1, R2
		BNE	loc_13041EC
		LDR	R1, [R0,#8]
		LDR	R4, dword_1304308
		CMP	R1, #0x30
		BLT	loc_130419C
		CMP	R1, #0x3A
		BGE	loc_130419C
		LDR	R1, [R4]
		CMP	R1, #0xF
		BGE	loc_13041F0
		LDR	R0, [R0,#8]
		ADD	R2, R1,	R4
		STRB	R0, [R2,#8]
		ADD	R0, R1,	#1
		STR	R0, [R4]
		B	loc_13041EC
; ---------------------------------------------------------------------------

loc_130419C:	
		SUBS	R0, R1,	#1
		BEQ	loc_13041B4
		SUBS	R0, R0,	#0xB
		BEQ	loc_13041E4
		SUBS	R0, R0,	#0xE
		BNE	loc_13041EC

loc_13041B4:
		ADD	R0, R4,	#8
		BL	sub_1304388
		CMP	R0, #1
		BNE	loc_13041D4
		LDR	R0, [R4,#4]
		BLX	R0
		MOV	R0, #1
		LDMFD	SP!, {R4,PC}
; ---------------------------------------------------------------------------

loc_13041D4:
		//MOVL	R1, 0x239
    DCB    0x39
		DCB    0x10
		DCB    0xA0
		DCB    0xE3
		DCB    0x80
		DCB    0x1F
		DCB    0x81
		DCB    0xE3
		MOV	R0, #1
		SWI	0x148  //extern int ShowMSG(int flag, int lgp_id)

loc_13041E4:
		MOV	R0, #1
		LDMFD	SP!, {R4,PC}
; ---------------------------------------------------------------------------
loc_13041EC:
		SWI	0x13F  //void DirectRedrawGUI(void)

loc_13041F0:
		MOV	R0, #0
		LDMFD	SP!, {R4,PC}
; ---------------------------------------------------------------------------
locret_13041F8:
		BX	LR
; ---------------------------------------------------------------------------
loc_13041FC:
		MOV	R0, #0
		BX	LR
; ---------------------------------------------------------------------------
loc_1304204:
		MOV	R0, #0
		BX	LR
		
sub_130420C:
		STMFD	SP!, {R4,R5,LR}
		MOV	R4, R0
		MOV	R0, #0x40
		SWI	0x14  //void *malloc(unsigned int size)
		MOV	R5, R0
		MOV	R1, #0x40
		SWI	0x11D  //void zeromem(void *dest,int n)
		LDR	R0, dword_1304264
		ADD	R1, R0,	#0x2C
		STR	R1, [R5]
		MOV	R1, #2
		STR	R1, [R5,#0x30]
		STR	R0, [R5,#4]
		SWI	0x8015  //void *mfree_adr(void);
		STR	R0, [R5,#0x20]
		MOV	R0, #0
		STR	R0, [R4,#0x10]
		STR	R0, [R4,#0x14]
		MOV	R0, R5
		SWI	0x137  //int CreateGUI(void *gui)
		STR	R0, [R4,#0x28]
		LDMFD	SP!, {R4,R5,PC}

dword_1304264	DCD loc_1304448

locret_1304268:
		BX	LR
; ---------------------------------------------------------------------------

loc_130426C:
		LDR	R2, [R1,#4]
		//MOVL	R3, 0x640E
                DCB    0x0E
                DCB    0x30 
                DCB    0xA0 
                DCB    0xE3
                DCB    0x64
                DCB    0x3C
                DCB    0x83
                DCB    0xE3
		CMP	R2, R3
		BNE	loc_1304294
		LDR	R1, [R1,#0xC]
		LDR	R2, [R0,#0x28]
		CMP	R1, R2
		//MOVLEQ	R1, 0xFFFFFFFD
                DCB    0x02 
                DCB    0x10 
                DCB    0xE0 
                DCB    0x03
		STREQ	R1, [R0,#0x10]

loc_1304294:
		MOV	R0, #1
		BX	LR

sub_130429C:
		LDR	R0, dword_13042B4
		STMFD	SP!, {LR}
		MOV	R1, R0
		ADD	R0, R0,	#0x38
		SWI	0x124  //int wsprintf(WSHDR *,const char *format,...)
		LDMFD	SP!, {PC}
dword_13042B4	DCD aEnterPassword
; ---------------------------------------------------------------------------
loc_13042B8:
		LDR	R2, dword_1304308
		STMFD	SP!, {LR}
		SUB	SP, SP,	#0x2C
		STR	R0, [R2,#4]
		MOV	R0, #0
		STR	R0, [R2]
		MOV	R1, #0x10
		ADD	R0, R2,	#8
		SWI	0x11D  //void zeromem(void *dest,int n)
		BL	sub_130429C
		SWI	0x146  //void LockSched(void)
		LDR	R0, dword_1304304
		MOV	R2, #0
		MOV	R1, SP
		SWI	0x107  //int CreateCSM(const CSM_DESC *,void *,int)
		SWI	0x147  //void UnlockSched(void)
		MOV	R0, #0
		ADD	SP, SP,	#0x2C
		LDMFD	SP!, {PC}

dword_1304304	DCD loc_1304408
dword_1304308	DCD RAM_BEGIN

sub_130430C:
		STMFD	SP!, {R4,R5,LR}
		MOV	R4, R0
		MOV	R5, #0
		SWI	0x1B  //unsigned int strlen(const char *)
		CMP	R0, #1
		BLT	loc_130437C
		MOV	R1, #0

loc_1304328:
		LDRB	R2, [R4]
		ADD	R4, R4,	#1
		ADD	R2, R2,	#0xD0
		AND	R2, R2,	#0xFF
		ADD	R3, R2,	R5
		ADD	R5, R1,	R1,LSR#31
		MOV	R5, R5,ASR#1
		SUBS	R5, R1,	R5,LSL#1
		MULEQ	R5, R2,	R3
		ADDNE	R5, R3,	#1
		LDR	R3, dword_1304384
		SMULL	R12, LR, R1, R3
		MOV	R12, #3
		ADD	LR, LR,	R1,LSR#31
		MUL	LR, R12, LR
		SUBS	R3, R1,	LR
		ADDEQ	R2, R2,	R2,LSL#1
		ADDEQ	R5, R2,	R5
		ADD	R1, R1,	#1
		CMP	R1, R0
		BLT	loc_1304328

loc_130437C:
		MOV	R0, R5
		LDMFD	SP!, {R4,R5,PC}
dword_1304384	DCD 0x55555556

sub_1304388:
var_10		= -0x10
		STMFD	SP!, {R4,R5,LR}
		SUB	SP, SP,	#8
		MOV	R4, R0
		LDR	R0, dword_13043F4
		MOV	R3, SP
		MOV	R2, #0
		MOV	R1, #0x80
		SWI	0xA
		MOVS	R5, R0
		BMI	loc_13043EC
		MOV	R3, SP
		MOV	R2, #4
		ADD	R1, SP,	#0x14+var_10
		SWI	0xB
		CMP	R0, #4
		BNE	loc_13043EC
		MOV	R1, SP
		MOV	R0, R5
		SWI	0xD
		MOV	R0, R4
		BL	sub_130430C
		LDR	R1, [SP,#0x14+var_10]
		CMP	R1, R0
		MOVEQ	R0, #1
		LDMEQFD	SP!, {R1,R2,R4,R5,PC}

loc_13043EC:
		MOV	R0, #0
		LDMFD	SP!, {R1,R2,R4,R5,PC}
; ---------------------------------------------------------------------------
dword_13043F4	DCD a2Ccq_wtf_dat
aEnterPassword	DCB "Enter Password",0
loc_1304408:
		DCD loc_130426C
		DCD sub_130420C
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCD locret_1304268
		DCD 0x2C
		DCD 1
		DCD loc_1304444
		DCD RAM_BEGIN+0x18
		DCB 0xCC
		DCB 0xCC
		DCB 0xAA
		DCB 0x55
		DCB 0x55
		DCB 0xAA
		DCB 0x33
		DCB 0x33
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCD 0x8B
loc_1304444:
		DCD 0xFFFFFFF5
loc_1304448:
		DCD sub_1304004
		DCD sub_13040D4
		DCD sub_1304100
		DCD loc_1304124
		DCD loc_1304130
		DCD sub_1304144
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCD locret_13041F8
		DCD loc_13041FC
		DCD loc_1304204
		DCB    0
		DCB    0
		DCB    0
		DCB    0
		DCB    5
		DCB    0
		DCB 0x64 ; d
		DCB    0
		DCB 0xEA ; ?
		DCB    0
		DCB 0xDB ; ?
		DCB    0
a2Ccq_wtf_dat£º
		DCB 0x32
		DCB 0x3A
		DCB 0x5C
		DCB 0x63
		DCB 0x63
		DCB 0x71
		DCB 0x5F
		DCB 0x77
		DCB 0x74
		DCB 0x66
		DCB 0x2E
		DCB 0x64
		DCB 0x61
		DCB 0x74
		DCB    0
		DCD 0x130
		DCD RAM_BEGIN
		DCD RAM_BEGIN
    
    END
