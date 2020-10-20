#ifndef CONSTANTPOOL_H_
#define CONSTANTPOOL_H_

#include "WideTypes.h"
#include <stdio.h>

#define CONSTANT_Class_info			7
#define CONSTANT_InterfaceMethodref_info	11
#define CONSTANT_Fieldref_info		9
#define CONSTANT_Methodref_info		10

#define CONSTANT_String_info		8
#define CONSTANT_Integer_info		3
#define CONSTANT_Float_info			4
#define CONSTANT_Long_info			5
#define CONSTANT_Double_info		6
#define CONSTANT_NameAndType_info	12
#define CONSTANT_Utf8_info			1

#define CONSTANT_MethodHandle_info	15
#define CONSTANT_MethodType_info	16
#define CONSTANT_Dynamic_info		17
#define CONSTANT_InvokeDynamic_info	18
#define CONSTANT_Module_info		19
#define CONSTANT_Package_info		20

/*
 * The parent structure for all constants. This acts like a header
 * preceding the constant's data.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.4
 *
 * tag
 *   A numeric tag identifying the type of constant.
 *
 * info
 *   Names the data following the header, which is
 *   implementation dependent.
 */
typedef struct {
	u1 tag;
	u1 info[];
} CONSTANT;


typedef struct {
	u1 tag;
	u2 name_index;
} CONSTANT_Class;

typedef struct {
	u1 tag;
	u2 string_index;
} CONSTANT_String;

typedef struct {
	u1 tag;
	u2 descriptor_index;
} CONSTANT_MethodType;

typedef struct {
	u1 tag;
	u2 name_index;
} CONSTANT_Module;

typedef struct {
	u1 tag;
	u2 name_index;
} CONSTANT_Package;

typedef struct {
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
} CONSTANT_Fieldref;

typedef struct {
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
} CONSTANT_Methodref;

typedef struct {
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
} CONSTANT_InterfaceMethodref;

typedef struct {
	u1 tag;
	u2 name_index;
	u2 descriptor_index;
} CONSTANT_NameAndType;

typedef struct {
	u1 tag;
	u2 bootstrap_method_attr_index;
	u2 name_and_type_index;
} CONSTANT_Dynamic;

typedef struct {
	u1 tag;
	u2 bootstrap_method_attr_index;
	u2 name_and_type_index;
} CONSTANT_InvokeDynamic;

typedef struct {
	u1 tag;
	u4 value;
} CONSTANT_Integer;

typedef struct {
	u1 tag;
	u4 value;
} CONSTANT_Float;

typedef struct {
	u1 tag;
	u4 low;
	u4 high;
} CONSTANT_Long;

typedef struct {
	u1 tag;
	u4 low;
	u4 high;
} CONSTANT_Double;

typedef struct {
	u1 tag;
	u2 length;
	u1 runes[];
} CONSTANT_Utf8;

typedef struct {
	u1 tag;
	u1 reference_kind;
	u2 reference_index;
} CONSTANT_MethodHandle;

/*
 * This parses the constant pool from a class file into a
 * pre-allocated vector.
 *
 * file
 *   The file providing a constant stream. The current location of
 *   the file buffer must be at the start of the stream.
 *   Must be non-NULL.
 *
 * constant_count
 *   The number of constant to parse from the file.
 *
 * constant_pool
 *   The vector of constants to be populated. Must be at least as
 *   long as constant_count elements. Must be non-NULL.
 */
JRESULT ReadConstantPool(FILE *file, u2 constant_pool_count, CONSTANT **constant_pool);

/*
 * This releases all memory allocated by ReadConstantPool.
 * Note that the vector itself is not deallocated.
 *
 * constant_pool
 *   The vector populated by ReadConstantPool. Must be non-NULL.
 */
void FreeConstantPool(CONSTANT **constant_pool);

#endif /* CONSTANTPOOL_H_ */
