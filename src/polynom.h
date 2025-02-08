#include "num.h"
#include <stdbool.h>

#ifndef POLYNOM
#define POLYNOM
typedef struct {
	int deg;
	num p[];
} polynom;
// polynom a;
// a.p = {0,1,2,3,4}
// => f(x) ^= 4x^4 + 3x^3 + 2x^2 + 1x + 0
typedef struct {
	bool remIsNull;
	polynom remainder;
	polynom f;
} divisoremainder;
#endif

////// general operations on any Ring, here in Polynoms over realnum////
// Turns the list of descending nums and the deg into a polynom.
polynom makePolynom(num a[], int deg);
// adds the tow given Polynoms together.
polynom addPolynom(polynom f, polynom g);
// multiplies the tow given Polynoms.
polynom mplPolynom(polynom f, polynom g);
// divide Polynoms
divisoremainder divPolynom(polynom numerator, polynom denominator);

////// Polynom or Function specific functions
// Calculates the value of a given polynom a location x.
num calcPolynom(polynom f, num x);
// calculates the derivative of f, usualy calles f'
polynom derivePolynom(polynom f);
// Calculates the standard Integral of f, commonly called F
polynom intergrate(polynom f);
