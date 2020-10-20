#include "classfile/attributes/EnclosingMethod.h"

JRESULT ReadEnclosingMethodAttribute(FILE *file, ATTRIBUTE_EnclosingMethod *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeEnclosingMethodAttribute(ATTRIBUTE_EnclosingMethod *attribute, CONSTANT **constant_pool);
