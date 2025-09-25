#include "header.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

/*Enter a number and character '\n'*/
int clean_stdin()
{
    while(getchar()!='\n');
    /*If not, return 0*/
    return 1;
}
/*Enter variable and block condition while we enter wrong*/
void Type(void)
{
    uint8_t unsignedNum[3];
    uint32_t a;
    char c;
	/* First number */
    printf("\n\tFirst number is: ");
    while ((scanf("%d%c", &a, &c)!=2||c!='\n')&&clean_stdin()||a > 255|| a <0)
    {
        printf("\n\tEnter again!\t");
        getch();
    }
    unsignedNum[0] = (uint8_t)a;
	/* Second number */
    printf("\n\tSecond number is: ");
    while ((scanf("%d%c", &a, &c)!=2||c!='\n')&&clean_stdin()||a > 255|| a <0)
    {
        printf("\n\tEnter again!\n");
        getch();
    }
    unsignedNum[1] = (uint8_t)a;
	/* Calculate abs */
    absoluteValue(unsignedNum);
    printf("\n\tValue of two inserted numbers: %u, %u\n", unsignedNum[0],unsignedNum[1]);
    printf("\tAbsolute value of two numbers: %u\n",unsignedNum[2]);
	/* Press any */
    printf("\n\tPress ENTER to continue");
    getch();
}
