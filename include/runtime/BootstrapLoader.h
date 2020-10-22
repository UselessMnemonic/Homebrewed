#ifndef RUNTIME_BOOTSTRAPLOADER_H_
#define RUNTIME_BOOTSTRAPLOADER_H_

#include "../WideTypes.h"
#include "Class.h"

JRESULT Bootstrap_LoadClassFromFile(const char* filename, CLASS *clazz);

#endif /* RUNTIME_BOOTSTRAPLOADER_H_ */
