#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************
 * Function
 **************************************************/

void Menu_Option(uint8_t *Array, uint8_t n)
{
    printf("\n\tPlease wait program responding....");
    char choose;
    do
    {
        choose = Menu_Display();
        switch (choose)
        {
            case 'c':
                Add_New_Array(Array, n);
                break;
            case 'p':
                Menu_PrintArray(Array, n);
                break;
            case 'i':
                Add_AtIndex(Array, n);
                break;
            case 'd':
                Remove_Element(Array, n);
                break;
            case 's':
                Sort_Up(Array, n);
                break;
            case 'x':
                Sort_Down(Array, n);
                break;
            case 't':
                Menu_SearchValue(Array, n);
                break;
            case 'a':
                Find_MaxElement(Array, n);
                break;
            case 'w':
                Find_MinElement(Array, n);
                break;
            case 'e':
                Menu_ExitProgram();
                break;
        }
    }
    while (choose!='c'||choose!='p'||choose!='i'||choose!='d'||choose!='s'||choose!='x'||choose!='t'||choose!='a'||choose!='w'||choose!='e');
}

/* Function check wrong input */
int clean_stdin()
{
    while(getchar()!='\n');
    return 1;
}

char Menu_Display(void)
{
    char type;
    char c;
    system("cls"); /* Clear the screen after enter each character */
    /* User manual */
    printf("\t\t\tPROGRAM MANGAGE SERIAL NUMBERS USING ARRAY\n");
    printf("\t\t=======================================================\n");
    printf("\t\t<Array have 100 element, value valid is from 1 to 100.>\n ");
    printf("\t\t=======================================================\n");
    printf("\t\t\t   USER MANUAL\n");
    printf("\n");
    printf("\t+------------------------------------------------------------------------------------------------------------+\n");
    printf("\t|1. Press 'c' tp clear data of old array and allow user enter new array.                                     |\n");
    printf("\t|2. Press 'p' to print array (If array has no value yet, printf array empty).                                |\n");
    printf("\t|3. Press 'i' to add 1 element into array with index k.                                                      |\n");
    printf("\t|4. Press 'd' to delete a 1 element at index k.                                                              |\n");
    printf("\t|5. Press 's' to sort ascending array and print it.                                                          |\n");
    printf("\t|6. Press 'x' to sort descending array and print it.                                                         |\n");
    printf("\t|7. Press 't' to find the element (from keyboard) in serial array.                                           |\n");
    printf("\t|8. Press 'a' to print maximum element.                                                                      |\n");
    printf("\t|9. Press 'w' to print minium element.                                                                       |\n");
    printf("\t|10. Press 'e' to exit program.                                                                              |\n");
    printf("\t+------------------------------------------------------------------------------------------------------------+\n");
    do
    {
        printf("\n\tEnter a character = ");
    }
    while ((scanf("%c%c", &type, &c)!=2||c!='\n')&&clean_stdin());
    return type;
}

void Menu_PrintArray(uint8_t *Array, uint8_t n)
{
    uint8_t index;
    printf("\n\tPrint all elements in array\n");
    n = strlen(Array);
    if (Array[0] == 0)
    {
        printf("\n\tNo elements in array.");
    }
    else
    {
        for (index = 0; index < n; index++)
        {
            printf("\n\tArray[%d]=%d\n",index, Array[index]);
        }
    }
    printf("\n\t<Press ENTER to go back Menu page.>");
    getch();
}

void Menu_SearchValue(uint8_t *Array, uint8_t n)
{

    uint8_t x;/*The value we want to search in array*/
    uint8_t i;/*Tool value*/
    uint8_t j;/*Declare j value to save search result*/
    n = strlen(Array);
    printf("\n----------------\n");
    printf("\n\tFind value in array\n");
    printf("------------------\n");
    /*  Press to find that value */
    do
    {
        printf("\n\tPress value need to be search: ");
        scanf("%u",&x);
    }
    while (x<0||x>n); /* If we enter the unqualified value, we must enter diferent value again*/
    /* Searching value in array */
    for(i=0; i<n; i++)
    {
        if(x==Array[i])
        {
            j=i;
        }
    }
    /* If j has search address, the results will be displayed */
    if(j > 0)
    {
        printf("\n\tFinded value %u in position at %u.\n",x,j);
    }
    else
    {
        printf("\n\tHAVEN'T FINDED EQUAL VALUE IN ARRAY = %d\n", x);
    }
    printf("\n\tPress ENTER to continue");
    getch();
}

void Menu_ExitProgram(void)
{
    printf("\nExit program...");
    exit(0); /* Immediately end the program */
}
