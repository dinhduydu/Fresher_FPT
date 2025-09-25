#include "allocate10Bytes.h"
char Scanf(void)
{
/*----------------------------------------------------Clear the screen after enter each character----------------------------------------*/
    system("cls");
/*-----------------------------------------------------------User manual------------------------------------------------------------------*/
    char choose;
    printf("=======================================\n");
    printf("NHAP KY TU TU BAN PHIM THEO HUONG DAN SAU:\n");
    printf("----------------------------------------------\n");
    printf("1. Nhap 'a' de cap phat bo nho dong 10 bytes cho con tro.\n");
    printf("2. Nhap 'e' de thoat chuong trinh.\n");
    printf("\n");
    printf("Ban chon: %c", choose);
    scanf("%c",&choose);
    return choose;
}
