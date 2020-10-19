#include <string.h>
#include <stdlib.h>
#include "ClassfileFieldMethods.h"

JRESULT ReadFields(FILE *file, FIELD *fields, u2 num_items, CONSTANT **constant_pool)
{
	JRESULT r = 0;
	FIELD *curr_field = NULL;
	for (int i = 0; i < num_items; i++)
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
			ReadAttributes(file, curr_field->attributes, curr_field->attributes_count, constant_pool);
		}
		else
		{
			curr_field->attributes = NULL;
		}
	}
	return r;
}

JRESULT ReadMethods(FILE *file, METHOD *methods, u2 num_items, CONSTANT **constant_pool)
{
	return ReadFields(file, (FIELD *)methods, num_items, constant_pool);
}

void FreeFields(FIELD *fields, u2 fields_count, CONSTANT **constant_pool)
{
	for (int i = 0; i < fields_count; i++)
	{
		FreeAttributes(fields[i].attributes, fields[i].attributes_count, constant_pool);
	}
	free(fields);
}

void FreeMethods(METHOD *methods, u2 methods_count, CONSTANT **constant_pool)
{
	FreeFields((FIELD *)methods, methods_count, constant_pool);
}
