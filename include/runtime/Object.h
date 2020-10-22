#ifndef RUNTIME_OBJECT_H_
#define RUNTIME_OBJECT_H_

#include "../WideTypes.h"
#include "Class.h"

typedef struct OBJECT OBJECT;
typedef struct CLASS CLASS;

struct OBJECT {
	CLASS *clazz;
	void **fields;
};

/*
 * Initializes a new object in a pre-allocated object
 * structure.
 *
 * obj
 *   A pointer to a pre-allcoated object structure
 *
 * clazz
 *   A pointer to the class definition from which the
 *   object will be initialized
 */
JRESULT OBJECT_new(OBJECT *obj, CLASS *clazz);

#endif /* RUNTIME_OBJECT_H_ */
