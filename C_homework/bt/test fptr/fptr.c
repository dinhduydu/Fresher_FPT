#include <stdio.h>

typedef void (*StoreFn)(char *str);

void download (StoreFn fn)
{
	printf("Pretend downloading....\n");
	fn("awesome!!!");
}

void store(char*str)
{
	printf("Store: %s\n",str);
}

