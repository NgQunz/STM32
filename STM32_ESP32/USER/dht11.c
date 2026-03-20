#include "dht11.h"
#include "uart.h"
#include "tim2.h"

int16_t g_temp = 0;
int16_t g_hum  = 0;

static uint8_t DHT11_ReadByte(void)
{
    uint8_t  byte   = 0;
    uint16_t u16Tim = 0;

    for (int i = 0; i < 8; ++i)
    {
        // Cho PB12 len HIGH (bit start ~50us)
        TIM_SetCounter(TIM2, 0);
        while (TIM_GetCounter(TIM2) < 65) {
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) break;
        }

        // Cho PB12 xuong LOW, do thoi gian HIGH
        TIM_SetCounter(TIM2, 0);
        while (TIM_GetCounter(TIM2) < 80) {
            if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) break;
        }
        u16Tim = TIM_GetCounter(TIM2);

        byte <<= 1;
        if (u16Tim > 45) byte |= 1;   // >45us = bit 1 (~70us), <45us = bit 0 (~28us)
    }
    return byte;
}

void DHT11_Init(void)
{
    GPIO_InitTypeDef gpioInit;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // LED PC13 - Push-Pull Output
    gpioInit.GPIO_Mode  = GPIO_Mode_Out_PP;
    gpioInit.GPIO_Pin   = GPIO_Pin_13;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpioInit);

    // DHT11 PB12 - Open-Drain Output (can pull-up ngoai)
    gpioInit.GPIO_Mode  = GPIO_Mode_Out_OD;
    gpioInit.GPIO_Pin   = GPIO_Pin_12;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpioInit);

    GPIO_SetBits(GPIOB, GPIO_Pin_12);  // Idle HIGH
}

void DHT11_Read(void)
{
    uint8_t u8Buff[5]  = {0};
    uint8_t u8CheckSum = 0;

    // === Tin hieu Start ===
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    Delay_ms(20);                          // Keo LOW >= 18ms
    GPIO_SetBits(GPIOB, GPIO_Pin_12);      // Nha ra HIGH

    // === Cho DHT11 phan hoi ===
    // Buoc 1: cho HIGH ngan (~20-40us)
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < 40) {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) break;
    }
    // Buoc 2: DHT keo LOW 80us
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < 95) {
        if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) break;
    }
    // Buoc 3: DHT keo HIGH 80us
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < 95) {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) break;
    }
    // Buoc 4: DHT keo LOW -> bat dau truyen data
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < 95) {
        if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) break;
    }

    // === Doc 5 byte ===
    for (int i = 0; i < 5; i++) {
        u8Buff[i] = DHT11_ReadByte();
    }

    // === Checksum ===
    u8CheckSum = u8Buff[0] + u8Buff[1] + u8Buff[2] + u8Buff[3];

    // === Cap nhat bien global ===
    g_temp = (int16_t)u8Buff[2];
    g_hum  = (int16_t)u8Buff[0];

    // === In ra USART1 (debug PC) ===
    PC_Print("Temperature: ");
    USART1_Send_Number(g_temp);
    PC_Print("*C | Humidity: ");
    USART1_Send_Number(g_hum);
    PC_Println("%");

    if (u8CheckSum != u8Buff[4]) {
        PC_Println("DHT11 Checksum ERROR!");
    }
}