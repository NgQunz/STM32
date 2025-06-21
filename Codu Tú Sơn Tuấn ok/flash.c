#include "flash.h"
#include "stm32f10x.h"


static void Flash_Unlock(void) {
    if (FLASH->CR & FLASH_CR_LOCK) {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

static void Flash_Lock(void) {
    FLASH->CR |= FLASH_CR_LOCK;
}

static void Flash_WaitBusy(void) {
    while (FLASH->SR & FLASH_SR_BSY);
}

static void Flash_ErasePage(uint32_t address) {
    Flash_WaitBusy();
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR = address;
    FLASH->CR |= FLASH_CR_STRT;
    Flash_WaitBusy();
    FLASH->CR &= ~FLASH_CR_PER;
}

static void Flash_WriteWord(uint32_t address, uint32_t data) {
    Flash_WaitBusy();
    FLASH->CR |= FLASH_CR_PG;

    *(volatile uint16_t*)address = (uint16_t)(data & 0xFFFF);
    Flash_WaitBusy();
    *(volatile uint16_t*)(address + 2) = (uint16_t)(data >> 16);
    Flash_WaitBusy();

    FLASH->CR &= ~FLASH_CR_PG;
}

void Flash_SaveValue(uint32_t address, uint32_t value) {
    Flash_Unlock();
    Flash_ErasePage(address);
    Flash_WriteWord(address, value);
    Flash_Lock();
}

uint32_t Flash_ReadValue(uint32_t address) {
    return *(volatile uint32_t*)address;
}
void Flash_SaveAll(uint16_t threshold, uint32_t interval, uint32_t lux_value)
{
    Flash_Unlock();
    Flash_ErasePage(FLASH_SAVE_ADDR);

    Flash_WriteWord(FLASH_SAVE_ADDR, (uint32_t)threshold);                  // offset 0
    Flash_WriteWord(FLASH_SAVE_ADDR + 4, interval);                         // offset 4
    Flash_WriteWord(FLASH_SAVE_ADDR + 8, lux_value);                        // offset 8

    Flash_Lock();
}
void Flash_ReadAll(uint16_t *threshold, uint32_t *interval, uint32_t *lux_value)
{
    *threshold = (uint16_t)(*(volatile uint32_t*)(FLASH_SAVE_ADDR));       // l?y 2 byte th?p
    *interval  = *(volatile uint32_t*)(FLASH_SAVE_ADDR + 4);
    *lux_value = *(volatile uint32_t*)(FLASH_SAVE_ADDR + 8);
}
