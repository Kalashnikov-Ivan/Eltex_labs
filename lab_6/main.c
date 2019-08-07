/*

		Author: Kalashnikov Ivan
		Task: Lab_6, Var 6 (bubbles)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "bubbles.h"

const int32_t min_dx = -1, min_dy = -1,
			  max_dx =  2, max_dy =  2;

const size_t BUFF_SIZE = 128UL,
	 		 MAX_FORKS = 128UL;

void itoa(int num, char str_in[]);
void reverse(char str[]);

int main(void) 
{
	FILE *fp;
	const size_t size_x = 30UL;
	const size_t size_y = 10UL;

	const uint32_t quantity_bubbles = 5;
	if (quantity_bubbles > ((size_x - 2) * (size_y - 2)) && quantity_bubbles > MAX_FORKS)
		return 1;

	field *field = init_field(size_x, size_y, quantity_bubbles);

	system("clear");
	print_field(field);

	uint8_t buff[BUFF_SIZE];
	uint8_t buff_support[BUFF_SIZE];

	int16_t pid[MAX_FORKS];

	uint32_t global_q_bubbles = field->quant_bubbles;

	while (field->quant_bubbles)
	{

		if (NULL == (fp = fopen("exchange.buf", "w")))
		{
			printf("File %s cannot open.\n", "exchange.buf");
			exit(1);
		}
		if(fclose(fp))
		{ 
			printf("Error close of file.\n");
			exit(1);
		}

		int32_t rand_dx, 
				rand_dy;

		for (size_t j = 0; j < global_q_bubbles; j++)
		{
			pid[j] = fork();

			srand(getpid());

			if (-1 == pid[j])
			{
				perror("fork");
				exit(1);
			}
			else if (0 == pid[j])
			{

				if (NULL == (fp = fopen("exchange.buf", "a")))
				{
					printf("File %s cannot open.\n", "exchange.buf");
					exit(1);
				}

				rand_dx = get_rand_in_range(min_dx, max_dx); 
				rand_dy = get_rand_in_range(min_dy, max_dy);

				move_bubble(field, &field->bubbles[j], rand_dx, rand_dy);

				//Creating string which will put in exchange file
				itoa(j, buff);
				strcat(buff, " ");
				itoa(field->bubbles[j].cord_x, buff_support);
				strcat(buff, buff_support);
				strcat(buff, " ");
				itoa(field->bubbles[j].cord_y, buff_support);
				strcat(buff, buff_support);
				strcat(buff, " ");
				strcat(buff, "\n");

				fputs(buff, fp);

				if(fclose(fp))
				{ 
					printf("Error close of file.\n");
					exit(1);
				}

				exit(0);
			}
		}

		if (NULL == (fp = fopen("exchange.buf", "r")))
		{
			printf("File %s cannot open.\n", "exchange.buf");
			exit(1);
		}

		size_t cur_bubble = 0;
		for (size_t i = 0; i < global_q_bubbles; i++)
		{
       		waitpid(pid[i], NULL, 0);
			
			fgets(buff, BUFF_SIZE, fp);

			uint8_t *tmp = strtok(buff, " ");
			cur_bubble = atoi(tmp);

			if (field->bubbles[cur_bubble].alive)
			{
				field->area[field->bubbles[cur_bubble].cord_y][field->bubbles[cur_bubble].cord_x] = ' ';

				tmp = strtok(NULL, " ");
				field->bubbles[cur_bubble].cord_x = atoi(tmp);

				tmp = strtok(NULL, " ");
				field->bubbles[cur_bubble].cord_y = atoi(tmp);

				if (is_board(field, field->bubbles[cur_bubble].cord_x, field->bubbles[cur_bubble].cord_y))
				{
					field->bubbles[cur_bubble].alive = false;
					field->quant_bubbles--;
				}
				else
					field->area[field->bubbles[cur_bubble].cord_y][field->bubbles[cur_bubble].cord_x] = 'o';
			}
		}

		if(fclose(fp))
		{ 
			printf("Error close of file.\n");
			exit(1);
		}
		
		usleep(600000);
		system("clear");
		print_field(field);

		for (int i = 0; i < global_q_bubbles; i++)
			printf("%d: x = %2d | y = %2d\n", i + 1, field->bubbles[i].cord_x, field->bubbles[i].cord_y);
	}

	free_field(field);

	return 0;
}

void itoa(int num, char str_in[])
 {
    int sign = num;
 
    if (sign < 0)  			  /* записываем знак */
         num = -num;          /* делаем n положительным числом */

    size_t i = 0;
    do 					  	  /* генерируем цифры в обратном порядке */
	{       
    	str_in[i++] = num % 10 + '0';   /* берем следующую цифру */
    } while ((num /= 10) > 0);     	    /* удаляем */

    if (sign < 0)
        str_in[i++] = '-';

    str_in[i] = '\0';
    reverse(str_in);
 }

void reverse(char str[])
 {
    char ch;
 
    for (size_t i = 0, j = strlen(str) - 1; i < j; i++, j--) 
	{
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }
 }