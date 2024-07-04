#include "led.h"

void Led_Init(void){
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitTypeDefStructure.GPIO_Pin = LED_1 | LED_2 | LED_3 | LED_4;
	GPIO_Init(LED_PORT, &GPIO_InitTypeDefStructure);
	Led_Off(LED_1);
	Led_Off(LED_2);
	Led_Off(LED_3);
	Led_Off(LED_4);
}

void Led_On(uint16_t pin){
	LED_PORT->BRR = pin;
}
void Led_Off(uint16_t pin){
	LED_PORT->BSRR = pin;
}


void Led_INV(uint16_t pin){
	if (GPIO_ReadInputDataBit(GPIOB, pin) == Bit_SET)
		GPIO_WriteBit(GPIOB, pin, Bit_RESET);
	else
		GPIO_WriteBit(GPIOB, pin, Bit_SET);
}