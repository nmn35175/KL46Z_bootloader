/*
 *  Project:        Bootloader for board KL46Z
 *  Author:         Minh Nguyen
 *  Description:    This bootloader reads .srec file from UART then programs
 *                  user application into flash memory.
 */

/******************************************************************************
 *  Includes
 *****************************************************************************/

#include "MKL46Z4.h"
#include "APP.h"
#include "GPIO.h"
#include "UART.h"

/******************************************************************************
 *  Main function
 *****************************************************************************/

int main(void)
{
    // Init UART0 module with baud rate 115200
    UART0_Init(115200);
    // Init switches
    GPIO_SwInit();
    // If SW1 is pressed
    if (SW1_PRESSED)
    {
        // Go to Bootloader mode
        APP_Boot();
    }
    else
    {
        // Go to Application mode
        APP_Run();
    }
}