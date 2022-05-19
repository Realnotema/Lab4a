all: run

comp: main.c process.c input.c timing.c
        gcc main.c process.c input.c timing.c -o lab4a.o -std=c11

run: comp
        ./lab4a.o

val: lab4a.o
        valgrind --leak-check=full ./lab4a.o
