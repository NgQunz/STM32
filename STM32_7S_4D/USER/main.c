// #include "stm32f10x.h"
// #include "stm32f10x_gpio.h"
// #include "stm32f10x_rcc.h"

// #define led_chuc GPIO_Pin_1
// #define led_dvi GPIO_Pin_0
// void Config(void);
// void Delay_ms(uint16_t _time);
// void led_Blink(void);
// uint8_t val[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
// GPIO_InitTypeDef GPIO;
// int n = 0, i = 0;
// int main()
// {
// 	Config();
// 	while (1)
// 	{
// 		led_Blink();
// 	}
// }

// void led_Blink(void)
// {
// 	// n = 0;
// 	// for (n; n <= 9999; n++)
// 	// {
// 	// 	i = 0;
// 	// 	for (i; i < 25; i++)
// 	// 	{
// 	GPIO_ResetBits(GPIOB, led_chuc);
// 	GPIOA->ODR = 0x90;
// 	Delay_ms(1);
// 	GPIO_SetBits(GPIOB, led_chuc);

// 	GPIO_ResetBits(GPIOB, led_dvi);
// 	GPIOA->ODR = 0x80;
// 	Delay_ms(1);
// 	GPIO_SetBits(GPIOB, led_dvi);
// 	Delay_ms(1000);
// 	// 	}
// 	// }
// }
// void Config(void)
// {
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
// 	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
// 	GPIO.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_0 | GPIO_Pin_4 |
// 					GPIO_Pin_5 | GPIO_Pin_6;
// 	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO);
// 	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
// 	GPIO.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
// 	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO);
// }

// void Delay_ms(uint16_t ms)
// {
// 	uint16_t i, j;
// 	for (i = 0; i < ms; i++)
// 	{
// 		for (j = 0; j < 0x2aff; j++)
// 			;
// 	}
// }
//#include "stm32f10x.h"		// Device header
//#include "stm32f10x_gpio.h" // Keil::Device:StdPeriph Drivers:GPIO
//#include "stm32f10x_rcc.h"	// Keil::Device:StdPeriph Drivers:RCC

//#define LED_DONVI GPIO_Pin_15
//#define LED_CHUC GPIO_Pin_14
//#define LED_TRAM GPIO_Pin_13
//#define LED_NGHIN GPIO_Pin_12

//unsigned int NUM[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

//void Delay_ms(uint16_t _time);
//void led_Init(void);
//void ledcontrol_Init(void);
//void led_Counter1(void);
//int main()
//{
//	led_Init();
//	ledcontrol_Init();
//	while (1)
//	{
//		led_Counter1();
//	}
//}

//void Delay_ms(uint16_t _time)
//{
//	uint16_t i, j;
//	for (i = 0; i < _time; i++)
//	{
//		for (j = 0; j < 7999; j++)
//			;
//	}
//}

//void led_Init(void)
//{
//	GPIO_InitTypeDef led_init;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//	led_init.GPIO_Mode = GPIO_Mode_Out_PP;
//	led_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |
//						GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//	led_init.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &led_init);
//	GPIOA->ODR = 0XFF;
//}

//void ledcontrol_Init(void)
//{
//	GPIO_InitTypeDef button_init;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	button_init.GPIO_Mode = GPIO_Mode_Out_PP;
//	button_init.GPIO_Pin = LED_NGHIN | LED_TRAM | LED_CHUC | LED_DONVI;
//	button_init.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &button_init);
//	GPIOB->ODR = 0xffff;
//}

//void led_Counter1(void)
//{
//	uint16_t i, j;
//	for (i = 0; i < 10000; i++)
//	{
//		for (j = 0; j < 24; j++)
//		{
//			/*quet led hang don vi*/
//			GPIO_ResetBits(GPIOB, LED_DONVI);
//			GPIOA->ODR = NUM[i % 10];
//			Delay_ms(10);
//			GPIO_SetBits(GPIOB, LED_DONVI);
//			// GPIOB->ODR = 0xffff;

//			/*quet led hang chuc vi*/
//			GPIO_ResetBits(GPIOB, LED_CHUC);
//			GPIOA->ODR = NUM[(i / 10) % 10];
//			Delay_ms(10);
//			GPIO_SetBits(GPIOB, LED_CHUC);
//			// GPIOB->ODR = 0xffff;
//			/*quet led hang tram*/
//			GPIO_ResetBits(GPIOB, LED_TRAM);
//			GPIOA->ODR = NUM[(i / 100) % 10];
//			Delay_ms(10);
//			GPIO_SetBits(GPIOB, LED_TRAM);

//			/*quet led hang nghin*/
//			GPIO_ResetBits(GPIOB, LED_NGHIN);
//			GPIOA->ODR = NUM[i / 1000];
//			Delay_ms(10);
//			GPIO_SetBits(GPIOB, LED_NGHIN);
//		}
//	}
//}
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define LED_DONVI GPIO_Pin_15
#define LED_CHUC GPIO_Pin_14
#define LED_TRAM GPIO_Pin_13

unsigned int NUM[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};


void Delay_ms(uint16_t _time);
void led_Init(void);
void ledcontrol_Init(void);
void led_Counter1(void);

int main()
{
	led_Init();
	ledcontrol_Init();
	while (1)
	{

		led_Counter1();
	}
}

void Delay_ms(uint16_t _time)
{
	uint16_t i, j;
	for (i = 0; i < _time; i++)
	{
		for (j = 0; j < 7999; j++)
			;
	}
}

void led_Init(void)
{
	GPIO_InitTypeDef led_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	led_init.GPIO_Mode = GPIO_Mode_Out_PP;
	led_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
						GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	led_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &led_init);
	GPIOA->ODR = 0xFF;
}

void ledcontrol_Init(void)
{
	GPIO_InitTypeDef led_control;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	led_control.GPIO_Mode = GPIO_Mode_Out_PP;
	led_control.GPIO_Pin = LED_TRAM | LED_CHUC | LED_DONVI;
	led_control.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &led_control);
	GPIOB->ODR = 0xFFFF;
}

void led_Counter1(void)
{
	uint16_t i;
	uint16_t elapsed = 0;
	while (1)
	{
			i = 255;
			
			while (elapsed < 1000) // hi?n th? s? trong 1000ms
			{
				// H�ng don v?
				GPIO_ResetBits(GPIOB, LED_DONVI);
				GPIOA->ODR = NUM[i % 10];
				Delay_ms(5);
				GPIO_SetBits(GPIOB, LED_DONVI);

				// H�ng ch?c
				GPIO_ResetBits(GPIOB, LED_CHUC);
				GPIOA->ODR = NUM[(i / 10) % 10];
				Delay_ms(5);
				GPIO_SetBits(GPIOB, LED_CHUC);

				// H�ng tram
				GPIO_ResetBits(GPIOB, LED_TRAM);
				GPIOA->ODR = NUM[i / 100];
				Delay_ms(5);
				GPIO_SetBits(GPIOB, LED_TRAM);

				// T?ng 1 l?n qu�t: ~15ms
				elapsed += 15;
			}
		}

}

