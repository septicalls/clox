CC = gcc
FLAGS = Wall -O3

clox: main.o chunk.o memory.o debug.o
	$(CC) -o clox main.o chunk.o memory.o debug.o

main: common.h
	$(CC) $(FLAGS) main.c -o main.o

chunk: common.h chunk.h memory.h
	$(CC) $(FLAGS) chunk.c -o chunk.o

memory: common.h memory.h
	$(CC) $(FLAGS) memory.c -o memory.o

debug: common.h debug.h
	$(CC) $(FLAGS) debug.c -o debug.o

clean:
	rm *.o clox