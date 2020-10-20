#include "classfile/attributes/SourceDebugExtension.h"

JRESULT ReadAttribute_SourceDebugExtension(FILE *file, ATTRIBUTE_SourceDebugExtension *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_SourceDebugExtension(ATTRIBUTE_SourceDebugExtension *attribute, CONSTANT **constant_pool);
