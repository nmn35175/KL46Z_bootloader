/******************************************************************************
 *  Includes
 *****************************************************************************/

#include <stdint.h>
#include "SREC.h"

/******************************************************************************
 *  Global variables
 *****************************************************************************/



/******************************************************************************
 *  Function definitions
 *****************************************************************************/

/*
 *  SREC_AsciiToHex()
 */

uint8_t SREC_AsciiToHex(uint8_t ascii)
{
    uint8_t value = 0xFF;
    // If ASCII digit from 0 to 9
    if (ascii >= '0' && ascii <= '9')
    {
        value = ascii - '0';
    }
    // If ASCII digit from A to F
    else if (ascii >= 'A' && ascii <= 'F')
    {
        value = ascii - 'A' + 10;
    }
    else
    {
        // Avoid Misra checking
    }
    return value;
}

/*
 *  SREC_TwoHexToByte()
 */

uint8_t SREC_TwoHexToByte(uint8_t *ascii)
{
    uint8_t data;
    // Convert two hex characters to one byte
    data = (SREC_AsciiToHex(ascii[0]) << 4) + SREC_AsciiToHex(ascii[1]);
    
    return data;
}

/*
 *  SREC_ParseData()
 */

srec_status_t SREC_ParseData(uint8_t *data, srec_struct_t *srec)
{
    // Local variables
    srec_status_t _srec_status;     // SREC error status
    uint8_t temp_data = 0;          // Storing read data
	uint8_t address_length = 0;     // Address length in bytes
	uint8_t index = 0;
	uint8_t offset = 4;             // Starting from address bytes	
	uint8_t checksum = 0;
    
    // Init values
    _srec_status = E_SREC_SUCCESS;
    srec->address = 0;
	srec->length = 0;
    srec->type = SREC_AsciiToHex(data[1]);      // Byte data[1] is record type
    checksum = SREC_TwoHexToByte(&data[2]);     // Checksum starts from data[2]    
    
    // Record type
    switch (srec->type)
    {
    case 0:     // Type 0: 2 bytes of address
        address_length = 2;
        _srec_status = E_SREC_START;
        break;
    case 1:     // Type 1: 2 bytes of address
    case 2:     // Type 2: 3 bytes of address
    case 3:     // Type 3: 4 bytes of address
        _srec_status = E_SREC_IN_PROGRESS;
        address_length = srec->type + 1;
        break;
    case 4:     // Type 4: reserved
    case 5:     // Type 5: other type
    case 6:     // Type 6: other type
        break;
    case 7:     // Type 7: 4 bytes of address
    case 8:     // Type 8: 3 bytes of address
    case 9:     // Type 9: 2 bytes of address
        _srec_status = E_SREC_SUCCESS;
        address_length = 11 - srec->type;
        break;
    default:
        break;
    }
    
    // Read address
    for (index = 0; index < address_length; index++)
    {
        // Read address byte by byte
        temp_data = SREC_TwoHexToByte(&data[offset]);
        // Store address in SREC struct instance
        srec->address = (srec->address << 8) | temp_data;
        // Accumulate checksum
        checksum += temp_data;
        // Move to next byte
        offset += 2;
    }
    
    // Read data
    srec->length = SREC_TwoHexToByte(&data[2]) - address_length - 1;
    for (index = 0; index < srec->length; index++)
    {
        // Read data byte by byte
        temp_data = SREC_TwoHexToByte(&data[offset]);
        // Store data in SREC struct instance
        srec->data[index] = temp_data;
        // Accumulate checksum
        checksum += temp_data;
        // Move to next byte
        offset += 2;
    }
    
    // Accumulate checksum with checksum byte
    checksum += SREC_TwoHexToByte(&data[offset]);
    // If checksum is not correct
    if(checksum != 0xFF)
    {
        // Return error
        _srec_status = E_SREC_INVALID_CHECKSUM;
    }
    
    return _srec_status;
}