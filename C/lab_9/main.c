/*

		Author: Kalashnikov Ivan
		Task: Lab_9, Var 5 (Winnie the Pooh)

*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <stdbool.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define MAX_FORKS 128UL

const uint32_t started_value_of_honey = 12;
const uint32_t bees_cargo = 2, time_of_way = 3;

//Semafor
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
	uint32_t bear_portion = 10, time_of_eat = 4;

	if (argc < 4) 
	{
		printf 
			("Are set default settings:\nQuantity bees = %ld\n\n",
			 quantity_bees);
		printf 
			("If you want to set your settings, then restart the programm and set this in this format:\n\n");
		printf 
			("./lab_9 <quantity_bees> <bear_portion> <time_of_eat>\n\n");

		sleep(2);
	}
	else
	{
		quantity_bees = atoi(argv[1]);
		bear_portion = atoi(argv[2]);
		time_of_eat = atoi(argv[3]);
	}

	if (quantity_bees > MAX_FORKS)
	{
		perror("\nToo much tasks for forks\n");
		return 1;
	}


	pid_t *pid = (pid_t*)malloc(sizeof(pid_t) * quantity_bees);
	if (NULL == pid)
		return 1;

	//For shm and sem IPC
	key_t key = ftok("./main.c", 42);
	if (key < 0) 
	{
		printf("Error: failed to get key from ftok\n");
		return 1;
	}


	int shm_id = shmget(key, sizeof (double), IPC_CREAT | 0666);
	if (shm_id < 0) 
	{
		perror("Error: failed to get shm_id from shmget\n");
		return 1;
	}

	int *shm_ptr = (int *)shmat(shm_id, NULL, 0);
	if (shm_ptr == (int *)-1) 
	{
		perror("Error: failed to get shm_ptr from shmat");
		return 1;
	}

	int sem_id = semget(key, 1, IPC_CREAT | 0660);
	if (-1 == sem_id)
	{
		perror("Error: failed to get sem_id from semget\n");
		return 1;
	}

	//Semafors
	sem_un arg;
	struct sembuf lock_res = { 0, -1, 0 };
	struct sembuf rel_res = { 0, 1, 0 };

	arg.val = 1;
	semctl(sem_id, 0, SETVAL, arg);

	*(shm_ptr) = started_value_of_honey;
	printf("Started value of honey = %d\n", *(shm_ptr));

	if (shmdt(shm_ptr) < 0)
	{
		printf("Error: failed to shutdown shm_ptr from shmdt\n");
		exit(1);
	}

	for (size_t i = 0; i < quantity_bees; i++) 
	{
		pid[i] = fork();
		srand(getpid());

		if (-1 == pid[i]) 
		{
			fprintf(stderr, "Error: fork %ld failed", i);
			exit(1);
		} 
		else if (0 == pid[i]) 
		{
			printf("Bees[%ld]: I was born... James Bourne!\n", i);
			while (true)
			{
				//Shared memory access check
				if ((shm_ptr = (int *)shmat(shm_id, NULL, 0)) == (int *)-1)
				{
					perror("Error: failed to get shm_ptr from shmat\n");
					exit(1);
				}

				if ((semop(sem_id, &lock_res, 1)) == -1) 
				{
					fprintf(stderr, "Error: Lock failed\n");
					exit(1);
				}

				*(shm_ptr) = *(shm_ptr) + bees_cargo;
				printf("Bees[%ld]: got %d honey!\n", i, bees_cargo);
				printf("Quantity of honey = %d\n", *(shm_ptr));

				sleep(rand() % time_of_way + 1);

				if ((semop(sem_id, &rel_res, 1)) == -1)
				{
					fprintf(stderr, "Error: Unlock failed\n");
					exit(1);
				}
				if (shmdt(shm_ptr) < 0) 
				{
					printf("Error: failed to shutdown shm_ptr from shmdt\n");
					exit(1);
				}
			}
			exit(1); //doesn't make sense but just in case
		}
	}
	while (true) 
	{
		if ((shm_ptr = (int *)shmat(shm_id, NULL, 0)) == (int *)-1) 
		{
			perror("Error: failed to get shm_ptr from shmat");
			exit(1);
		}
		if (*(shm_ptr) < bear_portion) 
		{
			sleep(time_of_eat);

			if (*(shm_ptr) < bear_portion) 
			{
				printf("Pooh is dead... :(\n");
				printf("And we have a %d honey\n", *(shm_ptr));
				for (size_t i = 0; i < quantity_bees; i++) 
					kill(pid[i], SIGKILL);

				return 0;
			}
		}

		*(shm_ptr) = *(shm_ptr) - bear_portion;
		sleep(time_of_eat);

		printf("Pooh ate. Honey left = %d\n", *(shm_ptr));
	}
	return 0;

}