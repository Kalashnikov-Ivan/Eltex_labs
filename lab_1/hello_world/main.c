#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct test
{
	int a;
};


int main(void) {

	printf("Hello, world!\n");

	uint8_t min = 5, max = 42;
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		int32_t cur =  min + rand() % (min - max);
		printf("%d\n", cur);
	}

	struct test t1;
	printf("test: %d\n", t1.a);

	return 0;
}