#include "classfile/Attributes.h"
#include "classfile/attributes/Code.h"
#include "classfile/attributes/SourceFile.h"
#include "classfile/attributes/LineNumberTable.h"
#include "classfile/attributes/LocalVariableTable.h"
#include "classfile/attributes/Unknown.h"
#include <string.h>
#include <stdlib.h>

JRESULT ReadAttributes(FILE *file, u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool) {
	JRESULT r = 0;

	// linear block of memory that will store attribute data
	void *attribute_block = NULL;
	size_t attribute_block_size = 0;

	// offset into the block per attribute
	size_t attribute_offsets[attributes_count];

	// pointer to access attribute
	ATTRIBUTE *curr_attribute = NULL;

	// temp vars to track and read attribute header
	u2 curr_attribute_name_index = 0;
	u4 curr_attribute_length = 0;
	size_t delta = 0;
	ReadAttributeFunction readAttribute;

	for (int i = 0; i < attributes_count; i++) {
		// read attribute header
		fread(&curr_attribute_name_index, 2, 1, file);
		curr_attribute_name_index = Big2(curr_attribute_name_index);

		fread(&curr_attribute_length, 4, 1, file);
		curr_attribute_length = Big4(curr_attribute_length);

		// resolve attribute name and check if supported
		// TODO replace with Modified-UTF8-safe code
		const char *attribute_name =
				(const char *)((struct CONSTANT_Utf8_info*) constant_pool[curr_attribute_name_index - 1])->runes;

		//printf("Found Attribute \"%s\" (%lu bytes)\n", attribute_name, curr_length);

		// find which attribute is being read
		if (strcmp(attribute_name, "Code") == 0) {
			delta = sizeof(ATTRIBUTE_Code);
			readAttribute = (ReadAttributeFunction)ReadCodeAttribute;
		}
		else if (strcmp(attribute_name, "SourceFile") == 0) {
			delta = sizeof(ATTRIBUTE_SourceFile);
			readAttribute = (ReadAttributeFunction)ReadSourceFileAttribute;
		}
		else if (strcmp(attribute_name, "LineNumberTable") == 0) {
			delta = sizeof(ATTRIBUTE_LineNumberTable);
			readAttribute = (ReadAttributeFunction)ReadLineNumberTableAttribute;
		}
		else if (strcmp(attribute_name, "LocalVariableTable") == 0) {
			delta = sizeof(ATTRIBUTE_LocalVariableTable);
			readAttribute = (ReadAttributeFunction)ReadLocalVariableTableAttribute;
		}
		else {
			delta = sizeof(ATTRIBUTE_Unknown);
			readAttribute = (ReadAttributeFunction)ReadUnknownAttribute;
		}

		// note the offset into the block and extend the block
		attribute_offsets[i] = attribute_block_size;
		attribute_block = realloc(attribute_block, attribute_block_size += delta);
		curr_attribute = attribute_block + attribute_offsets[i];

		// populate attribute data
		curr_attribute->attribute_name_index = curr_attribute_name_index;
		r = readAttribute(file, curr_attribute, curr_attribute_length, constant_pool);
	}

	for (int i = 0; i < attributes_count; i++) {
		attributes[i] = attribute_block + attribute_offsets[i];
	}

	return r;
}

// TODO move code into functions
void FreeAttributes(u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool) {
	const char *attribute_name;
	u2 curr_name_index;
	for (int i = 0; i < attributes_count; i++) {
		curr_name_index = attributes[i]->attribute_name_index;
		attribute_name =
				(const char *)((struct CONSTANT_Utf8_info*) constant_pool[curr_name_index - 1])->runes;

		if (strcmp(attribute_name, "Code") == 0) {
			ATTRIBUTE_Code *attr = (ATTRIBUTE_Code*) attributes[i];
			free(attr->code);
			free(attr->exception_table);
			FreeAttributes(attr->attributes_count, attr->attributes, constant_pool);
		}
		else if (strcmp(attribute_name, "LineNumberTable") == 0) {
			ATTRIBUTE_LineNumberTable *attr = (ATTRIBUTE_LineNumberTable*) attributes[i];
			free(attr->line_number_table);
		}
		else if (strcmp(attribute_name, "LocalVariableTable") == 0) {
			ATTRIBUTE_LocalVariableTable *attr = (ATTRIBUTE_LocalVariableTable*) attributes[i];
			free(attr->local_variable_table);
		}
	}
	free(attributes[0]);
	free(attributes);
}
