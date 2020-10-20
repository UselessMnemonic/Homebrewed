#include "classfile/attributes/InnerClasses.h"

JRESULT ReadAttribute_InnerClasses(FILE *file, ATTRIBUTE_InnerClasses *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_InnerClasses(ATTRIBUTE_InnerClasses *attribute, CONSTANT **constant_pool);
