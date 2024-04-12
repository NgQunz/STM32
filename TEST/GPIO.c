/*
  ******************************************************************************
  * @file		stm32_gpio.h                                                              *
  * @author	Nguyen Minh Quan                                                *
  * @date		27/03/2024    
	* @ver 1.0                                                       *
  ******************************************************************************
*/
#include "GPIO.h"

void Config(void);
void timer_Init(void);
void Delay_1ms(void);
void Delay_ms(unsigned int time);
void led_Blink(void);
void led_Blink(void){
//	GPIO_ResetBits(GPIOA,	GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0);
//	GPIO_WriteBit(GPIOA,	GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0, Bit_RESET);
//	GPIOC->ODR= 0x00;
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//	GPIO_Write (GPIOA,0xFFFF);
//	GPIO_WriteBit (GPIOA, GPIO_Pin_0, Bit_SET);
	Delay_ms(500);
//	GPIO_SetBits(GPIOA,	GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0);
//	GPIO_WriteBit(GPIOA,	GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0, Bit_SET);
//	GPIOC->ODR= 0xFF;
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
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
	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO.GPIO_Pin = GPIO_Pin_13;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO);
 }
void timer_Init(void){
    TIM_TimeBaseInitTypeDef timer_init;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    timer_init.TIM_CounterMode = TIM_CounterMode_Up;
    timer_init.TIM_Period = 65535; // co the de gia tri max 
    timer_init.TIM_Prescaler = 2 - 1;
    timer_init.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&timer_init);
    TIM_Cmd(TIM2,ENABLE); // Enable Timer2
}

void Delay_1ms(void){
    TIM_SetCounter(TIM2,0); // Set initial value for Timer2
    while(TIM_GetCounter(TIM2)<36000); // Loop until desired delay
}
void Delay_ms(unsigned int time){
    while(time--){
        Delay_1ms();
    }
}

/********************************* END OF FILE ********************************/
/******************************************************************************/