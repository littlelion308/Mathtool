// decided the algorithmes should also work in other real Numbers
// thogh this schould start later
#include "frac.h"

#ifndef REELNUM
#define REELNUM
typedef frac realnum;
#endif

realnum optimiseRealnum(realnum a);
realnum makerealnum(int numerator, int denominator);
double realnumToDouble(realnum a);
float realnumToFloat(realnum a);
void printRealnum(realnum a);
realnum addRealnum(realnum a, realnum b);
realnum subRealnum(realnum a, realnum b);
realnum mplRealnum(realnum a, realnum b);
realnum divRealnum(realnum a, realnum b);
realnum powerRealnumInt(realnum base, int exponent);
