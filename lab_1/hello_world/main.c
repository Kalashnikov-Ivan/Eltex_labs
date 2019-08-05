#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//For forks
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>


void itoa(int n, char s[]);
void reverse(char s[]);

struct test
{
	int a;
};


int main(void) {

	/*printf("Hello, world!\n");

	uint8_t min = 5, max = 42;
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		int32_t cur =  min + rand() % (min - max);
		printf("%d\n", cur);
	}

	struct test t1;
	printf("test: %d\n", t1.a);*/

	FILE *fp = fopen("test", "a+");

	char buff[128];

	itoa(4266, buff);

	fputs(buff, fp);

	printf("%s\n", buff);
	
	return 0;
}

 void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* записываем знак */
         n = -n;          /* делаем n положительным числом */
     i = 0;
     do {       /* генерируем цифры в обратном порядке */
         s[i++] = n % 10 + '0';   /* берем следующую цифру */
     } while ((n /= 10) > 0);     /* удаляем */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }

  void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }