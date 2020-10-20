#include "classfile/attributes/SourceDebugExtension.h"

JRESULT ReadSourceDebugExtensionAttribute(FILE *file, ATTRIBUTE_SourceDebugExtension *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeSourceDebugExtensionAttribute(ATTRIBUTE_SourceDebugExtension *attribute, CONSTANT **constant_pool);
