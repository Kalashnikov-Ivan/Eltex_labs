#include <stdio.h>
#include <stdlib.h>

int main(void) {

	printf("Hello, world!\n");

	int min = 1, max = 10;
	srand(time(NULL));

for (int i = 0; i < 10; i++)
    printf("%d\n", min + rand() % (min - max));

	return 0;
}