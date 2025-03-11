#include "gpio.h"
#include "timer2_delay.h"

#define SH_PIN GPIO_Pin_0
#define DS_PIN GPIO_Pin_1
#define ST_PIN GPIO_Pin_2

uint32_t left_to_right_arr[] = { 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF };
uint32_t fly_arr[] = { 0x00, 0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18 };
uint32_t water_arr[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
                     0x81, 0x41, 0x21, 0x11, 0x09, 0x05, 0x03, 0x83,
                     0x43, 0x23, 0x13, 0x0B, 0x07, 0x87, 0x47, 0x27,
                     0x17, 0x0F, 0x8F, 0x4F, 0x2F, 0x1F, 0x9F, 0x5F,
                     0x3F, 0xBF, 0x7F, 0xFF };
uint32_t snake_arr[] = { 0x81, 0x41, 0x21, 0x11, 0x09, 0x05, 0x03, 0xC1,
                     0x61, 0x31, 0x19, 0x0D, 0x07, 0xE1, 0x71, 0x39,
                     0x1D, 0x0F, 0xF1, 0x79, 0x3D, 0x1F, 0xF9, 0x7D,
                     0x3F, 0xFD, 0x7F, 0xFF };
void left_to_right();
void fly();
void water();
void snake();
void customShiftOut(int dataPin, int clockPin, int bitOrder, uint32_t value);
int main(){
	timer_Init();
	led_Init();
	GPIO_Config();
	GPIO_SetBits(GPIOA, GPIO_Pin_9);  // ON LED 9
  GPIO_ResetBits(GPIOA, GPIO_Pin_10); // Off LED 10
    while (1) {
        Blink_led_snake();
    }
}

void left_to_right() {
    for (i = 0; i < sizeof(left_to_right_arr) / sizeof(left_to_right_arr[0]); i++) {
        customShiftOut(DS_PIN, SH_PIN, 0, left_to_right_arr[i]);
    }
}

void fly() {
    for (i = 0; i < sizeof(fly_arr) / sizeof(fly_arr[0]); i++) {
        customShiftOut(DS_PIN, SH_PIN, 0, fly_arr[i]);
    }
}

void water() {
    for (i = 0; i < sizeof(water_arr) / sizeof(water_arr[0]); i++) {
        customShiftOut(DS_PIN, SH_PIN, 0, water_arr[i]);
    }
}

void snake() {
    for (i = 0; i < sizeof(snake_arr) / sizeof(snake_arr[0]); i++) {
        customShiftOut(DS_PIN, SH_PIN, 0, snake_arr[i]);
    }
}

void customShiftOut(uint16_t dataPin, uint16_t clockPin, uint16_t bitOrder, uint32_t value) {
    GPIO_ResetBits(GPIOA, ST_PIN); // T?t luu d? li?u vào b? ghi-d?ch

    for (i = 0; i < 8; i++) {
        if (bitOrder == 0) { // LSBFIRST
            if (value & (1 << i)) {
                GPIO_SetBits(GPIOA, dataPin);
            } else {
                GPIO_ResetBits(GPIOA, dataPin);
            }
        } else { // MSBFIRST
            if (value & (1 << (7 - i))) {
                GPIO_SetBits(GPIOA, dataPin);
            } else {
                GPIO_ResetBits(GPIOA, dataPin);
            }
        }

        GPIO_SetBits(GPIOA, clockPin); // Xung clock lên
        Delay_us(5);  // Thay d?i th?i gian delay n?u c?n
        GPIO_ResetBits(GPIOA, clockPin); // Xung clock xu?ng
    }

    GPIO_SetBits(GPIOA, ST_PIN); // Luu d? li?u vào b? ghi-d?ch
    Delay_ms(200);  // Thay d?i th?i gian delay n?u c?n
}
