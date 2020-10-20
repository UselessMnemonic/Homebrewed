#ifndef CLASSFILE_ATTRIBUTES_NESTHOST_H_
#define CLASSFILE_ATTRIBUTES_NESTHOST_H_

#include "../Attributes.h"

/*
 * A structure for the Nest Host Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.28
 *
 * host_class_index
 *   A Constant Pool index to a CONSTANT_Class_info structure representing
 *   a class that hosts the current class.
 */
typedef struct {
	u2 attribute_name_index;
	u2 host_class_index;
} ATTRIBUTE_NestHost;

JRESULT ReadNestHostAttribute(FILE *file, ATTRIBUTE_NestHost *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeNestHostAttribute(ATTRIBUTE_NestHost *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_NESTHOST_H_ */
