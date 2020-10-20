#ifndef CLASSFILE_ATTRIBUTES_CODE_H_
#define CLASSFILE_ATTRIBUTES_CODE_H_

#include "../Attributes.h"

/*
 * A structure describing an exception handler.
 *
 * start_pc, end_pc
 *   Describes the range in the code array that this
 *   handler responds to. Specifically, the range is [start_pc, end_pc)
 *
 * handler_pc
 *   The start of the exception handler in the code array.
 *
 * catch_type
 *   When non-zero, this is an index to a CONSTANT_Class_info structure
 *   in the Constant Pool. The exception handler will take over iff
 *   the handler is Throwable.
 *   When zero, this handler responds to any exceptions thrown in its
 *   range.
 *
 */
struct ExceptionEntry {
	u2 start_pc;
	u2 end_pc;
	u2 handler_pc;
	u2 catch_type;
};

/*
 * A structure for the Code attribute.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.3
 *
 * max_stack
 *   The maximum depth of the stack at any point during this method invocation.
 *
 * max_locals
 *   The number of local variables allocated for this method invocation.
 *
 * code_length
 *   The length of the code array, in bytes.
 *
 * code
 *   An array of bytecode instructions.
 *
 * exception_table_length
 *   The number of elements in the exception table.
 *
 * exception_table
 *   An array of exception handlers.
 *
 * attributes_count
 *   The number of elements in the attributes vector.
 *
 * attributes
 *   A vector of attributes specific to this Code attribute.
 */
typedef struct {
	u2 attribute_name_index;
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	bytecode *code;
	u2 exception_table_length;
	struct ExceptionEntry *exception_table;
	u2 attributes_count;
	ATTRIBUTE **attributes;
} ATTRIBUTE_Code;

JRESULT ReadCodeAttribute(FILE *file, ATTRIBUTE_Code *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeCodeAttribute(ATTRIBUTE_Code *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_CODE_H_ */
