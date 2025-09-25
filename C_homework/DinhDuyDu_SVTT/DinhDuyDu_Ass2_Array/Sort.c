#include "header.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************************
 * Function
 *****************************************************************************************/

void Sort_Up(uint8_t *Array, uint8_t n)
{
    uint8_t temp = 0;
    uint8_t i = 0;
    uint8_t j = 0;
    n = strlen(Array);
    /* Search from 0th element to 100 element - worth algorithm */
    for (i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(Array[i] > Array[j])
            {
                temp = Array[i]; /* Replace 2 element i th and (i-1) th */
                Array[i] = Array[j];
                Array[j] = temp;
            }
        }
    }
    /* Print array after sort */
    for (i = 0; i < n; i++)
    {
        printf("Array[%d]=%d\n",i, Array[i]);
    }
    printf("\n\t<Press ENTER to continue.>");
    getch();
}

void Sort_Down(uint8_t *Array, uint8_t n)
{
    uint8_t temp;
    uint8_t i;
    uint8_t j;
    n = strlen(Array);
    /* Search from 0th element to 100 element */
    for (i = 0; i < n - 1; i++)
    {
        for(j=i+1;j < n; j++)
        {
            if(Array[i] < Array[j])
            {
    /* Replace 2 element i th and (i-1) th */
                temp = Array[i];
                Array[i] = Array[j];
                Array[j] = temp;
            }
        }
    }
    for (i=0; i < n; i++)
    {
        printf("Array[%d]=%d\n",i, Array[i]);
    }
    printf("\n\t<Press ENTER to continue.>");
    getch();
}
