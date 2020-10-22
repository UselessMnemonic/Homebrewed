#include "util/FileReading.h"

JRESULT FILE_ReadArrayU2(u2 *array, size_t count, FILE *file)
{
	JRESULT r = 0;
	fread(array, 2, count, file);
	for (int i = 0; i < count; i++)
	{
		array[i] = Big2(array[i]);
	}
	return r;
}
