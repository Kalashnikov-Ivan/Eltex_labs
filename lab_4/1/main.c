/*

		Author: Kalashnikov Ivan
		Task: Lab_4, Var 6.1

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...

#define FILENAME_SIZE 128UL
#define BUFF_SIZE 2056UL

int main(int argc, char *argv[]) 
{
	FILE *fp_in;

	if (argc < 3)
	{
		fprintf (stderr, "Too few arguments. Use <filename>\n");
		exit(1);
    }

	if((fp_in = fopen(argv[1], "r")) == NULL)
	{
		printf("File %s cannot open.\n", argv[1]);
		exit(1);
  	}

	//For second argument
	int q_str = atoi(argv[2]);

	char new_filename[FILENAME_SIZE];
	strcpy(new_filename, argv[1]);
	strcat(new_filename, ".from");

	FILE *fp_out = fopen(new_filename, "w");

	int bool_with_num;
	char buff[BUFF_SIZE];

	for (int q_current = 0; q_current != q_str; q_current++)
	{
		bool_with_num = 0;
		fgets(buff, BUFF_SIZE, fp_in);

		for (size_t i = 0; buff[i] != '\n'; i++)
		{
			if (isdigit(buff[i]))
				bool_with_num = 1;
		}

		if (!bool_with_num)
			fputs(buff, fp_out);
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