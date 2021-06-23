/******************************************************************************
 *  Defines
 *****************************************************************************/

#define RED_LED_MASK        1 << 29
#define RED_LED_ON          (FPTE->PCOR |= RED_LED_MASK)
#define RED_LED_OFF         (FPTE->PSOR |= RED_LED_MASK)
#define RED_LED_TOGGLE      (FPTE->PTOR |= RED_LED_MASK)

#define GREEN_LED_MASK      1 << 5
#define GREEN_LED_ON        (FPTD->PCOR |= GREEN_LED_MASK)
#define GREEN_LED_OFF       (FPTD->PSOR |= GREEN_LED_MASK)
#define GREEN_LED_TOGGLE    (FPTD->PTOR |= GREEN_LED_MASK)

#define SW1_MASK            1 << 3
#define SW1_STATE           (FPTC->PDIR & SW1_MASK)
#define SW1_PRESSED         ((FPTC->PDIR & SW1_MASK) == 0x00000000)
#define SW1_RELEASED        ((FPTC->PDIR & SW1_MASK) == 0x00000008)

#define SW3_MASK            1 << 12
#define SW3_STATE           (FPTC->PDIR & SW3_MASK)
#define SW3_PRESSED         ((FPTC->PDIR & SW3_MASK) == 0x00000000)
#define SW3_RELEASED        ((FPTC->PDIR & SW3_MASK) == 0x00001000)

/******************************************************************************
 *  Function prototypes
 *****************************************************************************/

/*
 *  @function       GPIO_LedInit()
 *  @description    Initialize LEDs.
 *  @parameter      none
 *  @return         none
 */

void GPIO_LedInit(void);

/*
 *  @function       GPIO_LedDeinit()
 *  @description    Deinitialize LEDs.
 *  @parameter      none
 *  @return         none
 */

void GPIO_LedDeinit(void);

/*
 *  @function       GPIO_SwInit()
 *  @description    Initialize switches.
 *  @parameter      none
 *  @return         none
 */

void GPIO_SwInit(void);

/*
 *  @function       GPIO_SwDeinit()
 *  @description    Deinitialize switches.
 *  @parameter      none
 *  @return         none
 */

void GPIO_SwDeinit(void);