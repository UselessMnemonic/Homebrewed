#ifndef CLASSFILE_ATTRIBUTES_SOURCEDEBUGEXTENSION_H_
#define CLASSFILE_ATTRIBUTES_SOURCEDEBUGEXTENSION_H_

#include "Attributes.h"

/*
 * A structure for the Source Debug Extension Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.11
 *
 * debug_extension
 *   Modified UTF8 that holds extended debugging information.
 */
typedef struct {
	u2 attribute_name_index;
	char *debug_extension;
} ATTRIBUTE_SourceDebugExtension;

JRESULT ReadAttribute_SourceDebugExtension(FILE *file, ATTRIBUTE_SourceDebugExtension *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_SourceDebugExtension(ATTRIBUTE_SourceDebugExtension *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_SOURCEDEBUGEXTENSION_H_ */
