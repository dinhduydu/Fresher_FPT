#ifndef _LIB_H
#define _LIB_H



typedef void (*StoreFn)(char *str);

void download (StoreFn fn);

void store(char*str);

#endif


