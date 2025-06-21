#include "stm32f10x.h"
#include "button.h"
#include "tim2.h"

int main(void)
{
    Timer2_Init();      // Kh?i t?o Timer2 d? dùng millis()
    GPIO_Config();      // C?u hình LED và nút nh?n

    while (1)
    {
			Run_button();
    }
}
