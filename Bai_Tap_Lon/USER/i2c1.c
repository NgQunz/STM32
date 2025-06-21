#include "i2c1.h"


void MMA845_I2C_Init(void)
{
    I2C_InitTypeDef I2C_InitStructure;
	
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // Enable I2C and GPIO clocks
    RCC_APB1PeriphClockCmd(MMA845_I2C_RCC_Periph, ENABLE);
    RCC_APB2PeriphClockCmd(MMA845_I2C_RCC_Port, ENABLE);
    
    // Configure I2C pins: SCL and SDA
    GPIO_InitStructure.GPIO_Pin = MMA845_I2C_SCL_Pin | MMA845_I2C_SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(MMA845_I2C_Port, &GPIO_InitStructure);
    
    // I2C configuration
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = MMA845_I2C_Speed;
    
    I2C_Init(MMA845_I2C, &I2C_InitStructure);
    I2C_Cmd(MMA845_I2C, ENABLE);
}

void MMA845_I2C_ByteWrite(u8 slaveAddr, u8* pBuffer, u8 writeAddr)
{
    // Wait until I2C bus is not busy
    while(I2C_GetFlagStatus(MMA845_I2C, I2C_FLAG_BUSY));
    
    // Send START condition
    I2C_GenerateSTART(MMA845_I2C, ENABLE);
    while(!I2C_CheckEvent(MMA845_I2C, I2C_EVENT_MASTER_MODE_SELECT));
    
    // Send slave address
    I2C_Send7bitAddress(MMA845_I2C, slaveAddr, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(MMA845_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    // Send register address
    I2C_SendData(MMA845_I2C, writeAddr);
    while(!I2C_CheckEvent(MMA845_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // Send data
    I2C_SendData(MMA845_I2C, *pBuffer);
    while(!I2C_CheckEvent(MMA845_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // Send STOP condition
    I2C_GenerateSTOP(MMA845_I2C, ENABLE);
}

void MMA845_I2C_BufferRead(u8 slaveAddr, u8* pBuffer, u8 readAddr, u16 NumByteToRead)
{
    while(I2C_GetFlagStatus(MMA845_I2C, I2C_FLAG_BUSY));
    
    // Send START condition
    I2C_GenerateSTART(MMA845_I2C, ENABLE);
    while(!I2C_CheckEvent(MMA845_I2C, I2C_EVENT_MASTER_MODE_SELECT));
    
    // Send slave address for write
    I2C_Send7bitAddress(MMA845_I2C, slaveAddr, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(MMA845_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    // Send register address
    I2C_SendData(MMA845_I2C, readAddr);
    while(!I2C_CheckEvent(MMA845_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // Send RESTART condition
    I2C_GenerateSTART(MMA845_I2C, ENABLE);
    while(!I2C_CheckEvent(MMA845_I2C, I2C_EVENT_MASTER_MODE_SELECT));
    
    // Send slave address for read
    I2C_Send7bitAddress(MMA845_I2C, slaveAddr, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(MMA845_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    
    // Read data
    while(NumByteToRead)
    {
        if(NumByteToRead == 1)
        {
            I2C_AcknowledgeConfig(MMA845_I2C, DISABLE);
            I2C_GenerateSTOP(MMA845_I2C, ENABLE);
        }
        
        while(!I2C_CheckEvent(MMA845_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED));
        *pBuffer = I2C_ReceiveData(MMA845_I2C);
        pBuffer++;
        NumByteToRead--;
    }
    
    I2C_AcknowledgeConfig(MMA845_I2C, ENABLE);
}

