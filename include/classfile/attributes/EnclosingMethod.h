#ifndef CLASSFILE_ATTRIBUTES_ENCLOSINGMETHOD_H_
#define CLASSFILE_ATTRIBUTES_ENCLOSINGMETHOD_H_

#include "../Attributes.h"

/*
 * A structure for the Enclosing Method Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.7
 *
 * class_index
 *   A Constant Pool index to a CONSTANT_Class structure representing
 *   the innermost class that encloses the declaration of the current class.
 *
 * method_index
 *   A Constant Pool index to a CONSTANT_NameAndType structure
 *   representing the method referenced by the class mentioned above.
 */
typedef struct {
	u2 attribute_name_index;
	u2 class_index;
	u2 method_index;
} ATTRIBUTE_EnclosingMethod;

JRESULT ReadAttribute_EnclosingMethod(FILE *file, ATTRIBUTE_EnclosingMethod *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_EnclosingMethod(ATTRIBUTE_EnclosingMethod *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_ENCLOSINGMETHOD_H_ */
