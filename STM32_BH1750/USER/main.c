#include "stm32f10x.h"
#include "Delay.h"
#include "bh1750.h"
#include "My_usart.h"
#include "button.h"
#include "i2c_lcd.h"

void Run_Sys(void);

uint32_t last_sent_time = 0;
extern uint16_t light_threshold;

int main(void)
{
  SysTick_Init();
  usart1_cfg_A9A10(BAUD_9600);
  bh1750_init();
  GPIO_Config();
	

  I2C2_LCD_Init();
  lcd_address = I2C2_Scan_Address();
  LCD_Init();
  LCD_Clear();
  LCD_Set_Cursor(0, 0);
  LCD_Send_String("I2C LCD Found!");
  LCD_Clear();

  while (1)
  {
    Run_button(); // lu�n ki?m tra button
    Run_Sys();
  }
}
void Run_Sys(void)
{
  uint32_t now = SysTick_Millis();

  if (now - last_sent_time >= 1000)
  {
    last_sent_time = now;
    uint16_t light = BH1750_ReadLight();
    LCD_Set_Cursor(0, 0);
    LCD_Send_String("Lux:");
    LCD_Send_Number(light);
    LCD_Send_String("/");
    LCD_Send_Number(light_threshold);

    if (light > light_threshold)
    {
      GPIO_SetBits(GPIOC, GPIO_Pin_13);
      LCD_Set_Cursor(0, 1);
      LCD_Send_String("Tat den");
    }
    else
    {
      GPIO_ResetBits(GPIOC, GPIO_Pin_13);
      LCD_Set_Cursor(0, 1);
      LCD_Send_String("Bat den");
    }
  }
  delay_ms(10); // Kh�ng n�n qu� l?n d? kh�ng l? nh?n n�t
}
