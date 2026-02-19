#include <stdint.h> // C99 standard integers
#include "bsp.h"

#if 0
/* background code: sequential with blocking version */
int main(void) {
    BSP_init();
    while (1) {
        BSP_ledGreenOn();
        BSP_delay(BSP_TICKS_PER_SEC / 4U);
        BSP_ledGreenOff();
        BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
    }

    //return 0;
}
#endif

uint32_t stack_blinky1[40];
uint32_t *sp_blinky1 = & stack_blinky1;
/* background code: non-blocking version */
int main1(void) {
    BSP_init();
    while (1) {
        /* Blinky polling state machine */
        static enum {
            INITIAL,
            OFF_STATE,
            ON_STATE
        } state = INITIAL;
        static uint32_t start;
        switch (state) {
            case INITIAL:
                start = BSP_tickCtr();
                state = OFF_STATE; /* initial transition */
                break;
            case OFF_STATE:
                if ((BSP_tickCtr() - start) > BSP_TICKS_PER_SEC * 3U / 4U) {
                    BSP_ledGreenOn();
                    start = BSP_tickCtr();
                    state = ON_STATE; /* state transition */
                }
                break;
            case ON_STATE:
                if ((BSP_tickCtr() - start) > BSP_TICKS_PER_SEC / 4U) {
                    BSP_ledGreenOff();
                    start = BSP_tickCtr();
                    state = OFF_STATE; /* state transition */
                }
                break;
            default:
                //error();
                break;
        }
    }
    //return 0;
}

uint32_t stack_blinky2[40];
uint32_t *sp_blinky2 = & stack_blinky2;
/* background code: non-blocking version */
int main2(void) {
    BSP_init();
    while (1) {
        /* Blinky polling state machine */
        static enum {
            INITIAL,
            OFF_STATE,
            ON_STATE
        } state = INITIAL;
        static uint32_t start;
        switch (state) {
            case INITIAL:
                start = BSP_tickCtr();
                state = OFF_STATE; /* initial transition */
                break;
            case OFF_STATE:
                if ((BSP_tickCtr() - start) > BSP_TICKS_PER_SEC * 3U / 4U) {
                    BSP_ledGreenOn();
                    start = BSP_tickCtr();
                    state = ON_STATE; /* state transition */
                }
                break;
            case ON_STATE:
                if ((BSP_tickCtr() - start) > BSP_TICKS_PER_SEC / 4U) {
                    BSP_ledGreenOff();
                    start = BSP_tickCtr();
                    state = OFF_STATE; /* state transition */
                }
                break;
            default:
                //error();
                break;
        }
    }
    //return 0;
}

int main(){
    uint32_t volatile run = 0U;

    BSP_init();

    *(--sp_blinky1) = (1U << 24);
    *(--sp_blinky1) = (uint32_t)&main1; // you can cast address to fcn, this is PC register, where it will return to
    *(--sp_blinky1) = 0x00000001; // lr, etc.

    *(--sp_blinky2) = (1U << 24);
    *(--sp_blinky2) = (uint32_t)&main2; // you can cast address to fcn, this is PC register, where it will return to
    *(--sp_blinky2) = 0x00000001; // lr, etc.
}