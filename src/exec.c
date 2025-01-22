#include "frac.h"
#include <stdio.h>

void testFrac() {
	frac fracA = makeFrac(8,-6);
	frac fracB_infty = makeFrac(1,0);
	frac fracC_zero  = makeFrac(0,99);
	printf("optimising fracA:%2d/%2d; fracB:%11d/%1d; fracC:%1d/%2d\n", fracA.numerator,fracA.denominator, fracB_infty.numerator ,fracB_infty.denominator, fracC_zero.numerator, fracC_zero.denominator);
	fracA 		= optimise(fracA);
	fracB_infty 	= optimise(fracB_infty);
	fracC_zero 	= optimise(fracC_zero);
	printf("to:        fracA:%2d/%2d; fracB:%11d/%1d; fracC:%1d/%2d\n", fracA.numerator,fracA.denominator, fracB_infty.numerator ,fracB_infty.denominator, fracC_zero.numerator, fracC_zero.denominator);
	frac fracD = add(fracA, fracB_infty);
	frac fracE = add(fracA, fracC_zero);
	printf("adding fracA and fracB as fracD: %d/%d, and fracA and fracC as fracE: %d/%d\n", fracD.numerator, fracD.denominator, fracE.numerator, fracE.denominator);
	printf("subing fracA and fracB as _    : %d/%d, and fracA and fracE as _    : %d/%d\n", sub(fracA,fracB_infty).numerator, sub(fracA,fracB_infty).denominator, sub(fracA,fracE      ).numerator, sub(fracA,fracE      ).denominator);
	fracD = mpl(fracA, fracB_infty);
	fracE = mpl(fracA, fracC_zero);
	printf("mpling fracA and fracB as fracD: %d/%d, and fracA and fracC as fracE: %d/%d\n", fracD.numerator, fracD.denominator, fracE.numerator, fracE.denominator);
	fracD = div(fracA, fracB_infty);
	fracE = div(fracA, fracC_zero);
	printf("diving fracA and fracB as fracD: %d/%d, and fracA and fracC as fracE: %d/%d\n", fracD.numerator, fracD.denominator, fracE.numerator, fracE.denominator);
	printFrac(power(fracA, -2));
}

int main() {
	printf("%d\n", gcd(20,31));
	testFrac();
	return 0;
}

