#ifndef HEADER_H_
#define HEADER_H_

/************************************************************************
 * Include
*************************************************************************/
#include <stdbool.h>
#include <stdint.h>

/*************************************************************************
 * Enum
*************************************************************************/
typedef enum
{
    HEADER_OK,
    HEADER_ERROR,
} HEADER_Status_t;
/**************************************
*Prototype
**************************************/

/**
 * @brief Function to allocate 10 Bytes (memory) for a pointer.
 * return bool: true if allocate successful and fail if allocate fail
 */
bool allocate10Bytes(uint8_t *outPtr );

/**
 * @brief Function used to free memory 
 */
HEADER_Status_t freeMemory(bool check, uint8_t *p);
#endif/*HEADER_H*/
/************************************************************************
 * EOF
*************************************************************************/