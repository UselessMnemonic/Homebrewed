#ifndef CLASSFILE_ATTRIBUTES_DEPRECATED_H_
#define CLASSFILE_ATTRIBUTES_DEPRECATED_H_

#include "../Attributes.h"

/*
 * A structure for the Deprecated Attribute.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.15
 */
typedef struct {
	u2 attribute_name_index;
} ATTRIBUTE_Deprecated;

JRESULT ReadDeprecatedAttribute(FILE *file, ATTRIBUTE_Deprecated *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeDeprecatedAttribute(ATTRIBUTE_Deprecated *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_DEPRECATED_H_ */
