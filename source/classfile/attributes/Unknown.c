#include "classfile/attributes/Unknown.h"

JRESULT ReadUnknownAttribute(FILE *file, ATTRIBUTE_Unknown *attribute, u4 attribute_length, CONSTANT **constant_pool) {
	JRESULT r = 0;
	u1 ignore[attribute_length];
	attribute->attribute_length = attribute_length;
	fread(ignore, 1, attribute_length, file);
	return r;
}

void FreeUnknownAttribute(ATTRIBUTE_Unknown *attribute, CONSTANT **constant_pool) {
	return;
}
