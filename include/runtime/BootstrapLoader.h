#ifndef RUNTIME_BOOTSTRAPLOADER_H_
#define RUNTIME_BOOTSTRAPLOADER_H_

#include "../WideTypes.h"
#include "Class.h"
#include <stdio.h>

JRESULT Bootstrap_LoadClassFromFile(FILE *classfile, CLASS *clazz);

#endif /* RUNTIME_BOOTSTRAPLOADER_H_ */
