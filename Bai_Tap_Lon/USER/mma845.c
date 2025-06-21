#include "mma845.h"

static float x_offset = 0, y_offset = 0, z_offset = 0;
static uint8_t is_calibrated = 0;

void MMA845_Init(void)
{
	uint8_t data ;
        // Cấu hình sensor settings (±2g)

    data = 0x40;  // Set RST bit
    MMA845_I2C_ByteWrite(MMA845_ADDR, &data, CTRL_REG2);
    Delay_ms(10);

    // 3. Enter standby mode
    MMA845_I2C_BufferRead(MMA845_ADDR, &data, CTRL_REG1, 1);
    data &= ~0x01;  // Clear active bit
    MMA845_I2C_ByteWrite(MMA845_ADDR, &data, CTRL_REG1);

    data = RANGE_2G;
    MMA845_I2C_ByteWrite(MMA845_ADDR, &data, XYZ_DATA_CFG);

    // Cấu hình ngắt
    data = 0x04; // Enable motion interrupt
    MMA845_I2C_ByteWrite(MMA845_ADDR, &data, CTRL_REG4);

    data = 0x04; // Route to INT1 pin
    MMA845_I2C_ByteWrite(MMA845_ADDR, &data, CTRL_REG5);

    // Cấu hình cho Step Counting (Quan trọng)
    // a. Bật bộ lọc thông cao
    data = 0x10; // Enable HP filter for motion detection
    MMA845_I2C_ByteWrite(MMA845_ADDR, &data, CTRL_REG2);

    data = 0x05;
    MMA845_I2C_ByteWrite(MMA845_ADDR, &data, FF_MT_THS);

    // c. Cấu hình khử nhiễu (Ví dụ: 25ms với ODR 400Hz)
    data = 0x0A; // 10 samples (10 * 2.5ms = 25ms với ODR 400Hz)
    MMA845_I2C_ByteWrite(MMA845_ADDR, &data, FF_MT_COUNT);

    // d. Cấu hình FF_MT_CFG (Chỉ dùng trục Z)
    //data = 0x20; // 0b00100000 - Chỉ bật trục Z
		data = 0x20;
    MMA845_I2C_ByteWrite(MMA845_ADDR, &data, FF_MT_CFG);

    // 7. Exit standby mode - Set active and ODR (400Hz)
    data = 0x11; // Active mode | 400Hz ODR
    MMA845_I2C_ByteWrite(MMA845_ADDR, &data, CTRL_REG1);

    USART1_Send_String("MMA845 configuration complete\r\n");
}

uint8_t MMA845_TestConnection(void)
{
    uint8_t data;
    MMA845_I2C_BufferRead(MMA845_ADDR, &data, WHO_AM_I, 1);
    return (data == 0x2A); // Correct value for MMA8452Q
}


void MMA845_ReadAccel(float *x, float *y, float *z)
{
    uint8_t data[6];
    int16_t x_raw, y_raw, z_raw;
    
    MMA845_I2C_BufferRead(MMA845_ADDR, data, OUT_X_MSB, 6);
    
    x_raw = ((int16_t)(data[0] << 8 | data[1])) >> 4;
    y_raw = ((int16_t)(data[2] << 8 | data[3])) >> 4;
    z_raw = ((int16_t)(data[4] << 8 | data[5])) >> 4;

    *x = (float)x_raw * (float)SCALE_2G;
    *y = (float)y_raw * (float)SCALE_2G;
    *z = (float)z_raw * (float)SCALE_2G;

    if (is_calibrated) {
        *x -= x_offset;
        *y -= y_offset;
        *z -= z_offset;
    }
}

void MMA845_Calibrate(void)
{
    const int num_samples = 200;  // Increase samples for better calibration
    float x_sum = 0, y_sum = 0, z_sum = 0;
    float x_max = -16, x_min = 16;
    float y_max = -16, y_min = 16;
    float z_max = -16, z_min = 16;

    for (int i = 0; i < num_samples; i++) {
        float x_temp, y_temp, z_temp;
        MMA845_ReadAccel(&x_temp, &y_temp, &z_temp);
        
        // Track min/max values
        x_max = (x_temp > x_max) ? x_temp : x_max;
        x_min = (x_temp < x_min) ? x_temp : x_min;
        y_max = (y_temp > y_max) ? y_temp : y_max;
        y_min = (y_temp < y_min) ? y_temp : y_min;
        z_max = (z_temp > z_max) ? z_temp : z_max;
        z_min = (z_temp < z_min) ? z_temp : z_min;
        
        x_sum += x_temp;
        y_sum += y_temp;
        z_sum += z_temp;
        Delay_ms(3);
    }

    // Calculate offset using min/max values
    x_offset = (x_max + x_min) / 2.0f;
    y_offset = (y_max + y_min) / 2.0f;
    z_offset = ((z_max + z_min) / 2.0f) - 1.0f;
    
    is_calibrated = 1;

    USART1_Send_String("Calibration complete\r\n");
}


void MMA845_Read_Z(float z)
{
    uint8_t data[2];
    MMA845_I2C_BufferRead(MMA845_ADDR, data, OUT_Z_MSB, 2);
    z = (int16_t)((data[0] << 8) | data[1]) >> 4;

    z = z* SCALE_2G;
}
