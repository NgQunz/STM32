#include "uart.h"
#include "timer2_delay.h"
void init(void)
{
	timer_Init();
	USART_config();
	led_Init();
	GPIO_Config_TX_RX();
}
int main(void)
{ 
	int i=0;
	init();
	while (1)
	{
//		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
//		UARTPrintf_Number(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13));
//		Delay_ms(500);
//		GPIO_SetBits(GPIOB, GPIO_Pin_13);
//		UARTPrintf_Number(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13));
//		Delay_ms(500);
		USART1_IRQHandler();
	}
}

