#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static uint8_t hasa;

void test(uint8_t *yasuo);

void nhap(void)
{

	test(&hasa);
	printf("\n\tyasuofirst is: %d", hasa);
}

void test(uint8_t *yasuo)
{
	*yasuo += 5;

}

int main (void)
{
	nhap();
	return 0;
}
