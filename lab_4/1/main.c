/*

		Author: Kalashnikov Ivan

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

	if (argc < 2)
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
	int q_str = atoi(argv[2]);

	char new_filename[FILENAME_SIZE];

	{
		size_t i = 0;
		for (; argv[1][i] != '\0'; i++)
			new_filename[i] = argv[1][i];

		new_filename[i++] = '.';
		new_filename[i++] = 'f';
		new_filename[i++] = 'r';
		new_filename[i++] = 'o';
		new_filename[i++] = 'm';
		new_filename[i] = '\0';
	}

	FILE *fp_out = fopen(new_filename, "w");

	int out, bool_with_num, q_current = 0;
	char buff[BUFF_SIZE];

	for (int symbol_count; q_current != q_str; q_current++)
	{
		bool_with_num = 0;
		fgets(buff, BUFF_SIZE, fp_in);

		for (size_t i = 0; buff[i] != '\n'; i++)
		{
			if (isdigit(buff[i]))
				bool_with_num = 1;
		}

		if (!bool_with_num)
		{
			fp_in->_IO_read_ptr -= symbol_count;
			while ((out = fgetc(fp_in)) != '\n' && out != EOF)
				fputc(out, fp_out);
			fputc(out, fp_out);
		}

		if (out == EOF)
			break;
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