#include "classfile/attributes/InnerClasses.h"

JRESULT ReadInnerClassesAttribute(FILE *file, ATTRIBUTE_InnerClasses *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeInnerClassesAttribute(ATTRIBUTE_InnerClasses *attribute, CONSTANT **constant_pool);
