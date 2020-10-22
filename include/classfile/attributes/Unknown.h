#ifndef CLASSFILE_ATTRIBUTES_UNKNOWN_H_
#define CLASSFILE_ATTRIBUTES_UNKNOWN_H_

#include "Attributes.h"

/*
 * A structure for Unknown Attributes
 *
 * attribute_length
 *   The length, in bytes, of the attribute in the classfile.
 */
typedef struct {
	u2 attribute_name_index;
	u2 attribute_length;
} ATTRIBUTE_Unknown;

JRESULT ReadAttribute_Unknown(FILE *file, ATTRIBUTE_Unknown *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_Unknown(ATTRIBUTE_Unknown *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_UNKNOWN_H_ */
