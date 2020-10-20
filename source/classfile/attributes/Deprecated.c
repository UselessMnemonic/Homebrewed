#include "classfile/attributes/Deprecated.h"

JRESULT ReadDeprecatedAttribute(FILE *file, ATTRIBUTE_Deprecated *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeDeprecatedAttribute(ATTRIBUTE_Deprecated *attribute, CONSTANT **constant_pool);
