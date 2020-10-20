#include "classfile/attributes/Synthetic.h"

JRESULT ReadSyntheticAttribute(FILE *file, ATTRIBUTE_Synthetic *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeSyntheticAttribute(ATTRIBUTE_Synthetic *attribute, CONSTANT **constant_pool);
