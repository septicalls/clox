#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, char *argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    // Gibberish instructions to test line numbers
    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, constant, 1);

    constant = addConstant(&chunk, 2.1);
    writeChunk(&chunk, OP_CONSTANT, 2);
    writeChunk(&chunk, constant, 2);

    writeConstant(&chunk, 355 / 113.0, 3);

    writeChunk(&chunk, OP_RETURN, 3);

    disassembleChunk(&chunk, "Trying out new line numbers");
    freeChunk(&chunk);
    return 0;
}