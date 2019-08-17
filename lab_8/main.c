/*

		Author: Kalashnikov Ivan
		Task: Lab_8, Var 7 (Battlefield)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdbool.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>

#include <wait.h>
#include <fcntl.h>

#include "battlefield.h"

#define MAX_FORKS 128UL
#define DEFAULT_UNITS 100

//MSG
typedef struct 
{
	long msg_type;
	uint8_t msd_data[1];
} msg_buff_t;

void send_message(int msg_id, msg_buff_t * restrict msg_buff, long msg_type, void *data, size_t size_data);
void read_message(int msg_id, msg_buff_t * restrict msg_buff, long msg_type, void *data, size_t size_data);


int main(int argc, char *argv[]) 
{
	size_t quantity_battlefields = 3;

	if (argc < 2) 
	{
		printf 
			("Are set default settings:\nQuantity battlefields = %ld\n\n", 
			 quantity_battlefields);
		printf 
			("If you want to set your settings, then restart the programm and set this in this format:\n\n");
		printf 
			("./lab_8 <quantity_battlefields>\n\n");

		sleep(2);
	}
	else
	{
		quantity_battlefields = atoi(argv[1]);
	}

	if (quantity_battlefields > MAX_FORKS)
	{
		perror("\nToo much tasks for forks\n");
		return 1;
	}


	pid_t *pid = (pid_t*)malloc(sizeof(pid_t) * quantity_battlefields);
	if (NULL == pid)
		return 1;

	//For msg IPC
	const key_t key = ftok("./lab_8", 42);
	const int msg_type = 1;
	msg_buff_t msg_buff;

	int msg_id = msgget(key, IPC_CREAT | 0660);
	if (-1 == msg_id)
	{
		perror("Error: failed to get msd_id ");
		return 1;
	}
	
	battlefield ** battlefields = (battlefield**)malloc(sizeof(battlefield*) * quantity_battlefields);

	for (size_t i = 0; i < quantity_battlefields; i++)
	{
		battlefields[i] = init_battlefield
								(DEFAULT_UNITS, "Command 1",
								 DEFAULT_UNITS, "Command 2");
	}


	for (size_t i = 0; i < quantity_battlefields; i++)
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
			printf("Battlefield %ld has been started!\n", i);
			while (battlefields[i]->command_one_units > 0 && battlefields[i]->command_two_units > 0)
			{
				sleep(2);
				printf("Battlefield %ld: \n", i);

				battle(battlefields[i]);

				printf("Total: %s = %d VS %s = %d\n", 
						battlefields[i]->command_one_name, battlefields[i]->command_one_units,
						battlefields[i]->command_two_name, battlefields[i]->command_two_units);
			}

			exit(1);
		}
	}


	for (size_t i = 0; i < quantity_battlefields; i++)
	{
		waitpid(pid[i], NULL, 0);
	}

	for (size_t i = 0; i < quantity_battlefields; i++)
		free(battlefields[i]);

	free(battlefields);
	return 0;
}
/*
void send_message(int msg_id, msg_buff_t * restrict msg_buff, long msg_type, void *data, size_t size_data)
{
	qbuf->mtype = type;
	strcpy(qbuf->mtext, text);

	if ((msgsnd(qid, (struct msgbuf *)qbuf,
		    strlen(qbuf->mtext) + 1, 0)) == -1) {
		perror("msgsnd");
		exit(1);
	}
}

void read_message(int msg_id, msg_buff_t * restrict msg_buff, long msg_type, void *data, size_t size_data)
{
	qbuf->mtype = type;
	msgrcv(qid, (struct msgbuf *)qbuf, MAX_SEND_SIZE, type, 0);
	strcpy(msg, qbuf->mtext);
}*/