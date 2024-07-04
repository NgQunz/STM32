#ifndef	__LED_H
#define	__LED_H

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#define LED_PORT GPIOB
#define LED_1 GPIO_Pin_12
#define LED_2 GPIO_Pin_13
#define LED_3 GPIO_Pin_14
#define LED_4 GPIO_Pin_15

void Led_Init(void);
void Led_On(uint16_t pin);
void Led_Off(uint16_t pin);
void Led_INV(uint16_t pin);

#endif
