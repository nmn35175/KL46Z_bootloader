/******************************************************************************
 *  Function prototypes
 *****************************************************************************/

/*
 *  @function       UART0_Init()
 *  @description    Enable and inititalize UART0 module with 8-bit data mode,
 *                  1-bit stop, no parity and input baud rate.
 *  @parameter      uint32_t  baudrate  :   Desired baud rate
 *  @return         none
 */

void UART0_Init(uint32_t baudrate);

/*
 *  @function       UART0_Deinit()
 *  @description    Deinitialize UART0 module.
 *  @parameter      none
 *  @return         none
 */

void UART0_Deinit(void);
     
/*
 *  @function       UART0_SetBaudRate()
 *  @description    Set baud rate for UART0 module.
 *  @parameter      uint32_t  baudrate  :   Desired baud rate
 *  @return         none
 */

void UART0_SetBaudRate(uint32_t baudrate);

/*
 *  @function       UART0_SendChar()
 *  @description    Send a byte using UART0 TX.
 *  @parameter      uint8_t  byte   :   Byte of data
 *  @return         none
 */

void UART0_SendChar(uint8_t byte);

/*
 *  @function       UART0_SendString()
 *  @description    Send a NULL-terminated string using UART0 TX.
 *  @parameter      uint8_t*  data  :   NULL-terminated string
 *  @return         none
 */

void UART0_SendString(uint8_t *data);

/*
 *  @function       UART0_ReadChar()
 *  @description    Read a byte of data from UART0 RX.
 *  @parameter      uint8_t*  data  :   Pointer to store data byte
 *  @return         none
 */

void UART0_ReadChar(uint8_t *data);