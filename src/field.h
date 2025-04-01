#include "group.h"

typedef struct {
	group add;
	group mpl;
	void (*optimise)(void *a);	//i.e. make 2/4 into 1/2
} field;
