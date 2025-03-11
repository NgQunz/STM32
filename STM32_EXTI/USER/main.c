#include "stm32f10x.h"               
#include "stm32f10x_gpio.h"       
#include "stm32f10x_rcc.h"             
#include "stm32f10x_exti.h"             
#include "timer2_delay.h"

void EXTI15_10_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void Led_Init(void);
void button_Init(void);
void exti_Init(void);
void nvic_Init(void);

void Led_Init(void){
	
	GPIO_InitTypeDef led_init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	led_init.GPIO_Mode = GPIO_Mode_Out_PP;
	led_init.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|
											GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	led_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&led_init);
	GPIOB->ODR |= 0X00FF;	// Turn LEDs off
}

void button_Init(void){
	GPIO_InitTypeDef button_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	button_init.GPIO_Mode = GPIO_Mode_IPU;
	button_init.GPIO_Pin = GPIO_Pin_8;
	button_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&button_init);
	
	button_init.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOC,&button_init);
	exti_Init();
	nvic_Init();
}


void exti_Init(void){
	EXTI_InitTypeDef exti_init;
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource14);
	exti_init.EXTI_Line = EXTI_Line14 | EXTI_Line8;		// Chon pin
	exti_init.EXTI_Mode = EXTI_Mode_Interrupt;		// Chon mode la ngat
	exti_init.EXTI_Trigger=EXTI_Trigger_Falling;	// Chon suon ngat
	exti_init.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti_init);
	
}
void nvic_Init(void){
	NVIC_InitTypeDef NVIC_ST;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_ST.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_ST.NVIC_IRQChannelSubPriority=0;
	NVIC_ST.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_ST);
	
	NVIC_ST.NVIC_IRQChannel = EXTI9_5_IRQn ;
	NVIC_Init(&NVIC_ST);
}
void EXTI15_10_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line14)!=RESET){
		GPIOA->ODR &= 0xFF00;	//	Turn LEDs on
		EXTI_ClearITPendingBit(EXTI_Line14);
	}	
}


void EXTI9_5_IRQ_Handler(void)
{
	if( EXTI_GetITStatus(EXTI_Line8)!=RESET)
	{
		GPIOA->ODR |=0x00FF;
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}
int main(){
	Led_Init();
	led_Init();
	button_Init();
	    GPIOC->ODR |= GPIO_Pin_13;
		GPIOC->ODR &= ~GPIO_Pin_13;
	while(1){
		EXTI9_5_IRQHandler();
		EXTI15_10_IRQHandler();


	}
}
