#ifndef __DELAY_H
#define __DELAY_H
#include <stdint.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_tim.h>

#define TIMER TIM4

void Delay_Init(void);
void Delay_ms(uint16_t time);
void Delay_s(uint16_t time);

#endif
