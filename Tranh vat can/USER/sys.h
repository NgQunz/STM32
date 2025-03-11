#ifndef __sys__
#define __sys__
#ifdef __cplusplus
extern "C" {
#endif
	
#include "define.h"
#include "math.h"
#include "delay.h"
#include "motor.h"
#include "uart_lib.h"
#include "MPU6050.h"
#include "ir_sensor.h"   
#include "kalman_filter.h" 	
	
typedef enum
{
	FALSE,
	TRUE
}Logic_State;

typedef struct
{
	float kp;
	float ki;
	float kd;
	float pid;
	float pre_pv;
	float error;
	float P;
	float I;
	float D;
	
}PID_InitTypeDef;

extern uint32_t  dt, current_time, previous_time;
extern uint8_t    rotate_flag;

float Get_yaw(uint8_t *reset);
void PID_Update(PID_InitTypeDef *PID, float pv);
void Rotate(float sp);
void AvoidObstacles(void);
void Sys_Init(void);

#ifdef __cplusplus
}
#endif
#endif
