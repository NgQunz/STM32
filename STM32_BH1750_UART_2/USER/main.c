#include "stm32f10x.h"
#include "tim2.h"
#include "bh1750.h"
#include "My_usart.h"
#include "i2c_lcd.h"

void Run_Sys(void);

uint32_t last_sample_time = 0;
uint32_t last_flash_read_time = 0;
extern uint16_t light_threshold;
extern uint32_t ti_check_lux;
extern uint16_t light;

int main(void)
{
	Timer2_Init();
  usart1_cfg_A9A10(BAUD_9600);
	
  bh1750_init();
  //GPIO_Config();
	
  I2C2_LCD_Init();
	
  lcd_address = I2C2_Scan_Address();
	if (!lcd_address) {
        printf_string("No LCD detected. Check connections.\r\n");
        while (1);
    }
  LCD_Init();
  LCD_Clear();
  LCD_Set_Cursor(0, 0);
		
  LCD_Send_String("I2C LCD Found!");
  LCD_Clear();

  while (1)
  {
    Run_Sys();
		uart_handle_command();
  }
}
void Run_Sys(void)
{
    uint32_t now = millis();
		
    // Cập nhật ánh sáng và ghi vào flash mỗi 1 giây
    if (now - last_sample_time >= 1000)
    {
        last_sample_time = now;
        light = BH1750_ReadLight();
        LCD_Set_Cursor(0, 0);	
        LCD_Send_String("Lux:");
        LCD_Send_Number(light);
        LCD_Send_String("/");
        LCD_Send_Number(light_threshold);
				
				printf_string("Threshold: ");
				printf_num(light_threshold);
				printf_string(" ms\r\nLux: ");
				printf_num(light);
				printf_string("\r\n");
        if (light > light_threshold)
        {
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
            LCD_Set_Cursor(0, 1);
            LCD_Send_String("Tat den ");
        }
        else
        {
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
            LCD_Set_Cursor(0, 1);
            LCD_Send_String("Bat den ");
        }

    }

}
