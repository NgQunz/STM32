/*
  ******************************************************************************
  * @file		uart.h                                                              *
  * @author	Nguyen Minh Quan                                                *
  * @date		27/03/2024    
	* @ver 1.0                                                       *
  ******************************************************************************
*/
#include "uart.h"

char arr[MAX];
char received_data[MAX];
int count=0,vtri_stt=0;
char temp_char;
void UART_Config (void){
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

void 	UART_Send_Str(char *str){
	while(*str != NULL){
		UART_Send_Char(*str++);		
	}
}
void UART_Send_Char(char _chr){
	USART_SendData(USART1,_chr);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}
void UART_Receive_Data(){
	char temp;
	temp= USART_ReceiveData(USART1);
	if (temp == 'B') GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	else if(temp== 'T') GPIO_SetBits(GPIOC, GPIO_Pin_13);
}
void UART_Printf_Number(long number) {
  char str[18];  // Luu so nguyen am
  int num_digits = 0,i,j;
  int is_negative = 0;
	long temp = number;
  if (number < 0) {
    is_negative = 1;
    number = -number;  // Chuyen so am thanh duong de xu ly
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

  str[num_digits] = '\0';  // Ket thuc chuoi bang NULL

	UART_Send_Str(str);
	UART_Send_Str("\n");
}


void UART_Printf_Float(double number, int decimalPlaces) {
  char str[10],temp_char; 
  int num_digits = 0,is_negative = 0,int_part,digit,i=0,j=0;
	int temp;
  double decimal_part;
  if (number < 0) {
    is_negative = 1;
    number = -number;
  }

  // Phan nguyên
  decimal_part = number - int_part;
	int_part = (int)number;
  // In phan nguyên
  temp = int_part;
  while (temp > 0) {
    str[num_digits] = '0' + (temp % 10);
    temp = temp / 10;
    num_digits++;
  }

  if (int_part == 0) {
    str[num_digits++] = '0';
  }

  // Dao nguoc chuoi so nguyên
  for (i = 0; i < j;i++) {
		j = num_digits - 1;
		j--;
    temp_char = str[i];
    str[i] = str[j];
    str[j] = temp_char;
  }

  // In dau thap phân
  str[num_digits++] = '.';

  // In phan thap phân
  for (i = 0; i < decimalPlaces; i++) {
    decimal_part *= 10;
    digit = (int)decimal_part;
    str[num_digits++] = '0' + digit;
    decimal_part -= digit;
  }

  str[num_digits] = '\0';  // Ket thúc chuoi bang NULL

  // Dat lai dau am neu can
  if (is_negative) {
    for (i = num_digits; i >= 0; i--) {
      str[i + 1] = str[i];
    }
    str[0] = '-';
    num_digits++;
  }
  UART_Send_Str(str);
	UART_Send_Str("\n");
}

void UART_IRQHandler(void){
	char received_char;
	if ( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		received_char= (char) USART_ReceiveData(USART1);
		if (received_char== '\n')
		{
			received_data[count-1]= '\0';
			count =0;
			vtri_stt=1;
		}
		else if (received_char== '\b')
		{
			if (count >0)
			{
				count--;
				received_data[count]= '\0';
			}
		}
		else 
		{
			received_data[count]=received_char;
			count++;
		}
	}
	UART_Send_Str(received_data);
	UART_Send_Str("\n");
}
void UARTPrintf_Int_Number(int number) {
  char str[10];  
  int num_digits = 0,i,j;
  int is_negative = 0;
	long temp = number;
  if (number < 0) {
    is_negative = 1;
    number = -number; 
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

  str[num_digits] = '\0'; 

	UART_Send_Str(str);
	UART_Send_Str("\n");
}
/********************************* END OF FILE ********************************/
/******************************************************************************/