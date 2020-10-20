#include <string.h>
#include <stdlib.h>
#include "classfile/Classfile.h"

JRESULT ReadClassfile(FILE *file, CLASSFILE *clazz)
{
	JRESULT r = 0;

	/* Read Header */
	fread(&clazz->magic, 4, 1, file);
	clazz->magic = Big4(clazz->magic);

	fread(&clazz->minor_version, 2, 1, file);
	clazz->minor_version = Big2(clazz->minor_version);

	fread(&clazz->major_version, 2, 1, file);
	clazz->major_version = Big2(clazz->major_version);

	/* Parse Constant Pool */
	fread(&clazz->constant_pool_count, 2, 1, file);
	clazz->constant_pool_count = Big2(clazz->constant_pool_count);

	u2 num_items = clazz->constant_pool_count - 1;
	clazz->constant_pool = NULL;
	if (num_items > 0)
	{
		clazz->constant_pool = calloc(num_items, sizeof(CONSTANT*));
		r = ReadConstantPool(file, num_items, clazz->constant_pool);
	}

	/* Parse Flags and Class Hierarchy */
	fread(&clazz->access_flags, 2, 1, file);
	clazz->access_flags = Big2(clazz->access_flags);

	fread(&clazz->this_class, 2, 1, file);
	clazz->this_class = Big2(clazz->this_class);

	fread(&clazz->super_class, 2, 1, file);
	clazz->super_class = Big2(clazz->super_class);

	/* Parse Interfaces */
	fread(&clazz->interfaces_count, 2, 1, file);
	clazz->interfaces_count = Big2(clazz->interfaces_count);

	num_items = clazz->interfaces_count;
	clazz->interfaces = NULL;
	if (num_items > 0)
	{
		clazz->interfaces = calloc(num_items, sizeof(u2));
		r = ReadInterfaces(file, num_items, clazz->interfaces);
	}

	/* Parse Fields */
	fread(&clazz->fields_count, 2, 1, file);
	clazz->fields_count = Big2(clazz->fields_count);

	num_items = clazz->fields_count;
	clazz->fields = NULL;
	if (num_items > 0)
	{
		clazz->fields = calloc(num_items, sizeof(FIELD));
		r = ReadFields(file, num_items, clazz->fields, clazz->constant_pool);
	}

	/* Parse Methods */
	fread(&clazz->methods_count, 2, 1, file);
	clazz->methods_count = Big2(clazz->methods_count);

	num_items = clazz->methods_count;
	clazz->methods = NULL;
	if (num_items > 0)
	{
		clazz->methods = calloc(num_items, sizeof(METHOD));
		r = ReadMethods(file, num_items, clazz->methods, clazz->constant_pool);
	}

	/* Parse Attributes */
	fread(&clazz->attributes_count, 2, 1, file);
	clazz->attributes_count = Big2(clazz->attributes_count);

	num_items = clazz->attributes_count;
	clazz->attributes = NULL;
	if (num_items > 0)
	{
		clazz->attributes = calloc(num_items, sizeof(ATTRIBUTE*));
		r = ReadAttributes(file, num_items, clazz->attributes, clazz->constant_pool);
	}

	//if (fgetc(file) != EOF) r = JRESULT_EXPECTED_EOF;

	return r;
}

void FreeClassfile(CLASSFILE *clazz)
{
	free(clazz->interfaces);
	clazz->interfaces = NULL;

	FreeFields(clazz->fields_count, clazz->fields, clazz->constant_pool);
	free(clazz->fields);
	clazz->fields = NULL;

	FreeMethods(clazz->methods_count, clazz->methods, clazz->constant_pool);
	free(clazz->methods);
	clazz->methods = NULL;

	FreeAttributes(clazz->attributes_count, clazz->attributes, clazz->constant_pool);
	free(clazz->attributes);
	clazz->attributes = NULL;

	FreeConstantPool(clazz->constant_pool_count, clazz->constant_pool);
	free(clazz->constant_pool);
	clazz->constant_pool = NULL;
}

JRESULT ReadInterfaces(FILE *file, u2 interfaces_count, u2 *interfaces)
{
	JRESULT r = 0;
	fread(interfaces, 2, interfaces_count, file);
	for (int i = 0; i < interfaces_count; i++)
	{
		interfaces[i] = Big2(interfaces[i]);
	}
	return r;
}
