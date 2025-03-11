#ifndef __DEFINE_H__
#define __DEFINE_H__
#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "stm32f10x_usart.h"

// Motor
// TIM4 - PWM // declare in motor.c
#define MOTOR_PORT       GPIOB
#define MOTOR_L_PIN1     GPIO_Pin_6
#define MOTOR_L_PIN2     GPIO_Pin_7
#define MOTOR_R_PIN1     GPIO_Pin_8
#define MOTOR_R_PIN2     GPIO_Pin_9

// MPU6050
#define MPU6050_I2C                  I2C2
#define MPU6050_I2C_RCC_Periph       RCC_APB1Periph_I2C2
#define MPU6050_I2C_Port             GPIOB
#define MPU6050_I2C_SCL_Pin          GPIO_Pin_10
#define MPU6050_I2C_SDA_Pin          GPIO_Pin_11
#define MPU6050_I2C_RCC_Port         RCC_APB2Periph_GPIOB
#define MPU6050_I2C_Speed            100000 // 100kHz standard mode
	
// Receive led
#define REC_LED_R2       GPIO_Pin_4  // GPIOA    //ADC_Channel_4
#define REC_LED_R1       GPIO_Pin_5  // GPIOA    //ADC_Channel_5
#define REC_LED_R0       GPIO_Pin_6  // GPIOA    //ADC_Channel_6
#define REC_LED_L0       GPIO_Pin_7  // GPIOA    //ADC_Channel_7
#define REC_LED_L1       GPIO_Pin_0  // GPIOB    //ADC_Channel_8
#define REC_LED_L2       GPIO_Pin_1  // GPIOB    //ADC_Channel_9

// Transmitter led
#define TRAN_LED_PORT     GPIOB
#define TRAN_LED_L2       GPIO_Pin_3
#define TRAN_LED_L1       GPIO_Pin_4
#define TRAN_LED_L0       GPIO_Pin_5
#define TRAN_LED_R0       GPIO_Pin_12
#define TRAN_LED_R1       GPIO_Pin_13
#define TRAN_LED_R2       GPIO_Pin_14
#define ALL_TRAN_LEDS     TRAN_LED_L2 | TRAN_LED_L1 | TRAN_LED_L0 | TRAN_LED_R0 | TRAN_LED_R1 | TRAN_LED_R2


#ifdef __cplusplus
}
#endif
#endif
