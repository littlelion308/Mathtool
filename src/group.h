#ifndef GROUP
#define GROUP
typedef struct {
	void *(*op)(void *a, void *b); 	// i.e. add a + b
	void *neutral;			// i.e. 0
	void *(*invert)(void *a); 	// i.e. -a
	void *(*invOp)(void *a, void *b);//i.e. a - b
} group;
#endif
