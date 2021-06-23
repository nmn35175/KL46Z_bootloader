/******************************************************************************
 *  Defines
 *****************************************************************************/

#define SREC_LINE_MAX    80
#define SREC_DATA_MAX    64

/******************************************************************************
 *  Typedefs
 *****************************************************************************/

/*
 *  @struct         srec_struct_t
 *  @description    Data struct of a SREC line
 *  @member         uint32_t  address   :   Memory address
 *                  uint16_t  length    :   Data length in bytes
 *                  uint8_t  type       :   Record type
 *                  uint8_t  data[]     :   Data
 */

typedef struct
{
    uint32_t    address;
    uint16_t    length;
    uint8_t     type;
    uint8_t     data[SREC_DATA_MAX];
}
srec_struct_t;

/*
 *  @emun           srec_status_t
 *  @description    SREC error status.
 *  @value          SREC_SUCCESS    :   No error
 *                  SREC_ERROR      :   Error
 */

typedef enum 
{
    E_SREC_SUCCESS          = 0,
    E_SREC_START            = 1,
    E_SREC_IN_PROGRESS      = 2,
    E_SREC_INVALID_CHECKSUM = 3
}
srec_status_t;

/******************************************************************************
 *  Function prototypes
 *****************************************************************************/

/*
 *  @function       SREC_AsciiToHex()
 *  @description    Convert ASCII hexadecimal digit to hexadecimal value.
 *  @parameter      uint8_t  ascii  :   ASCII hexadecimal digit
 *  @return         uint8_t         :   Hexadecimal value
 */

uint8_t SREC_AsciiToHex(uint8_t ascii);

/*
 *  @function       SREC_TwoHexToByte()
 *  @description    Convert 2 ASCII hexadecimal digits to byte.
 *  @parameter      uint8_t*  ascii :   2 ASCII hexadecimal digits
 *  @return         uint8_t         :   Byte value
 */

uint8_t SREC_TwoHexToByte(uint8_t *ascii);

/*
 *  @function       SREC_ParseData()
 *  @description    Parse data from SREC line to SREC struct.
 *  @parameter      uint8_t*  text      :   SREC line
 *                  srec_struct_t  srec :   SREC struct instance
 *  @return         srec_status_t       :   SREC error status
 */

srec_status_t SREC_ParseData(uint8_t *text, srec_struct_t *srec);