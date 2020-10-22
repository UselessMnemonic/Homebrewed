#include "classfile/Member.h"
#include <string.h>
#include <stdlib.h>

JRESULT ReadFields(FILE *file, u2 fields_count, FIELD *fields, CONSTANT **constant_pool)
{
	JRESULT r = 0;
	FIELD *curr_field = NULL;
	for (int i = 0; i < fields_count; i++)
	{
		curr_field = &fields[i];

		fread(&curr_field->access_flags, 2, 1, file);
		curr_field->access_flags = Big2(curr_field->access_flags);

		fread(&curr_field->name_index, 2, 1, file);
		curr_field->name_index = Big2(curr_field->name_index);

		fread(&curr_field->descriptor_index, 2, 1, file);
		curr_field->descriptor_index = Big2(curr_field->descriptor_index);

		fread(&curr_field->attributes_count, 2, 1, file);
		curr_field->attributes_count = Big2(curr_field->attributes_count);

		curr_field->attributes = NULL;
		if (curr_field->attributes_count > 0)
		{
			curr_field->attributes = calloc(curr_field->attributes_count, sizeof(ATTRIBUTE *));
			ATTRIBUTE_ReadFromFile(file, curr_field->attributes_count, curr_field->attributes, constant_pool);
		}
	}
	return r;
}

JRESULT ReadMethods(FILE *file, u2 methods_count, METHOD *methods, CONSTANT **constant_pool)
{
	JRESULT r = 0;
	METHOD *curr_method = NULL;
	for (int i = 0; i < methods_count; i++)
	{
		curr_method = &methods[i];

		fread(&curr_method->access_flags, 2, 1, file);
		curr_method->access_flags = Big2(curr_method->access_flags);

		fread(&curr_method->name_index, 2, 1, file);
		curr_method->name_index = Big2(curr_method->name_index);

		fread(&curr_method->descriptor_index, 2, 1, file);
		curr_method->descriptor_index = Big2(curr_method->descriptor_index);

		fread(&curr_method->attributes_count, 2, 1, file);
		curr_method->attributes_count = Big2(curr_method->attributes_count);

		curr_method->attributes = NULL;
		if (curr_method->attributes_count > 0)
		{
			curr_method->attributes = calloc(curr_method->attributes_count, sizeof(ATTRIBUTE *));
			ATTRIBUTE_ReadFromFile(file, curr_method->attributes_count, curr_method->attributes, constant_pool);
		}
	}
	return r;
}

void FreeFields(u2 fields_count, FIELD *fields, CONSTANT **constant_pool)
{
	if (fields_count == 0 || fields == NULL) return;
	for (int i = 0; i < fields_count; i++)
	{
		ATTRIBUTE_Dealloc(fields[i].attributes_count, fields[i].attributes, constant_pool);
		free(fields[i].attributes);
	}
}

void FreeMethods(u2 methods_count, METHOD *methods, CONSTANT **constant_pool)
{
	if (methods_count == 0 || methods == NULL) return;
	for (int i = 0; i < methods_count; i++)
	{
		ATTRIBUTE_Dealloc(methods[i].attributes_count, methods[i].attributes, constant_pool);
		free(methods[i].attributes);
	}
}
