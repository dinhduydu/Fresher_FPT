/**************************************************************************************
 * Include
 **************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Check.h"
#include "Convert.h"
/**********************************************************
 * Function
 * **********************************************************/

int8_t Check_File (SRecord *srecord, FILE *fp)
{
    int8_t retValue;
    /* Check our record pointer and file pointer */
    if (srecord == NULL || fp == NULL)
    {
        retValue = SRECORD_ERROR_FILE;
    }
    else
    {
        retValue =     SRECORD_CORRECT;
    }
    return retValue;
}

int8_t Check_Hexa (char *ptr)
{
    uint8_t index = 1;
    uint8_t count =1;
    uint8_t retValue = SRECORD_CORRECT;
    for (index = 1; index < (uint8_t)strlen(ptr); index ++)
     {
         if ((ptr[count] >= '0' && ptr[count] <= '9') || (ptr[count] >= 'A' && ptr[count] <= 'F'))
        {
            count ++;
        }
        else
        {
            retValue =  SRECORD_ERROR_HEXA;
        }
    }
    return retValue;
}

int8_t Check_S (char *ptr)
{
    int8_t retValue;
    /* Check for the S-Record start code at the beginning of every record */
    if (ptr[0] != SRECORD_START_CODE )
    {
        retValue = SRECORD_ERROR_S;
    }
    else
    {
        retValue = SRECORD_CORRECT;
    }
    return retValue;
}

int8_t Check_Type (SRecord *srecord)
{
    int8_t retValue;
    /* Check that our S-Record type is valid */
    if (((srecord->type >= SRECORD_TYPE_S0) && (srecord->type <= SRECORD_TYPE_S9)) && (srecord->type != SRECORD_TYPE_S4))
    {
        retValue = SRECORD_CORRECT;
    }
    else
    {
        retValue = SRECORD_ERROR_TYPE;
    }
    return retValue;
}

int8_t Check_ByteCount(SRecord *srecord, char *ptr)
{
    uint8_t index;
    uint8_t count = 0;
    int8_t retValue;
    for (index = 4; index < (uint8_t)(strlen(ptr)); index ++)
    {
        count ++;
    }
    if(srecord->bytecount != (count/2)) /* Bescause 2 ASCII character = 1 byte hex -> count must be divied by 2 to present length by hexa, isn't ASCII*/
    {
        retValue = SRECORD_ERROR_BYTE_COUNT;
    }
    else
    {
        retValue = SRECORD_CORRECT;
    }
    return retValue;
}

int8_t Check_AddressLength(char *recordBuffer, uint8_t ASCII_AddressLength)
{
    int8_t retValue;
    /* Size check for address field */
    if (strlen(recordBuffer) < (SRECORD_ADDRESS_OFFSET + ASCII_AddressLength))
    {
        retValue = SRECORD_ERROR_ADDRESS_FIELD;
    }
    else
    {
        retValue = SRECORD_CORRECT;
    }
    return retValue;
}

int8_t Check_DataLength(uint8_t ASCII_DataLength)
{
    int8_t retValue;
    /* Bailout if we get an invalid data length */
    if (ASCII_DataLength < 0 || ASCII_DataLength > SRECORD_MAX_DATA_LENGTH)
    {
        retValue = SRECORD_ERROR_DATA_LENGTH;
    }
    else
    {
        retValue = SRECORD_CORRECT;
    }
    return retValue;
}

int8_t Check_Sum(const SRecord *srecord) 
{
    /* Declare variable to calculate the checksum of an S-Record */
    uint8_t checksum;
    uint8_t fieldDataCount;
    uint8_t index;
    int8_t retValue;
    /* Compute the record count, address and checksum lengths are halved because record count is the number of bytes left in the record, 
    not the length of the ASCII hex representation */
    fieldDataCount = SRecord_Address_Lengths[srecord->type]/2 + srecord->dataLength + SRECORD_CHECK_SUM_LENGTH/2;
    /* Add the count, address, and data fields together */
    checksum = (uint8_t)fieldDataCount;
    /* Add each byte of the address individually */
    checksum += (uint8_t)(srecord->address & 0x000000FF); /* C+=A <=> C = C + A */
    checksum += (uint8_t)((srecord->address & 0x0000FF00) >> 8);
    checksum += (uint8_t)((srecord ->address & 0x00FF0000) >> 16);
    checksum += (uint8_t)((srecord->address & 0xFF000000) >> 24);
    for (index = 0; index < srecord->dataLength; index++)
    {
        checksum += (uint8_t)srecord->data[index];
    }
    /* One's complement the checksum */
    checksum = ~checksum;
    checksum = (uint8_t)(checksum & 0x000000FF);
    printf("\t|\tChecksum after computed is: %X\t\t", checksum);
    if (srecord->checkSum != checksum)
    {
        retValue =  SRECORD_ERROR_CHECK_SUM;
    }
    else
    {
        retValue =SRECORD_CORRECT;
    }

    return retValue;
}

void Print_Error(int8_t check)
{
    switch (check)
    {
        case SRECORD_ERROR_S:
            printf("Invalid S\n");
            break;
        case SRECORD_ERROR_HEXA:
            printf("Invalid hexa\n");
            break;
        case SRECORD_ERROR_BYTE_COUNT:    
            printf("Invalid byte count\n");
            break;
        case SRECORD_ERROR_CHECK_SUM:
            printf("Invalid check sum\n");
            break;
        case SRECORD_ERROR_ADDRESS_FIELD:
            printf("Invalid address field\n");
            break;
        case SRECORD_ERROR_FILE:
            printf("Invalid file\n");
            break;
        case SRECORD_ERROR_TYPE:
            printf("Invalid type\n");
            break;
        case SRECORD_ERROR_DATA_LENGTH:
            printf("Invalid data length");
            break;
        default :
            printf("Valid\n");
            break;
    }
}
