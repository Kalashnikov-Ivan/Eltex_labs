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
	battlefield_t msd_data;
} msg_buff_t;

void send_message(int msg_id, msg_buff_t *msg_buff, long msg_type, void *data, size_t size_data);
void read_message(int msg_id, msg_buff_t *msg_buff_src, long msg_type, void *dest);


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
	
	battlefield_t ** battlefields = (battlefield_t**)malloc(sizeof(battlefield_t*) * quantity_battlefields);

	for (size_t battlefield_id = 0; battlefield_id < quantity_battlefields; battlefield_id++)
	{
		battlefields[battlefield_id] = init_battlefield
								( battlefield_id,
								 DEFAULT_UNITS, "Command 1",
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
				//printf("Battlefield %ld: \n", i);

				battle(battlefields[i]);

				send_message
					(msg_id, &msg_buff, msg_type, (battlefield_t*)battlefields[i], sizeof(*battlefields[i]));

			/*	printf("Battlefield %ld: %s = %4d VS %s = %4d\n", i,
						battlefields[i]->command_one_name, battlefields[i]->command_one_units,
						battlefields[i]->command_two_name, battlefields[i]->command_two_units);*/
			}

			exit(1);
		}
	}


	size_t current_quant_battlef = quantity_battlefields;
	battlefield_t current_battlefield;
	while (current_quant_battlef)
	{
		read_message(msg_id, &msg_buff, msg_type, &current_battlefield);

		printf("Battlefield %ld: %s = %4d VS %s = %4d\n", current_battlefield.battfield_id,
				current_battlefield.command_one_name, current_battlefield.command_one_units,
				current_battlefield.command_two_name, current_battlefield.command_two_units);

		if (current_battlefield.command_one_units <= 0 || current_battlefield.command_two_units <= 0)
			current_quant_battlef--;
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

void send_message(int msg_id, msg_buff_t *msg_buff, long msg_type, void *data, size_t size_data)
{
	msg_buff->msg_type = msg_type;
	memcpy(&msg_buff->msd_data, data, size_data);

	if ((msgsnd(msg_id, (msg_buff_t*)msg_buff, sizeof(msg_buff_t) - sizeof(long), 0)) == -1) 
	{
		perror("Error: cannot send msg in msg_buff");
		exit(1);
	}
}

void read_message(int msg_id, msg_buff_t *msg_buff_src, long msg_type, void *dest)
{
	msg_buff_src->msg_type = msg_type;
	msgrcv(msg_id, (msg_buff_t*)msg_buff_src, sizeof(msg_buff_t) - sizeof(long), msg_type, 0);
	memcpy(dest, &msg_buff_src->msd_data, sizeof(msg_buff_t) - sizeof(long));
}