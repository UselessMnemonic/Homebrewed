#ifndef CLASSFILE_ATTRIBUTES_SYNTHETIC_H_
#define CLASSFILE_ATTRIBUTES_SYNTHETIC_H_

#include "../Attributes.h"

/*
 * A structure denoting a synthetic element.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.8
 */
typedef struct {
	u2 attribute_name_index;
} ATTRIBUTE_Synthetic;

JRESULT ReadAttribute_Synthetic(FILE *file, ATTRIBUTE_Synthetic *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_Synthetic(ATTRIBUTE_Synthetic *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_SYNTHETIC_H_ */
