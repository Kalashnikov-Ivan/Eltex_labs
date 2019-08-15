/*

		Author: Kalashnikov Ivan
		Task: Lab_7, Var 4 (Warcraft)

*/

#include <stdio.h>

#include "warcraft.h"

#define MAX_FORKS 128UL

int main(void) 
{
	uint64_t gold_in_main = 100;
	const uint16_t quantity_workers = 10;

	if (quantity_workers > MAX_FORKS)
		return 1;

	unit_worker *workers = (unit_worker*) malloc(sizeof(unit_worker) * quantity_workers);
	if (NULL == workers)
		return 1;

	__pid_t *pid = (__pid_t*) malloc(sizeof(__pid_t) * quantity_workers);
	if (NULL == pid)
		return 1;

		for (size_t i = 0; i < quantity_workers; i++)
		{
			pid[i] = fork();

			srand(getpid());

			if (-1 == pid[i])
			{
				perror("fork");
				exit(1);
			}
			else if (0 == pid[i])
			{

				if (NULL == (fp = fopen("exchange.buf", "a")))
				{
					printf("File %s cannot open.\n", "exchange.buf");
					exit(1);
				}

				rand_dx = get_rand_in_range(min_dx, max_dx); 
				rand_dy = get_rand_in_range(min_dy, max_dy);

				move_bubble(field, &field->bubbles[i], rand_dx, rand_dy);

				//Creating string which will put in exchange file
				itoa(i, buff);
				strcat(buff, " ");
				itoa(field->bubbles[i].cord_x, buff_support);
				strcat(buff, buff_support);
				strcat(buff, " ");
				itoa(field->bubbles[i].cord_y, buff_support);
				strcat(buff, buff_support);
				strcat(buff, " ");
				strcat(buff, "\n");

				fputs(buff, fp);

				if(fclose(fp))
				{ 
					printf("Error close of file.\n");
					exit(1);
				}

				exit(0);
			}
		}


	free(workers);
	free(pid);
	return 0;
}