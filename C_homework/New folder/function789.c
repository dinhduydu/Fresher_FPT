#include "header.h"

/*===================================================Sort array in ascending order=======================================================*/
void Sort_Up(void)
{
    uint8_t tg = 0;
    uint8_t i = 0;
    uint8_t j = 0;
/*---------------------------------------------Search from 0th element to 100 element----------------------------------------------------*/
    for (i = 0; i < g_n - 1; i++)
    {
        for(j=i+1; j<g_n; j++)
        {
            if(g_Mang[i] > g_Mang[j])
            {
/*----------------------------------------------Replace 2 element i th and (i-1) th-------------------------------------------------------*/
                tg = g_Mang[i];
                g_Mang[i] = g_Mang[j];
                g_Mang[j] = tg;
            }
        }
    }
    for (i=0; i < g_n; i++)
    {
        printf("Mang[%d]=%d\n",i, g_Mang[i]);
    }
/*-------------------------------------------------------Press ENTER to continue----------------------------------------------------------*/
    printf("\nBam ENTER de tiep tuc");
    getch();
}

/*=================================================Sort array in descending order=========================================================*/
void Sort_Down(void)
{
    uint8_t tg;
    uint8_t i;
    uint8_t j;
/*---------------------------------------------Search from 0th element to 100 element-----------------------------------------------------*/
    for (i = 0; i < g_n - 1; i++)
    {
        for(j=i+1;j < g_n; j++)
        {
            if(g_Mang[i] < g_Mang[j])
            {
/*----------------------------------------------Replace 2 element i th and (i-1) th-------------------------------------------------------*/
                tg = g_Mang[i];
                g_Mang[i] = g_Mang[j];
                g_Mang[j] = tg;
            }
        }
    }
    g_n--;
    for (i=0; i < g_n; i++)
    {
        printf("Mang[%d]=%d\n",i, g_Mang[i]);
    }
/*--------------------------------------------------Press ENTER to continue---------------------------------------------------------------*/
    printf("\nBam ENTER de tiep tuc");
    getch();
}
/*=========================================Function that searches for a value in an array=================================================*/
int Search_Value(void)
{
    printf("\n----------------\n");
    printf("TIM KIEM GIA TRI TRONG MANG\n");
    printf("------------------\n");
    uint8_t x;/*The value we want to search in array*/
    uint8_t i;/*Tool value*/
    uint8_t j;/*Declare j value to save search result*/
/*-------------------------------------------------------Press to find that value---------------------------------------------------------*/
    do
    {
    printf("Nhap gia tri x: ");
    scanf("%d",&x);
    }
/*----------------------------------If we enter the unqualified value, we must enter diferent value again--------------------------------*/
    while (x<0||x>g_n);
/*-------------------------------------------------------Searching value in array---------------------------------------------------------*/
    for(i=0; i<g_n; i++)
    {
        if(x==g_Mang[i])
        {
            j=i;
        }
    }
/*----------------------------------------------If j has search address, the results will be displayed------------------------------------*/
    if(j > 0)
    {
        printf("Tim thay so %d tai vi tri thu %d\n",x,j);
    }
    else
    {
        printf("\nKHONG THAY PHAN TU CO GIA TRI BANG = %d\n", x);
    }
/*----------------------------------------------------------Press ENTER to continue-------------------------------------------------------*/
    printf("\nBam ENTER de tiep tuc");
    getch();
    return 0;
}
