/*

		Author: Kalashnikov Ivan
		Task: Lab_5, Var 6.3 (dynamic)

*/


#include <stdio.h>

#include "../myLib/source/str_op.h"

#define STR_SIZE 128UL

int main(void) 
{
	char str[STR_SIZE] = "hello, ";
	str_conc(str, STR_SIZE, "dynamic libs");

	printf("%s\n", str);


	char str2[STR_SIZE];
	str_gap(str2, STR_SIZE, str, 8);

	printf("%s, bye!\n", str2);

	return 0;
}