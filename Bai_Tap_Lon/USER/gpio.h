#ifndef __GPIO__
#define __GPIO__

#include "stm32f10x.h" 

#include <stdint.h>

#define LED_PORT_STOP   GPIOC
#define LED_PORT_START  GPIOA
#define BUTTON_PORT     GPIOB
#define BUTTON_STOP     (1 << 14) // PB14
#define BUTTON_START    (1 << 15) // PB15
#define LED_STOP       	(1 << 14) // PC14
#define LED_START       (1 << 1)  // PA1

#define INT_PORT    	GPIOA
#define INT_PIN     	(1 << 0)    // PA0
#define LED_PIN    		(1 << 13)
#define LED_PORT  		 GPIOC

extern uint8_t flag_check;

void GPIO_init(void );
uint16_t Read_Pin(uint16_t pin);
void EXTI0_IRQHandler(void);

#endif



