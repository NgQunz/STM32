#include "sensor.h"

void Sensor_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitTypeDefStructure.GPIO_Pin = SENSOR_PIN1 | SENSOR_PIN2 | SENSOR_PIN3 | SENSOR_PIN4 | SENSOR_PIN5;
	GPIO_Init(SENSOR_PORT, &GPIO_InitTypeDefStructure);
}

uint8_t Sensor_Read(uint8_t pin){
	if(GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
		return SENSOR_ON;
	else
		return SENSOR_OFF;
}
