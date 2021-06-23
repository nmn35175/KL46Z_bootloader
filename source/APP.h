/******************************************************************************
 *  Defines
 *****************************************************************************/

#define APP_START_ADDRESS   0x0000A000
#define APP_END_ADDRESS     0x0003FFFF
#define SECTOR_SIZE         1024

/******************************************************************************
 *  Function prototypes
 *****************************************************************************/

/*
 *  @function       APP_Boot()
 *  @description    Run the bootloader.
 *  @parameter      none
 *  @return         none
 */

void APP_Boot(void);

/*
 *  @function       APP_Run()
 *  @description    Run the user application.
 *  @parameter      none
 *  @return         none
 */

void APP_Run(void);