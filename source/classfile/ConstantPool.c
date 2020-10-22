#include "classfile/ConstantPool.h"
#include <string.h>
#include <stdlib.h>

/*
 * This uses a linear allocation algorithm, the efficacy of which
 * is still in question.
 */
JRESULT ReadConstantPool(FILE *file, u2 constant_pool_count, CONSTANT **constant_pool)
{
	JRESULT r = 0;

	u1 curr_tag = 0;
	for (int i = 0; i < constant_pool_count; i++)
	{
		fread(&curr_tag, 1, 1, file);
		switch (curr_tag)
		{
		case CONSTANT_Class_info:
		case CONSTANT_String_info:
		case CONSTANT_MethodType_info:
		case CONSTANT_Module_info:
		case CONSTANT_Package_info: {
			CONSTANT_String *string_info = calloc(1, sizeof(CONSTANT_String));

			fread(&string_info->string_index, 2, 1, file);
			string_info->string_index = Big2(string_info->string_index);
			string_info->tag = curr_tag;

			constant_pool[i] = (CONSTANT *)string_info;
			break;
		}
		case CONSTANT_Fieldref_info:
		case CONSTANT_Methodref_info:
		case CONSTANT_InterfaceMethodref_info:
		case CONSTANT_NameAndType_info:
		case CONSTANT_Dynamic_info:
		case CONSTANT_InvokeDynamic_info: {
			CONSTANT_Fieldref *ref_info = calloc(1, sizeof(CONSTANT_Fieldref));

			fread(&ref_info->class_index, 2, 1, file);
			fread(&ref_info->name_and_type_index, 2, 1, file);
			ref_info->class_index = Big2(ref_info->class_index);
			ref_info->name_and_type_index = Big2(ref_info->name_and_type_index);
			ref_info->tag = curr_tag;

			constant_pool[i] = (CONSTANT *)ref_info;
			break;
		}
		case CONSTANT_Integer_info:
		case CONSTANT_Float_info: {
			CONSTANT_Integer *integer_info = calloc(1, sizeof(CONSTANT_Integer));

			fread(&integer_info->value, 4, 1, file);
			integer_info->value = Big4(integer_info->value);
			integer_info->tag = curr_tag;

			constant_pool[i] = (CONSTANT *)integer_info;
			break;
		}
		case CONSTANT_Long_info:
		case CONSTANT_Double_info: {
			CONSTANT_Long *long_info = calloc(1, sizeof(CONSTANT_Long));

			fread(&long_info->high, 4, 1, file);
			fread(&long_info->low, 4, 1, file);
			long_info->high = Big4(long_info->high);
			long_info->low = Big4(long_info->low);
			long_info->tag = curr_tag;

			constant_pool[i] = (CONSTANT *)long_info;
			break;
		}
		case CONSTANT_MethodHandle_info: {
			CONSTANT_MethodHandle *handle_info = calloc(1, sizeof(CONSTANT_MethodHandle));

			fread(&handle_info->reference_kind, 1, 1, file);
			fread(&handle_info->reference_index, 2, 1, file);
			handle_info->reference_index = Big2(handle_info->reference_index);
			handle_info->tag = curr_tag;

			constant_pool[i] = (CONSTANT *)handle_info;
			break;
		}
		case CONSTANT_Utf8_info: {
			u2 length = 0;
			fread(&length, 2, 1, file);
			length = Big2(length);

			CONSTANT_Utf8 *utf8_info = calloc(1, sizeof(CONSTANT_Utf8) + length + 1); //TODO remove leading null?

			fread(utf8_info->runes, 1, length, file);
			utf8_info->runes[length] = 0;
			utf8_info->length = length;
			utf8_info->tag = curr_tag;

			constant_pool[i] = (CONSTANT *)utf8_info;
			break;
		}
		default:
			return JRESULT_UNKNOWN_CONSTANT;
			break;
		}
	}
	return r;
}

void FreeConstantPool(u2 constant_pool_count, CONSTANT **constant_pool)
{
	if (constant_pool_count == 0 || constant_pool == NULL) return;
	for (int i = 0; i < constant_pool_count; i++)
	{
		free(constant_pool[i]);
		constant_pool[i] = NULL;
	}
}
