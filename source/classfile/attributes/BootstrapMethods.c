#include "classfile/attributes/BootstrapMethods.h"

JRESULT ReadBootstrapMethodsAttribute(FILE *file, ATTRIBUTE_BootstrapMethods *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeBootstrapMethodsAttribute(ATTRIBUTE_BootstrapMethods *attribute, CONSTANT **constant_pool);
