#include "stm32f10x.h"
#include "Delay.h"
#include "LCD.h"
#include "MQ2.h"
#include "Speaker.h"
#include "flash.h"

uint32_t elapsed_ms = 0;
void LED_Init(void) {
	GPIO_InitTypeDef GPIO;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |
									GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO);
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	//GPIO_Init(GPIOC,&GPIO);
 }
void LED_Red_Blink(void) {

	GPIO_SetBits(GPIOB, GPIO_Pin_2); 
	delay_ms(500);
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	delay_ms(500);
}

// Cau hinh dong ho he thong
void SystemClock_Config(void) {
    RCC_HSEConfig(RCC_HSE_ON);
    while (!RCC_GetFlagStatus(RCC_FLAG_HSERDY));
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while (!RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  // AHB = 72 MHz
    RCC_PCLK1Config(RCC_HCLK_Div2);   // APB1 = 36 MHz
    RCC_PCLK2Config(RCC_HCLK_Div1);   // APB2 = 72 MHz
}
void Display_Saved_PPM(void) {
    uint32_t saved_ppm = Flash_ReadValue(FLASH_SAVE_ADDR);

    LCD_SetCursor(1,9);            // Di chuy?n con tr? v? dòng 2
    LCD_PrintNumber(saved_ppm);
    LCD_Print(" ppm           ");     // Xóa ký t? du n?u có
	
}

int main(void) {
	LED_Init();
    SystemClock_Config(); // Khoi tao dong ho he thong
    I2C_Init_Custom();    // Khoi tao I2C
    LCD_Init();           // Khoi tao LCD
    MQ2_Init();           // Khoi tao cam bien MQ2 (ADC)
    Speaker_Init();       // Khoi tao coi
		
    // Hien thi thong diep khoi dong
    LCD_Print("Canh bao khi gas ");
    delay_ms(2000);
    LCD_SendCommand(0x01); // Xoa man hinh
    delay_ms(2);

    while (1) {
    uint32_t ppm = MQ2_Read_ppm();
		GPIO_SetBits(GPIOB, GPIO_Pin_2);
    LCD_SetCursor(0,0);
    LCD_Print("Gas: ");
    LCD_PrintNumber(ppm);
    LCD_Print(" ppm    ");
		Display_Saved_PPM();
    if (ppm > 200) {
        LCD_SetCursor(1,0);
        LCD_Print("Nguy hiem");
        //Speaker_On();
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); // Tat led xanh
				LED_Red_Blink();	// Nhap nhay led do
//    } else if (ppm > 150) {
//        LCD_SetCursor(1,0);
//        LCD_Print("Bao dong ");
//        Speaker_Off();
			
    } else {
        LCD_SetCursor(1,0);
        LCD_Print("An toan  ");
        Speaker_Off();
				GPIO_SetBits(GPIOB, GPIO_Pin_0); // Tat led do
				GPIO_ResetBits(GPIOB, GPIO_Pin_2); // Bat led xanh 
    }

    elapsed_ms += 500;

    if (elapsed_ms >= 10000) {
        Flash_SaveValue(FLASH_SAVE_ADDR, ppm);
        elapsed_ms = 0;
    }

    delay_ms(500);  // Delay c? d?nh 500 ms
}

}
