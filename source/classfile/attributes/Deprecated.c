#include "classfile/attributes/Deprecated.h"

JRESULT ReadAttribute_Deprecated(FILE *file, ATTRIBUTE_Deprecated *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_Deprecated(ATTRIBUTE_Deprecated *attribute, CONSTANT **constant_pool);
