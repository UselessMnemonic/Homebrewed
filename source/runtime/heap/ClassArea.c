#include "runtime/heap/ClassArea.h"
#include <string.h>

/*
 * The Class Area has a fixed size in this implementation. One may
 * decide to pre-allocate space and grow the Class Area dynamically.
 */
#define MAX_NUMBER_OF_CLASSES 256

static CLASS CLASSAREA[MAX_NUMBER_OF_CLASSES];
static uint8_t IS_USED[MAX_NUMBER_OF_CLASSES];

CLASS* ClassArea_AllocClass()
{
	for (int i = 0; i < MAX_NUMBER_OF_CLASSES; i++)
	{
		if (!IS_USED[i])
		{
			IS_USED[i] = 1;
			return memset(&CLASSAREA[i], 0, sizeof(CLASS));
		}
	}
	return NULL;
}

void ClassArea_FreeClass(CLASS* clazz)
{
	for (int i = 0; i < MAX_NUMBER_OF_CLASSES; i++)
	{
		if (&CLASSAREA[i] == clazz && IS_USED[i])
		{
			IS_USED[i] = 0;
			return;
		}
	}
}
