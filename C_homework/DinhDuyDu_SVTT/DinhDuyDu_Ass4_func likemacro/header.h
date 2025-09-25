#ifndef _HEADER_H_
#define _HEADER_H_
#include <stdint.h>

/*Function like macro*/
#define ABS(a,b) ((a > b)? (a - b) : (b - a))
/*******************************************
*Prototype
*******************************************/
void absoluteValue(uint8_t *data);
char Display_Menu(void);
void Type(void);

#endif/* _HEADER_H_ */
