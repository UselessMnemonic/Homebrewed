#ifndef RUNTIME_CLASS_H_
#define RUNTIME_CLASS_H_

#include "classfile/Classfile.h"

typedef struct _CLASS CLASS;

struct _CLASS {
	u2 constant_pool_count; // embedded items
	u2 fields_count;
	u2 methods_count;
	u2 attributes_count;

	CONSTANT **constant_pool;
	FIELD *fields;
	METHOD *methods;
	ATTRIBUTE **attributes;

	u2 this_class_name_index; // symbolic references
	u2 super_class_name_index;

	u2 access_flags;

	u2 interface_count;
	u2 *interface_name_indices;

	u2 instance_field_count; // resolution cache
	u2 static_field_count;

	CLASS *super_class;
	CLASS **interfaces;
	void **static_fields;
};

/*
 * TODO
 */
JRESULT CLASS_Link(CLASS *clazz);

#endif /* RUNTIME_CLASS_H_ */
