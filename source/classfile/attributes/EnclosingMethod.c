#include "classfile/attributes/EnclosingMethod.h"

JRESULT ReadAttribute_EnclosingMethod(FILE *file, ATTRIBUTE_EnclosingMethod *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_EnclosingMethod(ATTRIBUTE_EnclosingMethod *attribute, CONSTANT **constant_pool);
