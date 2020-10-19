#ifndef CLASSFILEATTRIBUTES_H_
#define CLASSFILEATTRIBUTES_H_

#include "WideTypes.h"
#include "ClassfileConstantPool.h"
#include <stdio.h>

/*
 * This is the parent structure of all attributes defined in the
 * Java class file specification. Specifically, it is a header
 * used to resolve the type of attribute.
 *
 * attribute_name_index
 *   This is the index into the Constant Pool for the name of the attribute.
 *
 * info[]
 *   Names the data ahead of the struct, whose format is specific to the
 *   implementation and NOT the class file.
 */
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
 *   the file buffer must be at the start of an attribute stream.
 *   Must be non-NULL.
 *
 * attributes_count
 *   The number of attributes to parse from the file.
 *
 * attributes
 *   The vector of pointers to be populated. Must be at least as long as
 *   attributes_count elements.
 *
 * constant_pool
 *   The constant pool parsed earlier from the same file, needed to
 *   identify each attribute. Must be non-NULL.
 */
JRESULT ReadAttributes(FILE *file, u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool);

/*
 * This releases all memory for the vector of pointers populated by
 * GetAttributes, except for the vector itself.
 *
 * attributes
 *   The vector returned by ReadAttributes. Must be non-NULL.
 *
 * attributes_count
 *   The length the vector.
 *
 * constant_pool
 *   The constant pool used when creating attributes, needed to
 *   identify each attribute. Must be non-NULL.
 */
void FreeAttributes(ATTRIBUTE **attributes, u2 attributes_count, CONSTANT **constant_pool);


////////////////////   CRITICAL: Constant Value Attribute                                 ////////////////////


/*
 * A structure for the Constant Value attribute.
 *
 * attribute_name_index
 *   This is the index into the Constant Pool for the name of the attribute.
 *
 * constantvalue_index
 *   This is the index into the Constant Pool for the target constant.
 */
struct ATTRIBUTE_ConstantValue
{
	u2 attribute_name_index;
	u2 constantvalue_index;
};

JRESULT ReadConstantValueAttribute(FILE *file, struct ATTRIBUTE_ConstantValue *attribute, CONSTANT **constant_pool);


////////////////////   CRITICAL: Code Attribute                                           ////////////////////


struct ExceptionTable
{
	u2 start_pc;
	u2 end_pc;
	u2 handler_pc;
	u2 catch_type;
};

struct ATTRIBUTE_Code
{
	u2 attribute_name_index;
	u2 max_stack;
	u2 max_locals;
	u2 exception_table_length;
	struct ExceptionTable *exception_table;
	u4 code_length;
	bytecode *code;
	u2 attributes_count;
	ATTRIBUTE **attributes;
};

JRESULT ReadCodeAttribute(FILE *file, struct ATTRIBUTE_Code *attribute, CONSTANT **constant_pool);


////////////////////   CRITICAL: Stack Map Table Attribute                                ////////////////////


struct VerificationInfo
{
	u1 tag;
	u2 offset_or_cp_index;
};

struct StackMapFrame
{
	u1 frame_type;
	u1 data[];
};

struct StackMapFrame_same
{
	u1 frame_type; // 0 - 63
};

struct StackMapFrame_same_locals_1_stack_item
{
	u1 frame_type; // 64 - 127
	struct VerificationInfo stack;
};

struct StackMapFrame_same_locals_1_stack_item_ext
{
	u1 frame_type; // 247
	u2 offset_delta;
	struct VerificationInfo stack;
};

struct StackMapFrame_chop
{
	u1 frame_type; // 248 - 250
	u2 offset_delta;
};

struct StackMapFrame_same_ext
{
	u1 frame_type; // 251
	u2 offset_delta;
};

struct StackMapFrame_append
{
	u1 frame_type; // 252 - 254
	u2 offset_delta;
	struct VerificationInfo *locals; // [frame_type - 251]
};

struct StackMapFrame_full
{
	u1 frame_type; // 255
	u2 offset_delta;
	u2 number_of_locals;
	struct VerificationInfo *locals;
	u2 number_of_stack_items;
	struct VerificationInfo *stack;
};

struct ATTRIBUTE_StackMapTable
{
	u2 attribute_name_index;
	u2 number_of_entries;
	struct StackMapFrame **entries;
};

JRESULT ReadStackMapTableAttribute(FILE *file, struct ATTRIBUTE_StackMapTable *attribute, CONSTANT **constant_pool);
JRESULT ReadVerificationInfo(FILE *file, struct VerificationInfo *vi, u2 number_of_items);


////////////////////   USEFUL: Exceptions Attribute                                       ////////////////////


struct ATTRIBUTE_Exceptions
{
	u2 attribute_name_index;
	u2 number_of_exceptions;
	u2 *exception_index_table;
};

JRESULT ReadExceptionsAttribute(FILE *file, struct ATTRIBUTE_Exceptions *attribute, CONSTANT **constant_pool);


////////////////////   USEFUL: Inner Classes Attribute                                    ////////////////////


struct InnerClass
{
	u2 inner_class_info_index;
	u2 outer_class_info_index;
	u2 inner_name_index;
	u2 inner_class_access_flags;
};

struct ATTRIBUTE_InnerClasses
{
	u2 attribute_name_index;
	u2 number_of_classes;
	struct InnerClass *classes;
};

JRESULT ReadInnerClassesAttribute(FILE *file, struct ATTRIBUTE_InnerClasses *attribute, CONSTANT **constant_pool);


////////////////////   USEFUL: Enclosing Method Attribute                                 ////////////////////


struct ATTRIBUTE_EnclosingMethod
{
	u2 attribute_name_index;
	u2 class_index;
	u2 method_index;
};

JRESULT ReadEnclosingMethodAttribute(FILE *file, struct ATTRIBUTE_EnclosingMethod *attribute, CONSTANT **constant_pool);


////////////////////   USEFUL: Synthetic Attribute                                        ////////////////////


struct ATTRIBUTE_Synthetic
{
	u2 attribute_name_index;
};

JRESULT ReadSyntheticAttribute(FILE *file, struct ATTRIBUTE_Synthetic *attribute, CONSTANT **constant_pool);


////////////////////   USEFUL: Signature Attribute                                        ////////////////////


struct ATTRIBUTE_Signature
{
	u2 attribute_name_index;
	u2 signature_index;
};

JRESULT ReadSignatureAttribute(FILE *file, struct ATTRIBUTE_Signature *attribute, CONSTANT **constant_pool);


////////////////////   USEFUL: Source File Attribute                                      ////////////////////


struct ATTRIBUTE_SourceFile
{
	u2 attribute_name_index;
	u2 sourcefile_index;
};

JRESULT ReadSourceFileAttribute(FILE *file, struct ATTRIBUTE_SourceFile *attribute);


////////////////////   OPTIONAL: Source Debug Extension Attribute                         ////////////////////


struct ATTRIBUTE_SourceDebugExtension
{
	u2 attribute_name_index;
	char *debug_extension;;
};

JRESULT ReadSourceDebugExtensionAttribute(FILE *file, struct ATTRIBUTE_SourceDebugExtension *attribute, CONSTANT **constant_pool);


////////////////////   USEFUL: Line Number Table Attribute                                ////////////////////


struct LineNumberEntry
{
	u2 start_pc;
	u2 line_number;
};

struct ATTRIBUTE_LineNumberTable
{
	u2 attribute_name_index;
	u2 line_number_table_length;
	struct LineNumberEntry *line_number_table;
};

JRESULT ReadLineNumberTableAttribute(FILE* file, struct ATTRIBUTE_LineNumberTable *attribute);


////////////////////   USEFUL: Local Variable Table Attribute                             ////////////////////


struct LocalVariableEntry
{
	u2 start_pc;
	u2 length;
	u2 name_index;
	u2 descriptor_index;
	u2 index;
};

struct ATTRIBUTE_LocalVariableTable
{
	u2 attribute_name_index;
	struct LocalVariableEntry *local_variable_table;
};

JRESULT ReadLocalVariableTableAttribute(FILE* file, struct ATTRIBUTE_LocalVariableTable *attribute);


////////////////////   TODO USEFUL: Local Variable Type Table Attribute                   ////////////////////


////////////////////   OPTIONAL: Deprecated Attribute                                     ////////////////////


struct ATTRIBUTE_Deprecated
{
	u2 attribute_name_index;
};

JRESULT ReadDeprecatedAttribute(FILE *file, struct ATTRIBUTE_Deprecated *attribute, CONSTANT **constant_pool);


////////////////////   TODO OPTIONAL: Runtime Visible Annotations Attribute               ////////////////////


////////////////////   TODO OPTIONAL: Runtime Invisible Annotations Attribute             ////////////////////


////////////////////   TODO OPTIONAL: Runtime Visible Parameter Annotations Attribute     ////////////////////


////////////////////   TODO OPTIONAL: Runtime Invisible Parameter Annotations Attribute   ////////////////////


////////////////////   TODO OPTIONAL: Runtime Visible Type Annotations Attribute          ////////////////////


////////////////////   TODO OPTIONAL: Runtime Invisible Type Annotations Attribute        ////////////////////


////////////////////   TODO OPTIONAL: Annotations Default Attribute                       ////////////////////


////////////////////   CRITICAL: Bootstrap Methods Attribute                              ////////////////////


struct BootstrapMethod
{
	u2 bootstrap_method_ref;
	u2 num_bootstrap_arguments;
	u2 bootstrap_arguments[];
};

struct ATTRIBUTE_BootstrapMethods
{
	u2 attribute_name_index;
	u2 num_bootstrap_methods;
	struct BootstrapMethod **bootstrap_methods;
};

JRESULT ReadBootstrapMethodsAttribute(FILE *file, struct ATTRIBUTE_BootstrapMethods *attribute, CONSTANT **constant_pool);


////////////////////   TODO OPTIONAL: Method Parameters Attribute                         ////////////////////


////////////////////   TODO OPTIONAL: Module Attribute                                    ////////////////////


////////////////////   TODO OPTIONAL: Module Packages Attribute                           ////////////////////


////////////////////   TODO OPTIONAL: Module Main Class Attribute                         ////////////////////


////////////////////   CRITICAL: Nest Host Attribute                                      ////////////////////


struct ATTRIBUTE_NestHost
{
	u2 attribute_name_index;
	u2 host_class_index;
};

JRESULT ReadNestHostAttribute(FILE *file, struct ATTRIBUTE_NestHost *attribute, CONSTANT **constant_pool);


////////////////////   CRITICAL: Nest Members Attribute                                   ////////////////////


struct ATTRIBUTE_NestMembers
{
	u2 attribute_name_index;
	u2 number_of_classes;
	u2 *classes;
};

JRESULT ReadNestMembersAttribute(FILE *file, struct ATTRIBUTE_NestMembers *attribute, CONSTANT **constant_pool);

#endif /* CLASSFILEATTRIBUTES_H_ */
