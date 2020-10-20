#include "classfile/attributes/NestHost.h"
#include <stdio.h>

JRESULT ReadAttribute_NestHost(FILE *file, ATTRIBUTE_NestHost *attribute, u4 attribute_length, CONSTANT **constant_pool)
{
	JRESULT r = 0;
	fread(&attribute->host_class_index, 2, 1, file);
	attribute->host_class_index = Big2(attribute->host_class_index);
	return r;
}

void FreeAttribute_NestHost(ATTRIBUTE_NestHost *attribute, CONSTANT **constant_pool)
{
	return;
}
