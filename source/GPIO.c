/******************************************************************************
 *  Includes
 *****************************************************************************/

#include "MKL46Z4.h"
#include "GPIO.h"

/******************************************************************************
 *  Function definitions
 *****************************************************************************/

/*
 *  GPIO_LedInit()
 */

void GPIO_LedInit(void)
{
    /* Enable clock for PORTE & PORTD */
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

    /* Initialize the RED LED (PTE29)*/
    /* Set the PTE29 pin multiplexer to GPIO mode */
    PORTE->PCR[29] = PORT_PCR_MUX(1);
    /* Set the pin's direction to output */ 
    FPTE->PDDR |= RED_LED_MASK;
    /* Set the initial output state to high */
    FPTE->PSOR |= RED_LED_MASK;

    /* Initialize the Green LED (PTD5) */
    /* Set the PTD5 pin multiplexer to GPIO mode */
    PORTD->PCR[5] = PORT_PCR_MUX(1);
    /* Set the pin's direction to output */
    FPTD->PDDR |= GREEN_LED_MASK;
    /* Set the initial output state to high */
    FPTD->PSOR |= GREEN_LED_MASK;
}

/*
 *  GPIO_LedDeinit()
 */

void GPIO_LedDeinit(void)
{
    /* Set the output state to high */
    FPTE->PSOR |= RED_LED_MASK;
    /* Disable the PTE29 pin */
    PORTE->PCR[29] = PORT_PCR_MUX(0);
    /* Set the output state to high */
    FPTD->PSOR |= GREEN_LED_MASK;
    /* Disable the PTD5 pin  */
    PORTD->PCR[5] = PORT_PCR_MUX(0);
}

/*
 *  GPIO_SwInit()
 */

void GPIO_SwInit(void)
{
    /* Enable clock for PORTC */
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    /* Initialize the SW1 (PTC3)*/
    /* Set the PTC3 pin multiplexer to GPIO mode, pullup */
    PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_PE(1) | PORT_PCR_PS(1);
    /* Set the pin's direction to input */ 
    FPTC->PDDR &= ~(1 << 3);

    /* Initialize the SW3 (PTC12) */
    /* Set the PTD5 pin multiplexer to GPIO mode, pullup */
    PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE(1) | PORT_PCR_PS(1);
    /* Set the pin's direction to output */
    FPTC->PDDR &= (1 << 12);
}

/*
 *  GPIO_SwDeinit()
 */

void GPIO_SwDeinit(void)
{
    /* Disable the PTC3 pin */
    PORTC->PCR[3] = PORT_PCR_MUX(0);
    /* Disable the PTD5 pin */
    PORTC->PCR[12] = PORT_PCR_MUX(0);  
}