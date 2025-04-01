#include "frac.h"
#include <stdio.h>

void testFrac() {
	frac fracA = makeFrac(8,-6);
	frac fracB_infty = makeFrac(1,0);
	frac fracC_zero  = makeFrac(0,99);

	frac *fPa = &fracA;
	frac *fPb = &fracB_infty;
	frac *fPc = &fracC_zero;
	printf("optimising fracA:%2d/%2d; fracB:%11d/%1d; fracC:%1d/%2d\n", fracA.numerator,fracA.denominator, fracB_infty.numerator ,fracB_infty.denominator, fracC_zero.numerator, fracC_zero.denominator);
	optimise(fPa);
	optimise(fPb);
	optimise(fPc);
	printf("to:        fracA:%2d/%2d; fracB:%11d/%1d; fracC:%1d/%2d\n", fracA.numerator,fracA.denominator, fracB_infty.numerator ,fracB_infty.denominator, fracC_zero.numerator, fracC_zero.denominator);
	frac *fracD = add(fPa, fPb);
	frac *fracE = add(fPa, fPc);
	printf("adding fracA and fracB as fracD: %d/%d, and fracA and fracC as fracE: %d/%d\n", fracD->numerator, fracD->denominator, fracE->numerator, fracE->denominator);
	printf("subing fracA and fracB as _    : %d/%d, and fracA and fracE as _    : %d/%d\n", ((frac *)sub(fPa,fPb))->numerator, ((frac *)sub(fPa,fPb))->denominator, ((frac *)sub(fPa,fracE      ))->numerator, ((frac *)sub(fPa,fracE      ))->denominator);
	fracD = mpl(fPa, fPb);
	fracE = mpl(fPa, fPb);
	printf("mpling fracA and fracB as fracD: %d/%d, and fracA and fracC as fracE: %d/%d\n", fracD->numerator, fracD->denominator, fracE->numerator, fracE->denominator);
	fracD = divide(fPa, fPb);
	fracE = divide(fPa, fPc);
	printf("diving fracA and fracB as fracD: %d/%d, and fracA and fracC as fracE: %d/%d\n", fracD->numerator, fracD->denominator, fracE->numerator, fracE->denominator);
	printFrac(power(fracA, -2));
}

int main() {
	printf("%d\n", gcd(20,31));
	testFrac();
	return 0;
}

