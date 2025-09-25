#include "header.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************************
 * Function
 *****************************************************************************************/

void Find_MaxElement(uint8_t *Array, uint8_t n)
{
    printf("\n\t<FIND MAX ELEMENT IN ARRAY>");

    uint8_t max = Array[0];/*Assign the first element to max variable*/
    uint8_t index;/*tool variable to check the maximum element*/
    n = strlen(Array);
    /* Find the maximum value by comparing adjacent values */
    for (index = 1; index < n; index++)
    {
        if (max < Array[index])
        {
            max = Array[index];
        }
    }
    /* Just  */
    printf("\n\tMaximum value in array is: %u", max);
    printf("\n\tPress ENTER to continue");
    getch();
}

void Find_MinElement(uint8_t *Array, uint8_t n)
{
    printf("\n\t<FIND MIN ELEMNT IN ARAY>");
    uint8_t min = Array[0]; /* Assign the first element to min variable */
    uint8_t index;/* tool variable to check the minium element */
    n = strlen(Array);
    /* Find the minium value by comparing adjacent values */
    for (index=1; index< n; index++)
    {
        if (min > Array[index])
        {
            min = Array[index];
        }
    }
    printf("\n\tMinium value in array is: %u", min);
    printf("\n\t<Press ENTER to continue.>");    
    getch();
}



