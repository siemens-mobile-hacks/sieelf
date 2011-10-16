//  Draw Hook //
//alpha_selector.asm - Capturing images of translucent
//(c)Dimadze

#include "drawhook.h"

                    EXTERN FuncDistributor_0x05
                    EXTERN FuncDistributor_0x17               
#ifdef X75
                    EXTERN isCSMException
#endif
                    
                    
                    CODE16  // Cut in THUMB mode
                    
                    
// Capturing all of the images IMGHDR

                    RSEG PATCH_DRAWOBJECT_OBJ05:CODE
                    
                    PUSH   {R4-R7,LR} // Restore erased team
                    BL      img_05_check   
                   
                    
// Capturing all of the images EIMGHDR

                    RSEG PATCH_DRAWOBJECT_OBJ17:CODE 
                    
                    PUSH   {R4-R7,LR} // Restore erased team
                    BL      img_17_check                

// Well, this is our processor test
// This is sort of images on transparent and regular
// Compute arguments for our p-uu rendering
       
                    RSEG PATCH_BODY:CODE
                    
       img_05_check: // Check for the presence of translucent IMGHDR
    
                    MOV    R5, R0          // Recover command
                    MOV    R4, R1          // Recover command
                    
                    
                    // R0 = SCREEN_STRUCT
                    // R1 = DRAWOBJ_05
 
                    PUSH  {R0-R2,LR}       // Now we need to survive, who knows what ...
                    
#ifdef X75
                    BLX    isCSMException  // Let's see, a CSM is "on top" is not an exception?
                    CMP    R0, #0x01
                    MOV    R0, R5 
                    BEQ    is_csm_exc_05   // Exception, then dumps ...
#endif
                    
                    LDR    R2, [R1, #0x14] // R2 = IMGHDR *img
                    LDRB   R2, [R2, #0x02] // R2 = img->bpnum 
                    
                    MOV    R1, #0xF0       // Pre-clearing bit
                    BIC    R2, R1          // Clear the 4.8 bits, ie Any number of 0xXA would like 0x0A
                    
                    CMP    R2, #0x0A       // Check to see if the alpha channel?
                    BNE    not_alpha_05    // Depending on the test leaving
                    
                    // Yeah, the alpha channel is! Draw a special function ...
                    MOV    R1, R0          // Take the address of the structure SCREEN_STRUCT
                    MOV    R0, R4          // Take the address of the structure DRWOBJ_05
                    LDR    R2, =FuncDistributor_0x05            
 	            BLX    R2              // Let's go to the distributor
                    
#ifdef X75  
                    MOV    R2, #0x00       // The picture is painted, now break its structure
                    STR    R2, [R4, #0x14] // to the phone itself, it again drew
#endif
                    
     not_alpha_05:
    is_csm_exc_05:
     
                    POP   {R0-R2,PC}        // Now will ship preservation
                    
 
 
       img_17_check: // Check for the presence of translucent EIMGHDR
   
                    SUB    SP, #0x14       // Recover command
                    MOV    R6, R0          // Recover command
                    
                    // R0 = SCREEN_STRUCT
                    // R1 = DRAWOBJ_17
                    
                    PUSH  {R0-R2,LR}       // Now we need to survive, who knows
                    
#ifdef X75
                    BLX    isCSMException
                    CMP    R0, #0x01
                    MOV    R0, R6 
                    BEQ    is_csm_exc_17
#endif
                     
                    LDR    R2, [R1, #0x14] // R2 = EIMGHDR *eimg
                    LDR    R2, [R2, #0x00] // R2 = eimg->bpnum 
                    
                    MOV    R1, #0xF0       // Pre-clearing bit
                    BIC    R2, R1          // Clear the 4.8 bits, ie Any number of 0xXA would like 0x0A
                    
                    CMP    R2, #0x0A       // Check to see if the alpha channel?
                    BNE    not_alpha_17    // Depending on the test leaving
                    
                    // Yeah, the alpha channel is! Draw a special function ...
                    MOV    R1, R0          // Take the address of the structure SCREEN_STRUCT
                    MOV    R0, R4          // Take the address of the structure DRWOBJ_17
                    LDR    R5, =FuncDistributor_0x17            
 	            BLX    R5              // Let's go to the distributor
                    
#ifdef X75  
                    MOV    R2, #0x00       // The picture is painted, now break its structure
                    STR    R2, [R4, #0x14] // to the phone itself, it again drew
#endif
                    
      not_alpha_17:
     is_csm_exc_17:
     
                    POP   {R0-R2,PC}       // Now will ship preservation
     
                    END
                    
                    
                    
