#include "gpio.h"

uint8_t flag_check = 0 ;

void GPIO_init(void) {
    // Enable clocks for GPIOC, GPIOA, and GPIOB
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enable GPIOC clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable GPIOA clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable GPIOB clock

    // Configure PC14 (LED Stop) as output push-pull, max speed 50 MHz
    LED_PORT_STOP->CRH &= ~(unsigned int)(0xF << ((14 - 8) * 4)); // Clear configuration for PC14
    LED_PORT_STOP->CRH |= (0x3 << ((14 - 8) * 4));  // Output mode, 50 MHz

    // Configure PA1 (LED Start) as output push-pull, max speed 50 MHz
    LED_PORT_START->CRL &= ~(unsigned int)(0xF << (1 * 4));        // Clear configuration for PA1
    LED_PORT_START->CRL |= (0x3 << (1 * 4));         // Output mode, 50 MHz

    // Configure PB14 and PB15 as input with pull-up
    GPIOB->CRH &= ~(unsigned int)(0xF << ((14 - 8) * 4)); // Clear configuration for PB14
    GPIOB->CRH |= (0x8 << ((14 - 8) * 4));  // Input mode with pull-up
    GPIOB->CRH &= ~(unsigned int)(0xF << ((15 - 8) * 4)); // Clear configuration for PB15
    GPIOB->CRH |= (unsigned int)(0x8 << ((15 - 8) * 4));  // Input mode with pull-up

    // Enable pull-up for PB14 and PB15
    GPIOB->ODR |= (BUTTON_START | BUTTON_STOP);

    // Initialize LEDs to OFF
    LED_PORT_START->ODR &= ~ (unsigned int) LED_START;
    LED_PORT_STOP ->ODR &= ~ (unsigned int) LED_STOP;

    // Configure PB4 as input with pull-up resistor
    GPIOB->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);  // Clear configuration for PB4
    GPIOB->CRL |= GPIO_CRL_CNF4_1;  // Input with pull-up/pull-down
    GPIOB->ODR |= GPIO_ODR_ODR4;    // Enable pull-up resistor
		
		
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;


    GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);  
    GPIOA->CRL |= GPIO_CRL_CNF0_1;                    
    GPIOA->ODR |=  GPIO_Pin_0;                         

    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);  
    GPIOC->CRH |= GPIO_CRH_MODE13_0;                    

    
    GPIOC->ODR |= LED_PIN;

    AFIO->EXTICR[0] &= ~(unsigned int )AFIO_EXTICR1_EXTI0;
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;


    EXTI->RTSR |= EXTI_RTSR_TR0;  // Rising edge trigger
    EXTI->FTSR |= EXTI_FTSR_TR0;  // Falling edge trigger


    EXTI->IMR |= EXTI_IMR_MR0;


    NVIC_SetPriority(EXTI0_IRQn, 2);
    NVIC_EnableIRQ(EXTI0_IRQn);
}


uint16_t Read_Pin(uint16_t pin)
{
    return BUTTON_PORT->IDR & pin;  // Read input data register
}


void EXTI0_IRQHandler(void) 
 {
    if (EXTI->PR & EXTI_PR_PR0) 
    {
        GPIOC->ODR ^= (1 << 13);
        flag_check = 1 ; 
        EXTI->PR = EXTI_PR_PR0;
    }
}