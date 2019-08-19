/*

		Author: Kalashnikov Ivan
		Task: Lab_9, Var 5 (Battlefield)

*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define MAX_FORKS 128UL

typedef union 
{
	int val;
	struct semid_ds *buff;
	unsigned short *array;
	struct seminfo *__buf;
} sem_un;

int main(int argc, char *argv[]) 
{
	size_t quantity_bees = 3;

	if (argc < 2) 
	{
		printf 
			("Are set default settings:\nQuantity bees = %ld\n\n", 
			 quantity_bees);
		printf 
			("If you want to set your settings, then restart the programm and set this in this format:\n\n");
		printf 
			("./lab_9 <quantity_bees>\n\n");

		sleep(2);
	}
	else
	{
		quantity_bees = atoi(argv[1]);
	}

	if (quantity_bees > MAX_FORKS)
	{
		perror("\nToo much tasks for forks\n");
		return 1;
	}


	pid_t *pid = (pid_t*)malloc(sizeof(pid_t) * quantity_bees);
	if (NULL == pid)
		return 1;

	return 0;
}