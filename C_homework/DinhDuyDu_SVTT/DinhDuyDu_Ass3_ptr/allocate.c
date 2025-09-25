#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "header.h"

/*r*/
bool allocate10Bytes(uint8_t *outPtr )
{
    const size_t N = 10; /* 10 Bytes*/
    uint8_t **p2p = (uint8_t**)outPtr; /* p2p is pointer to pointer to value of type uint8_t */
    *p2p = (uint8_t*)calloc(N,sizeof(uint8_t)); /* datatypes is 1 byte --> 10*1 byte = 10 bytes */
    return *p2p != NULL; /* memory has been allocated to the pointer then this function will return TRUE */
}

HEADER_Status_t freeMemory(bool check, uint8_t *p)
{
    HEADER_Status_t retval;
    if (check == true)
    {
        retval = HEADER_OK;
        free( p );
    }
    else
    {
    	retval = HEADER_ERROR;
	}
    return retval;
}