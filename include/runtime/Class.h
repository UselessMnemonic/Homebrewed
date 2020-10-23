#ifndef RUNTIME_CLASS_H_
#define RUNTIME_CLASS_H_

#include "../WideTypes.h"
#include "../classfile/ConstantPool.h"
#include "../classfile/Member.h"
#include "../classfile/attributes/BootstrapMethods.h"
#include "../classfile/attributes/NestHost.h"
#include "../classfile/attributes/NestMembers.h"
#include "Object.h"

typedef struct CLASS CLASS;
typedef struct OBJECT OBJECT;

struct CLASS {
	// these are populated during loading
	u2 access_flags;
	u2 constant_pool_count;
	u2 interfaces_count;
	u2 fields_count;
	u2 methods_count;
	u2 attributes_count;

	u2 this_class_ref_index;
	u2 super_class_ref_index;

	CONSTANT **constant_pool;
	u2 *interface_ref_indices;
	FIELD *fields;
	METHOD *methods;
	ATTRIBUTE **attributes;

	// resolved during linkage
	u2 instance_field_count;
	u2 static_field_count;

	CLASS *super_class;
	CLASS **interfaces;
	void **static_fields;

	// resolved... lazily?
	OBJECT *instance;
	ATTRIBUTE_BootstrapMethods *bootstrap_methods_attr;
	ATTRIBUTE_NestHost *nest_host_attr;
	ATTRIBUTE_NestMembers *nest_members_attr;
};

/*
 * Links a loaded class by resolving symbolic references and
 * initializing static variables.
 *
 * If this class's super class is not yet linked, it will be linked.
 * If the super class is not yet loaded, the default Bootstrap Loader
 * will load the class.
 * If the super class cannot be loaded and linked, an error will propagate
 * through the VM.
 */
JRESULT CLASS_Link(CLASS *clazz);

#endif /* RUNTIME_CLASS_H_ */
