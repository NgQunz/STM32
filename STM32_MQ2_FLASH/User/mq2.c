#include "MQ2.h"
#include <math.h>

// Ham khoi tao cam bien MQ2 su dung kenh ADC1 Channel 0 (PA0)
void MQ2_Init(void) {
    ADC_InitTypeDef ADC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    // Bat dong ho cho ngo vao GPIOA va bo ADC1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

    // Cau hinh chan PA0 o che do analog (chan nay ket noi voi chan analog cua cam bien MQ2)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;              // Chon chan PA0
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;          // Analog input
    GPIO_Init(GPIOA, &GPIO_InitStruct);                 // Khoi tao GPIOA

    // Cau hinh ADC1 hoat dong doc mot kenh duy nhat, lien tuc
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;         // Su dung ADC doc lap
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;              // Khong quet nhieu kenh
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;         // Che do chuyen doi lien tuc
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // Khong dung trigger ngoai
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;     // Can le phai (du lieu 12 bit)
    ADC_InitStruct.ADC_NbrOfChannel = 1;                    // Chi su dung 1 kenh ADC
    ADC_Init(ADC1, &ADC_InitStruct);                        // Khoi tao ADC1

    // Cau hinh kenh ADC so 0 (PA0) voi thoi gian lay mau
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

    // Bat ADC1
    ADC_Cmd(ADC1, ENABLE);

    // Thuc hien hieu chinh ADC de dam bao do chinh xac
    ADC_ResetCalibration(ADC1);                             // Reset lai viec hieu chinh
    while (ADC_GetResetCalibrationStatus(ADC1));            // Cho den khi hoan tat
    ADC_StartCalibration(ADC1);                             // Bat dau hieu chinh
    while (ADC_GetCalibrationStatus(ADC1));                 // Cho den khi hoan tat

    // Bat dau chuyen doi ADC lien tuc
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

// Ham doc gia tri tu cam bien MQ2 va chuyen doi sang don vi ppm (parts per million)
uint32_t MQ2_Read_ppm(void) {
    // Cho den khi viec chuyen doi hoan tat
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    // Lay gia tri ADC (0 - 4095 tuong ung voi 0V - 3.3V)
    uint16_t adc_value = ADC_GetConversionValue(ADC1);

    // Chuyen gia tri ADC sang dien ap (V = ADC_value * 3.3 / 4095)
    float voltage = (adc_value * 3.3) / 4095.0;

    // Kiem tra neu dien ap = 0 (co the do cam bien khong hoat dong)
    if (voltage == 0.0) {
        return 0; // Tra ve 0 ppm hoac thong bao loi tuy truong hop
    }

    // Tinh dien tro RS (Rs = [(Vcc * RL) / Vo] - RL)
    // Vcc = 5V, RL = 10k ohm, Vo = dien ap doc duoc
    double RS = ((5.0 * 10000.0) / voltage) - 10000.0;

    // Gia tri R0 la dien tro trong khong khi sach (da duoc hieu chinh truoc do)
    double R0 = 10000.0;

    // ppm = 10 ^ { [log10(RS / R0) - b] / m }
    // b va m la he so duoc lay tu datasheet cua cam bien MQ2 (tra bang do thi)
    double b = 1.24;    // He so dich tren do thi log-log
    double m = -0.455;  // Do doc cua do thi log-log
    double ppm = pow(10.0, (log10(RS / R0) - b) / m);

    return (uint32_t)ppm; 
}
