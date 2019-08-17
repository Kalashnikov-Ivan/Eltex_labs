CC=gcc
CFLAGS=-c -Wall -std=c99 -O0 -g

all : lab_8.elf

lab_8.elf : main.o battlefield.o
	$(CC) main.o battlefield.o -o lab_8.elf

main.o : main.c
	$(CC) $(CFLAGS) main.c

battlefield.o : battlefield.c
	$(CC) $(CFLAGS) battlefield.c
	
clean:
	rm -rf *.o