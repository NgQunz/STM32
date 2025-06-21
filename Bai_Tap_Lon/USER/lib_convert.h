#ifndef __CONVERT_H
#define __CONVERT_H


#include "stdint.h"
#include "stdio.h"

typedef union 
{
  int data_int;
  uint8_t data_bytes[4];
} data_convert_int_and_bytes;

typedef union
{
  float data_float;
  uint8_t data_bytes[4];
} data_convert_float_and_bytes;

typedef union
{
  uint16_t data_uint16;
  uint8_t data_bytes[2];
} data_convert_uint16_and_bytes;

typedef union {
    int16_t value;
    uint8_t bytes[2];
} data_convert_14bit;
      
uint8_t *Convert_Int_To_Bytes(int data);
uint8_t *Convert_Float_To_Bytes(float data);
uint8_t *Convert_Uint16_To_Bytes(uint16_t data);
int Convert_Bytes_To_Int(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
float Convert_Bytes_To_Float(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
uint16_t Convert_Bytes_To_Uint16(uint8_t data1, uint8_t data2);
int16_t Convert_14bit_To_Int16(uint8_t msb, uint8_t lsb);
float Convert_14bit_To_Float(uint8_t msb, uint8_t lsb);

#endif

