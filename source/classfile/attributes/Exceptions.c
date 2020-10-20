#include "classfile/attributes/Exceptions.h"

JRESULT ReadAttribute_Exceptions(FILE *file, ATTRIBUTE_Exceptions *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_Exceptions(ATTRIBUTE_Exceptions *attribute, CONSTANT **constant_pool);
