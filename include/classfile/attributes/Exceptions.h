#ifndef CLASSFILE_ATTRIBUTES_EXCEPTIONS_H_
#define CLASSFILE_ATTRIBUTES_EXCEPTIONS_H_

#include "../Attributes.h"

/*
 * A structure for the Exceptions Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.5
 *
 * number_of_exceptions
 *   The number of elements in the table.
 *
 * exception_index_table
 *   An array of Constant Pool indices to CONSTANT_Class structures
 *   describing the exception types thrown by the method.
 */
typedef struct {
	u2 attribute_name_index;
	u2 number_of_exceptions;
	u2 *exception_index_table;
} ATTRIBUTE_Exceptions;

JRESULT ReadAttribute_Exceptions(FILE *file, ATTRIBUTE_Exceptions *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_Exceptions(ATTRIBUTE_Exceptions *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_EXCEPTIONS_H_ */
