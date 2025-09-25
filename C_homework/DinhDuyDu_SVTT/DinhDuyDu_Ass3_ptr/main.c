#include <stdio.h>
#include "header.h"

int main(void) 
{
    /*declare pointer, this pointer just has a address but doesn't have memory, 
    data type of this pointer (uint8_t*) must same data type of variable which this pointer point to.*/
    uint8_t *p = 0;/*NULL --> this pointer doesn't point anywhere*/
    /*argument is address --> casting address to (uint8_t) because the propotype is constant*/
    HEADER_Status_t Status;
    bool check = allocate10Bytes( (uint8_t*)&p );
    if (HEADER_OK != freeMemory(check, p))
    {
        printf("\n\t<Can't free>");
    }
    else
    {
        printf("\n\t<Free successful");
    }
}
