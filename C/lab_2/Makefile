all : lab_2.x

lab_2.x : main.o support_func.o tasks.o
	gcc main.o support_func.o tasks.o -o lab_2.x

main.o : main.c
	gcc -Wall -std=c11 -c -g -O0 main.c

tasks.o : tasks.c
	gcc -Wall -std=c11 -c -g -O0 tasks.c

support_func.o : support_func.c
	gcc -Wall -std=c11 -c -g -O0 support_func.c

clean:
	rm -rf *.o lab_2.x