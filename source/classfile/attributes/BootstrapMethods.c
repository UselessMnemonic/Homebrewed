#include "classfile/attributes/BootstrapMethods.h"
#include <stdlib.h>
#include <stdio.h>

JRESULT ReadBootstrapMethods(FILE *file, u2 num_bootstrap_methods, struct BootstrapMethod **bootstrap_methods)
{
	JRESULT r = 0;

	// temporary entry
	u2 curr_ref = 0;
	u2 curr_num_arguments = 0;
	struct BootstrapMethod *curr_method;
	size_t total_new_size = 0;

	for (int i = 0; i < num_bootstrap_methods; i++)
	{
		// read needed data
		fread(&curr_ref, 2, 1, file);
		curr_ref = Big2(curr_ref);

		fread(&curr_num_arguments, 2, 1, file);
		curr_num_arguments = Big2(curr_num_arguments);

		// allocate and construct new bootstrap method
		total_new_size = sizeof(struct BootstrapMethod) + (2 * curr_num_arguments);
		curr_method = calloc(1, total_new_size);

		curr_method->bootstrap_method_ref = curr_ref;
		curr_method->num_bootstrap_arguments = curr_num_arguments;

		fread(&curr_method->num_bootstrap_arguments, 2, curr_num_arguments, file);
		for (int k = 0; k < curr_num_arguments; k++) // fix the byte order
		{
			curr_method->bootstrap_arguments[k] = Big2(curr_method->bootstrap_arguments[k]);
		}

		// save new method
		bootstrap_methods[i] = curr_method;
	}

	return r;
}

JRESULT ReadAttribute_BootstrapMethods(FILE *file, ATTRIBUTE_BootstrapMethods *attribute, u4 attribute_length, CONSTANT **constant_pool)
{
	JRESULT r = 0;

	fread(&attribute->num_bootstrap_methods, 2, 1, file);
	attribute->num_bootstrap_methods = Big2(attribute->num_bootstrap_methods);

	attribute->bootstrap_methods = NULL;
	if (attribute->num_bootstrap_methods > 0)
	{
		attribute->bootstrap_methods = calloc(attribute->num_bootstrap_methods, sizeof(struct BootstrapMethod*));
		ReadBootstrapMethods(file, attribute->num_bootstrap_methods, attribute->bootstrap_methods);
	}

	return r;
}

void FreeAttribute_BootstrapMethods(ATTRIBUTE_BootstrapMethods *attribute, CONSTANT **constant_pool)
{
	if (attribute->bootstrap_methods == NULL || attribute->num_bootstrap_methods == 0) return;
	for (int i = 0; i < attribute->num_bootstrap_methods; i++) // free all bootstrap methods
	{
		free(attribute->bootstrap_methods[i]);
	}
	free(attribute->bootstrap_methods); // free vector
}
