#include "field.h"
#include "ring.h"

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
void optimise(void *a);
void *copy(void *a);

// add
void *add(void *a, void *b);
void *subFromZero(void *a);
void *sub(void *a, void *b);

// multipy
void *mpl(void *a, void *b);
void *mplMOne(void *a);
void *divide(void *a, void *b);
