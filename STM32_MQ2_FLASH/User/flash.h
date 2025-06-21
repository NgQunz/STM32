#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

#define FLASH_SAVE_ADDR  0x0801FC00  // �?a ch? cu?i flash (ch?nh n?u b?n d�ng flash nh? hon)

void Flash_SaveValue(uint32_t address, uint32_t value);
uint32_t Flash_ReadValue(uint32_t address);

#endif
