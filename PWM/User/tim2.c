#include "tim2.h"


void Timer_Init(void)
{
	  TIM_TimeBaseInitTypeDef timer2;
		TIM_OCInitTypeDef tim_oc;
		GPIO_InitTypeDef gpio;
		// khoi tao cac gia tri cua timer 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
    timer2.TIM_CounterMode = TIM_CounterMode_Up; 
    timer2.TIM_Period = TIM2_period; 
    timer2.TIM_Prescaler = TIM2_prescaler ;
    timer2.TIM_RepetitionCounter = 0;
		timer2.TIM_ClockDivision =TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2,&timer2); 
    TIM_Cmd(TIM2,ENABLE); 
		// khoi tao cac gia tri cua gpio
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		gpio.GPIO_Mode = GPIO_Mode_AF_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &gpio);
		
		tim_oc.TIM_OCMode = TIM_OCMode_PWM1;
		tim_oc.TIM_OutputState = TIM_OutputState_Enable;
		tim_oc.TIM_OCPolarity = TIM_OCPolarity_High;
		tim_oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
		tim_oc.TIM_Pulse = TIM2_PWM_PULSE;
		
		TIM_OC1Init(TIM2, &tim_oc);
		TIM_OC2Init(TIM2, &tim_oc);
		TIM_Cmd(TIM2 , ENABLE);
		TIM_CtrlPWMOutputs(TIM2, ENABLE);
}
