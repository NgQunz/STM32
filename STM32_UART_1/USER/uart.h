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
void led_Init(void);
	 
void UART_Send_Str(char *str);
void UART_Send_Char(char _chr);
void UART_Receive_Data();
void UART_Printf_Number(long number);
void UART_Printf_Str(char ch);
void UART_IRQHandler(void);
void UART_Printf_Float(double number, int decimalPlaces);

extern char arr[MAX];
extern char received_data[MAX];
extern int count,vtri_stt;
	 
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/