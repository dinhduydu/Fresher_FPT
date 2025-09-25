#ifndef _HEADER_H_
#define _HEADER_H_
#include <stdint.h>

/********************************************************************************************
 * Declare enum type 
 *******************************************************************************************/
typedef enum _statetype 
{
    CORRECT, 
    CHAR_INVALID, 
    LENGTH_INVALID 
}status_enum_t;

/*********************************************************************************************
 * Declare typdef function pointer - callback function: pass a pointer to char & return void 
 ********************************************************************************************/
typedef void (*func)(char*);

/*********************************************************************************************
 * Prototype
 *********************************************************************************************/

 
/**
 * @brief check length and any characters in string
 * @retval retValue
 */
uint8_t Check_Account (char *ptr, uint8_t length);

/**
 * @brief Register call back
 * 
 */
void RegisterCallback(char *ptr,func func_add);

/**
 * @brief check status return to print error
 * 
 */
void check (status_enum_t x);

#endif /* _HEADER_H_ */

