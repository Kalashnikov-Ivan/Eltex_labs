CC=gcc
CFLAGS=-c -Wall -std=c99
LIBS=-L/home/st/Work/Eltex/C/lab_5/myLib/ -lStr_op

all : static.elf

static.elf : main.o
	$(CC) main.o $(LIBS) -o static.elf

main.o : main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -rf *.o