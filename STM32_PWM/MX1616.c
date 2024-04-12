/*
  ******************************************************************************
  * @file		stm32_gpio.h                                                              *
  * @author	Nguyen Minh Quan                                                *
  * @date		27/03/2024    
	* @ver 1.0                                                       *
  ******************************************************************************
*/
#include "MX1616.h"

void MX1616_Init(void){
    Timer_Init(); // 1 kHz 50%
		PWM_Init();
    MX1616_SetForward(0);
}

/* INAx = PWM, INBx = LOW */
void MX1616_SetForward(uint8_t level){
    TIM2->CCR2 = TIM2_period*level/100;
    TIM2->CCR1 = 0;
}

/* INAx = LOW, INBx = PWM */
void MX1616_SetBackward(uint8_t level){
    TIM2->CCR2 = 0;
    TIM2->CCR1 = TIM2_period*level/100;
}

/* INAx = HIGH, INBx = HIGH */
void MX1616_SetStopping(void){
    TIM2->CCR2 = TIM2_period;
    TIM2->CCR1 = TIM2_period;
}

/********************************* END OF FILE ********************************/
/******************************************************************************/