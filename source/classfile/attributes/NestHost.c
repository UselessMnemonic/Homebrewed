#include "classfile/attributes/NestHost.h"

JRESULT ReadNestHostAttribute(FILE *file, ATTRIBUTE_NestHost *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeNestHostAttribute(ATTRIBUTE_NestHost *attribute, CONSTANT **constant_pool);
