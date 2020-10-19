#ifndef CLASSFILEATTRIBUTES_H_
#define CLASSFILEATTRIBUTES_H_

#include "WideTypes.h"
#include "ClassfileConstantPool.h"
#include <stdio.h>


typedef struct {
	u2 attribute_name_index;
	u1 info[];
} ATTRIBUTE;

/*
 * This parses some number of attributes from a file into a vector
 * of pointers.
 *
 * The return value value indicates any potential errors during
 * the operation.
 *
 * file
 *   The file providing an attribute stream. The current location of
 *   the file buffer must be at the start of the attribute stream.
 *   Must be non-NULL.
 *
 * attributes_count
 *   The number of attributes to parse from the file.
 *
 * attributes
 *   The vector of pointers to be populated. Must be at least as long as
 *   attributes_count elements. Must be non-NULL.
 *
 * constant_pool
 *   The constant pool parsed earlier from the same file, needed to
 *   identify each attribute. Must be non-NULL.
 */
JRESULT ReadAttributes(FILE *file, u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool);

/*
 * This releases all memory allocated by GetAttributes, and sets
 * each element in the vector to NULL.
 *
 * attributes
 *   The vector populated by ReadAttributes. Must be non-NULL.
 *
 * attributes_count
 *   The length the vector.
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
 * The FILE* argument must read beginning after the attribute_length
 * value in the attribute data.
 *
 * None of the arguments may be NULL unless otherwise denoted.
 */
typedef JRESULT (*ReadAttributeFunction)(FILE*, ATTRIBUTE*, u4, CONSTANT**);

////////////////////   CRITICAL: Unknown Attribute                                        ////////////////////

/*
 * A structure for Unknown Attributes
 *
 * attribute_length
 *   The length, in bytes, of the attribute in the classfile.
 */
struct ATTRIBUTE_Unknown {
	u2 attribute_name_index;
	u2 attribute_length;
};

JRESULT ReadUnknownAttribute(FILE *file, struct ATTRIBUTE_Unknown *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   CRITICAL: Constant Value Attribute                                 ////////////////////

/*
 * A structure for the Constant Value attribute.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.2
 *
 * constantvalue_index
 *   The constant_pool entry at that index gives the value represented
 *   by this attribute.
 */
struct ATTRIBUTE_ConstantValue {
	u2 attribute_name_index;
	u2 constantvalue_index;
};

JRESULT ReadConstantValueAttribute(FILE *file, struct ATTRIBUTE_ConstantValue *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   CRITICAL: Code Attribute                                           ////////////////////

/*
 * A structure describing an exception handler.
 *
 * start_pc, end_pc
 *   Describes the range in the code array that this
 *   handler responds to. Specifically, the range is [start_pc, end_pc)
 *
 * handler_pc
 *   The start of the exception handler in the code array.
 *
 * catch_type
 *   When non-zero, this is an index to a CONSTANT_Class_info structure
 *   in the Constant Pool. The exception handler will take over iff
 *   the handler is Throwable.
 *   When zero, this handler responds to any exceptions thrown in its
 *   range.
 *
 */
struct ExceptionEntry {
	u2 start_pc;
	u2 end_pc;
	u2 handler_pc;
	u2 catch_type;
};

/*
 * A structure for the Code attribute.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.3
 *
 * max_stack
 *   The maximum depth of the stack at any point during this method invocation.
 *
 * max_locals
 *   The number of local variables allocated for this method invocation.
 *
 * code_length
 *   The length of the code array, in bytes.
 *
 * code
 *   An array of bytecode instructions.
 *
 * exception_table_length
 *   The number of elements in the exception table.
 *
 * exception_table
 *   An array of exception handlers.
 *
 * attributes_count
 *   The number of elements in the attributes vector.
 *
 * attributes
 *   A vector of attributes specific to this Code attribute.
 */
struct ATTRIBUTE_Code {
	u2 attribute_name_index;
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	bytecode *code;
	u2 exception_table_length;
	struct ExceptionEntry *exception_table;
	u2 attributes_count;
	ATTRIBUTE **attributes;
};

JRESULT ReadCodeAttribute(FILE *file, struct ATTRIBUTE_Code *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   CRITICAL: Stack Map Table Attribute                                ////////////////////

/*
 * A structure containing verification information for the elements
 * in the stack.
 *
 * tag
 *   The type of the element.
 *
 * offset_or_cpool_index
 *   For Object-types, this is the index into the constant pool
 *   for the object's class.
 *   For Uninitialized types, this is the offset into the code
 *   array for the new instruction that created the object.
 */
struct VerificationInfo {
	u1 tag;
	u2 offset_or_cp_index;
};

struct StackMapFrame {
	u1 frame_type;
	u1 data[];
};

struct StackMapFrame_same {
	u1 frame_type; // 0 - 63
};

struct StackMapFrame_same_locals_1_stack_item {
	u1 frame_type; // 64 - 127
	struct VerificationInfo stack;
};

struct StackMapFrame_same_locals_1_stack_item_ext {
	u1 frame_type; // 247
	u2 offset_delta;
	struct VerificationInfo stack;
};

struct StackMapFrame_chop {
	u1 frame_type; // 248 - 250
	u2 offset_delta;
};

struct StackMapFrame_same_ext {
	u1 frame_type; // 251
	u2 offset_delta;
};

struct StackMapFrame_append {
	u1 frame_type; // 252 - 254
	u2 offset_delta;
	struct VerificationInfo *locals; // [frame_type - 251]
};

struct StackMapFrame_full {
	u1 frame_type; // 255
	u2 offset_delta;
	u2 number_of_locals;
	struct VerificationInfo *locals;
	u2 number_of_stack_items;
	struct VerificationInfo *stack;
};

/*
 * A structure for the Stack Map table attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.4
 *
 * number_of_entries
 *   The number of elements in the entries vector.
 *
 * entries
 *   A vector of stack frame structures.
 */
struct ATTRIBUTE_StackMapTable {
	u2 attribute_name_index;
	u2 number_of_entries;
	struct StackMapFrame **entries;
};

JRESULT ReadStackMapTableAttribute(FILE *file, struct ATTRIBUTE_StackMapTable *attribute, u4 attribute_length, CONSTANT **constant_pool);
JRESULT ReadVerificationInfo(FILE *file, struct VerificationInfo *vi, u2 number_of_items);

////////////////////   USEFUL: Exceptions Attribute                                       ////////////////////

/*
 * A structure for the Exceptions Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.5
 *
 * number_of_exceptions
 *   The number of elements in the table.
 *
 * exception_index_table
 *   An array of Constant Pool indices to CONSTANT_Class_info structures
 *   describing the exception types thrown by the method.
 */
struct ATTRIBUTE_Exceptions {
	u2 attribute_name_index;
	u2 number_of_exceptions;
	u2 *exception_index_table;
};

JRESULT ReadExceptionsAttribute(FILE *file, struct ATTRIBUTE_Exceptions *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   USEFUL: Inner Classes Attribute                                    ////////////////////

/*
 * A structure describing an inner class, a class that is not a member of a package.
 *
 * inner_class_info_index
 *   A Constant Pool index to a CONSTANT_Class_info for the
 *   inner class.
 *
 * outter_class_info_index
 *   A Constant Pool index to a CONSTANT_Class_info for the
 *   enclosing class, or zero if the inner class has no
 *   enclosing class.
 *
 * inner_name_index
 *   A Constant Pool index to a CONSTANT_Utf8_info for the
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
struct ATTRIBUTE_InnerClasses {
	u2 attribute_name_index;
	u2 number_of_classes;
	struct InnerClass *classes;
};

JRESULT ReadInnerClassesAttribute(FILE *file, struct ATTRIBUTE_InnerClasses *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   USEFUL: Enclosing Method Attribute                                 ////////////////////

/*
 * A structure for the Enclosing Method Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.7
 *
 * class_index
 *   A Constant Pool index to a CONSTANT_Class_info structure representing
 *   the innermost class that encloses the declaration of the current class.
 *
 * method_index
 *   A Constant Pool index to a CONSTANT_NameAndType_info structure
 *   representing the method referenced by the class mentioned above.
 */
struct ATTRIBUTE_EnclosingMethod {
	u2 attribute_name_index;
	u2 class_index;
	u2 method_index;
};

JRESULT ReadEnclosingMethodAttribute(FILE *file, struct ATTRIBUTE_EnclosingMethod *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   USEFUL: Synthetic Attribute                                        ////////////////////

/*
 * A structure denoting a synthetic element.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.8
 */
struct ATTRIBUTE_Synthetic {
	u2 attribute_name_index;
};

JRESULT ReadSyntheticAttribute(FILE *file, struct ATTRIBUTE_Synthetic *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   USEFUL: Signature Attribute                                        ////////////////////

/*
 * A structure for the Signature Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.9
 *
 * signature_index
 *   A Constant Pool index to a CONSTANT_Utf8_info structure
 *   representing the class, method, or field attribute.
 */
struct ATTRIBUTE_Signature {
	u2 attribute_name_index;
	u2 signature_index;
};

JRESULT ReadSignatureAttribute(FILE *file, struct ATTRIBUTE_Signature *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   USEFUL: Source File Attribute                                      ////////////////////

/*
 * A structure for the Source File Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.10
 *
 * sourcefile_index
 *   A Constant Pool index to a CONSTANT_Utf8_info structure
 *   for the name of the source file.
 */
struct ATTRIBUTE_SourceFile {
	u2 attribute_name_index;
	u2 sourcefile_index;
};

JRESULT ReadSourceFileAttribute(FILE *file, struct ATTRIBUTE_SourceFile *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   OPTIONAL: Source Debug Extension Attribute                         ////////////////////

/*
 * A structure for the Source Debug Extension Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.11
 *
 * debug_extension
 *   Modified UTF8 that holds extended debugging information.
 */
struct ATTRIBUTE_SourceDebugExtension {
	u2 attribute_name_index;
	char *debug_extension;
};

JRESULT ReadSourceDebugExtensionAttribute(FILE *file, struct ATTRIBUTE_SourceDebugExtension *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   USEFUL: Line Number Table Attribute                                ////////////////////

/*
 * A structure mapping line numbers to bytecode.
 *
 * start_pc
 *   An index into the code array at which the source begins.
 *
 * line_number
 *   The corresponding line number in the original source file.
 */
struct LineNumberEntry {
	u2 start_pc;
	u2 line_number;
};

/*
 * A structure for the Line Number Table Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.12
 *
 * line_number_table_length
 *   The number of elements in the line number table.
 *
 * line_number_table
 *   An array of line number entries.
 */
struct ATTRIBUTE_LineNumberTable {
	u2 attribute_name_index;
	u2 line_number_table_length;
	struct LineNumberEntry *line_number_table;
};

JRESULT ReadLineNumberTableAttribute(FILE *file, struct ATTRIBUTE_LineNumberTable *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   USEFUL: Local Variable Table Attribute                             ////////////////////

/*
 * A structure describing the value of a local variable during
 * method invocation.
 *
 * start_pc, length
 *   Together, these define the range in the bytecode array
 *   during which the local variable has a value. Specifically,
 *   the range is [start_pc, start_pc + length)
 *
 * name_index
 *   A Constant Pool index to a CONSTANT_Utf8_info containing
 *   the name of the local variable.
 *
 * descriptor_index
 *   A Constant Pool index to a CONSTANT_Utf8_info containing
 *   the field descriptor of the local variable.
 *
 * index
 *  An index into the local variable array of the current frame
 *  for the local variable. For variables of type double and long,
 *  the variable spans [index, index + 1]
 */
struct LocalVariableEntry {
	u2 start_pc;
	u2 length;
	u2 name_index;
	u2 descriptor_index;
	u2 index;
};

/*
 * A structure for the Local Variable Table Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.13
 *
 * local_variable_table_length
 *   The number of elements in the local variable table.
 *
 * local_variable_table
 *   An array of local variable entries.
 */
struct ATTRIBUTE_LocalVariableTable {
	u2 attribute_name_index;
	u2 local_variable_table_length;
	struct LocalVariableEntry *local_variable_table;
};

JRESULT ReadLocalVariableTableAttribute(FILE *file, struct ATTRIBUTE_LocalVariableTable *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   TODO USEFUL: Local Variable Type Table Attribute                   ////////////////////

////////////////////   OPTIONAL: Deprecated Attribute                                     ////////////////////

/*
 * A structure for the Deprecated Attribute.
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.15
 */
struct ATTRIBUTE_Deprecated {
	u2 attribute_name_index;
};

JRESULT ReadDeprecatedAttribute(FILE *file, struct ATTRIBUTE_Deprecated *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   TODO OPTIONAL: Runtime Visible Annotations Attribute               ////////////////////

////////////////////   TODO OPTIONAL: Runtime Invisible Annotations Attribute             ////////////////////

////////////////////   TODO OPTIONAL: Runtime Visible Parameter Annotations Attribute     ////////////////////

////////////////////   TODO OPTIONAL: Runtime Invisible Parameter Annotations Attribute   ////////////////////

////////////////////   TODO OPTIONAL: Runtime Visible Type Annotations Attribute          ////////////////////

////////////////////   TODO OPTIONAL: Runtime Invisible Type Annotations Attribute        ////////////////////

////////////////////   TODO OPTIONAL: Annotations Default Attribute                       ////////////////////

////////////////////   CRITICAL: Bootstrap Methods Attribute                              ////////////////////

/*
 * A structure describing a bootstrap method, used
 * to support dynamic languages.
 *
 * bootstrap_method_ref
 *   A Constant Pool index to a CONSTANT_MethodHandle_info describing
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
struct ATTRIBUTE_BootstrapMethods {
	u2 attribute_name_index;
	u2 num_bootstrap_methods;
	struct BootstrapMethod **bootstrap_methods;
};

JRESULT ReadBootstrapMethodsAttribute(FILE *file, struct ATTRIBUTE_BootstrapMethods *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   TODO OPTIONAL: Method Parameters Attribute                         ////////////////////

////////////////////   TODO OPTIONAL: Module Attribute                                    ////////////////////

////////////////////   TODO OPTIONAL: Module Packages Attribute                           ////////////////////

////////////////////   TODO OPTIONAL: Module Main Class Attribute                         ////////////////////

////////////////////   CRITICAL: Nest Host Attribute                                      ////////////////////

/*
 * A structure for the Nest Host Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.28
 *
 * host_class_index
 *   A Constant Pool index to a CONSTANT_Class_info structure representing
 *   a class that hosts the current class.
 */
struct ATTRIBUTE_NestHost {
	u2 attribute_name_index;
	u2 host_class_index;
};

JRESULT ReadNestHostAttribute(FILE *file, struct ATTRIBUTE_NestHost *attribute, u4 attribute_length, CONSTANT **constant_pool);

////////////////////   CRITICAL: Nest Members Attribute                                   ////////////////////

/*
 * A structure for the Nest Members Attribute
 * See https://docs.oracle.com/javase/specs/jvms/se14/html/jvms-4.html#jvms-4.7.29
 *
 * number_of_classes
 *   The number of elements in the classes array.
 *
 * classes
 *   An array of Constant Pool indices to CONSTANT_Class_info structures
 *   representing a class which is hosted by this current class.
 */
struct ATTRIBUTE_NestMembers {
	u2 attribute_name_index;
	u2 number_of_classes;
	u2 *classes;
};

JRESULT ReadNestMembersAttribute(FILE *file, struct ATTRIBUTE_NestMembers *attribute, u4 attribute_length, CONSTANT **constant_pool);

#endif /* CLASSFILEATTRIBUTES_H_ */
