#include "sys.h"

int main()
{
	// Config
	Sys_Init();
	
	// LOOP8
	while(1)
	{
		// Get dt
		previous_time = current_time;
		current_time = millis();
		dt = current_time - previous_time; // unit: ms
		// ===
		
		AvoidObstacles();
		//printf("%.0f\n", Get_yaw(FALSE));
	}
}
