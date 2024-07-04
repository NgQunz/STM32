#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"

int speedMax = 80;
int speed3 = 0.8 *speedMax;
int speed2 = 0.4 *speedMax;
int speed1 = 0.2 *speedMax;

void RePhai(int motor1, int motor2){
    Motor_SetForward(MOTOR_1, motor1);
    Motor_SetForward(MOTOR_2, motor2);
}

void ReTrai(int motor1, int motor2){
    Motor_SetForward(MOTOR_2, motor2);
    Motor_SetForward(MOTOR_1, motor1);
}

void diThang(int motor1, int motor2){
    Motor_SetForward(MOTOR_1, motor1);
    Motor_SetForward(MOTOR_2, motor2);
}

uint16_t SensorRead(uint16_t pin){
    if(GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
        return SENSOR_ON;
    else
        return SENSOR_OFF;
}

int main(void){
    Delay_Init();
    Led_Init();
    Motor_Init();
    Button_Init();
    Sensor_Init();

    while(1){
        uint8_t sensor1 = Sensor_Read(SENSOR_PIN1);
        uint8_t sensor2 = Sensor_Read(SENSOR_PIN2);
        uint8_t sensor3 = Sensor_Read(SENSOR_PIN3);
        uint8_t sensor4 = Sensor_Read(SENSOR_PIN4);
        uint16_t sensor5 = SensorRead(SENSOR_PIN5);
        int line_state = (sensor1 << 4) | (sensor2 << 3) | (sensor3 << 2) | (sensor4 << 1) | sensor5;

            switch(line_state) {
                case 0b11011: 
                    diThang(speedMax,speedMax);
                    break;
								case 0b11101:
                    ReTrai(speed3,speedMax);
                    break;
								case 0b11110:
									  ReTrai(speed2,speedMax);
                    break;
								case 0b11000:
										RePhai(speedMax,speed1);
										break;
								case 0b10111:
										RePhai(speedMax,speed3);
                    break;
								case 0b01111:
										RePhai(speedMax,speed2);
                    break;
								case 0b00011:
										ReTrai(speed1,speedMax);
                    break;
								default:
										break;
            }
    }
}
