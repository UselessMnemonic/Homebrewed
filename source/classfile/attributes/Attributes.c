#include "classfile/attributes/Attributes.h"

#include "classfile/attributes/ConstantValue.h"
#include "classfile/attributes/Code.h"
#include "classfile/attributes/StackMapTable.h"
#include "classfile/attributes/BootstrapMethods.h"
#include "classfile/attributes/NestHost.h"
#include "classfile/attributes/NestMembers.h"

//#include "classfile/attributes/SourceFile.h"
//#include "classfile/attributes/LineNumberTable.h"
//#include "classfile/attributes/LocalVariableTable.h"
#include "classfile/attributes/Unknown.h"
#include <string.h>
#include <stdlib.h>

JRESULT ATTRIBUTE_ReadFromFile(FILE *file, u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool)
{
	JRESULT r = 0;

	// pointer to access attribute
	ATTRIBUTE *curr_attribute = NULL;

	// temp vars to track and read attribute header
	u2 curr_attribute_name_index = 0;
	u4 curr_attribute_length = 0;
	size_t delta = 0;
	ReadAttributeFunction readAttribute;

	for (int i = 0; i < attributes_count; i++)
	{
		// read attribute header
		fread(&curr_attribute_name_index, 2, 1, file);
		curr_attribute_name_index = Big2(curr_attribute_name_index);

		fread(&curr_attribute_length, 4, 1, file);
		curr_attribute_length = Big4(curr_attribute_length);

		// resolve attribute name and check if supported
		// TODO replace with Modified-UTF8-safe code
		const char *attribute_name =
				(const char *)((CONSTANT_Utf8*) constant_pool[curr_attribute_name_index - 1])->runes;

		//printf("Found Attribute \"%s\" (%lu bytes)\n", attribute_name, curr_length);

		// find which attribute is being read
		 if (strcmp(attribute_name, "ConstantValue") == 0)
		{
			delta = sizeof(ATTRIBUTE_ConstantValue);
			readAttribute = (ReadAttributeFunction)ReadAttribute_ConstantValue;
		}
		else if (strcmp(attribute_name, "Code") == 0)
		{
			delta = sizeof(ATTRIBUTE_Code);
			readAttribute = (ReadAttributeFunction)ReadAttribute_Code;
		}
		else if (strcmp(attribute_name, "BootstrapMethods") == 0)
		{
			delta = sizeof(ATTRIBUTE_BootstrapMethods);
			readAttribute = (ReadAttributeFunction)ReadAttribute_BootstrapMethods;
		}
		else if (strcmp(attribute_name, "NestHost") == 0)
		{
			delta = sizeof(ATTRIBUTE_NestHost);
			readAttribute = (ReadAttributeFunction)ReadAttribute_NestHost;
		}
		else if (strcmp(attribute_name, "NestMembers") == 0)
		{
			delta = sizeof(ATTRIBUTE_NestMembers);
			readAttribute = (ReadAttributeFunction)ReadAttribute_NestMembers;
		}
		else
		{
			delta = sizeof(ATTRIBUTE_Unknown);
			readAttribute = (ReadAttributeFunction)ReadAttribute_Unknown;
		}

		// create attribute and populate
		curr_attribute = calloc(1, delta);
		curr_attribute->attribute_name_index = curr_attribute_name_index;
		r = readAttribute(file, curr_attribute, curr_attribute_length, constant_pool);
		attributes[i] = (ATTRIBUTE *)curr_attribute;
	}

	return r;
}

void ATTRIBUTE_Dealloc(u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool)
{
	if (attributes_count == 0 || attributes == NULL) return;

	const char *attribute_name;
	u2 curr_name_index;
	FreeAttributeFunction freeAttribute;
	for (int i = 0; i < attributes_count; i++)
	{
		curr_name_index = attributes[i]->attribute_name_index;
		attribute_name =
				(const char *)((CONSTANT_Utf8*) constant_pool[curr_name_index - 1])->runes;

		if (strcmp(attribute_name, "ConstantValue") == 0)
		{
			freeAttribute = (FreeAttributeFunction)FreeAttribute_ConstantValue;
		}
		else if (strcmp(attribute_name, "Code") == 0)
		{
			freeAttribute = (FreeAttributeFunction)FreeAttribute_Code;
		}
		else if (strcmp(attribute_name, "BootstrapMethods") == 0)
		{
			freeAttribute = (FreeAttributeFunction)FreeAttribute_BootstrapMethods;
		}
		else if (strcmp(attribute_name, "NestHost") == 0)
		{
			freeAttribute = (FreeAttributeFunction)FreeAttribute_NestHost;
		}
		else if (strcmp(attribute_name, "NestMembers") == 0)
		{
			freeAttribute = (FreeAttributeFunction)FreeAttribute_NestMembers;
		}
		else
		{
			freeAttribute = (FreeAttributeFunction)FreeAttribute_Unknown;
		}

		// destroy attribute and null entry
		freeAttribute(attributes[i], constant_pool);
		free(attributes[i]);
		attributes[i] = NULL;
	}
}
