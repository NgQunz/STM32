#include "stm32f10x.h"  // Device header

void delay(uint32_t time);
void GPIO_Configuration(void);

int main(void)
{
    GPIO_Configuration();  // Configure GPIO
    GPIOC->ODR |= GPIO_Pin_13;
		GPIOC->ODR &= ~GPIO_Pin_13;
    while(1)
    {
        // Check if button is pressed (active low)
        if ((GPIOA->IDR & GPIO_Pin_8))  // Button pressed (input low)
        {
            GPIOC->ODR |= GPIO_Pin_13;  // Toggle LED

        }
				else if ((GPIOC->IDR & GPIO_Pin_14))
				{
					GPIOC->ODR &= ~GPIO_Pin_13;
				}
    }
}

void delay(uint32_t time)
{
    while(time-- > 0)  // Correct comparison: > 0
    {
        for(int i = 0; i < 8000; i++)  // Rough 1ms delay per iteration
        {
            __NOP();  // Do nothing (No Operation)
        }
    }
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef gpio;
    
    // Enable clock for GPIOC (Port C)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    // Configure PC13 as output (Push-Pull, 50MHz)
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio);  // Initialize GPIOC with the settings
    
    // Enable clock for GPIOB (Port B)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // Configure PB9 as input with pull-up (for button)
    gpio.GPIO_Mode = GPIO_Mode_IPU;  // Input with Pull-up
    gpio.GPIO_Pin = GPIO_Pin_14;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio);  // Initialize GPIOB with the settings
	gpio.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &gpio);
}
