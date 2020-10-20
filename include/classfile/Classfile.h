#ifndef CLASSFILE_H_
#define CLASSFILE_H_

#include "WideTypes.h"
#include <stdio.h>

#include "ConstantPool.h"
#include "FieldMethods.h"
#include "Attributes.h"

/* Classfile Definition */

typedef struct {
	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 constant_pool_count;
	CONSTANT **constant_pool;
	u2 access_flags;
	u2 this_class;
	u2 super_class;
	u2 interfaces_count;
	u2 *interfaces;
	u2 fields_count;
	FIELD *fields;
	u2 methods_count;
	METHOD *methods;
	u2 attributes_count;
	ATTRIBUTE **attributes;
} CLASSFILE;

JRESULT ReadClassfile(FILE *file, CLASSFILE *clazz);
JRESULT ReadInterfaces(FILE *file, u2 *interfaces, u2 num_items);

void FreeClassfile(CLASSFILE *clazz);
void FreeClassfileReference(CLASSFILE *clazz);

#endif /* CLASSFILE_H_ */
