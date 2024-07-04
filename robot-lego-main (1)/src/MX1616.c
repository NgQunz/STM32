#include "MX1616.h"

void MX1616_Init(void){
    Pwm_Init();
    MX1616_SetForward(0);
}

/* INAx = PWM, INBx = LOW */
void MX1616_SetForward(uint8_t level){
    TIM2->CCR2 = TIM2_PERIOD*level/100;
    TIM2->CCR1 = 0;
}

/* INAx = LOW, INBx = PWM */
void MX1616_SetBackward(uint8_t level){
    TIM2->CCR2 = 0;
    TIM2->CCR1 = TIM2_PERIOD*level/100;
}

/* INAx = HIGH, INBx = HIGH */
void MX1616_SetStopping(void){
    TIM2->CCR2 = TIM2_PERIOD;
    TIM2->CCR1 = TIM2_PERIOD;
}
