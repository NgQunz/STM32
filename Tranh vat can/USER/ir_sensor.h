#ifndef __IR_SENSOR__
#define __IR_SENSOR__
#ifdef __cplusplus
    extern "C" {
#endif

#include "define.h"
#include "kalman_filter.h"
			
typedef enum
{
	LED_CHANNEL_R2 = 0x04,
	LED_CHANNEL_R1,
	LED_CHANNEL_R0,
	LED_CHANNEL_L0,
	LED_CHANNEL_L1,
	LED_CHANNEL_L2,
	
}ledChannel_E;

typedef struct
{
	KalmanFilter_InitTypeDef KF_Infrared;
	float raw_value;
	float value;
}Value_InitTypeDef;
			
extern Value_InitTypeDef IRSensor[6]; 
			
void IRSensor_Init(void);
float Read_One_Sensor(uint8_t chnl);
void Read_All_Sensors(void);
void TurnOn_Transmitter(uint16_t GPIO_Pin);
void TurnOff_Transmitter(uint16_t GPIO_Pin);

#ifdef __cplusplus
    }
#endif
#endif
