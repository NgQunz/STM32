#ifndef __SYS_H
#define __SYS_H

#include "stm32f10x.h"
#include "i2c_lcd.h"
#include <math.h>

// System states
typedef struct {
    uint32_t stepCount;
    float totalAccel;
    float lastTotalAccel;  
    float STEP_THRESHOLD;
} SystemState;

extern SystemState systemState;

// Function prototypes
void System_Init(void);
void System_Run(void);
void ProcessStepDetection(float totalAccel);
void Display_LCD(float number);
void Display_count(uint16_t number);

#endif
