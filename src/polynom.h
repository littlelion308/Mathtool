#include "field.h"
#include "ring.h"
#include "divableRing.h"
#include "genericVar.h"

// For deriving / Integrating
#include "frac.h"

#ifndef POLYNOM
#define POLYNOM
typedef struct {
	unsigned int deg;
	fieldVar p[];
} polynom;
// polynom a;
// a.p = {0,1,2,3,4}
// => f(x) ^= 4x^4 + 3x^3 + 2x^2 + 1x + 0
#endif

//////////// Specific
////// general operations on any Ring, here in Polynoms over realnum////
// divide Polynoms
divisorremainder divPolynom(ringVar *numerator, ringVar *denominator);

////// Polynom or Function specific functions
// calculates the derivative of f, usualy calles f' // Only works over Real and Rational Numbers
ringVar *derivePolynom(ringVar *f);
// Calculates the standard Integral of f, commonly called F
ringVar *intergrate(ringVar *f);







// general fkjdhaskjflhasl
//// generic
const ring getPolynomRing(field *f);
void *copyPolynom(void *f);
void freePolynom(void *f);
void *optimisePolynom(void *f);

//// Add
// adds the tow given Polynoms together.
void *addPolynom(void *f, void *g);

void *addInvertPolynom(void *f);
void *subPolynom(void *f, void *g);

//// Mpl
// multiplies the tow given Polynoms.
void *mplPolynom(void *f, void *g);


/////// Specific
// Turns the list of descending nums and the deg into a polynom.
polynom makePolynom(fieldVar a[], int deg);

// Calculates the value of a given polynom a location x.
fieldVar *calcPolynom(ringVar *f, void *x);
