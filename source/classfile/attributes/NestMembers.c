#include "classfile/attributes/NestMembers.h"

JRESULT ReadNestMembersAttribute(FILE *file, ATTRIBUTE_NestMembers *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeNestMembersAttribute(ATTRIBUTE_NestMembers *attribute, CONSTANT **constant_pool);
