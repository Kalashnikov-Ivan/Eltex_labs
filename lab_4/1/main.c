/*

		Author: Kalashnikov Ivan

*/

#include <stdio.h>

int main(int argc, char *argv[]) 
{
	if (argc < 2)
	{
		fprintf (stderr, "Too few arguments. Use <filename>\n");
		exit (1);
    }

	FILE *fp = fopen(argv[1], "r");

	if(fp == NULL) 
	{
		printf("File %s cannot open\n", argv[1]);
		exit(1);
  	}


	printf("----Programm is finished----\n");
	return 0;
}