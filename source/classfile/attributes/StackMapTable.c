#include "classfile/attributes/StackMapTable.h"

JRESULT ReadStackMapTableAttribute(FILE *file, ATTRIBUTE_StackMapTable *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeStackMapTableAttribute(ATTRIBUTE_StackMapTable *attribute, CONSTANT **constant_pool);

JRESULT ReadVerificationInfo(FILE *file, struct VerificationInfo *vi, u2 number_of_items);
