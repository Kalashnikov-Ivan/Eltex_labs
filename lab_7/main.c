/*

		Author: Kalashnikov Ivan
		Task: Lab_7, Var 4 (Warcraft)

*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdbool.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include "warcraft.h"

#define FIFO_GOLD "./exchange_gold_main.fifo"
#define MAX_FORKS 128UL

int main(int argc, char *argv[]) 
{
	int64_t gold_in_mine = 89;
	uint16_t quantity_workers = 5, cargo = 7;

	int read_fd, write_fd;

	if (argc < 2) 
	{
		printf 
			("Are set default settings:\nGold in mine = %d\nWorkers = %d\nCargo = %d\n\n", 
			 gold_in_mine, quantity_workers, cargo);
		printf 
			("If you want to set your settings, then restart the programm and set this in this format:\n\n");
		printf 
			("./lab_7 <gold_in_mine> <workers> <cargo>\n");

		sleep(2);
	}
	else
	{
		gold_in_mine = atoi(argv[1]);
		quantity_workers = atoi(argv[2]);
		cargo = atoi(argv[3]);
	}
	

	if (quantity_workers > MAX_FORKS)
		return 1;

	pid_t *pid = (pid_t*) malloc(sizeof(pid_t) * quantity_workers);
	if (NULL == pid)
		return 1;


		for (size_t i = 0; i < quantity_workers; i++)
		{
			mkfifo(FIFO_GOLD, 0666);

			pid[i] = fork();

			srand(getpid());

			if (-1 == pid[i])
			{
				perror("fork");
				exit(1);
			}
			else if (0 == pid[i])
			{

				while (true)
				{
					sleep(get_rand_in_range(1, 4)); //Go to mine

					write(write_fd, &cargo, sizeof(uint16_t));

					close(write_fd);

					sleep(get_rand_in_range(1, 4)); //Go from mine
				}

				exit(1); //doesn't make sense but just in case 
			}
		}

		uint16_t current_cargo, tmp;
		while (true) 
		{
			for (size_t i = 0; i < quantity_workers; i++) 
			{
				current_cargo = 0;

				if (gold_in_mine <= 0) 
				{
					for (size_t j = 0; j < quantity_workers; j++)
						kill(pid[j], SIGKILL);
					
					printf("Now mine is empty...\n");

					remove(FIFO_GOLD);

					free(pid);

					return 0;
				}

				read_fd = open(FIFO_GOLD, O_RDONLY);

				read(read_fd, &tmp, sizeof(uint16_t));

				close(read_fd);

				while (tmp-- != 0 && gold_in_mine-- > 0)
					current_cargo++;

				if (gold_in_mine < 0)
					gold_in_mine = 0;

				printf ("Worker[%d]: I got %d gold, and left in the mine %d gold\n", 
						i, current_cargo, gold_in_mine);
			}
		}
}