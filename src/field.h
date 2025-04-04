#include "group.h"

#ifndef GENOPSSTR
#define GENOPSSTR
typedef struct {
	void *(*optimise)(void *a);	//i.e. make 2/4 into 1/2
	void *(*copy)(void *a);		// return a new pointer to the same Addres
	void (*mFree)(void *a);		// free the used memory
} genops;
#endif
#ifndef FIELD

#define FIELD
typedef struct {
	group add;
	group mpl;
	genops gen;
	const char name[10];
} field;

typedef struct {
	void *val;
	field *field;
} fieldVar;
#endif
