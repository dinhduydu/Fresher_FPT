#include "header.h"
#include <stdio.h>
/*Function to display Menu.*/
char Display_Menu(void)
{
    /*Clear the screen after enter each character */
    system("cls");
    /*User manual*/
    printf("\n\tPROGRAM TO CALCULATE THE ABSOLUTE VALUE OF THE DIFFERENCE OF 2 POSITIVE NUMBERS\n");
    printf("\t===============================================================================\n");
    printf("\t                                User Manual:\n");
    printf("\t________________________________________________________________________________\n");
    printf("\t1. Press 't' to enter two value of integer a and b from 1 to 255.\n");
    printf("\t2. Press 'e' to exit program.\n");
    /*Press character*/
    printf("\tEnter your choice: ");
    char chon;
    scanf("%c",&chon);
    return chon;
}
