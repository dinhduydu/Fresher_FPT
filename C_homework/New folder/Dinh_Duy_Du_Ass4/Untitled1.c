#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

bool allocate10Bytes( uint8_t **outPtr )
{
    const size_t N = 10;

    *outPtr = malloc( N * sizeof( uint8_t ) );

    return *outPtr != NULL;
}

int main(void) 
{
    uint8_t *p;

    bool success = allocate10Bytes( &p );

    if ( success ) free( p );

    return 0;
}
