#include "motor.h"

void Motor_Init(void){
	Pwm_Init();
	Motor_SetForward(0);
	Motor_SetForward(0);
}

void Motor_SetForward( uint8_t level){
		TIM2->CCR1 = TIM2_PERIOD*level/100;
		TIM2->CCR2 = 0;				
}

void Motor_SetBackward(uint8_t level){
			TIM2->CCR1 = 0;
		  	TIM2->CCR2 = TIM2_PERIOD*level/100;
}

void Motor_SetStopping(uint8_t motor){
			TIM2->CCR2 = 0;
			TIM2->CCR1 = 0;	
}

