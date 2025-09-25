#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

/********************************************************************************************************************************************
 * Function
 *******************************************************************************************************************************************/

/* Random values */
int random(int minN, int maxN)
{
    return minN + rand() % (maxN + 1 - minN);
}

/* Enter 100 elements into array. However, instead of entering 100 values, computer will enter in a random way */
void Add_Random(uint8_t *Array)
{
    srand((int)time(0));
    uint8_t index = 0;
    for(index = 0; index < MAX_ELEMENT; ++index)
    {
        Array[index] = random(1,MAX_ELEMENT);
    }
}

/* Enter manual values */
void Add_Manual(uint8_t *Array, uint8_t n)
{
    uint8_t index = 0;
    char c;
    /*Enter the number of elements of the array */
    do
    {
        printf("\n\tEnter number of elements: ");
    }
    while ((scanf("%u%c", &n, &c)!=2||c!='\n')&&clean_stdin());
    for (index = 0;index < n; index ++)
    {
        do 
        {
            printf ("\n\tEnter element of array[%u] =", index);
        }
        while ((scanf("%u%c", &Array[index], &c)!=2||c!='\n')&&clean_stdin()||Array[index]>100||Array[index]<0);
    }
}

void Add_New_Array(uint8_t *Array, uint8_t n)
{
    uint32_t mode;
    char c;
    printf("\n\t\t\tENTER NEW ARRAY\n");
    printf("\t\t=====================\n");
    printf("\tChoose 1 or 2 modes:\n");
    printf("\t=====================\n");
    printf("\t<MODE 1: Press 1 to enter random>\n");
    printf("\t<MODE 2: Press 2 to enter manual>\n");
    do
    {
        printf("\tEnter mode which you want to choose: ");
    }
    while ((scanf("%u%c", &mode, &c)!=2||c!='\n')&&clean_stdin()||mode<1||mode>2);
    if (mode == 1)
    {
        printf("\n\tComputer will enter random\n");
        Add_Random(Array);
    }
    else if (mode = 2)
    {
        printf("\n\tUser enter manual\n");
        Add_Manual(Array, n);
    }
    printf("\n\t\t<Done enter.>\n");
    printf("\t\t=============");
    printf("\n\t<Press ENTER to go back Menu page and press 'p' to print array.>");
    getch();
}

void Add_AtIndex(uint8_t *Array, uint8_t n)
{
    uint32_t k;/* Declare local variable which position which will be added BUT type of scanf is 32bytes*/
    uint8_t k1;/* Declare local variable which position which will be added*/
    uint8_t index;/* Declare tool value*/
    uint32_t checkVal;
    uint8_t Val;/* Declare variable will be filled in k th position*/
    n = strlen(Array);
    printf("\n\tEnter position need to be add: ");
    scanf("%u", &k); /* Press the k th position */
    /* Block condition of k Value */
    if ( k < 0)
    {
        k = 0;/*If k < 0 => k =0*/
    }
    else if (k > n)
    {
        k = n;/*If k > 100 => k =100*/
    }
    k1 = k; /*Assign k to k1 to save the position kth that we want to assign value to k th element, 
            If not, k wil be reset to 0 after we scanf Val-*/
    printf("\n\tPress value need to be added into k position: ");
    scanf("%u", &checkVal); /* Press the Value which we want */
    /* Block condition of Val Value */
    if (checkVal < 0)
    {
        checkVal = 0; /* If Val < 0 => Val = 0 */
    }
    else if (checkVal>100)
    {
        checkVal = 100; /* If val> 100 => Val = 100 */
    }
    Val = checkVal;
    /* Shift array to the right before adding element */
    if (n <=100)
    {
        for (index = n; index > k1; index--)
        {
            Array[index] = Array[index-1];/* Shift array */
        }
        Array[k1] = Val;/* Fill value in position k th */
        ++n;
        printf("\n\tPrint vicinity Value:\n");
        for (index = k1-2; index < k1+3; index++)
        {
            printf("\n\tArray[%d]=%d\n",index, Array[index]);
        }
    }
    else
    {
        printf("\n\tArray is full, can't added");
    }
    printf("\n\t<Press ENTER to continue.>");
    getch();
}
