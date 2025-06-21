#include "Delay.h"

// Delay micro giay (hieu chinh cho dong ho 72 MHz)
// Moi __NOP() mat ~13.89 ns, dieu chinh '9' neu dong ho thay doi
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
