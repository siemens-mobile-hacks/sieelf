	CODE16
	RSEG	HOOK
	LDR	R2, =CODE_
	BLX	R2


	EXTERN	AddTheName
	CODE16
	RSEG	CODE
#ifdef NEWSGOLD
CODE_
	STR	R0, [SP,#4] //LGP
	LDR	R1, [SP,#8] //WS
	PUSH	{R0-R7, LR}
	MOV	R6, R0
	MOV	R7, R1
	SWI	0x89
	LDR	R5, =0xAC5
	CMP	R6, R5
	BNE	exit
	MOV	R0, R7
	BLX	AddTheName
#else //SGOLD by DaiKangaroo
CODE_
	//ԭ��Hookλ�ô���
	//MOV R0, R4
        //BLX Sub ��������:ADD R0, #0x80  STR R1, [R0, #4]
        //MOV R1, R6
        //����Ϊ
	MOV	R0, R4
	ADD 	R0, #0x80
	STR 	R1, [R0, #4]
        MOV     R1, R6	

	PUSH	{R0-R7, LR}
	LDR	R2, =0x272 //�յ��µ���ϢLGP
	CMP	R7, R2
	BNE	exit
	MOV	R0, R5 //WS
	BLX	AddTheName
#endif
exit
	POP	{R0-R7}
	POP	{R0}
	ADD	R0, R0, #4
	BX	R0
	
	END