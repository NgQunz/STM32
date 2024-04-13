/*
  ******************************************************************************
  * @file		stm32_gpio.h                                                              *
  * @author	Nguyen Minh Quan                                                *
  * @date		27/03/2024    
	* @ver 1.0                                                       *
  ******************************************************************************
*/
#include "adc.h"

void GPIO_Config_ADC0(void);
void ADC_Config(void);
int ADCx_Read(void);
int Map(int x, int in_min, int in_max, int out_min, int out_max);
int Temp();
// int value_adc;
uint8_t data = 10;
float value_adc1 = 0, sum_adc1 = 0, adc_tb = 0;
const double VCC = 3.3; 
const double R2 = 10000;
const double adc_resolution = 4095; 
const double A = 0.001129148;
const double B = 0.000234125;
const double C = 0.0000000876741; 
double t = 0; 


void GPIO_Config_ADC0(void){
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ADC_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	/* cho phep cam bien nhiet hoat dong */
	ADC_TempSensorVrefintCmd(ENABLE);
	/* Reset thanh ghi cablib  */
	ADC_ResetCalibration(ADC1);
	/* Cho thanh ghi cablib reset xong */
	while (ADC_GetResetCalibrationStatus(ADC1))
		;
	/* Khoi dong bo ADC */
	ADC_StartCalibration(ADC1);
	/* Cho trang thai cablib duoc bat */
	while (ADC_GetCalibrationStatus(ADC1))
		;
	/* Bat dau chuyen doi ADC */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
int ADCx_Read(void){
	int b = 0;
		for (b = 0; b < 10; b++)
		{
			value_adc1 = ADC_GetConversionValue(ADC1);
			sum_adc1 = sum_adc1 + value_adc1;
		}
		adc_tb = sum_adc1 / 10;
		sum_adc1 = 0;
		return adc_tb;
}

int Temp()
{
  double Vout, Rth, adc_value; 
  adc_value = ADC_GetConversionValue(ADC1);
  Vout = (adc_value * VCC) / adc_resolution;
  Rth = (VCC * R2 / Vout) - R2;
  t = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)),3))));  
  t = t - 273.15;
  return t;
}

int Map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/********************************* END OF FILE ********************************/
/******************************************************************************/