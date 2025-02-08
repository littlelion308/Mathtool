#include "num.h"
#include <limits.h>
#include <stdio.h>

realnum optimiseRealnum(realnum a) {
	int num = a.numerator;
	int den = a.denominator;
	realnum ret;
	if (num == 0) {
		ret.numerator = 0;
		ret.denominator = 1;
		return ret;
	}
	if (den < 0) {
		num *= -1;
		den *= -1;
	}
	if (den == 0) {
		ret.numerator = num > 0 ? INT_MAX : INT_MIN;
		ret.denominator = 0;
		return ret;
	}
	int div = gcd(num, den);
	ret.numerator = num/div;
	ret.denominator = den/div;
	return ret;
}

// writtern in case it ever gets needed
/* realnum static extend(realnum a, int b) { */
/* 	return  makerealnum(a.numerator * b, a.denominator * b); */
/* } */

realnum addRealnum(realnum a, realnum b) {
	a = makerealnum((a.numerator * b.denominator) + (b.numerator * a.denominator), a.denominator * b.denominator);
	return optimise(a);
}

realnum subRealnum(realnum a, realnum b) {
	return optimise(makerealnum((a.numerator * b.denominator) - (b.numerator * a.denominator), a.denominator * b.denominator));
}

realnum mplRealnum(realnum a, realnum b) {
	a = makerealnum(a.numerator * b.numerator, a.denominator * b.denominator);
	return optimise(a);
}

realnum divRealnum(realnum a, realnum b) {
	return optimise(makerealnum(a.numerator * b.denominator, a.denominator * b.numerator));

}
/* realnum power(realnum a, realnum b) {} */

realnum powerRealnumInt(realnum base, int exponent) {
	realnum ret = base;
	if (exponent == 0) return makerealnum(1,1);
	if (exponent > 1)
		for (; exponent > 1; exponent--)
			ret = mpl(ret, base);
	else if (exponent < 0)
		for (; exponent < 1; exponent++)
			ret = div(ret, base);
	return ret;
}

realnum makerealnum(int numerator, int denominator) {
	realnum ret;
	ret.denominator = denominator;
	ret.numerator   = numerator;
	return ret;
}
double realnumToDouble(realnum a) {
	return a.numerator/a.denominator;
}
float realnumToFloat(realnum a) {
	return a.numerator/a.denominator;
}

void printRealnum(realnum a) {
	printf("%d/%d\n", a.numerator, a. denominator);
}
