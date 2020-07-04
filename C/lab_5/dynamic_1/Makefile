CC=gcc
CFLAGS=-c -Wall -std=c99
LIBS=-L../myLib/ -lDL_str_op

all : dynaminc_1.elf

dynaminc_1.elf : main.o
	$(CC) main.o $(LIBS) -o dynaminc_1.elf

main.o : main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -rf *.o