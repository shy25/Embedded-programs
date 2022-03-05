#include "../inc/asm.h"


//------------------------------------------------------------------------------
//   uint8_t wakeupFromSleepFlag
//
// A simple flag used to indicate if the wakeup occurred from Sleep or Standby 
// condition.
// If this flag is zero, an interrupt has affected the WFI instruction and the
// BlueNRG-1 doesn't enter in deep sleep state. So, no context restore is
// necessary.
// If this flag is non-zero, the WFI instruction puts the BlueNRG-1 in deep sleep.
// So, at wakeup time a context restore is necessary.
// Note: The smallest unit of storage is a single byte.
//
// NOTE: This flag must be cleared before the context restore is called
//------------------------------------------------------------------------------

	
                __BSS__
                __EXPORT__  wakeupFromSleepFlag
GLOBAL_VAR(wakeupFromSleepFlag)
                __SPACE__ 1
		ALIGN_MEM(4)

//------------------------------------------------------------------------------
//   uint32_t savedMSP
//
// Private storage to hold the saved stack pointer.  This variable is only used
// in this file and should not be extern'ed.  In our current design we
// do not use real context switching, but only context saving and restoring.
// As such, we only need to keep track of the Main Stack Pointer (MSP). This
// variable is used to hold the MSP between a save and a restore.
//------------------------------------------------------------------------------


         __BSS__
         __EXPORT__ savedMSP
GLOBAL_VAR(savedMSP)
         __SPACE__ 4


		
//------------------------------------------------------------------------------
//   void CS_contextSave(void)
//   void CS_contextRestore(void)
//
// These two functions are needed for the context switch during the power
// save procedure. The purpose of the CS_contextSave() function is to 
// either save the current context and trigger sleeping through the 'WFI' 
// instruction. 
// The CS_contextRestore() function restores the context saved before 
// to go in deep sleep.  
// All the Cortex M0 registers are saved and restored plus after wakeup
// -----------------------------------------------------------------------------
                 __CODE__
                 __THUMB__
                 __EXPORT__ CS_contextSave
                 __EXPORT__ CS_contextRestore
EXPORT_FUNC(CS_contextSave)
                 PUSH   { r4 - r7, lr }       /* store R4-R7 and LR (5 words) onto the stack */
                 MOV    R3, R8                /* mov thread {r8 - r12} to {r3 - r7} */
                 MOV    R4, R9
                 MOV    R5, R10
                 MOV    R6, R11        
                 MOV    R7, R12        
                 PUSH   {R3-R7}               /* store R8-R12 (5 words) onto the stack */
                 LDR    R4, =savedMSP         /* load address of savedMSP into R4 */
                 MOV    R3, SP                /* load the stack pointer into R3 */
                 STR    R3, [R4]              /* store the MSP into savedMSP */
                 DSB
                 WFI                          /* all saved, trigger deep sleep */
                 ENDFUNC
					
EXPORT_FUNC(CS_contextRestore)
                /* Even if we fall through the WFI instruction, we will immediately
                 * execute a context restore and end up where we left off with no
                 * ill effects.  Normally at this point the core will either be
                 * powered off or reset (depending on the deep sleep level). */
                LDR    R4, =savedMSP         /* load address of savedMSP into R4 */
                LDR    R4, [R4]              /* load the SP from savedMSP */
                MOV    SP, R4                /* restore the SP from R4 */
                POP   {R3-R7}                /* load R8-R12 (5 words) from the stack */
                MOV    R8, R3                /* mov {r3 - r7} to {r8 - r12} */
                MOV    R9, R4
                MOV    R10, R5
                MOV    R11, R6
                MOV    R12, R7
                POP   { R4 - R7, PC }        /*load R4-R7 and PC (5 words) from the stack */
                ENDFUNC
               
//------------------------------------------------------------------------------
//   void InternalIdleSleep(void)
//
// A simple internal function call (to be called from halSleep) for executing
// the WFI instruction and entering the simple, idle sleep state.
//------------------------------------------------------------------------------
                  __EXPORT__ BlueNRG_IdleSleep
EXPORT_FUNC(BlueNRG_IdleSleep)
                  NOP
                  WFI                    /* trigger idle sleep */
                  NOP
                  BX   LR                /* return */
                  ENDFUNC


    ALIGN_MEM(4)
	__END__
