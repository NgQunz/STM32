//#include "led.h"
//#include "delay.h"
//#include "motor.h"
//#include "button.h"
//#include "sensor.h"

//int Converted_value[6];
//int Sum = 0;
//int old_sum = 0,previous_sum=0;

//void MoveForward(int speed)
//{
//    Motor_SetForward(MOTOR_1, speed);
//    Motor_SetForward(MOTOR_2, speed);
//}
//void TurnLeft (int SpeedM1,int SpeedM2)
//{
//		Motor_SetBackward(MOTOR_1, SpeedM1);
//    Motor_SetForward(MOTOR_2, SpeedM2);
//}
//void TurnRight(int SpeedM1,int SpeedM2)
//{
//		Motor_SetForward(MOTOR_1, SpeedM1);
//		Motor_SetBackward(MOTOR_2, SpeedM2);
//}

//int Distance(int Converted_value[])
//{
//    int sum = 0;
//    char i = 0;
//    for (char k = 1; k <= 5; k++) 
//    {
//        if (Converted_value[k] == 0) // Black line
//        {
//            i++;
//            sum = sum + k * 100;
//        }
//    }
//    if ((i > 0) && (i < 5))
//    {
//				if (i!=1)
//				{
//						previous_sum=old_sum;
//				}
//        old_sum = sum / i;
//        return old_sum;
//    }
//    else if (i == 5 && old_sum==300) // all line ?
//    {
//        return previous_sum;
//    }
//		else if (i == 5 && old_sum!=300)
//		{
//			return old_sum;
//		}
//    else // no line ?
//    {
//        if ( (200 < old_sum ) && (old_sum < 400) )
//          return 300;
//        else
//			
//					return old_sum;
//				
//    }
//}
//int speed1=65,speed2=25;
//void Control(uint16_t distance)
//{

//    switch (distance)
//    {
//    case 100:
//        TurnLeft(speed2,speed1);
//        break;
//    case 200:
//        TurnLeft(speed2,speed1);
//        break;
//    case 300:
//        MoveForward(80);
//        break;
//    case 400:
//        TurnRight(speed1,speed2);
//        break;
//    case 500:
//        TurnRight(speed1,speed2);
//        break;
//    case 150:
//        TurnLeft(speed2,speed1);
//        break;
//    case 250:
//        TurnLeft(speed2,speed1);
//        break;
//    case 350:
//        TurnRight(speed1,speed2);
//        break;
//    case 450:
//        TurnRight(speed1,speed2);
//        break;
//    default:
//        break;
//    }
//}
//int main(void)
//{
//    Delay_Init();
//    Led_Init();
//    Motor_Init();
//    Button_Init();
//    Sensor_Init();
//    while (1)
//    {
//        Converted_value[1] = Sensor_Read(SENSOR_PIN1);
//        Converted_value[2] = Sensor_Read(SENSOR_PIN2);
//        Converted_value[3] = Sensor_Read(SENSOR_PIN3);
//        Converted_value[4] = Sensor_Read(SENSOR_PIN4);
//        Converted_value[5] = Sensor_Read(SENSOR_PIN5);

//        Sum = Distance(Converted_value); // return sum based on Converted_value
//        Control(Sum);
//    }
//}
#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"
int Converted_value[6];
int Sum = 0;
int old_sum = 0,previous_sum=0;
int button_status=0,reading_button=0;    // Tr?ng th�i hi?n t?i c?a button
int lastButtonState = 0;
void Off_All()
{
	Led_Off(LED_1);
	Led_Off(LED_2);
	Led_Off(LED_3);
	Led_Off(LED_4);
}
void On_1()
{
	Led_On(LED_1);
	Led_Off(LED_2);
	Led_Off(LED_3);
	Led_Off(LED_4);
}
void On_2()
{
	Led_Off(LED_1);
	Led_On(LED_2);
	Led_Off(LED_3);
	Led_Off(LED_4);
}
void On_3()
{
	Led_Off(LED_1);
	Led_Off(LED_2);
	Led_On(LED_3);
	Led_Off(LED_4);
}
void On_4()
{
	Led_Off(LED_1);
	Led_Off(LED_2);
	Led_Off(LED_3);
	Led_On(LED_4);
}
void MoveForward(int speed)
{
    Motor_SetForward(MOTOR_1, speed);
    Motor_SetForward(MOTOR_2, speed);
}
void TurnLeft (int SpeedM1,int SpeedM2)
{
		Motor_SetBackward(MOTOR_1, SpeedM1);
    Motor_SetForward(MOTOR_2, SpeedM2);
}
void TurnRight(int SpeedM1,int SpeedM2)
{
		Motor_SetForward(MOTOR_1, SpeedM1);
		Motor_SetBackward(MOTOR_2, SpeedM2);
}


int Distance(int Converted_value[])
{
	Off_All();
    int sum = 0;
    char i = 0;
    for (char k = 1; k <= 5; k+=2) // 8 sensor
    {
        if (Converted_value[k] == 0) // Black line
        {
            i++;
            sum = sum + k * 100;
        }
    }
	if (i!=1)
	{
		previous_sum=old_sum;
	}
    if ((i > 0) && (i < 5))
    {
        old_sum = sum / i;
        return old_sum;
    }
    else if (i == 5 && old_sum==300) // all line ?
    {
        return previous_sum;
    }
	else if (i == 5 && old_sum!=300)
	{
		return old_sum;
	}
    else // no line ?
    {
        if ( (200 < old_sum ) && (old_sum < 400) )
          	return 300;
        else	
			return old_sum;
			
    }
}

void Control(uint16_t distance)
{
	Off_All();
	switch (distance)
	{
	case 100:
		Motor_SetBackward(MOTOR_1, 30);
		Motor_SetForward(MOTOR_2, 70);
		
		break;
	case 200:
		Motor_SetBackward(MOTOR_1, 10);
		Motor_SetForward(MOTOR_2, 60); 
		
		break;
	case 300:
		MoveForward(80);
		//On_1();
		break;
	case 400:
		Motor_SetForward(MOTOR_1, 70); // co the tang
		Motor_SetBackward(MOTOR_2, 40);
	
		On_2();
			break;
	case 500:
		Motor_SetForward(MOTOR_1, 70);
		Motor_SetBackward(MOTOR_2, 40);
		On_4();
		break;
	case 150:
		Motor_SetBackward(MOTOR_1, 20);
		Motor_SetForward(MOTOR_2, 70);
		//On_2();
		break;
	case 250:
		Motor_SetBackward(MOTOR_1, 0); // trai
		Motor_SetForward(MOTOR_2, 60); // ben phai  // k dc thif ve 50
//	On_1();
//		On_4();
		break;
	case 350:
		Motor_SetForward(MOTOR_1, 60); // k dc thif ve 50
		Motor_SetBackward(MOTOR_2, 0);
		On_1();
		break;
	case 450:
		Motor_SetForward(MOTOR_1, 70);
		Motor_SetBackward(MOTOR_2, 20);
		On_3();
		break;
	default:
		break;
	}
				
    
}
int main(void)
{
    Delay_Init();
    Led_Init();
    Motor_Init();
    Button_Init();
    Sensor_Init();
    while (1)
    {
        Converted_value[1] = Sensor_Read(SENSOR_PIN1);
        //Converted_value[2] = Sensor_Read(SENSOR_PIN2);
        Converted_value[3] = Sensor_Read(SENSOR_PIN3);
        //Converted_value[4] = Sensor_Read(SENSOR_PIN4);
        Converted_value[5] = Sensor_Read(SENSOR_PIN5);

        Sum = Distance(Converted_value); // return sum based on Converted_value
        Control(Sum);
    }
}