#include "header.h"
#include <string.h>
#include <stdio.h>

/************************************************************************
 * Function
 ************************************************************************/

void Remove_Element(uint8_t *Array, uint8_t n)
{
    uint32_t k;/*Declare position which will be added BUT type of scanf is 32bytes*/
    uint8_t k1;/*Declare Position which will be remove.*/
    uint8_t index;/*Declare Tool value*/
    n = strlen(Array);
    printf("\n\tEnter k position need to be deleted");
    scanf("%u", &k); /* Press the k th position */
    /* block condition of k Value-*/
    if (k < 0)
    {
        k = 0;
    }
    else if (k >= n)
    {
        k = n-1;
    }
    k1 = k;
    /* Shift array to the left before removing element */
    for (index = k1; index < n; index++)
    {
        Array[index] = Array[index+1];
        Array[n] = 0;
    }
    --n;
    printf("\n\tPrint vicinity Value:\n");
    for (index = k1-2; index < k1 + 3; index++)
    {
        printf("Array[%d]=%d\n", index, Array[index]);
    }
    printf("\n\tress ENTER to continue");
    getch();
}
