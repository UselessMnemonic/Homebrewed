#ifndef CONSTANTPOOL_H_
#define CONSTANTPOOL_H_

#include "WideTypes.h"
#include <stdio.h>

#define CONSTANT_Class				7
#define CONSTANT_Fieldref			9
#define CONSTANT_Methodref			10
#define CONSTANT_InterfaceMethodref	11

#define CONSTANT_String			8
#define CONSTANT_Integer		3
#define CONSTANT_Float			4
#define CONSTANT_Long			5
#define CONSTANT_Double			6
#define CONSTANT_NameAndType	12
#define CONSTANT_Utf8			1

#define CONSTANT_MethodHandle	15
#define CONSTANT_MethodType		16
#define CONSTANT_Dynamic		17
#define CONSTANT_InvokeDynamic	18
#define CONSTANT_Module			19
#define CONSTANT_Package		20

typedef struct
{
	u1 tag;
	u1 info[];
} CONSTANT;

struct CONSTANT_Class_info
{
	u1 tag;
	u2 name_index;
};

struct CONSTANT_String_info
{
	u1 tag;
	u2 string_index;
};

struct CONSTANT_MethodType_info
{
	u1 tag;
	u2 descriptor_index;
};

struct CONSTANT_Module_info
{
	u1 tag;
	u2 name_index;
};

struct CONSTANT_Package_info
{
	u1 tag;
	u2 name_index;
};

struct CONSTANT_Fieldref_info
{
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
};

struct CONSTANT_Methodref_info
{
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info
{
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
};

struct CONSTANT_NameAndType_info
{
	u1 tag;
	u2 name_index;
	u2 descriptor_index;
};

struct CONSTANT_Dynamic_info
{
	u1 tag;
	u2 bootstrap_method_attr_index;
	u2 name_and_type_index;
};

struct CONSTANT_InvokeDynamic_info
{
	u1 tag;
	u2 bootstrap_method_attr_index;
	u2 name_and_type_index;
};

struct CONSTANT_Integer_info
{
	u1 tag;
	u4 value;
};

struct CONSTANT_Float_info
{
	u1 tag;
	u4 value;
};

struct CONSTANT_Long_info
{
	u1 tag;
	u4 low;
	u4 high;
};

struct CONSTANT_Double_info
{
	u1 tag;
	u4 low;
	u4 high;
};

struct CONSTANT_Utf8_info
{
	u1 tag;
	u2 length;
	u1 runes[];
};

struct CONSTANT_MethodHandle_info
{
	u1 tag;
	u1 reference_kind;
	u2 reference_index;
};

JRESULT ReadConstantPool(FILE *file, CONSTANT **constant_pool, u2 num_items);
void FreeConstantPool(CONSTANT **constant_pool);

#endif /* CONSTANTPOOL_H_ */
