#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

#define LINE_BUFFER_SIZE 256

void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    // lines stores number of instructions per line 
    // where index == line_number
    chunk->lines = NULL;
    chunk->lineCapacity = 0;
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
            oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;

    // This is to ensure that the program doesn't crash when
    // the difference in line number is greater than LINE_BUFFER_SIZE
    while(chunk->lineCapacity < line + 1) updateLineArray(chunk, line);
    chunk->lines[line]++;
    chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void updateLineArray(Chunk *chunk, int line) {
    // This snippet assumes that line number can only be a 
    // positive integer in non-decreasing order
    int oldLineCapacity = chunk->lineCapacity;
    chunk->lineCapacity += LINE_BUFFER_SIZE;
    chunk->lines = GROW_ARRAY(int, chunk->lines,
        oldLineCapacity, chunk->lineCapacity);
    for (int i = oldLineCapacity; i < chunk->lineCapacity; i++) {
        chunk->lines[i] = 0;
    }
}