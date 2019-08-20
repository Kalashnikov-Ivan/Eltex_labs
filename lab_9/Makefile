CC=gcc
CFLAGS=-c -Wall -std=gnu99 -O0 -g

all : lab_9.elf

lab_9.elf : main.o
	$(CC) main.o -o lab_9.elf

main.o : main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -rf *.o