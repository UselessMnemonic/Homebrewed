#include "classfile/attributes/ConstantValue.h"
#include <stdio.h>

JRESULT ReadAttribute_ConstantValue(FILE *file, ATTRIBUTE_ConstantValue *attribute, u4 attribute_length, CONSTANT **constant_pool)
{
	JRESULT r = 0;
	fread(&attribute->constantvalue_index, 2, 1, file);
	attribute->constantvalue_index = Big2(attribute->constantvalue_index);
	return r;
}

void FreeAttribute_ConstantValue(ATTRIBUTE_ConstantValue *attribute, CONSTANT **constant_pool)
{
	return;
}
