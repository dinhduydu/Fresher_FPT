#include <stdio.h>
#include <stdint.h>
/* definition  */

/* declare enum type */
typedef enum _statetype 
{ 

    CORRECT, 

    CHAR_INVALID, 

    LENGTH_INVALID 

}status_enum_t; 
/* declare typdef function pointer - callback function: pass a pointer to char & return void */
typedef void (*func)(char*);

	status_enum_t retValue;
/* function enter string */
void nhap (char *ptr)
{
   gets(ptr);
}

/* function get length */
uint8_t strlen1(char *ptr)
{
	uint8_t index;
	/* until NULL character */
	while (ptr[index] != '\0')
	{
		index++;
	}
	return index;
}

/* check length and any characters in string */
void Check_Account (char *ptr, uint8_t length)
{   
	uint8_t index;
	uint8_t tim_thay = 0;
	for (index = 0; index < length; index++)
	{
		if ((ptr[index]>= ' ' &&ptr[index]<= '/')||(ptr[index] >= ':' && ptr[index]<= '@')||(ptr[index]>='['&&ptr[index]<='`')||(ptr[index]>='{'&&ptr[index]<=' '))
		{
			tim_thay = 1;
			printf("\n\tChuoi co chua ky tu dac biet\n", ptr);
			retValue = CHAR_INVALID;
			break;
		}
	}
//	status_enum_t retValue;
	if (tim_thay ==0)
	{
		retValue= CORRECT;
		printf("\nChuoi %s khong chua ky tu dac biet\n", ptr);
	}
	
	else if (length > 10)
	{	
		retValue = LENGTH_INVALID;
	}
	

}

void RegisterCallback(char *ptr,func func_add)
{
	printf("This is callback function.\n");
//	(*func_add)(char*);
	return func_add(ptr);
}

void my_function(char*str)
{
	printf("this is a normal function.\n");
}


void check (status_enum_t x)
{
	
	switch (x)
	{
		case LENGTH_INVALID:
			printf("length invalid\n");
			break;
		case CHAR_INVALID:
			printf("char invalid\n");
			break;
		case CORRECT:
			printf("correct");	
			break;
	}
}

int main()
{
	char str[50];
	uint8_t x = 0;
	/* enter string */
    printf("Nhap mot chuoi: ");
//	nhap(str);
	
	RegisterCallback(str,nhap);
	
	/* print that string */
    printf("Ban vua nhap chuoi: %s\n", str);
	/* get length of that string */
	x = strlen1(str);
	printf("number of characters is %u\n", x);
	Check_Account(str, x);
	check (retValue);
   return(0);
}



//#include<stdio.h>
//void my_function() {
//   printf("This is a normal function.");
//}
//void my_callback_function(void (*ptr)()) {
//   printf("This is callback function.\n");
//   (*ptr)();    //calling the callback function
//}
//main() {
//   void (*ptr)() = &my_function;
//   my_callback_function(ptr);
//}

//
//
//#include<stdio.h>
//
//typedef void (*ptr)(void);
//void my_function() {
//   printf("This is a normal function.");
//}
//void my_callback_function(ptr aptr) {
//   printf("This is callback function.\n");
//   (*aptr)();    //calling the callback function
//}
//main() {
//   void (*ptr)() = &my_function;
//   my_callback_function(ptr);
//}

//#include <stdio.h>
//#include <conio.h>
//#include <math.h>
//
//// Dinh nghia callback
//typedef int (* opstion) (int *, int);
//
////ham nhap mang
//void nhapMang (int * array, int lengthArray)
//{
//    int i;
//    printf("Nhap mang %d phan tu:n",lengthArray);
//    for (i = 0; i<lengthArray; i++)
//        {
//            scanf("%d",(array + i));
//        }
//}
//
//
////Ham in mang
//
//void inMang (int * array, int lengthArray)
//{
//    int i;
//    printf("Mang da nhapn");
//    for (i = 0; i<lengthArray; i++)
//        {
//            printf("%2d",*(array + i));
//        }
//}
//
////ham tim min
//int timMin(int *array, int lengthArray)
//{
// int i;
// int Min = *array;
// for(i=1;i<lengthArray;i++)
// if(Min>*(array+i)) Min = *(array+i);
// return Min;
//}
//
////Ham tim max
//int timMax(int *array, int lengthArray)
//{
// int i;
// int Max = *(array);
// for(i=1;i<lengthArray;i++)
// if(Max<*(array+i)) Max = *(array+i);
// return Max;
//}
//
//// Khai bao cho phep goi lai ham callback de xu ly mang 1 mang voi chieu dai la lengthArray, chuc nang trong opstion
//int opstionArray (int * array, int lengthArray, opstion pOption)
//{
//    // Tr? xy ly cho mang
//    return  pOption (array, lengthArray);
//}
//
///// Main /////
//int main ()
//{
//    int array [10];
//    int choise;
//    // Nhap mang
//    nhapMang (array, 10);
//    // In ra mang vua nhap mang
//    inMang (array, 10);
//    choise = 0;
//    printf ("nTim Min Max hoac cua mang da nhap n");
//    while (choise!= 3)
//    {
//        printf ("nChon: n1: Tim Min n2: Tim Max n3: Exit n");
//        scanf ("%d", &choise);
//        // Chon lua opstion cho m?ng da nhap
//        switch (choise)
//        {
//        case 1:
//            printf ("Min =%d", opstionArray (array, 10, timMin));
//            break;
//        case 2:
//            printf ("Max =%d", opstionArray (array, 10, timMax));
//            break;
//        case 3:
//            break;
//        }
//    }
//
//    getch ();
//}
