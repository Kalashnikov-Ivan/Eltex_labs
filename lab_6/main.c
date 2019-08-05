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

void itoa(int num, char str_in[]);
void reverse(char str[]);

int main(void) 
{

	FILE *fp;
	size_t size_x = 10UL;
	size_t size_y = 5UL;

	uint32_t quantity_bubbles = 2;
	if (quantity_bubbles > ((size_x - 2) * (size_y - 2)))
		return 1;

	field *field = init_field(size_x, size_y, quantity_bubbles);

	system("clear");
	print_field(field);
	

	const int32_t min_dx = -1, min_dy = -1,
				  max_dx =  2, max_dy =  2;

	
	if (NULL == (fp = fopen("exchange.buf", "w")))
	{
		printf("File %s cannot open.\n", "exchange.buf");
		exit(1);
  	}
	
	uint8_t buff[128];
	uint8_t buff_support[128];

	uint32_t global_q_bubbles = field->quant_bubbles;

	while (field->quant_bubbles)
	{
		for (size_t j = 0; j < global_q_bubbles; j++)
		{
			uint32_t rand_dx = get_rand_in_range(min_dx, max_dx), 
					 rand_dy = get_rand_in_range(min_dy, max_dy);

			move_bubble(field, &field->bubbles[j], rand_dx, rand_dy);

			itoa(field->bubbles[j].cord_x, buff);
			strcat(buff, " ");
			itoa(field->bubbles[j].cord_y, buff_support);
			strcat(buff, buff_support);
			strcat(buff, "\n");

			fputs(buff, fp);
		}

		usleep(300000);
		system("clear");
		print_field(field);
	}
	


	if(fclose(fp))
	{ 
		printf("Error close of file.\n");
		exit(1);
	}

	free_field(field);

	return 0;
}

void itoa(int num, char str_in[])
 {
     int sign = num;
 
    if (sign < 0)  			  /* записываем знак */
         num = -num;          /* делаем n положительным числом */

    int i = 0;
     do 					  /* генерируем цифры в обратном порядке */
	 {       
         str_in[i++] = num % 10 + '0';   /* берем следующую цифру */
     } while ((num /= 10) > 0);     	 /* удаляем */

     if (sign < 0)
         str_in[i++] = '-';

     str_in[i] = '\0';
     reverse(str_in);
 }

void reverse(char str[])
 {
     char ch;
 
     for (int i = 0, j = strlen(str) - 1; i < j; i++, j--) {
         ch = str[i];
         str[i] = str[j];
         str[j] = ch;
     }
 }