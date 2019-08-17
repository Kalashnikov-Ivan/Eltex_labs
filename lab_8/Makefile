CC=gcc
CFLAGS=-c -Wall -std=c99 -O0 -g

all : lab_8.elf

lab_8.elf : main.o
	$(CC) main.o -o lab_8.elf

main.o : main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -rf *.o