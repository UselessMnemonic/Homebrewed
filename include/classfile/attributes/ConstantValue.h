#ifndef CLASSFILE_ATTRIBUTES_CONSTANTVALUE_H_
#define CLASSFILE_ATTRIBUTES_CONSTANTVALUE_H_

#include "../Attributes.h"

/*
 * A structure for the Constant Value attribute.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.2
 *
 * constantvalue_index
 *   The constant_pool entry at that index gives the value represented
 *   by this attribute.
 */
typedef struct {
	u2 attribute_name_index;
	u2 constantvalue_index;
} ATTRIBUTE_ConstantValue;

JRESULT ReadConstantValueAttribute(FILE *file, ATTRIBUTE_ConstantValue *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeConstantValueAttribute(ATTRIBUTE_ConstantValue *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_CONSTANTVALUE_H_ */