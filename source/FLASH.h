/******************************************************************************
 *  Defines
 *****************************************************************************/

#define COMMAND_READ_1S_SECTION             0x01
#define COMMAND_PROGRAM_CHECK               0x02
#define COMMAND_READ_RESOURCE               0x03
#define COMMAND_PROGRAM_LONGWORD            0x06
#define COMMAND_ERASE_FLASH_SECTOR          0x09
#define COMMAND_READ_1S_ALL_BLOCKS          0x40
#define COMMAND_READ_ONCE                   0x41
#define COMMAND_PROGRAM_ONCE                0x43
#define COMMAND_ERASE_ALL_BLOCKS            0x44
#define COMMAND_VERIFY_BACKDOOR_ACCESS_KEY  0x06

#define FLASH_SECTOR_SIZE     1024

/******************************************************************************
 *  Function prototypes
 *****************************************************************************/

/*
 *  @function       FLASH_ProgramLongword()
 *  @description    Write 4 bytes of data to an address of flash memory.
 *  @parameter      uint32_t  address   :   Memory address
 *                  uint8_t*  data      :   4 bytes of data
 *  @return         none
 */

void FLASH_ProgramLongword(uint32_t address, uint8_t *data);

/*
 *  @function       FLASH_EraseFlashSector()
 *  @description    Erase a flash sector.
 *  @parameter      uint32_t  address   :   Start memory address
 *  @return         none
 */

void FLASH_EraseFlashSector(uint32_t address);

/*
 *  @function       FLASH_EraseFlashSectors()
 *  @description    Erase multiple adjacent flash sectors.
 *  @parameter      uint32_t  address   :   Start memory address
 *                  uint8_t  size       :   Number of sectors
 *  @return         none
 */

void FLASH_EraseFlashSectors(uint32_t address, uint8_t size);