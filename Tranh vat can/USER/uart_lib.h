/*
	********************************************************************************************
	*@file				uart_lib.h																													*
	*@author			Vu Quang Luong																								*
	*@date				27/04/2023																										*
	********************************************************************************************
*/

#ifndef __USART__
#define __USART__

#ifdef __cplusplus
	extern "C"{
#endif

#include "define.h"
#include "stdio.h"
		
uint8_t* Recev_Str_Arr(void);
void Reset_Flag(void);

void USART1_Init(uint32_t baud_rates);												/* Khoi tao USART1				*/
void USART2_Init(uint32_t baud_rates);
void USART1_Send_Char(uint16_t _char);												/* Truyen mot ky tu				*/
void USART1_Send_String(uint8_t *string);											/* Truyen mot chuoi				*/
void USART1_Send_Number(int32_t number);											/* Truyen mot so					*/
uint8_t Compare_String(int8_t *string);												/* So sanh chuoi					*/
uint8_t USART1_Check_Flag(void);															/* Check co								*/
void USART1_Send_Received_String(void);												/* In chuoi nhan duoc			*/

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ***********************************************/
/*********************************************************************************************/



