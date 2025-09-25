#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void main (void)
{
	uint8_t *bufferFolderTemp = (uint8_t*)malloc(0);
	uint8_t *yas = (uint8_t*)malloc(512);
	if (bufferFolderTemp == NULL)
	{
		printf("Error");
	}
	else 
	{
		printf ("success");
	}
//	return 0;
}
