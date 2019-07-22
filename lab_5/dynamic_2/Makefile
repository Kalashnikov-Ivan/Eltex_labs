CC=gcc
CFLAGS=-c -Wall -std=c99
#LIBS=-L/home/st/Work/Eltex/C/lab_5/myLib/ -lDL_str_op

all : dynaminc_2.elf

dynaminc_2.elf : main.o
	$(CC) main.o -ldl -o dynaminc_2.elf

main.o : main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -rf *.o