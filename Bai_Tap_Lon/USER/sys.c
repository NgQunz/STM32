#include "sys.h"

SystemState systemState;
ButtonState buttonState;


void System_Init(void) 
{
    Timer2_Init(); // init timer 2 for delay
	
    GPIO_init(); // init gpio for led and button
	
		USART1_Init(115200); // init usart1 for debug 9600 / 115200 / 57600 baudrate 
		
    Delay_ms(500);
    I2C2_LCD_Init(); // init i2c2 for lcd
    LCD_Init(); // init lcd
    LCD_Clear(); // clear lcd
		LCD_Send_String("Nam ngu");
    Delay_ms(1000);

    MMA845_I2C_Init(); // init i2c1 for mma845
    Delay_ms(10);
    MMA845_Init(); // init mma845
    Delay_ms(10);
    MMA845_Calibrate();
    USART1_Send_String("MMA845 initialized\r\n");

    // Initialize system state
    systemState.stepCount = 0;
    systemState.lastStepTime = 0;
    systemState.lastTotalAccel = 1.0f;
    systemState.isPeak = 0;
    systemState.accelX = 0;
    systemState.accelY = 0;
    systemState.accelZ = 0;
    systemState.totalAccel = 0;
    systemState.STEP_THRESHOLD = 0.05f; 

    // Initialize button state
		buttonState.cnt_button_stop =0;
    buttonState.cnt_button_start = 0;

    LED_PORT_START -> ODR &= ~LED_START;
    LED_PORT_STOP -> ODR &= ~LED_STOP;

}

void System_Run(void)
{
    button_status();

    if (buttonState.flag_stop) {
        // Reset system state
        systemState.stepCount = 0;
        LED_PORT_START->ODR &= ~LED_START;
        LED_PORT_STOP->ODR &= ~LED_STOP;
        buttonState.flag_start = 0;
        buttonState.flag_stop  = 0;
        LCD_Clear();
        USART1_Send_String("System reset\r\n");
    }

    if (flag_check && buttonState.flag_start) {
        float X, Y, Z;
        MMA845_ReadAccel(&X, &Y, &Z);
        float total = sqrtf(X * X + Y * Y + Z * Z);
        ProcessStepDetection(Z);
        Display_count(systemState.stepCount);
        Display_LCD(total);
        flag_check = 0; // Reset flag after processing
    }
    if (buttonState.flag_start) {
        Blink_LED();
    }
}

void ProcessStepDetection(float totalAccel) {
    uint32_t current_time = millis();
    if (current_time - systemState.lastStepTime < 100) {
        return;
    }
    if (fabs(totalAccel - systemState.lastTotalAccel) > systemState.STEP_THRESHOLD) {
        systemState.stepCount++;
        systemState.lastStepTime = current_time;
        USART1_Send_String("Step detected! Count: ");
        USART1_Send_Number(systemState.stepCount);
        USART1_Send_String("\r\n");
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

void Blink_LED(void)
{
    static uint32_t last_toggle = 0;
    uint32_t current_time = millis();
    if (current_time - last_toggle > 1000) {
        LED_PORT_START->ODR ^= LED_START;
        last_toggle = current_time;
    }
}

void button_status(void)
{
    buttonState.status_button_Start = Read_Pin(BUTTON_START);
    buttonState.status_button_Stop = Read_Pin(BUTTON_STOP);

    if (buttonState.status_button_Start == 0) {
        buttonState.cnt_button_start++;
        Delay_ms(50); // Debounce
        if (buttonState.cnt_button_start % 2 == 1) {
            buttonState.flag_start = 1;
            LED_PORT_START->ODR |= LED_START;
            LED_PORT_STOP->ODR &= ~LED_STOP;
            USART1_Send_String("System started\r\n");
        } else {
            buttonState.flag_start = 0;
            LED_PORT_START->ODR &= ~LED_START;
            LED_PORT_STOP->ODR |= LED_STOP;
            USART1_Send_String("System stopped\r\n");
        }
    }

    if (buttonState.status_button_Stop == 0) {
        buttonState.flag_stop = 1;
        Delay_ms(50); // Debounce
    }
}


