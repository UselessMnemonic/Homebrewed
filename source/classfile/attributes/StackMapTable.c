#include "classfile/attributes/StackMapTable.h"
#include <stdlib.h>
#include <stdio.h>

JRESULT ReadVerificationInfo(FILE *file, struct VerificationInfo *vi, u2 number_of_items)
{
	JRESULT r = 0;

	for (int i = 0; i < number_of_items; i++)
	{
		fread(&(vi[i].tag), 1, 1, file);
		fread(&(vi[i].offset_or_cp_index), 1, 2, file);
		vi[i].offset_or_cp_index = Big2(vi[i].offset_or_cp_index);
	}

	return r;
}

JRESULT ReadStackFrames(FILE *file, struct StackMapFrame **frames, u2 number_of_entries)
{
	JRESULT r = 0;

	u1 curr_frame_type = 0;

	for (int i = 0; i < number_of_entries; i++)
	{
		fread(&curr_frame_type, 1, 1, file);

		if (curr_frame_type <= 63) // same
		{
			struct StackMapFrame_same *same = calloc(1, sizeof(struct StackMapFrame_same));
			same->frame_type = curr_frame_type;

			frames[i] = (struct StackMapFrame *)same;
		}

		else if (curr_frame_type <= 127) // same_locals
		{
			struct StackMapFrame_same_locals *same_locals = calloc(1, sizeof(struct StackMapFrame_same_locals));
			same_locals->frame_type = curr_frame_type;

			r = ReadVerificationInfo(file, &same_locals->stack, 1);

			frames[i] = (struct StackMapFrame *)same_locals;
		}

		else if (curr_frame_type <= 246) // unused
		{
			r = JRESULT_UNKNOWN_STACK_FRAME;
		}

		else if (curr_frame_type == 247) // same_locals_ext
		{
			struct StackMapFrame_same_locals_ext *same_locals_ext = calloc(1, sizeof(struct StackMapFrame_same_locals_ext));
			same_locals_ext->frame_type = curr_frame_type;

			fread(&same_locals_ext->offset_delta, 2, 1, file);
			same_locals_ext->offset_delta = Big2(same_locals_ext->offset_delta);

			r = ReadVerificationInfo(file, &same_locals_ext->stack, 1);

			frames[i] = (struct StackMapFrame *)same_locals_ext;
		}

		else if (curr_frame_type <= 250) // chop
		{
			struct StackMapFrame_chop *chop = calloc(1, sizeof(struct StackMapFrame_chop));
			chop->frame_type = curr_frame_type;

			fread(&chop->offset_delta, 2, 1, file);
			chop->offset_delta = Big2(chop->offset_delta);

			frames[i] = (struct StackMapFrame *)chop;
		}

		else if (curr_frame_type == 251) // same_ext
		{
			struct StackMapFrame_same_ext *same_ext = calloc(1, sizeof(struct StackMapFrame_same_ext));
			same_ext->frame_type = curr_frame_type;

			fread(&same_ext->offset_delta, 2, 1, file);
			same_ext->offset_delta = Big2(same_ext->offset_delta);

			frames[i] = (struct StackMapFrame *)same_ext;
		}

		else if (curr_frame_type <= 254) // append
		{
			struct StackMapFrame_append *append = calloc(1, sizeof(struct StackMapFrame_append));
			append->frame_type = curr_frame_type;

			fread(&append->offset_delta, 2, 1, file);
			append->offset_delta = Big2(append->offset_delta);

			append->locals = NULL;
			if (curr_frame_type > 251)
			{
				append->locals = calloc(curr_frame_type - 251, sizeof(struct VerificationInfo));
				r = ReadVerificationInfo(file, append->locals, 1);
			}

			frames[i] = (struct StackMapFrame *)append;
		}

		else //if (curr_frame_type == 255) // full
		{
			struct StackMapFrame_full *full = calloc(1, sizeof(struct StackMapFrame_full));
			full->frame_type = curr_frame_type;

			fread(&full->offset_delta, 2, 1, file);
			full->offset_delta = Big2(full->offset_delta);

			fread(&full->number_of_locals, 2, 1, file);
			full->number_of_locals = Big2(full->number_of_locals);

			full->locals = NULL;
			if (full->number_of_locals > 0)
			{
				full->locals = calloc(full->number_of_locals, sizeof(struct VerificationInfo));
				r = ReadVerificationInfo(file, full->locals, full->number_of_locals);
			}

			fread(&full->number_of_stack_items, 2, 1, file);
			full->number_of_stack_items = Big2(full->number_of_stack_items);

			full->stack = NULL;
			if (full->number_of_stack_items > 0)
			{
				full->stack = calloc(full->number_of_stack_items, sizeof(struct VerificationInfo));
				r = ReadVerificationInfo(file, full->stack, full->number_of_stack_items);
			}

			frames[i] = (struct StackMapFrame *)full;
		}
	}

	return r;
}

JRESULT ReadAttribute_StackMapTable(FILE *file, ATTRIBUTE_StackMapTable *attribute, u4 attribute_length, CONSTANT **constant_pool)
{
	JRESULT r = 0;

	fread(&attribute->number_of_entries, 2, 1, file);
	attribute->number_of_entries = Big2(attribute->number_of_entries);

	attribute->entries = NULL;
	if (attribute->number_of_entries > 0)
	{
		attribute->entries = calloc(attribute->number_of_entries, sizeof(struct StackMapFrame *));
		ReadStackFrames(file, attribute->entries, attribute->number_of_entries);
	}

	return r;
}

void FreeAttribute_StackMapTable(ATTRIBUTE_StackMapTable *attribute, CONSTANT **constant_pool)
{
	if (attribute->number_of_entries == 0 || attribute->entries == NULL) return;

	struct StackMapFrame *curr_frame = NULL;
	for (int i = 0; i < attribute->number_of_entries; i++)
	{
		curr_frame = attribute->entries[i];
		if (curr_frame->frame_type <= 63) // same
		{ }
		else if (curr_frame->frame_type <= 127) // same_locals
		{ }
		else if (curr_frame->frame_type <= 246) // unused
		{ return; }
		else if (curr_frame->frame_type == 247) // same_locals_ext
		{ }
		else if (curr_frame->frame_type <= 250) // chop
		{ }
		else if (curr_frame->frame_type == 251) // same_ext
		{ }
		else if (curr_frame->frame_type <= 254) // append
		{
			struct StackMapFrame_append *append = (struct StackMapFrame_append *)curr_frame;
			free(append->locals);
		}
		else //if (curr_frame->frame_type == 255) // full
		{
			struct StackMapFrame_full *full = (struct StackMapFrame_full *)curr_frame;
			free(full->locals);
			free(full->stack);
		}
		free(curr_frame);
	}
	free(attribute->entries);
}
