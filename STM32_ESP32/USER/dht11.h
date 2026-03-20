#ifndef __DHT11__
#define __DHT11__

#include "stm32f10x.h"
#include "tim2.h"

extern int16_t g_temp;  // Nhiet do nguyen (do C)
extern int16_t g_hum;   // Do am nguyen (%)

void DHT11_Init(void);
void DHT11_Read(void);

#endif