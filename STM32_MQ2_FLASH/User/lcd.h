#ifndef _LCD_H_
#define _LCD_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "stdio.h"

#define LCD8574_ADDR 0x4E // Dia chi I2C cua PCF8574 (0x27 << 1)

// Khai bao cac ham
void I2C_Init_Custom(void);
uint8_t I2C_WriteByte(uint8_t addr, uint8_t data);
void LCD_Init(void);
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_Print(char *str);
void LCD_PrintNumber(int num);

void LCD_SetCursor(uint8_t row, uint8_t col);

#endif
