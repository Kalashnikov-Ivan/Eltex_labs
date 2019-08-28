/*

		Author: Kalashnikov Ivan
		Task: Lab_10, Var 11 (Turns game)

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define	MAX_NITEMS 1000000UL

const int32_t min_dx = -1, min_dy = -1,
			  max_dx =  2, max_dy =  2;

const size_t BUFF_SIZE = 128UL;

void *thread_walker(void *arg);
struct 
{
	pthread_mutex_t	mutex;
	int tik;
	pthread_t main_thread;
} shared = { 
	PTHREAD_MUTEX_INITIALIZER
};

typedef struct
{
	field_t *field;
	size_t walker_id;
} thread_data_t;

int main(void) 
{
//--------INIT---------
	shared.tik = 0;
	shared.main_thread = pthread_self();
	signal(SIGUSR1, SIG_IGN);
	signal(SIGUSR2, SIG_IGN);

	const size_t size_x = 10UL;
	const size_t size_y = 10UL;

	const uint32_t quantity_walkers = 3, start_health_walker = 1;
	if (quantity_walkers > ((size_x - 2) * (size_y - 2)))
		return 1;

	field_t *field = init_field(size_x, size_y, quantity_walkers, start_health_walker);

	system("clear");
	print_field(field);

	uint32_t global_q_walkers = field->quant_walkers;

	srand(time(NULL));

//--------THREADS---------
	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * quantity_walkers);
	void **threads_status = (void**)malloc(sizeof(void*) * quantity_walkers);
		for (size_t i = 0; i < quantity_walkers; i++)
			threads_status[i] = (void*)malloc(sizeof(void));

	thread_data_t *thread_data = (thread_data_t*)malloc(sizeof(thread_data_t) * global_q_walkers);

	for (size_t i = 0; i < global_q_walkers; i++)
	{
		thread_data[i].field = field;
		thread_data[i].walker_id = i;
		
		if (pthread_create(&threads[i], NULL, thread_walker, &thread_data[i]) != 0) 
		{
			fprintf(stderr, "Error: create thread[%ld]", i);
			return EXIT_FAILURE;
		}
	}

	while (field->quant_walkers)
	{
		sleep(1);
		system("clear");
		print_field(field);

		sigwait(NULL, SIGUSR2);
		for (size_t i = 0; i < global_q_walkers; i++)
		{
			if (1)
			{
				if (field->walkers[i].alive)
					printf("id[%ld]: x = %2d | y = %2d | health = %2d\n", 
						field->walkers[i].id, field->walkers[i].cord_x, field->walkers[i].cord_y,
						field->walkers[i].health);
				else
					printf("id[%ld]: death\n",
						field->walkers[i].id);
			}

			pthread_kill(threads[i], SIGUSR1);
		}
	}
	

	for (size_t i = 0; i < global_q_walkers; i++)
	{
		if (pthread_join(threads[i], NULL) != 0) 
		{
			fprintf(stderr, "Error: joining thread[%ld]", i);
			return EXIT_FAILURE;
		}
		free(threads_status[i]);
	}

	free(thread_data);
	free(threads_status);
	free(threads);
	free_field(field);
	return 0;
}

void *thread_walker(void *arg)
{
	int *ptr_status = (int*)malloc(sizeof(int));
	thread_data_t *data = (thread_data_t*)arg;
	field_t *thread_field = data->field;
	size_t walker_id = data->walker_id;

	while (thread_field->walkers[walker_id].alive)
	{
		int32_t rand_dx = get_rand_in_range(min_dx, max_dx),
				rand_dy = get_rand_in_range(min_dy, max_dy);

		pthread_mutex_lock(&shared.mutex);

		ssize_t overlay_id = check_overlay(thread_field, rand_dx, rand_dy);
		if (overlay_id != NOT_OVERLAY)
		{
			battle_walker(&thread_field->walkers[walker_id], &thread_field->walkers[overlay_id]);
			thread_field->quant_walkers--;
		}

		move_walker(thread_field, &thread_field->walkers[walker_id], rand_dx, rand_dy);
		shared.tik++;

		if (shared.tik == thread_field->quant_walkers)
			pthread_kill(shared.main_thread, SIGUSR2);

		pthread_mutex_unlock(&shared.mutex);

		sigwait(NULL, SIGUSR1);
		//usleep(600000);
	}

	pthread_exit((void *)ptr_status);
}