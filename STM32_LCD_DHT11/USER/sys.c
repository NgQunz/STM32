#include "sys.h"

SystemState systemState;

void System_Init(void) 
{
    I2C2_LCD_Init(); // Init I2C2 for LCD
    LCD_Init(); // Init LCD
    LCD_Clear(); // Clear LCD
    LCD_Send_String("Initializing...");
    Delay_ms(1000);

    // Initialize system state
    systemState.stepCount = 0;
    systemState.lastTotalAccel = 1.0f;
    systemState.totalAccel = 0;
    systemState.STEP_THRESHOLD = 0.05f; 
}

void System_Run(void)
{
    float X=0, Y=0, Z=0;
    float total = sqrtf(X * X + Y * Y + Z * Z);
    ProcessStepDetection(Z);
    Display_count(systemState.stepCount);
    Display_LCD(19.5);
}

void ProcessStepDetection(float totalAccel) {
    if (fabs(totalAccel - systemState.lastTotalAccel) > systemState.STEP_THRESHOLD) {
        systemState.stepCount++;
    }
    systemState.lastTotalAccel = totalAccel;
}

void Display_LCD(float number)
{
    LCD_Set_Cursor(0, 0);
    LCD_Send_String("Total: ");
    LCD_Send_Float(number);
}

void Display_count(uint16_t number)
{
    LCD_Set_Cursor(0, 1);
    LCD_Send_String("Step Count: ");
    LCD_Send_Number(number);
}
