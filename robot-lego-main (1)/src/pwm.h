#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"     
#include "stm32f10x_rcc.h"  
#include "stm32f10x_gpio.h" 
#include "stm32f10x_tim.h"

#define TIM2_PERIOD			1999
#define TIM2_PRESCALER	79
#define TIM2_REPETITION	0
#define TIM2_PWM_PULSE	(uint16_t) TIM2_PERIOD/2

#define PWM_TIM2_OC1_PIN			GPIO_Pin_0
#define PWM_TIM2_OC2_PIN			GPIO_Pin_1
#define PWM_TIM2_OC3_PIN			GPIO_Pin_2
#define PWM_TIM2_OC4_PIN			GPIO_Pin_3

void Pwm_Init(void);

#endif
