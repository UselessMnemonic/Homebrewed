#ifndef FIELDMETHODS_H_
#define FIELDMETHODS_H_

#include "WideTypes.h"
#include <stdio.h>
#include "Attributes.h"
#include "ConstantPool.h"

/* Field and Method Definition */

typedef struct
{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	ATTRIBUTE **attributes;
} FIELD;

typedef FIELD METHOD;

JRESULT ReadFields(FILE *file, FIELD *fields, u2 num_items, CONSTANT **constant_pool);
JRESULT ReadMethods(FILE *file, METHOD *methods, u2 num_items, CONSTANT **constant_pool);

void FreeFields(FIELD *fields, u2 fields_count, CONSTANT **constant_pool);
void FreeMethods(METHOD *methods, u2 methods_count, CONSTANT **constant_pool);

#endif /* FIELDMETHODS_H_ */
