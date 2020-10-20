#ifndef CLASSFILE_ATTRIBUTES_NESTMEMBERS_H_
#define CLASSFILE_ATTRIBUTES_NESTMEMBERS_H_

#include "../Attributes.h"

/*
 * A structure for the Nest Members Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.29
 *
 * number_of_classes
 *   The number of elements in the classes array.
 *
 * classes
 *   An array of Constant Pool indices to CONSTANT_Class structures
 *   representing a class which is hosted by this current class.
 */
typedef struct {
	u2 attribute_name_index;
	u2 number_of_classes;
	u2 *classes;
} ATTRIBUTE_NestMembers;

JRESULT ReadNestMembersAttribute(FILE *file, ATTRIBUTE_NestMembers *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeNestMembersAttribute(ATTRIBUTE_NestMembers *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_NESTMEMBERS_H_ */
