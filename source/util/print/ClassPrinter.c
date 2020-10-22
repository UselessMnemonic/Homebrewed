#include "util/print/ClassPrinter.h"
#include "classfile/attributes/Unknown.h"
#include <stdio.h>
#include <string.h>

void _PrintIndent(size_t indent)
{
	while(indent-- != 0) putchar('\t');
}

void _PrintConstantPool(u2 constant_pool_count, CONSTANT **constant_pool, size_t indent)
{
	for (int i = 0; i < constant_pool_count - 1; i++)
	{
		CONSTANT *cp_info = constant_pool[i];
		if (cp_info) switch (cp_info->tag)
		{
		case CONSTANT_Integer_info:
		{
			CONSTANT_Integer *int_info = (CONSTANT_Integer *)cp_info;
			_PrintIndent(indent); printf("[#%d] Integer Constant: %d\n", i+1, (int)int_info->value);
			break;
		}
		case CONSTANT_Float_info:
		{
			CONSTANT_Float *float_info = (CONSTANT_Float *)cp_info;
			_PrintIndent(indent); printf("[#%d] Float Constant: %f\n", i+1, (float)float_info->value);
			break;
		}
		case CONSTANT_Long_info:
		{
			CONSTANT_Long *long_info = (CONSTANT_Long *)cp_info;
			uint64_t temp = long_info->high;
			temp <<= 32;
			temp |= long_info->low;
			_PrintIndent(indent); printf("[#%d] Long Constant: %ld\n", i+1, (long)temp);
			break;
		}
		case CONSTANT_Double_info:
		{
			CONSTANT_Double *long_info = (CONSTANT_Double *)cp_info;
			uint64_t temp = long_info->high;
			temp <<= 32;
			temp |= long_info->low;
			_PrintIndent(indent); printf("[#%d] Double Constant: %lf\n", i+1, (double)temp);
			break;
		}
		case CONSTANT_String_info:
		{
			CONSTANT_String *string_info = (CONSTANT_String *)cp_info;
			_PrintIndent(indent); printf("[#%d] String Reference:\n", i+1);
			_PrintIndent(indent+1); printf("Name @ %u\n", string_info->string_index);
			break;
		}
		case CONSTANT_Class_info:
		{
			CONSTANT_Class *class_info = (CONSTANT_Class *)cp_info;
			_PrintIndent(indent); printf("[#%d] Class Reference:\n", i+1);
			_PrintIndent(indent+1); printf("Name @ %u\n", class_info->name_index);
			break;
		}
		case CONSTANT_Fieldref_info:
		{
			CONSTANT_Fieldref *field_info = (CONSTANT_Fieldref *)cp_info;
			_PrintIndent(indent); printf("[#%d] Field Reference:\n", i+1);
			_PrintIndent(indent+1); printf("Class @ %u\n", field_info->class_index);
			_PrintIndent(indent+1); printf("Name and Type @ %u\n", field_info->name_and_type_index);
			break;
		}
		case CONSTANT_Methodref_info:
		{
			CONSTANT_Methodref *method_info = (CONSTANT_Methodref *)cp_info;
			_PrintIndent(indent); printf("[#%d] Method Reference:\n", i+1);
			_PrintIndent(indent+1); printf("Class @ %u\n", method_info->class_index);
			_PrintIndent(indent+1); printf("Name and Type @ %u\n", method_info->name_and_type_index);
			break;
		}
		case CONSTANT_InterfaceMethodref_info:
		{
			CONSTANT_InterfaceMethodref *interface_info = (CONSTANT_InterfaceMethodref *)cp_info;
			_PrintIndent(indent); printf("[#%d] Interface Method Reference:\n", i+1);
			_PrintIndent(indent+1); printf("Class @ %u\n", interface_info->class_index);
			_PrintIndent(indent+1); printf("Name and Type @ %u\n", interface_info->name_and_type_index);
			break;
		}
		case CONSTANT_NameAndType_info:
		{
			CONSTANT_NameAndType *name_and_type_info = (CONSTANT_NameAndType *)cp_info;
			_PrintIndent(indent); printf("[#%d] Name and Type:\n", i+1);
			_PrintIndent(indent+1); printf("Name @ %u\n", name_and_type_info->name_index);
			_PrintIndent(indent+1); printf("Descriptor @ %u\n", name_and_type_info->descriptor_index);
			break;
		}
		case CONSTANT_Utf8_info:
		{
			CONSTANT_Utf8 *utf8_info = (CONSTANT_Utf8 *)cp_info;
			_PrintIndent(indent); printf("[#%d] UTF-8 Constant: \"%s\"\n", i+1, utf8_info->runes);
			break;
		}
		}
	}
}

void _PrintAttribute_ConstantValue(ATTRIBUTE_ConstantValue *attribute, CONSTANT **constant_pool, size_t indent)
{
}

void _PrintAttribute_Code(ATTRIBUTE_Code *attribute, CONSTANT **constant_pool, size_t indent)
{
}

void _PrintAttribute_StackMapTable(ATTRIBUTE_StackMapTable *attribute, CONSTANT **constant_pool, size_t indent)
{
}

void _PrintAttribute_BootstrapMethods(ATTRIBUTE_BootstrapMethods *attribute, CONSTANT **constant_pool, size_t indent)
{
}

void _PrintAttribute_NestHost(ATTRIBUTE_NestHost *attribute, CONSTANT **constant_pool, size_t indent)
{
}

void _PrintAttribute_NestMembers(ATTRIBUTE_NestMembers *attribute, CONSTANT **constant_pool, size_t indent)
{
}

void _PrintAttributes(u2 attributes_count, ATTRIBUTE **attributes, CONSTANT **constant_pool, size_t indent)
{
	for (int i = 0; i < attributes_count; i++)
	{
		// resolve attribute name and check if supported
		// TODO replace with Modified-UTF8-safe code
		u2 name_index = attributes[i]->attribute_name_index;
		const char *attribute_name =
				(const char *)((CONSTANT_Utf8*) constant_pool[name_index - 1])->runes;

		void (*_PrintAttributeFunction)(ATTRIBUTE*, CONSTANT**, size_t) = NULL;

		// find which attribute is being read
		if (strcmp(attribute_name, "ConstantValue") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_ConstantValue;
		}
		else if (strcmp(attribute_name, "Code") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_Code;
		}
		else if (strcmp(attribute_name, "StackMapTable") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_StackMapTable;
		}
		else if (strcmp(attribute_name, "BootstrapMethods") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_BootstrapMethods;
		}
		else if (strcmp(attribute_name, "NestHost") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_NestHost;
		}
		else if (strcmp(attribute_name, "NestMembers") == 0)
		{
			_PrintAttributeFunction = (void *)_PrintAttribute_NestMembers;
		}
		else
		{
			_PrintAttributeFunction = NULL;
			ATTRIBUTE_Unknown *unk = (ATTRIBUTE_Unknown *)attributes[i];
			_PrintIndent(indent); printf("Unknown Attribute \"%s\" (%d bytes)\n", attribute_name, unk->attribute_length);
		}

		if (_PrintAttributeFunction != NULL)
		{
			_PrintIndent(indent); printf("%s Attribute {\n", attribute_name);
			_PrintAttributeFunction(attributes[i], constant_pool, indent+1);
			_PrintIndent(indent); printf("}\n");
		}
	}
}

void _PrintFields(u2 fields_count, FIELD *fields, CONSTANT **constant_pool, size_t indent)
{
	for (int i = 0; i < fields_count; i++)
	{
		FIELD *field = &fields[i];
		_PrintIndent(indent); printf("{\n");
		_PrintIndent(indent); printf("Access Flags: 0x%02X\n", field->access_flags);
		_PrintIndent(indent); printf("Descriptor @ #%d\n", field->descriptor_index);
		_PrintIndent(indent); printf("Attributes Count: %u\n", field->attributes_count);
		_PrintAttributes(field->attributes_count, field->attributes, constant_pool, indent);
		_PrintIndent(indent); printf("}\n");
	}
}

void _PrintMethods(u2 methods_count, METHOD *methods, CONSTANT **constant_pool, size_t indent)
{
	for (int i = 0; i < methods_count; i++)
	{
		METHOD *method = &methods[i];
		_PrintIndent(indent); printf("{\n");
		_PrintIndent(indent); printf("Access Flags: 0x%02X\n", method->access_flags);
		_PrintIndent(indent); printf("Descriptor @ #%d\n", method->descriptor_index);
		_PrintIndent(indent); printf("Attributes Count: %u\n", method->attributes_count);
		_PrintAttributes(method->attributes_count, method->attributes, constant_pool, indent+1);
		_PrintIndent(indent); printf("}\n");
	}
}

void _PrintClass(CLASS *clazz, size_t indent)
{
	_PrintIndent(indent); printf("Constant Pool Count: %u\n", clazz->constant_pool_count);
	_PrintConstantPool(clazz->constant_pool_count, clazz->constant_pool, indent+1);

	_PrintIndent(indent); printf("Access Flags: 0x%02X\n", clazz->access_flags);
	_PrintIndent(indent); printf("Class ID: #%u\n", clazz->this_class_name_index);
	_PrintIndent(indent); printf("Superclass ID: #%u\n", clazz->super_class_name_index);
	_PrintIndent(indent); printf("Interfaces Count: %u\n", clazz->interfaces_count);
	for (int i = 0; i < clazz->interfaces_count; i++)
	{
		_PrintIndent(indent+1); printf("Interface @ #%d", clazz->interface_name_indices[i]);
	}

	_PrintIndent(indent); printf("Fields Count: %u\n", clazz->fields_count);
	_PrintFields(clazz->fields_count, clazz->fields, clazz->constant_pool, indent+1);

	_PrintIndent(indent); printf("Methods Count: %u\n", clazz->methods_count);
	_PrintMethods(clazz->methods_count, clazz->methods, clazz->constant_pool, indent+1);

	_PrintIndent(indent); printf("Attributes Count: %u\n", clazz->attributes_count);
	_PrintAttributes(clazz->attributes_count, clazz->attributes, clazz->constant_pool, indent+1);
}

void PrintClass(CLASS *clazz)
{
	_PrintClass(clazz, 0);
}
