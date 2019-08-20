CC=gcc
CFLAGS=-c -Wall -std=c99 -O0 -g

all : lab_10.elf

lab_10.elf : main.o
	$(CC) main.o -o lab_10.elf

main.o : main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -rf *.o