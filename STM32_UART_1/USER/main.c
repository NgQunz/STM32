#include "uart.h"
#include "timer2_delay.h"
void init(void)
{
	Timer_Init();
	UART_Config();
	//Led_Init();
	GPIO_Config_TX_RX();
}
int main(void)
{ 
	long x= 10000000;
	init();
	while (1)
	{
		//UART_Printf_Number(x);
		//Delay_ms(1000);
			UART_IRQHandler();
	}
}

