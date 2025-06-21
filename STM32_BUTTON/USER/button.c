#include "button.h"
#include "tim2.h"  // Gi? s? b?n c� thu vi?n th?i gian tr? nhu Delay_ms()

bool led_state = false;
bool button_prev = false;

void GPIO_Config(void){
    GPIO_InitTypeDef GPIO;

    // B?t clock GPIOA, GPIOB, GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

    // C?u h�nh LED output (GPIOC, PC13)
    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO.GPIO_Pin = GPIO_Pin_13;
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);  // LED t?t khi kh?i d?ng

    // C?u h�nh button input pull-up (PA8)
    GPIO.GPIO_Pin = GPIO_Pin_8;
    GPIO.GPIO_Mode = GPIO_Mode_IPU;
    GPIO.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO);
}

uint8_t debounce_button(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET) {
        Delay_ms(200);  // Tang th?i gian debounce l�n 200ms
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET) {
            return 1;  // N�t d� du?c nh?n
        }
    }
    return 0;  // Kh�ng nh?n
}


void Toggle_LED(uint8_t *led_State) {
    *led_State = !(*led_State);  // �?o tr?ng th�i LED
    if (*led_State) {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // LED s�ng
    } else {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED t?t
    }
}

void Run_button(void){
	        uint8_t button_state = debounce_button(GPIOA, GPIO_Pin_8);
        if (button_state && !button_prev) {  // Ki?m tra s? thay d?i tr?ng th�i n�t nh?n
            Toggle_LED(&led_state);         // Ch? thay d?i LED khi n�t nh?n
        }
        button_prev = button_state;         // C?p nh?t tr?ng th�i n�t nh?n tru?c
}
