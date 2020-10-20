#include "classfile/attributes/Synthetic.h"

JRESULT ReadAttribute_Synthetic(FILE *file, ATTRIBUTE_Synthetic *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_Synthetic(ATTRIBUTE_Synthetic *attribute, CONSTANT **constant_pool);
