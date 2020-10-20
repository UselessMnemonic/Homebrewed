#ifndef CLASSFILE_ATTRIBUTES_INNERCLASSES_H_
#define CLASSFILE_ATTRIBUTES_INNERCLASSES_H_

#include "../Attributes.h"

/*
 * A structure describing an inner class, a class that is not a member of a package.
 *
 * inner_class_info_index
 *   A Constant Pool index to a CONSTANT_Class for the
 *   inner class.
 *
 * outter_class_info_index
 *   A Constant Pool index to a CONSTANT_Class for the
 *   enclosing class, or zero if the inner class has no
 *   enclosing class.
 *
 * inner_name_index
 *   A Constant Pool index to a CONSTANT_Utf8 for the
 *   name of the inner class, or 0 if the class is anonymous.
 *
 * inner_class_access_flags
 *   A flag mask denoting access permissions as declared in source.
 */
struct InnerClass {
	u2 inner_class_info_index;
	u2 outer_class_info_index;
	u2 inner_name_index;
	u2 inner_class_access_flags;
};

/*
 * A structure for the Inner Classes Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.6
 *
 * number_of_classes
 *   The number of elements in the classes array.
 *
 * classes
 *   An array of Inner Class structures.
 */
typedef struct {
	u2 attribute_name_index;
	u2 number_of_classes;
	struct InnerClass *classes;
} ATTRIBUTE_InnerClasses;

JRESULT ReadInnerClassesAttribute(FILE *file, ATTRIBUTE_InnerClasses *attribute, u4 attribute_length, CONSTANT **constant_pool);

void FreeInnerClassesAttribute(ATTRIBUTE_InnerClasses *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILE_ATTRIBUTES_INNERCLASSES_H_ */
