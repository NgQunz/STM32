/*
  ******************************************************************************
  * @file		LED_MATRIX.h                                                             *
  * @author	Nguyen Minh Quan                                                 *
  * @date		28/2/2024
	* @ver 1.0
  ******************************************************************************
*/
	
#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
	 
extern unsigned char cot[];
extern unsigned int hang[];
	 
void led_Matrix_Init(void);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/