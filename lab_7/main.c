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
#define BUFF_SIZE 256UL

int main(void) 
{
	int64_t gold_in_mine = 100;
	const uint16_t quantity_workers = 3, cargo = 10;

	int read_fd, write_fd;

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
				uint32_t time_way;
				while (true)
				{
					time_way = get_rand_in_range(1, 7);
					sleep(time_way); //Go to mine
					
					write_fd = open(FIFO_GOLD, O_WRONLY | O_NONBLOCK);

					write(write_fd, &cargo, sizeof(uint16_t));

					close(write_fd);

					time_way = get_rand_in_range(1, 7);
					sleep(time_way); //Go from mine
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

				while (tmp-- != 0 && gold_in_mine-- != 0)
					current_cargo++;

				printf ("Worker[%d]: I got %d gold, and left in the mine %d gold\n", 
						i, current_cargo, gold_in_mine);
			}
		}
}

/*

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
#define BUFF_SIZE 256UL

int main(void) 
{
	int64_t gold_in_mine = 100;
	const uint16_t quantity_workers = 3, cargo = 10;

	int fd_pipe[quantity_workers][2];

	if (quantity_workers > MAX_FORKS)
		return 1;

	pid_t *pid = (pid_t*) malloc(sizeof(pid_t) * quantity_workers);
	if (NULL == pid)
		return 1;


		for (size_t i = 0; i < quantity_workers; i++)
		{
			pipe(fd_pipe[i]);

			pid[i] = fork();

			srand(getpid());

			if (-1 == pid[i])
			{
				perror("fork");
				exit(1);
			}
			else if (0 == pid[i])
			{
				close(fd_pipe[i][0]);

				while (true)
				{
					sleep(get_rand_in_range(1, 4)); //Go to mine
					
					write(fd_pipe[i][1], &len, sizeof (int));

					sleep(get_rand_in_range(1, 4)); //Go from mine
				}

				exit(1); //doesn't make sense but just in case 
			}
		}

		uint16_t current_cargo, tmp;
		while (true) 
		{
			current_cargo = 0;

			for (size_t i = 0; i < quantity_workers; i++) 
			{
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

				while (tmp-- != 0 && gold_in_mine-- != 0)
					current_cargo++;

				printf ("Worker[%d]: I got %d gold, and left in the mine %d gold\n", 
						i, current_cargo, gold_in_mine);
			}
		}
}

//printf("PID: %d Worker: %d, gold in mine: %d\n\n", getpid(), i, gold_in_mine);
*/