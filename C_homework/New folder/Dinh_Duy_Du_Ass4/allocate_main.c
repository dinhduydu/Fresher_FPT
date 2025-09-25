#include "allocate10Bytes.h"


int main()
{
    uint8_t* ptr;
    char chon;
    do 
    {
        chon = Scanf();
        switch (chon)
        {
/*Write a program to dynamically allocate 10 bytes of memory for a pointer:*/
            case 'a':
                allocateMemory(ptr);
                break;
            case 'e':
                exitProgram();
                break;
        }
    }
    while(chon!='a'||chon!='e');
    return 1;
}
