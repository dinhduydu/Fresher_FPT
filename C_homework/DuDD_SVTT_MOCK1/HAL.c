/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "HAL.h"

/******************************************************************************
 * Variables
 ******************************************************************************/
static FILE* s_image = NULL;                        /* Declare pointer of File */
static uint32_t s_sectorSize = 0U;                  /* Declare variable of sectorSize */

/******************************************************************************
 * Code
 ******************************************************************************/
bool kmc_open_img_file(uint8_t *filePath)
{
    bool retVal = true;                             /* Declare a variable to return true or false */
    s_image = fopen(filePath,"rb");                 /* Initialize pointer for file, "rb" means read binary file  */
    if (s_image == NULL)
    {
        retVal = false;
    }
    else
    {
        s_sectorSize = SIZE_OF_SECTOR;              /* Assign size 512 for size of sector variable */
    }
    return retVal;
}

bool kmc_update_sector_size(uint32_t sectorSize)
{
    bool retVal = true;                             /* Declare a variable to return update size true or false */
    if (sectorSize % 512 == 0)
    {
        s_sectorSize = sectorSize;
    }
    else
    {
        retVal = false;
    }
    return retVal;
}

int32_t kmc_read_sector(uint32_t index, uint8_t *buff)
{
    size_t numberOfByte = 0;                        /* Initialize variable is number of byte which received from function fread */
    /* Check function fseek have do successful, and pick at index need to read */
    if (fseek(s_image, (s_sectorSize*index), SEEK_SET) == 0 )
    {
        numberOfByte = fread(buff, 1U, (size_t)s_sectorSize, s_image);
        if (numberOfByte != s_sectorSize)
        {
            numberOfByte = -1;                      /* Assign pointer at set position */
        }
    }
    return (int32_t)numberOfByte;
}

int32_t kmc_read_multi_sector(uint32_t index,uint32_t num, uint8_t *buff)
{
    size_t numberOfByte = 0;                        /* Declare variable to return number of bytes which had been read */
    size_t numberOfByteTemp = 0;                    /* Declare variable to count number of bytes when reading multi sector*/
    uint64_t offset = 0U; /* Position need to read byte */
    uint32_t i = 0U;
    if (fseek(s_image, (s_sectorSize *index), SEEK_SET) == 0 )
    {
        for (i = 0U; i < num; i++)
        {
            offset = (uint64_t)i * s_sectorSize;    
            numberOfByteTemp += fread(&buff[offset], 1U, (size_t)s_sectorSize, s_image); /* Total number element has been read successful */
		}
        if (numberOfByteTemp == (size_t)num * s_sectorSize)
        {
            numberOfByte = numberOfByteTemp;
        }
    }
    return (int32_t)numberOfByte;
}

bool kmc_close_img_file(void)
{
    bool retVal = true;                         /* Declare a variable to return update size true or false */
    if (fclose(s_image) == 0)
    {
        retVal = true;
        s_image = NULL;
    }
    else 
    {
        retVal = false;
    }
    return retVal;
}