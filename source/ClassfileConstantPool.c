#include <string.h>
#include <stdlib.h>
#include "ClassfileConstantPool.h"

JRESULT ReadConstantPool(FILE *file, CONSTANT **constant_pool, u2 num_items)
{
	JRESULT r = 0;
	void *cp_block = NULL;
	size_t cp_block_size = 0;

	u1 curr_tag;
	size_t cp_offset = 0;
	size_t offsets[num_items];
	for (int i = 0; i < num_items; i++)
	{
		fread(&curr_tag, 1, 1, file);
		switch (curr_tag)
		{
			case CONSTANT_Class:
			case CONSTANT_String:
			case CONSTANT_MethodType:
			case CONSTANT_Module:
			case CONSTANT_Package:
				cp_block = realloc(cp_block, cp_block_size += sizeof(struct CONSTANT_String_info));
				struct CONSTANT_String_info *string_info = cp_block + cp_offset;
				offsets[i] = cp_offset;
				cp_offset += sizeof(struct CONSTANT_String_info);

				fread(&string_info->string_index, 2, 1, file);
				string_info->string_index = Big2(string_info->string_index);
				string_info->tag = curr_tag;
				break;

			case CONSTANT_Fieldref:
			case CONSTANT_Methodref:
			case CONSTANT_InterfaceMethodref:
			case CONSTANT_NameAndType:
			case CONSTANT_Dynamic:
			case CONSTANT_InvokeDynamic:
				cp_block = realloc(cp_block, cp_block_size += sizeof(struct CONSTANT_Fieldref_info));
				struct CONSTANT_Fieldref_info *ref_info = cp_block + cp_offset;
				offsets[i] = cp_offset;
				cp_offset += sizeof(struct CONSTANT_Fieldref_info);

				fread(&ref_info->class_index, 2, 1, file);
				fread(&ref_info->name_and_type_index, 2, 1, file);
				ref_info->class_index = Big2(ref_info->class_index);
				ref_info->name_and_type_index = Big2(ref_info->name_and_type_index);
				ref_info->tag = curr_tag;
				break;

			case CONSTANT_Integer:
			case CONSTANT_Float:
				cp_block = realloc(cp_block, cp_block_size += sizeof(struct CONSTANT_Integer_info));
				struct CONSTANT_Integer_info *int_info = cp_block + cp_offset;
				offsets[i] = cp_offset;
				cp_offset += sizeof(struct CONSTANT_Integer_info);

				fread(&int_info->value, 4, 1, file);
				int_info->value = Big4(int_info->value);
				int_info->tag = curr_tag;
				break;

			case CONSTANT_Long:
			case CONSTANT_Double:
				cp_block = realloc(cp_block, cp_block_size += sizeof(struct CONSTANT_Long_info));
				struct CONSTANT_Long_info *long_info = cp_block + cp_offset;
				offsets[i] = cp_offset;
				cp_offset += sizeof(struct CONSTANT_Long_info);

				fread(&long_info->high, 4, 1, file);
				fread(&long_info->low, 4, 1, file);
				long_info->high = Big4(long_info->high);
				long_info->low = Big4(long_info->low);
				long_info->tag = curr_tag;
				break;

			case CONSTANT_Utf8:
				cp_block = realloc(cp_block, cp_block_size += sizeof(struct CONSTANT_Utf8_info));
				struct CONSTANT_Utf8_info *utf8_info = cp_block + cp_offset;
				offsets[i] = cp_offset;
				cp_offset += sizeof(struct CONSTANT_Utf8_info);

				fread(&utf8_info->length, 2, 1, file);
				utf8_info->length = Big2(utf8_info->length);
				utf8_info->tag = curr_tag;

				cp_block = realloc(cp_block, cp_block_size += utf8_info->length + 1);
				cp_offset += utf8_info->length + 1;

				fread (utf8_info->runes, 1, utf8_info->length, file);
				utf8_info->runes[utf8_info->length] = 0;
				break;

			case CONSTANT_MethodHandle:
				cp_block = realloc(cp_block, cp_block_size += sizeof(struct CONSTANT_MethodHandle_info));
				struct CONSTANT_MethodHandle_info *handle_info = cp_block + cp_offset;
				offsets[i] = cp_offset;
				cp_offset += sizeof(struct CONSTANT_MethodHandle_info);

				fread(&handle_info->reference_kind, 1, 1, file);
				fread(&handle_info->reference_index, 2, 1, file);
				handle_info->reference_index = Big2(handle_info->reference_index);
				handle_info->tag = curr_tag;
				break;

			default:
				return JRESULT_UNKNOWN_CONSTANT;
				break;
		}
	}
	for (int i = 0; i < num_items; i++)
	{
		constant_pool[i] = cp_block + offsets[i];
	}
	return r;
}

void FreeConstantPool(CONSTANT **constant_pool)
{
	free(constant_pool[0]);
	free(constant_pool);
}
