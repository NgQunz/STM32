/*
  ******************************************************************************
  * @file		LED_MATRIX.h                                                             *
  * @author	Nguyen Minh Quan                                                 *
  * @date		28/2/2024
	* @ver 1.0
  ******************************************************************************
*/
	
#ifndef __TIMER2_H__
#define __TIMER2_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"    // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"                 
	 
#define PWM_TIM2_OC1_PIN			GPIO_Pin_0
#define PWM_TIM2_OC2_PIN			GPIO_Pin_1
#define TIM2_PWM_PULSE (uint16_t) TIM2_period/2
#define TIM2_period 35999
#define TIM2_prescaler 1
#define TIM2_repertition 0
	 
void Timer_Init(void);
void Delay_1ms(void);
void Delay_ms(unsigned int time);
void led_Init(void);
void PWM_Init(void);
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/