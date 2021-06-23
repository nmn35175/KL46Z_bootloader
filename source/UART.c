/******************************************************************************
 *  Includes
 *****************************************************************************/

#include "MKL46Z4.h"
#include "UART.h"

/******************************************************************************
 *  Function definitions
 *****************************************************************************/

/*
 *  UART0_Init()
 */

void UART0_Init(uint32_t baudrate)
{
    // Enable peripheral clock for PORTA
    SIM->SCGC5 |= SIM_SCGC5_PORTA(1);
    // Alternative 2 mode for PTA1 and PTA2 (UART0_RX and UART0_TX)
    PORTA->PCR[1] &= ~PORT_PCR_MUX_MASK;
    PORTA->PCR[2] &= ~PORT_PCR_MUX_MASK;
    PORTA->PCR[1] |= PORT_PCR_MUX(2);
    PORTA->PCR[2] |= PORT_PCR_MUX(2);
    // Select UART0 clock source: MCGFLLCLK clock (20971520 Hz)
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
    // Enable peripheral clock for UART0
    SIM->SCGC4 |= SIM_SCGC4_UART0(1);
    // Set baud rate for UART0
    UART0_SetBaudRate(baudrate);
    // Enable interrupt for UART0
    NVIC_EnableIRQ(UART0_IRQn);
}

/*
 *  UART0_Deinit()
 */

void UART0_Deinit(void)
{
    // Enable interrupt for UART0
    NVIC_DisableIRQ(UART0_IRQn);
    // Disable RX, TX and receiver interrupt for UART0
    UART0->C2 &= ~(UART0_C2_RE_MASK | UART0_C2_TE_MASK | UART0_C2_RIE_MASK);
}

/*
 *  UART0_SetBaudRate()
 */

void UART0_SetBaudRate(uint32_t desired_baudrate)
{
    
    // Local variables
    uint32_t clock = SystemCoreClock;       // Default baud clock
    uint32_t temp_baudrate_1 = 0;
    uint32_t temp_baudrate_2 = 0;
    uint32_t deviation_1 = 0;
    uint32_t deviation_2 = 0;
    uint32_t deviation_min = 0xFFFFFFFF;
    uint16_t sbr = 1;                       // SBR value ranges from 1 to 8191
    uint16_t temp_sbr = 1;                  // SBR value ranges from 1 to 8191
    uint8_t osr = 4;                        // OSR value ranges from 4 to 32
    uint8_t temp_osr = 4;                   // OSR value ranges from 4 to 32
    
    // Set maximum baud rate to be 115200
    if (desired_baudrate > 115200)      
    {
        desired_baudrate = 115200;
    }
    // Set minimum baud rate to be 1200
    else if (desired_baudrate < 1200)   
    {
        desired_baudrate = 1200;
    }
    // Finding best OSR and SBR values
    for (temp_osr = 32; temp_osr >= 4; temp_osr--)
    {
        temp_sbr = clock / (temp_osr * desired_baudrate);
        // SBR value ranges from 1 to 8191
        if (temp_sbr < 8192)
        {
            // Avoid division by 0
            if (temp_sbr == 0)
            {
                temp_sbr = 1;
            }
            // Calculate temporary baud rate values
            temp_baudrate_1 = clock / (temp_osr * temp_sbr);    
            temp_baudrate_2 = clock / (temp_osr * (temp_sbr + 1));
            deviation_1 = temp_baudrate_1 - desired_baudrate;
            deviation_2 = desired_baudrate - temp_baudrate_2;
            // If temp_baudrate_1 is closer to desired_baudrate
            if (deviation_1 < deviation_2)
            {
                // If closer than its previous value
                if (deviation_1 < deviation_min)
                {
                    // Take all current values
                    osr = temp_osr;
                    sbr = temp_sbr;
                    deviation_min = deviation_1;
                    // If temp_baudrate_1 == desired_baudrate
                    if (deviation_1 == 0)
                    {
                        break;  // Break the loop
                    }
                }
            }
            // If temp_baudrate_2 is closer to desired_baudrate
            else
            {
                // If closer than its previous value
                if (deviation_2 < deviation_min)
                {
                    // Take all current values
                    osr = temp_osr;
                    sbr = temp_sbr + 1;
                    deviation_min = deviation_2;
                    // If temp_baudrate_2 == desired_baudrate
                    if (deviation_2 == 0)
                    {
                        break;  // Break the loop
                    }
                }
            }
        }
    }
    // Disable RX and TX for UART0
    UART0->C2 &= ~(UART0_C2_RE_MASK | UART0_C2_TE_MASK);
    // Set OSR value
    UART0->C4 &= ~UART0_C4_OSR_MASK;        // clear bits OSR of C4 register
    UART0->C4 = UART0_C4_OSR(osr - 1);      // set OSR value
    // Set SBR value
    UART0->BDH &= ~UART0_BDH_SBR_MASK;      // clear bits SBR of BDH register
    UART0->BDL &= ~UART0_BDL_SBR_MASK;      // clear bits SBR of BDL register
    UART0->BDH = (uint8_t)(sbr >> 8);       // set SBR value (BDH)
    UART0->BDL = (uint8_t)(sbr);            // set SBR value (BDL)
    // Enable RX and TX for UART0
    UART0->C2 |= (UART0_C2_RE_MASK | UART0_C2_TE_MASK);
    // Enable interrupts
    UART0->C2 |= UART0_C2_RIE(1);    
}

/*
 *  UART0_SendChar()
 */

void UART0_SendChar(uint8_t byte)
{
    // Wait for UART0 data register to be empty
    while (!(UART0->S1 & 0x80))
    {
    }
    // Send data byte to UART0 data register
    UART0->D = byte;    
}

/*
 *  UART0_SendString()
 */

void UART0_SendString(uint8_t *data)
{
    // Send data until NULL character
    while (*data != '\0')
    {
        UART0_SendChar(*data);
        data++;
    }
}

/*
 *  UART0_ReadChar()
 */

void UART0_ReadChar(uint8_t *data)
{
    // Wait until UART0 data register to be full
    while (!(UART0->S1 & 0x20))
    {
    }
    // Read data from UART0 data register
    *data = UART0->D;
}