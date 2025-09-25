#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdint.h>
#include <string.h>

#ifndef HEADER_H_
#define HEADER_H_

/*******************************************************************************************************************************************
*Variable.
*******************************************************************************************************************************************/
extern uint8_t g_n;/*variable which stores the number of elements of the array*/
extern uint8_t g_Mang[100];/*declare array to store elements*/

/*=========================================================function123.c==================================================================*/
char Display_Menu(void);
void Enter_New_Array(void);
void Print_Array(void);
/*=========================================================function456.c==================================================================*/
void Add_Element(void);
void Remove_Element(void);
/*=========================================================function789.c==================================================================*/
void Sort_Up(void);
void Sort_Down(void);
int Search_Value(void);
/*=========================================================function1011.c==================================================================*/
int Find_Max_Number(void);
int Find_Min_Number(void);
void Exit_Program(void);
#endif/*HEADER_H_*/
