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
	DCD	0xA0689F4E+1  //B0B5041CFF300130????????201CFF30
	
	PUBLIC	OldOnCreate
OldOnCreate:
	DCD	0xA0689CEC+1  //F0B5F54D85B0A861041CFF302D30
	
	PUBLIC	OldShowMsg
OldShowMsg:
	DCD	0xA097B77A+1  //8E4AC30700D438320B1C00212BE78A4A

	PUBLIC	PITgetN
PITgetN:
	DCD	0xA0A63C3C  //54009FE51EFF2FE110402DE960CE50E2
	
	PUBLIC	PITret
PITret:
	DCD	0xA0979FE4+1  //01D9201C11E0D9494A1C8B1C8C4203D0

	defadr	StoreErrInfoAndAbort,0xA04E8A64 //38402DE9D0449FE500C094E500005CE3
	defadr	StoreErrString,0xA04E8930 //0A10A0E3E9FFFFEA08402DE9D410A0E3


	END
