#ifndef CLASSFILE_ATTRIBUTES_LINENUMBERTABLE_H_
#define CLASSFILE_ATTRIBUTES_LINENUMBERTABLE_H_

#include "../Attributes.h"

/*
 * A structure mapping line numbers to bytecode.
 *
 * start_pc
 *   An index into the code array at which the source begins.
 *
 * line_number
 *   The corresponding line number in the original source file.
 */
struct LineNumberEntry {
	u2 start_pc;
	u2 line_number;
};

/*
 * A structure for the Line Number Table Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.12
 *
 * line_number_table_length
 *   The number of elements in the line number table.
 *
 * line_number_table
 *   An array of line number entries.
 */
typedef struct {
	u2 attribute_name_index;
	u2 line_number_table_length;
	struct LineNumberEntry *line_number_table;
} ATTRIBUTE_LineNumberTable;

JRESULT ReadLineNumberTableAttribute(FILE *file, ATTRIBUTE_LineNumberTable *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeLineNumberTableAttribute(ATTRIBUTE_LineNumberTable *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_LINENUMBERTABLE_H_ */
