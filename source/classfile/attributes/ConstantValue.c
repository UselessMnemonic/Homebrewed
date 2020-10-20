#include "classfile/attributes/ConstantValue.h"

JRESULT ReadConstantValueAttribute(FILE *file, ATTRIBUTE_ConstantValue *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeConstantValueAttribute(ATTRIBUTE_ConstantValue *attribute, CONSTANT **constant_pool);
