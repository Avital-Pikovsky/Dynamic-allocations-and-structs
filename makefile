CC = gcc
FLAGS = -Wall -g

all: main

main: main.o frequency.o
	$(CC) $(FLAGS) -o main main.o frequency.o

main.o: main.c frequency.h
	$(CC) $(FLAGS) -c main.c 

frequency.o: frequency.c frequency.h
	$(CC) $(FLAGS) -c frequency.c 

.PHONY: clean all

clean:
	rm -f *.o main
