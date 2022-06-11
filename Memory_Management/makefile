CC = gcc
FLAGS = -Wpedantic -std=gnu99

all: helper.o heap.o holes.o holes

helper.o: helper.c
	$(CC) $(FLAGS) -c helper.c -o helper.o

heap.o: heap.c
	$(CC) $(FLAGS) -c heap.c -o heap.o

holes.o: holes.c myHeader.h
	$(CC) $(FLAGS) -c holes.c -o holes.o
holes: holes.o helper.o
	$(CC) $(FLAGS) holes.o helper.o heap.o -o holes

clean:
	rm *.o holes
