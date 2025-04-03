#include "field.h"
#include "ring.h"
#include "genericVar.h"

#ifndef FRAC
#define FRAC
// This is a number construct, ti display, and work with rational Numbers
typedef struct {
	unsigned int denominator;
	int numerator;
} frac;
#endif
// fi denominator equals 0, optimize will equal INT_MAX/0

//spcific
int gcd(int a, int b);
frac makeFrac(int numerator, int denominator);
double toDouble(frac a);
float toFloat(frac a);
void printFrac(frac a);
frac power(frac base, int exponent);

// generic
field getFracField();
ring getFracRing();
void optimiseFrac(void *a);
void *copyFrac(void *a);
void freeFrac(void *a);

// add
void *addFrac(void *a, void *b);
void *subFromZeroFrac(void *a);
void *subFrac(void *a, void *b);

// multipy
void *mplFrac(void *a, void *b);
void *mplMOneFrac(void *a);
void *divideFrac(void *a, void *b);
