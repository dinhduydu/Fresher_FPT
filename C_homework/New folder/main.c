#include "header.h"
/*******************************
*Variable.
*******************************/
uint8_t g_n = 100;/*variable which stores the number of elements of the array*/
uint8_t g_Mang[100];/*declare array to store elements*/
/*======================Run this program using the console pauser or add your own getch, system("pause") or input loop===================*/
void main(void)
{
    char chon;
    do
    {
        chon = Display_Menu();
        switch (chon)
        {
            case 'c':
                Enter_New_Array();
                break;
            case 'p':
                Print_Array();
                break;
            case 'i':
                Add_Element();
                break;
            case 'd':
                Remove_Element();
                break;
            case 's':
                Sort_Up();
                break;
            case 'x':
                Sort_Down();
                break;
            case 't':
                Search_Value();
                break;
            case 'a':
                Find_Max_Number();
                break;
            case 'w':
                Find_Min_Number();
                break;
            case 'e':
                Exit_Program();
                break;
        }
    }
    while (chon!='c'||chon!='p'||chon!='i'||chon!='d'||chon!='s'||chon!='x'||chon!='t'||chon!='a'||chon!='w'||chon!='e');
}
