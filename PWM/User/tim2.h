#ifndef __TIM2__
#define __TIM2__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"    // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC


#define TIM2_period 35999
#define TIM2_prescaler 1
#define TIM2_repertition 0
#define TIM2_PWM_PULSE (uint16_t) TIM2_period/2

#define PWM_TIM2_OC1_PIN			GPIO_Pin_0
#define PWM_TIM2_OC2_PIN			GPIO_Pin_1

void Timer_Init(void);
//void TIM2_IRQHandler(void);
//void delay_Ms(uint32_t time);

	 
#ifdef __cplusplus
}
#endif

#endif

