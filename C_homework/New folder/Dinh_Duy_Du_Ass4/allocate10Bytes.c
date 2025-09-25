#include "allocate10Bytes.h"
/*============================================Function check if pointer has been allocated or not==================================================*/
/*Create a function that allocate 10 bytes dynamically to a pointer, then check whether pointer has been allocated? 
The function must be a boolean one, and return boolean as well.*/

bool allocate10Bytes(uint8_t *outPtr)
{
    bool return_Value = false;
    if (outPtr = NULL)
    {
        return_Value = false;
    }
    else
    {
        return_Value = true;
    }
    return return_Value;
}
/*=====================================================Function to allocate memory successful======================================================*/
void allocateMemory (uint8_t *ptr)
{
    printf("========Allocate memory========\n");
/*pointer of type uint8_t and allocate 10 Bytes of memory for the pointer*/
    ptr = (uint8_t*)calloc(10,sizeof(uint8_t*));
    printf("Gia tri cua bien con tro %d\n", *ptr);
    printf("Gia tri dia chi cua con tro %d\n", &ptr);
    (allocate10Bytes(ptr))?printf("pointer has been allocated successfully\n"):printf("pointer has been allocated failed\n");
    uint32_t v;
    printf("Nhap gia tri v = ");
    scanf("%u",&v);
    *ptr = v;
    printf("Gia tri cua bien con tro la: %u\n", *ptr);
    printf("Gia tri cua bien con tro %d\n", &ptr);
    free(ptr);
    printf("_______________________________\n");
    printf("Press ENTER to continue\n");
    getch();
}
/*==========================================================Function to exit program===============================================================*/
void exitProgram()
{
    printf("Exit Program ...\n");
    printf("Press ENTER to continue\n");
    exit(0);
    getch();
}
