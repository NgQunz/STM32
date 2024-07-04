#include "delay.h"

void Delay_Init(void){
//	
	
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	RCC_HSICmd(DISABLE);
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, 9);
	RCC_PLLCmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7;
	TIM_TimeBaseInitStructure.TIM_Period = 999;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMER, &TIM_TimeBaseInitStructure);	
	TIM_Cmd(TIMER, ENABLE);
}

void Delay_ms(uint16_t time){
	while(time > 0){
		TIM_ClearFlag(TIMER, TIM_FLAG_Update);
		while(TIM_GetFlagStatus(TIMER, TIM_FLAG_Update) != SET);
		time--;
	}
}

void Delay_s(uint16_t time){
	
}
