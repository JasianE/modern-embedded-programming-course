/* Board Support Package */
#include "TM4C123GH6PM.h"
#include "bsp.h"

__attribute__((naked)) void assert_failed (char const *file, int line) {
    /* TBD: damage control */
    NVIC_SystemReset(); /* reset the system */
}

void SysTick_Handler(void) {
    GPIOF_AHB->DATA_Bits[LED_BLUE] ^= LED_BLUE;
}

void BSP_init(void) {
    SYSCTL->RCGCGPIO  |= (1U << 5U); /* enable Run mode for GPIOF */
    SYSCTL->GPIOHBCTL |= (1U << 5U); /* enable AHB for GPIOF */

    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

    SysTick->LOAD = SYS_CLOCK_HZ/2U - 1U;
    SysTick->VAL  = 0U;
    SysTick->CTRL = (1U << 2U) | (1U << 1U) | 1U;

    SysTick_Handler();

    __enable_irq();
}
