#include "Fibonacci.h"
#include <stdint.h>

int Fibonacci(int n)
{
    /* f(1)=1 & f(2)=1 */
    int a1 = 1; /* First element of serial fibonacci */
    int a2 = 1; /* Second element of serial fibonacci */
    int index = 3; /* Start at third element */
    unsigned long long int a; /* 100th element of serial fibonacci is too high */
    uint8_t retValue; /* Declare a variable use to return */
    if (n == 1 || n == 2)
    {
        retValue = 1;
    }
    /*f(0)=0*/
    else if (n ==0)
    {
        retValue = 0;
    }
    else 
    {
        /* When we enter the value n = 0 or 1 or 2, program must print f(0) or f(1) or f(2)
        When we enter the value n >2, f(n) = f(n-1) + f(n-2) until i = n, then we get the value of f(n) */
        while (index <= n)
        {
            a = a1 + a2;
            a1 = a2;
            a2 = a;
            index++;
        }
        retValue = a; /* Returns the result of the function Fibonacci; f(n) = a after we calculated */
    }
    return retValue;
}
