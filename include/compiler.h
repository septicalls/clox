#ifndef clox_compiler_h
#define clox_compiler_h

#include "vm.h"
#include "object.h"

ObjFunction *compile(const char *source);

#endif