/*
  ******************************************************************************
  * @file		uart.h                                                              *
  * @author	Nguyen Minh Quan                                                *
  * @date		27/03/2024    
	* @ver 1.0                                                       *
  ******************************************************************************
*/
#include "uart.h"

void USART_config (void){
	USART_InitTypeDef uart;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	uart.USART_BaudRate = 9600;
	uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	uart.USART_Parity = USART_Parity_No ;
	uart.USART_StopBits = USART_StopBits_1 ;
	uart.USART_WordLength = USART_WordLength_8b ;
	USART_Init ( USART1, &uart);
	USART_Cmd (USART1, ENABLE);
}
void GPIO_Config_TX_RX(){
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpio.GPIO_Pin = GPIO_Pin_9;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_10;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);
}

void uart_SendStr(char *str){
	while(*str != NULL){
		uart_SendChar(*str++);		
	}
}
void uart_SendChar(char _chr){
	USART_SendData(USART1,_chr);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}
void uart_Receive_data()
{
	char temp;
	temp= USART_ReceiveData(USART1);
	if (temp == 'B') GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	else if(temp== 'T') GPIO_SetBits(GPIOC, GPIO_Pin_13);
}
void UARTPrintf_Number(long number) {
  char str[MAX];  // Ð? l?n d? luu s? nguyên có d?u âm
  int num_digits = 0,i,j;
  int is_negative = 0;
	long temp = number;
  if (number < 0) {
    is_negative = 1;
    number = -number;  // Chuy?n s? âm thành duong d? x? lý
  }
  
  while (temp > 0) {
    str[num_digits] = '0' + (temp % 10);
    temp = temp / 10;
    num_digits++;
  }

  if (number == 0) {
    str[num_digits++] = '0';
  }
	j = num_digits - 1;
  for (i = 0; i < j; i++) {
    char temp_char = str[i];
    str[i] = str[j];
    str[j] = temp_char;
		j--;
  }

  if (is_negative) {
    for (i = num_digits; i >= 0; i--) {
      str[i + 1] = str[i];
    }
    str[0] = '-';
    num_digits++;
  }

  str[num_digits] = '\0';  // K?t thúc chu?i b?ng NULL

 // char *ch = str;
	uart_SendStr(str);
	uart_SendStr("\n");
}


/********************************* END OF FILE ********************************/
/******************************************************************************/