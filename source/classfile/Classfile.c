#include <string.h>
#include <stdlib.h>
#include "classfile/Classfile.h"

JRESULT ReadClassfile(FILE *file, CLASSFILE *clazz)
{
	JRESULT r = 0;
	memset(clazz, 0, sizeof(CLASSFILE));

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
	if (num_items > 0)
	{
		clazz->constant_pool = calloc(num_items, sizeof(CONSTANT *));
		r = ReadConstantPool(file, clazz->constant_pool, num_items);
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
	if (num_items > 0)
	{
		clazz->interfaces = calloc(num_items, sizeof(u2));
		r = ReadInterfaces(file, clazz->interfaces, num_items);
	}

	/* Parse Fields */
	fread(&clazz->fields_count, 2, 1, file);
	clazz->fields_count = Big2(clazz->fields_count);

	num_items = clazz->fields_count;
	if (num_items > 0)
	{
		clazz->fields = calloc(num_items, sizeof(FIELD));
		r = ReadFields(file, clazz->fields, num_items, clazz->constant_pool);
	}

	/* Parse Methods */
	fread(&clazz->methods_count, 2, 1, file);
	clazz->methods_count = Big2(clazz->methods_count);

	num_items = clazz->methods_count;
	if (num_items > 0)
	{
		clazz->methods = calloc(num_items, sizeof(METHOD));
		r = ReadMethods(file, clazz->methods, num_items, clazz->constant_pool);
	}

	/* Parse Attributes */
	fread(&clazz->attributes_count, 2, 1, file);
	clazz->attributes_count = Big2(clazz->attributes_count);

	num_items = clazz->attributes_count;
	if (num_items > 0)
	{
		clazz->attributes = calloc(num_items, sizeof(ATTRIBUTE *));
		r = ReadAttributes(file, num_items, clazz->attributes, clazz->constant_pool);
	}
	else
	{
		clazz->attributes = NULL;
	}

	//if (fgetc(file) != EOF) r = JRESULT_EXPECTED_EOF;

	return r;
}

void FreeClassfileReference(CLASSFILE *clazz)
{
	free(clazz->interfaces);
	clazz->interfaces = NULL;

	if (clazz->fields) FreeMethods(clazz->fields, clazz->fields_count, clazz->constant_pool);
	clazz->fields = NULL;

	if (clazz->methods) FreeMethods(clazz->methods, clazz->methods_count, clazz->constant_pool);
	clazz->methods = NULL;

	if (clazz->attributes) FreeAttributes(clazz->attributes_count, clazz->attributes, clazz->constant_pool);
	clazz->attributes = NULL;

	if (clazz->constant_pool) FreeConstantPool(clazz->constant_pool);
	clazz->constant_pool = NULL;
}

void FreeClassfile(CLASSFILE *clazz)
{
	FreeClassfileReference(clazz);
	free(clazz);
}

JRESULT ReadInterfaces(FILE *file, u2 *interfaces, u2 num_items)
{
	JRESULT r = 0;
	for (int i = 0; i < num_items; i++)
	{
		fread(&interfaces[i], 2, 1, file);
		interfaces[i] = Big2(interfaces[i]);
	}
	return r;
}
