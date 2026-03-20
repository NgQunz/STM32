#include "uart.h"
#include "timer2_delay.h"

int main(void) {
    timer_Init();
    GPIO_Config_TX_RX();
    USART1_Config();   // PC
    USART2_Config();   // ESP32
    led_Init();

    PC_Println("=== STM32 UART Bridge ===");
    PC_Println("Nhap ban tin roi nhan Enter de gui ESP32:");

    char input[64];
    char log[96];
    Message_t tx_msg, rx_msg;

    while (1) {
        // -- Nh?n l?nh t? PC, g?i t?i ESP32 --
        if (PC_ReadLine(input, sizeof(input))) {
            snprintf(log, sizeof(log), "[PC->ESP32] %s", input);
            PC_Println(log);

            MSG_Build(&tx_msg, CMD_TEXT, (uint8_t*)input, strlen(input));
            MSG_Send_ESP32(&tx_msg);
        }

        // -- Nh?n b?n tin t? ESP32, hi?n th? lên PC --
        if (MSG_Receive_ESP32(&rx_msg)) {
            rx_msg.data[rx_msg.len] = '\0';

            if (rx_msg.cmd == CMD_TEXT) {
                snprintf(log, sizeof(log), "[ESP32->PC] %s", (char*)rx_msg.data);
                PC_Println(log);

                // G?i ACK l?i
                uint8_t ack = 0x01;
                MSG_Build(&tx_msg, CMD_ACK, &ack, 1);
                MSG_Send_ESP32(&tx_msg);
                PC_Println("[STM32] Da gui ACK");
            } else if (rx_msg.cmd == CMD_ACK) {
                PC_Println("[STM32] Nhan ACK tu ESP32");
            }
        }
    }
}