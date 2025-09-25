#include "header.h"
/*======================================Function that adds 1 element to the kth position in the array=====================================*/
void Add_Element(void)
{
/*--------------------------------------------------------Declare local variable----------------------------------------------------------*/
    uint32_t k;/*position which will be added BUT type of scanf is 32bytes*/
    uint8_t k1;/*position which will be added*/
    uint8_t i;/*Tool value*/
    uint8_t Val;/*This value will be filled in k th position*/
/*--------------------------------------------------------Press the k th position--------------------------------------------------------*/
    printf("Nhap vi tri thu k can chen gia tri vao: \n");
    scanf("%u", &k);
/*--Assign k to k1 to save the position kth that we want to assign value to k th element, If not, k wil be reset to 0 after we scanf Val-*/
    k1=k;
/*---------------------------------------------------------block condition of k Value-----------------------------------------------------*/
    if (k<0)
    {
        k =0;/*If k < 0 => k =0*/
    }
    else if (k> g_n)
    {
        k = g_n;/*If k > 100 => k =100*/
    }
/*----------------------------------------------------Press the Value which we want-------------------------------------------------------*/
    printf("Nhap gia tri Val can chen vao vi tri thu k: \n");
    scanf("%u", &Val);
/*-------------------------------------------------------block condition of Val Value------------------------------------------------------*/
    if (Val<0)
    {
    
        Val =0;/*If Val < 0 => Val = 0*/
    }
    else if (Val>100)
    {
        Val = 100;/*If val> 100 => Val = 100*/
    }
/*--------------------------------------------------Shift array to the right before adding element-----------------------------------------------------*/
    for (i = g_n; i>k1; i--)
    {
        g_Mang[i] = g_Mang[i-1];/*Shift array*/
    }
    g_Mang[k1]=Val;/*Fill value in position k th */
    ++g_n;
/*---------------------------------------------------------Print vicinity Value-----------------------------------------------------------*/
    printf("Cac gia tri lan can la: \n");
    for (i=k1-2; i < k1+3; i++)
    {
        printf("Mang[%d]=%d\n",i, g_Mang[i]);
    }
/*------------------------------------------------------Press ENTER to continue-----------------------------------------------------------*/
    printf("\nBam ENTER de tiep tuc");
    getch();
}

/*===================================Function that remove 1 element to the kth position in the array======================================*/
void Remove_Element(void)
{
/*----------------------------------------------------------Declare local variable--------------------------------------------------------*/
    uint32_t k;/*position which will be added BUT type of scanf is 32bytes*/
    uint8_t k1;/*Position which will be remove.*/
    uint8_t i;/*Tool value*/
/*----------------------------------------------------------Press the k th position-------------------------------------------------------*/
    printf("Nhap vi tri thu k can xoa gia tri: \n");
    scanf("%u", &k);
/*-----------------------------------------------------------block condition of k Value---------------------------------------------------*/
    if (k<0)
    {
        k =0;
    }
    else if (k >= g_n)
    {
        k = g_n-1;
    }
/*----------------------------------------------------------Shift array to the left before removing element-------------------------------------------*/
    for (i=k; i < g_n; i++)
    {
        g_Mang[i] = g_Mang[i+1];
        g_Mang[g_n] = '\0';
    }
    --g_n;
/*-------------------------------------------------------------Print vicinity Value-------------------------------------------------------*/
    printf("Cac gia tri lan can la: \n");
    for (i=k-2; i < k+3; i++)
    {
        printf("Mang[%d]=%d\n",i, g_Mang[i]);
    }
/*---------------------------------------------------------Press ENTER to continue--------------------------------------------------------*/
    printf("\nBam ENTER de tiep tuc");
    getch();
}
