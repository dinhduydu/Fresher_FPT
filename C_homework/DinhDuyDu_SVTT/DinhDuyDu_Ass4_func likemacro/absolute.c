#include "header.h"

/*Function to calculate of absolution of subtraction between two 8 bit integer*/
void absoluteValue(uint8_t *data)
{
    data[2]= ABS(data[0],data[1]);/*Use function like macro because it is used once time*/
}
