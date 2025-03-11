#include "gpio.h"
#include "timer2_delay.h"

int main(){
	timer_Init();
	led_Init();
	GPIO_Config();
	while(1){
		led_Blink();
	}
}
	