#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"

#define ON 1
#define OFF 0
#define baseSpeed 60
#define turnSpeed 20

int count = 0;
int buttonState = OFF;
int lastButtonState = OFF;

void Sensor_Read_All();
void Read_Button();
void Turn_Left(int Speed_M_1, int Speed_M_2);
void Turn_Right(int Speed_M_1, int Speed_M_2);
void ForWard(int Speed);
void BackWard(int Speed);
void Run();

int Status_Robot = 0;
int S1, S2, S3, S4, S5;

int main(void)
{
	Delay_Init();
	Led_Init();
	Motor_Init();
	Button_Init();
	Sensor_Init();
	while (1)
	{
		Read_Button();
		Sensor_Read_All();
		Delay_ms(50);
		if (Status_Robot == ON)
		{
			Run();
		}
	}
}
void Run()
{
	int S = S1 * 10000 + S2 * 1000 + S3 * 100 + S4 * 10 + S5;

	switch (S)
	{
	case 11011:
		ForWard(baseSpeed + turnSpeed);
		break;
	case 01111:
		Turn_Left(baseSpeed, baseSpeed + turnSpeed); // re bang cach quay nguoc banh trai to do 80
		break;
	case 11110:
		Turn_Right(baseSpeed + turnSpeed, baseSpeed); // re bang cach quay nguoc banh phai to do 80
		break;
	case 10111:
		Turn_Left(baseSpeed, baseSpeed - turnSpeed); // re bang cach quay nguoc banh trai to do 40
		break;
	case 11101:
		Turn_Right(baseSpeed - turnSpeed, baseSpeed); // re bang cach quay nguoc banh phai to do 40
		break;
	case 00111:
		Turn_Left(baseSpeed, baseSpeed); // re bang cach quay nguoc banh trai to do 60
		break;
	case 11100:
		Turn_Right(baseSpeed, baseSpeed); // re bang cach quay nguoc banh phai to do 60
		break;
	default:
		BackWard(baseSpeed);
		break;
	}
}
void Read_Button()
{
	int reading = Button_Read(BUTTON_ONOFF);
	if (reading != lastButtonState)
	{
		Delay_ms(200);
		if (reading != buttonState)
		{
			buttonState = reading;
			if (buttonState == OFF)
			{
				count++;
				count %= 2;
				Status_Robot = count;
			}
		}
	}
	lastButtonState = reading;
}
void Sensor_Read_All()
{
	S1 = Sensor_Read(SENSOR_PIN1);
	S2 = Sensor_Read(SENSOR_PIN2);
	S3 = Sensor_Read(SENSOR_PIN3);
	S4 = Sensor_Read(SENSOR_PIN4);
	S5 = Sensor_Read(SENSOR_PIN5);
}
void ForWard(int Speed)
{
	Motor_SetForward(MOTOR_1, Speed);
	Motor_SetForward(MOTOR_2, Speed);
}
void BackWard(int Speed)
{
	Motor_SetBackward(MOTOR_1, Speed);
	Motor_SetBackward(MOTOR_2, Speed);
}
void Turn_Left(int Speed_M_1, int Speed_M_2)
{
	Motor_SetForward(MOTOR_1, Speed_M_1);
	Motor_SetBackward(MOTOR_2, Speed_M_2);
}
void Turn_Right(int Speed_M_1, int Speed_M_2)
{
	Motor_SetBackward(MOTOR_1, Speed_M_1);
	Motor_SetForward(MOTOR_2, Speed_M_2);
}