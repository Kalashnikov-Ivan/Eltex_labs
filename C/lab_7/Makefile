CC=gcc
CFLAGS=-c -Wall -std=c99 -O0 -g

all : lab_7.elf

lab_7.elf : main.o warcraft.o
	$(CC) main.o warcraft.o -o lab_7.elf

main.o : main.c
	$(CC) $(CFLAGS) main.c

warcraft.o : warcraft.c
	$(CC) $(CFLAGS) warcraft.c
	
clean:
	rm -rf *.os