/*
  ******************************************************************************
  * @file		LED_MATRIX.h                                                             *
  * @author	Nguyen Minh Quan                                                 *
  * @date		28/2/2024
	* @ver 1.0
  ******************************************************************************
*/
	
#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "string.h"
#include "stdio.h"
	 
#define MAX 20

void GPIO_Config_TX_RX();
void USART_config(void);
void UART_SendStr(char *str);
void UART_SendChar(char _chr);
void UART_Receive_data();
void UART_Printf_Number(long number);
void UARTPrintf_IntNumber(int number);
void UARTPrintf_Str(char ch);
	 
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/