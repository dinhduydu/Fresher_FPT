#include "header.h"
#include <time.h>
/*========================================================Function to display Menu.======================================================*/
char Display_Menu(void)
{
/*----------------------------------------------------Clear the screen after enter each character----------------------------------------*/
    system("cls");
/*-----------------------------------------------------------User manual------------------------------------------------------------------*/
    printf("CT QUAN LY DAY SO BANG MANG\n");
    printf("=====================\n");
    printf("Mang gom 100 phan tu\n ");
    printf("=====================\n");
    printf("HUONG DAN SU DUNG:\n");
    printf("\n");
    printf("1. Nhap 'c' de clear data cua mang cu va cho nguoi dung nhap.\n");
    printf("2. Nhap 'p' de in day (Neu day chua co gia tri thi bao day trong).\n");
    printf("3. Nhap 'i' de them 1 phan tu vao day voi vi tri k (Neu co roi thi khong cho nua).\n");
    printf("4. Nhap 'd' de xoa 1 phan tu tai vi tri thu k (Neu vi tri k khong chua gia tri thi bao ko co phan tu k).\n");
    printf("5. Nhap 's' de in ra day sap xep day so the chieu tang dan.\n");
    printf("5. Nhap 'x' de in ra day sap xep day so the chieu giam dan.\n");
    printf("6. Nhap 't' de tim kiem 1 so x co trong day khong (x nhap tu ban phim)? --> Neu co thi dua ra vi tri.\n");
    printf("7. Nhap 'a' de in ra man hinh so lon nhat.\n");
    printf("8. Nhap 'w' de in ra man hinh so be nhat.\n");
    printf("9. Nhap 'e' de thoat chuong trinh.\n");
/*--------------------------------------------------------------------Press character-----------------------------------------------------*/
    printf("Ban chon: ");
    char chon;
    scanf("%c",&chon);
    return chon;
}

/*=======================================================Enter random values==============================================================*/
int random(int minN, int maxN)
{
    return minN + rand() % (maxN + 1 - minN);
}
void Enter_Random(void)
{
/*-----------------------------------------------------------------------------------------------------------------------------------------
    Enter an array of 100 elements.
    However, instead of entering 100 values, the computer will enter in a random way
------------------------------------------------------------------------------------------------------------------------------------------*/
    srand((int)time(0));
    uint8_t i = 0;
    for(i = 0; i < g_n; ++i)
    {
        g_Mang[i] = random(1,g_n);
    }
}
/*=======================================================Enter manual values==============================================================*/
void Enter_Manual()
{
    uint8_t i =0;
    for (i=0;i<g_n;i++)
    {
        printf ("Nhap Mang[%u] =",i);
        scanf("%u", &g_Mang[i]);
        if (g_Mang[i]>100||g_Mang[i]<0)
        {
            printf("Nhap lai Mang[%u]",i);
            scanf("%u", &g_Mang[i]);
        }
    }
}
/*==================================================Enter the number of elements of the array=============================================*/
void Enter_New_Array(void)
{
    uint32_t mode;
    printf("\n----------------------\n");
    printf("NHAP MANG MOI\n");
    printf("=====================\n");
    printf("CHON MOT TRONG HAI CHE DO:\n");
    printf("=====================\n");
    printf("CHE DO NHAP RANDOM THI BAM 1:\n");
    printf("CHE DO NHAP BANG TAY THI BAM 2:\n");
    printf("NHAP CHE DO MA BAN MONG MUON:\n");
    
scanf("%u", &mode);
    printf("mode la %u\n", mode);
//    while(mode!=1||mode!=2);
    if (mode == 1)
    {
        Enter_Random();
    }
    else if (mode = 2)
    {
        Enter_Manual();
    }
    else 
    {
        exit(0);
    }
/*-----------------------------------------------------------------Done!-----------------------------------------------------------------*/
    printf("DA NHAP XONG\n");
    printf("=============\n");
    printf("");
/*-----------------------------------------------------------Press ENTER to continue------------------------------------------------------*/
    printf("\nBam ENTER de tiep tuc va sau do bam p de in ra mang");
    getch();
}

/*===========================================================Function to print array.=====================================================*/
void Print_Array(void)
{
    printf("\n-----------------\n");
    printf("IN RA GIA TRI CUA CAC PHAN TU TRONG MANG\n");
    printf("-------------------\n");

/*--------------------------------------------------------Print all element values in array-----------------------------------------------*/
    uint8_t i;
    for (i=0; i < g_n; i++)
    {
        printf("Mang[%d]=%d\n",i, g_Mang[i]);
    }
/*-----------------------------------------------------------Press ENTER to continue------------------------------------------------------*/
    printf("\nBam ENTER de tiep tuc");
    getch();
}
