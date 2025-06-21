#include "stm32f10x.h"
#include "i2c_lcd.h"
#include "tim2.h"
#include "uart.h"
#include "dht11.h"

int main(void)
{
		uint8_t temperature, humidity;
    USART1_Init(9600);
    USART1_Send_String("Starting I2C LCD Address Scan...\r\n");
		Timer2_Init();
    I2C2_LCD_Init();
		DHT11_Init();
    lcd_address = I2C2_Scan_Address();

    if (!lcd_address) {
        USART1_Send_String("No LCD detected. Check connections.\r\n");
        while (1);
    }
		
    LCD_Init();
    LCD_Clear();
    LCD_Set_Cursor(0, 0);
    LCD_Send_String("I2C LCD Found!");
    
    USART1_Send_String("LCD Initialization Completed!\r\n");
		LCD_Clear();
	
	while (1) 
	{
		DHT11_Read();
		GPIOC->ODR ^= GPIO_Pin_13;
		Delay_ms(1000);
	}
}
