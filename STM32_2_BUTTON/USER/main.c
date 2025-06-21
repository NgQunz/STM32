#include "stm32f10x.h"
#include "button.h"
#include "tim2.h"
#include "uart.h"
extern uint16_t light;
int main(void)
{
		USART1_Init(9600);
    USART1_Send_String("Starting I2C LCD Address Scan...\r\n");
    Timer2_Init();      // Kh?i t?o Timer2 d? d�ng millis()
    GPIO_Config();      // C?u h�nh LED v� n�t nh?n
		
    while (1)
    {
			Run_button();
			 USART1_Send_String("Starting I2C LCD Address Scan...\r\n");
			Delay_ms(1000);
    }
}
