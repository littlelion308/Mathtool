#include "monide.h"
#include "group.h"

#include "ring.h"

#ifndef DIVRING
#define DIVRING
typedef struct {
	ringVar divisor;
	ringVar remainder;
} divisorremainder;
#endif
