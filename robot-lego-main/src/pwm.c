#include "pwm.h"

void Pwm_Init(void)
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_TypeDefStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
	
	GPIO_TypeDefStructure.GPIO_Pin = PWM_TIM2_OC1_PIN | PWM_TIM2_OC2_PIN | PWM_TIM2_OC3_PIN | PWM_TIM2_OC4_PIN;
	GPIO_TypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_TypeDefStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_TypeDefStructure);		
	
	/* Basic Timer Init */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM2_PRESCALER;
	TIM_TimeBaseInitStructure.TIM_Period = TIM2_PERIOD;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = TIM2_REPETITION;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;

	TIM_OCInitStructure.TIM_Pulse = TIM2_PWM_PULSE;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_Cmd(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);	
	
	TIM2->CCR1 = 0;
	TIM2->CCR2 = 0;
	TIM2->CCR3 = 0;
	TIM2->CCR4 = 0;
}
