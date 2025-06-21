//#include "gpio.h"
#include "timer2_delay.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void GPIO_Config(void){
    GPIO_InitTypeDef GPIO;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // B?t xung cho GPIOA

    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO.GPIO_Pin = GPIO_Pin_5;  // S? d?ng PA5
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO);
}

void led_Blink(void){
    GPIO_ResetBits(GPIOB, GPIO_Pin_5); // LED ON (PA5 LOW)
    Delay_ms(500);
    GPIO_SetBits(GPIOB, GPIO_Pin_5);   // LED OFF (PA5 HIGH)
    Delay_ms(500);
}

int main(){
    timer_Init();
    GPIO_Config();
    while(1){
        led_Blink();
    }
}


//#include "stm32f10x.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//void GPIO_Config_MultiplePin()
//{

//	GPIO_InitTypeDef GPIO;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
//	
//	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |
//									GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0;
//	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO);
//}
//int sangdan[8] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
//void delay(int time){
//	int i,j;
//	for( i = 0; i< time; i++){
//		for( j = 0; j< 0x2AF; j++);
//	}
//}
//int main()
//{
//	int i=0;
//	/*Initialization GPIOA, PA0->PA7, 50MHz, Output pushpull*/
//	GPIO_Config_MultiplePin();
//	while(1)
//	{
//		 for(i = 0; i < 8; i++)
//		 {
//			 GPIOA -> ODR = sangdan[i];
//			 delay(100);
//		 }
//		 for(i = 7; i >= 0; i--)
//		 {
//			 GPIOA -> ODR = sangdan[i];
//			 delay(100);
//		 }
//	}
//}
