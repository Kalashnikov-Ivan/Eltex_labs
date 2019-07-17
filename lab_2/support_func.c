#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include "support_func.h"

//-----------------------------------------

void swap_int (int *a, int *b) 
{

	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_size (size_t *a, size_t *b) 
{
	size_t tmp = *a;
	*a = *b;
	*b = tmp;
}

unsigned int is_big(char ch)
{
	return (ch > 64 && ch < 91) ? 1 : 0;
}

unsigned int is_num(char ch)
{
	return (ch >= '0' && ch <= '9') ? 1 : 0;
}

//-----------------------------------------

size_t inp_str(char buff[], size_t max_size) {

	size_t i;
	for (i = 0; (i < max_size - 1) && ((buff[i] = getchar()) != '\n'); i++)
		;

	if (i == max_size - 1)
		fprintf(stderr, "Warning: buffer has been overflow!\nSaved only %ld characters, because buffer size is %ld\n", i + 1, max_size);

	buff[i] = '\0';
	return i + 1;
}

//-----------------------------------------

void bubble_sort(int arr[], size_t size_arr, char flag_reverse) {

	unsigned char boolSwapped = 0;
	for (size_t i = 0; i < size_arr - 1; i++)
	{
		boolSwapped = 0;
		for (size_t j = 0; j < size_arr - i - 1; j++)
		{
			if ((arr[j] > arr[j + 1])  && flag_reverse == 0)
			{
				swap_int(&arr[j], &arr[j + 1]);
				boolSwapped = 1;
			}
			else if ((arr[j] < arr[j + 1]) && flag_reverse == 1)
			{
				swap_int(&arr[j], &arr[j + 1]);
				boolSwapped = 1;
			}
		}
		if (boolSwapped == 0)
			break;
	}
}

void bubble_sort_string (string *strings[], size_t quantity_s, char flag_reverse) {

	unsigned char boolSwapped = 0;
	for (size_t i = 0; i < quantity_s - 1; i++)
	{
		boolSwapped = 0;
		for (size_t j = 0; j < quantity_s - i - 1; j++)
		{
			if ((strings[j]->counter > strings[j + 1]->counter) && flag_reverse == 0)
			{
				swap_size(&strings[j], &strings[j + 1]);
				boolSwapped = 1;
			}
			else if ((strings[j]->counter < strings[j + 1]->counter) && flag_reverse == 1)
			{
				swap_size(&strings[j], &strings[j + 1]);
				boolSwapped = 1;
			
			}
		if (boolSwapped == 0)
			break;
		}
	}
}

unsigned int bubble_sort_string_count (string *strings[], size_t quantity_s, char flag_reverse) {

	unsigned int counter = 0;

	unsigned char boolSwapped = 0;
	for (size_t i = 0; i < quantity_s - 1; i++)
	{
		boolSwapped = 0;
		for (size_t j = 0; j < quantity_s - i - 1; j++)
		{
			if ((strings[j]->counter > strings[j + 1]->counter) && flag_reverse == 0)
			{
				swap_size(&strings[j], &strings[j + 1]);
				boolSwapped = 1;
				counter++;
			}
			else if ((strings[j]->counter < strings[j + 1]->counter) && flag_reverse == 1)
			{
				swap_size(&strings[j], &strings[j + 1]);
				boolSwapped = 1;
				counter++;
			}
		}
		if (boolSwapped == 0)
			break;
	}

	return counter;
}

//-----------------------------------------

void q_sort(int arr[], int first_index, int last_index, char flag_reverse)
{
    if (first_index < last_index)
    {
        int left = first_index, 
			right = last_index, 
			pivot = arr[(left + right) >> 1];

		if (flag_reverse == 0)
		{
			do
			{
				while (arr[left] < pivot) left++;
				while (arr[right] > pivot) right--;
				if (left <= right)
				{
					swap_int(&arr[left], &arr[right]);
					left++; right--;
				}
			} while (left <= right);
		}
		else
		{
			do
			{
				while (arr[left] > pivot) left++;
				while (arr[right] < pivot) right--;
				if (left <= right)
				{
					swap_int(&arr[left], &arr[right]);
					left++; right--;
				}
			} while (left <= right);
		}
		
        q_sort(arr, first_index, right, flag_reverse);
        q_sort(arr, left, last_index, flag_reverse);
    }
}

void q_sort_string(string *strings[], int first_index, int last_index, char flag_reverse)
{
    if (first_index < last_index)
    {
        int left = first_index, 
			right = last_index, 
			pivot = strings[(left + right) >> 1]->counter;

        if (flag_reverse == 0)
		{
			do
			{
				while (strings[left]->counter < pivot) left++;
				while (strings[right]->counter > pivot) right--;
				if (left <= right)
				{
					swap_size(&strings[left], &strings[right]);
					left++; right--;
				}
			} while (left <= right);
		}
		else
		{
			do
			{
				while (strings[left]->counter > pivot) left++;
				while (strings[right]->counter < pivot) right--;
				if (left <= right)
				{
					swap_size(&strings[left], &strings[right]);
					left++; right--;
				}
			} while (left <= right);
		}
		
        q_sort_string(strings, first_index, right, flag_reverse);
        q_sort_string(strings, left, last_index, flag_reverse);
    }
}

unsigned int q_sort_string_count(string *strings[], int first_index, int last_index, char flag_reverse)
{
	static unsigned int counter = 0;
    if (first_index < last_index)
    {
        int left = first_index, 
			right = last_index, 
			pivot = strings[(left + right) >> 1]->counter;

        if (flag_reverse == 0)
		{
			do
			{
				while (strings[left]->counter < pivot) left++;
				while (strings[right]->counter > pivot) right--;
				if (left <= right)
				{
					swap_size(&strings[left], &strings[right]);
					left++; right--;
					counter++;
				}
			} while (left <= right);
		}
		else
		{
			do
			{
				while (strings[left]->counter > pivot) left++;
				while (strings[right]->counter < pivot) right--;
				if (left <= right)
				{
					swap_size(&strings[left], &strings[right]);
					left++; right--;
					counter++;
				}
			} while (left <= right);
		}

        q_sort_string_count(strings, first_index, right, flag_reverse);
        q_sort_string_count(strings, left, last_index, flag_reverse);
    }

	return counter;
}