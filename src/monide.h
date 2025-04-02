#ifndef MONOID
#define MONOID
typedef struct {
	void *(*op)(void *a, void *b); 	// i.e. mpl a * b
	void *neutral; 			// i.e. 1
	void *(*copy)(void *a);		// return a new pointer to the same Addres
} monoid;
#endif
