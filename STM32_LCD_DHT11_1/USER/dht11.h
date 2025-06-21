#ifndef __DHT11__
#define __DHT11__

#include "stm32f10x.h"                  // Device header
#include "tim2.h"
#include "i2c_lcd.h"
void DHT11_Init(void);
void DHT11_Read(void);

#endif