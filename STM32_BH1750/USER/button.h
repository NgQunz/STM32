/**
  ******************************************************************************
  * @file    button.h
  * @author  Nguyen Minh Quan
  * @date    8-5-2025
  * @brief   2 BUTTON 
  ******************************************************************************
  * @attention
  ******************************************************************************
*/

#ifndef __BUTTON_LED_H
#define __BUTTON_LED_H

#include "stm32f10x.h"
#include <stdbool.h>
#include "My_usart.h"


void GPIO_Config(void);
uint8_t debounce_button(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Toggle_LED(uint8_t *led_State);                      // Hàm di?u khi?n LED
void Run_button(void);

#endif
