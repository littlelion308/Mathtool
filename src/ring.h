#include "monide.h"
#include "group.h"

#ifndef GENOPSSTR
#define GENOPSSTR
typedef struct {
	void *(*optimise)(void *a);	//i.e. make 2/4 into 1/2
	void *(*copy)(void *a);		// return a new pointer to the same Addres
	void (*mFree)(void *a);		// free the used memory
} genops;
#endif


#ifndef RING
#define RING
typedef struct {
	group add;
	monoid mpl;
	genops gen;
	const char name[10];
} ring;

typedef struct {
	void *val;
	ring *ring;
} ringVar;
#endif

