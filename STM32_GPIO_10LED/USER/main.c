#include "gpio.h"
#include "timer2_delay.h"

int n=4;
void Blink_led_1()
{
	uint32_t i;
	for (i = 0; i < 4; i++) {
            GPIO_SetBits(GPIOA, (1 << i));// On LED A 0-3 // phép dich trai, tuc la se bat theo ma nhi pha
            Delay_ms(500); // ví du led A0 se la 00000001, A1 la 00000010
            //GPIO_ResetBits(GPIOA, (1 << i));// Off LED A 0-3
        }
	for (i = 0; i < 4; i++) {
            //GPIO_SetBits(GPIOA, (1 << i));// On LED A 0-3 // phép dich trai, tuc la se bat theo ma nhi pha
            Delay_ms(500); // ví du led A0 se la 00000001, A1 la 00000010
            GPIO_ResetBits(GPIOA, (1 << i));// Off LED A 0-3
        }
}
void Blink_led_2()
{
	uint32_t i;
	for (i = 0; i < 4; i++) {
            GPIO_SetBits(GPIOA, (1 << i));
            Delay_ms(500);
            GPIO_ResetBits(GPIOA, (1 << i));
        }
}
void Blink_led_fly()
{
	int i=0;
for (i = 0; i < 2; i++) {
            GPIO_SetBits(GPIOA, (1 << i));      // Bat LED ngoài cùng (A0 và A3)
            GPIO_SetBits(GPIOA, (1 << (3 - i)));// Bat LED ngoài cùng d?i di?n (A3 và A0)
            Delay_ms(500);
        }

        // Tat tu trong ra ngoài
        for (i = 1; i >= 0; i--) {
            GPIO_ResetBits(GPIOA, (1 << i));      // Tat LED trong cùng (A1 và A2)
            GPIO_ResetBits(GPIOA, (1 << (3 - i)));// Tat LED trong cùng d?i di?n (A2 và A1)
            Delay_ms(500);
        }
			}
void Blink_led_water_drop() {
    int i;  // Declare variable i outside the loops
		
    // Water drop effect: light up LEDs from A0 to A3
    for (i = 0; i < n; i++) {
        GPIO_SetBits(GPIOA, (1 << i));  // Turn on LED from A0 to A3
        Delay_ms(500);                    // Delay between each LED turning on
			if (i!=n-1)
			{
        GPIO_ResetBits(GPIOA, (1 << i));  // Turn off LED after the drop
			}
    }
		n--;
		if (n==0)
		{
			// Turn off all LEDs and repeat the effect
			for (i = 0; i < 4; i++) {
					GPIO_ResetBits(GPIOA, (1 << i));  // Turn off all LEDs from A0 to A3
			}
			Delay_ms(500);  // Delay before starting the effect again
			n=4;
		}
}

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

	