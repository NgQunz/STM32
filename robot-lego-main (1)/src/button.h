#ifndef __BUTTON_H
#define	__BUTTON_H

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stdbool.h>
#include <stm32f10x_exti.h>


#define BUTTON_PORT GPIOB
#define BUTTON_VIEW GPIO_Pin_6
#define BUTTON_ONOFF GPIO_Pin_7
#define BUTTON_RUN GPIO_Pin_8
#define BUTTON_PRG	GPIO_Pin_9

typedef enum{
	Press = 0,
	Release = 1
}Button_Val;

void Button_Init(void);
uint8_t Button_Read(uint8_t pin);

#endif



