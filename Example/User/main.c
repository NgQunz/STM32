//#include "stm32f10x.h"
//#include "stm32f10x_gpio.h"
//void GPIO_Configure()
//{
//	/*B1: Enable Port A -> Cho phep cac chan portA duoc
//	Su dung*/
//	RCC -> APB2ENR |= 0x00000004;
//	/*B2: Reset chan pin PA5 ve 0 truoc khi ma thuc hien
//	Set gia tri cau hinh*/
//	GPIOA -> CRL   &= 0xFF0FFFFF;
//	/*B3: Configurion pin PA5: 
//	MODE5[1:0]: 11 Speec 50MHz
//	CNF5[1:0] : 00 General pupose Push-pull*/
//	GPIOA -> CRL   |= 0x00300000;
//}

//void GPIO_ConfiguretionLibrary()
//{
//	/*Buoc1: Enable port A cho phep Cac chan pin port A hoat dong*/
//	RCC_APB2PeriphClockCmd(RCC_APB2ENR_IOPAEN, ENABLE);
//	/*Buoc2: Config Pin MODE OUTPUT, CLOCK 50MHz*/
//  GPIO_InitTypeDef gpio;
//  gpio.GPIO_Mode  = GPIO_Mode_Out_PP;
//	gpio.GPIO_Pin   = GPIO_Pin_5;
//	gpio.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &gpio);
//}


//void delay(int time){
//	for(int i = 0; i< time; i++){
//		for(int j = 0; j< 0x2AF; j++);
//	}
//}

//int main()
//{
//	/*Initialization GPIOA, PA5, 50MHz, Output.*/
//	GPIO_ConfiguretionLibrary();
//	while(1)
//	{
////		/*Set Led PA5 len 1*/
////		GPIOA -> ODR |= 0x00000020;
////		delay(1000);
////		/*Reset Led PA5 ve 0*/
////		GPIOA -> ODR &= ~(0x00000020);
////		delay(1000);
//		GPIO_SetBits(GPIOA, GPIO_Pin_5);
//		delay(100);
//		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
//		delay(100);
//	}
//}
//#include "gpio.h"
//#include "timer2_delay.h"

//int main(){
//	timer_Init();
//	led_Init();
//	GPIO_Config();
//	while(1){
//		led_Blink();
//	}
//}
//#include "stm32f10x.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
////void GPIO_Config_MultiplePin()
////{

////	GPIO_InitTypeDef GPIO;
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
////	
////	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
////	GPIO.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |
////									GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0;
////	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_Init(GPIOA,&GPIO);
////}
//void GPIO_Config_MultiplePin()
//{
//	/*Buoc1: Enable port A cho phep Cac chan pin port A hoat dong*/
//	RCC_APB2PeriphClockCmd(RCC_APB2ENR_IOPAEN, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2ENR_IOPBEN, ENABLE);
//	/*Buoc2: Config Pin MODE OUTPUT, CLOCK 50MHz*/
//  GPIO_InitTypeDef GPIO_Structure_Pin;
//  GPIO_Structure_Pin.GPIO_Mode  = GPIO_Mode_Out_PP;
//	GPIO_Structure_Pin.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | 
//	GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_Structure_Pin.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_Structure_Pin);
//	
//	GPIO_InitTypeDef GPIP_Structure_Pin_PortB;
//	GPIO_Structure_Pin.GPIO_Mode  = GPIO_Mode_Out_PP;
//	GPIO_Structure_Pin.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | 
//	GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	GPIO_Structure_Pin.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_Structure_Pin);
//}
//int sangdan[8] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
//int fly_arr[9] = { 0x00, 0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18, 0x00};	

//uint16_t sangDanPortA[8] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
//uint32_t sangDanPortB[8] = {0xFE00, 0xFC00, 0xF800, 0x7000, 0x3000, 0x1000, 0x0000};

//	
//void delay(int time){
//	int i,j;
//	for( i = 0; i< time; i++){
//		for( j = 0; j< 0x2AF; j++);
//	}
//}
//void Chan_le()
//{
//	GPIOA -> ODR = 0x55;
//	delay(500);
//	GPIOA -> ODR = 0xAA;
//	delay(500);
//}
//int main()
//{
//	int i=0;
//	/*Initialization GPIOA, PA0->PA7, 50MHz, Output pushpull*/
//	GPIO_Config_MultiplePin();
//	while(1)
//	{
//		 for (i = 0; i < 9; i++)
//        {
////            GPIOA->ODR = fly_arr[i];
////            delay(500);
//					GPIOA -> ODR = sangDanPortA[i];
//					delay(1000);
//					GPIOB -> ODR = sangDanPortB[i];
//					delay(1000);
//        }
//        
////        // Hi?u ?ng t? ngoài vào trong
////        for (i = 8; i >= 0; i--)
////        {
////            GPIOA->ODR = fly_arr[i];
////            delay(500);
////        }
//		// Chan_le();
//	}
//}
//#include "stm32f10x.h"
//#include "stm32f10x_gpio.h"

//int sangdan[8] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};

//void GPIO_Configure_Led()
//{
//	/*B1: Cap Clock PortA. PA7, Output Push-pull, Speed: 50MHz.*/
//	RCC-> APB2ENR |= 0x00000004;
//	/*B2: Configuration: CFN7[1:0] = 00 Output push pull, MODE7[1:0] = 11 (50MHz)*/
//	GPIOA -> CRL  |= 0x30000000;
//}

//void GPIO_Configure_Button()
//{
//	/*B1: Cap Clock portB (Cho phep cac Pin port B hoat dong)*/
//	RCC -> APB2ENR |= 0x00000008;
//	/*B2: Configuration: CNF0[1:0] = 10 (input with Pull up/Pull down), MODE0[1:0] = 00*/
//	GPIOB -> CRL  |= 0x00000008;
//	/*B3: Set Pin PB0 GPIOB -> ODR = 0 -> Pull Down*/
//	GPIOA -> ODR  = 0x01;
//}
//void delay(int time)
//{
//	for(int i = 0; i < time; i++)
//	{
//		for(int j = 0; j < 0x2AFF; j++);
//	}
//}
//void SetLedPA7()
//{
//		GPIOA -> ODR &= ~(0x80);
//}
//void ResetLedPA7()
//{
//		GPIOA -> ODR |= 0x80;
//}
//int main()
//{
//	GPIO_Configure_Led();
//	GPIO_Configure_Button();
//	int i=0;
//	while(1)
//	{
//		if(((GPIOB -> IDR) & 0x00000001) == 0)
//		{
//			for (i = 0; i < 8; i++)
//        {
//					GPIOA -> ODR = sangdan[i];
//					delay(500);
//        }
//		}
//	}
//}

//#include "stm32f10x.h"

//int sangdan[8] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
//int tatdan[8]  = {0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80};

//void GPIO_Config_MultiplePin()
//{
//    GPIO_InitTypeDef GPIO;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
//                    GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO);
//}

//void GPIO_Configure_Button()
//{
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

//    GPIO_InitTypeDef GPIO;
//    GPIO.GPIO_Mode = GPIO_Mode_IPU;  
//    GPIO.GPIO_Pin = GPIO_Pin_2;      
//    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOB, &GPIO);
//}

//void delay(int time)
//{
//    for (int i = 0; i < time; i++)
//    {
//        for (int j = 0; j < 0x2AFF; j++);
//    }
//}

//int main()
//{
//    GPIO_Config_MultiplePin();
//    GPIO_Configure_Button();
//    int i = 0;

//    while (1)
//    {
//        while ((GPIOB->IDR & GPIO_Pin_2) == 0)
//        {
//            for (i = 0; i < 8; i++)  
//            {
//                GPIOA->ODR = sangdan[i];
//                delay(50);
//            }
//            for (i = 0; i < 8; i++)  
//            {
//                GPIOA->ODR = tatdan[i];
//                delay(50);
//            }
//        }
//    }
//}
//#include "stm32f10x.h"
//#include "stm32f10x_gpio.h"

//uint8_t segmentMap[10] = {
//  0xC0, // 0
//  0xF9, // 1
//  0xA4, // 2
//  0xB0, // 3
//  0x99, // 4
//  0x92, // 5
//  0x82, // 6
//  0xF8, // 7
//  0x80, // 8
//  0x90  // 9
//};

//void GPIO_Config_7Seg_Pin()
//{
//    GPIO_InitTypeDef GPIO;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
//                    GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 ;
//    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO);
//	
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
//                    GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 ;
//    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO);
//		
//}

//void delay(int time)
//{
//    for (int i = 0; i < time; i++)
//    {
//        for (int j = 0; j < 0x2AFF; j++);
//    }
//}

//void displayNumber(uint8_t num)
//{
//    uint8_t value = segmentMap[num];

//    GPIO_WriteBit(GPIOA, GPIO_Pin_0, (value & 0x01) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_1, (value & 0x02) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_2, (value & 0x04) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_3, (value & 0x08) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (value & 0x10) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_5, (value & 0x20) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_6, (value & 0x40) ? Bit_SET : Bit_RESET);
//}

//// Hàm ki?m tra s? nguyên t?
//int isPrime(int num)
//{
//    if (num < 2) return 0;  
//    for (int i = 2; i * i <= num; i++)
//    {
//        if (num % i == 0) return 0; 
//    }
//    return 1;
//}

//int main()
//{
//    GPIO_Config_7Seg_Pin();

//    while (1)
//    {
//        for (int i = 0; i < 10; i++)
//        {
//            if (isPrime(i)) 
//            {
//                displayNumber(i);
//                delay(5);
//            }
//        }
//    }
//}

//#include "stm32f10x.h"
//#include "stm32f10x_gpio.h"


//uint8_t segmentMap[10] = {
//    0xC0, // 0
//    0xF9, // 1
//    0xA4, // 2
//    0xB0, // 3
//    0x99, // 4
//    0x92, // 5
//    0x82, // 6
//    0xF8, // 7
//    0x80, // 8
//    0x90  // 9
//};

//void GPIO_Config()
//{
//    GPIO_InitTypeDef GPIO;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
//    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
//                    GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
//    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO);
//    GPIO.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
//    GPIO_Init(GPIOB, &GPIO);
//}

//void delay(int time)
//{
//    for (int i = 0; i < time; i++)
//    {
//        for (int j = 0; j < 0x1FFF; j++);
//    }
//}

//void displayDigit(uint8_t digit, uint8_t num)
//{
//    uint8_t value = segmentMap[num];

//    GPIO_WriteBit(GPIOA, GPIO_Pin_0, (value & 0x01) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_1, (value & 0x02) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_2, (value & 0x04) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_3, (value & 0x08) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (value & 0x10) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_5, (value & 0x20) ? Bit_SET : Bit_RESET);
//    GPIO_WriteBit(GPIOA, GPIO_Pin_6, (value & 0x40) ? Bit_SET : Bit_RESET);

//    if (digit == 0)
//    {
//        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
//        GPIO_SetBits(GPIOB, GPIO_Pin_1);
//    }
//    else
//    {
//        GPIO_ResetBits(GPIOB, GPIO_Pin_1);
//        GPIO_SetBits(GPIOB, GPIO_Pin_0);
//    }
//}

//int isPrime(int num)
//{
//    if (num < 2) return 0;
//    for (int i = 2; i * i <= num; i++)
//    {
//        if (num % i == 0) return 0;
//    }
//    return 1;
//}
//int isPerfectSquare(int num)
//{
//    for (int i = 0; i * i <= num; i++)
//    {
//        if (i * i == num) return 1;
//    }
//    return 0;
//}
//void displayNumber(int num)
//{
//    uint8_t tens = num / 10;
//    uint8_t ones = num % 10;

//    displayDigit(1, tens);
//		delay(2);

//    displayDigit(0, ones);
//delay(2);
//}

//int main()
//{
//    GPIO_Config();

//    while (1)
//    {
//        for (int i = 0; i < 100; i++)
//        {
//            if (isPerfectSquare(i))
//            {
//    
//                    displayNumber(i);
//										delay(2);
//            }
//        }
//    }
//}

//#include "stm32f10x.h"
//#include "stm32f10x_gpio.h"
//#include "stdio.h"
//#include "string.h"

//void Clock_Config(void);
//void UART_Configuration(void);
//void UART_SendChar(USART_TypeDef *USARTx, char data);
//void UART_SendString(USART_TypeDef *USARTx, const char *Str);
//void Delay_ms(uint32_t ms);
//char UART_ReceiveChar(USART_TypeDef *USARTx);
//void LED_Blink(uint8_t times);

//struct __FILE {
//    int dummy;
//};
//FILE __stdout;

//int fputc(int ch, FILE *f){
//    /* Send your custom byte */
//    USART_SendData(USART1, ch);
//    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){};
//    /* If everything is OK, you have to return character written */
//    return ch;
//}

//// Cau hinh clock su dung HSI 8MHz
//void Clock_Config(void) {
//    RCC_DeInit();
//    RCC_HCLKConfig(RCC_SYSCLK_Div1);
//    RCC_PCLK2Config(RCC_HCLK_Div1);
//    RCC_PCLK1Config(RCC_HCLK_Div1);
//    RCC_HSICmd(ENABLE);
//    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET) {}
//    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
//    while (RCC_GetSYSCLKSource() != 0x00) {}
//}

//void Delay_ms(uint32_t ms) {
//    for (uint32_t i = 0; i < ms * 1000; i++) {
//        __NOP();
//    }
//}

//// Ham gui 1 ky tu qua UART
//void UART_SendChar(USART_TypeDef *USARTx, char data) {
//    USART_SendData(USARTx, data);
//    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET) {}
//}

//// Ham gui chuoi ky tu qua UART
//void UART_SendString(USART_TypeDef *USARTx, const char *Str) {
//    while (*Str) {
//        UART_SendChar(USARTx, *Str++);
//    }
//}

//// Ham nhan 1 ky tu tu UART
//char UART_ReceiveChar(USART_TypeDef *USARTx) {
//    while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET) {}
//    return (USART_ReceiveData(USARTx)) & 0xFF;
//}

//void LED_Blink(uint8_t times) {
//    for (uint8_t i = 0; i < times; i++) {
//        GPIO_SetBits(GPIOA, GPIO_Pin_5);
//        Delay_ms(200);
//        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
//        Delay_ms(200);
//    }
//}

//// Cau hinh UART2, PA2 -> TX, PA3 -> RX
//void UART_Configuration(void) {
//    GPIO_InitTypeDef GPIO_InitStructure;
//    USART_InitTypeDef USART_InitStructure;

//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

//    // PA2 (TX)
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    // PA3 (RX)
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    // PA5 (LED)
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    // Cau hinh UART2
//    USART_InitStructure.USART_BaudRate = 9600;
//    USART_InitStructure.USART_WordLength = USART_WordLength_9b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//    USART_Init(USART2, &USART_InitStructure);

//    USART_Cmd(USART2, ENABLE);
//}
//int main(void) {
//    Clock_Config();
//    SystemCoreClockUpdate();
//    UART_Configuration();

//    char buffer[10] = {0};
//    int index = 0;

//    UART_SendString(USART2, "NguyenBaHieu-B22DCDT113\r\n> ");

//    while (1) {
//        if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET) {
//            char received = UART_ReceiveChar(USART2);

//            if (received == '\r' || received == '\n') {
//                buffer[index] = '\0'; 

//                if (index > 0) {
//                    // Chuyen doi chuoi thanh chu hoa de khong phan biet ON/off
//                    for (int i = 0; buffer[i]; i++) {
//                        if (buffer[i] >= 'a' && buffer[i] <= 'z') {
//                            buffer[i] -= 32; 
//                        }
//                    }

//                    if (strcmp(buffer, "ON") == 0) {
//                        LED_Blink(2);
//                        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
//                        UART_SendString(USART2, "Da bat LED!\r\n");
//                    } else if (strcmp(buffer, "OFF") == 0) {
//                        GPIO_SetBits(GPIOA, GPIO_Pin_5);
//                        UART_SendString(USART2, "Da tat LED!\r\n");
//                    } else {
//                        UART_SendString(USART2, "Lenh sai! Dung ON hoac OFF\r\n");
//                    }
//                }

//                index = 0;
//                memset(buffer, 0, sizeof(buffer));
//                UART_SendString(USART2, "\r\n> "); 
//            } 
//            else if (index < sizeof(buffer) - 1) { 
//                buffer[index++] = received;
//                UART_SendChar(USART2, received);
//            }
//        }
//    }
//}
#include "stm32f10x.h"

#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "stm32f10x.h"     
static volatile uint32_t counter_ms = 0; 
volatile uint32_t msTicks = 0;

void SysTick_Handler(void)
{
    msTicks++;
}

void delay_ms(uint32_t ms)
{
    uint32_t start = msTicks;
    while ((msTicks - start) < ms);
}

void SysTick_Config_ms(void)
{
    SysTick_Config(SystemCoreClock / 1000); // Ng?t m?i 1ms (v?i HCLK = 72MHz)
}

void GPIO_Config(void){
	GPIO_InitTypeDef GPIO;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |
									GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_Init(GPIOA,&GPIO);
	GPIO_Init(GPIOC,&GPIO);
 }

int main(void)
{
    GPIO_Config();     
    SysTick_Config_ms();   
		
    while (1)
    {
        GPIOC->ODR ^= GPIO_ODR_ODR13; 
        delay_ms(1000);               
    }
}

