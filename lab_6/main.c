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

	uint8_t from_board = 0;
	while (field->quant_bubbles)
	{
		from_board = 0;
		for (size_t j = 0; !from_board && j < field->quant_bubbles; j++)
			from_board = move_bubble(field, &field->bubbles[j], 1, 0);

		/*if (!not_from_board)
			field->quant_bubbles--;*/

		//usleep(300000);
		system("clear");
		print_field(field);
	}
	

	free_field(field);

	return 0;
}