#include "monide.h"
#include "group.h"

typedef struct {
	group add;
	monoid mpl;
	void (*optimise)(void *a);	//i.e. make 2/4 into 1/2
} ring;
