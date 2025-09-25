#include <stdio.h> 
#include <stdint.h>
#include "Fibonacci.h"

/**********************************************************************
 * Function
 *********************************************************************/
void main(void)
{
    uint32_t n; /* Declare value to enter because type of scanf is 32 bit */
    uint8_t n1; /* Declare variable to enter number fibonacci */
    printf("\n\tEnter number of serial fibonacci from 0 to 100: ");
    scanf("%d", &n);
    if (n < 0|| n > 100) /* We must enter the value 0<= N <= 100 */
    {
        printf("\n\tEnter again!");
    }
    else
    {
        n1 = n;
    }
    printf("\n\tElement Fibonacci is %d : %llld", n1, Fibonacci(n1));
}
