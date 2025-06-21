#include "stm32f10x.h"
#include <stdint.h>

// ---------------- DEF VA BIEN ----------------

#define LCD8574_ADDR 0x4E // Dia chi I2C cua PCF8574 (0x27 << 1)
uint32_t elapsed_ms = 0;
#define FLASH_SAVE_ADDR  0x0801FC00  // ÐIa chi cuoi flash 

// ---------------- NGUYEN HAM ----------------

// Khai báo hàm cam bien MQ2
void MQ2_Init(void);
uint32_t MQ2_Read_ppm(void);

void LED_Init(void);
void LED_Red_Blink(void);
void SystemClock_Config(void);
void Display_Saved_PPM(void);

// Khai bao cac ham I2C LCD
void I2C_Init_Custom(void);
uint8_t I2C_WriteByte(uint8_t addr, uint8_t data);
void LCD_Init(void);
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_Print(char *str);
void LCD_PrintNumber(int num);
void LCD_SetCursor(uint8_t row, uint8_t col);

// Khai báo hàm delay
void delay_us(uint32_t us);
void delay_ms(uint32_t time);

void Flash_SaveValue(uint32_t address, uint32_t value);
uint32_t Flash_ReadValue(uint32_t address);

// ---------------- KET THUC NGUYEN HAM ----------------
int main(void) {
    LED_Init();
    SystemClock_Config();
    I2C_Init_Custom();
    LCD_Init();
    MQ2_Init();

    LCD_Print("Canh bao khi gas ");
    delay_ms(2000);
    LCD_SendCommand(0x01);
    delay_ms(2);

    while (1) {
        uint32_t ppm = MQ2_Read_ppm();
        LCD_SetCursor(0, 0);
        LCD_Print("Gas: ");
        LCD_PrintNumber(ppm);
        LCD_Print(" ppm    ");
        Display_Saved_PPM();

        if (ppm > 180) {
            LCD_SetCursor(1, 0);
            LCD_Print("Nguy hiem");
            GPIO_ResetBits(GPIOB, GPIO_Pin_1);
            LED_Red_Blink();
        } else {
            LCD_SetCursor(1, 0);
            LCD_Print("An toan  ");
            GPIO_SetBits(GPIOB, GPIO_Pin_1);
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
        }

        elapsed_ms += 500;

        if (elapsed_ms >= 10000) {
            Flash_SaveValue(FLASH_SAVE_ADDR, ppm);
            elapsed_ms = 0;
        }

        delay_ms(500);
    }
}

// ---------------- MQ2 CODE BEGIN ----------------

// Hàm kh?i t?o c?m bi?n MQ2 s? d?ng kênh ADC1 Channel 0 (PA0)
void MQ2_Init(void) {
    ADC_InitTypeDef ADC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStruct);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

// Hàm d?c giá tr? t? c?m bi?n MQ2 và chuy?n d?i sang don v? ppm
uint32_t MQ2_Read_ppm(void) {
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    uint16_t adc_value = ADC_GetConversionValue(ADC1);
    float voltage = (adc_value * 3.3) / 4095.0;

    if (voltage == 0.0) {
        return 0;
    }

    double RS = ((5.0 * 10000.0) / voltage) - 10000.0;
    double R0 = 10000.0;
    double b = 1.24;
    double m = -0.455;
    double ppm = pow(10.0, (log10(RS / R0) - b) / m);

    return (uint32_t)ppm;
}

// ---------------- MQ2 CODE END ----------------

// ---------------- SYSTEM - LED AND DISPLAY ----------------
void LED_Init(void) {
    GPIO_InitTypeDef GPIO;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO.GPIO_Pin = GPIO_Pin_1;
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO);
		GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO.GPIO_Pin = GPIO_Pin_13;
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO);
    GPIO_ResetBits(GPIOB, GPIO_Pin_1);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

void LED_Red_Blink(void) {
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
    delay_ms(500);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    delay_ms(500);
}

void SystemClock_Config(void) {
    RCC_HSEConfig(RCC_HSE_ON);
    while (!RCC_GetFlagStatus(RCC_FLAG_HSERDY));
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while (!RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);
}

void Display_Saved_PPM(void) {
    uint32_t saved_ppm = Flash_ReadValue(FLASH_SAVE_ADDR);

    LCD_SetCursor(1, 9);
    LCD_PrintNumber(saved_ppm);
    LCD_Print(" ppm           ");
}

// ---------------- SYSTEM - LED AND DISPLAY END ----------------

// ---------------- I2C - LCD ----------------

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

// ---------------- I2C - LCD - END ----------------

// ---------------- DELAY ----------------

void delay_us(uint32_t us) {
    uint32_t i;
    for (i = 0; i < us * 9; i++) {
        __NOP();
    }
}

// Delay mili giay
void delay_ms(uint32_t time) {
    delay_us(time * 1000);
}

// ---------------- DELAY - END ----------------

// ---------------- FLASH ----------------

static void Flash_Unlock(void) {
    if (FLASH->CR & FLASH_CR_LOCK) {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

static void Flash_Lock(void) {
    FLASH->CR |= FLASH_CR_LOCK;
}

static void Flash_WaitBusy(void) {
    while (FLASH->SR & FLASH_SR_BSY);
}

static void Flash_ErasePage(uint32_t address) {
    Flash_WaitBusy();
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR = address;
    FLASH->CR |= FLASH_CR_STRT;
    Flash_WaitBusy();
    FLASH->CR &= ~FLASH_CR_PER;
}

static void Flash_WriteWord(uint32_t address, uint32_t data) {
    Flash_WaitBusy();
    FLASH->CR |= FLASH_CR_PG;

    *(volatile uint16_t*)address = (uint16_t)(data & 0xFFFF);
    Flash_WaitBusy();
    *(volatile uint16_t*)(address + 2) = (uint16_t)(data >> 16);
    Flash_WaitBusy();

    FLASH->CR &= ~FLASH_CR_PG;
}

void Flash_SaveValue(uint32_t address, uint32_t value) {
    Flash_Unlock();
    Flash_ErasePage(address);
    Flash_WriteWord(address, value);
    Flash_Lock();
}

uint32_t Flash_ReadValue(uint32_t address) {
    return *(volatile uint32_t*)address;
}

// ---------------- FLASH - END ----------------

// ---------------- MAIN - END ----------------
