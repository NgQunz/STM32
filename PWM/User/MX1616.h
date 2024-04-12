#ifndef __ABC__
#define __ABC__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "tim2.h"

#define MX1616_PORT	GPIOA		
#define INA1_PIN		PWM_TIM2_OC2_PIN
#define INB1_PIN	 	PWM_TIM2_OC1_PIN

void MX1616_Init(void);
void MX1616_SetLevel(uint8_t level);
void MX1616_SetForward(uint8_t level);
void MX1616_SetBackward(uint8_t level);
void MX1616_SetStopping(void);


#ifdef __cplusplus
}
#endif

#endif
