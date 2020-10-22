#ifndef CLASSFILE_ATTRIBUTES_CONSTANTVALUE_H_
#define CLASSFILE_ATTRIBUTES_CONSTANTVALUE_H_

#include "Attributes.h"

/*
 * A structure for the Constant Value attribute.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.2
 *
 * constantvalue_index
 *   A Constant Pool index to the constant's value.
 */
typedef struct {
	u2 attribute_name_index;
	u2 constantvalue_index;
} ATTRIBUTE_ConstantValue;

JRESULT ReadAttribute_ConstantValue(FILE *file, ATTRIBUTE_ConstantValue *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_ConstantValue(ATTRIBUTE_ConstantValue *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_CONSTANTVALUE_H_ */
