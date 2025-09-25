#include "lib.h"
#include <stdint.h>

char arr[20];

void RegisterCallback(func func_add)
{

}

void Check_Account(char* ptr, uint8_t length)
{

}

uint8_t Check_Length (char *ptr)
{
    uint8_t index = 0;

    printf("Account name is: \n");
    while (ptr[index] !=NULL )  
    {
        printf("%s", ptr[index]);
        index++;
    }    
}

void Enter_Account(char *ptr)
{
    puts(ptr);
}

/* Creating enum variable */