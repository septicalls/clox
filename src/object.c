#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type *)allocateObject(sizeof(type), objectType)

#define ALLOCATE_STR(length) \
    (ObjString *)allocateObject(offsetof(ObjString, chars) + length + 1, OBJ_STRING)

static Obj* allocateObject(size_t size, ObjType type) {
    Obj *object = (Obj *)reallocate(NULL, 0, size);
    object->type = type;

    object->next = vm.objects;
    vm.objects = object;
    return object;
}

ObjString *takeString(char *chars, int length) {
    ObjString *string = ALLOCATE_STR(length);
    string->length = length;
    string->owned = true;
    string->ownedString = chars;
    return string;
}

ObjString *makeString(const char *chars, int length) {
    ObjString *string = ALLOCATE_STR(length);
    string->length = length;
    string->owned = false;
    string->ownedString = NULL;
    memcpy(string->chars, chars, length);
    string->chars[length] = '\0';
    return string;
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            printf("%s", AS_CSTRING(value));
            break;
    }
}

char *getString(ObjString *string) {
    if (string->owned) {
        return string->ownedString;
    } else {
        return string->chars;
    }
}