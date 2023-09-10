#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "memory.h"
#include "vm.h"

#define STACK_BUFFER_SIZE 256

VM vm;

static void resetStack() {
    vm.stack = GROW_ARRAY(Value, vm.stack, 0, STACK_BUFFER_SIZE);
    vm.stackTop = vm.stack;
    vm.stackLimit = vm.stack + STACK_BUFFER_SIZE;
}

static void updateStack() {
    uint64_t stackSize = vm.stackLimit - vm.stack;
    vm.stack = GROW_ARRAY(Value, vm.stack, stackSize, stackSize + STACK_BUFFER_SIZE);
    vm.stackTop = vm.stack + stackSize;
    vm.stackLimit = vm.stack + stackSize + STACK_BUFFER_SIZE;
}

void initVM() {
    resetStack();
}

void freeVM() {
    FREE_ARRAY(Value, vm.stack, vm.stackLimit - vm.stack);
}

void push(Value value) {
    if (vm.stackTop == vm.stackLimit) {
        updateStack();
    }
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run() {
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    #define BINARY_OP(op) \
        do {\
            double b = pop(); \
            double a = pop(); \
            push(a op b); \
        } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("        ");
    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
        printf("[ ");
        printValue(*slot);
        printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD:        BINARY_OP(+); break;
            case OP_MULTIPLY:   BINARY_OP(*); break;
            case OP_DIVIDE:     BINARY_OP(/); break;
            case OP_NEGATE:     push(-pop()); break;
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }
    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}

InterpretResult interpret(Chunk *chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}