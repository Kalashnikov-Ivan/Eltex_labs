/*

		Author: Kalashnikov Ivan
		Task: Lab_6, Var 6 (bubbles)

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "bubbles.h"

int main(void) 
{
	size_t size_x = 20UL;
	size_t size_y = 10UL;



	field *field = init_field(20, 10, 201);

	print_field(field);

	free_field(field);

	return 0;
}