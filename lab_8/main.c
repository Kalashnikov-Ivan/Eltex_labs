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

#define MAX_FORKS 128UL

typedef struct 
{
	long mtype;
	uint8_t mtext[1];
} msg_buff_t;

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
			("./lab_8 <quantity_battlefields>\n");

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
 
	return 0;
}