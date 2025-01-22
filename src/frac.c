#include "frac.h"
#include <stdio.h>
#include <limits.h>

int gcd(int a, int b) {
	if (a < 0) a = (-a);
	if (b < 0) b = (-b);
	if (a == b) return a;
	if (a < b) {
		int get = a;
		a = b;
		b = get;
	}
//      a > b
	int rem = a % b;
	if (rem == 0) return b;
	return gcd(b, rem);


}

frac optimise(frac a) {
	int num = a.numerator;
	int den = a.denominator;
	frac ret;
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

frac static extend(frac a, int b) {
	return  makeFrac(a.numerator * b, a.denominator * b);
}

frac add(frac a, frac b) {
	a = makeFrac((a.numerator * b.denominator) + (b.numerator * a.denominator), a.denominator * b.denominator);
	return optimise(a);
}

frac sub(frac a, frac b) {
	return optimise(makeFrac((a.numerator * b.denominator) - (b.numerator * a.denominator), a.denominator * b.denominator));
}

frac mpl(frac a, frac b) {
	a = makeFrac(a.numerator * b.numerator, a.denominator * b.denominator);
	return optimise(a);
}

frac div(frac a, frac b) {
	return optimise(makeFrac(a.numerator * b.denominator, a.denominator * b.numerator));

}
/* frac power(frac a, frac b) {} */

frac power(frac base, int exponent) {
	frac ret = base;
	if (exponent == 0) return makeFrac(1,1);
	if (exponent > 1)
		for (; exponent > 1; exponent--)
			ret = mpl(ret, base);
	else if (exponent < 0)
		for (; exponent < 1; exponent++)
			ret = div(ret, base);
	return ret;
}

frac makeFrac(int numerator, int denominator) {
	frac ret;
	ret.denominator = denominator;
	ret.numerator   = numerator;
	return ret;
}
double toDouble(frac a) {
	return a.numerator/a.denominator;
}
float toFloat(frac a) {
	return a.numerator/a.denominator;
}

void printFrac(frac a) {
	printf("%d/%d\n", a.numerator, a. denominator);
}
