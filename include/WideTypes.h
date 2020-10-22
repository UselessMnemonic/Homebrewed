#ifndef WIDETYPES_H_
#define WIDETYPES_H_

#include <stdint.h>

#define Big2(x) ((u2)(((x>>8) & 0x00ff) | ((x<<8) & 0xff00)))
#define Big4(x) ((u4)(((x>>24) & 0x000000ff) | ((x>>8) & 0x0000ff00) | ((x<<8) & 0x00ff0000) | ((x<<24) & 0xff000000)))

typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;

typedef int8_t  s1;
typedef int16_t s2;
typedef int32_t s4;

typedef int8_t JBYTE;
typedef int16_t JSHORT;
typedef int32_t JINT;
typedef int64_t JLONG;
typedef float JFLOAT;
typedef double JDOUBLE;
typedef uint8_t JBOOL;
typedef uint16_t JCHAR;

typedef u1 bytecode;

#define JRESULT_OK (0)
#define JRESULT_ALLOCATION_FAILED (1)
#define JRESULT_BAD_ATTRIBUTE (2)
#define JRESULT_BAD_MAGIC (3)
#define JRESULT_BAD_CONSTANT (4)
#define JRESULT_UNKNOWN_CONSTANT (5)
#define JRESULT_BAD_FIELD_METHOD (6)
#define JRESULT_BAD_CLASSFILE (7)
#define JRESULT_EXPECTED_EOF (8)
#define JRESULT_UNKNOWN_STACK_FRAME (9)
#define JRESULT_FILE_ERROR (10)

typedef u1 JRESULT;

#endif /* WIDETYPES_H_ */
