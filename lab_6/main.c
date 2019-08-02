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
	size_t size_x = 40UL;
	size_t size_y = 10UL;

	uint32_t quantity_bubbles = 55;
	if (quantity_bubbles > ((size_x - 2) * (size_y - 2)))
		return 1;

	field *field = init_field(size_x, size_y, quantity_bubbles);

	system("clear");
	print_field(field);

	uint32_t global_q_bubbles = field->quant_bubbles;
	while (field->quant_bubbles)
	{
		for (size_t j = 0; j < global_q_bubbles; j++)
		{
			uint32_t rand_dx = -1 + rand() % (-1 - 2), rand_dy = -1 + rand() % (-1 - 2);
			move_bubble(field, &field->bubbles[j], rand_dx, rand_dy);
		}

		usleep(300000);
		system("clear");
		print_field(field);
	}
	

	free_field(field);

	return 0;
}