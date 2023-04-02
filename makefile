UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
LIB = -lncurses
else
LIB = -lpdcurses
endif

all:snake main

main:
	gcc main.c snake.o $(LIB) -static -o snake.exe

snake:
	gcc -c snake.c


clean:
	del *.o