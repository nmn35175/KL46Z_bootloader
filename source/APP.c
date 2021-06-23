/******************************************************************************
 *  Includes
 *****************************************************************************/

#include "MKL46Z4.h"
#include "APP.h"
#include "FLASH.h"
#include "QUEUE.h"
#include "SREC.h"
#include "UART.h"

/******************************************************************************
 *  Typedefs
 *****************************************************************************/

typedef void(*pFunction)(void);

/******************************************************************************
 *  Global variables
 *****************************************************************************/

queue_struct_t  *gp_Queue;

/******************************************************************************
 *  Function definitions
 *****************************************************************************/

/*
 *  APP_Boot()
 */

void APP_Boot(void)
{
    
    queue_struct_t uart0_queue;         // UART0 QUEUE instance
    queue_status_t _queue_status;       // QUEUE error status
    srec_struct_t srec;                 // SREC struct
    srec_status_t _srec_status;         // SREC error status   
    uint32_t sector = 0;                // Number of flash sectors
    uint8_t *data;
    uint8_t index = 0;
    
    gp_Queue = &uart0_queue;            // Queue pointer
    // Inform user of Application mode
    UART0_SendString("\r\n  -- BOOTLOADER MODE --\r\n");
    UART0_SendString("Send SREC file through terminal.\r\n");
    // Init UART0 queue
    QUEUE_Init(gp_Queue);
    // Erase flash for loading user application
    sector = ((APP_END_ADDRESS - APP_START_ADDRESS + 1) / SECTOR_SIZE);
    FLASH_EraseFlashSectors(APP_START_ADDRESS, sector);
    
    while (1)
    {
        // Read and store data from UART0_queue
        _queue_status = QUEUE_Read(gp_Queue, &data);
        // If uart0_queue is not empty
        if(_queue_status != E_QUEUE_EMPTY)
        {
            // Parse data from SREC line to SREC struct
            _srec_status = SREC_ParseData(data, &srec);
            // If error occur (incorrect checksum)
            switch (_srec_status)
            {
            case E_SREC_START:
                // Inform user: process starts
                //UART0_SendString("\r\nBooting started.\r\n\r\n");
                break;
            case E_SREC_IN_PROGRESS:
                for (index = 0; index < srec.length; index += 4)
                {
                    // Write data in to flash memory address location
                    FLASH_ProgramLongword(srec.address + index, srec.data + index);
                }
                UART0_SendChar('>');
                break;
            case E_SREC_SUCCESS:
                // Inform user: process ends
                UART0_SendString("Completed!\r\nPress RESET to run Application.\r\n");
                break;
            case E_SREC_INVALID_CHECKSUM:
                // Inform user: error
                UART0_SendString("Error!\r\nPress RESET + SW1 to restart the Bootloader.\r\n");
                return;
            default:
                break;
            }
            // Move to next element
            QUEUE_Get(gp_Queue);
        }
    }
}

/*
 *  APP_Run()
 */

void APP_Run(void)
{
    uint32_t reset_address = 0;
    pFunction jump_to_address;
    // Inform user of Application mode
    UART0_SendString("\r\n  -- APPLICATION MODE --\r\n");
    UART0_SendString("Press RESET + SW1 to run Bootloader.\r\n");
    __disable_irq();
    // Relocate exception vector table
    SCB->VTOR = APP_START_ADDRESS;
    // Set main stack pointer
    __set_MSP(*(uint32_t*)APP_START_ADDRESS);
    // Reset interrupt handler address
    reset_address = *(uint32_t*)(APP_START_ADDRESS + 4);
    // Call reset interrupt handler
    jump_to_address = (pFunction)(reset_address);
    // Jump to application
    jump_to_address();
}

/*
 *  UART0_IRQHandler()
 */

void UART0_IRQHandler(void)
{
    uint8_t data = 0;
    // Receive data register full flag
    if(UART0->S1 & 0x20)
    {
        // Read data from receive data register
        data = UART0->D;
        // Write data into queue
        QUEUE_WriteByte(gp_Queue, data);
        if (data == '\n')
        {
            QUEUE_WriteByte(gp_Queue, '\0');
            // Put the current element
            QUEUE_Put(gp_Queue);
        }
    }
    // Clear the interrupt flag
    NVIC_ClearPendingIRQ(UART0_IRQn);
}