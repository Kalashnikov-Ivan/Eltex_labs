CC=gcc
CFLAGS=-c -Wall -std=c99 -O0 -g

all : 2.x

2.x : main.o
	$(CC) main.o -o 2.x

main.o : main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -rf *.o