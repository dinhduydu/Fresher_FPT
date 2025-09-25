#include "header.h"

/*===============================================Function to find the maximum number in an array=========================================*/
int Find_Max_Number(void)
{
    printf("\n------------------------\n");
    printf("TIM SO LON NHAT TRONG MANG\n");
    printf("--------------------------\n");

    uint8_t max = g_Mang[0];/*Assign the first element to max variable*/
    uint8_t i;/*tool variable to check the maximum element*/
    
/*--------------------------------------------Find the maximum value by comparing adjacent values----------------------------------------*/
    for (i=1; i<g_n; i++)
    {
        if (max < g_Mang[i])
        {
            max = g_Mang[i];
        }
    }
/*-------------------------------------------------------Just print the maximum value----------------------------------------------------*/
    printf("\nGia tri lon nhat trong mang la: %d", max);
    getch();
    return max;

/*-------------------------------------------------------Press ENTER to continue---------------------------------------------------------*/
    printf("\nBam ENTER de tiep tuc");
    getch();
}

/*=========================================Function to find the minium number in an array=================================================*/
int Find_Min_Number(void)
{
    printf("\n------------------------\n");
    printf("TIM SO BE NHAT TRONG MANG\n");
    printf("--------------------------\n");

    uint8_t min = g_Mang[0];/*Assign the first element to min variable*/
    uint8_t i;/*tool variable to check the minium element*/
    
/*---------------------------------------Find the maximum value by comparing adjacent values----------------------------------------------*/
    for (i=1; i<g_n; i++)
    {
        if (min > g_Mang[i])
        {
            min = g_Mang[i];
        }
    }
    
    /*Just print the maximum value*/
    printf("\nGia tri be nhat trong mang la: %d", min);	
    getch();
    return min;

    /*Press ENTER to continue.*/
    printf("\nBam ENTER de tiep tuc");
    getch();
}

/*==========================================================Function to exit program===============================================================*/
void Exit_Program(void)
{
    printf("\nExit program...");
    /*Immediately end the program*/
    exit(0);
}
