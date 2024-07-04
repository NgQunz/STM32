/*
  ******************************************************************************
  * @file		LED_MATRIX.h                                                             *
  * @author	Nguyen Minh Quan                                                 *
  * @date		28/2/2024
	* @ver 1.0
  ******************************************************************************
*/
	
#ifndef __TIMER2_H__
#define __TIMER2_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"                  // Device header

void Timer_Init(void);
void Delay_1ms(void);
void Delay_ms(unsigned int time);
void Led_Init(void);
	 
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/