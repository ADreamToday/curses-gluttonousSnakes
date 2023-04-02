UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
LIB = -lncurses
OUT = snake
DEL = rm
else
LIB = -lpdcurses
OUT = snake.exe
DEL = del
endif

all:snake main

main:
	gcc main.c snake.o $(LIB) -o $(OUT)

snake:
	gcc -c snake.c
static:
	gcc main.c snake.o $(LIB) -static -o $(OUT)

clean:
	$(DEL) *.o
