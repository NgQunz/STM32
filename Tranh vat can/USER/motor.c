#include "motor.h"

TIM_TypeDef *TIM_Motor = TIM4;
// Motor
uint8_t prescaler  =  72 -1;
int16_t period     =  2000 -1;
	
int8_t max_speed = 100;
int8_t min_speed = 20;


void Motor_Init(void)
{
	// Struct
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	//====================== Motor ======================
	// Clock GPIO
	if(MOTOR_PORT == GPIOA) 
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	if(MOTOR_PORT == GPIOB) 
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	if(MOTOR_PORT == GPIOC) 
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	if(MOTOR_PORT == GPIOD) 
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	}

	// Clock Timer
	if(TIM_Motor == TIM1) 
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	}
	if(TIM_Motor == TIM2) 
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
	if(TIM_Motor == TIM3) 
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	if(TIM_Motor == TIM4) 
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}
	
	GPIO_InitStruct.GPIO_Pin = MOTOR_L_PIN1 | MOTOR_L_PIN2 | MOTOR_R_PIN1 | MOTOR_R_PIN2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_PORT, &GPIO_InitStruct);
	
	TIM_InitStruct.TIM_ClockDivision = 0;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = period;
	TIM_InitStruct.TIM_Prescaler = prescaler;
	TIM_TimeBaseInit(TIM_Motor, &TIM_InitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM_Motor, &TIM_OCInitStruct);
	TIM_OC2Init(TIM_Motor, &TIM_OCInitStruct);
	TIM_OC3Init(TIM_Motor, &TIM_OCInitStruct);
	TIM_OC4Init(TIM_Motor, &TIM_OCInitStruct);
	
	TIM_Cmd(TIM_Motor, ENABLE);
	TIM_CtrlPWMOutputs(TIM_Motor, ENABLE);
}

void Motor_Move(uint8_t motor, float level) // level: -100 / 100
{
	if(level > max_speed){ 
		level = max_speed;
	}
	else if(level < -max_speed){ 
		level = -max_speed;
	}

	switch(motor){
		case MOTOR_LEFT:
				if(level >= 0){
					TIM_Motor->CCR1 = 0;
					TIM_Motor->CCR2 = (uint16_t)(period*level/100);
				}
				else{
					TIM_Motor->CCR1 = (uint16_t)(-period*level/100);
					TIM_Motor->CCR2 = 0;
				}
				break;
					
		case MOTOR_RIGHT:
				if(level >= 0){
					TIM_Motor->CCR3 = (uint16_t)(period*level/100);
					TIM_Motor->CCR4 = 0;
				}
				else{
					TIM_Motor->CCR3 = 0;
					TIM_Motor->CCR4 = (uint16_t)(-period*level/100);
				}
				break;
	}
}
