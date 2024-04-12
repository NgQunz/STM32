#include "motor.h"

void Motor_Init(void){
	Pwm_Init();
	Motor_SetForward(MOTOR_1,0);
	Motor_SetForward(MOTOR_2,0);
}

void Motor_SetForward(uint8_t motor, uint8_t level){
	if(level < MOTOR_MIN)
		level = 0;
	if(level > MOTOR_MAX)
		level = MOTOR_MAX;
	switch(motor){
		case MOTOR_1:
			TIM2->CCR3 = 0;
			TIM2->CCR4 = TIM2_PERIOD*level/100;
			break;
		case MOTOR_2:
			TIM2->CCR1 = TIM2_PERIOD*level/100;
		  	TIM2->CCR2 = 0;
			break;
	}								
}

void Motor_SetBackward(uint8_t motor, uint8_t level){
	if(level < MOTOR_MIN)
		level = 0;
	if(level > MOTOR_MAX)
		level = MOTOR_MAX;
	switch(motor){
		case MOTOR_1:
			TIM2->CCR3 = TIM2_PERIOD*level/100;
			TIM2->CCR4 = 0;
			break;
		case MOTOR_2:
			TIM2->CCR1 = 0;
		  	TIM2->CCR2 = TIM2_PERIOD*level/100;
			break;
	}	
}

void Motor_SetStopping(uint8_t motor){
	switch(motor){
		case MOTOR_1:
			TIM2->CCR2 = 0;
			TIM2->CCR1 = 0;
			break;
		case MOTOR_2:
			TIM2->CCR3 = 0;
		  TIM2->CCR4 = 0;
			break;
	}	
}

