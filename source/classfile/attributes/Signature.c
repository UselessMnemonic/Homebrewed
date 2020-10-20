#include "classfile/attributes/Signature.h"

JRESULT ReadSignatureAttribute(FILE *file, ATTRIBUTE_Signature *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeSignatureAttribute(ATTRIBUTE_Signature *attribute, CONSTANT **constant_pool);
