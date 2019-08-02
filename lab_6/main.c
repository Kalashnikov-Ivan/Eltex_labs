/*

		Author: Kalashnikov Ivan
		Task: Lab_6, Var 6 (bubbles)

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "bubbles.h"

int main(void) 
{
	size_t size_x = 20UL;
	size_t size_y = 10UL;

	uint32_t quantity_bubbles = 5;
	if (quantity_bubbles > ((size_x - 2) * (size_y - 2)))
		return 1;

	field *field = init_field(size_x, size_y, quantity_bubbles);

	system("clear");
	print_field(field);

	uint8_t is_end = 0;
	while (!is_end)
	{
		for (size_t j = 0; !is_end && j < field->quant_bubbles; j++)
			is_end = move_bubble(field, &field->bubbles[j], 1, 0);


		//if (is_end)
		sleep(1);
		system("clear");
		print_field(field);
	}
	

	free_field(field);

	return 0;
}