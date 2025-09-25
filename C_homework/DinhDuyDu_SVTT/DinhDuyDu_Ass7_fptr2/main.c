#include <stdio.h>
#include <stdint.h>
#include "fptr.h"
#include <string.h>

/*****************************************************************
 * Function
 ****************************************************************/

/**
 * @brief function enter string 
 * 
 */
void EnterAccount (char *ptr);

void main(void)
{
    char str[50];
    uint8_t x = 0;
    uint8_t retValue;
    /* enter string */
    printf("\n\tEnter your account name: ");
    RegisterCallback(str,EnterAccount);
    /* print that string */
    printf("\n\tString that you entered: %s\n", str);
    /* get length of that string */
    x = strlen(str);
    printf("\n\tNumber of characters is %u\n", x);
    retValue = Check_Account(str, x);
    check (retValue);
}

void EnterAccount (char *ptr)
{
   gets(ptr); /* function enter string */
}