#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Config(void);
void Delay_ms(uint16_t _time);
void Button(void);
GPIO_InitTypeDef GPIO;
int main()
{
	Config();
	while (1)
	{
		
	}
}
void Button(void)
{
	
}
void Delay_ms(uint16_t ms)
{
	uint16_t i, j;
	for (i = 0; i < ms; i++)
	{
		for (j = 0; j < 7999; j++)
			;
	}
}

void Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO.GPIO_Pin = GPIO_Pin_13;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO);
	GPIO.GPIO_Mode = GPIO_Mode_IPU;
	GPIO.GPIO_Pin = GPIO_Pin_1;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO);
}