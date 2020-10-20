#ifndef CLASSFILE_ATTRIBUTES_LOCALVARIABLETABLE_H_
#define CLASSFILE_ATTRIBUTES_LOCALVARIABLETABLE_H_

#include "../Attributes.h"

/*
 * A structure describing the value of a local variable during
 * method invocation.
 *
 * start_pc, length
 *   Together, these define the range in the bytecode array
 *   during which the local variable has a value. Specifically,
 *   the range is [start_pc, start_pc + length)
 *
 * name_index
 *   A Constant Pool index to a CONSTANT_Utf8 containing
 *   the name of the local variable.
 *
 * descriptor_index
 *   A Constant Pool index to a CONSTANT_Utf8 containing
 *   the field descriptor of the local variable.
 *
 * index
 *  An index into the local variable array of the current frame
 *  for the local variable. For variables of type double and long,
 *  the variable spans [index, index + 1]
 */
struct LocalVariableEntry {
	u2 start_pc;
	u2 length;
	u2 name_index;
	u2 descriptor_index;
	u2 index;
};

/*
 * A structure for the Local Variable Table Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.13
 *
 * local_variable_table_length
 *   The number of elements in the local variable table.
 *
 * local_variable_table
 *   An array of local variable entries.
 */
typedef struct {
	u2 attribute_name_index;
	u2 local_variable_table_length;
	struct LocalVariableEntry *local_variable_table;
} ATTRIBUTE_LocalVariableTable;

JRESULT ReadLocalVariableTableAttribute(FILE *file, ATTRIBUTE_LocalVariableTable *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeLocalVariableTableAttribute(ATTRIBUTE_LocalVariableTable *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_LOCALVARIABLETABLE_H_ */
