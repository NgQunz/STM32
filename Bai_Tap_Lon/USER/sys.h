#ifndef __SYS_H
#define __SYS_H

#include "stm32f10x.h"
#include "tim2.h"
#include "mma845.h"
#include "i2c_lcd.h"
#include <math.h>
#include "gpio.h"
#include "i2c1.h"

// System states
typedef struct {
    uint32_t stepCount;
    uint32_t lastStepTime;
    uint8_t isPeak;
    float accelX;
    float accelY;
    float accelZ;
    float totalAccel;
    float lastTotalAccel;  
    float STEP_THRESHOLD ; 
} SystemState;

typedef struct 
{
    uint16_t status_button_Start;
    uint16_t status_button_Stop;
    int16_t cnt_button_start;
    int16_t cnt_button_stop;
    uint8_t flag_start;
    uint8_t flag_stop;

} ButtonState;


extern int16_t cnt;
extern ButtonState buttonState;
extern SystemState systemState;
// Function prototypes
void System_Init(void);
void System_Run(void);
void ProcessStepDetection(float totalAccel);
void Blink_LED(void);
void button_status(void);
void Display_LCD(float number);
void Display_count(uint16_t number);

#endif
