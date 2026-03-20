#include "stm32f10x.h"
#include "uart.h"
#include "tim2.h"
#include "dht11.h"
#include <string.h>

// =============================================================
//  Nguyen Minh Quan - B22DCDT248
//  Node 2 : STM32 + DHT11 (PB12) + LED (PC13)
//  Node 1 : ESP32 + BH1750 + LED (D2)
//
//  Luong hoat dong:
//  1. Cho ban tin tu ESP32 (Node 1):
//     "Nguyen Minh Quan - B22DCDT248 - Lux:<lux>"
//  2. Doc DHT11 -> g_temp, g_hum
//  3. Gui phan hoi ve ESP32:
//     "Phan hoi tu Node 2 ve Node 1: T:<temp>C H:<hum>%"
//  4. Lux < 100 -> bat LED PC13
//     Lux >= 100 -> tat LED PC13
// =============================================================

#define LUX_THRESHOLD  100

// ---- int16 -> string ----------------------------------------
static void i16_to_str(char *buf, int16_t val)
{
    uint8_t i = 0;
    if (val == 0) { buf[0]='0'; buf[1]=0; return; }
    if (val < 0)  { buf[i++]='-'; val = -val; }
    char tmp[8]; uint8_t n = 0;
    while (val > 0) { tmp[n++] = '0' + (val % 10); val /= 10; }
    for (int8_t k = n-1; k >= 0; k--) buf[i++] = tmp[k];
    buf[i] = 0;
}

// ---- Parse lux tu "...- Lux:<lux>" -------------------------
static int32_t parse_lux(const char *str)
{
    const char *p = strstr(str, "Lux:");
    if (!p) return -1;
    p += 4;
    int32_t val = 0;
    while (*p >= '0' && *p <= '9') { val = val*10 + (*p - '0'); p++; }
    return val;
}

// =============================================================
int main(void)
{
    GPIO_Config_TX_RX();
    USART1_Config();
    USART2_Config();
    Timer2_Init();
    DHT11_Init();   // PB12 + LED PC13

    PC_Println("=== STM32 Node 2 READY ===");
    PC_Println("Nguyen Minh Quan - B22DCDT248");

    Message_t tx_msg, rx_msg;
    char payload[80];
    char s_temp[8], s_hum[8];

    while (1)
    {
        // =====================================================
        // BUOC 1: Cho ban tin tu ESP32 (toi da 3000ms)
        // =====================================================
        uint32_t t_wait = millis();
        uint8_t  got_msg = 0;

        while ((millis() - t_wait) < 3000)
        {
            if (MSG_Receive_ESP32(&rx_msg))
            {
                rx_msg.data[rx_msg.len] = 0;
                //PC_Print("Ban tin nhan duoc tu  "); 
							PC_Println((char*)rx_msg.data);
                got_msg = 1;
                break;
            }
        }

        if (!got_msg) {
            PC_Println("[WARN] Khong nhan duoc ban tin tu ESP32");
            continue;
        }

        // =====================================================
        // BUOC 2: Doc DHT11
        // =====================================================
        DHT11_Read();  // cap nhat g_temp, g_hum

        // =====================================================
        // BUOC 3: Gui phan hoi ve ESP32
        // "Phan hoi tu Node 2 ve Node 1: T:<temp>C H:<hum>%"
        // =====================================================
        i16_to_str(s_temp, g_temp);
        i16_to_str(s_hum,  g_hum);

        strcpy(payload, "Phan hoi tu Node 2 ve Node 1: T:");
        strcat(payload, s_temp);
        strcat(payload, "C H:");
        strcat(payload, s_hum);
        strcat(payload, "%");

        MSG_Build(&tx_msg, CMD_TEXT, (uint8_t*)payload, (uint8_t)strlen(payload));
        MSG_Send_ESP32(&tx_msg);
        //PC_Print("Ban tin den ESP32 "); 
				PC_Println(payload);

        // =====================================================
        // BUOC 4: Parse lux tu ban tin ESP32
        //         Lux < 100 -> bat LED PC13
        //         Lux >= 100 -> tat LED PC13
        // =====================================================
        int32_t lux = parse_lux((char*)rx_msg.data);
        if (lux >= 0) {
            if (lux < LUX_THRESHOLD) {
                GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // Active LOW: bat
                PC_Println(" Lux < 100 -> BAT PC13");
            } else {
                GPIO_SetBits(GPIOC, GPIO_Pin_13);    // Tat
                PC_Println("Lux >= 100 -> TAT PC13\n");
            }
        }
    }
}