#include "button.h"
#include "tim2.h"  // Gi? s? b?n có thu vi?n th?i gian tr? nhu Delay_ms()


void GPIO_Config(void){
    GPIO_InitTypeDef GPIO;

    // B?t clock GPIOA, GPIOB, GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

    // C?u hình LED output (GPIOC, PC13)
    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO.GPIO_Pin = GPIO_Pin_13;
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);  // LED t?t khi kh?i d?ng

}

// Funtion EXTI PA12 - Input pull up : press 0  - just call in main and auto run IRQHandler when press PA12
void Button_EXTI_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    // Enable Clock for GPIOA and AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    // Config PA12 as input pull-up
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Connect PA12 to EXTI Line12
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);

    // Config EXTI Line12
    EXTI_InitStruct.EXTI_Line = EXTI_Line12;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // Trigger on button press (active low)
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    // Config NVIC for EXTI15_10_IRQn (covers Line10–15)
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

// Fution Process EXTI 

void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        // Reversal status PC13 with XOR logic
        GPIOC->ODR ^= GPIO_Pin_13;
        // Clear Flag
        EXTI_ClearITPendingBit(EXTI_Line12);
    }
}
