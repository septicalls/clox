#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, char *argv[]) {
    initVM();

    Chunk chunk;
    initChunk(&chunk);

    // Load 2 onto the stack
    int constant = addConstant(&chunk, 2);
    writeChunk(&chunk, OP_CONSTANT, 5);
    writeChunk(&chunk, constant, 5);

    // Load 3 onto the stack
    constant = addConstant(&chunk, 3);
    writeChunk(&chunk, OP_CONSTANT, 4);
    writeChunk(&chunk, constant, 4);

    // Put 2 * 3 onto the stack
    writeChunk(&chunk, OP_MULTIPLY, 6);
    // Load 4 onto the stack
    constant = addConstant(&chunk, 4);
    writeChunk(&chunk, OP_CONSTANT, 2);
    writeChunk(&chunk, constant, 2);

    // Load -5 onto the stack
    constant = addConstant(&chunk, 5);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, constant, 1);
    writeChunk(&chunk, OP_NEGATE, 1);

    // Put 4 / -5 on the stack
    writeChunk(&chunk, OP_DIVIDE, 3);

    // Put (2 * 3) - (4 / -5) on the stack
    writeChunk(&chunk, OP_SUBTRACT, 7);

    // Load 1 onto the stack
    constant = addConstant(&chunk, 1);
    writeChunk(&chunk, OP_CONSTANT, 8);
    writeChunk(&chunk, constant, 8);

    // Put 1 + ((2 * 3) - (4 / -5)) onto the stack
    writeChunk(&chunk, OP_ADD, 9);

    // Return!
    writeChunk(&chunk, OP_RETURN, 10);

    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);
    return 0;
}