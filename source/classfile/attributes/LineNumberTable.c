#include "classfile/attributes/LineNumberTable.h"
#include <stdlib.h>

JRESULT ReadLineNumberTableAttribute(FILE *file, ATTRIBUTE_LineNumberTable *attribute, u4 attribute_length, CONSTANT **constant_pool) {
	JRESULT r = 0;

	fread(&attribute->line_number_table_length, 2, 1, file);
	attribute->line_number_table_length = Big2(attribute->line_number_table_length);

	attribute->line_number_table = NULL;
	if (attribute->line_number_table_length > 0) {
		attribute->line_number_table = calloc(attribute->line_number_table_length, sizeof(struct LineNumberEntry));
		for (int i = 0; i < attribute->line_number_table_length; i++) {
			struct LineNumberEntry *table = &attribute->line_number_table[i];
			fread(table, 2, 2, file);
			table->start_pc = Big2(table->start_pc);
			table->line_number = Big2(table->line_number);
		}
	}

	return r;
}

void FreeLineNumberTableAttribute(ATTRIBUTE_LineNumberTable *attribute, CONSTANT **constant_pool) {
	free(attribute->line_number_table);
}
