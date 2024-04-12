/*
  ******************************************************************************
  * @file		stm32_gpio.h                                                              *
  * @author	Nguyen Minh Quan                                                *
  * @date		27/03/2024    
	* @ver 1.0                                                       *
  ******************************************************************************
*/
#include "GPIO.h"


void timer_Init(void);
void Delay_1ms(void);
void Delay_ms(unsigned int time);

void led_Blink(void){
//	GPIO_ResetBits(GPIOA,	GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0);
//	GPIO_WriteBit(GPIOA,	GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0, Bit_RESET);
//	GPIOC->ODR= 0x00;
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
//	GPIO_Write (GPIOA,0xFFFF);
//	GPIO_WriteBit (GPIOA, GPIO_Pin_0, Bit_SET);
	Delay_ms(500);
//	GPIO_SetBits(GPIOA,	GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0);
//	GPIO_WriteBit(GPIOA,	GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0, Bit_SET);
//	GPIOC->ODR= 0xFF;
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
//	GPIO_Write (GPIOA,0x0000);
//	GPIO_WriteBit (GPIOA, GPIO_Pin_0, Bit_RESET);
	Delay_ms(500);
}
void Config(void){
	GPIO_InitTypeDef GPIO;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |
									GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO);
 }

/********************************* END OF FILE ********************************/
/******************************************************************************/