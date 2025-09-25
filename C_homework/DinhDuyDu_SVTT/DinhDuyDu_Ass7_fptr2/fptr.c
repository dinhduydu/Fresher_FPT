#include "fptr.h"
#include <stdio.h>

status_enum_t retValue;



uint8_t Check_Account (char *ptr, uint8_t length)
{   
    uint8_t index;
    uint8_t find = 0;
    uint8_t retValue;
    for (index = 0; index < length; index++)
    {
        if ((ptr[index]>= ' ' &&ptr[index]<= '/')||(ptr[index] >= ':' && ptr[index]<= '@')||(ptr[index]>='['&&ptr[index]<='`')||(ptr[index]>='{'&&ptr[index]<=' '))
        {
            find = 1;
            printf("\n\tString containing special characters\n", ptr);
            retValue = CHAR_INVALID;
            break;
        }
    }
    if (find == 0)
    {
        retValue= CORRECT;
        printf("\n\tString %s hasn't contained special characters.\n", ptr);
    }
    else if (length > 10)
    {    
        retValue = LENGTH_INVALID;
    }
    return retValue;
}

void RegisterCallback(char *ptr,func func_add)
{
    return func_add(ptr);
}

void check(status_enum_t x)
{
    switch (x)
    {
        case LENGTH_INVALID:
            printf("\n\t<Length invalid>\n");
            break;
        case CHAR_INVALID:
            printf("\n\t<Char invalid>\n");
            break;
        case CORRECT:
            printf("\n\t<Correct>");    
            break;
    }
}
