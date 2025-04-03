#include "monide.h"
#include "group.h"

#ifndef RING
#define RING
typedef struct {
	group add;
	monoid mpl;
	void (*optimise)(void *a);	//i.e. make 2/4 into 1/2
} ring;

typedef struct {
	void *val;
	ring *ring;
} ringVar;
#endif
