//S7Cv47
        RSEG	SWILIB_FUNC2EE_2F5:CODE
	EXTERN	sub_elfclose
	EXTERN	dlopen
	EXTERN	dlsym
        EXTERN	dlclose
        EXTERN	setenv
        EXTERN	unsetenv
        EXTERN	getenv
        EXTERN	clearenv
        EXTERN  environ
	EXTERN  dlerror
        EXTERN  dlclean_cache
        EXTERN  SHARED_TOP
        
	DCD	sub_elfclose
	DCD	dlopen
	DCD	dlsym
        DCD     dlclose
        DCD	setenv
	DCD	unsetenv
        DCD     getenv
        DCD     clearenv
        DCD	environ
        DCD	dlerror
        DCD	dlclean_cache
	DCD	SHARED_TOP


	RSEG	DATA_N
	RSEG	SWILIB_FUNC1B8_1BB:CODE
	EXTERN	EXT2_AREA
	EXTERN	pngtop
	EXTERN	pLIB_TOP
	DCD	EXT2_AREA
	DCD	pngtop
	DCD	pLIB_TOP
	DCD	SFE(DATA_N)
        


defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM

        RSEG	CODE:CODE
        

	PUBLIC	OldOnClose
OldOnClose:
	DCD	0xA0303C6A+1  //B0 B5 04 1C???????? ???? 20 1Cff303530
	
	PUBLIC	OldOnCreate
OldOnCreate:
	DCD	0xA0303A54+1 // F0 B5 ???? ?????? ???? 1C FF 30 29 30
	
	PUBLIC	OldShowMsg
OldShowMsg:
	DCD	0xA09A566E+1 //A3 4A C3 07 00 D4 38 32 0B 1C 00 21 30 E7 A0 4A
	
	PUBLIC	PITgetN
PITgetN:
	DCD	0xA0A44234 //54 00 9F E5 1E FF 2F E1 10 40 2D E9 40 CE 50 E2
	
	PUBLIC	PITret
PITret:
	DCD	0xA09A3F2A+1 //01 D9 20 1C 12 E0 D9 49 4A 1C 8B 1C 8C 42 03 D0


	defadr	StoreErrInfoAndAbort,0xA01CF2E8 //10 40 2D E9 A8 44 9F E5 00 C0 94 E5 00 00 5C E3
	defadr	StoreErrString,0xA01CF1B4 //0A 10 A0 E3 E9 FF FF EA 08 40 2D E9 D4 10 A0 E3

	END