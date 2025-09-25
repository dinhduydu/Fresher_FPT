#include <stdio.h>

typedef void (*StoreFn)(char *str);

void downlaod(StoreFn fn);
void store(char *str);

void download (StoreFn fn)
{
	printf("Pretend downloading....\n");
	fn("awesome!!!");
}

void store(char*str)
{
	printf("Store: %s\n",str);
}

int main ()
{
	download(store);
	return 0;
}
