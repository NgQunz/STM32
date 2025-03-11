#include "ir_sensor.h"
#include "delay.h"

Value_InitTypeDef IRSensor[6]; 

void IRSensor_Init(void)
{
	int i;
	
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	// Config clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	// Receive led
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = REC_LED_R2 | REC_LED_R1 | REC_LED_R0 | REC_LED_L0;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = REC_LED_L1 | REC_LED_L2;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// Transmitter led
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = TRAN_LED_L2 | TRAN_LED_L1 | TRAN_LED_L0 | TRAN_LED_R0 | TRAN_LED_R1 | TRAN_LED_R2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TRAN_LED_PORT, &GPIO_InitStruct);
	
	// ADC
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStruct);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	// KalmanFilter Init
	for(i=0; i<6; i++) KalmanFilter_Init(&IRSensor[i].KF_Infrared, 1, 1, 0.01);
}

float Read_One_Sensor(uint8_t chnl)
{
	float value = 0;
	uint8_t channel = chnl;
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_71Cycles5); // set channel
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
	
	IRSensor[channel - LED_CHANNEL_R2].raw_value = ADC_GetConversionValue(ADC1);
	value = KalmanFilter_Update(&IRSensor[channel - LED_CHANNEL_R2].KF_Infrared, IRSensor[channel - LED_CHANNEL_R2].raw_value);
	IRSensor[channel - LED_CHANNEL_R2].value = value;
	
	return value;
}

void Read_All_Sensors(void)
{
	uint8_t count = LED_CHANNEL_R2;
	while(count <= LED_CHANNEL_L2) Read_One_Sensor(count++);
}

void TurnOn_Transmitter(uint16_t GPIO_Pin)
{
	TRAN_LED_PORT->BSRR = GPIO_Pin;
}

void TurnOff_Transmitter(uint16_t GPIO_Pin)
{
	TRAN_LED_PORT->BSRR = GPIO_Pin << 16;
}
