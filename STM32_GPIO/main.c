#include "GPIO.h"
#include "TIMER2.h"

int main(){
	timer_Init();
	led_Init();
	Config();
	while(1){
		led_Blink();
	}
}
