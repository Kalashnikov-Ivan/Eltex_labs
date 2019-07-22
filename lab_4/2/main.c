/*

		Author: Kalashnikov Ivan
		Task: Lab_4, Var 6.2

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...

#define SIZE_FILENAME 128UL

int main(int argc, char *argv[]) 
{
	FILE *fp_in;

	if (argc < 3)
	{
		fprintf (stderr, "Too few arguments. Use <filename>\n");
		exit (1);
    }

	if((fp_in = fopen(argv[1], "r")) == NULL)
	{
		printf("File %s cannot open.\n", argv[1]);
		exit(1);
  	}

	//For second argument
	int q_insertion = atoi(argv[2]);

	char new_filename[SIZE_FILENAME];
	strcpy(new_filename, argv[1]);
	strcat(new_filename, ".from");

	FILE *fp_out = fopen(new_filename, "w");

	int out, q_current = 0;	

	while (((out = fgetc(fp_in)) != EOF) && q_current != q_insertion)
	{
		fputc(out, fp_out);
		if (out == '.')
		{
			fputc('\n', fp_out);
			q_current++;
		}
	}
	
	if(fclose(fp_in))
	{ 
		printf("Error close of file.\n");
		exit(1);
	}

	if(fclose(fp_out))
	{ 
		printf("Error close of file.\n");
		exit(1);
	}
	

	printf("\n----Programm is finished----\n");
	return 0;
}