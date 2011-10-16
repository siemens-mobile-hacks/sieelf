//  Draw Hook //
//Alpha_selector_ll.asm - Capturing images of translucent (LONG LINK) on the phone, where the frame of the body do not reach the patch
//(c)Dimadze

#include "drawhook.h"

                    EXTERN FuncDistributor_0x05
                    EXTERN FuncDistributor_0x17
#ifdef X75
                    EXTERN isCSMException
#endif
                    
                    CODE16  // cut in THUMB mode
                    
// Catching all the images IMGHDR

                    RSEG    PATCH_DRAWOBJECT_OBJ05:CODE
                    
                    PUSH   {R4-R7,LR} // Restore the overwritten command
                    BLX     img_05_check_j32 
                   
                    
// Catching all the images EIMGHDR

                    RSEG    PATCH_DRAWOBJECT_OBJ17:CODE 
                    
                    PUSH   {R4-R7,LR} // Restore the overwritten command
                    BLX     img_17_check_j32
                    
// Transitions
                    
                    CODE32
                    
                    RSEG    PATCH_DRAWOBJECT_OBJ05_J32:CODE 
                    
  img_05_check_j32:
                    
                    B       img_05_check
                    
                    
                    RSEG    PATCH_DRAWOBJECT_OBJ17_J32:CODE 
                    
  img_17_check_j32:
                    
                    B       img_17_check
                    
                    
//Restore
                    
                    RSEG    PATCH_REPAIRJUMP100:CODE 
                    
                    B       loc_jump_swi100
                    
                    RSEG    PATCH_REPAIRJUMP145:CODE 
                    
                    B       loc_jump_swi145
                    
                    
                    RSEG    PATCH_LOCALJUMP100:CODE 

   loc_jump_swi100:    
                    
                    
                    RSEG    PATCH_LOCALJUMP145:CODE 

   loc_jump_swi145:    

                           

// Well, this is our processor test
// This is sort of images on transparent and regular
// Compute arguments for our p-uu rendering

       
                    RSEG PATCH_BODY:CODE
                    
       img_05_check: // Check for the presence of this image in the text
    
                    MOV    R5, R0          // Recover command
                    MOV    R4, R1          // Recover command
                    
                    // R0 = SCREEN_STRUCT
                    // R1 = DRAWOBJ_05
                    
 
                    PUSH  {R0-R2,LR}       // Now we need to survive, who knows what ...
    
#ifdef X75
                    BL     isCSMException  // Let's see, a CSM is "on top" is not an exception?
                    CMP    R0, #0x01
                    MOV    R0, R5 
                    BEQ    is_csm_exc_05   // exception, then dumps ...
#endif
    
                    LDR    R2, [R1, #0x14] // R2 = IMGHDR *img
                    LDRB   R2, [R2, #0x02] // R2 = img->bpnum 
                    
                    BIC    R2, R2, #0xF0   // Clear the 8.4 bits, ie Any number of 0xXA would like 0x0A
                    
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
     
                    POP   {R0-R2,LR}        // Now will ship preservation
    
                    CMP    R0, #0x00         // Recover command
                    BX     LR
 
 
       img_17_check: // Check Pictures
   
                    SUB    SP, SP, #0x14   // Recover command
                    MOV    R6, R0          // Recover command
                    
                    // R0 = SCREEN_STRUCT
                    // R1 = DRAWOBJ_17
                    
                    PUSH  {R0-R2,LR}       // Now we need to survive, who knows what ...
                    
#ifdef X75
                    BL     isCSMException  // Let's see, a CSM is "on top" is not an exception?
                    CMP    R0, #0x01
                    MOV    R0, R6 
                    BEQ    is_csm_exc_17   // exception, then dumps ...
#endif
                     
                    LDR    R2, [R1, #0x14] // R2 = EIMGHDR *eimg
                    LDR    R2, [R2, #0x00] // R2 = eimg->bpnum 
                    
                    BIC    R2, R2, #0xF0   // Clear the 8.4 bits, ie Any number of 0xXA would like 0x0A
                    
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
                    
                    
                    
