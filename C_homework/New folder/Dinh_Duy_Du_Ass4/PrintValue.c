#include "allocate10Bytes.h"

void printAddress (uint8_t *ptr)
{
    uint32_t v;
    printf("Nhap gia tri v = ");
    scanf("%u",&v);
    *ptr = v;
    printf("Gia tri cua bien con tro la: %u", *ptr);
    free(ptr);
}
