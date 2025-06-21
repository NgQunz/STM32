#include "Speaker.h"

// Cau hinh coi tu dong (PA2, TIM2 Channel 3, PWM 2 kHz)
void Speaker_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;

    // Bat dong ho cho GPIOA va TIM2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // Cau hinh PA2 la PWM (alternate function)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Cau hinh TIM2: 2 kHz (chu ky = 500 us)
    TIM_TimeBaseStruct.TIM_Period = 1000 - 1; // ARR = 1000
    TIM_TimeBaseStruct.TIM_Prescaler = 36 - 1; // PSC = 36
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);

    // Cau hinh PWM Channel 3 (PA2)
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0; // Duty cycle = 0% (tat ban dau)
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(TIM2, &TIM_OCInitStruct);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

    // Bat TIM2
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

// Bat coi (PWM 50% duty cycle, lien tuc)
void Speaker_On(void) {
    TIM_SetCompare3(TIM2, 500); // Duty cycle = 50% (500/1000)
}

// Tat coi (PWM 0% duty cycle)
void Speaker_Off(void) {
    TIM_SetCompare3(TIM2, 0); // Duty cycle = 0%
}
