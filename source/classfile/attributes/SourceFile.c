#include "classfile/attributes/SourceFile.h"

JRESULT ReadAttribute_SourceFile(FILE *file, ATTRIBUTE_SourceFile *attribute, u4 attribute_length, CONSTANT **constant_pool)
{
	JRESULT r = 0;

	fread(&attribute->sourcefile_index, 2, 1, file);
	attribute->sourcefile_index = Big2(attribute->sourcefile_index);

	return r;
}

void FreeAttribute_SourceFile(ATTRIBUTE_SourceFile *attribute, CONSTANT **constant_pool)
{
	return;
}
