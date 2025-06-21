#ifndef _MQ2_H_
#define _MQ2_H_

#include "stm32f10x.h"

// Khai báo hàm cam bien MQ2
void MQ2_Init(void);
uint32_t MQ2_Read_ppm(void);

#endif

