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
 * Define to prevent recursive inclusion 
**********************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
* Macros
******************************************************************************/

#define KMC_BYTE_PER_SEC_IN_RDET 512                  
/* Define number byte of boot sector, default 512 byte*/
/* #define SIZE_OF_SECTOR 512 */

/*******************************************************************************
* Prototypes
******************************************************************************/

/**
 * @brief Initialize pointer file and size of sector
 * 
 * @param filePath Pointer of file
 * @return true 
 * @return false 
 */
bool kmc_open_img_file(const uint8_t *filePath);

/**
 * @brief Update size of sector, for different Fat type
 * 
 * @param sectorSize size of sector
 * @return true 
 * @return false 
 */
bool kmc_update_sector_size(uint32_t sectorSize);

/**
 * @brief Read number bytes in one sector
 * 
 * @param index Sector need to access
 * @param buff Buffer need to store
 * @return int32_t 
 * @retval bytes were read
 */
int32_t kmc_read_sector(const uint32_t index, uint8_t *buff);

/**
 * @brief Read number bytes of multiple sectors
 * 
 * @param index Start sector
 * @param num Number of sector need to read
 * @param buff Buffer need to store
 * @return int32_t 
 * @retval return value bytes were read
 */
int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff);

/**
 * @brief Delete initialization of file and pointer of file including close of file
 * 
 * @return true 
 * @return false 
 */
bool kmc_close_img_file(void);

#endif/* __HAL_H_*/
