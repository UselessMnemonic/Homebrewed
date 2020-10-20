#include <string.h>
#include <stdlib.h>

#include "classfile/ConstantPool.h"

JRESULT ReadConstantPool(FILE *file, u2 constant_pool_count, CONSTANT **constant_pool)
{
	JRESULT r = 0;
	void *cp_block = NULL;
	size_t cp_block_size = 0;

	u1 curr_tag;
	size_t offsets[constant_pool_count];
	for (int i = 0; i < constant_pool_count; i++)
	{
		fread(&curr_tag, 1, 1, file);
		switch (curr_tag)
		{
		case CONSTANT_Class_info:
		case CONSTANT_String_info:
		case CONSTANT_MethodType_info:
		case CONSTANT_Module_info:
		case CONSTANT_Package_info:
			offsets[i] = cp_block_size;
			cp_block = realloc(cp_block, cp_block_size += sizeof(CONSTANT_String));
			CONSTANT_String *string_info = cp_block + offsets[i];

			fread(&string_info->string_index, 2, 1, file);
			string_info->string_index = Big2(string_info->string_index);
			string_info->tag = curr_tag;
			break;

		case CONSTANT_Fieldref_info:
		case CONSTANT_Methodref_info:
		case CONSTANT_InterfaceMethodref_info:
		case CONSTANT_NameAndType_info:
		case CONSTANT_Dynamic_info:
		case CONSTANT_InvokeDynamic_info:
			offsets[i] = cp_block_size;
			cp_block = realloc(cp_block, cp_block_size += sizeof(CONSTANT_Fieldref));
			CONSTANT_Fieldref *ref_info = cp_block + offsets[i];

			fread(&ref_info->class_index, 2, 1, file);
			fread(&ref_info->name_and_type_index, 2, 1, file);
			ref_info->class_index = Big2(ref_info->class_index);
			ref_info->name_and_type_index = Big2(ref_info->name_and_type_index);
			ref_info->tag = curr_tag;
			break;

		case CONSTANT_Integer_info:
		case CONSTANT_Float_info:
			offsets[i] = cp_block_size;
			cp_block = realloc(cp_block, cp_block_size += sizeof(CONSTANT_Integer));
			CONSTANT_Integer *integer_info = cp_block + offsets[i];

			fread(&integer_info->value, 4, 1, file);
			integer_info->value = Big4(integer_info->value);
			integer_info->tag = curr_tag;
			break;

		case CONSTANT_Long_info:
		case CONSTANT_Double_info:
			offsets[i] = cp_block_size;
			cp_block = realloc(cp_block, cp_block_size += sizeof(CONSTANT_Long));
			CONSTANT_Long *long_info = cp_block + offsets[i];

			fread(&long_info->high, 4, 1, file);
			fread(&long_info->low, 4, 1, file);
			long_info->high = Big4(long_info->high);
			long_info->low = Big4(long_info->low);
			long_info->tag = curr_tag;
			break;

		case CONSTANT_MethodHandle_info:
			offsets[i] = cp_block_size;
			cp_block = realloc(cp_block, cp_block_size += sizeof(CONSTANT_MethodHandle));
			CONSTANT_MethodHandle *handle_info = cp_block + offsets[i];

			fread(&handle_info->reference_kind, 1, 1, file);
			fread(&handle_info->reference_index, 2, 1, file);
			handle_info->reference_index = Big2(handle_info->reference_index);
			handle_info->tag = curr_tag;
			break;

		case CONSTANT_Utf8_info: {
			u2 length = 0;
			fread(&length, 2, 1, file);
			length = Big2(length);

			offsets[i] = cp_block_size;
			cp_block = realloc(cp_block, cp_block_size += sizeof(CONSTANT_Utf8) + length + 1); //TODO remove leading null?
			CONSTANT_Utf8 *utf8_info = cp_block + offsets[i];

			fread (utf8_info->runes, 1, length, file);
			utf8_info->runes[utf8_info->length] = 0;
			utf8_info->length = length;
			utf8_info->tag = curr_tag;
			break;
		}
		default:
			return JRESULT_UNKNOWN_CONSTANT;
			break;
		}
	}
	for (int i = 0; i < constant_pool_count; i++)
	{
		constant_pool[i] = cp_block + offsets[i];
	}
	return r;
}

void FreeConstantPool(CONSTANT **constant_pool)
{
	free(constant_pool[0]);
}
