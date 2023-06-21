CC = gcc
FLAGS = Wall -O3

clox: main.o chunk.o memory.o
	$(CC) -o clox main.o chunk.o memory.o

main: common.h
	$(CC) $(FLAGS) main.c -o main.o

chunk: common.h chunk.h memory.h
	$(CC) $(FLAGS) chunk.c -o chunk.o

memory: common.h memory.h
	$(CC) $(FLAGS) memory.c -o memory.o

clean:
	rm *.o clox