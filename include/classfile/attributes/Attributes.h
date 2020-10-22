#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_

#include "../../WideTypes.h"
#include "../ConstantPool.h"
#include <stdio.h>

/*
 * The parent structure for all attributes. This acts like a header
 * preceding the attribute's data.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7
 *
 * attribute_name_index
 *   A Constant Pool index to a CONSTANT_Utf8 structure
 *   for the name of the attribute.
 *
 * info
 *   Names the data following the header, which is
 *   implementation dependent.
 */
typedef struct {
	u2 attribute_name_index;
	u1 info[];
} ATTRIBUTE;

/*
 * This parses some number of attributes from a file into a vector.
 *
 * file
 *   The file providing an attribute stream. The current location of
 *   the file buffer must be at the start of the stream.
 *   Must be non-NULL.
 *
 * attributes_count
 *   The number of attributes to parse from the file.
 *
 * attributes
 *   The vector of attributes to be populated. Must be at least as
 *   long as attributes_count elements. Must be non-NULL.
 *
 * constant_pool
 *   The constant pool parsed earlier from the same file, needed to
 *   identify each attribute. Must be non-NULL.
 */
JRESULT ReadAttributes(FILE *file, u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool);

/*
 * This releases all memory allocated by ReadAttributes, and sets
 * each element in the vector to NULL.
 *
 * attributes_count
 *   The number of elements in the vector.
 *
 * attributes
 *   The vector populated by ReadAttributes.
 *
 * constant_pool
 *   The constant pool used when creating attributes, needed to
 *   identify each attribute. Must be non-NULL.
 */
void FreeAttributes(u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool);

/*
 * This describes a function type that reads an attribute
 * from a file into a pre-allocated structure.
 *
 * The file buffer must point just after the attribute_length
 * value in the attribute data (i.e. where attribute-specific
 * data starts)
 *
 * None of the arguments may be NULL unless otherwise specified.
 */
typedef JRESULT (*ReadAttributeFunction)(FILE*, ATTRIBUTE*, u4, CONSTANT**);

/*
 * This describes a function type that tears down any memory used
 * by an attribute such that freeing the memory to which this
 * attribute belongs does not incur a memory leak.
 *
 * None of the arguments may be NULL unless otherwise specified.
 */
typedef void (*FreeAttributeFunction)(ATTRIBUTE*, CONSTANT**);

#endif /* ATTRIBUTES_H_ */
