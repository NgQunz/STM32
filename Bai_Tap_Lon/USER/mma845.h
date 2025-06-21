#ifndef __MMA845__
#define __MMA845__

#include "i2c1.h"
#include "uart.h"
#include "tim2.h"
#include <math.h>
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define CALC_THRESHOLD_HEX(g_threshold_times_1000) ((uint8_t)(g_threshold_times_1000))
#define CALCULATE_MOTION_COUNT(debounce_time_ms) ((uint8_t)(((uint32_t)(debounce_time_ms) * 400) / 1000))


// Device address (SA0 connected to GND)
#define MMA845_ADDR     (0x1C << 1)

// Register addresses
#define WHO_AM_I        0x0D
#define XYZ_DATA_CFG    0x0E
#define CTRL_REG1       0x2A
#define CTRL_REG2       0x2B
#define OUT_X_MSB       0x01
#define OUT_X_LSB       0x02
#define OUT_Y_MSB       0x03
#define OUT_Y_LSB       0x04
#define OUT_Z_MSB       0x05
#define OUT_Z_LSB       0x06
#define STATUS          0x00

// Range configuration
#define RANGE_2G        0x00    // ±2g range
#define RANGE_4G        0x01    // ±4g range
#define RANGE_8G        0x02    // ±8g range

// Scale factors for different ranges (in g/LSB)
#define SCALE_2G        (1.0/4096.0)    // 2g range = 4g/16384
#define SCALE_4G        0.000488    // 4g range = 8g/16384
#define SCALE_8G        0.000976    // 8g range = 16g/16384

// Data rate configuration
#define DR_800HZ        0x00
#define DR_400HZ        0x08
#define DR_200HZ        0x10
#define DR_100HZ        0x18
#define DR_50HZ         0x20

// mode configuration
#define MODE_ACTIVE     0x01
#define MODE_STANDBY    0x00
#define CTRL_REG4       0x2D   // Interrupt Enable Register
#define CTRL_REG5       0x2E  // Interrupt Pin Mapping Register

// transient mode 
#define TRANSIENT_CFG   0x1D 
#define TRANSIENT_THS   0x1F 
#define TRANSIENT_COUNT	0x20

// Motion Detection Configuration
#define FF_MT_THS       0x17    // Threshold register
#define FF_MT_COUNT     0x18    // Debounce counter
#define FF_MT_CFG       0x15    // Motion configuration

// INTERRUPT 
#define INT_SOURCE		0x0C 
	
// Function declarations
void MMA845_Init(void);
void MMA845_ReadAccel(float *x, float *y, float *z);
uint8_t MMA845_TestConnection(void);
void MMA845_Debug_Print(void);
void MMA845_Calibrate(void);
void MMA845_Read_Z(float z);


#endif
