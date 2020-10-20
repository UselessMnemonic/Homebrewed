#include "classfile/attributes/Signature.h"

JRESULT ReadAttribute_Signature(FILE *file, ATTRIBUTE_Signature *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_Signature(ATTRIBUTE_Signature *attribute, CONSTANT **constant_pool);
