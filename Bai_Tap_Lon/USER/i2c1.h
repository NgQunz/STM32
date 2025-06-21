#ifndef __I2C1__
#define __I2C1__

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C


// MMA845 I2C Settings
#define MMA845_I2C                 I2C1
#define MMA845_I2C_RCC_Periph      RCC_APB1Periph_I2C1
#define MMA845_I2C_Port            GPIOB
#define MMA845_I2C_RCC_Port        RCC_APB2Periph_GPIOB
#define MMA845_I2C_SCL_Pin         GPIO_Pin_6
#define MMA845_I2C_SDA_Pin         GPIO_Pin_7
#define MMA845_I2C_Speed           400000 // 400kHz


void MMA845_I2C_Init(void);
void MMA845_I2C_ByteWrite(u8 slaveAddr, u8* pBuffer, u8 writeAddr);
void MMA845_I2C_BufferRead(u8 slaveAddr, u8* pBuffer, u8 readAddr, u16 NumByteToRead);

#endif
