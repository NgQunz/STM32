#include "LCD.h"
#include "Delay.h"

// Khoi tao I2C1 de giao tiep voi PCF8574
void I2C_Init_Custom(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    I2C_InitTypeDef I2C_InitStruct;

    // Bat dong ho cho I2C1 va GPIOB
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // Cau hinh PB6 (SCL) va PB7 (SDA) o che do open-drain
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Cau hinh I2C1 o che do master, toc do 100 kHz
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1 = 0x00;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStruct.I2C_ClockSpeed = 100000;
    I2C_Init(I2C1, &I2C_InitStruct);
    I2C_Cmd(I2C1, ENABLE);
}

// Gui mot byte den dia chi I2C voi timeout
uint8_t I2C_WriteByte(uint8_t addr, uint8_t data) {
    uint32_t timeout = 100000;

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) && --timeout);
    if (timeout == 0) return 1; // Loi: Bus ban

    I2C_GenerateSTART(I2C1, ENABLE);
    timeout = 100000;
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) && --timeout);
    if (timeout == 0) return 1; // Loi: Khong tao duoc START

    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);
    timeout = 100000;
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) && --timeout);
    if (timeout == 0) return 1; // Loi: Gui dia chi that bai

    I2C_SendData(I2C1, data);
    timeout = 100000;
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && --timeout);
    if (timeout == 0) return 1; // Loi: Gui du lieu that bai

    I2C_GenerateSTOP(I2C1, ENABLE);
    return 0; // Thanh cong
}

// Khoi tao LCD qua PCF8574
void LCD_Init(void) {
    delay_ms(50);
    LCD_SendCommand(0x28); // Che do 4-bit, 2 dong, font 5x8
    LCD_SendCommand(0x0C); // Bat hien thi, tat con tro
    LCD_SendCommand(0x06); // Con tro di chuyen sang phai
    LCD_SendCommand(0x01); // Xoa man hinh
    delay_ms(2);
}

// Gui lenh dieu khien den LCD (RS = 0)
void LCD_SendCommand(uint8_t cmd) {
    uint8_t data_u = (cmd & 0xF0) | 0x08; // Nibble cao, RS=0
    uint8_t data_l = ((cmd << 4) & 0xF0) | 0x08; // Nibble thap, RS=0
    I2C_WriteByte(LCD8574_ADDR, data_u | 0x04); // EN=1
    I2C_WriteByte(LCD8574_ADDR, data_u);        // EN=0
    I2C_WriteByte(LCD8574_ADDR, data_l | 0x04); // EN=1
    I2C_WriteByte(LCD8574_ADDR, data_l);        // EN=0
}

// Gui du lieu den LCD (RS = 1)
void LCD_SendData(uint8_t data) {
    uint8_t data_u = (data & 0xF0) | 0x09; // Nibble cao, RS=1
    uint8_t data_l = ((data << 4) & 0xF0) | 0x09; // Nibble thap, RS=1
    I2C_WriteByte(LCD8574_ADDR, data_u | 0x04); // EN=1
    I2C_WriteByte(LCD8574_ADDR, data_u);        // EN=0
    I2C_WriteByte(LCD8574_ADDR, data_l | 0x04); // EN=1
    I2C_WriteByte(LCD8574_ADDR, data_l);        // EN=0
}

// Hien thi chuoi ky tu tren LCD
void LCD_Print(char *str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}

// Hien thi so nguyen tren LCD
void LCD_PrintNumber(int num) {
    char buffer[10];
    sprintf(buffer, "%d", num);
    LCD_Print(buffer);
}
// Set con tr? t?i dòng 'row' và c?t 'col' (0-based)
void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t addr;

    // Tính d?a ch? d?a trên dòng và c?t
    if (row == 0) {
        addr = 0x80 + col;  // Dòng 1
    } else if (row == 1) {
        addr = 0xC0 + col;  // Dòng 2
    }

    // G?i l?nh d? set con tr?
    LCD_SendCommand(addr);
}
