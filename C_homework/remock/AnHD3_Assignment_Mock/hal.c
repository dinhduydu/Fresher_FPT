/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "hal.h"

/******************************************************************************
 * Variables
 ******************************************************************************/
static FILE* s_image = NULL; /* Declare pointer of File */

/******************************************************************************
 * Code
 ******************************************************************************/
bool kmc_open_img_file(const uint8_t* const filePath)
{
    bool retVal = true; /* Return true or false */
    s_image = fopen(filePath,"rb"); /* Initialize pointer for file, "rb" means read binary file */
    /* Check Pointer, return false if cannot open */
    if (s_image == NULL)
    {
        retVal = false;
    }
    else
    {
        s_sectorSize = KMC_BYTE_PER_SEC_IN_RDET; /* Assign size 512 for static variable */
    }
    return retVal;
}

int32_t kmc_read_sector(uint32_t index, uint8_t *buff)
{
    size_t numberOfByte = 0; /* To return number of bytes have been read */
    fseek(fptr, index * 512, SEEK_SET);
    numberOfByte = fread(buff, 1, BYTE_PER_SEC, fptr); /* Each byte is a element */
    return numberOfByte;
}

int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff)
{
    size_t numberOfByte = 0; /* To return number of bytes when reading multi sector */
    uint64_t offSet = 0U; /* Position need to read byte */
    uint8_t i = 0U; 
    fseek(s_image, index*BYTE_PER_SEC, SEEK_SET);
	for (i = 0; i < num; j++)
	{
		offSet = (uint64)(i*BYTE_PER_SEC);
		/* Total number elemnt has been read successful */
		numberOfByte += fread(buff[offset], 1, (size_t)num*BYTE_PER_SEC, s_image); 
	} 
    return (uint32_t)numberOfByte ;
}

bool kmc_close_img_file(void)
{
    bool retVal = true;
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
