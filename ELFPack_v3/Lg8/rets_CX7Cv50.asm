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
	DCD	0xA0923F8C+1  //10B5041C0320????????201C7030
	
	PUBLIC	OldOnCreate
OldOnCreate:
	DCD	0xA0923DC6+1  //FEB5041C0020????????????00270460
        
	PUBLIC	ESIOld
ESIOld:
	DCD	0xA11BFC8A+1  //07DB????904204D00A1C211C00F0
        
        PUBLIC	PITgetN
PITgetN:
	DCD	0xA00DDFCE+1  //DA48192189014018C068808A704710B5
	
	PUBLIC	PITret
PITret:
	DCD	0xA00DDFE4+1  //A04205D9????????0069E100401810BD
        
        PUBLIC	KEYBret
KEYBret:
	DCD	0xA00F261E+1  //381CFF38C8382FD1301C????????0028 
        
        PUBLIC	KEYBfunc
KEYBfunc:
	DCD	0xA00E32B8+1  //FEB5041C00680D1CC668206D02AA311C          
        
	PUBLIC	FReadOld
FReadOld:
	DCD	0xA137D924  //FE402DE90270A0E10160A0E10350A0E10040A0E1????????0030E0E304308DE500508DE530C090E50000A0E3
        
        PUBLIC	FWriteOld
FWriteOld:
	DCD	0xA137DA0C  //FE402DE90270A0E10160A0E10350A0E10040A0E1????????0030E0E304308DE500508DE55CC090E50000A0E3       
        
        defadr	StoreErrInfoAndAbort,0xA137E458  //F04D2DE90040A0E190029FE50080A0E30260A0E10150A0E1
	defadr	StoreErrString,0xA137E27C  //0A10A0E3E9FFFFEA10402DE9F410A0E33C049FE5

	END