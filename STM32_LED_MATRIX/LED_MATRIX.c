/*
  ******************************************************************************
  * @file		stm32_gpio.h                                                              *
  * @author	Nguyen Minh Quan                                                *
  * @date		27/03/2024    
	* @ver 1.0                                                       *
  ******************************************************************************
*/
#include "LED_MATRIX.h"

unsigned char cot[]= {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned int hang[]= {0xffff, 0x80ff,0x77ff, 0x77ff, 0x77ff, 0x77ff, 0x80ff, 0xffff};

void led_Matrix_Init(void){
	GPIO_InitTypeDef led_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	led_init.GPIO_Mode = GPIO_Mode_Out_PP;
	led_init.GPIO_Pin = GPIO_Pin_8 |  GPIO_Pin_9 |  GPIO_Pin_10 |  GPIO_Pin_11 |
											GPIO_Pin_12 |  GPIO_Pin_13 |  GPIO_Pin_14 |  GPIO_Pin_15 ;
	led_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&led_init);
	
	led_init.GPIO_Mode = GPIO_Mode_Out_PP;
	led_init.GPIO_Pin = GPIO_Pin_0 |  GPIO_Pin_1 |  GPIO_Pin_2 |  GPIO_Pin_3 |
											GPIO_Pin_4 |  GPIO_Pin_5 |  GPIO_Pin_6 |  GPIO_Pin_7 ;
	led_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&led_init);
}

/********************************* END OF FILE ********************************/
/******************************************************************************/