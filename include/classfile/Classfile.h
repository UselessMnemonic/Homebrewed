#ifndef CLASSFILE_CLASSFILE_H_
#define CLASSFILE_CLASSFILE_H_

#include "../WideTypes.h"
#include "ConstantPool.h"
#include "Member.h"
#include "attributes/Attributes.h"
#include <stdio.h>

/*
 * A structure defining a class file for use with the JVM.
 * All relevant components are exposed here for access.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.1
 *
 * TODO Convert Classfile reader into Class parser
 */
typedef struct {
	u2 minor_version;
	u2 major_version;
	u2 constant_pool_count;
	CONSTANT **constant_pool;
	u2 access_flags;
	u2 this_class;
	u2 super_class;
	u2 interfaces_count;
	u2 *interface_name_indices;
	u2 fields_count;
	FIELD *fields;
	u2 methods_count;
	METHOD *methods;
	u2 attributes_count;
	ATTRIBUTE **attributes;
} CLASSFILE;

/*
 * Parses a classfile from a file into a pre-allocated
 * structure.
 *
 * file
 *   The file providing classfile data. The current location of
 *   the file buffer must be at the start of the data.
 *   Must be non-NULL.
 *
 * clazz
 *   A pre-allocated structure in which to store data.
 */
JRESULT CLASSFILE_ReadFromFile(FILE *file, CLASSFILE *clazz);

/*
 * This releases all memory allocated by ReadClassfile.
 * Note that the pointer itself is not deallocated.
 *
 * clazz
 *   The classfile populated by ReadClassfile. Must be non-NULL.
 */
void CLASSFILE_Dealloc(CLASSFILE *clazz);

#endif /* CLASSFILE_CLASSFILE_H_ */
