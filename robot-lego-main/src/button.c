#include "button.h"
#include "led.h"


void Button_Init(void){
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_IPU;	//	Pull up
	GPIO_InitTypeDefStructure.GPIO_Pin  = BUTTON_VIEW | BUTTON_ONOFF | BUTTON_RUN | BUTTON_PRG;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUTTON_PORT, &GPIO_InitTypeDefStructure);
}

uint8_t Button_Read(uint8_t pin){
	if(GPIO_ReadInputDataBit(BUTTON_PORT, pin) == Bit_SET)
		return Release;
	else 
		return Press;
}


