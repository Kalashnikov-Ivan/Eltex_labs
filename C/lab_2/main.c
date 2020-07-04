#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h> //For uint8_t and so on...
#include <stddef.h> //For size_t, ptrdiff_t and so on...


#include "support_func.h"
#include "tasks.h"

//#define BUFF_SIZE 1024UL
const size_t BUFF_SIZE = 1024UL;

int main(void) {

	uint8_t buff[BUFF_SIZE];

	long q_str = 0;
	printf("How much strings do you want to input?\n");
	printf("Quantity: ");

	while((scanf("%ld", &q_str) != 1) || (q_str < 0)) {
		printf("ERROR: enter correct positive value!\nQuantity: ");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	string **strings = (string**)malloc(sizeof(string*) * q_str);
		for (size_t i = 0; i < q_str; i++)
			strings[i] = (string*)malloc(sizeof(string));

	for (size_t i = 0; i < q_str; i++) {
		strings[i]->string = (uint8_t*)malloc((strings[i]->size = inp_str(buff, BUFF_SIZE)) * sizeof(uint8_t));
		//strcpy(strings[i]->string, buff); //----> Or memcpy?
		memcpy(strings[i]->string, buff, strings[i]->size);
	}

	printf("\n\n");

	printf("Your input:\n\n");

	for (size_t i = 0; i < q_str; i++) {
		printf("%s\n", strings[i]->string);
		printf("len: %ld\n", strings[i]->size - 1);
	}

	/*
	//Task_1
	sort_by_greatest_string(strings, q_str);

	//Task_2
	sort_by_lesser_string(strings, q_str);
	*/

	/*
	//Task_3
	sort_by_alphabet_A(strings, q_str);

	//Task_4
	sort_by_alphabet_Z(strings, q_str);
	*/

	/*
	//Task_5
	sort_by_words_BE(strings, q_str);

	//Task_6
	sort_by_words_LE(strings, q_str);
	*/

	/*
	//Task_7
	sort_by_count_nums_BE(strings, q_str);

	//Task_8
	sort_by_count_nums_LE(strings, q_str);
	*/

	//Task_9
	sort_by_first_word_BE(strings, q_str);


	for (size_t i = 0; i < q_str; i++) {
		free(strings[i]->string);
		free(strings[i]);
	}

	free(strings);

	printf("----Programm is finished----\n");
	return 0;
}