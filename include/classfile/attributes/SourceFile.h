#ifndef CLASSFILE_ATTRIBUTES_SOURCEFILE_H_
#define CLASSFILE_ATTRIBUTES_SOURCEFILE_H_

#include "Attributes.h"

/*
 * A structure for the Source File Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.10
 *
 * sourcefile_index
 *   A Constant Pool index to a CONSTANT_Utf8 structure
 *   for the name of the source file.
 */
typedef struct {
	u2 attribute_name_index;
	u2 sourcefile_index;
} ATTRIBUTE_SourceFile;

JRESULT ReadAttribute_SourceFile(FILE *file, ATTRIBUTE_SourceFile *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_SourceFile(ATTRIBUTE_SourceFile *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_SOURCEFILE_H_ */
