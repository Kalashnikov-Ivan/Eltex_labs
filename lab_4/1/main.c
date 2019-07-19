/*

		Author: Kalashnikov Ivan

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...

#define SIZE_FILENAME 128UL

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

	char new_filename[SIZE_FILENAME];

	size_t i = 0;
	for (; argv[1][i] != '\0'; i++)
		new_filename[i] = argv[1][i];
	
	new_filename[i++] = '.';
	new_filename[i++] = 'f';
	new_filename[i++] = 'r';
	new_filename[i++] = 'o';
	new_filename[i++] = 'm';
	new_filename[i] = '\0';

	/*printf("%s\n", new_filename);

	int out;
	while ((out = fgetc(fp_in)) != EOF)
	{
		printf("%c\n", out);
		printf("%ld\n", fp_in->_IO_read_ptr);
		fp_in->_IO_read_ptr--;
		out = fgetc(fp_in);
		printf("%c\n", out);
		printf("%ld\n", fp_in->_IO_read_ptr);
	}
	*/

	FILE *fp_out = fopen(new_filename, "w");

	int out, bool_with_num = 0;

	for (size_t i = 0, j = 0; out != EOF;)
	{
		while (out = getc(fp_in))
		{
			if (isdigit(out))
				bool_with_num = 1;

		}
	}

	if(fclose(fp_in))
	{ 
		printf("Error of close file.\n");
		exit(1);
	}
	

	printf("\n----Programm is finished----\n");
	return 0;
}