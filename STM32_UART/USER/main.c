#include "uart.h"
#include "timer2_delay.h"

int main(){
	//char arr[MAX]= "kt vxl\n";
	long x= 10000000;
	timer_Init();
	USART_config();
	led_Init();
	GPIO_Config_TX_RX();
	while(1){
		UARTPrintf_Number(x);
		
		Delay_ms(1000);
	}
}