#include "classfile/attributes/Exceptions.h"

JRESULT ReadExceptionsAttribute(FILE *file, ATTRIBUTE_Exceptions *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeExceptionsAttribute(ATTRIBUTE_Exceptions *attribute, CONSTANT **constant_pool);
