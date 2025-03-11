#include "sys.h"
#include "math.h"

uint32_t  dt, current_time = 0, previous_time;
int8_t    left_speed = 0, right_speed = 0;

float     LSB = 0;
float     yaw = 0;
float     sum_sp = 0;
float     gyro_errorZ = 0;

uint8_t    rotate_flag = FALSE;

// Struct
PID_InitTypeDef   PID_Yaw;

float Get_yaw(uint8_t *reset)
{
	static float yaw_raw = 0;
	static int   pre_yaw = 0;
	float  gyro_z = 0;
	int16_t   accel_gyro[7];
	
	if(*reset == TRUE)
	{
		yaw_raw = 0;
		pre_yaw = 0;
		*reset = FALSE;
	}
	
	// Get Gyro
	MPU6050_GetRawAccelGyro(accel_gyro);
	gyro_z = (float)accel_gyro[5] - gyro_errorZ;
	gyro_z /= LSB;// gyro value
	
	yaw_raw -= gyro_z * dt;
	
	// calib yaw
	if((int)yaw_raw - pre_yaw >= 100)  // chieu duong
	{
		yaw_raw += 0.85;
		pre_yaw = (int)yaw_raw;
	}
	else if((int)yaw_raw - pre_yaw <= -100)  // chieu am
	{
		yaw_raw -= 0.85;
		pre_yaw = (int)yaw_raw;
	}
	//
	return yaw_raw/1000;
}

// Quay
// De kich hoat can phai set rotate_flag = TRUE
void Rotate(float sp)
{
	float       pre_yaw = 0;
	float       delta_yaw = 0.3;
	uint8_t     original_speed = min_speed + 10;

	uint8_t     reset = FALSE;   // reset encoder and yaw
	uint8_t     start = TRUE;    // Slow acceleretion at start == TRUE
	uint32_t    disable_time = 0;
	uint32_t    time = 0;

	while(rotate_flag == TRUE)
	{
		Read_All_Sensors();

		// Get dt
		previous_time = current_time;
		current_time = millis();
		dt = (current_time - previous_time); // ms
		
		// Dieu kien ban dau
		if(reset == FALSE)
		{
			reset = TRUE;
			start = TRUE;
			sum_sp += sp;
		}
		
		yaw = Get_yaw(FALSE); // Get yaw
		
		// Neu khong co su thay doi nhieu thi disable ==> tranh bi vong lap dao dong
		if(abs(pre_yaw - yaw) <= delta_yaw && (abs(yaw - sum_sp) <= 1))
		{
			if(millis() - disable_time > 100)
			{
				rotate_flag = FALSE;
			}
		}
		else
		{
			disable_time = millis();
		}
			
		pre_yaw = yaw;
		
		// PID
		PID_Yaw.error = sum_sp - yaw;

		// If pv approaches sp
		if(abs(PID_Yaw.error) <= delta_yaw)
		{
			left_speed = 0;
			right_speed = 0;
			if(millis() - time > 100) // delay a bit
			{
				rotate_flag = FALSE;
			}
		}
		else
		{
			time = millis();
			
			// tang toc tu tu khi start
			if(start == TRUE)
			{
				if(abs(yaw - (sum_sp - sp)) < min(20, (sp / 2)))
				{
					if(PID_Yaw.error >= 0){
						left_speed  = min_speed + original_speed * abs(yaw - (sum_sp - sp)) / 20;
						right_speed = -(min_speed + original_speed * abs(yaw - (sum_sp - sp)) / 20);
					}
					else{
						left_speed  = -(min_speed + original_speed * abs(yaw - (sum_sp - sp)) / 20);
						right_speed = min_speed + original_speed * abs(yaw - (sum_sp - sp)) / 20;
					}
				}
				else 
				{
					start = FALSE;
				}
			}

			// error <= 45 -> update pid
			else if(abs(PID_Yaw.error) <= 45)
			{
				// Update PID
				PID_Update(&PID_Yaw, yaw);

				if(PID_Yaw.pid >= 0){
					left_speed  = min_speed + PID_Yaw.pid;
					right_speed = -(min_speed + PID_Yaw.pid);
				}
				else{
					left_speed  = -min_speed + PID_Yaw.pid;
					right_speed = -(-min_speed + PID_Yaw.pid);
				}
			}
			
			// max_speed
			else
			{
				if(PID_Yaw.error >= 0){
					left_speed  = original_speed;
					right_speed = -original_speed;
				}
				else{
					left_speed  = -original_speed;
					right_speed = original_speed;
				}
			}
		}

		Motor_Move(MOTOR_LEFT,   left_speed);
		Motor_Move(MOTOR_RIGHT, right_speed);
	}

	// rotate_flag == FALSE
	PID_Yaw.I = 0;
	Motor_Move(MOTOR_LEFT,   0);
	Motor_Move(MOTOR_RIGHT,  0);
}

void AvoidObstacles(void)
{
	int16_t angle = 0;
	uint8_t original_speed = 50;

	Read_All_Sensors();

	if(IRSensor[2].value > 800 || IRSensor[3].value > 800)
	{
		rotate_flag = TRUE;

		if(IRSensor[0].value > 800 && IRSensor[5].value > 800)
		{
			if(IRSensor[2].value - IRSensor[3].value > 0)
			{
				angle = -180;
			}
			else 
			{
				angle = 180;
			}
		}
		else if(IRSensor[2].value > 800)
		{
			angle = -90;
		}
		else if(IRSensor[3].value > 800)
		{
			angle = 90;
		}

		// Rotate
		if(rotate_flag == TRUE)
		{
			Rotate(angle);
			rotate_flag = FALSE;
		}
	}
	else 
	{
		// Go straight
		Motor_Move(MOTOR_LEFT,  original_speed);
		Motor_Move(MOTOR_RIGHT, original_speed);
		delay_ms(2);
	}
}

void PID_Update(PID_InitTypeDef *PID, float pv)
{
	PID->P = PID->kp * PID->error;
	PID->I += PID->ki * PID->error*dt/1000;          // dt: ms
	if(PID->pre_pv != 0) {
		PID->D = -PID->kd * (pv - PID->pre_pv)*1000/dt;
	}
	PID->pre_pv = pv;

	if(max(left_speed, right_speed)  >  max_speed) PID->I -= PID->ki * PID->error * dt / 1000;
	else if(min(left_speed, right_speed)  < -max_speed) PID->I += PID->ki * PID->error * dt / 1000;
	
	PID->pid = PID->P + PID->I + PID->D;
}

/*
 * PID_Struct, kp, ki, kd
*/
void PID_Init(PID_InitTypeDef *PID, float kp, float ki, float kd)
{
	PID->kp = kp;
	PID->ki = ki;
	PID->kd = kd;
	PID->P = 0;
	PID->I = 0;
	PID->D = 0;
	PID->pid = 0;
	PID->error = 0;
	PID->pre_pv = 0;
}

void Get_Gyro_Error(void)
{
	uint16_t i;
	int16_t   accel_gyro[7];
	int check_time = 500;
	
	for(i=0; i< check_time; i++){
		MPU6050_GetRawAccelGyro(accel_gyro);
		gyro_errorZ += accel_gyro[5];
	}
	gyro_errorZ /= check_time;
}

void Sys_Init(void)
{
	// SETUP
	delay_init();
	Motor_Init();
	//USART1_Init(9600);
	IRSensor_Init();
	MPU6050_Initialize();
	
	// SetFullScaleGyroRange
	MPU6050_SetFullScaleGyroRange(MPU6050_GYRO_FS_2000);
	
	// Set LSB
	if(MPU6050_GetFullScaleGyroRange() == 0){
		LSB = 131.0;
	}
	if(MPU6050_GetFullScaleGyroRange() == 1){
		LSB = 65.5;
	}
	if(MPU6050_GetFullScaleGyroRange() == 2){
		LSB = 32.8;
	}
	if(MPU6050_GetFullScaleGyroRange() == 3){
		LSB = 16.4;
	}
	delay_ms(1000);
	// Get Gyro Error
	Get_Gyro_Error();
	
	// PID
	PID_Init(&PID_Yaw, 0.22, 0.01, 0.009);
	
	// Turn on IRSensor
	TurnOn_Transmitter(ALL_TRAN_LEDS);
	delay_ms(10);
	Read_All_Sensors();
}
