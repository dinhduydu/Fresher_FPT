#include "header.h"

void main (void)
{
    char type ;
    do
    {
        type = Display_Menu();
        switch(type)
        {
            case 't':
                Type();
                break;
            case 'e':
                printf("Exit Program ....");
                exit(0);
                break;
        }
    }
    while (type!='t'||type!='e');
}
