#include <string.h>
#include <stdlib.h>
#include "ClassfileAttributes.h"

JRESULT ReadAttributes(FILE *file, ATTRIBUTE **attributes, u2 attributes_count, CONSTANT **constant_pool)
{
	JRESULT r = 0;

	// linear block of memory that will store attribute data
	void *attribute_block = NULL;
	size_t attribute_block_size = 0;

	// offset into the block per attribute
	size_t offsets[attributes_count];

	// pointer to access attribute and its offset into the block
	ATTRIBUTE *curr_attribute = NULL;
	size_t curr_attribute_offset = 0;

	// temp vars to read attribute header
	u2 curr_name_index = 0;
	u4 curr_length = 0;
	for (int i = 0; i < attributes_count; i++)
	{
		// read attribute header
		fread(&curr_name_index, 2, 1, file);
		curr_name_index = Big2(curr_name_index);

		fread(&curr_length, 4, 1, file);
		curr_length = Big4(curr_length);

		// resolve attribute name and check if supported
		const char *attribute_name =
				((struct CONSTANT_Utf8_info *)constant_pool[curr_name_index - 1])->runes;

		//printf("Found Attribute \"%s\" (%lu bytes)\n", attribute_name, curr_length);

		if (strcmp(attribute_name, "Code") == 0)
		{
			// extend block
			attribute_block = realloc(attribute_block, attribute_block_size += sizeof(struct ATTRIBUTE_Code));
			curr_attribute = attribute_block + curr_attribute_offset;
			offsets[i] = curr_attribute_offset;
			curr_attribute_offset += sizeof(struct ATTRIBUTE_Code);

			// populate attribute data
			curr_attribute->attribute_name_index = curr_name_index;
			curr_attribute->attribute_length = curr_length;
			r = ReadCodeAttribute(file, (struct ATTRIBUTE_Code *)curr_attribute, constant_pool);
		}
		else if (strcmp(attribute_name, "SourceFile") == 0)
		{
			// extend block
			attribute_block = realloc(attribute_block, attribute_block_size += sizeof(struct ATTRIBUTE_SourceFile));
			curr_attribute = attribute_block + curr_attribute_offset;
			offsets[i] = curr_attribute_offset;
			curr_attribute_offset += sizeof(struct ATTRIBUTE_SourceFile);

			// populate attribute data
			curr_attribute->attribute_name_index = curr_name_index;
			curr_attribute->attribute_length = curr_length;
			r = ReadSourceFileAttribute(file, (struct ATTRIBUTE_SourceFile *)curr_attribute);
		}
		else if (strcmp(attribute_name, "LineNumberTable") == 0)
		{
			// extend block
			attribute_block = realloc(attribute_block, attribute_block_size += sizeof(struct ATTRIBUTE_LineNumberTable));
			curr_attribute = attribute_block + curr_attribute_offset;
			offsets[i] = curr_attribute_offset;
			curr_attribute_offset += sizeof(struct ATTRIBUTE_LineNumberTable);

			// populate attribute data
			curr_attribute->attribute_name_index = curr_name_index;
			curr_attribute->attribute_length = curr_length;
			r = ReadLineNumberTableAttribute(file, (struct ATTRIBUTE_LineNumberTable *)curr_attribute);
		}
		else if (strcmp(attribute_name, "LocalVariableTable") == 0)
		{
			// extend block
			attribute_block = realloc(attribute_block, attribute_block_size += sizeof(struct ATTRIBUTE_LocalVariableTable));
			curr_attribute = attribute_block + curr_attribute_offset;
			offsets[i] = curr_attribute_offset;
			curr_attribute_offset += sizeof(struct ATTRIBUTE_LocalVariableTable);

			// populate attribute data
			curr_attribute->attribute_name_index = curr_name_index;
			curr_attribute->attribute_length = curr_length;
			r = ReadLocalVariableTableAttribute(file, (struct ATTRIBUTE_LocalVariableTable *)curr_attribute);
		}
		else
		{
			// extend block
			attribute_block = realloc(attribute_block, attribute_block_size += sizeof(ATTRIBUTE));
			curr_attribute = attribute_block + curr_attribute_offset;
			offsets[i] = curr_attribute_offset;
			curr_attribute_offset += sizeof(ATTRIBUTE);

			// populate attribute data
			curr_attribute->attribute_name_index = curr_name_index;
			curr_attribute->attribute_length = curr_length;
		}
	}

	for (int i = 0; i < attributes_count; i++)
	{
		attributes[i] = attribute_block + offsets[i];
	}

	return r;
}

void FreeAttributes(ATTRIBUTE **attributes, u2 attributes_count, CONSTANT **constant_pool)
{
	const char *attribute_name;
	u2 curr_name_index;
	for (int i = 0; i < attributes_count; i++)
	{
		curr_name_index = attributes[i]->attribute_name_index;
		attribute_name =
			((struct CONSTANT_Utf8_info *)constant_pool[curr_name_index - 1])->runes;

		if (strcmp(attribute_name, "Code") == 0)
		{
			struct ATTRIBUTE_Code *attr = (struct ATTRIBUTE_Code *)attributes[i];
			free(attr->code);
			free(attr->exception_table);
			FreeAttributes(attr->attributes, attr->attributes_count, constant_pool);
		}
		else if (strcmp(attribute_name, "LineNumberTable") == 0)
		{
			struct ATTRIBUTE_LineNumberTable *attr = (struct ATTRIBUTE_LineNumberTable *)attributes[i];
			free(attr->line_number_table);
		}
		else if (strcmp(attribute_name, "LocalVariableTable") == 0)
		{
			struct ATTRIBUTE_LocalVariableTable *attr = (struct ATTRIBUTE_LocalVariableTable *)attributes[i];
			free(attr->local_variable_table);
		}
	}
	free(attributes[0]);
	free(attributes);
}

JRESULT ReadConstantValueAttribute(FILE *file, struct ATTRIBUTE_ConstantValue *attribute, CONSTANT **constant_pool);

JRESULT ReadCodeAttribute(FILE *file, struct ATTRIBUTE_Code *attribute, CONSTANT **constant_pool)
{
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

	if (attribute->exception_table_length > 0)
	{
		attribute->exception_table = calloc(attribute->exception_table_length, sizeof(struct ExceptionTable));
		for (int i = 0; i < attribute->exception_table_length; i++)
		{
			struct ExceptionTable *table = &(attribute->exception_table[i]);

			fread(table, 2, 4, file);
			table->start_pc = Big2(table->start_pc);
			table->end_pc = Big2(table->end_pc);
			table->handler_pc = Big2(table->handler_pc);
			table->catch_type = Big2(table->catch_type);
		}
	}
	else
	{
		attribute->exception_table = NULL;
	}

	fread(&attribute->attributes_count, 2, 1, file);
	attribute->attributes_count = Big2(attribute->attributes_count);
	//printf("\tAttribute Count: %u\n", attribute->attributes_count);

	if (attribute->attributes_count > 0)
	{
		attribute->attributes = calloc(attribute->attributes_count, sizeof(ATTRIBUTE *));
		ReadAttributes(file, attribute->attributes, attribute->attributes_count, constant_pool);
	}
	else
	{
		attribute->attributes = NULL;
	}

	return r;
}

JRESULT ReadSourceFileAttribute(FILE *file, struct ATTRIBUTE_SourceFile *attribute)
{
	JRESULT r = 0;

	fread(&attribute->sourcefile_index, 2, 1, file);
	attribute->sourcefile_index = Big2(attribute->sourcefile_index);

	return r;
}

JRESULT ReadLineNumberTableAttribute(FILE* file, struct ATTRIBUTE_LineNumberTable *attribute)
{
	JRESULT r = 0;

	fread(&attribute->line_number_table_length, 2, 1, file);
	attribute->line_number_table_length = Big2(attribute->line_number_table_length);

	if (attribute->line_number_table_length > 0)
	{
		attribute->line_number_table = calloc(attribute->line_number_table_length, sizeof(struct LineNumberEntry));
		for (int i = 0; i < attribute->line_number_table_length; i++)
		{
			struct LineNumberEntry *table = &(attribute->line_number_table[i]);
			fread(table, 2, 2, file);
			table->start_pc = Big2(table->start_pc);
			table->line_number = Big2(table->line_number);
		}
	}
	else
	{
		attribute->line_number_table = NULL;
	}

	return r;
}

JRESULT ReadLocalVariableTableAttribute(FILE* file, struct ATTRIBUTE_LocalVariableTable *attribute)
{
	JRESULT r = 0;

	fread(&attribute->local_variable_table_length, 2, 1, file);
	attribute->local_variable_table_length = Big2(attribute->local_variable_table_length);

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
	else
	{
		attribute->local_variable_table = NULL;
	}

	return r;
}

JRESULT ReadDeprecatedAttribute(FILE *file, struct ATTRIBUTE_Deprecated *attribute, CONSTANT **constant_pool);

JRESULT ReadBootstrapMethodsAttribute(FILE *file, struct ATTRIBUTE_BootstrapMethods *attribute, CONSTANT **constant_pool);