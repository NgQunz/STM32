#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"

#define ON 1
#define OFF 0

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
    int weights[] = {-2, -1, 0, 1, 2};    // weights for each sensor
    int sensors[] = {S1, S2, S3, S4, S5}; // sensor readings
    int position = 0;                     // position of the line
    int total = 0;                        // total sensor value

    for (int i = 0; i < 5; i++)
    {
        position += weights[i] * (1 - sensors[i]); // invert sensor reading
        total += (1 - sensors[i]);                 // invert sensor reading
    }

    if (total != 0)
    {
        position /= total;
    }

    int baseSpeed = 60;
    int maxSpeed = 80;
    int speedDifference = maxSpeed - baseSpeed;

    if (position < 0)
    {
        // line is to the left
        Turn_Left(baseSpeed + speedDifference * (-position), baseSpeed);
    }
    else if (position > 0)
    {
        // line is to the right
        Turn_Right(baseSpeed, baseSpeed + speedDifference * position);
    }
    else
    {
        // line is straight ahead
        Drive(baseSpeed, baseSpeed);
    }
}
void Run()
{
    int weights[] = {-2, -1, 0, 1, 2};    // weights for each sensor
    int sensors[] = {S1, S2, S3, S4, S5}; // sensor readings
    int position = 0;                     // position of the line
    int total = 0;                        // total sensor value

    for (int i = 0; i < 5; i++)
    {
        position += weights[i] * sensors[i];
        total += sensors[i];
    }
    // 0 1 1 1 1
    //
    if (total != 0)
    {
        position /= total;
    }

    int baseSpeed = 60;
    int maxSpeed = 80;
    int speedDifference = maxSpeed - baseSpeed;

    if (position < 0)
    {
        // line is to the left
        Turn_Left(baseSpeed + speedDifference * (-position), baseSpeed);
    }
    else if (position > 0)
    {
        // line is to the right
        Turn_Right(baseSpeed, baseSpeed + speedDifference * position);
    }
    else
    {
        // line is straight ahead
        ForWard(maxSpeed, maxSpeed);
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