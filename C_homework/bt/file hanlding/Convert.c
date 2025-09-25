/**************************************************************************************
 * Include
 **************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include "Convert.h"
#include "Check.h"
/*************************************************************************************
 * Function
 * ***************************************************************************************/

/* Length of the ASCII hex encoded address fields of different SRecord types */
uint8_t SRecord_Address_Lengths[] = 
{
    4, /* S0: 16-bit 0000*/
    4, /* S1: 16-bit address */
    6, /* S2: 24-bit address */
    8, /* S3: 32-bit address */
    8, /* S4: not use*/
    4, /* S5: 16-bit count */
    6, /* S6: 24-bit count */
    8, /* S7: 32-bit count */
    6, /* S8: 24-bit address */
    4  /* S9: 16-bit address */
};

/* Utility function to read an S-Record from a file */
void Read_SRecord(SRecord *srecord, FILE *fp) 
{
    SRecord memory;                                                         /* Declare a variable to cointain value of srecord pointer point to */
    srecord = &memory;                                                         /* Before using pointer, allocate memory */
    unsigned char recordBuffer[SRECORD_RECORD_BUFF_SIZE];                    /* A temporary buffer to hold ASCII hex encoded data, set to the maximum length we would ever need */
    unsigned char hexBuffer[SRECORD_MAX_ADDRESS_LENGTH+1];                    /* A temporary buffer to hold ASCII hex encoded data, set to the maximum length we would ever need */
    uint8_t ASCII_AddressLength;
    uint8_t ASCII_DataLength;
    uint8_t dataOffset;
    uint8_t index;
    int8_t errorhexa;
    char *eof;
    /* Start checking file */
    printf("\t|\t-->checking file: ");
    Print_Error(Check_File(srecord, fp));
    /* Read a line from stream and save it in recordBuffer */
    printf("\t|\t-->Reading line....");
     fgets(recordBuffer, SRECORD_RECORD_BUFF_SIZE, fp);
    /* Null character: Terminate the string at the first sign of a \r or \n */
    for (index = 0; index < (uint8_t)strlen(recordBuffer); index++) 
    {
        /* Find end of line and assign it by '0' */
        if (recordBuffer[index] == '\r' || recordBuffer[index] == '\n') 
        {
            printf("\t\tGot end of line");
            recordBuffer[index] = 0;
            break;
        }
    }
    /* Print Line  */    
    printf("\n\t|\t1) SRECORD BUFFER now is char:\t");
    for (index = 0; index < (uint8_t)strlen(recordBuffer); index ++)
     {
         printf("%c", recordBuffer[index]);
    }
    /* Check hexa, if hexa fault, check new line */
    printf("\n\t|\t-->Checking hexa:\t");
    errorhexa = Check_Hexa(recordBuffer);
    Print_Error(errorhexa);
    if (errorhexa == SRECORD_CORRECT)
    {
        printf("\t|\t-->Continue checking first character 'S':\t");
        Print_Error(Check_S(recordBuffer));
        /* Check Type */
        Convert_Type (srecord, hexBuffer, recordBuffer);
        printf("\t|\t-->Checking type ....");
        Print_Error(Check_Type(srecord));
        /* Check Byte Count */
        Convert_ByteCount (srecord, hexBuffer,recordBuffer);
        printf("\t|\t-->Checking byte count....");
        Print_Error(Check_ByteCount(srecord, recordBuffer));
        /* Get the ASCII hex address length of this particular S-Record type */
        ASCII_AddressLength = SRecord_Address_Lengths[srecord->type];
        /* Check Address Length */
        Convert_AddressLength (srecord, hexBuffer,recordBuffer, ASCII_AddressLength);
        printf("\t|\t-->Checking address length....");
        Print_Error(Check_AddressLength(recordBuffer, ASCII_AddressLength));
        
        /* Compute the ASCII hex data length by subtracting the remaining field lengths from the S-Record
         * count field (times 2 to account for the number of characters used in ASCII hex encoding) */
        ASCII_DataLength = (srecord->bytecount)*2 - ASCII_AddressLength - SRECORD_CHECK_SUM_LENGTH;
        srecord->dataOffset = SRECORD_ADDRESS_OFFSET + ASCII_AddressLength;
        Convert_DataLength (srecord,hexBuffer,recordBuffer,ASCII_DataLength );
        printf("\t|\t-->Checking data length....");
        Print_Error(Check_DataLength(ASCII_AddressLength));
        /* Check Sum */
        Convert_CheckSum (srecord, hexBuffer, recordBuffer, ASCII_AddressLength);
        printf("\t|\t-->Checking checkSum....\n");
        Print_Error(Check_Sum(srecord));
    }
    else
    {
        printf("\t|\t==>STOP CHECKING THIS LINE \n");
    }
}

void Convert_Type (SRecord *srecord, char *hexBuffer, char *recordBuffer)
{
    /* Copy the ASCII hex encoding of the type field into hexBuffer, convert it into a usable integer */
    strncpy(hexBuffer, recordBuffer+SRECORD_TYPE_OFFSET, SRECORD_TYPE_LENGTH);
    printf("\t|\t2) Type of line is: S%c\n", hexBuffer[0]);
    hexBuffer[SRECORD_TYPE_LENGTH] = 0; 
    /* convert it into a usable integer */
    srecord->type = (uint8_t)strtoul(hexBuffer, (char **)NULL, 16); /* unsigned long int stroul(const char *str, char **endptr, int base) */
}

void Convert_ByteCount (SRecord *srecord, char *hexBuffer, char *recordBuffer)
{
    /* Copy the ASCII hex encoding of the byte count field into hexBuffer, convert it to a usable integer */
    strncpy(hexBuffer, recordBuffer+SRECORD_BYTE_COUNT_OFFSET, SRECORD_BYTE_COUNT_LENGTH); /* char *strncpy(char *dest, const char *src, size_t n) */
    hexBuffer[SRECORD_BYTE_COUNT_LENGTH] = 0;
    srecord->bytecount= (uint8_t)strtoul(hexBuffer, (char **)NULL, 16);
    printf("\t|\t3) Byte count is: %X\n", srecord->bytecount);
}    

void Convert_AddressLength (SRecord *srecord, char *hexBuffer, char *recordBuffer, uint8_t ASCII_AddressLength )
{
    /* Copy the ASCII hex encoding of the count field into hexBuff, convert it to a usable integer */
    strncpy(hexBuffer, recordBuffer + SRECORD_ADDRESS_OFFSET, ASCII_AddressLength);
    hexBuffer[ASCII_AddressLength] = 0;
    srecord->address = (uint32_t)strtoul(hexBuffer, (char **)NULL, 16);
    printf("\t|\t4) AddressField is: %X\n", srecord->address);
    printf("\t|\t   AddressLength is: %d\n", strlen(hexBuffer));    
}

void Convert_DataLength (SRecord *srecord,char *hexBuffer, char *recordBuffer, uint8_t ASCII_DataLength)
{
    uint8_t index;
    ;
    /* Loop through each ASCII hex byte of the data field, pull it out into hexBuff,
     * convert it and store the result in the data buffer of the S-Record */
    for (index = 0; index < ASCII_DataLength/2; index++) 
    {
        /* Times two i because every byte is represented by two ASCII hex characters <=> 1 byte = 2 ASCII */
        strncpy(hexBuffer, recordBuffer+srecord->dataOffset+SRECORD_ASCII_HEX_BYTE_LENGTH*index, SRECORD_ASCII_HEX_BYTE_LENGTH);
        hexBuffer[SRECORD_ASCII_HEX_BYTE_LENGTH] = 0;
        srecord->data[index] = (uint8_t)strtoul(hexBuffer, (char **)NULL, 16);
    }
    /* Real data length is divided by two because every byte is represented by two ASCII hex characters */
    srecord->dataLength = ASCII_DataLength/2;
}

void Convert_CheckSum (SRecord *srecord, char *hexBuffer, char *recordBuffer, uint8_t ASCII_AddressLength )
{    
    /* Copy out the checksum ASCII hex encoded byte, and convert it back to a usable integer */
    strncpy(hexBuffer, recordBuffer+srecord->dataOffset+srecord->dataLength*2, SRECORD_CHECK_SUM_LENGTH);
    hexBuffer[SRECORD_CHECK_SUM_LENGTH] = 0;    
    
    srecord->checkSum = (uint8_t)strtoul(hexBuffer, (char **)NULL, 16);    
    printf("\t|\t6) Check sum converted is: %X\n", srecord->checkSum);
}
