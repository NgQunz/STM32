#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif
	#include "stm32f10x.h"                  // Device header
//	#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
//	#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
 
	#define LED_PIN GPIO_Pin_13
	#define LED_PORT GPIOC
	
	void GPIO_Configuration(void);

#ifdef __cplusplus
}
#endif

#endif
