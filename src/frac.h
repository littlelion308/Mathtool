#ifndef FRAC
#define FRAC
// This is a number construct, ti display, and work with rational Numbers
typedef struct {
	unsigned int denominator;
	int numerator;
} frac;
#endif
// fi denominator equals 0, optimize will equal INT_MAX/0

int gcd(int a, int b);
frac optimise(frac a);
frac makeFrac(int denominator, int numerator);
double toDouble(frac a);
float toFloat(frac a);
void printFrac(frac a);
frac add(frac a, frac b);
frac sub(frac a, frac b);
frac mpl(frac a, frac b);
frac div(frac a, frac b);
frac power(frac base, int exponent);
