#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"
#include "uart.h"

void RePhai_Lui(double SpeedM1, double SpeedM2)
{
    Motor_SetForward(MOTOR_1, SpeedM1);
    // Motor_SetStopping(MOTOR_2);
    Motor_SetBackward(MOTOR_2, SpeedM2);
}
void ReTrai_Lui(double SpeedM1, double SpeedM2)
{
    Motor_SetForward(MOTOR_2, SpeedM2);
    // Motor_SetStopping(MOTOR_1);
    Motor_SetBackward(MOTOR_1, SpeedM1);
}
void RePhai(double SpeedM2, double SpeedM1)
{
    Motor_SetBackward(MOTOR_1, SpeedM1);
    // Motor_SetStopping(MOTOR_2);
    Motor_SetBackward(MOTOR_2, 15);
}
void ReTrai(double SpeedM2, double SpeedM1)
{
    Motor_SetBackward(MOTOR_2, SpeedM2);
    // Motor_SetStopping(MOTOR_1);
    Motor_SetBackward(MOTOR_1, SpeedM1);
}
void dithang(double SpeedM1)
{
    Motor_SetForward(MOTOR_1, SpeedM1);
    Motor_SetForward(MOTOR_2, SpeedM1);
}
uint16_t SensorRead(uint16_t pin)
{
    if (GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
        return SENSOR_ON;
    else
        return SENSOR_OFF;
}

uint16_t SensorRead(uint16_t pin);

int Converted_value[6];
int Sum = 0;
int old_sum = 0;

int Distance(int Converted_value[])
{
    int sum = 0;
    char i = 0;
    for (char k = 1; k <= 5; k++) // 8 sensor
    {
        if (Converted_value[k] == 0) // Black line
        {
            i++;
            sum = sum + k * 100;
        }
    }

    if ((i > 0) && (i < 5))
    {
        old_sum = sum / i;
        return old_sum;
    }
    else if (i == 5) // all line ?
    {
        return old_sum;
    }
    else // no line ?
    {
        //    if ( (200 < old_sum ) && (old_sum < 400) )
        //      return 300;
        //    else
        return old_sum;
    }
}
void PID(uint16_t distance)
{
    int distance_error;
    //	float quy_doi=0.4;
    distance_error = 300 - distance;

    switch (distance)
    {
    case 100:
        Motor_SetBackward(MOTOR_1, 25);
        Motor_SetForward(MOTOR_2, 60);
        break;
    case 200:
        Motor_SetForward(MOTOR_2, 60); // ben phai // co the tang
        Motor_SetForward(MOTOR_1, 25); // trai
        break;
    case 300:
        dithang(80);
        break;
    case 400:
        Motor_SetForward(MOTOR_1, 60); // co the tang
        Motor_SetBackward(MOTOR_2, 25);
        break;
    case 500:
        Motor_SetForward(MOTOR_1, 60);
        Motor_SetBackward(MOTOR_2, 25);
        break;
    case 150:
        Motor_SetBackward(MOTOR_1, 25);
        Motor_SetForward(MOTOR_2, 60);
        break;
    case 250:
        Motor_SetForward(MOTOR_2, 60); // ben phai  // k dc thif ve 50
        Motor_SetForward(MOTOR_1, 25); // trai
        break;
    case 350:
        Motor_SetForward(MOTOR_1, 60); // k dc thif ve 50
        Motor_SetForward(MOTOR_2, 25);
        break;
    case 450:
        Motor_SetForward(MOTOR_1, 60);
        Motor_SetBackward(MOTOR_2, 25);
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
    USART_config();
    GPIO_Config_TX_RX();
    UARTPrintf_Number(20);
    uint16_t i = 0;
    // Motor_SetForward(1 ,30);
    while (1)
    {
        Converted_value[1] = Sensor_Read(SENSOR_PIN1);
        Converted_value[2] = Sensor_Read(SENSOR_PIN2);
        Converted_value[3] = Sensor_Read(SENSOR_PIN3);
        Converted_value[4] = Sensor_Read(SENSOR_PIN4);
        Converted_value[5] = SensorRead(SENSOR_PIN5);

        Sum = Distance(Converted_value); // return sum based on Converted_value
        PID(Sum);
    }
}