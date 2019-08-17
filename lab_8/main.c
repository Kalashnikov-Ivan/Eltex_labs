/*

		Author: Kalashnikov Ivan
		Task: Lab_8, Var 7 (Battlefield)

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

#define MAX_LEN 32UL

typedef struct 
{
	long mtype;
	uint8_t mtext[1];
} msg_buff;

typedef struct
{
	uint32_t command_one_units;
	uint8_t  command_one_name[MAX_LEN];	

	uint32_t command_two_units;
	uint8_t  command_two_name[MAX_LEN];	
} battlefield;

int main(void) 
{
	
	return 0;
}