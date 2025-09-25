/**
 * @file HAL.h
 * @author Dinh Duy Du (DuDD@fsoft.com.vn)
 * @brief This file contains function prototypes to manipulate physical layer (Hardware abtraction layer)
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _HAL_H_
#define _HAL_H_
/**********************************************
 * Include library
**********************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
* Macro
******************************************************************************/
#define SIZE_OF_SECTOR 512                              /* Define number byte of sector, default 512 bytes */

/*******************************************************************************
* API
******************************************************************************/

/**
 * @brief Initialize pointer file and size of sector
 * 
 * @param filePath Pointer of file which user enter
 * @return true if open successful
 * @return false if open failed
 */
bool kmc_open_img_file(uint8_t *filePath);

/**
 * @brief Update size of sector, for different Fat type
 * 
 * @param sectorSize size of sector
 * @return true if size of sector is multiple of 512
 * @return false if it is not multiple of 512
 */
bool kmc_update_sector_size(uint32_t sectorSize);

/**
 * @brief Read number bytes in one sector
 * 
 * @param index Sector need to read
 * @param buff Buffer need to store
 * @return type int32_t 
 * @retval number of bytes were read
 */
int32_t kmc_read_sector(uint32_t index, uint8_t *buff);

/**
 * @brief Read number bytes of multiple sectors
 * 
 * @param index Start sector need to reda
 * @param num Number of sector need to read
 * @param buff Buffer need to store
 * @return type int32_t 
 * @retval number of bytes were read
 */
int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff);

/**
 * @brief Delete initialization of file and pointer of file including close of file
 * 
 * @return true if close successful
 * @return false if close failed
 */
bool kmc_close_img_file(void);

#endif/* __HAL_H_*/
