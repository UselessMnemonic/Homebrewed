#include <string.h>
#include <stdio.h>
#include <3ds.h>

#include "Homebrewed.h"

void printAttributes(ATTRIBUTE **attributes, u2 num_items, const char *indentation)
{
	for (int i = 0; i < num_items; i++)
	{
		ATTRIBUTE *curr_attribute = attributes[i];
		printf("%s#%d)\tName @ #%d\n", indentation, i+1, curr_attribute->attribute_name_index);
	}
}

int main(int argc, char** argv)
{
	freopen("stdout.txt", "w", stdout);
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// load example class
	CLASSFILE clazz;
	FILE *file = fopen("Main.class", "rb");

	if (file == NULL)
	{
		printf("No such file \"Main.class\"");
	}

	if (ReadClassfile(file, &clazz))
	{
		printf("Unexpected error.");
	}
	else
	{
		printf("Magic is 0x%04lX\n", clazz.magic);
		printf("Minor Version: %u\n", clazz.minor_version);
		printf("Major Version: %u\n", clazz.major_version);
		printf("Constant Pool Count: %u\n", clazz.constant_pool_count);
		for (int i = 0; i < clazz.constant_pool_count - 1; i++)
		{
			CONSTANT *cp_info = clazz.constant_pool[i];
			if (cp_info) switch (cp_info->tag)
			{
				case CONSTANT_Integer:
				{
					struct CONSTANT_Integer_info *int_info = (struct CONSTANT_Integer_info *)cp_info;
					printf("\t#%d) Integer Constant: %d\n", i+1, (int)int_info->value);
					break;
				}
				case CONSTANT_Float:
				{
					struct CONSTANT_Float_info *float_info = (struct CONSTANT_Float_info *)cp_info;
					printf("\t#%d) Float Constant: %f\n", i+1, (float)float_info->value);
					break;
				}
				case CONSTANT_Long:
				{
					struct CONSTANT_Long_info *long_info = (struct CONSTANT_Long_info *)cp_info;
					uint64_t temp = long_info->high;
					temp <<= 32;
					temp |= long_info->low;
					printf("\t#%d) Long Constant: %ld\n", i+1, (long)temp);
					break;
				}
				case CONSTANT_Double:
				{
					struct CONSTANT_Double_info *long_info = (struct CONSTANT_Double_info *)cp_info;
					uint64_t temp = long_info->high;
					temp <<= 32;
					temp |= long_info->low;
					printf("\t#%d) Double Constant: %lf\n", i+1, (double)temp);
					break;
				}
				case CONSTANT_String:
				{
					struct CONSTANT_String_info *string_info = (struct CONSTANT_String_info *)cp_info;
					printf("\t#%d) String Reference\n\t\tName @ %u\n", i+1, string_info->string_index);
					break;
				}
				case CONSTANT_Class:
				{
					struct CONSTANT_Class_info *class_info = (struct CONSTANT_Class_info *)cp_info;
					printf("\t#%d) Class Reference\n\t\tName @ %u\n", i+1, class_info->name_index);
					break;
				}
				case CONSTANT_Fieldref:
				{
					struct CONSTANT_Fieldref_info *field_info = (struct CONSTANT_Fieldref_info *)cp_info;
					printf("\t#%d) Field Reference\n\t\tClass @ %u\n\t\tName and Type @ %u\n", i+1, field_info->class_index, field_info->name_and_type_index);
					break;
				}
				case CONSTANT_Methodref:
				{
					struct CONSTANT_Methodref_info *method_info = (struct CONSTANT_Methodref_info *)cp_info;
					printf("\t#%d) Method Reference\n\t\tClass @ %u\n\t\tName and Type @ %u\n", i+1, method_info->class_index, method_info->name_and_type_index);
					break;
				}
				case CONSTANT_InterfaceMethodref:
				{
					struct CONSTANT_InterfaceMethodref_info *interface_info = (struct CONSTANT_InterfaceMethodref_info *)cp_info;
					printf("\t#%d) Interface Method Reference\n\t\tClass @ %u\n\t\tName and Type @ %u\n", i+1, interface_info->class_index, interface_info->name_and_type_index);
					break;
				}
				case CONSTANT_NameAndType:
				{
					struct CONSTANT_NameAndType_info *name_and_type_info = (struct CONSTANT_NameAndType_info *)cp_info;
					printf("\t#%d) Name and Type\n\t\tName @ %u\n\t\tDescriptor @ %u\n", i+1, name_and_type_info->name_index, name_and_type_info->descriptor_index);
					break;
				}
				case CONSTANT_Utf8:
				{
					struct CONSTANT_Utf8_info *utf8_info = (struct CONSTANT_Utf8_info *)cp_info;
					printf("\t#%d) UTF-8 Constant: \"%s\"\n", i+1, utf8_info->runes);
					break;
				}

				default:
					printf("\t#%d) Undefined Constant Tag %02X\n", i+1, cp_info->tag);
			}
		}
		printf("Access Flags: 0x%02X\n", clazz.access_flags);
		printf("Class ID: #%u\n", clazz.this_class);
		printf("Superclass ID: #%u\n", clazz.super_class);
		printf("Interfaces Count: %u\n", clazz.interfaces_count);
		for (int i = 0; i < clazz.interfaces_count; i++)
		{
			printf("\tInterface @ Constant #%d", clazz.interfaces[i]);
		}
		printf("Fields Count: %u\n", clazz.fields_count);
		for (int i = 0; i < clazz.fields_count; i++)
		{
			FIELD *field = &clazz.fields[i];
			printf("\t#%d)\tAccess Flags: 0x%02X\n", i+1, field->access_flags);
			printf("\t\tName @ #%d\n", field->name_index);
			printf("\t\tDescriptor @ #%d\n", field->descriptor_index);
			printf("\t\tAttributes Count: %u\n", field->attributes_count);
			printAttributes(field->attributes, field->attributes_count, "\t\t\t");
		}
		printf("Methods Count: %u\n", clazz.methods_count);
		for (int i = 0; i < clazz.methods_count; i++)
		{
			METHOD *method = &clazz.methods[i];
			printf("\t#%d)\tAccess Flags: 0x%02X\n", i+1, method->access_flags);
			printf("\t\tName @ #%d\n", method->name_index);
			printf("\t\tDescriptor @ #%d\n", method->descriptor_index);
			printf("\t\tAttributes Count: %u\n", method->attributes_count);
			printAttributes(method->attributes, method->attributes_count, "\t\t\t");
		}
		printf("Attributes Count: %u\n", clazz.attributes_count);
		printAttributes(clazz.attributes, clazz.attributes_count, "\t");
	}

	fclose(file);

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}
