#include "stm32f10x.h"
#include "button.h"
#include "tim2.h"

int main(void)
{
    Timer2_Init();      // Kh?i t?o Timer2 d? d�ng millis()
    GPIO_Config();      // C?u h�nh LED v� n�t nh?n

    while (1)
    {
			Run_button();
    }
}
