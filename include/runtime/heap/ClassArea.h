#ifndef RUNTIME_HEAP_CLASSAREA_H_
#define RUNTIME_HEAP_CLASSAREA_H_

#include "../Class.h"

/*
 * Allocates space for a class structure in the Class area.
 * If the return is NULL, no class can be allocated.
 *
 * This function does not load any class; such a job is
 * left for a Class Loader.
 */
CLASS* ClassArea_AllocClass();

/*
 * Deallocates a class structure from the Class area,
 * making space for future classes.
 *
 * This function does not unload a any class; such a job
 * is left for a Class Loader. (TODO)
 */
void ClassArea_FreeClass(CLASS* clazz);

#endif /* RUNTIME_HEAP_CLASSAREA_H_ */
