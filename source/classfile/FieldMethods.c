#include <string.h>
#include <stdlib.h>

#include "classfile/FieldMethods.h"

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

		if (curr_field->attributes_count > 0)
		{
			curr_field->attributes = calloc(curr_field->attributes_count, sizeof(ATTRIBUTE *));
			ReadAttributes(file, curr_field->attributes_count, curr_field->attributes, constant_pool);
		}
		else
		{
			curr_field->attributes = NULL;
		}
	}
	return r;
}

JRESULT ReadMethods(FILE *file, u2 methods_count, METHOD *methods, CONSTANT **constant_pool)
{
	return ReadFields(file, methods_count, (FIELD *)methods, constant_pool);
}

void FreeFields(u2 fields_count, FIELD *fields, CONSTANT **constant_pool)
{
	for (int i = 0; i < fields_count; i++)
	{
		FreeAttributes(fields[i].attributes_count, fields[i].attributes, constant_pool);
	}
}

void FreeMethods(u2 methods_count, METHOD *methods, CONSTANT **constant_pool)
{
	FreeFields(methods_count, (FIELD *)methods, constant_pool);
}
