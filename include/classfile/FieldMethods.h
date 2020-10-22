#ifndef FIELDMETHODS_H_
#define FIELDMETHODS_H_

#include "../WideTypes.h"
#include "attributes/Attributes.h"
#include "ConstantPool.h"
#include <stdio.h>

/*
 * A structure representing a field or method as defined in a Class.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.5
 * and https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.6
 *
 * access_flags
 *   A mask denoting access permissions.
 *
 * name_index
 *   A Constant Pool index to a CONSTANT_Utf8 structure for the name
 *   of the field or method.
 *
 * descriptor_index
 *   A Constant Pool index to a CONSTANT_Utf8 structure for the
 *   descriptor of the field or method.
 *
 * attributes_count
 *   The number of attributes in the field or method.
 *
 * attributes
 *   A vector of attributes attributes_count elements long.
 */
typedef struct
{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	ATTRIBUTE **attributes;
} FIELD;

typedef struct
{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	ATTRIBUTE **attributes;
} METHOD;

/*
 * Parses some number of fields from a file into a pre-allocated
 * array.
 *
 * file
 *   The file providing field data. The current location of
 *   the file buffer must be at the start of the data.
 *   Must be non-NULL.
 *
 * fields_count
 *   The number of fields to parse from the file.
 *
 * fields
 *   A pre-allocated array of fields to populate, at least
 *   fields_count elements long
 *
 * constant_pool
 *   The constant pool parsed earlier from the same file.
 */
JRESULT ReadFields(FILE *file, u2 fields_count, FIELD *fields, CONSTANT **constant_pool);

/*
 * Parses some number of methods from a file into a pre-allocated
 * array.
 *
 * file
 *   The file providing method data. The current location of
 *   the file buffer must be at the start of the data.
 *   Must be non-NULL.
 *
 * methods_count
 *   The number of methods to parse from the file.
 *
 * methods
 *   A pre-allocated array of methods to populate, at least
 *   methods_count elements long.
 *
 * constant_pool
 *   The constant pool parsed earlier from the same file.
 */
JRESULT ReadMethods(FILE *file, u2 methods_count, METHOD *methods, CONSTANT **constant_pool);

/*
 * This releases all memory allocated by ReadFields.
 * Note that the pointer itself is not freed.
 *
 * fields_count
 *   The number of fields in the field array.
 *
 * fields
 *   The array of fields to be deallocated, at least
 *   fields_count elements long.
 */
void FreeFields(u2 fields_count, FIELD *fields, CONSTANT **constant_pool);

/*
 * This releases all memory allocated by ReadMethods.
 * Note that the pointer itself is not freed.
 *
 * methods_count
 *   The number of methods in the method array.
 *
 * methods
 *   The array of methods to be deallocated, at least
 *   methods_count elements long.
 */
void FreeMethods(u2 methods_count, METHOD *methods, CONSTANT **constant_pool);

#endif /* FIELDMETHODS_H_ */
