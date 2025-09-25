/**
 * @file Check.h
 * @author your name (you@domain.com)
 * @brief low-level utility functions to create, read, write and print Motorola S-Record binary record
 * @version 0.1
 * @date 2022-07-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef H_CHECK_H
#define H_CHECK_H
#include <stdint.h>

#include <stdio.h>
/**************************************************************************************
 * Definitions: General definitions of the S-Record specification
 ****************************************************************************************/
enum SRecordDefinitions
{
    /* 768 should be plenty of space to read a S-Record */
    SRECORD_RECORD_BUFF_SIZE = 768,
    /* Offsets and lengths of various fields in an S-Record record */
    SRECORD_TYPE_OFFSET = 1,
    SRECORD_TYPE_LENGTH = 1,
    SRECORD_BYTE_COUNT_OFFSET = 2,
    SRECORD_BYTE_COUNT_LENGTH = 2,
    SRECORD_ADDRESS_OFFSET = 4,
    SRECORD_CHECK_SUM_LENGTH = 2,
    /* Maximum ASCII hex length of the S-Record data field */
    SRECORD_MAX_DATA_LENGTH = 254*2, /* 127 characters ASCII */
    /* Maximun ASCII hex length of the s-Record address field */
    SRECORD_MAX_ADDRESS_LENGTH = 8,
    /* ASCII hex length of a signle byte */
    SRECORD_ASCII_HEX_BYTE_LENGTH = 2,
    /* Start code offset and value */
    SRECORD_START_CODE_OFFSET = 0,
    SRECORD_START_CODE = 'S' /* 0x53 in hexa or 83 in decimal */
};

/*******************************************************************************************
 * Definitions: All possible error codes the Motorola S-Record utility functions may return.
 *******************************************************************************************/
enum SRecordError 
{
    SRECORD_CORRECT = 0,  /**< Error code for success or no error */
    SRECORD_ERROR_S = -1, /**< */
    SRECORD_ERROR_HEXA = -2,
    SRECORD_ERROR_LINE = -3 ,
    SRECORD_ERROR_BYTE_COUNT = -4,
    SRECORD_ERROR_CHECK_SUM = -5,
    SRECORD_ERROR_ADDRESS_FIELD = -6,     /**< Error code for error from invalid arguments passed to function. */
    SRECORD_ERROR_FILE = -7,
    SRECORD_ERROR_TYPE = -8,
    SRECORD_ERROR_EOF = -9,
    SRECORD_ERROR_DATA_LENGTH = -10,
};

enum SrecordTypes
{
    SRECORD_TYPE_S0 = 0, /**< Header record, although there is an official format by 3rd-parties.
                            16 bit address normally set to 0x0000 and header information is stored in data field.
                            This record is unnecessary and commonly not used. */
    SRECORD_TYPE_S1 = 1, /**< Data record with 16-bit address <=> 4 bytes */
    SRECORD_TYPE_S2 = 2, /**< Data record with 24-bit address <=> 6 bytes */
    SRECORD_TYPE_S3 = 3, /**< Data record with 32-bit address <=> 8 bytes */
    SRECORD_TYPE_S4 = 4, /**< A few company use it, included FSoft */
    SRECORD_TYPE_S5 = 5, /**< 16-bit count field that contains the number of S1, S2 and S3 records transmitted. 
                            No data field. */
    SRECORD_TYPE_S6 = 6, /**< 24-bit count field that contains the number of S1, S2 and S3 records transmitted. 
                            No data field. */
    SRECORD_TYPE_S7 = 7, /**< Termination record for S3 data records. 
                            32-bit address field contains address of the entry point after the S-Record file has been processed.
                            No data field. */
    SRECORD_TYPE_S8 = 8, /**< Termination record for S2 data records. 
                            24-bit address field contains address of the entry point after the S-Record file has been processed.
                            No data field. */
    SRECORD_TYPE_S9 = 9, /**< Termination record for S1 data records. 
                            16-bit address field contains address of the entry point after the S-Record file has been processed.
                            No data field. */
};

/**
 * Structure to hold the fields of a Motorola S-Record record
 */
typedef struct SREC
{
    uint8_t type; /**< The Motorola S-Record type of this record (S0 - S9). */
    uint32_t address; /**< The address field. This can be 16, 24 or 32 bits depending on the record type. */
    uint8_t data[SRECORD_MAX_DATA_LENGTH/2]; /**< The 8-bit array data field, which has a maximum size of 32 bytes. */ 
    uint32_t dataLength; /**< The number of bytes of data stored in this record.  */
    uint8_t checkSum; /**< The CheckSum of this record. */
    uint8_t bytecount;
    uint8_t dataOffset;
} SRecord;

/**
 * @brief Sets all of the record field of a Motorola S-Record structure
 * 
 * @param type The Motorola S-Record type (S0 - S9)
 * @param address The actual size of address (16, 24, 32) depends on the S-Record type.
 * @param data A pointer to the 8-bit array of data 
 * @param datalength The size of 8-bit array. 
 * @param srecord A pointer to the target Motorola S-Record structure where these field will be set
 * @return SRECORD_OK if success
 * @retVal
 */
int New_Srecord(uint8_t type, uint32_t address, const uint8_t *data, uint32_t datalength, SRecord *srecord);
/****************************************************************************************
 * Prototypes
 ***************************************************************************************/

/**
 * @brief Check file
 * 
 * @param srecord 
 * @param fp 
 * @return int8_t 
 */
int8_t Check_File(SRecord *srecord, FILE *fp);

/**
 * @brief Check hexa.
 * 
 * @param srecord A pointer to the Motorola S-Record structure.
 * @return SRECORD_CORRECT on success, otherwise one of the SRECORD_ERROR_error codes.
 * @retval SRECORD_CORRECT on success.
 * @retval SRECORD_ERROR_HEXA if one character in a line isn't a hex character (except first character 'S' )
 */
int8_t Check_Hexa( char *ptr);

/**
 * @brief check S
 * 
 * @param srecord 
 * @return SRECORD_CORRECT on success, otherwise one of the SRECORD_ERROR_error codes.
 * @retval SRECORD_CORRECT on success.
 * @retval SRECORD_ERROR_S if first character isn't 'S'.
 */
int8_t Check_S(char *ptr);

/**
 * @brief Check Type of SREC
 * 
 * @param srecord A pointer to the Motorola S-Record structure.
 * @return SRECORD_CORRECT on success, otherwise one of the SRECORD_ERROR_error codes.
 * @retval SRECORD_CORRECT on success.
 * @retval SRECORD_ERROR_TYPE if second character isn't S0-S9 (except S4)
 */
int8_t Check_Type(SRecord *srecord);

/**
 * @brief Calculate numbers of characters in line from address to checksum
 * 
 * @param srecord A pointer to the Motorola S-Record structure.
 * @param ptr A pointer to the recordBuffer.
 * @return SRECORD_CORRECT on success, otherwise one of the SRECORD_ERROR_error codes.
 * @retval SRECORD_CORRECT on success.
 * @retval SRECORD_ERROR_BYTE_COUNT if count bytes from address to checksum differ with byte count in this line
 */
int8_t Check_ByteCount(SRecord *srecord, char *ptr);

/**
 * @brief Check address length
 * 
 * @param srecord 
 * @return SRECORD_CORRECT on success, otherwise one of the SRECORD_ERROR_error codes.
 * @retval SRECORD_CORRECT on success.
 * @retval SRECORD_ERROR_ADDRESS_FIELD if 
 */
int8_t Check_AddressLength(char *srecord, uint8_t ASCII_AddressLength);

/**
 * @brief Check data length
 * 
 * @param recordBuffer A pointer
 * @param ASCII_DataLength 
 * @return int8_t 
 */
int8_t Check_DataLength(uint8_t ASCII_DataLength);
/**
 * @brief Utility function to calculate the checksum of an S-Record 
 * 
 * @param length 
 * @param srecord A pointer to the Motorola S-Record structure.
 * @return int8_t 
 */
int8_t Check_Sum(const SRecord *srecord);

void Print_Error(int8_t check);

#endif /* H_CHECK_BOOL_H */

