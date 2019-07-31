CC=gcc
CFLAGS=-c -Wall -std=c99 -O0 -g

all : lab_6.elf

lab_6.elf : main.o bubbles.o
	$(CC) main.o bubbles.o -o lab_6.elf

main.o : main.c
	$(CC) $(CFLAGS) main.c

bubbles.o : bubbles.c
	$(CC) $(CFLAGS) bubbles.c
	
clean:
	rm -rf *.o