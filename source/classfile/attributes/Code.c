#include "classfile/attributes/Code.h"
#include <stdlib.h>

JRESULT ReadCodeAttribute(FILE *file, ATTRIBUTE_Code *attribute, u4 attribute_length, CONSTANT **constant_pool) {
	JRESULT r = 0;

	fread(&attribute->max_stack, 2, 1, file);
	attribute->max_stack = Big2(attribute->max_stack);
	//printf("\tMax Stack: %u\n", attribute->max_stack);

	fread(&attribute->max_locals, 2, 1, file);
	attribute->max_locals = Big2(attribute->max_locals);
	//printf("\tMax Locals: %u\n", attribute->max_locals);

	fread(&attribute->code_length, 4, 1, file);
	attribute->code_length = Big4(attribute->code_length);
	//printf("\tCode Length: %lu\n", attribute->code_length);

	attribute->code = calloc(attribute->code_length, 1);
	fread(attribute->code, 1, attribute->code_length, file);

	fread(&attribute->exception_table_length, 2, 1, file);
	attribute->exception_table_length = Big2(attribute->exception_table_length);
	//printf("\tException Table Length: %u\n", attribute->exception_table_length);

	if (attribute->exception_table_length > 0) {
		attribute->exception_table = calloc(attribute->exception_table_length, sizeof(struct ExceptionEntry));
		for (int i = 0; i < attribute->exception_table_length; i++) {
			struct ExceptionEntry *table = &(attribute->exception_table[i]);

			fread(table, 2, 4, file);
			table->start_pc = Big2(table->start_pc);
			table->end_pc = Big2(table->end_pc);
			table->handler_pc = Big2(table->handler_pc);
			table->catch_type = Big2(table->catch_type);
		}
	}
	else {
		attribute->exception_table = NULL;
	}

	fread(&attribute->attributes_count, 2, 1, file);
	attribute->attributes_count = Big2(attribute->attributes_count);
	//printf("\tAttribute Count: %u\n", attribute->attributes_count);

	if (attribute->attributes_count > 0) {
		attribute->attributes = calloc(attribute->attributes_count, sizeof(ATTRIBUTE*));
		ReadAttributes(file, attribute->attributes_count, attribute->attributes, constant_pool);
	}
	else {
		attribute->attributes = NULL;
	}

	return r;
}

void FreeCodeAttribute(ATTRIBUTE_Code *attribute, CONSTANT **constant_pool);
