#include <stdint.h>
#include "miros.h"
#include "TM4C123GH6PM.h"

OSThread * volatile OS_curr;
OSThread * volatile OS_next;

void OS_init(void){
    // set pendsv bit to lowest prioirty
    *(uint32_t volatile *)0xE000ED20 |= (0xFFU << 16);
}

void OS_sched(void){
    // to avoid race conditions, os sched mMUST be called in critical conds
    if (OS_next != OS_curr){
        *(uint32_t volatile *)0xE000ED04 = (1U << 28);
    }
}
void OSThread_start(
    OSThread *me,
    OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize){
        uint32_t *sp = (uint32_t *)((((uint32_t)stkSto + stkSize)/8)*8);
        // cortex m stack must be alligned w/ 8 byte boundary, must deal w/ this our own
        //We can ensure allignment by rounding that address, divide by 8 then multiply by 8
        // arm cortex m grows down from hi-low memory

        /* fabricate Cortex-M ISR stack frame for blinky1 */
    *(--sp) = (1U << 24);  /* xPSR */
    *(--sp) = (uint32_t)&threadHandler; /* PC */
    *(--sp) = 0x0000000EU; /* LR  */
    *(--sp) = 0x0000000CU; /* R12 */
    *(--sp) = 0x00000003U; /* R3  */
    *(--sp) = 0x00000002U; /* R2  */
    *(--sp) = 0x00000001U; /* R1  */
    *(--sp) = 0x00000000U; /* R0  */
    /* additionally, fake registers R4-R11 */
    *(--sp) = 0x0000000BU; /* R11 */
    *(--sp) = 0x0000000AU; /* R10 */
    *(--sp) = 0x00000009U; /* R9 */
    *(--sp) = 0x00000008U; /* R8 */
    *(--sp) = 0x00000007U; /* R7 */
    *(--sp) = 0x00000006U; /* R6 */
    *(--sp) = 0x00000005U; /* R5 */
    *(--sp) = 0x00000004U; /* R4 */

    // save top of stack 
    me->sp = sp;
    }
//it  a good idea to set the stack entry tos like DEADBEEF to show you where each mem is allocated
// check datasheet to figure out how to trigger interrupt

// other interruts can preempt other interrupts
// READ DATASHEEt to figure out how to change nterrupt priorities

__ASM
void PendSV_Handler(void){
    /**Dissaembly code */
}