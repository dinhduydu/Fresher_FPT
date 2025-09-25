#include <stdint.h>
#include <stdlib.h>
#include "Linked_List.h"

void Menu (void)
{
    printf("\t                    MENU\n");
    printf("\t  +-------------------------------------------    + \n");
    printf("\t  |        1. Insert a number 0 - 100.             |\n");
    printf("\t  |        2. Delete a number in the list.         |\n");
    printf("\t  |        3. Print.                               |\n");
    printf("\t  |        4. Exit.                                |\n");
    printf("\t  +-------------------------------------------    + \n");
    printf("\tEnter choice: ")
}

uint8_t EnterValue (void)
{
    uint8_t retValue;
    uint32_t enterValue;
    scanf("%u", &enterValue);
    if (enterValue > 0 & enterValue < 256)
    {
        retValue =  enterValue;
    }
    else
    {
        exit(0);
    }
}
