#include "led7seg.h"

const uint8_t NUM[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void Delay_ms(uint16_t ms)
{
    for (uint16_t i = 0; i < ms; i++)
        for (uint16_t j = 0; j < 7999; j++);
}

void LED7SEG_InitDisplay(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
                                   GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIOA->ODR = 0xFF;
}

void LED7SEG_InitControl(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED_DONVI | LED_CHUC | LED_TRAM;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIOB->ODR = 0xFFFF;
}

void LED7SEG_DisplayNumber(uint16_t number)
{
    uint16_t elapsed = 0;

    while (elapsed < 1000)
    {
        // �on v?
        GPIO_SetBits(GPIOB, LED_DONVI);
        GPIOA->ODR = NUM[number % 10];
        Delay_ms(5);
        GPIO_ResetBits(GPIOB, LED_DONVI);

        // Ch?c
        GPIO_SetBits(GPIOB, LED_CHUC);
        GPIOA->ODR = NUM[(number / 10) % 10];
        Delay_ms(5);
        GPIO_ResetBits(GPIOB, LED_CHUC);

        // Tram
        GPIO_SetBits(GPIOB, LED_TRAM);
        GPIOA->ODR = NUM[(number / 100) % 10];
        Delay_ms(5);
        GPIO_ResetBits(GPIOB, LED_TRAM);

        elapsed += 15;
    }
}
