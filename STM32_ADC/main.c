#include "UART.h"
#include "ADC.h"
#include "TIMER2.h"
int value_adc;
void init(void)
{
	timer_Init();
	USART_config();
	ADC_Config();
	GPIO_Config_ADC0();
	GPIO_Config_TX_RX();
	led_Init();
}
int main(void)
{ 
	init();
	while (1)
	{
		UARTPrintf_Number(100000);
		value_adc=  ADCx_Read();
		UARTPrintf_Number(value_adc);
		Delay_ms(1000);
	}
}

