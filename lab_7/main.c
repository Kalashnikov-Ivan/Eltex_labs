/*

		Author: Kalashnikov Ivan
		Task: Lab_7, Var 4 (Warcraft)

*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdbool.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include "warcraft.h"

#define FIFO_GOLD "./exchange_gold_main.fifo"
#define FIFO_CARGO "./exchange_cargo.fifo"
#define MAX_FORKS 128UL
#define BUFF_SIZE 256UL

int main(void) 
{
	int64_t gold_in_main = 100;
	const uint16_t quantity_workers = 2, cargo = 10;

	if (quantity_workers > MAX_FORKS)
		return 1;

	unit_worker *workers = (unit_worker*) malloc(sizeof(unit_worker) * quantity_workers);
	if (NULL == workers)
		return 1;

	for (size_t i = 0; i < quantity_workers; i++)
		workers[i].cargo = cargo;


	pid_t *pid = (pid_t*) malloc(sizeof(pid_t) * quantity_workers);
	if (NULL == pid)
		return 1;

	int read_fd, write_fd;
	char buff[BUFF_SIZE];

		for (size_t i = 0; i < quantity_workers; i++)
		{
			pid[i] = fork();
			mkfifo(FIFO_GOLD, 0666);

			srand(getpid());

			if (-1 == pid[i])
			{
				perror("fork");
				exit(1);
			}
			else if (0 == pid[i])
			{
				uint32_t time_way;
				while (gold_in_main)
				{
					time_way = get_rand_in_range(1, 3);
					sleep(time_way); //Go to main

					read_fd = open(FIFO_GOLD, O_RDONLY);

					if (read(read_fd, buff, BUFF_SIZE))
						gold_in_main = atoi(buff);

					close(read_fd);
					
					if (gold_in_main < 0)
						break;

					if (!(gold_in_main == workers[i].cargo))
						gold_in_main -= (gold_in_main + workers[i].cargo % gold_in_main) % gold_in_main;
					else
						gold_in_main = 0;

					printf("PID: %d Worker: %d, gold in mine: %d\n\n", getpid(), i, gold_in_main);

					write_fd = open(FIFO_GOLD, O_WRONLY);

					sprintf(buff, "%d", gold_in_main);
					write(write_fd, buff, BUFF_SIZE);

					close(write_fd);

					time_way = get_rand_in_range(1, 3);
					sleep(time_way); //Go from main
				}

				exit(0);
			}

			write_fd = open(FIFO_GOLD, O_WRONLY);

			sprintf(buff, "%d", gold_in_main - (i * workers[i].cargo));
			write(write_fd, buff, BUFF_SIZE);

			close(write_fd);
		}

		while (gold_in_main)
		{
			read_fd = open(FIFO_GOLD, O_RDONLY);

			if (read(read_fd, buff, BUFF_SIZE))
				gold_in_main = atoi(buff);

			close(read_fd);

			write_fd = open(FIFO_GOLD, O_WRONLY);

			sprintf(buff, "%d", gold_in_main);
			write(write_fd, buff, BUFF_SIZE);

			close(write_fd);
		}
		

		for (size_t i = 0; i < quantity_workers; i++)
		{
       		waitpid(pid[i], NULL, 0);
		}

	remove(FIFO_GOLD);

	free(workers);
	free(pid);
	return 0;
}