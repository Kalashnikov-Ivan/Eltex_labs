#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include "support_func.h"
#include "tasks.h"

//-----------------------------------------

//Task_1
unsigned int sort_by_greatest_string(string *strings[], size_t q_str) 
{
	for (size_t i = 0; i < q_str; i++)
		strings[i]->counter = strings[i]->size;

    //unsigned int swaps = bubble_sort_string_count(strings, q_str, 0);
	unsigned int swaps = q_sort_string_count(strings, 0, q_str - 1, 0);

	printf("\nAfter sort by greatest string:\n");

	for (size_t i = 0; i < q_str; i++) {
		printf("%s\n", strings[i]->string);
		printf("len: %d\n", strings[i]->size - 1);
	}

	printf("\nSwaps: %d\n", swaps);
	printf("Length of less string: %d\n", strings[0]->size - 1);

    return swaps;
}

//Task_2
unsigned int sort_by_lesser_string(string *strings[], size_t q_str)
{
	for (size_t i = 0; i < q_str; i++)
		strings[i]->counter = strings[i]->size;
		
    //unsigned int swaps = bubble_sort_string_count(strings, q_str, 1)
	unsigned int swaps = q_sort_string_count(strings, 0, q_str - 1, 1);

	printf("\nAfter sort by less string:\n");

	for (size_t i = 0; i < q_str; i++) {
		printf("%s\n", strings[i]->string);
		printf("len: %d\n", strings[i]->size - 1);
	}

	printf("\nSwaps: %d\n", swaps);
	printf("Length of greatest string: %d\n", strings[0]->size - 1);

    return swaps;
}

//-----------------------------------------

//Task_3
unsigned int sort_by_alphabet_A(string *strings[], size_t q_str)
{
		for (size_t i = 0; i < q_str; i++)
			if (is_big(strings[i]->counter = strings[i]->string[0]))
				strings[i]->counter += 32;

    //unsigned int swaps = bubble_sort_string_count(strings, q_str, 0)
	unsigned int swaps = q_sort_string_count(strings, 0, q_str - 1, 0);

	printf("\nAfter sort by alphabet from 'a':\n");

	for (size_t i = 0; i < q_str; i++) {
		printf("%s\n", strings[i]->string);
		//printf("len: %d\n", strings[i]->size - 1);
	}

	printf("\nSwaps: %d\n", swaps);
	printf("First letter of first string: %c\n", strings[0]->string[0]);

    return swaps;
}

//Task_4
unsigned int sort_by_alphabet_Z(string *strings[], size_t q_str)
{
	for (size_t i = 0; i < q_str; i++)
		if (is_big(strings[i]->counter = strings[i]->string[0]))
			strings[i]->counter += 32;

    //unsigned int swaps = bubble_sort_string_count(strings, q_str, 1)
	unsigned int swaps = q_sort_string_count(strings, 0, q_str - 1, 1);

	printf("\nAfter sort by alphabet from 'z':\n");

	for (size_t i = 0; i < q_str; i++) {
		printf("%s\n", strings[i]->string);
		//printf("len: %d\n", strings[i]->size - 1);
	}

	printf("\nSwaps: %d\n", swaps);
	printf("Length of first string: %d\n", strings[0]->size - 1);
	printf("First letter of first string: %c\n", strings[0]->string[0]);

    return swaps;
}

//-----------------------------------------

//Task_5
unsigned int sort_by_words_BE(string *strings[], size_t q_str)
{
	for (size_t i = 0; i < q_str; i++) 
	{
		strings[i]->counter = 0;
		for (size_t j = 0; strings[i]->string[j] != '\0'; j++)
			if (strings[i]->string[j] != ' ' && strings[i]->string[j + 1] == ' ')
				strings[i]->counter++;
	}
			
    //unsigned int swaps = bubble_sort_string_count(strings, q_str, 0)
	unsigned int swaps = q_sort_string_count(strings, 0, q_str - 1, 0);

	printf("\nAfter sort by the number of words with the greatest:\n");

	for (size_t i = 0; i < q_str; i++) 
	{
		printf("%s\n", strings[i]->string);
		//printf("len: %d\n", strings[i]->size - 1);
	}

	printf("\nSwaps: %d\n", swaps);
	printf("First letter of last string: %c\n", strings[q_str - 1]->string[0]);

    return swaps;
}

//Task_6
unsigned int sort_by_words_LE(string *strings[], size_t q_str)
{
	for (size_t i = 0; i < q_str; i++) 
	{
		strings[i]->counter = 0;
		for (size_t j = 0; strings[i]->string[j] != '\0'; j++)
			if (strings[i]->string[j] != ' ' && strings[i]->string[j + 1] == ' ')
				strings[i]->counter++;
	}
			
    //unsigned int swaps = bubble_sort_string_count(strings, q_str, 1)
	unsigned int swaps = q_sort_string_count(strings, 0, q_str - 1, 1);

	printf("\nAfter sort by the number of words with the less:\n");

	for (size_t i = 0; i < q_str; i++) 
	{
		printf("%s\n", strings[i]->string);
		//printf("len: %d\n", strings[i]->size - 1);
	}

	printf("\nSwaps: %d\n", swaps);
	printf("Max the number of words in string: %d\n", strings[0]->counter);

    return swaps;
}

//-----------------------------------------

//Task_7
unsigned int sort_by_count_nums_BE(string *strings[], size_t q_str)
{
	for (size_t i = 0; i < q_str; i++) 
	{
		strings[i]->counter = 0;
		for (size_t j = 0; strings[i]->string[j] != '\0'; j++)
			if (is_num(strings[i]->string[j]))
				strings[i]->counter++;
	}
			
    //unsigned int swaps = bubble_sort_string_count(strings, q_str, 0)
	unsigned int swaps = q_sort_string_count(strings, 0, q_str - 1, 0);

	printf("\nAfter sort by the number of words with the less:\n");

	char first_num = 0, second_num = -1;

	for (size_t i = 0; i < q_str; i++) 
	{
		printf("%s\n", strings[i]->string);
		
		//Find second num
		if (strings[i]->counter != 0)
		{
			size_t j = 0;
			while (!is_num(strings[i]->string[j]) && j < strings[i]->size - 2)
				j++;
			if (is_num(strings[i]->string[j]))
				first_num = strings[i]->string[j];
			/*if (++j == strings[i]->size - 1)
				j--;*/
			j++;
			while (!is_num(strings[i]->string[j]) && j < strings[i]->size - 2)
				j++;
			if (is_num(strings[i]->string[j]))
				second_num = strings[i]->string[j];


			printf("Number of digits: %d\n", strings[i]->counter);
			if (second_num != -1)
				printf("Second digit of string: %c\n", second_num);
			else
				printf("String contain only one digit: %c\n", first_num);

		}
		else
		{
			printf("Number of digits: %d\n", strings[i]->counter);
			printf("String without digits\n");
		}
	}

	printf("\nSwaps: %d\n", swaps);

    return swaps;
}

//Task_8
unsigned int sort_by_count_nums_LE(string *strings[], size_t q_str)
{
	for (size_t i = 0; i < q_str; i++) 
	{
		strings[i]->counter = 0;
		for (size_t j = 0; strings[i]->string[j] != '\0'; j++)
			if (is_num(strings[i]->string[j]))
				strings[i]->counter++;
	}
			
    //unsigned int swaps = bubble_sort_string_count(strings, q_str, 1)
	unsigned int swaps = q_sort_string_count(strings, 0, q_str - 1, 1);

	printf("\nAfter sort by the number of words with the greatest:\n");

	for (size_t i = 0; i < q_str; i++) 
	{
		printf("%s\n", strings[i]->string);
		printf("Number of digits: %d\n", strings[i]->counter);
	}

	printf("\nSwaps: %d\n", swaps);

    return swaps;
}

//-----------------------------------------

//Task_9
unsigned int sort_by_first_word_BE(string *strings[], size_t q_str)
{
	for (size_t i = 0; i < q_str; i++) 
	{
		strings[i]->counter = 0;
		size_t j = 0;
		while (strings[i]->string[j] == ' ')
			j++;
			
		while (strings[i]->string[j] > ' ')
		{
			strings[i]->counter++;
			j++;
		}
	}
			
    //unsigned int swaps = bubble_sort_string_count(strings, q_str, 0)
	unsigned int swaps = q_sort_string_count(strings, 0, q_str - 1, 0);

	uint32_t *max_len_word = (uint32_t*)calloc(q_str ,sizeof(uint32_t));

	for (size_t i = 0; i < q_str; i++) 
	{
		uint32_t current;
		for (size_t j = 0; strings[i]->string[j] != '\0'; j++)
		{
			current = 0;
			while (strings[i]->string[j] == ' ')
				j++;
			
			while (strings[i]->string[j] > ' ')
			{
				current++;
				j++;
			}

			if (current > max_len_word[i])
				max_len_word[i] = current;
		}
	}

	printf("\nAfter sort by the length of first word from less to big:\n");

	for (size_t i = 0; i < q_str; i++) 
	{
		printf("%s\n", strings[i]->string);
		printf("Max len of word: %d\n", max_len_word[i]);
	}

	printf("\nSwaps: %d\n", swaps);


	free(max_len_word);
    return swaps;
}

//Task_10
/*unsigned int sort_by_first_word_LE(string *strings[], size_t q_str)
{
	for (size_t i = 0; i < q_str; i++) 
	{
		strings[i]->counter = 0;
		size_t j = 0;
		while (strings[i]->string[j] == ' ')
			j++;
			
		while (strings[i]->string[j] > ' ')
		{
			strings[i]->counter++;
			j++;
		}
	}
			
    //unsigned int swaps = bubble_sort_string_count(strings, q_str, 1)
	unsigned int swaps = q_sort_string_count(strings, 0, q_str - 1, 1);

	uint32_t *words_counter = (uint32_t*)calloc(q_str, sizeof(uint32_t));

	uint32_t *min_len_word = (uint32_t*)calloc(q_str ,sizeof(uint32_t));

	for (size_t i = 0; i < q_str; i++) 
	{
		uint32_t current;
		for (size_t j = 0; strings[i]->string[j] != '\0'; j++)
		{
			current = 0;
			while (strings[i]->string[j] == ' ')
				j++;
			
			while (strings[i]->string[j] > ' ')
			{
				current++;
				j++;
			}
			
			if (current < min_len_word[i] && )
				min_len_word[i] = current;

			j--;

			if (strings[i]->string[j] != ' ' && strings[i]->string[j + 1] == ' ')
				words_counter[i]++;
		}
	}

	printf("\nAfter sort by the length of first word from big to less:\n");

	for (size_t i = 0; i < q_str; i++) 
	{
		printf("%s\n", strings[i]->string);
		printf("Min len of word: %d\n", min_len_word[i]);
	}

	printf("\nSwaps: %d\n", swaps);
	printf("")


	free(min_len_word);
    return swaps;
}*/

//-----------------------------------------