#include "led_matrix.h"
#include "timer2_delay.h"

int main(){
	void led_Matrix_Init();
	while(1){
		int i=0;
		for (i=0;i<8;i++)
		{
			GPIOB->ODR = hang[i];
			GPIOA->ODR = cot[i];
			Delay_ms(1);
		}
	}
}
