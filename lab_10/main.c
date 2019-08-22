#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdbool.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include <pthread.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <wait.h> 
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#include "walkers_game.h"

#define	MAX_NITEMS 1000000

struct 
{
	pthread_mutex_t	mutex;
	int	buff[MAX_NITEMS];
	int	n_put;
	int	n_val;
} shared = { 
	PTHREAD_MUTEX_INITIALIZER
};

const int32_t min_dx = -1, min_dy = -1,
			  max_dx =  2, max_dy =  2;

const size_t BUFF_SIZE = 128UL;

int main(void) 
{
	const size_t size_x = 10UL;
	const size_t size_y = 10UL;

	const uint32_t quantity_walkers = 3, start_health_walker = 2;
	if (quantity_walkers > ((size_x - 2) * (size_y - 2)))
		return 1;

	field_t *field = init_field(size_x, size_y, quantity_walkers, start_health_walker);

	system("clear");
	print_field(field);

	uint32_t global_q_walkers = field->quant_walkers;

	srand(time(NULL));
	
	while (field->quant_walkers)
	{
		int32_t rand_dx, 
				rand_dy;

		for (size_t j = 0; j < global_q_walkers; j++)
		{
			rand_dx = get_rand_in_range(min_dx, max_dx); 
			rand_dy = get_rand_in_range(min_dy, max_dy);

			move_walker(field, &field->walkers[j], rand_dx, rand_dy);
		}
		
		usleep(600000);
		system("clear");
		print_field(field);
	
		if (1)
			for (size_t i = 0; i < global_q_walkers; i++)
				printf("id[%d]: x = %2d | y = %2d | health = %2d\n", 
					field->walkers[i].id, field->walkers[i].cord_x, field->walkers[i].cord_y,
					field->walkers[i].health);
	}

	free_field(field);
	return 0;
}