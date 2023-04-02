UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
LIB = -lncurses
OUT = snake
else
LIB = -lpdcurses
OUT = snake.exe
endif

all:snake main

main:
	gcc main.c snake.o $(LIB) -static -o $(OUT)

snake:
	gcc -c snake.c


clean:
	del *.o