/******************************************************************************
 *  Includes
 *****************************************************************************/

#include "MKL46Z4.h"
#include "FLASH.h"

/******************************************************************************
 *  Function definitions
 *****************************************************************************/

/*
 *  FLASH_ProgramLongword()
 */

void FLASH_ProgramLongword(uint32_t address, uint8_t *data)
{
    // Wait until previous command complete
    while (!(FTFA->FSTAT & 0x80))
    {
    }
    // Disable interrupts
    __disable_irq();
    // Clear previous command error
    if (FTFA->FSTAT & 0x30 == 0x30)
    {
        FTFA->FSTAT = 0x30;
    }
    // Flash Command
    FTFA->FCCOB0 = COMMAND_PROGRAM_LONGWORD;
    // Flash Address
    FTFA->FCCOB1 = address >> 16;
    FTFA->FCCOB2 = address >> 8;
    FTFA->FCCOB3 = address;
    // Flash Data
    FTFA->FCCOB4 = data[3];
    FTFA->FCCOB5 = data[2];
    FTFA->FCCOB6 = data[1];
    FTFA->FCCOB7 = data[0];
    // Clear the CCIF flag
    FTFA->FSTAT = 0x80;
    // Wait until current command complete
    while (!(FTFA->FSTAT & 0x80))
    {
    }
    // Enable interrupts
    __enable_irq();
}

/*
 *  FLASH_EraseFlashSector()
 */

void FLASH_EraseFlashSector(uint32_t address)
{
    // Wait until previous command complete
    while (!(FTFA->FSTAT & 0x80))
    {
    }
    // Disable interrupts
    __disable_irq();
    // Flash Command
    FTFA->FCCOB0 = COMMAND_ERASE_FLASH_SECTOR;
    // Flash Address
    FTFA->FCCOB1 = address >> 16;
    FTFA->FCCOB2 = address >> 8;
    FTFA->FCCOB3 = address;
    // Clear the CCIF flag
    FTFA->FSTAT = 0x80;
    // Wait until current command complete
    while (!(FTFA->FSTAT & 0x80))
    {
    }
    // Enable interrupts
    __enable_irq();
}

/*
 *  FLASH_EraseFlashSectors()
 */

void FLASH_EraseFlashSectors(uint32_t address, uint8_t size)
{
    uint8_t  index = 0;
    // Erase multiple flash sector
    for (index = 0; index < size; index++)
    {
        FLASH_EraseFlashSector(address + index * FLASH_SECTOR_SIZE);
    }
}