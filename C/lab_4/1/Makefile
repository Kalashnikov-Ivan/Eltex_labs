CC=gcc
CFLAGS=-c -Wall -std=c99 -O0 -g

all : 1.x

1.x : main.o
	$(CC) main.o -o 1.x

main.o : main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -rf *.o