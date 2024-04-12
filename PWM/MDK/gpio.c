#include "gpio.h"

void GPIO_config(void)
{
		GPIO_InitTypeDef gpio;
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio.GPIO_Pin = led_Pin;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(led_Port, &gpio);	
	
}
