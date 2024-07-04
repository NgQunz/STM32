#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"
#include "uart.h"

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
void Stop();
void Previous();
void USART_PRINT();
int status_previous=0,sensors_previous=0,status_previous_flag=0;

int Status_Robot = 0;
int S1, S2, S3, S4, S5;

int main(void)
{
	
	Delay_Init();
	Led_Init();
	Motor_Init();
	Button_Init();
	Sensor_Init();
	USART_config();
	GPIO_Config_TX_RX();
	
	while (1)
	{
		//Read_Button();
		
		Sensor_Read_All();
		//Run();
//		if (Status_Robot == ON)
//		{
			Run();
		//}
	}
}
void Run()
{
	int S =S2 * 100 + S3 * 10 + S4;
	if (sensors_previous!=S)
	{
		sensors_previous=S;
		USART_PRINT();
	}
	switch (S)
	{
	case 11011:
		ForWard(baseSpeed);
		break;
	case 11001:
		ForWard(baseSpeed);
		break;
	case 10011:
		ForWard(baseSpeed);
		break;
	case 1111:   // 01111
		Turn_Left(40, 4);
		break;
	case 11110:
		Turn_Right(4, 40);
		break;
	case 1011:   //01011
		Turn_Left(40, 4);
		break;
	case 11010:
		Turn_Right(4, 40);
		break;
	case 10111:
		Turn_Left(40, 4);
		break;
	case 11101:
		Turn_Right(4, 40);
		break;
	case 111: // 00111
		Turn_Left(40, 4);
		break;
	case 11100:
		Turn_Right(4, 40);
		break;
	case 11:  //00011
		Turn_Left(40, 4);
		break;
	case 11000:
		Turn_Right(4, 40);
		break;
	case 11111:
		if (status_previous_flag!= status_previous) {UARTPrintf_Number(status_previous);}
		Previous();
		break;
	case 00000:
		Stop();
		break;
	default:
		Previous();
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
	S1=0,S2=0,S3=0,S4=0,S5=0;
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
	status_previous=2;
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
	status_previous=3;
}
void Turn_Right(int Speed_M_1, int Speed_M_2)
{
	Motor_SetBackward(MOTOR_1, Speed_M_1);
	Motor_SetForward(MOTOR_2, Speed_M_2);
	status_previous=4;
	
}
void Stop()
{
	Motor_SetStopping(MOTOR_1);
	Motor_SetStopping(MOTOR_2);
}
void Previous()
{
	
	if (status_previous == 2) ForWard(80);
	else if (status_previous == 3) Turn_Left(40, 4);
	else if (status_previous == 4) Turn_Right(4, 40);
}
void USART_PRINT()
{
	UARTPrintf_Number(S1);
	UARTPrintf_Number(S2);
	UARTPrintf_Number(S3);
	UARTPrintf_Number(S4);
	UARTPrintf_Number(S5);
	uart_SendStr("\n");
}
