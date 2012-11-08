
                    RSEG     CODE:CODE

                
                    PUBLIC   UnLockAccess
                  
      UnLockAccess:
     
 	            STR	     LR, [SP, #-0x04]!
	            MRS	     R2,  CPSR
            
                    SWI      0x81B5
                    CMP      R0, #0x00
	            SWIEQ    0x00
                    SWINE    0x04

	            MRS      R1, CPSR
	            ORR      R1, R1,#0xC0
	            MSR      CPSR_c, R1
           
                    MOV      R0, #0xFFFFFFFF
                    MCR      p15, 0, R0, c3, c0 
                  
                    NOP
	            NOP
	            NOP
	            NOP
                    NOP
	            NOP
	            NOP
	            NOP
                    NOP
	            NOP
	            NOP
	            NOP
                    NOP
	            NOP
	            NOP
	            NOP
                   
	            MSR	     CPSR_c,R2
	            LDR	     PC,[SP], #+0x04
                    
                    PUBLIC   UnLockSYSAccess
                  
   UnLockSYSAccess:
     
                    MOV      R0, #0xFFFFFFFF
                    MCR      p15, 0, R0, c3, c0 
                    
	            NOP
	            NOP
                    NOP
	            NOP
	            NOP
	            NOP
                    NOP
	            NOP
	            NOP
                  
	            BX       LR
                    

        
                    PUBLIC  UnlockCFI
           
         UnlockCFI:
         

                    MRS     R1, CPSR
                   
                    SWI     0x81B5
                    CMP     R0, #0x00
	            SWIEQ   0x00
                    SWINE   0x04
                   
                    ORR     R1, R1, #0x1F
                    MSR     CPSR_c, R1
                   
                    MOV     R0, #0xF0000000
                   
                    LDR     R1, [R0, #0xE0]
                    BIC     R1, R1, #0xFF000000
                    STR     R1, [R0, #0xE0]
                   
                    BX      LR
                   
                   PUBLIC   GetTBaseAddr
            
     GetTBaseAddr:
            
 	            STR	   LR, [SP, #-0x04]!
	            MRS	   R2,  CPSR
             
                    SWI     0x81B5
                    CMP     R0, #0x00
	            SWIEQ   0x00
                    SWINE   0x04

	            MRS     R1, CPSR
	            ORR     R1, R1,#0xC0
	            MSR     CPSR_c, R1
           
                    MOV     R0, #0
                    MRC     p15, 0, R0, c2, c0 //R0 = 0x90000 (SGold, NewSGold), R0 = 0x8C000 (ELKA) 
                  
	            MSR	    CPSR_c,R2
	            LDR	    PC,[SP], #+0x04
                    
                   PUBLIC   GetTBaseSYSAddr
            
   GetTBaseSYSAddr:
            
                    MOV     R0, #0
                    MRC     p15, 0, R0, c2, c0 //R0 = 0x90000 (SGold, NewSGold), R0 = 0x8C000 (ELKA) 
                  
	            BX      LR
                    

                   PUBLIC ExecuteIMB

       ExecuteIMB:
                    STR	  LR, [SP, #-0x04]!
                    MRS	  R2,  CPSR
             
                    SWI     0x81B5
                    CMP     R0, #0x00
	            SWIEQ   0x00
                    SWINE   0x04
           
                    MRS	  R1, CPSR
                    ORR   R1, R1,#0xC0
                    MSR   CPSR_c, R1
             
                    NOP
                    NOP
                    NOP
            
        clean_loop:
 
                    // clean entire dcache using test and clean
                    MRC   p15, 0, r15, c7, c10, 3
            
                    NOP
                    NOP
                    NOP
            
                    BNE   clean_loop
                    MOV   R0, #0x00
             
                    // drain write buffer
                    MCR   p15, 0, r0, c7, c10, 4
            
                    NOP
                    NOP
                    NOP
                    NOP
            
                    // invalidate icache
                    MCR	  p15, 0, r0, c7, c5, 0
            
                    NOP
                    NOP
                    NOP
                    NOP
            
                    MSR	  CPSR_c,R2
                    LDR	  PC,[SP], #+0x04
                   
                   
                   PUBLIC ExecuteSYSIMB

     ExecuteSYSIMB:
            
                    NOP
                    NOP
                    NOP
             
      clean_loop_s:
 
                    // clean entire dcache using test and clean
                    MRC   p15, 0, r15, c7, c10, 3
            
                    NOP
                    NOP
                    NOP
            
                    BNE   clean_loop_s
                    MOV   R0, #0x00
            
                    // drain write buffer
                    MCR   p15, 0, r0, c7, c10, 4
            
                    NOP
                    NOP
                    NOP
                    NOP
            
                    // invalidate icache
                    MCR	  p15, 0, r0, c7, c5, 0
            
                    NOP
                    NOP
                    NOP
                    NOP
            
                    BX       LR
                   
                    PUBLIC   InitSystemMode
                  
    InitSystemMode:
     
 	            STR	     LR, [SP, #-0x04]!
	            MRS	     R2,  CPSR
            
                    SWI      0x81B5
                    CMP      R0, #0x00
	            SWIEQ    0x00
                    SWINE    0x04

	            MRS      R1, CPSR
	            ORR      R1, R1,#0x1F
	            MSR      CPSR_c, R1
                    
                    LDR	     PC,[SP], #+0x04  
                    
                    PUBLIC   InitUserMode
                  
       InitUserMode:
     
 	            STR	     LR, [SP, #-0x04]!
	            MRS	     R2,  CPSR
            
                    SWI      0x81B5
                    CMP      R0, #0x00
	            SWIEQ    0x00
                    SWINE    0x04

	            MRS      R1, CPSR
                    BIC      R1, R1,#0x1F
	            ORR      R1, R1,#0x10
	            MSR      CPSR_c, R1
                    
                    LDR	     PC,[SP], #+0x04 
                    
                  

                    PUBLIC  EnableInterrupts
            
 EnableInterrupts:
             
                    PUSH   {R1-R2, LR}
             
                    MRS     R1, CPSR
                    BIC     R1, R1, #0xC0
            
                    SWI     0x81B5
                    CMP     R0, #0x00
	            SWIEQ   0x00
                    SWINE   0x04

                    MSR     CPSR_c, R1
                    POP    {R1-R2, PC}
            

                    PUBLIC  DisableInterrupts
            
 DisableInterrupts:
             
                    PUSH   {R1-R2, LR}
             
                    MRS     R0, CPSR
                    ORR     R1, R0, #0xC0
            
                    SWI     0x81B5
                    CMP     R0, #0x00
	            SWIEQ   0x00
                    SWINE   0x04

                    MSR     CPSR_c, R1
                    POP    {R1-R2, PC}
                   

	
                   END

	