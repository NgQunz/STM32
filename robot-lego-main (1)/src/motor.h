#ifndef	__MOTOR_H
#define	__MOTOR_H

#ifdef __cplusplus
	extern "C"{
#endif

#include "stm32f10x.h"     
#include "stm32f10x_rcc.h"  
#include "stm32f10x_gpio.h" 
#include "pwm.h"

/* Motor 1 */
#define MOTOR_1			1
/* Motor 2 */
#define MOTOR_2			2		

#define MOTOR_MAX	80
#define MOTOR_MIN	4

void Motor_Init(void);
void Motor_SetForward(uint8_t motor, uint8_t level);
void Motor_SetBackward(uint8_t motor, uint8_t level);
void Motor_SetStopping(uint8_t motor);

#ifdef __cplusplus
}
#endif

#endif



/***********************************************/
