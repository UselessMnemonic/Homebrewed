#include "classfile/attributes/NestMembers.h"
#include <stdio.h>
#include <stdlib.h>

JRESULT ReadAttribute_NestMembers(FILE *file, ATTRIBUTE_NestMembers *attribute, u4 attribute_length, CONSTANT **constant_pool)
{
	JRESULT r = 0;

	fread(&attribute->number_of_classes, 2, 1, file);
	attribute->number_of_classes = Big2(attribute->number_of_classes);

	attribute->classes = NULL;
	if (attribute->number_of_classes > 0)
	{
		attribute->classes = calloc(attribute->number_of_classes, 2);
		for (int i = 0; i < attribute->number_of_classes; i++)
		{
			attribute->classes[i] = Big2(attribute->classes[i]);
		}
	}

	return r;
}

void FreeAttribute_NestMembers(ATTRIBUTE_NestMembers *attribute, CONSTANT **constant_pool)
{
	free(attribute->classes);
}
