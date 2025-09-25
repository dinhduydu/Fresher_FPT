/**
 * @file Convert.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef H_CONVERT_H
#define H_CONVERT_H
#include "Check.h"

#define LINE 10

extern uint8_t SRecord_Address_Lengths[];

/*****************************************************************************************
 * Prototypes
 *****************************************************************************************/

/**
 * @brief Initializes a new SRecord structure that the parameter SREC point to with the pass
 * 
 * @param type S-Record type
 * @param address up to 32-bit uint32_t address
 * @param data 8-bit data array
 * @param datalength size of 8-bit data array 
 * @param srecord 
 * @return int 
 */
//int New_Srecord(uint8_t type, uint32_t address, const uint8_t *data, uint32_t datalength, SRecord *srecord);


void Convert_Type (SRecord *srecord, char *hexBuffer, char *recordBuffer);
void Convert_AddressLength (SRecord *srecord, char *hexBuffer, char *recordBuffer, uint8_t ASCII_AddressLength);
void Convert_ByteCount (SRecord *srecord, char *hexBuffer, char *recordBuffer);
void Read_SRecord (SRecord *srecord, FILE *fp);
void Print_SRecord(SRecord *srecord);
void Convert_CheckSum (SRecord *srecord, char *hexBuffer, char *recordBuffer, uint8_t ASCII_AddressLength );
void Convert_DataLength (SRecord *srecord,char *hexBuffer, char *recordBuffer, uint8_t ASCII_DataLength);
#endif /* H_CONVERT_H */

