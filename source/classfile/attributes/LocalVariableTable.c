#include "classfile/attributes/LocalVariableTable.h"
#include <stdlib.h>

JRESULT ReadAttribute_LocalVariableTable(FILE *file, ATTRIBUTE_LocalVariableTable *attribute, u4 attribute_length, CONSTANT **constant_pool)
{
	JRESULT r = 0;

	fread(&attribute->local_variable_table_length, 2, 1, file);
	attribute->local_variable_table_length = Big2(attribute->local_variable_table_length);

	attribute->local_variable_table = NULL;
	if (attribute->local_variable_table_length > 0)
	{
		attribute->local_variable_table = calloc(attribute->local_variable_table_length, sizeof(struct LocalVariableEntry));
		for (int i = 0; i < attribute->local_variable_table_length; i++)
		{
			struct LocalVariableEntry *table = &(attribute->local_variable_table[i]);
			fread(table, 2, 5, file);
			table->start_pc = Big2(table->start_pc);
			table->length = Big2(table->length);
			table->name_index = Big2(table->name_index);
			table->descriptor_index = Big2(table->descriptor_index);
			table->index = Big2(table->index);
		}
	}

	return r;
}

void FreeAttribute_LocalVariableTable(ATTRIBUTE_LocalVariableTable *attribute, CONSTANT **constant_pool)
{
	free(attribute->local_variable_table);
}
