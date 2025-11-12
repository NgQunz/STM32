#include "stm32f10x.h"
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC



void Delay_ms(uint16_t time){
	uint16_t i,j;
	for(i=0;i<time;i++){
		for(j=0;j<0x2aff;j++);
	}
}

int main(void){
	
	GPIO_InitTypeDef gpio;
	// Cau hinh gpio
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC , &gpio);
	
	
	while(1){
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_ms(500);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay_ms(500);
		
	}
	
	return 0;
	
}