#ifndef CLASSFILE_ATTRIBUTES_BOOTSTRAPMETHODS_H_
#define CLASSFILE_ATTRIBUTES_BOOTSTRAPMETHODS_H_

#include "Attributes.h"

/*
 * A structure describing a bootstrap method, used
 * to support dynamic languages.
 *
 * bootstrap_method_ref
 *   A Constant Pool index to a CONSTANT_MethodHandle describing
 *   the method.
 *
 * num_boostram_arguments
 *   The number of elements in the bootstrap arguments array.
 *
 * boostrap_arguments
 *   An array of Constant Pool indices that denote the arguments to
 *   the bootstrap method.
 */
struct BootstrapMethod {
	u2 bootstrap_method_ref;
	u2 num_bootstrap_arguments;
	u2 bootstrap_arguments[];
};

/*
 * A structure for the Bootstrap Methods Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.23
 *
 * num_bootstrap_methods
 *   The number of elements in the bootstrap methods vector.
 *
 * bootstrap_methods
 *   A vector of bootstrap methods.
 */
typedef struct {
	u2 attribute_name_index;
	u2 num_bootstrap_methods;
	struct BootstrapMethod **bootstrap_methods;
} ATTRIBUTE_BootstrapMethods;

JRESULT ReadAttribute_BootstrapMethods(FILE *file, ATTRIBUTE_BootstrapMethods *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeAttribute_BootstrapMethods(ATTRIBUTE_BootstrapMethods *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_BOOTSTRAPMETHODS_H_ */
