/**
 * @file lib.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _LIB_H_
#define _LIB_H_
/*************************************************************************************************************************
 * Define Enum type
 ************************************************************************************************************************/
/**
 * @brief Define code error
 * 
 */
typedef enum _statetype 
{ 

    CORRECT, 

    CHAR_INVALID, 

    LENGHT_INVALID 

}status_enum_t; 

typedef void(*func)(char *str);

/*************************************************************************************************************************
 * Prototype
*************************************************************************************************************************/

/**
 * @brief Call back function 
 * 
 * @param func_add 
 */
void RegisterCallback(func func_add);  

/**
 * @brief 
 * 
 * @param ptr 
 * @param lenght 
 */
void Check_Account(char* ptr, uint8_t lenght); 

#endif /*_LIB_H_*/
