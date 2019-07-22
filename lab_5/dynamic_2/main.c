/*

		Author: Kalashnikov Ivan
		Task: Lab_5, Var 6.4 (dynamic)

*/


#include <stdio.h>
#include <dlfcn.h>

#define STR_SIZE 128UL

int main(void) 
{

	void *str_op_HAND = dlopen("/home/st/Work/Eltex/C/lab_5/myLib/libDL_str_op.so", RTLD_LAZY);
	if (str_op_HAND == NULL)
	{
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		exit(1);
	}

	void (*conc)(char * restrict dest, const size_t capacity_dest, 
 				 const char * restrict source) = dlsym(str_op_HAND, "str_conc");
	


	void (*gap)(char * restrict dest, const size_t capacity_dest, 
 				char * restrict source, int gap_from)= dlsym(str_op_HAND, "str_gap");


	char str[STR_SIZE] = "hello again, ";
	(*conc)(str, STR_SIZE, "dynamic libs");

	printf("%s\n", str);


	char str2[STR_SIZE];
	(*gap)(str2, STR_SIZE, str, 14);

	printf("%s, bye again!\n", str2);

	dlclose(str_op_HAND);

	return 0;
}