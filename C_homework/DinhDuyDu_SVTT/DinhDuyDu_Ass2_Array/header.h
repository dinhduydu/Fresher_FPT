/**
 * @file header.h
 * @author Dinh Duy Du (DuDD@fsoft.com.vn)
 * @brief header of all file.c in this project
 * @version 0.1
 * @date 2022-07-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/***/
#ifndef _HEADER_H_
#define _HEADER_H_

#define MAX_ELEMENT 100
#include <stdint.h>

/*****************************************************************************************************
 * Prototype
 ****************************************************************************************************/
/**
 * @brief Function used to display menu
 * 
 * @return char 
 */
char Menu_Display(void);

/**
 * @brief Enter new array.
 * 
 * @param Array an array allow user enter number of elements.
 * @param n elements of that array.
 */
void Add_New_Array(uint8_t *Array, uint8_t n);

/**
 * @brief Add element at index of array.
 * 
 * @param Array an array allow user enter number of elements.
 * @param n elements of that array.
 */
void Add_AtIndex(uint8_t *Array, uint8_t n);


/**
 * @brief Print all element values in array.
 * 
 * @param Array an array allow user enter number of elements.
 * @param n elements of that array.
 */
void Menu_PrintArray(uint8_t *Array, uint8_t n);

/**
 * @brief Function that remove 1 element to the kth position in the array.
 * 
 * @param Array an array allow user enter number of elements.
 * @param n elements of that array.
 */
void Remove_Element(uint8_t *Array, uint8_t n);
/**
 * @brief Sort array in ascending order - Bubble sort.
 * 
 * @param Array an array allow user enter number of elements.
 * @param n elements of that array.
 */
void Sort_Up(uint8_t *Array, uint8_t n);
/**
 * @brief Sort array in descending orde - Bubble sort.
 * 
 * @param Array an array allow user enter number of elements.
 * @param n elements of that array.
 */
void Sort_Down(uint8_t *Array, uint8_t n);

/**
 * @brief Function searches a value in an array.
 * 
 * @param Array an array allow user enter number of elements.
 * @param n elements of that array.
 */
void Menu_SearchValue(uint8_t *Array, uint8_t n);

/**
 * @brief Function finds the maximum number in an array.
 * 
 * @param Array an array allow user enter number of elements.
 * @param n elements of that array.
 */
void Find_MaxElement(uint8_t *Array, uint8_t n);

/**
 * @brief Function finds the minium number in an array.
 * 
 * @param Array an array allow user enter number of elements.
 * @param n elements of that array.
 */
void Find_MinElemnt(uint8_t *Array, uint8_t n);

/**
 * @brief Function to exit program
 * 
 */
void Menu_ExitProgram(void);

/**
 * @brief Show menu display.
 * 
 * @param Array an array allow user enter number of elements.
 * @param n elements of that array.
 */
void Menu_Option(uint8_t *Array, uint8_t n);

#endif /* _HEADER_H_ */

