#ifndef CLASSFILE_ATTRIBUTES_STACKMAPTABLE_H_
#define CLASSFILE_ATTRIBUTES_STACKMAPTABLE_H_

#include "../Attributes.h"

/*
 * A structure containing verification information for the elements
 * in the stack.
 *
 * tag
 *   The type of the element.
 *
 * offset_or_cpool_index
 *   For Object-types, this is the index into the constant pool
 *   for the object's class.
 *   For Uninitialized types, this is the offset into the code
 *   array for the new instruction that created the object.
 */
struct VerificationInfo {
	u1 tag;
	u2 offset_or_cp_index;
};

/*
 * Parent structure for Stack Map Frames
 */
struct StackMapFrame {
	u1 frame_type;
	u1 data[];
};

struct StackMapFrame_same {
	u1 frame_type; // 0 - 63
};

struct StackMapFrame_same_locals {
	u1 frame_type; // 64 - 127
	struct VerificationInfo stack;
};

struct StackMapFrame_same_locals_ext {
	u1 frame_type; // 247
	u2 offset_delta;
	struct VerificationInfo stack;
};

struct StackMapFrame_chop {
	u1 frame_type; // 248 - 250
	u2 offset_delta;
};

struct StackMapFrame_same_ext {
	u1 frame_type; // 251
	u2 offset_delta;
};

struct StackMapFrame_append {
	u1 frame_type; // 252 - 254
	u2 offset_delta;
	struct VerificationInfo *locals; // [frame_type - 251]
};

struct StackMapFrame_full {
	u1 frame_type; // 255
	u2 offset_delta;
	u2 number_of_locals;
	struct VerificationInfo *locals;
	u2 number_of_stack_items;
	struct VerificationInfo *stack;
};

/*
 * A structure for the Stack Map table attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.4
 *
 * number_of_entries
 *   The number of elements in the entries vector.
 *
 * entries
 *   A vector of stack frame structures.
 */
typedef struct {
	u2 attribute_name_index;
	u2 number_of_entries;
	struct StackMapFrame **entries;
} ATTRIBUTE_StackMapTable;

JRESULT ReadAttribute_StackMapTable(FILE *file, ATTRIBUTE_StackMapTable *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_StackMapTable(ATTRIBUTE_StackMapTable *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_STACKMAPTABLE_H_ */
