CC=gcc
CFLAGS=-c -Wall -std=c99 -O0 -g

all : lab_10.elf

lab_10.elf : main.o walkers_game.o
	$(CC) main.o walkers_game.o -lpthread -o lab_10.elf

main.o : main.c
	$(CC) $(CFLAGS) main.c

walkers_game.o : walkers_game.c
	$(CC) $(CFLAGS) walkers_game.c

clean:
	rm -rf *.o