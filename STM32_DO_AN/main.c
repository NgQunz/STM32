#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "dwt_stm32_delay.h"
char temp1[20];
char rx_data[2];
int mode = 0;
int a;
uint32_t data;
uint8_t count;
uint8_t sv1, sv2;
TIM_HandleTypeDef htim1;
UART_HandleTypeDef huart1;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static void delay_us(uint32_t us);
// Nhan tín hieu ir
uint32_t receive_data(void)
{
    uint32_t code = 0;
    while (!(HAL_GPIO_ReadPin(IN1_GPIO_Port, IN1_Pin)))
        ; // wait for the pin to go high.. 9ms LOW
    while ((HAL_GPIO_ReadPin(IN1_GPIO_Port, IN1_Pin)))
        ; // wait for the pin to go low.. 4.5ms HIGH
    for (int i = 0; i < 32; i++)
    {
        count = 0;
        while (!(HAL_GPIO_ReadPin(IN1_GPIO_Port, IN1_Pin)))
            ;                                              // wait for pin to go high..this is 562.5us LOW
        while ((HAL_GPIO_ReadPin(IN1_GPIO_Port, IN1_Pin))) // count
            the space length while the pin is high
            {
                count++;
                delay_us(100); // DWT_Delay_us(100);
            }

        if (count > 12) // if the space is more than 1.2 ms
        {
            code |= (1UL << (31 - i)); // write 1
        }

        else
            code &= ~(1UL << (31 - i)); // write 0
    }

    return code;
}
uint8_t hb1, hb2, tb1, tb2;
uint16_t s, h, t;

float nhietdo = 0;
float doam = 0;
uint8_t rp = 0;

void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void DHT11_start()
{
    Set_Pin_Output(GPIOB, GPIO_PIN_12);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
    79

        delay_us(18000); // delay 18ms
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
    delay_us(20); // delay 20us
    Set_Pin_Input(GPIOB, GPIO_PIN_12);
}

uint8_t Check_response(void)
{
    uint8_t r = 0;
    delay_us(40);
    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
    {
        delay_us(80);
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
        {
            r = 1;
        }
        else
        {
            r = -1;
        }
    }
    while ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)))
        ;
    return r;
}
uint8_t DHT11_Read(void)
{
    uint8_t i, j;
    for (j = 0; j < 8; j++)
    {
        while (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)))
            ; // wait for
        the pin to go high
            delay_us(40);                            // wait for 40 us
        if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))) // if the pin is
            low
            {
                i &= ~(1 << (7 - j)); // write 0
            }
        else
            i |= (1 << (7 - j)); // if the pin is high, write 1
        while ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)))
            ; // wait for
        the pin to go low
    }
    return i;
    80
}
void get_DHT11()
{
    DHT11_start();
    rp = Check_response();
    hb1 = DHT11_Read();
    hb2 = DHT11_Read();
    tb1 = DHT11_Read();
    tb2 = DHT11_Read();
    s = DHT11_Read();

    t = tb1;
    h = hb1;

    nhietdo = (float)t;
    doam = (float)h;

    char str[20];
    sprintf(str, "nd:%d da:%d end", (int)nhietdo, (int)doam);
    HAL_UART_Transmit(&huart1, (uint8_t *)&str, sizeof(str), 1000);

    // delay_us(1000);
}
// diêu khien servo
void servo1_open()
{
    for (int i = 0; i < 20; i++)
    {
        HAL_GPIO_WritePin(OUT11_GPIO_Port, OUT11_Pin, 1);
        delay_us(1000);
        HAL_GPIO_WritePin(OUT11_GPIO_Port, OUT11_Pin, 0);
        delay_us(19000);
    }
    mode = 1;
}
void servo1_close()
{
    for (int i = 0; i < 20; i++)
    {
        HAL_GPIO_WritePin(OUT11_GPIO_Port, OUT11_Pin, 1);
        delay_us(2100);
        HAL_GPIO_WritePin(OUT11_GPIO_Port, OUT11_Pin, 0);
        delay_us(17900);
    }
    mode = 0;
    81
}
void servo2_open()
{
    for (int i = 0; i < 20; i++)
    {
        HAL_GPIO_WritePin(OUT12_GPIO_Port, OUT12_Pin, 1);
        delay_us(1000);
        HAL_GPIO_WritePin(OUT12_GPIO_Port, OUT12_Pin, 0);
        delay_us(19000);
    }
}
void servo2_close()
{
    for (int i = 0; i < 20; i++)
    {
        HAL_GPIO_WritePin(OUT12_GPIO_Port, OUT12_Pin, 1);
        delay_us(2100);
        HAL_GPIO_WritePin(OUT12_GPIO_Port, OUT12_Pin, 0);
        delay_us(17900);
    }
}
void USART1_IRQHandler(void)
{

    if (mode == 0)
    {
        a = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
        if (a == 1)
        {
            HAL_GPIO_WritePin(OUT9_GPIO_Port, OUT9_Pin, 1);
        }
        else
        {
            HAL_GPIO_WritePin(OUT9_GPIO_Port, OUT9_Pin, 0);
        }
    }

    // get_DHT11();

    HAL_UART_IRQHandler(&huart1);
    HAL_UART_Receive_IT(&huart1, (uint8_t *)rx_data, 1);

    if (rx_data[0] == '1')
    {
        HAL_GPIO_WritePin(OUT1_GPIO_Port, OUT1_Pin, 1);
    }
    if (rx_data[0] == '2')
    {
        HAL_GPIO_WritePin(OUT2_GPIO_Port, OUT2_Pin, 1);
    }
    82 if (rx_data[0] == '3')
    {
        HAL_GPIO_WritePin(OUT3_GPIO_Port, OUT3_Pin, 1);
    }
    if (rx_data[0] == '4')
    {
        HAL_GPIO_WritePin(OUT4_GPIO_Port, OUT4_Pin, 1);
    }
    if (rx_data[0] == '5')
    {
        HAL_GPIO_WritePin(OUT5_GPIO_Port, OUT5_Pin, 1);
    }
    if (rx_data[0] == '6')
    {
        HAL_GPIO_WritePin(OUT6_GPIO_Port, OUT6_Pin, 1);
    }
    if (rx_data[0] == 'a')
    {
        HAL_GPIO_WritePin(OUT1_GPIO_Port, OUT1_Pin, 0);
    }
    if (rx_data[0] == 'b')
    {
        HAL_GPIO_WritePin(OUT2_GPIO_Port, OUT2_Pin, 0);
    }
    if (rx_data[0] == 'c')
    {
        HAL_GPIO_WritePin(OUT3_GPIO_Port, OUT3_Pin, 0);
    }
    if (rx_data[0] == 'd')
    {
        HAL_GPIO_WritePin(OUT4_GPIO_Port, OUT4_Pin, 0);
    }
    if (rx_data[0] == 'e')
    {
        HAL_GPIO_WritePin(OUT5_GPIO_Port, OUT5_Pin, 0);
    }
    if (rx_data[0] == 'f')
    {
        HAL_GPIO_WritePin(OUT6_GPIO_Port, OUT6_Pin, 0);
    }
    if (rx_data[0] == 'A')
    {
        servo1_open();
    }
    if (rx_data[0] == 'B')
    {
        servo1_close();
    }
    if (rx_data[0] == 'C')
    {
        servo2_open();
    }
    if (rx_data[0] == 'D')
    {
        servo2_close();
    }
    HAL_GPIO_TogglePin(OUT10_GPIO_Port, OUT10_Pin);
}
/**************Ctr giao tiep LCD 16x2 4bit**********************/
void LCD_Enable(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
    delay_us(2000);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
    delay_us(2000);
}
void LCD_Send4Bit(unsigned char Data)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, Data & 0x01);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (Data >> 1) & 0x01);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (Data >> 2) & 0x01);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (Data >> 3) & 0x01);
    83
}
void LCD_SendCommand(unsigned char command)
{
    LCD_Send4Bit(command >> 4);
    LCD_Enable();
    LCD_Send4Bit(command);
    LCD_Enable();
}
void LCD_Clear()
{
    LCD_SendCommand(0x01);
    delay_us(2000);
}
void LCD_Gotoxy(unsigned char x, unsigned char y)
{
    unsigned char address;
    if (!y)
        address = (0x80 + x);
    else
        address = (0xc0 + x);
    delay_us(2000);
    LCD_SendCommand(address);
    delay_us(2000);
}
void LCD_PutChar(unsigned char Data)
{ // Ham Gui 1 Ki Tu
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
    LCD_SendCommand(Data);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
}
void LCD_Puts(char *s)
{ // Ham gui 1 chuoi ky tu
    while (*s)
    {
        LCD_PutChar(*s);
        s++;
    }
}
void LCD_Init()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);

    LCD_SendCommand(0x28); // giao thuc 8 bit, hien thi 2 hang, ki tu 5x8
    LCD_SendCommand(0x0C); // cho phep hien thi man hinh
    LCD_SendCommand(0x06); // tang ID, khong dich khung hinh
    LCD_SendCommand(0x01); // xoa toan bo khung hinh
}

// hien thi
void Hienthi()
{
    sprintf(temp1, "Nhiet do: %d", (int)nhietdo);
    LCD_Gotoxy(0, 0);
    LCD_Puts(temp1);
    sprintf(temp1, "Do am: %d", (int)doam);
    LCD_Gotoxy(0, 1);
    LCD_Puts(temp1);
}
int main(void)
{

    HAL_Init();
    SystemClock_Config();

    HAL_Delay(1000);

    MX_GPIO_Init();
    MX_TIM1_Init();
    MX_USART1_UART_Init();

    HAL_TIM_Base_Start(&htim1);
    HAL_UART_Receive_IT(&huart1, (uint8_t *)rx_data, 1);

    LCD_Init();

    while (1)
    {
        get_DHT11();
        Hienthi();

        while (HAL_GPIO_ReadPin(IN1_GPIO_Port, IN1_Pin))
            ; // wait for
        the pin to go low
            data = receive_data();

        if (data == 0x00FF30CF)
        {
            HAL_GPIO_TogglePin(OUT1_GPIO_Port, OUT1_
                                                   Pin);
        }
        85

            if (data == 0x00FF18E7)
        {
            HAL_GPIO_TogglePin(OUT2_GPIO_Port, OUT2_P
                                                   in);
        }

        if (data == 0x00FF7A85)
        {
            HAL_GPIO_TogglePin(OUT3_GPIO_Port, OUT3_
                                                   Pin);
        }

        if (data == 0x00FF10EF)
        {
            HAL_GPIO_TogglePin(OUT4_GPIO_Port, OUT4_
                                                   Pin);
        }

        if (data == 0x00FF38C7)
        {
            HAL_GPIO_TogglePin(OUT5_GPIO_Port, OUT5_
                                                   Pin);
        }

        if (data == 0x00FF5AA5)
        {
            HAL_GPIO_TogglePin(OUT6_GPIO_Port, OUT6_
                                                   Pin);
        }
        if (data == 0x00FF42BD)
        {
            sv1 = !sv1;
            if (sv1)
            {
                servo1_open();
            }
            else
            {
                servo1_close();
            }
        }
        if (data == 0x00FF4AB5)
        {
            sv2 = !sv2;
            if (sv2)
            {
                servo2_open();
            }
            else
            {
                servo2_close();
            }
        }
        HAL_Delay(300);
    }
}

/**
  * @brief System Clock Configuration
86
* @retval None
*/
void delay_us(uint32_t us)
{
    __HAL_TIM_SetCounter(&htim1, 0);
    while (__HAL_TIM_GetCounter(&htim1) < us)
        ;
}
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) !=
        HAL_OK)
    {
    }
}
Error_Handler();
/**
* @brief TIM1 Initialization Function
87
* @param None
* @retval None
*/
static void MX_TIM1_Init(void)
{
    /* USER CODE BEGIN TIM1_Init 0 */
    /* USER CODE END TIM1_Init 0 */
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    /* USER CODE BEGIN TIM1_Init 1 */
    /* USER CODE END TIM1_Init 1 */
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 72 - 1;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 0xffff - 1;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) !=
        HAL_OK)
    {
    }
    Error_Handler();
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) !=
        HAL_OK)
    {
        Error_Handler();
    }
    88
    /* USER CODE BEGIN TIM1_Init 2 */
    /* USER CODE END TIM1_Init 2 */
}
/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{
    /* USER CODE BEGIN USART1_Init 0 */
    /* USER CODE END USART1_Init 0 */
    /* USER CODE BEGIN USART1_Init 1 */
    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */
    /* USER CODE END USART1_Init 2 */
}
/**
89


  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, OUT10_Pin | OUT11_Pin | OUT12_Pin,
                      GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, OUT1_Pin | OUT2_Pin | OUT3_Pin | OUT4_Pin | OUT5_Pin | OUT6_Pin | OUT7_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, OUT8_Pin | OUT9_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : OUT10_Pin OUT11_Pin OUT12_Pin */
    GPIO_InitStruct.Pin = OUT10_Pin | OUT11_Pin | OUT12_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : OUT1_Pin OUT2_Pin OUT3_Pin OUT4_Pin
                             OUT5_Pin OUT6_Pin OUT7_Pin */
    GPIO_InitStruct.Pin = OUT1_Pin | OUT2_Pin | OUT3_Pin | OUT4_Pin | OUT5_Pin | OUT6_Pin | OUT7_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    90
        /*Configure GPIO pins : OUT8_Pin OUT9_Pin */
        GPIO_InitStruct.Pin = OUT8_Pin | OUT9_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    /*Configure GPIO pins : IN1_Pin IN2_Pin */
    GPIO_InitStruct.Pin = IN1_Pin | IN2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    /*Configure GPIO pin : PB12 PB13 PB14 PB15 */
    GPIO_InitStruct.Pin =
        GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    /*Configure GPIO pins : PA11 PA12 Pa15 */
    GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /*Configure GPIO pins : PB4 PB5 PB6 PB7 */
    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_15,
                      GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,
                      GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_RESET);
}
