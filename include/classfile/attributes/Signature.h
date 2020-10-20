#ifndef CLASSFILE_ATTRIBUTES_SIGNATURE_H_
#define CLASSFILE_ATTRIBUTES_SIGNATURE_H_

#include "../Attributes.h"

/*
 * A structure for the Signature Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.9
 *
 * signature_index
 *   A Constant Pool index to a CONSTANT_Utf8_info structure
 *   representing the class, method, or field attribute.
 */
typedef struct {
	u2 attribute_name_index;
	u2 signature_index;
} ATTRIBUTE_Signature;

JRESULT ReadSignatureAttribute(FILE *file, ATTRIBUTE_Signature *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeSignatureAttribute(ATTRIBUTE_Signature *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_SIGNATURE_H_ */
