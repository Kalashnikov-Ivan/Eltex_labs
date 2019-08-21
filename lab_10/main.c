#include <stdio.h>

#include <stdbool.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include "walkers_game.h"

const int32_t min_dx = -1, min_dy = -1,
			  max_dx =  2, max_dy =  2;

const size_t BUFF_SIZE = 128UL;

int main(void) 
{
	const size_t size_x = 10UL;
	const size_t size_y = 10UL;

	const uint32_t quantity_walkers = 3;
	if (quantity_walkers > ((size_x - 2) * (size_y - 2)))
		return 1;

	field_t *field = init_field(size_x, size_y, quantity_walkers);

	system("clear");
	print_field(field);

	const int32_t min_dx = -1, min_dy = -1,
				  max_dx =  2, max_dy =  2;

	uint32_t global_q_bubbles = field->quant_walkers;

	srand(time(NULL));
	
	while (field->quant_walkers)
	{
		int32_t rand_dx, 
				rand_dy;

		for (size_t j = 0; j < global_q_bubbles; j++)
		{
			rand_dx = get_rand_in_range(min_dx, max_dx); 
			rand_dy = get_rand_in_range(min_dy, max_dy);

			move_walker(field, &field->walkers[j], rand_dx, rand_dy);
		}
		
		usleep(600000);
		system("clear");
		print_field(field);
	
		if (0)
			for (int i = 0; i < global_q_bubbles; i++)
				printf("%d: x = %2d | y = %2d\n", i + 1, field->walkers[i].cord_x, field->walkers[i].cord_y);
	}

	free_field(field);
	return 0;
}