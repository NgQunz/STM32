#include "GPIO.h"

void Config(void);
void timer_Init(void);
void Delay_1ms(void);
void Delay_ms(unsigned int time);
void led_Blink(void);
int main(){
	timer_Init();
	Config();
	while(1){
		led_Blink();
	}
}
