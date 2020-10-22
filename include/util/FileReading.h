#ifndef UTIL_FILEREADING_H_
#define UTIL_FILEREADING_H_

#include "../WideTypes.h"
#include <stdio.h>

/*
 * Reads an array of U2 from a file
 */
JRESULT FILE_ReadArrayU2(u2 *array, size_t count, FILE *file);

#endif /* UTIL_FILEREADING_H_ */
