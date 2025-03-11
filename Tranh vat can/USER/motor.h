#ifndef __motor__
#define __motor__
#ifdef __cplusplus
extern "C" {
#endif
	
#include "define.h"

#define MOTOR_LEFT    1
#define MOTOR_RIGHT   2
	
extern int8_t max_speed;
extern int8_t min_speed;
	
void Motor_Init(void);
void Motor_Move(uint8_t motor, float level);
	
void EXTI0_IRQHandler(void);
void EXTI2_IRQHandler(void);

#ifdef __cplusplus
}
#endif
#endif
