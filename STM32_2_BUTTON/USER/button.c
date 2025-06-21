#include "button.h"
#include "tim2.h"
#include "uart.h"  // n?u mu?n hi?n th? light qua UART

bool led_state = false;
bool button_inc_prev = false;
bool button_dec_prev = false;
uint16_t light = 0;  // Bi?n c?n tang/gi?m

void GPIO_Config(void) {
    GPIO_InitTypeDef GPIO;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

    // LED PC13
    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO.GPIO_Pin = GPIO_Pin_13;
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);

    // Button PA8 (Tang), PA9 (Gi?m)
    GPIO.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_6;
    GPIO.GPIO_Mode = GPIO_Mode_IPU;
    GPIO.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO);
}

uint8_t debounce_button(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET) {
        Delay_ms(20);  // debounce time
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET) {
            return 1;
        }
    }
    return 0;
}

void Toggle_LED(uint8_t *led_State) {
    *led_State = !(*led_State);
    if (*led_State)
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // LED on
    else
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED off
}

void Run_button(void) {
    uint8_t button_inc = debounce_button(GPIOA, GPIO_Pin_6);  // Nút tang
    uint8_t button_dec = debounce_button(GPIOA, GPIO_Pin_8);  // Nút gi?m

    if (button_inc && !button_inc_prev) {
        light++;
        Toggle_LED(&led_state);
        USART1_Send_String("Light increased");
			USART1_Send_Number(light);
    }

    if (button_dec && !button_dec_prev) {
        light--;
        Toggle_LED(&led_state);
        USART1_Send_String("Light decreased" );
			USART1_Send_Number(light);
    }

    button_inc_prev = button_inc;
    button_dec_prev = button_dec;
}
