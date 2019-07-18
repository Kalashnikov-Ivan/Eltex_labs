CC=gcc
CFLAGS=-c -Wall -std=c99 -O0 -g

all : lab_4.x

lab_4.x : main.o
	$(CC) main.o -o lab_4.x

main.o : main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -rf *.o