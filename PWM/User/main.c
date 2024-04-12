#include "tim2.h"
#include "MX1616.h"

int main(void)
{
	MX1616_Init();
	MX1616_SetForward(50);
	while(1)
	{
	}
}
