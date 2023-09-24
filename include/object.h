#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value)         (AS_OBJ(value)->type)

#define IS_STRING(value)        isObjType(value, OBJ_STRING)

#define AS_STRING(value)        ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value) \
    (char *)getString((ObjString *)AS_OBJ(value))

typedef enum {
    OBJ_STRING
} ObjType;

struct Obj {
    ObjType type;
    struct Obj *next;
};

struct ObjString {
    Obj obj;
    int length;
    bool owned;
    char *ownedString;
    char chars[];
};

ObjString *takeString(char *chars, int length);
ObjString *makeString(const char *chars, int length);
void printObject(Value value);
char *getString(ObjString *string);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif