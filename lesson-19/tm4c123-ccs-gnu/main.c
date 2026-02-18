#include "TM4C123GH6PM.h"
#include "bsp.h"

int main(void) {
    SYSCTL->RCGCGPIO  |= (1U << 5U); /* enable Run mode for GPIOF */
    SYSCTL->GPIOHBCTL |= (1U << 5U); /* enable AHB for GPIOF */

#if (__ARM_FP != 0) /* if VFP available... */
    /* make sure that the FPU is enabled by seting CP10 & CP11 Full Access */
    SCB->CPACR |= ((3UL << 20U)|(3UL << 22U));
#endif

    BSP_init();

    while (1) {
        //GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
        //GPIOF_AHB->DATA_Bits[LED_GREEN] = 0U;
        __disable_irq();
        GPIOF_AHB->DATA = GPIOF_AHB->DATA | LED_GREEN; // do not distrub the other bits
        __enable_irq();
        GPIOF_AHB->DATA = GPIOF_AHB->DATA & ~LED_GREEN; // clear the led_green bit, flashes it now
        __disable_irq();

#if (__ARM_FP != 0) /* if VFP available... */
        /* exercise the single-precision FPU */
        float x = 1.234f;
        float volatile y = x*x;
#endif
    }
    //return 0; // unreachable code
}
