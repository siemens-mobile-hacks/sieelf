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
	DCD	0xA02EFCA6+1 //?? B5 04 1C???????? ???? 20 1C FF 30 15 30
	
	PUBLIC	OldOnCreate
OldOnCreate:
	DCD	0xA02EFA8C+1 //??B5 ???????????? 04 1C FF 30
	
	PUBLIC	OldShowMsg
OldShowMsg:
	DCD	0xA08556AE+1 // A3 4A C3 07 00 D4 38 32 0B 1C 00 21 30 E7 A0 4A

	PUBLIC	PITgetN
PITgetN:
	DCD	0xA0C3C04C //54 00 9F E5 1E FF 2F E1 10 40 2D E9 60 CE 50 E2
	
	PUBLIC	PITret
PITret:
	DCD	0xA0853F6A+1 //01 D9 20 1C 12 E0 D9 49 4A 1C 8B 1C 8C 42 03 D0


	defadr	StoreErrInfoAndAbort,0xA018DA00  //01 00 00 0A 00009DE5???????? 08 80 BD E838402DE9
	defadr	StoreErrString,0xA018D8CC //01 70 87 E2 28 30 9D E5 00 00 53 E3 C3 FF FF 1A


	END