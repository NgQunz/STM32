#ifndef __LED7SEG_H
#define __LED7SEG_H

#include "stm32f10x.h"

// �?nh nghia c�c ch�n LED di?u khi?n 3 ch? s?
#define LED_DONVI GPIO_Pin_15
#define LED_CHUC  GPIO_Pin_14
#define LED_TRAM  GPIO_Pin_13

// M?ng hi?n th? s?
extern const uint8_t NUM[10];

// Kh?i t?o LED 7 do?n
void LED7SEG_InitDisplay(void);       // GPIOA - SEG a,b,c,...
void LED7SEG_InitControl(void);       // GPIOB - ch?n ch? s?

// H�m hi?n th? 1 gi� tr? (0-999) trong 1 gi�y
void LED7SEG_DisplayNumber(uint16_t number);

#endif
